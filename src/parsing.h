#ifndef SRC_PARSING_H_
#define SRC_PARSING_H_

char *str_transformation(char *input);
int valid_input(char *input);
int check_priority(char operation);
int check_dimension(char operation);
int priority_compare(char op1, char op2);
int is_func(char c);
int is_math_symbol(char c);
int is_num(char c);
void change_expr(char *exp, char *func, char sym);
void squeeze(char *s, int c);
char *get_num(char *start, char **res);
char *copy(char *start, int len);

#endif  // SRC_PARSING_H_
