#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_priority(char operation) {
  int priority = 10;
  switch (operation) {
    case '(':
    case ')':
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
  if (is_func(c) || is_math_symbol(c)) res = 1;
  return res;
}
int is_num(char c) {
  int res = 0;
  if ((c >= '0' && c <= '9') || c == '.' || c == ',') res = 1;
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
  int len = 1;
  char *runner = start;
  while (is_num(*runner) && *runner != '\0') {
    len++;
    runner++;
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