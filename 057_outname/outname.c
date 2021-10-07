#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * p = inputName;
  int cnt = 0;
  while (*p != '\0') {
    cnt++;
    p++;
  }
  char * outname = malloc(cnt + 8);
  p = inputName;
  int i = 0;
  while (*p != '\0') {
    outname[i++] = *p;
    p++;
  }
  outname[i++] = '.';
  outname[i++] = 'c';
  outname[i++] = 'o';
  outname[i++] = 'u';
  outname[i++] = 'n';
  outname[i++] = 't';
  outname[i++] = 's';
  outname[i++] = '\0';
  return outname;
}
