#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsing.h"
#include "stack.h"

char* charInput();
struct stack* Polska(char* input);
int validInput(char* input);

int main() {
  char* funcs[] = {"sin(x)", "cos(x)", "tg(x)", "ctg(x)", "sqrt(x)", "ln(x)"};
  char* minifuncs = "sctgql";
  char* input = charInput();
  squeeze(input, ' ');
  printf("%s\n ", input);
  // printf("\n%s", expr);
  while (*input != '\0') {
    if (is_num(*input)) {
      char* num;
      input = get_num(input, &num);

      printf("%s\n", num);
      free(num);
    }

    input++;
  }
  /*
  for (int i = 0; i < 6; i++) {
    change_expr(input, funcs[i], minifuncs[i]);
  }
  printf("\n%s", input);
  if (validInput(input)) {
    Polska(input);
  }
  */
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

int validInput(char* input) {
  int res = 1;
  while (*input != '\0') {
    if (!is_math_oper(*input) && !is_num(*input)) res = 0;
    input++;
  }
  return res;
}

struct stack* Polska(char* input) {
  int size = strlen(input);
  struct stack* res = NULL;  // строка результат
  struct stack* oper = NULL;  // строка куда кидаем операторов

  while (*input != '\0') {
    // если пришла операция
    if (is_math_oper(*input)) {
      char* op;
      // елси приоритет операции на верхушке стека меньше пришедшей из строки -
      if (oper != NULL ||
          check_priority(*input) > check_priority(*pick(oper))) {
        op = input;
        push(oper, &op);  // пушим в стек
      } else {
        // если приоритет в стеке больше, чем в инпуте
        // пока стек не пуст либо же не придет операция с меньшим приоритетом
        while (oper != NULL ||
               check_priority(*input) < check_priority(*pick(oper))) {
          // выводим операции меньшего приоритета в строку результат
          op = pick(oper);
          push(res, &op);
          // удаляем запушенную операцию из стека операций
          pop(oper);
        }
      }
    }
    if (is_num(*input)) {
      char* num;
      input = get_num(input, &num);
      push(res, num);
      free(num);
    }
    input++;
  }

  free(oper);
  return res;
}
