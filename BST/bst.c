#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

struct BST * new_BST() {
    struct BST * result = malloc(sizeof(struct BST));
    result->root = NULL;
    return result;
}

struct Node * new_node(int key, int val, int n) {
    struct Node * result = malloc(sizeof(struct Node));
    result->key = key;
    result->val = val;
    result->n = n;
    result->left = NULL;
    result->right = NULL;
    return result;
}

int sizeN(struct Node * x) {
    if (x == NULL) {
        return 0;
    } else {
        return x->n;
    }
}

int size(struct BST * tree) {
    return sizeN(tree->root);
}

int isEmpty(struct BST * tree){
    if (size(tree) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int getN(struct Node * x, int key) {
    if (x == NULL) {
        return -1;
    }
    if (key < x->key) {
        return getN(x->left, key);
    } else if (key > x->key) {
        return getN(x->right, key);
    } else {
        return x->val;
    }
}

int get(struct BST * tree, int key) {
    return getN(tree->root, key);
}

int contains(struct BST * tree, int key) {
    if (get(tree, key) == -1) {
        return 0;
    } else {
        return 1;
    }
}

struct Node * putN(struct Node * x, int key, int val) {
    if (x == NULL) {
        return new_node(key, val, 1);
    }
    if (key < x->key) {
        x->left = putN(x->left, key, val);
    } else if (key > x->key) {
        x->right = putN(x->right, key, val);
    } else {
        x->val = val;
    }
    x->n = 1 + sizeN(x->left) + sizeN(x->right);
    return x;
}

struct Node * delN (struct Node * x, int key) {
    if (key < x->key) {
        x->left = delN(x->left, key);
    } else {
        if (key > x->key) {
            x->right = delN(x->right, key);
        } else {
            if (x->right == NULL) {
                return x->left;
            }
            struct Node * tempNode = x;
            x = max(tempNode->left);
            x->left = delMax(tempNode->left);
            x->right =tempNode->right;
        }
    }
    x->n = sizeN(x->left) + sizeN(x->right) + 1;
    return x;
}

void del(struct BST * tree, int key) {
    if(contains(tree, key) == 1) {
        tree->root = delN(tree->root, key);
    }
}

struct Node * max(struct Node * x) {
    if (x->right == NULL) {
        return x;
    }
    return max(x->right);
}

struct Node * delMax(struct Node * x) {
    if (x->right == NULL) {
        return x->left;
    }
    x->right = delMax(x->right);
    x->n = sizeN(x->left) + sizeN(x->right) + 1;
    return x;
}

void put(struct BST * tree, int key, int val) {
    tree->root = putN(tree->root, key, val);
}

int heightN(struct Node * x) {
    if (x == NULL) {
        return -1;
    }
    int leftHeight = heightN(x->left);
    int rightHeight = heightN(x->right);
    if (leftHeight > rightHeight) {
        return 1 + leftHeight;
    }
    return 1 + rightHeight;
}

int height(struct BST * tree) {
    return heightN(tree->root);
}

struct Node * traverse(struct Node * x, int ind) {
    int leftLen = sizeN(x->left);
    if (leftLen > ind) {
        return traverse(x->left, ind);
    } else if (leftLen < ind) {
        return traverse(x->right, ind-leftLen-1);
    } else {
        return x;
    }
}

int median(struct BST * tree) {
    if (isEmpty(tree) == 1) {
        return -1;
    }
    int index = ((tree->root->n) + 1)/2;
    struct Node * tempNode = traverse(tree->root, index-1);
    return tempNode->key;
}

void printInorder(struct Node * root)
{
    if(root == NULL)
        return;
    printInorder(root->left);
    printf("%d ", root->key);
    printInorder(root->right);
}

void printPreorder(struct Node * root)
{
    if (root == NULL) {
        return;
    } else {
        printf("%d ", root->key);
    }
    if (root->left != NULL) {
        printPreorder(root->left);
    }
    if (root->right != NULL) {
        printPreorder(root->right);
    }
}