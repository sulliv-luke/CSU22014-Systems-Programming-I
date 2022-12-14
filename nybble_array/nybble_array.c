//   nybble_array.c
//   David Gregg
//   December 2021

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "nybble_array.h"


// create a new array of nybbles with space for "size"
// nybbles and initialize the values of the array to zero
struct nybble_array * nybble_array_new(int size) {
  struct nybble_array * result = malloc(sizeof(struct nybble_array));
  result->size_in_nybbles = size;
  result->size_in_bytes = size / 2;
  result->data_bytes = malloc(sizeof(unsigned char) * result->size_in_bytes);
  for (int i = 0; i < result->size_in_bytes; i++) {
    result->data_bytes[i] = 0;
  }
  return result;
}
// return the nybble value at position index
unsigned get_nybble_value(struct nybble_array * this, int index) {
  unsigned char  maskNybbleOne = 240; // binary 1111 0000
  unsigned char  maskNybbleTwo = 15; // binary 0000 1111
  int byteIndex = index / 2;
  unsigned char value = 0;
  if (index == 0 || (index % 2 == 0)) {
    value = (this->data_bytes[byteIndex] & maskNybbleOne) >> 4;
  } else {
    value = this->data_bytes[byteIndex] & maskNybbleTwo;
  }
  return value;
}

// set the nybble at position index to value
void set_nybble_value(struct nybble_array * this, int index, unsigned value) {
  unsigned char maskDeleteFront = 15; // binary 0000 1111
  unsigned char maskDeleteBack = 240; // binary 1111 0000
  int byteIndex = index / 2;
  if (index == 0 || (index % 2 == 0)) {
    this->data_bytes[byteIndex] = this->data_bytes[byteIndex] & maskDeleteFront;
    this->data_bytes[byteIndex] = this->data_bytes[byteIndex] | (value << 4);
  } else {
    this->data_bytes[byteIndex] = this->data_bytes[byteIndex] & maskDeleteBack;
    this->data_bytes[byteIndex] = this->data_bytes[byteIndex] | value;
  }
}

// free the memory used by a nybble array
void nybble_array_free(struct nybble_array * this) {
  free(this);
}

// given an array of unsigned integers with values 0 to 15 create
// a new nybble_array with the same values
struct nybble_array * unsigned_to_nybble_array(unsigned * array, int size) {
  struct nybble_array * result = nybble_array_new(size);
  for (int i = 0; i < size; i++) {
    set_nybble_value(result, i, (unsigned char)array[i]);
  }
  return result;
}

// given an array of nybbles, create a new array of unsigned integers
// with the same values
unsigned * nybble_array_to_unsigned(struct nybble_array * this) {
  unsigned * arr = malloc(sizeof(unsigned) * this->size_in_nybbles);
  for (int i = 0; i < this->size_in_nybbles; i++) {
    arr[i] = (unsigned int)get_nybble_value(this, i);
  }
  return arr;
}

// print the raw byte content of the nybble array
void print_raw_bytes_nybble_array(struct nybble_array * this) {
  for ( int i = 0; i < this->size_in_bytes; i++ ) {
    printf("%x ", this->data_bytes[i]);
  }
  printf("\n");
}

