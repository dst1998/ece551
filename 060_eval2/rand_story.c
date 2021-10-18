#include "rand_story.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int check_underscore(FILE * f) {
  char * line = NULL;
  size_t sz = 0;
  char * p =
      NULL;  // p will ponits to every char in the line got by getline fuction later.
  //reading lines from the file f.
  while (getline(&line, &sz, f) >= 0) {
    // printf("check in it success.\n");  //
    p = line;
    int cnt = 0;  //record the number of underscore in a line.
    //counting the number of underscore in a line.
    while (*p != '\n') {
      if (*p == '_') {
        cnt++;
      }
      p++;
    }
    //printf("cnt= %d\n", cnt);  //
    //exit if the number of underscore in line is odd.
    if (cnt % 2 != 0) {
      printf("Wrong number of underscore in a line!\n");
      free(line);
      return EXIT_FAILURE;
    }
  }
  free(line);
  //printf("check with success.\n");  //
  return EXIT_SUCCESS;
}

void replaceBlank(FILE * f, catarray_t * cats) {
  //printf("in replaceblank.\n");  //
  char * line = NULL;
  size_t sz = 0;
  char * p = NULL;
  // p will ponits to every char in the line got by getline fuction later.
  //reading lines from the file f.
  int len = 0;
  category_t * usedWords = malloc(sizeof(*usedWords));
  usedWords->words = NULL;
  usedWords->n_words = 0;
  char * dest = NULL;
  while ((len = getline(&line, &sz, f)) >= 0) {
    //printf("len = %d\n", len);  //
    p = line;
    int underscore =
        0;  // become 1 if the beginning underscore of a category name appears.
    char * category =
        NULL;   //string for storing category name from input story template file.
    int i = 0;  //record the number of char of a category name.
    while (*p != '\0') {
      if (underscore == 0) {  // no beginning undersocre has appeared.
        if (*p != '_') {
          printf("%c", *p);
        }
        else {
          underscore = 1;
        }
      }

      else {  //beginning underscore of a blank appears.
        if (*p != '_') {
          category = realloc(category, (i + 1) * sizeof(*category));
          category[i] = *p;
          i++;
        }
        else {  //ending underscore appears, and category name captured.
          underscore = 0;
          category = realloc(category, (i + 1) * sizeof(*category));
          category[i] = '\0';
          //printf("%s", chooseWord(category, cats));
          dest = judgeBlank(category, cats, usedWords);
          printf("%s", dest);
          usedWords->words = realloc(
              usedWords->words, (usedWords->n_words + 1) * sizeof(*usedWords->words));
          usedWords->words[usedWords->n_words] =
              dest;  ///////////////////////////////////
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

char * judgeBlank(char * blank, catarray_t * cats, category_t * usedWords) {
  char * dest = NULL;
  char * tmp;
  const char * tmp1;
  int len = 0;
  //if(blank[0])
  int num = atoi(blank);
  if (num != 0) {
    tmp = usedWords->words[usedWords->n_words - num];
    len = 1 + strlen(tmp);
    dest = realloc(dest, len * sizeof(*dest));
    int i = 0;
    while (tmp[i] != '\0') {
      dest[i] = tmp[i];
      i++;
    }
    dest[i] = '\0';
    return dest;
  }
  //return chooseWord(blank, cats);
  tmp1 = chooseWord(blank, cats);
  len = 1 + strlen(tmp1);
  dest = realloc(dest, len * sizeof(*dest));
  //strcpy(dest, tmp1);
  int i = 0;
  while (tmp1[i] != '\0') {
    dest[i] = tmp1[i];
    i++;
  }
  dest[i] = '\0';
  return dest;
}

//check if there is a colon in every line in the file.
int check_colon(FILE * f) {
  char * line = NULL;
  size_t sz = 0;
  char * p =
      NULL;  // p will ponits to every char in the line got by getline fuction later.
  //reading lines from the file f.
  while (getline(&line, &sz, f) >= 0) {
    // printf("check in it success.\n");  //
    p = line;
    int cnt = 0;  //record the number of colon in a line.
    //counting the number of colon in a line.
    while (*p != '\0') {
      if (*p == ':') {
        cnt++;
      }
      p++;
    }
    //printf("cnt= %d\n", cnt);  //
    //exit if the number of underscore in line is odd.
    if (cnt != 1) {
      printf("Wrong number of colon in a line!\n");
      free(line);
      return EXIT_FAILURE;
    }
  }
  free(line);
  //printf("check with success.\n");  //
  return EXIT_SUCCESS;
}

catarray_t * readCate(FILE * f, catarray_t * cats) {
  char * line = NULL;
  size_t sz = 0;
  char * p = NULL;
  // p will ponits to every char in the line got by getline fuction later.
  //reading lines from the file f.
  int len = 0;  //

  while ((len = getline(&line, &sz, f)) >= 0) {
    //printf("len = %d\n", len);  //
    p = line;
    int colon = 0;  // become 1 if the colon appears.
    char * category =
        NULL;  //string for storing category name from input story template file.
    char * word = NULL;  //string for stroring word of the category.
    size_t i = 0;        //record the number of char of a category name.
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
        }
      }

      else {  //a colon has appeared.
        word = realloc(word, (i + 1) * sizeof(*word));
        word[i] = *p;
        i++;
      }
      p++;
    }
    word = realloc(word, (i + 1) * sizeof(*word));
    word[i] = '\0';  //word captured.

    if (cats->n == 0) {  //malloc if array has nothing.
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

  //printf("len = %d\n", len);
  return cats;
}
