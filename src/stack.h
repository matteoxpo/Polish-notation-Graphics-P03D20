#ifndef SRC_STACK_H_
#define SRC_STACK_H_

struct stack {
  char data;
  float num;
  struct stack *next;
};

struct stack *init(char val, float d);
struct stack *push(struct stack *h, char val);
struct stack *push_num(struct stack *h, float val);
struct stack *pop(struct stack *h);
void destroy(struct stack *h);
void stack_output(struct stack *h);
char pick(struct stack *h);
struct stack *reverse(struct stack *s);

#endif  // SRC_STACK_H_
