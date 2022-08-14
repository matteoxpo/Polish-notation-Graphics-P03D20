#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"
#include "parsing.h"
#include "stack.h"

#define H 25
#define W 80
#define DOT '*'
#define EMPTY '.'

char* charInput();
struct stack* Polska(char* input);
void print_graph(struct stack* exp);
float func(struct stack* f, float x);
float calculate_f(float* nums, char operation);

int main() {
  char* input = charInput();
  input = str_transformation(input);
  if (valid_input(input)) {
    struct stack* res = Polska(input);
    struct stack* rev = reverse(res);

    print_graph(rev);

    destroy(res);
    destroy(rev);
  }
  free(input);
}

struct stack* Polska(char* input) {
  struct stack *res = NULL, *oper = NULL;
  char* num = NULL;
  while (*input != '\0') {
    if (*input == '(' && *(input + 1) == ')') input += 2;
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
      if (*num != 'x') {
        res = push_num(res, atof(num));
      } else {
        res = push(res, *num);
      }
      free(num);
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
  destroy(oper);
  return res;
}

void print_graph(struct stack* exp) {
  char** field;
  if (allocMem(&field, H, W)) {
    float x = 0, step = 2.0 / 24.0;
    for (int i = 0; i < W; i++) {
      float y = func(exp, x);
      float h = -1.0;
      for (int j = 0; j < H; j++) {
        if (y >= h - step / 2 && y <= h + step / 2) {
          field[j][i] = DOT;
        } else {
          field[j][i] = EMPTY;
        }
        h += step;
      }
      x += (4.0 * M_PI) / (W - 1);
    }
    turn_over(field, H);
    output_matrix(field, H, W);
  }
  freeMem(field, H);
}

float func(struct stack* f, float x) {
  struct stack* nums = NULL;
  struct stack* runner = f;
  float* nums_for_opertion = malloc(2 * sizeof(float));
  float operation_res = 0;
  while (runner != NULL) {
    char top = pick(runner);
    if (top == 'x' || top == '\0') {
      if (top == '\0')
        nums = push_num(nums, runner->num);
      else
        nums = push_num(nums, x);
    } else {
      for (int i = 0; i < check_dimension(top); i++) {
        nums_for_opertion[i] = nums->num;
        nums = pop(nums);
      }
      operation_res = calculate_f(nums_for_opertion, top);
      nums = push_num(nums, operation_res);
    }
    runner = runner->next;
  }
  if (nums != NULL) operation_res = nums->num;

  destroy(nums);
  free(nums_for_opertion);
  return operation_res;
}

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
    case '~':
      res = -1 * nums[0];
  }
  return res;
}
