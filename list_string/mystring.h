//   mystring.h
//   David Gregg
//   November 2022

// a node in a linked list string
struct ls_node {
  char c;     // one character of the string
  struct ls_node * next;
};

// the list string type that points to the nodes
struct mystring {
  struct ls_node * head; // pointer to the first node of the string
};

// (a) create a new empty list string
struct mystring * new_empty_mystring();

// (b) create a new list string with the same contents as a normal
// NULL-terminated C string
struct mystring * new_array2mystring(char * text);

// (c) create a new mystring that is a copy of str
struct mystring * mystring_copy(struct mystring * str);

// (d) create a new mystring that is the concatenation of two
// mystrings
struct mystring * mystring_concatenate(struct mystring * str1,
				       struct mystring * str2);

// (e) create a new mystring containing the same characters as str,
// but in reverse order
struct mystring * mystring_reverse(struct mystring * str);

// (f) return 1 if 'search' is a substring of 'text'; 0 otherwise
int mystring_substring(struct mystring * text, struct mystring * search);

// (g) free the memory used by the mystring
void mystring_free(struct mystring * str);
