#include "rand_story.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    printf("Wrong number of command line argiments!\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Cannot open the input file!\n");
    exit(EXIT_FAILURE);
  }
  //print if the number of underscore is correct.
  if (!check_colon(f)) {  //return 0, checking done with success.
    //printf("begin repalcing.\n");  //
    rewind(f);  //make f back to the beginning of file.
    catarray_t * cats = malloc(sizeof(*cats));
    // cats->arr = NULL;
    cats->n = 0;
    cats = readCate(f, cats);  //
    printWords(cats);

    for (size_t i = 0; i < cats->n; i++) {
      free(cats->arr[i].name);
      for (size_t j = 0; j < cats->arr[i].n_words; j++) {
        free(cats->arr[i].words[j]);
      }
      free(cats->arr[i].words);
    }
    free(cats->arr);
    free(cats);
  }
  if (fclose(f)) {
    printf("Cannot close the input file!\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
