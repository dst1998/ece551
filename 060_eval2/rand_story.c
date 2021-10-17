#include "rand_story.h"

#include "stdio.h"
#include "stdlib.h"

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
          category[i] = '\0';
          printf("%s", chooseWord(category, cats));
          i = 0;
          free(category);
          category = NULL;
        }
      }
      p++;
    }
  }
  free(line);
  //printf("len = %d\n", len);
}
