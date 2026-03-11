#ifndef LIST_H
#define LIST_H

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

typedef struct Node {
    Film data;
    struct Node *next;
} Node;

Film readFilm(void);
void printFilm(Film f);
Node* createList(void);
void inputList(Node **head);
void displayList(Node *head);
Node* searchByName(Node *head, const char *name);
void modifyElement(Node *head);
Node* getLastElement(Node *head);
int getLength(Node *head);
void swapElements(Node **head, int pos1, int pos2);
void sortList(Node **head);
void addElement(Node **head, int where);
void insertElement(Node **head, int pos, int after);
void deleteElement(Node **head, int pos);
void splitList(Node *head, Node **first, Node **second, int pos);
void concatenateLists(Node **first, Node *second);
void saveToFile(Node *head, const char *filename);
void loadFromFile(Node **head, const char *filename);
void freeList(Node **head);

#endif
