#include "rand_story.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    perror("Wrong number of command line argiments!\n");
    exit(EXIT_FAILURE);
  }
  FILE * f_words = fopen(argv[1], "r");
  if (f_words == NULL) {
    perror("Cannot open the words input file!\n");
    exit(EXIT_FAILURE);
  }

  if (check_colon(f_words)) {  //return 1, checking failed.
    exit(EXIT_FAILURE);
  }
  rewind(f_words);  //make f back to the beginning of file.
  catarray_t * cats = malloc(sizeof(*cats));
  cats->n = 0;
  cats = readCate(f_words, cats);
  //printWords(cats);

  FILE * f_story = fopen(argv[2], "r");
  if (f_story == NULL) {
    perror("Cannot open the story input file!\n");
    exit(EXIT_FAILURE);
  }
  //print if the number of underscore is correct.
  if (check_underscore(f_story)) {  //return 1, checking failed.
    exit(EXIT_FAILURE);
  }
  /////////////////////////////////
  rewind(f_story);                      //make f back to the beginning of file.
  if (check_blank(f_story, cats, 0)) {  //return 1, checking failed.
    exit(EXIT_FAILURE);
  }
  /////////////////////////////////
  rewind(f_story);  //make f back to the beginning of file.
  replaceBlank(f_story, cats, 0);

  for (size_t i = 0; i < cats->n; i++) {
    for (size_t j = 0; j < cats->arr[i].n_words; j++) {
      free(cats->arr[i].words[j]);
    }
    free(cats->arr[i].words);
    free(cats->arr[i].name);
  }

  free(cats->arr);
  free(cats);

  if (fclose(f_words)) {
    perror("Cannot close the words input file!\n");
    exit(EXIT_FAILURE);
  }
  if (fclose(f_story)) {
    perror("Cannot close the story input file!\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
