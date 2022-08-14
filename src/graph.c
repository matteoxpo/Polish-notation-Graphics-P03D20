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
  struct stack* res = Polska(input);
  printf("Time to look at stack\n");
  stack_output(res);

  /*
  if (valid_input(input)) {
  }
  return 0;
  */
}

struct stack* Polska(char* input) {
  printf("Expression:%s\n", input);
  int size = strlen(input);
  struct stack* res = NULL;  // строка результат
  struct stack* oper = NULL;  // строка куда кидаем операторов
  char op;
  while (*input != '\0') {
    if (is_math_symbol(*input) || is_func(*input)) {
      if (oper == NULL || check_priority(*input) > check_priority(pick(oper))) {
        op = *input;
        oper = push(oper, op);
      } else if (*input != '(') {
        while (oper != NULL &&
               check_priority(*input) <= check_priority(pick(oper)) &&
               pick(oper) != '(') {
          op = pick(oper);
          res = push(res, op);
          oper = pop(oper);
        }
        oper = push(oper, *input);
      } else {
        op = *input;
        oper = push(oper, op);
      }
      if (*input != '\0') input++;
    }

    if (is_num(*input)) {
      char* num;
      input = get_num(input, &num);

      if (*num != 'x')
        res = push_num(res, atof(num));
      else {
        res = push(res, *num);
        free(num);
      }
    }
    if (*input == ')') {
      while (oper != NULL && oper->data != '(') {
        op = pick(oper);
        res = push(res, op);
        oper = pop(oper);
      }
      oper = pop(oper);
      input++;
    }
  }

  while (oper != NULL) {
    op = pick(oper);
    res = push(res, op);
    oper = pop(oper);
  }
  free(oper);
  return res;
}
