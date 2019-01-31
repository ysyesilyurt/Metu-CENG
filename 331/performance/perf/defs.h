/*
 * driver.h - Various definitions for the Performance Lab.
 * 
 * DO NOT MODIFY ANYTHING IN THIS FILE
 */
#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdlib.h>

#define RIDX(i,j,n) ((i)*(n)+(j))

typedef struct {
  char *team;
  char *name1, *email1;
  char *name2, *email2;
} team_t;

extern team_t team;



typedef void (*lab_test_func3) (int, int*, int*, int*);

typedef void (*lab_test_func5) (int, int*, int*, int*);


void convolution(int, int *,int *, int *);

void matrix_multiplication(int, int *,int *, int *);



void register_conv_functions(void);

void register_matrix_multiplication_functions(void);




void add_matrix_multiplication_function(lab_test_func3, char*);

void add_conv_function(lab_test_func5, char*);

#endif /* _DEFS_H_ */

