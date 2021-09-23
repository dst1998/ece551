#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int count(int array[], int n) {
  int pos = 0;
  int value = array[0];
  for (int i = 0; i < n; i++) {
    if (value < array[i]) {
      value = array[i];
      pos = i;
    }
  }
  return pos;
}

int decrypt(FILE * f) {
  int c;
  int myarray[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      myarray[c - 'a'] += 1;
    }
  }
  int p = count(myarray, 26);
  return p - 4;  //"e"-"a"=4
}

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
  int key = decrypt(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  if (key < 0 || key >= 26) {
    fprintf(stderr, "Key is not the correct range.\n");
    return EXIT_FAILURE;
  }
  printf("%d\n", key);
  return EXIT_SUCCESS;
}
