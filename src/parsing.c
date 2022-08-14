#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *charInput() {
  char *res = malloc(sizeof(char));
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

int check_priority(char operation) {
  int priority = 10;
  switch (operation) {
    case '(':
      priority = 1;
      break;
    case '+':
    case '-':
      priority = 2;
      break;
    case '*':
    case '/':
      priority = 3;
      break;
    case '^':
    case '#':
      priority = 4;
      break;
    case '~':
      priority = 5;
      break;
  }
  if (is_func(operation)) priority = 5;
  return priority;
}

int is_func(char c) {
  int res = 0;
  //       sin         cos         tg          ctg         sqrt        ln
  if (c == 's' || c == 'c' || c == 't' || c == 'g' || c == 'q' || c == 'l')
    res = 1;  // sin(x) + 5 + ln(x) *x --> s + 5 +l*x
  return res;
}
int is_math_symbol(char c) {
  int res = 0;
  if (c == '*' || c == '-' || c == '+' || c == '/' || c == '^') res = 1;
  return res;
}

int is_math_oper(char c) {
  int res = 0;
  if (is_func(c) || is_math_symbol(c) || c == '(') res = 1;
  return res;
}
int is_num(char c) {
  int res = 0;
  if ((c >= '0' && c <= '9') || c == '.' || c == ',' || c == 'x') res = 1;
  return res;
}

char *str_transformation(char *input) {
  char *funcs[] = {"sin(x)", "cos(x)", "tg(x)", "ctg(x)", "sqrt(x)", "ln(x)"};
  // char *funcs[] = {"sin", "cos", "tg", "ctg", "sqrt", "ln"};
  char *minifuncs = "sctgql";
  squeeze(input, ' ');
  for (int i = 0; i < 6; i++) {
    change_expr(input, funcs[i], minifuncs[i]);
  }
  return input;
}

int valid_input(char *input) {
  int res = 1;
  while (*input != '\0') {
    if (!is_math_oper(*input) && !is_num(*input)) res = 0;
    input++;
  }
  return res;
}

void change_expr(char *exp, char *func, char sym) {
  while (strstr(exp, func) != NULL) {
    char *change = strstr(exp, func);
    int i = strlen(exp) - strlen(change);
    exp[i] = sym;
    i++;
    int size = strlen(func) + i;
    for (i; i < size - 1; i++) {
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
