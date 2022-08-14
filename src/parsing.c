#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *charInput() {
  char *res = malloc(sizeof(char));
  int i = 0;
  while (1) {
    scanf("%c", &(res[i]));
    char *tmp = realloc(res, sizeof(char));
    if (tmp != NULL) res = tmp;
    if (res != NULL) {
      if (res[i] == '\n') {
        res[i] = '\0';
        break;
      }
      i++;
    } else {
      free(res);
    }
  }
  return res;
}

int check_priority(char operation) {
  int priority = 10;
  switch (operation) {
    case '+':
    case '-':
      priority = 2;
      break;
    case '*':
    case '/':
      priority = 3;
      break;
    case '^':
      priority = 4;
      break;
    case '~':
      priority = 5;
      break;
    case '(':
      priority = 6;
      break;
  }
  if (is_func(operation)) priority = 5;
  return priority;
}

int priority_compare(char op1, char op2) {
  return check_priority(op1) > check_priority(op2);
}

int check_dimension(char operation) {
  int size = 2;
  if (is_math_symbol(operation)) size = 2;
  if (is_func(operation) || operation == '~') size = 1;
  return size;
}

int is_func(char c) {
  int res = 0;
  //       sin         cos         tg          ctg         sqrt        ln
  if (c == 's' || c == 'c' || c == 't' || c == 'g' || c == 'q' || c == 'l')
    res = 1;
  return res;
}
int is_math_symbol(char c) {
  int res = 0;
  if (c == '*' || c == '-' || c == '+' || c == '/' || c == '^' || c == '(' ||
      c == '~')
    res = 1;
  return res;
}

int is_num(char c) {
  int res = 0;
  if ((c >= '0' && c <= '9') || c == '.' || c == ',' || c == 'x') res = 1;
  return res;
}

char *str_transformation(char *input) {
  char *funcs[] = {"sin", "cos", "ctg", "tg", "sqrt", "ln"};
  char *minifuncs = "scgtql";
  squeeze(input, ' ');
  for (int i = 0; i < 6; i++) {
    change_expr(input, funcs[i], minifuncs[i]);
  }
  return input;
}

int valid_input(char *input) {
  int res = 1;
  int countBrackets = 0;
  while (*input != '\0') {
    if (!is_math_symbol(*input) && !is_num(*input) && !is_func(*input) &&
        *input != ')')
      res = 0;
    if (*input == ',') *input = '.';
    if (*input == '(') countBrackets++;
    if (*input == ')') countBrackets--;
    if (countBrackets < 0) res = 0;
    if (is_func(*input) && *(input + 1) != '(') res = 0;
    input++;
  }
  if (countBrackets != 0) res = 0;
  return res;
}

void change_expr(char *exp, char *func, char sym) {
  while (strstr(exp, func) != NULL) {
    char *change = strstr(exp, func);
    if (sym == 'g') printf("%s", change);
    int i = strlen(exp) - strlen(change);
    exp[i] = sym;
    i++;
    int size = strlen(func) + i;
    for (; i < size - 1; i++) {
      exp[i] = ' ';
    }
  }
  squeeze(exp, ' ');
}

void squeeze(char *s, int c) {
  int i, j;
  for (i = j = 0; s[i] != '\0'; i++)
    if (s[i] != c) s[j++] = s[i];
  s[j] = '\0';
}

char *get_num(char *start, char **res) {
  int len = 0;
  char *runner = start;
  while (is_num(*runner) && *runner != '\0') {
    runner++;
    len++;
  }
  *res = copy(start, len);
  start += len;
  return start;
}

char *copy(char *start, int len) {
  char *res = malloc(len * sizeof(char));
  for (int i = 0; i < len; i++) {
    res[i] = *start;
    start++;
  }
  return res;
}
