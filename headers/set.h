#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int color;
    struct Node *left, *right, *parent;
} Node;

Node *newNode(int data);
void leftRotate(Node **root, Node *x);
void rightRotate(Node **root, Node *y);
void insertFixup(Node **root, Node *z);
void insert(int data);
Node *search(int data);
void transplant(Node **root, Node *u, Node *v);
Node *treeMinimum(Node *node);
void deleteFixup(Node **root, Node *x);
void erase(int data);


#endif
