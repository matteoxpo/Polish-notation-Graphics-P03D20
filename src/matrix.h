#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

int allocMem(char ***matrix, int n, int m);
void freeMem(char **matrix, int n);
void output_matrix(char **matrix, int n, int m);
void turn_over(char **matrix, int n);
void swap(char **matrix, int i, int j);

#endif  // SRC_MATRIX_H_
