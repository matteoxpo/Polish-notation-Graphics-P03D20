#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"
#include "parsing.h"
#include "stack.h"

#define H 25
#define W 80
char* charInput();
struct stack* Polska(char* input);
void print_graph(struct stack* exp);
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
  printf("\n\n");
  float num;
  scanf("%f", &num);
  printf("%f\n", func(rev, 1));
  printf("%f\n", func(rev, num + 1));
  printf("%f\n", func(rev, num + 2));
  //  print_graph(rev);
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

void print_graph(struct stack* exp) {
  char** field;
  if (!allocMem(&field, H, W))
    printf("ДОБАВЬ ПОПОЗЖЕ ЭТОТ ИФ ВОНЮЧИЙ СТРЕМНЫЙ___))))))");

  float step = 4 * M_PI / (W - 1);
  float max = -INFINITY;
  float min = INFINITY;

  float norma = (min + max) / H;
  for (int y = 0; y < H; y++) {
    for (float x = -M_PI; x <= M_PI + 0.001; x += step) {
      float res = func(exp, x);
      if (res > (max - (x + 1) * norma) && res <= (max - x * norma))
        printf("*");
      else
        printf(" ");
    }
    printf("\n");
  }
  printf("\n-------------------------------");
}

float func(struct stack* f, float x) {
  struct stack* nums = NULL;
  struct stack* runner = f;
  float* nums_for_opertion = malloc(2 * sizeof(float));
  float operation_res = 0;
  char top;
  int oper_dimension;
  while (runner != NULL) {
    top = pick(runner);
    if (top == 'x' || top == '\0') {
      if (top == '\0')
        nums = push_num(nums, runner->num);
      else
        nums = push_num(nums, x);
    } else {
      for (int i = 0; i < check_dimension(top); i++) {
        // printf("Now i am pushing: %f\n", nums->num);
        nums_for_opertion[i] = nums->num;
        nums = pop(nums);
      }
      operation_res = calculate_f(nums_for_opertion, top);
      // printf("Oper result: %f\n", operation_res);
      nums = push_num(nums, operation_res);
    }
    // printf("\n\n");
    runner = runner->next;
  }
  operation_res = nums->num;
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
