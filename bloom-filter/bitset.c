#include "bitset.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size) {
        struct bitset * result = malloc(sizeof(struct bitset));
        result -> universe_size = size;
	result -> size_in_words = size / (sizeof(uint64_t) * 8ULL); // size divided by bits required for one word
	if (result->universe_size % 64 != 0) {
		result -> size_in_words++;
	}
		result -> bits = malloc(sizeof(uint64_t) * result -> size_in_words);
		for (int i = 0; i < result->size_in_words; i++) {
			result -> bits[i] = 0;
		}
	return result;
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this) {
	return this -> universe_size;
}

// print the contents of the bitset
void bitset_pr(struct bitset * this) {
  int i;
  int size = bitset_size(this);
  for ( i = 0; i < size; i++ ) {
    if ( bitset_lookup(this, i) == 1 ) {
      fprintf(stderr, "%d ", i);
    }
  }
  fprintf(stderr,"\n");
}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset * this){
        int count = 0;
	for (int i = 0; i < this->universe_size; i++) {
		if (bitset_lookup(this, i) == 1) {
			count++;
		}
	}
       return count;
}

// check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item){
	uint64_t bit_index = item % 64ULL; // index of bit in word
	uint64_t word_index;
	if (item >= 64) {
		word_index = (item-bit_index/64ULL);  // index of word in set
	} else {
		word_index = 0ULL;
	}
	uint64_t mask = 1ULL << (64ULL-bit_index-1ULL);
        if ((this->bits[word_index] & mask) > 0ULL) {
        	return 1;
        } else {
        	return 0;
        }
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset * this, int item) {
       if (bitset_lookup(this, item) == 0) {
       		uint64_t bit_index = item % 64ULL;
        	uint64_t word_index;
        	if (item >= 64){
        		word_index = (item-bit_index/64ULL);  // index of word in set
        	} else {
        		word_index = 0ULL;
        	}
        	uint64_t mask = 1ULL << (64ULL-bit_index-1ULL);
        	this->bits[word_index] = this->bits[word_index] | mask;
       }
}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset * this, int item) {
        uint64_t bit_index = item % 64ULL;
        uint64_t word_index;
        if (item >= 64){
        	word_index = (item-bit_index/64ULL);  // index of word in set
        } else {
        	word_index = 0ULL;
        }
        uint64_t mask = 1ULL << (64ULL-bit_index-1ULL);
        mask = ~(mask);
        this->bits[word_index] = this->bits[word_index] & mask;
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {
    	for (int i = 0; i < src1->universe_size; i++) {
    		if ((bitset_lookup(src1, i) == 1) && (bitset_lookup(dest, i) == 0)) {
    			bitset_add(dest, i);
    		}
    	}
    	for (int i = 0; i < src2->universe_size; i++) {
    		if ((bitset_lookup(src2, i) == 1) && (bitset_lookup(dest, i) == 0)) {
    			bitset_add(dest, i);
    		}
    	}
    	 	
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {
    	for (int i = 0; i < src1->universe_size; i++) {
    		if ((bitset_lookup(src1, i) == 1) && (bitset_lookup(src2, i) == 1)) {
    			bitset_add(dest, i);
    		}
    	}
}
