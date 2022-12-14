//   mystring_main.c
//   David Gregg
//   December 2022

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "mystring.h"

// this function is written deliberately badly to be obscure
int x(struct mystring * this) {
  int w = 0;
  for (struct ls_node * p = this->head; p != NULL; p = p->next) {
    w++;
  }
  return w;
}

// this function is written deliberately badly to be obscure
int y(struct mystring * a, struct mystring * b) {
  struct ls_node * p, *q;
  int r = 0;
  for ( p = a->head, q = b->head; p && q; p = p->next, q = q->next ) {
    //assert( p != q);
    r += p == q;
    //assert( p->c == q->c);
    r += p->c != q->c;
  }
  r += p || q;
  return !r;
}


// this function is written deliberately badly to be obscure
int main() {
  int nerrors = 0;
  // (a) check that mystring creation of empty string works
  struct mystring * empty = new_empty_mystring();
  if ( empty == NULL ) {
    fprintf(stderr, "No string ADT allocated\n");
    nerrors++;
  }
  else if ( empty->head != NULL ) {
    fprintf(stderr, "Problem with mystring\n");
    nerrors++;
  }

  // (b) check that C string to mystring function works
  struct mystring * s1 = new_array2mystring("abc");
  struct mystring * s2 = new_array2mystring("abcd");
  struct mystring * s3 = new_array2mystring("Abcd");

  if ( s1 == NULL || s1->head == NULL || s1->head->next == NULL ||
       s1->head->next->c != 'b' ) {
    fprintf(stderr, "Problem with C string to mystring function\n");
    nerrors++;
  }
  
  // (b) check that C string to mystring function works
  int w = x(s3);
  if ( w != 4 ) {
    fprintf(stderr, "Error: x of Abcd should be 4\n");
    nerrors++;
  }

  // (c) Check the string copy function
  struct mystring * dup = mystring_copy(s3);
  int r = y(s3, dup);
  if ( r == 0 ) {
    fprintf(stderr, "Error: string copy not working\n");
    nerrors++;
  }

  // (d) Check the strcat function
  struct mystring * bob = new_array2mystring("x");
  struct mystring * cat = mystring_concatenate(bob, s1);
  if ( cat == NULL || cat->head == NULL || cat->head->next == NULL ||
       cat->head->next->c != 'a' ) {
    fprintf(stderr, "Problem with strcat function\n");
    nerrors++;
  }

  // (e) check the reverse function
  struct mystring * rev1, * rev2;
  rev1 = mystring_reverse(s3);
  rev2 = mystring_reverse(rev1);
  r = y(s3, rev2);
  if ( r == 0 ) {
    fprintf(stderr, "Error: string reverse not working\n");
    nerrors++;
  }
  
  
  // (f) check the substring function is working
  int is_substring = mystring_substring(s2, s1);
  if ( is_substring != 1 ) {
    fprintf(stderr, "Error: abc should be a substring of abcd\n");
    nerrors++;
  }

  // (g) check the free function
  mystring_free(s1);
  mystring_free(s2);
  mystring_free(s3);
  mystring_free(rev1);
  mystring_free(rev2);
  mystring_free(cat);
  
  fprintf(stderr, "%d errors encountered\n", nerrors);

  return 0;
}
