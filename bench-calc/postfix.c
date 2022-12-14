#include<stdio.h>
#include<ctype.h>
#include "postfix.h"
#include<math.h>


// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char ** args, int nargs) {
  // Write your code here
  struct double_stack * stack = double_stack_new(nargs);
  memset(stack->items, 0, nargs * sizeof(double));
  double n1, n2, result, num;
  printf("nargs in postfix: %d\n", nargs);
  for (int i = 0; i < nargs; i++) {
    printf("yup %c\n", *args[i]);
    
    if(isdigit(*args[i]) || (*args[i] == '-' && atof(args[i]) != 0)) {
      num = atof(args[i]);
      printf("%f\n", num);
      double_stack_push(stack, num);
      printf("Pushed %f\n", num);
    } else if (*args[i] != ' '){
      printf("Operation being performed: %c\n", *args[i]);
      n1 = double_stack_pop(stack);
      printf("Popped %f\n", n1);
      n2 = double_stack_pop(stack);
      printf("Popped %f\n", n2);

      if (*args[i] == '+') {
	result  = n1 + n2;
      } else if (*args[i] == '-') {
	result = n2 - n1;
      } else if (*args[i] ==  'X') {
	result = n1 * n2;
      } else if (*args[i] == '/') {
	result = n2 / n1;
      } else if (*args[i] == '^') {
	result = pow(n2, n1);
      }
      double_stack_push(stack, result);
      printf("Pushed %f\n", result);
      }
    printf("Iteration: %d\n", i);
   }
  printf("Stack top: %d\n", stack->top);
  return result;
}
