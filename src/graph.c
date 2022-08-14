#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsing.h"
#include "stack.h"

char* charInput();
struct stack* Polska(char* input);

int main() {
  char* input = charInput();

  input = str_transformation(input);
  printf("%s\n", input);
  struct stack* res = Polska(input);
  printf("Time to look at stack\n");
  struct stack* rev = reverse(res);
  stack_output(res);
  destroy(res);
  printf("\n");
  stack_output(rev);
}

struct stack* Polska(char* input) {
  struct stack *res = NULL, *oper = NULL;
  char* num;
  while (*input != '\0') {
    if (is_math_symbol(*input) || is_func(*input)) {
      if (oper == NULL || priority_compare(*input, pick(oper))) {
        oper = push(oper, *input);
      } else {
        while (oper != NULL && !priority_compare(*input, pick(oper)) &&
               pick(oper) != '(') {
          res = push(res, pick(oper));
          oper = pop(oper);
        }
        oper = push(oper, *input);
        if (*input == '(') oper = push(oper, *input);
      }
      if (*input != '\0') input++;
    }
    if (is_num(*input)) {
      input = get_num(input, &num);
      if (*num != 'x')
        res = push_num(res, atof(num));
      else {
        res = push(res, *num);
        free(num);
      }
    }
    if (*input == ')') {
      while (oper->data != '(') {
        res = push(res, pick(oper));
        oper = pop(oper);
      }
      oper = pop(oper);
      input++;
    }
  }
  while (oper != NULL) {
    res = push(res, pick(oper));
    oper = pop(oper);
  }
  return res;
}
