#include "rand_story.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    perror("Wrong number of command line argiments!\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Cannot open the input file!\n");
    exit(EXIT_FAILURE);
  }
  //print if the number of underscore is correct.
  if (check_underscore(f)) {  //return 0, checking done with success.
    exit(EXIT_FAILURE);
  }
  rewind(f);  //make f back to the beginning of file.
  replaceBlank(f, NULL, 0);

  if (fclose(f)) {
    perror("Cannot close the input file!\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
