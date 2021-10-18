#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include "stdio.h"

//any functions you want your main to use

//check if the number of underscore in each line is a even.
int check_underscore(FILE * f);
//check if the blank is under requirement.//
int check_blank(FILE * f, catarray_t * cats, int usedOnce);
//replace blank with category name and print.
void replaceBlank(FILE * f, catarray_t * cats, int usedOnce);
//judge if the blank is catagory or valid int.
char * judgeBlank(char * blank, catarray_t * cats, category_t * usedWords, int usedOnce);
//check if there is a colon in every line in the file.
int check_colon(FILE * f);
//read the category/words from file f and stored in catarray cats.
catarray_t * readCate(FILE * f, catarray_t * cats);
#endif
