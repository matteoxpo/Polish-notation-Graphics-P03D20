#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsing.h"
#include "stack.h"

char* charInput();
struct stack* Polska(char* input);
float func(struct stack* f, float x);
float calculate_f(float* nums, char operation);

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

float func(struct stack* f, float x) {
  float res = 0;
  struct stack* nums = NULL;
  struct stack* runner = f;
  float* nums_for_opertion = malloc(2 * sizeof(float));
  float operation_res;
  char top;
  int oper_dimension;
  while (runner != NULL) {
    top = pick(runner);
    if (top == 'x' || top == '\0') {
      if (top == '\0')
        nums = push_num(nums, runner->num);
      else
        nums = push_nums(nums, x);
    } else {
      for (int i = 0; i < check_dimension(top); i++) {
        nums_for_opertion[i] = nums->num;
        nums = pop(nums);
      }
      operation_res = calculate_f(nums_for_opertion, top);
    }
    runner = runner->next;
  }
  free(nums_for_opertion);
  return res;
}

/*
       sin         cos         tg          ctg         sqrt        ln
  if (c == 's' || c == 'c' || c == 't' || c == 'g' || c == 'q' || c == 'l')

  if (c == '*' || c == '-' || c == '+' || c == '/' || c == '^'
*/

float calculate_f(float* nums, char operation) {
  float res = 0;
  switch (operation) {
    case '+':
      res = nums[1] + nums[0];
      break;
    case '-':
      res = nums[1] - nums[0];
      break;
    case '*':
      res = nums[1] * nums[0];
      break;
    case '/':
      res = nums[1] / nums[0];
      break;
    case '^':
      res = pow(nums[1], nums[0]);
      break;
    case 's':
      res = sin(nums[0]);
      break;
    case 'c':
      res = cos(nums[0]);
      break;
    case 't':
      res = tan(nums[0]);
      break;
    case 'g':
      res = pow(tan(nums[0]), -1);
      break;
    case 'q':
      res = sqrt(nums[0]);
      break;
    case 'l':
      res = log(nums[0]);
      break;
  }
  return res;
}