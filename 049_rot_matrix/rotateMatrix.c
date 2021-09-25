#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  char matrix[10][10];
  int c;
  int i = 0, j = 0, a, b;
  while ((c = fgetc(f)) != EOF) {
    if (c != '\n') {
      if (i >= 10) {
        perror("wrong number of row");
        return EXIT_FAILURE;
      }
      matrix[j++][10 - i - 1] = c;
    }
    else {
      if (j != 10) {
        perror("wrong number of col");
        return EXIT_FAILURE;
      }
      i++;
      j = 0;
    }
  }
  if (i < 10) {
    perror("wrong number of row");
    return EXIT_FAILURE;
  }
  for (a = 0; a < 10; a++) {
    for (b = 0; b < 10; b++) {
      printf("%c", matrix[a][b]);
    }
    printf("\n");
  }
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
