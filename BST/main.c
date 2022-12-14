#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


int main(int argc, char ** argv) {
  struct BST * tree = new_BST();
  FILE * input;
  input = fopen(argv[1], "r");
  assert(input != NULL);
  char c = fgetc(input);
  int i = c - '0';
  while(!feof(input)){ //while we haven't reached the end of the file
    if (c != ' ') {
      put(tree, i, i);
      printf("%d\n", i);
    }
    //move to next character
    c = fgetc(input);
    i = c - '0';
  }
  fclose(input);
  printPreorder(tree->root);
}