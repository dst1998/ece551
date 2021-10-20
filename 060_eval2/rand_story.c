#include "rand_story.h"

#include "errno.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int check_underscore(FILE * f) {
  char * line = NULL;
  size_t sz = 0;
  // p will ponits to every char in the line got by getline fuction later.
  char * p = NULL;
  //reading lines from the file f.
  while (getline(&line, &sz, f) >= 0) {
    p = line;
    //cnt records the number of underscore in a line.
    int cnt = 0;
    //counting the number of underscore in a line.
    while (*p != '\n') {
      if (*p == '_') {
        cnt++;
      }
      p++;
    }
    //exit if the number of underscore in line is odd.
    if (cnt % 2 != 0) {
      perror("Wrong number of underscore in a line!\n");
      free(line);
      return EXIT_FAILURE;
    }
  }
  free(line);
  return EXIT_SUCCESS;
}

int check_blank(FILE * f, catarray_t * cats, int usedOnce) {
  char * line = NULL;
  size_t sz = 0;
  char * p = NULL;
  // p will ponits to every char in the line got by getline fuction later.
  //reading lines from the file f.
  category_t * usedWords = malloc(sizeof(*usedWords));
  usedWords->words = NULL;
  usedWords->n_words = 0;
  char * dest = NULL;
  while (getline(&line, &sz, f) >= 0) {
    p = line;
    // "underscore" becomes 1 if the beginning underscore of a category name appears.
    int underscore = 0;
    //string for storing category name from input story template file.
    char * category = NULL;
    //record the number of char of a category name.
    int i = 0;
    while (*p != '\0') {
      // if: no beginning undersocre has appeared.
      if (underscore == 0) {
        if (*p == '_') {
          underscore = 1;
        }
      }
      //else: beginning underscore of a blank appears.
      else {
        if (*p != '_') {
          category = realloc(category, (i + 1) * sizeof(*category));
          category[i] = *p;
          i++;
        }
        //ending underscore appears, and category name captured.
        else {
          underscore = 0;
          category = realloc(category, (i + 1) * sizeof(*category));
          category[i] = '\0';
          //printf("%s", chooseWord(category, cats));
          dest = judgeBlank(category, cats, usedWords, usedOnce, 1);
          //printf("%s", dest);////
          usedWords->words = realloc(
              usedWords->words, (usedWords->n_words + 1) * sizeof(*usedWords->words));
          usedWords->words[usedWords->n_words] = dest;
          usedWords->n_words++;
          i = 0;
          free(category);
          category = NULL;
        }
      }
      p++;
    }
  }
  free(line);
  for (size_t i = 0; i < usedWords->n_words; i++) {
    free(usedWords->words[i]);
  }
  free(usedWords->words);
  free(usedWords);
  return EXIT_SUCCESS;
}

void replaceBlank(FILE * f, catarray_t * cats, int usedOnce) {
  char * line = NULL;
  size_t sz = 0;
  char * p = NULL;
  // p will ponits to every char in the line got by getline fuction later.
  //mallloc usedWords to store the words used.
  category_t * usedWords = malloc(sizeof(*usedWords));
  usedWords->words = NULL;
  usedWords->n_words = 0;
  char * dest = NULL;
  //reading lines from the file f.
  while (getline(&line, &sz, f) >= 0) {
    p = line;
    // "underscore" becomes 1 if the beginning underscore of a category name appears.
    int underscore = 0;
    //string for storing category name from input story template file.
    char * category = NULL;
    //record the number of char of a category name.
    int i = 0;
    while (*p != '\0') {
      // if: no beginning undersocre has appeared.
      if (underscore == 0) {
        if (*p != '_') {
          printf("%c", *p);
        }
        else {
          underscore = 1;
        }
      }
      //else: beginning underscore of a blank appears.
      else {
        if (*p != '_') {
          category = realloc(category, (i + 1) * sizeof(*category));
          category[i] = *p;
          i++;
        }
        //ending underscore appears, and category name captured.
        else {
          underscore = 0;
          category = realloc(category, (i + 1) * sizeof(*category));
          category[i] = '\0';
          dest = judgeBlank(category, cats, usedWords, usedOnce, 0);
          printf("%s", dest);
          usedWords->words = realloc(
              usedWords->words, (usedWords->n_words + 1) * sizeof(*usedWords->words));
          usedWords->words[usedWords->n_words] = dest;
          usedWords->n_words++;
          i = 0;
          free(category);
          category = NULL;
        }
      }
      p++;
    }
  }
  free(line);
  for (size_t i = 0; i < usedWords->n_words; i++) {
    free(usedWords->words[i]);
  }
  free(usedWords->words);
  free(usedWords);
}

