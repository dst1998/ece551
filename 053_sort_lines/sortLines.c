#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  char ** lines = NULL;
  char * line = NULL;
  size_t sz = 0;
  size_t i = 0;
  size_t j = 0;
  if (argc == 1) {
    //printf("Please input strings wanted to be sorted.\n");

    while (getline(&line, &sz, stdin) >= 0) {
      lines = realloc(lines, (i + 1) * sizeof(*lines));
      lines[i] = line;
      line = NULL;
      i++;
    }
    free(line);
    sortData(lines, i);
    for (j = 0; j < i; j++) {
      printf("%s", lines[j]);
      free(lines[j]);
    }
    free(lines);
    //printf("Success of all processing!");
    return EXIT_SUCCESS;
  }

  for (int n = 1; n < argc; n++) {
    FILE * f = fopen(argv[n], "r");
    if (f == NULL) {
      perror("Could not open file");
      return EXIT_FAILURE;
    }
    line = NULL;
    lines = NULL;
    sz = 0;
    i = 0;
    while (getline(&line, &sz, f) >= 0) {
      lines = realloc(lines, (i + 1) * sizeof(*lines));
      lines[i] = line;
      line = NULL;
      i++;
    }
    free(line);
    sortData(lines, i);
    for (j = 0; j < i; j++) {
      printf("%s", lines[j]);
      free(lines[j]);
    }
    free(lines);
    if (fclose(f) != 0) {
      perror("Failed to close the input file!");
      return EXIT_FAILURE;
    }
  }
  //printf("Success of all processing!");
  return EXIT_SUCCESS;
}
