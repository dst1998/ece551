#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include "stdio.h"

//any functions you want your main to use

//check if the number of underscore in each line is a even.
int check_underscore(FILE * f);
//replace blank with category name and print.
void replaceBlank(FILE * f, catarray_t * cats);
//check if there is a colon in every line in the file.
int check_colon(FILE * f);
catarray_t * readCate(FILE * f, catarray_t * cats);
#endif
