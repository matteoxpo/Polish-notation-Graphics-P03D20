#ifndef PARSIN_H
#define PARSIN_H

int check_priority(char operation);
int is_func(char c);
int is_math_symbol(char c);
int is_num(char c);
int is_math_oper(char c);
void change_expr(char *exp, char *func, char sym);
void squeeze(char *s, int c);
char *get_num(char *start, char **res);
char *copy(char *start, int len);
#endif