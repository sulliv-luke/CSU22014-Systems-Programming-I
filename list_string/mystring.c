//   mystring.c
//   David Gregg
//   December 2022

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "mystring.h"


// (a) create a new empty list string
struct mystring * new_empty_mystring() {
	struct mystring * result = malloc(sizeof(struct mystring));
	result->head = NULL;
	return result;
}

// (b) create a new list string with the same contents as a normal
// NULL-terminated C string
struct mystring * new_array2mystring(char * text) {
	int max = strlen(text);
	struct mystring * returnStr = new_empty_mystring();
	for (int i = 0; i < max; i++) {
		char yup = text[i];
		struct ls_node * newNode = malloc(sizeof(struct ls_node));
		newNode->c = yup;
		newNode->next = NULL;
		if (returnStr->head == NULL) {
			returnStr->head = newNode;
		} else {
			struct ls_node * tempNode = returnStr->head;
			while(tempNode->next != NULL) {
				tempNode = tempNode->next;
			}
			tempNode->next = newNode;
		}
	}
	return returnStr;
}

// (c) create a new mystring that is a copy of str
struct mystring * mystring_copy(struct mystring *str) {
	struct ls_node * originalPointer = str->head;
	struct mystring * copy = new_empty_mystring();
	struct ls_node * prev = NULL;
	while (originalPointer != NULL) {
		struct ls_node * newNode = malloc(sizeof(struct ls_node));
		newNode->c = originalPointer->c;
		newNode->next = NULL;
		if (prev != NULL) {
			prev->next = newNode;
		} else {
			copy->head = newNode;
		}
		prev = newNode;
		originalPointer = originalPointer->next;
	}
	return copy;
}

// (d) create a new mystring that is the concatenation of two
// mystrings
struct mystring * mystring_concatenate(struct mystring * str1,
				       struct mystring * str2) {

	struct mystring * result =  mystring_copy(str1);
	struct ls_node * temp = result->head;
	while(temp->next!=NULL) {
		temp =temp->next;
	}
	struct mystring * secondPart = mystring_copy(str2);
	temp->next = secondPart->head;
	temp = result->head;
	return result;		
}

// (e) create a new mystring containing the same characters as str,
// but in reverse order
struct mystring * mystring_reverse(struct mystring * str) {
	struct mystring * copy = mystring_copy(str);
	struct ls_node * prev = NULL;
    struct ls_node * current = copy->head;
    struct ls_node * next = NULL;

	while(current != NULL) {
		next = current->next;
		// Reverse current node's pointer
        current->next = prev;
		// Move pointers one position ahead.
        prev = current;
        current = next;
	}
    copy->head = prev;
	return copy;
}

// is there a match starting at this point in the text
int match_substring(struct ls_node * text, struct ls_node * str) {
	if (text->c == str->c) {
		return 1;
	}
	return 0;
}

// (f) return 1 if str is a substring of text; 0 otherwise
int mystring_substring(struct mystring * text, struct mystring * str) {
	struct ls_node * find = str->head;
	struct ls_node * temp = text->head;
	while (find != NULL) {
		if (match_substring(find, temp) == 1) {
			find = find->next;
			temp = temp->next;
		} else {
			return 0;
		}
	}
	return 1;
}


// (g) free the memory used by the mystring
void mystring_free(struct mystring * str) {
	free(str);
}
