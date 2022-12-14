#include "infix.h"
#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<string.h>

int isOperator(char value) {
  if (value == '+' || value == '-' || value == '^' || value == 'X' || value == '/' || value == '(' || value == ')') {
		return 1;
  } else {
    return 0;
  }
}

int eqOrHigherPrec(char value, char valueCheckedAgainst) {
	if (value == '^') {
		return 1;
	} else if (value == 'X' || value == '/') {
		if (valueCheckedAgainst == '^') {
			return 0;
		}
		return 1;
	} else if (value == '+'|| value == '-') {
	  if (valueCheckedAgainst == '+' || valueCheckedAgainst == '-') {
	    return 1;
	  }
	  return 0;
	}
	return 2;  
}


// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char ** args, int nargs) {
  // Write your code here
  struct double_stack * operatorStack = double_stack_new(nargs);
  memset(operatorStack->items, 0, nargs * sizeof(double));
  char * output[nargs];
  char null = '\0';
  int outputTop = 0;
  int bracketCount = 0;
  memset(output, 0, nargs * sizeof(char*));
  for (int i = 0; i < nargs; i++) {
    if (*args[i] != '\0') {
      if (isdigit(*args[i]) ||( (*args[i]) == '-' && atof(args[i]) != 0)) {
      printf("yup1: %c\n", *args[i]);
      output[outputTop] = args[i];
      outputTop++;
    } else if (isOperator(*args[i]) == 1) {
      printf("yup2: %c\n", *args[i]);
      if (*args[i] == '(') {
	 bracketCount++;
	 double_stack_push(operatorStack, *args[i]);
	 printf("Pushed %c\n", *args[i]);
      } else if (*args[i] == ')') {
	bracketCount++;
	char tempOp[2];
	tempOp[0] = double_stack_pop(operatorStack);
	tempOp[1] = null;
	printf("Popped %c\n", tempOp[0]);
        while (tempOp[0] != '(') {
	  output[outputTop] = strdup(tempOp);
	  outputTop++;
	  printf("Appended %c\n", tempOp[0]);
	  tempOp[0] = double_stack_pop(operatorStack);
	  printf("Popped %c\n", tempOp[0]);
	}
      } else {
	printf("yup: %c\n", *args[i]);
	char tempOp[2];
	if (operatorStack->top > 0) {
	  tempOp[0] = double_stack_pop(operatorStack);
	  tempOp[1] = null;
	  double_stack_push(operatorStack, tempOp[0]);
	}
	while (operatorStack->top > 0 && eqOrHigherPrec(tempOp[0], *args[i]) == 1) {
	  printf("Token: %c\n", *args[i]);
	  printf("Popped %c\n", tempOp[0]);
	  output[outputTop] = strdup(tempOp);
	  printf("%s\n", output[outputTop]);
	  outputTop++;
	  printf("Appended %c\n", tempOp[0]);
	  printf("Output String: ");
	  for (int i = 0; i < outputTop; i++) {
	    printf("%s ", output[i]);
	  }
	  printf("\n");
	  double_stack_pop(operatorStack);
	  if (operatorStack->top > 0) {
	    printf("Ooo recursive yup");
	    tempOp[0] = double_stack_pop(operatorStack);
	    printf("ooo recursive yup: %c\n", tempOp[0]);
	    tempOp[1] = null;
	    double_stack_push(operatorStack, tempOp[0]);
	    printf("STack top: %d\n", operatorStack->top);
	  }
	}
	double_stack_push(operatorStack, *args[i]);
	printf("Pushed %c\n", *args[i]);
    }
   }
  }
  }
  char op[2];
  while (operatorStack->top > 0) {
    op[0] = double_stack_pop(operatorStack);
    op[1] = '\0';
    printf("Popped %c\n", op[0]);
    output[outputTop] = strdup(op);
    outputTop++;
    printf("Appended %c\n", op[0]);
  }
  printf("Output String: ");
  for (int i = 0; i<outputTop;i++) {
    printf("%s at index %d\n", output[i], i);
  }
  printf("\n");
  printf("nargs: %d\n", nargs);
  return evaluate_postfix_expression(output, nargs-bracketCount);
}
