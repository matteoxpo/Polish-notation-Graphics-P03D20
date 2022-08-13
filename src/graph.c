#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#define OPERATIONS                                                         \
  "(", "+", "-", "*", "\\", "sin", "cos", "tan", "ctg", "sqrt", "ln", "^", \
      "~", ")"
#define COUNT_OPERATIONS 13

char* charInput();
struct stack* Polska(char* input);
int isNum(char c);
int validOperation(char* oper, int oper_count, char** operations);
int priorityOperation(char* oper, int oper_count, char** operations);
int main() {
  char* input = charInput();
  printf("%s", input);

  return 0;
}

char* charInput() {
  char* res = malloc(sizeof(char));
  int i = 0;
  while (1) {
    scanf("%c", &(res[i]));
    res = realloc(res, sizeof(char));
    if (res[i] == '\n') {
      res[i] = '\0';
      break;
    }
    i++;
  }
  return res;
}

struct stack* Polska(char* input) {
  int size = strlen(input);
  struct stack* res = malloc(size * sizeof(char));
  struct stack* oper = malloc(size * sizeof(char));
  char* temp = strtok(input, " ");
  while (temp != NULL) {
    if () {
    }
    temp = strtok(NULL, " ");
  }
  free(oper);
  return res;
}

int validOperation(char* oper, int oper_count, char** operations) {
  int res = 1;
  for (int i = 0; i < COUNT_OPERATIONS; i++) {
    if (!strcmp(oper, operations[i])) {
      res = 0;
      break;
    }
  }
  return res;
}

int priorityOperation(char* oper, int oper_count, char** operations) {
  int res = 0;
  for (int i = 0; i < COUNT_OPERATIONS; i++) {
    if (strcmp(oper, operations[i])) {
      if (i == 0) res = 0;
      if (i == 1 || i == 2) res = 1;
      if (i) }
  }
  return res;
}