char * judgeBlank(char * blank,
                  catarray_t * cats,
                  category_t * usedWords,
                  int usedOnce,
                  int firstCheck) {
  char * dest = NULL;
  char * p_u;        //pointer to certain word found in usedWords.
  const char * p_c;  //pointer to certain word choosen from cats.
  int len = 0;
  char * endptr = NULL;
  unsigned long int ul_num = strtoul(blank, &endptr, 0);
  //if errno==ERRANGE,blank cannot be transfered to a num.
  if (errno == ERANGE || usedWords->n_words < ul_num) {
    perror("Wrong int!\n");
    exit(EXIT_FAILURE);
  }
  //if only numbers (no chars) are in blank.
  if (ul_num != 0 && *endptr == '\0') {
    p_u = usedWords->words[usedWords->n_words - ul_num];
    len = 1 + strlen(p_u);
    dest = realloc(dest, len * sizeof(*dest));
    int i = 0;
    while (p_u[i] != '\0') {
      dest[i] = p_u[i];
      i++;
    }
    dest[i] = '\0';
    return dest;
  }
  //check: similar to chooseWord(blank, cats);
  if (firstCheck == 1) {
    if (notInclude(cats, blank) == NULL) {
      perror("Do not include this category.");
      exit(EXIT_FAILURE);
    }
    p_c = notInclude(cats, blank);
  }
  else {
    p_c = chooseWord(blank, cats);
  }
  len = 1 + strlen(p_c);
  dest = realloc(dest, len * sizeof(*dest));
  //strcpy(dest, tmp1);
  int i = 0;
  while (p_c[i] != '\0') {
    dest[i] = p_c[i];
    i++;
  }
  dest[i] = '\0';
  //delete used word this time if usedOnce is 1
  if (usedOnce) {
    int find = 0;
    for (size_t i = 0; i < cats->n; i++) {
      if (!strcmp(blank, cats->arr[i].name)) {
        for (size_t j = 0; j < cats->arr[i].n_words; j++) {
          if (!strcmp(p_c, cats->arr[i].words[j])) {
            //delete the word from the category.(switch to the end ,then resize the words)
            char * p = cats->arr[i].words[j];
            cats->arr[i].words[j] = cats->arr[i].words[cats->arr[i].n_words - 1];
            cats->arr[i].words[cats->arr[i].n_words - 1] = p;
            free(cats->arr[i].words[cats->arr[i].n_words - 1]);
            cats->arr[i].words =
                realloc(cats->arr[i].words,
                        (cats->arr[i].n_words - 1) * sizeof(*cats->arr[i].words));
            cats->arr[i].n_words--;
            find = 1;
            break;
          }
        }
      }
      if (find) {
        break;
      }
    }
  }
  return dest;
}
//use notInclude when checking,return the first word.
char * notInclude(catarray_t * cats, char * blank) {
  for (size_t i = 0; i < cats->n; i++) {
    if (!strcmp(blank, cats->arr[i].name) && cats->arr[i].n_words > 0) {
      return cats->arr[i].words[0];
    }
  }
  return NULL;
}

