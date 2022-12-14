//   list_string.c
//   David Gregg
//   January 2021

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"

// create a new empty deque
struct deque * new_deque() {
  struct deque * result = malloc(sizeof(struct deque));
  result->elements = malloc(sizeof(char *) * 1024);
  for (int i = 0; i < 1024; i++) {
    result->elements[i] = malloc(sizeof(char) * 1024);
    strcpy(result->elements[i], "");
  }
  result->nelements = 0;
  result->size = 1024;
  return result;
}

// push a string to the front of the deque
void push_front_deque(struct deque * this, char * str) {
  if ((this->nelements > 0 )& (this->nelements < this->size)) {
    for (int i = this->nelements; i > 0 ; i--) {
      strcpy(this->elements[i], this->elements[i-1]);
    }
    strcpy(this->elements[0], str);
    this->nelements++;
  } else {
    strcpy(this->elements[0], str);
    this->nelements++;
  }
}

// pop a string from the front of the deque
char * pop_front_deque(struct deque * this) {
  char * returnStr = malloc(sizeof(char) * 100);
  if (this->nelements > 0) {
    strcpy(returnStr, this->elements[0]);
    for (int i = 0; i < this->nelements; i++) {
      strcpy(this->elements[i], this->elements[i+1]);
    }
    this->nelements--;
    return returnStr;
  }
  return "ERR";
}

// push a string to the back of the deque
void push_back_deque(struct deque * this, char * str) {
  if (this->nelements < this->size) {
    strcpy(this->elements[this->nelements], str);
    this->nelements++;
  }
}

// pop a value from the back of the deque
char * pop_back_deque(struct deque * this) {
  if (this->nelements > 0) {
    char * returnStr = malloc(sizeof(char) * strlen(this->elements[this->nelements-1]));
    strcpy(returnStr, this->elements[this->nelements-1]);
    strcpy(this->elements[this->nelements-1], "");
    this->nelements--;
    return returnStr;
  }
  return "ERR";
}

// free the memory used by the deque
void free_deque(struct deque * this) {
  free(this);
}

// return a string from the deque at position "index", where the
// item at the front of the deque has index 0, and subsequent
// items are numbered successively. If there are fewer than index+1
// items in the deque, return a string containing the value "ERROR"
char * item_at_deque(struct deque * this, int index) {
  if (this->nelements < index+1) {
    return "ERROR";
  } else {
    return this->elements[index];
  }
}



