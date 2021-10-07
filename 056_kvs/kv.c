#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    return NULL;
  }
  kvarray_t * p = malloc(sizeof(*p));
  p->array = NULL;
  p->len = 0;
  size_t sz = 0;
  //size_t l = 0;
  char * line = NULL;
  char * b = NULL;  //b to find where the first '=' is.
  char * c = NULL;  //c to find whre the '\n'is.
  int i = 0;        //length of p->array.
  while ((getline(&line, &sz, f)) >= 0) {
    p->array = realloc(p->array, (i + 1) * sizeof(*(p->array)));
    p->array[i] = malloc(sizeof(*(p->array[i])));
    //(p->array[i])->key = malloc(sizeof(*(p->array[i]->key)));
    //(p->array[i])->value = malloc(sizeof(*(p->array[i]->value)));

    b = strchr(line, '=');
    *b = '\0';
    p->array[i]->key = line;
    b++;
    c = strchr(b, '\n');
    if (c != NULL)
      *c = '\0';
    p->array[i]->value = b;
    line = NULL;
    i++;
  }
  free(line);
  p->len = i;
  if (fclose(f) == 0) {
    return p;
  }
  return NULL;  //
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->len; i++) {
    free((pairs->array[i])->key);
    //free((pairs->array[i])->value);
    free(pairs->array[i]);
  }
  free(pairs->array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->len; i++) {
    printf("key = '%s' value = '%s'\n", pairs->array[i]->key, pairs->array[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  int i = 0;
  for (i = 0; i < pairs->len; i++) {
    if (!strcmp(key, (pairs->array[i])->key)) {
      return (pairs->array[i])->value;
    }
  }
  return NULL;
}
