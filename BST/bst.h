struct BST {
    struct Node * root;
};

struct Node {
    int val;
    int key;
    struct Node *left;
    struct Node *right;
    int n; // number of nodes in subtree
};

struct BST * new_BST();

struct Node * new_node(int key, int val, int n);

int isEmpty(struct BST * tree);

int size(struct BST * tree);

int contains(struct BST * tree, int key);

int get(struct BST * tree, int key); // Return value associated with given key

void put(struct BST * tree, int key, int val);

int height(struct BST * tree);

struct Node * traverse(struct Node * x, int ind);

int median(struct BST * tree);

void del(struct BST * tree, int key);

struct Node * delMax(struct Node * x);

struct Node * max(struct Node * x);

void printInorder(struct Node * root);

void printPreorder(struct Node * root);
