#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
int allocMem(char ***matrix, int n, int m) {
  int check = 1;
  (*matrix) = malloc(n * sizeof(char *));
  if (*matrix != NULL) {
    for (int i = 0; i < n; i++) {
      (*matrix)[i] = malloc(m * sizeof(char));
      if ((*matrix)[i] == NULL) {
        check = 0;
        for (int j = 0; j < i; j++) free((*matrix)[i]);
        free(matrix);
        break;
      }
    }
  } else {
    check = 0;
  }
  return check;
}

void freeMem(char **matrix, int n) {
  for (int i = 0; i < n; i++) free(matrix[i]);
  free(matrix);
}

void output_matrix(char **matrix, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%c", matrix[i][j]);
    }
    if (i != n - 1) printf("\n");
  }
}

void turn_over(char **matrix, int n) {
  for (int i = 0; i < n / 2; i++) {
    swap(matrix, i, n - 1 - i);
  }
}

void swap(char **matrix, int i, int j) {
  char *temp = matrix[i];
  matrix[i] = matrix[j];
  matrix[j] = temp;
}
