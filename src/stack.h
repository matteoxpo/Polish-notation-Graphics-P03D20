#ifndef STACK_H
#define STACK_H

struct stack {
  char *data;
  struct stack *next;
};

struct stack *init(char *val);
struct stack *push(struct stack *h, char *val);
struct stack *pop(struct stack *h);
void decstroy(struct stack *h);
void stack_output(struct stack *h);
int stack_len(struct stack *h);
char *pick(struct stack *h);

#endif
