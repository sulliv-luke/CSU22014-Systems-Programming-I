#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huff.h"

int main(int argc, char ** argv) {
    // create a new huffcoder structure
    struct huffcoder * coder;
    coder = huffcoder_new();
    // find character frequencies using the training file
    huffcoder_count(coder, argv[1]);

      // build the Huffman tree
  huffcoder_build_tree(coder);

  // from the Huffman tree fill the table with Huffman codes
  huffcoder_tree2table(coder);

  huffcoder_print_codes(coder);
    return 0;
}