//check if there is a colon in every line in the file.
int check_colon(FILE * f) {
  char * line = NULL;
  size_t sz = 0;
  // p will ponits to every char in the line got by getline fuction later.
  char * p = NULL;
  //reading lines from the file f.
  while (getline(&line, &sz, f) >= 0) {
    p = line;
    //record the number of colon in a line.
    int cnt = 0;
    //counting the number of colon in a line.
    while (*p != '\0') {
      if (*p == ':') {
        cnt++;
      }
      p++;
    }
    //exit if the number of underscore in line is odd.
    if (cnt == 0) {
      perror("Wrong number of colon in a line!\n");
      free(line);
      return EXIT_FAILURE;
    }
  }
  free(line);
  return EXIT_SUCCESS;
}

catarray_t * readCate(FILE * f, catarray_t * cats) {
  char * line = NULL;
  size_t sz = 0;
  char * p = NULL;
  // p will ponits to every char in the line got by getline fuction later.
  //reading lines from the file f.
  while (getline(&line, &sz, f) >= 0) {
    p = line;
    //"colon" becomes 1 if the colon appears.
    int colon = 0;
    //string for storing category name from input story template file.
    char * category = NULL;
    //string for stroring word of the category.
    char * word = NULL;
    //record the number of char of a category/word.
    size_t i = 0;
    while (*p != '\n') {
      if (colon == 0) {  // no colon has appeared.
        if (*p != ':') {
          category = realloc(category, (i + 1) * sizeof(*category));
          category[i] = *p;
          i++;
        }
        else {
          colon = 1;
          category = realloc(category, (i + 1) * sizeof(*category));
          category[i] = '\0';  //category captured.
          i = 0;
          /*if (!strcmp(category, ":")) {  //if category is a colon ,exit.
            perror("Category cannot be a colon!\n");
            exit(EXIT_FAILURE);
	    }*/
        }
      }
      //a colon has appeared.
      else {
        word = realloc(word, (i + 1) * sizeof(*word));
        word[i] = *p;
        i++;
      }
      p++;
    }
    word = realloc(word, (i + 1) * sizeof(*word));
    word[i] = '\0';  //word captured.

    //malloc if array has nothing.
    if (cats->n == 0) {
      cats->arr = malloc(sizeof(*cats->arr));
      cats->arr[0].n_words = 0;
      cats->arr[0].name = category;
      cats->arr[0].words = malloc(sizeof(*cats->arr[cats->n].words));
      cats->arr[0].words[cats->arr[cats->n].n_words] = word;
      cats->arr[0].n_words++;
      cats->n++;
      continue;
    }

    i = 0;
    size_t j = 0;

    for (i = 0; i < cats->n; i++) {
      if (!strcmp(category, cats->arr[i].name)) {  //equals,category existed.
        free(category);
        for (j = 0; j < cats->arr[i].n_words; j++) {
          if (!strcmp(word, cats->arr[i].words[j])) {  //word existed.
            free(word);
            break;
          }
        }
        if (j != cats->arr[i].n_words) {
          continue;
        }
        cats->arr[i].words = realloc(
            cats->arr[i].words, (cats->arr[i].n_words + 1) * sizeof(*cats->arr[i].words));
        cats->arr[i].words[cats->arr[i].n_words] = word;
        cats->arr[i].n_words++;
        break;
      }
    }
    if (i != cats->n) {
      continue;
    }
    //realloc if array needs to be bigger.
    cats->arr = realloc(cats->arr, (cats->n + 1) * sizeof(*cats->arr));
    cats->arr[cats->n].n_words = 0;
    cats->arr[cats->n].name = category;
    cats->arr[cats->n].words = malloc(sizeof(*cats->arr[cats->n].words));
    cats->arr[cats->n].words[cats->arr[cats->n].n_words] = word;
    cats->arr[cats->n].n_words++;
    cats->n++;
  }
  free(line);
  return cats;
}
