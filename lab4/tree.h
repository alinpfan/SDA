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
void displayBFS(TreeNode *root);
void displayDFS(TreeNode *root);
TreeNode* searchBFS(TreeNode *root, const char *name);
TreeNode* searchDFS(TreeNode *root, const char *name);
void modifyBFS(TreeNode *root, const char *name);
void modifyDFS(TreeNode *root, const char *name);
int countBFS(TreeNode *root);
int countDFS(TreeNode *root);
int heightIterative(TreeNode *root);
void freeTree(TreeNode **root);

#endif
