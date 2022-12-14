//   list_string_main.c
//   David Gregg
//   January 2021

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"

int simple_queue_test() {
  char * a = "shiny";
  char * b = "happy";
  char * c = "people";
  char * d;
  struct deque * d1;
  int error;
  
 // add and remove some things
  error = 0;
  d1 = new_deque();
  push_front_deque(d1, a);
  for (int i = 0; i < d1->nelements; i++) {
    fprintf(stderr, d1->elements[i]);
    fprintf(stderr, "\n");
  }
  push_front_deque(d1, b);
  for (int i = 0; i < d1->nelements; i++) {
    fprintf(stderr, d1->elements[i]);
    fprintf(stderr, "\n");
  }
  push_front_deque(d1, c);
  for (int i = 0; i < d1->nelements; i++) {
    fprintf(stderr, d1->elements[i]);
    fprintf(stderr, "\n");
  }
  d = pop_back_deque(d1);
  // if d is not equal to a, we have an error
  // fprintf(stderr, "d = %s, a = %s\n", d, a);
  if ( strcmp(d, a) != 0 ) {
    fprintf(stderr, "Error: expected %s, actually got %s\n", a, d);
    error = 1;
  }
  d = pop_back_deque(d1);
  if ( strcmp(d, b) != 0 )
    error = 1;
  d = pop_back_deque(d1);
  if ( strcmp(d, c) != 0 ) {
    error = 1;
  }
  free_deque(d1);
  
  return error;
}

int push_front_pop_front_test() {
  char * in;
  char * out;
  int error = 0;
  struct deque * mydeq = new_deque();

  // insert a bunch of strings correspending to numbers
  int start = 10, stop = 800;
  for ( int i = start; i < stop; i++ ) {
    // allocate some memory for a new string
    in = malloc(10);
    // populate the string with a number
    sprintf(in, "%d", i);
    push_front_deque(mydeq, in);
  }

  // now take the strings back out and check the have the right values
  for ( int i = stop - 1; i >= start; i-- ) {
    out = pop_front_deque(mydeq);
    fprintf(stderr, "%s\n", out);
    int out_num = atoi(out);
    if ( out_num != i ) {
      error = 1;
      fprintf(stderr, "Error: expected %d, actually got %d\n", i, out_num);
    }
    free(out);
  }
  
  free_deque(mydeq);
  
  return error;
}

int push_back_pop_back_test() {
  char * in;
  char * out;
  int error = 0;
  struct deque * mydeq = new_deque();

  // insert a bunch of strings correspending to numbers
  int start = 10, stop = 800;
  for ( int i = start; i < stop; i++ ) {
    // allocate some memory for a new string
    in = malloc(10);
    // populate the string with a number
    sprintf(in, "%d", i);
    push_back_deque(mydeq, in);
  }

  // now take the strings back out and check the have the right values
  for ( int i = stop - 1; i >= start; i-- ) {
    out = pop_back_deque(mydeq);
    // fprintf(stderr, "%s\n", out);
    int out_num = atoi(out);
    if ( out_num != i ) {
      error = 1;
      fprintf(stderr, "Error: expected %d, actually got %d\n", i, out_num);
    }
    free(out);
  }
  
  free_deque(mydeq);
  
  return error;
}

int push_front_pop_back_test() {
  char * in;
  char * out;
  int error = 0;
  struct deque * mydeq = new_deque();

  // insert a bunch of strings correspending to numbers
  int start = 10, stop = 800;
  for ( int i = start; i < stop; i++ ) {
    // allocate some memory for a new string
    in = malloc(10);
    // populate the string with a number
    sprintf(in, "%d", i);
    push_front_deque(mydeq, in);
  }

  // now take the strings back out and check the have the right values
  for ( int i = start; i < stop; i++ ) {
    out = pop_back_deque(mydeq);
    // fprintf(stderr, "%s\n", out);
    int out_num = atoi(out);
    if ( out_num != i ) {
      error = 1;
      fprintf(stderr, "Error: expected %d, actually got %d\n", i, out_num);
    }
    free(out);
  }
  
  free_deque(mydeq);
  
  return error;
}

int push_back_pop_front_test() {
  char * in;
  char * out;
  int error = 0;
  struct deque * mydeq = new_deque();

  // insert a bunch of strings correspending to numbers
  int start = 10, stop = 800;
  for ( int i = start; i < stop; i++ ) {
    // allocate some memory for a new string
    in = malloc(10);
    // populate the string with a number
    sprintf(in, "%d", i);
    push_back_deque(mydeq, in);
  }

  // now take the strings back out and check the have the right values
  for ( int i = start; i < stop; i++ ) {
    out = pop_front_deque(mydeq);
    // fprintf(stderr, "%s\n", out);
    int out_num = atoi(out);
    if ( out_num != i ) {
      error = 1;
      fprintf(stderr, "Error: expected %d, actually got %d\n", i, out_num);
    }
    free(out);
  }
  
  free_deque(mydeq);
  
  return error;
}

int indexing_test() {
  char * in;
  char * out;
  int error = 0;
  struct deque * mydeq = new_deque();

  // insert a bunch of strings correspending to numbers
  int start = 10, stop = 800;
  for ( int i = start; i < stop; i++ ) {
    // allocate some memory for a new string
    in = malloc(10);
    // populate the string with a number
    sprintf(in, "%d", i);
    push_back_deque(mydeq, in);
  }

  // check that the entries have the right values
  for ( int i = 0; i < stop - start; i++ ) {
    out = item_at_deque(mydeq, i);
    int out_num = atoi(out);
    //fprintf(stderr, "%s : %d\n", out, out_num);
    if ( out_num != start + i ) {
      error = 1;
      fprintf(stderr, "Error: expected %d, actually got %d\n", start + i, out_num);
    }
    // slight risky free'ing of data still in the deque
    // free(out);
  }
  out = item_at_deque(mydeq, stop);
  if ( strcmp(out, "ERROR") != 0 ) {
    error = 1;
    fprintf(stderr, "Error: expected ERROR, actually got %s\n", out);
  }
  
  free_deque(mydeq);
  
  return error;
}



int main() {

  int nerrors = 0;

  if ( simple_queue_test() == 1 ) {
    fprintf(stderr, "Error: failed Simple Queue Test 1\n");
    nerrors++;
  }

  if ( push_front_pop_back_test() == 1 ) {
    fprintf(stderr, "Error: failed Push Front Pop Back Test 2\n");
  }

  if ( push_back_pop_front_test() == 1 ) {
    fprintf(stderr, "Error: failed Push Back Pop Front Test 3\n");
  }
  
  if ( push_front_pop_front_test() == 1 ) {
    fprintf(stderr, "Error: failed Push Front Pop Front Test 4\n");
  }
  if ( push_back_pop_back_test() == 1 ) {
    fprintf(stderr, "Error: failed Push Back Pop Back Test 5\n");
  }

  if ( indexing_test() == 1 ) {
    fprintf(stderr, "Error: failed Indexing Test 6\n");
  }
  
  fprintf(stderr, "%d errors detected\n", nerrors);

  return 0;
}
