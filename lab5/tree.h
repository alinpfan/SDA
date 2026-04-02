#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100

typedef struct {
    char denumirea[MAX_STR];
    char tara[MAX_STR];
    char regizorul[MAX_STR];
    char genul[MAX_STR];
    int anul;
} Film;

typedef struct TreeNode {
    Film data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct QueueNode {
    TreeNode *tnode;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
} Queue;

typedef struct StackNode {
    TreeNode *tnode;
    struct StackNode *next;
} StackNode;

void initQueue(Queue *q);
int isQueueEmpty(Queue *q);
void enqueue(Queue *q, TreeNode *t);
TreeNode* dequeue(Queue *q);

void push(StackNode **top, TreeNode *t);
TreeNode* pop(StackNode **top);
int isStackEmpty(StackNode *top);

Film readFilm(void);
void printFilm(Film f);
void printNode(TreeNode *n);

TreeNode* createTree(void);
void displayTreeAllRecursive(TreeNode *root);
void displayQueueRecursive(TreeNode *root);
void displayStackRecursive(TreeNode *root);
TreeNode* searchRecursive(TreeNode *root, const char *name);
TreeNode* searchQueueRecursive(TreeNode *root, const char *name);
TreeNode* searchStackRecursive(TreeNode *root, const char *name);
void modifyRecursive(TreeNode *root, const char *name);
void modifyQueueRecursive(TreeNode *root, const char *name);
void modifyStackRecursive(TreeNode *root, const char *name);
int countRecursive(TreeNode *root);
int countQueueRecursive(TreeNode *root);
int countStackRecursive(TreeNode *root);
int heightRecursive(TreeNode *root);
void freeTree(TreeNode **root);

#endif
