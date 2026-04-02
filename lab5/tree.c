#include "tree.h"

void initQueue(Queue *q) { q->front = q->rear = NULL; }

int isQueueEmpty(Queue *q) { return q->front == NULL; }

void enqueue(Queue *q, TreeNode *t) {
    QueueNode *n = (QueueNode*)malloc(sizeof(QueueNode));
    if (!n) { printf("Eroare: memorie insuficienta!\n"); exit(1); }
    n->tnode = t; n->next = NULL;
    if (!q->rear) q->front = q->rear = n;
    else { q->rear->next = n; q->rear = n; }
}

TreeNode* dequeue(Queue *q) {
    if (isQueueEmpty(q)) return NULL;
    QueueNode *tmp = q->front;
    TreeNode *t = tmp->tnode;
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    free(tmp);
    return t;
}

void push(StackNode **top, TreeNode *t) {
    StackNode *n = (StackNode*)malloc(sizeof(StackNode));
    if (!n) { printf("Eroare: memorie insuficienta!\n"); exit(1); }
    n->tnode = t; n->next = *top; *top = n;
}

TreeNode* pop(StackNode **top) {
    if (!*top) return NULL;
    StackNode *tmp = *top;
    TreeNode *t = tmp->tnode;
    *top = tmp->next;
    free(tmp);
    return t;
}

int isStackEmpty(StackNode *top) { return top == NULL; }

Film readFilm(void) {
    Film f;
    printf("  Denumirea: "); fgets(f.denumirea, MAX_STR, stdin); f.denumirea[strcspn(f.denumirea, "\n")] = '\0';
    printf("  Tara: ");      fgets(f.tara, MAX_STR, stdin);      f.tara[strcspn(f.tara, "\n")] = '\0';
    printf("  Regizorul: "); fgets(f.regizorul, MAX_STR, stdin); f.regizorul[strcspn(f.regizorul, "\n")] = '\0';
    printf("  Genul: ");     fgets(f.genul, MAX_STR, stdin);     f.genul[strcspn(f.genul, "\n")] = '\0';
    printf("  Anul: ");      scanf("%d", &f.anul); while (getchar() != '\n');
    return f;
}

void printFilm(Film f) {
    printf("  Denumirea: %s | Tara: %s | Regizorul: %s | Genul: %s | Anul: %d\n",
           f.denumirea, f.tara, f.regizorul, f.genul, f.anul);
}

void printNode(TreeNode *n) {
    printf("  Nod: %p | Stang: %p | Drept: %p\n", (void*)n, (void*)n->left, (void*)n->right);
    printFilm(n->data);
}

static TreeNode* createNode(Film f) {
    TreeNode *n = (TreeNode*)malloc(sizeof(TreeNode));
    if (!n) { printf("Eroare: memorie insuficienta!\n"); exit(1); }
    n->data = f; n->left = n->right = NULL;
    return n;
}

static void createSubtree(TreeNode *node);

TreeNode* createTree(void) {
    printf("Datele radacinii:\n");
    TreeNode *root = createNode(readFilm());

    createSubtree(root);

    printf("Arborele creat.\n");
    return root;
}

static void createSubtree(TreeNode *node) {
    char ans;
    if (!node) return;

    if (!node->left) {
        printf("\nNodul curent: \"%s\"\n", node->data.denumirea);
        printf("Adaugati fiu stang? (d/n): "); scanf(" %c", &ans); while (getchar() != '\n');
        if (ans == 'd' || ans == 'D') {
            printf("Datele fiului stang:\n");
            node->left = createNode(readFilm());
        }
    }
    if (!node->right) {
        printf("Adaugati fiu drept? (d/n): "); scanf(" %c", &ans); while (getchar() != '\n');
        if (ans == 'd' || ans == 'D') {
            printf("Datele fiului drept:\n");
            node->right = createNode(readFilm());
        }
    }

    createSubtree(node->left);
    createSubtree(node->right);
}

static void printIndexedNode(TreeNode *node, int *index) {
    printf("\n[%d]\n", ++(*index));
    printNode(node);
}

static void preorderLR(TreeNode *root, int *index) {
    if (!root) return;
    printIndexedNode(root, index);
    preorderLR(root->left, index);
    preorderLR(root->right, index);
}

static void preorderRL(TreeNode *root, int *index) {
    if (!root) return;
    printIndexedNode(root, index);
    preorderRL(root->right, index);
    preorderRL(root->left, index);
}

static void inorderLR(TreeNode *root, int *index) {
    if (!root) return;
    inorderLR(root->left, index);
    printIndexedNode(root, index);
    inorderLR(root->right, index);
}

static void inorderRL(TreeNode *root, int *index) {
    if (!root) return;
    inorderRL(root->right, index);
    printIndexedNode(root, index);
    inorderRL(root->left, index);
}

static void postorderLR(TreeNode *root, int *index) {
    if (!root) return;
    postorderLR(root->left, index);
    postorderLR(root->right, index);
    printIndexedNode(root, index);
}

static void postorderRL(TreeNode *root, int *index) {
    if (!root) return;
    postorderRL(root->right, index);
    postorderRL(root->left, index);
    printIndexedNode(root, index);
}

void displayTreeAllRecursive(TreeNode *root) {
    int cnt = 0;
    if (!root) {
        printf("Arborele este gol.\n");
        return;
    }

    printf("\n--- Preordine R-S-D (radacina-stang-drept) ---\n");
    preorderLR(root, &cnt);
    printf("\nTotal noduri parcurse: %d\n", cnt);

    cnt = 0;
    printf("\n--- Preordine R-D-S (radacina-drept-stang) ---\n");
    preorderRL(root, &cnt);
    printf("\nTotal noduri parcurse: %d\n", cnt);

    cnt = 0;
    printf("\n--- Inordine S-R-D (stang-radacina-drept) ---\n");
    inorderLR(root, &cnt);
    printf("\nTotal noduri parcurse: %d\n", cnt);

    cnt = 0;
    printf("\n--- Inordine D-R-S (drept-radacina-stang) ---\n");
    inorderRL(root, &cnt);
    printf("\nTotal noduri parcurse: %d\n", cnt);

    cnt = 0;
    printf("\n--- Postordine S-D-R (stang-drept-radacina) ---\n");
    postorderLR(root, &cnt);
    printf("\nTotal noduri parcurse: %d\n", cnt);

    cnt = 0;
    printf("\n--- Postordine D-S-R (drept-stang-radacina) ---\n");
    postorderRL(root, &cnt);
    printf("\nTotal noduri parcurse: %d\n", cnt);
}

static void displayQueueHelper(Queue *q, int *idx) {
    TreeNode *cur;
    if (isQueueEmpty(q)) return;

    cur = dequeue(q);
    printIndexedNode(cur, idx);
    if (cur->left) enqueue(q, cur->left);
    if (cur->right) enqueue(q, cur->right);
    displayQueueHelper(q, idx);
}

void displayQueueRecursive(TreeNode *root) {
    Queue q;
    int idx = 0;
    if (!root) {
        printf("Arborele este gol.\n");
        return;
    }

    printf("\n--- Afisare recursiva prin coada (BFS) ---\n");
    initQueue(&q);
    enqueue(&q, root);
    displayQueueHelper(&q, &idx);
    printf("\nTotal noduri parcurse: %d\n", idx);
}

static void displayStackHelper(StackNode **st, int *idx) {
    TreeNode *cur;
    if (isStackEmpty(*st)) return;

    cur = pop(st);
    printIndexedNode(cur, idx);
    if (cur->right) push(st, cur->right);
    if (cur->left) push(st, cur->left);
    displayStackHelper(st, idx);
}

void displayStackRecursive(TreeNode *root) {
    StackNode *st = NULL;
    int idx = 0;
    if (!root) {
        printf("Arborele este gol.\n");
        return;
    }

    printf("\n--- Afisare recursiva prin stiva (DFS preordine) ---\n");
    push(&st, root);
    displayStackHelper(&st, &idx);
    printf("\nTotal noduri parcurse: %d\n", idx);
}

TreeNode* searchRecursive(TreeNode *root, const char *name) {
    TreeNode *found;
    if (!root) return NULL;
    if (strcmp(root->data.denumirea, name) == 0) return root;

    found = searchRecursive(root->left, name);
    if (found) return found;
    return searchRecursive(root->right, name);
}

static TreeNode* searchQueueHelper(Queue *q, const char *name) {
    TreeNode *cur;
    if (isQueueEmpty(q)) return NULL;

    cur = dequeue(q);
    if (strcmp(cur->data.denumirea, name) == 0) return cur;
    if (cur->left) enqueue(q, cur->left);
    if (cur->right) enqueue(q, cur->right);
    return searchQueueHelper(q, name);
}

TreeNode* searchQueueRecursive(TreeNode *root, const char *name) {
    Queue q;
    if (!root) return NULL;

    initQueue(&q);
    enqueue(&q, root);
    return searchQueueHelper(&q, name);
}

static TreeNode* searchStackHelper(StackNode **st, const char *name) {
    TreeNode *cur;
    if (isStackEmpty(*st)) return NULL;

    cur = pop(st);
    if (strcmp(cur->data.denumirea, name) == 0) return cur;
    if (cur->right) push(st, cur->right);
    if (cur->left) push(st, cur->left);
    return searchStackHelper(st, name);
}

TreeNode* searchStackRecursive(TreeNode *root, const char *name) {
    StackNode *st = NULL;
    if (!root) return NULL;

    push(&st, root);
    return searchStackHelper(&st, name);
}

void modifyRecursive(TreeNode *root, const char *name) {
    TreeNode *n = searchRecursive(root, name);
    if (!n) {
        printf("Nu a fost gasit nodul: \"%s\"\n", name);
        return;
    }

    printf("Nod gasit:\n");
    printNode(n);
    printf("Date noi:\n");
    n->data = readFilm();
    printf("Modificat.\n");
}

void modifyQueueRecursive(TreeNode *root, const char *name) {
    TreeNode *n = searchQueueRecursive(root, name);
    if (!n) {
        printf("Nu a fost gasit nodul: \"%s\"\n", name);
        return;
    }

    printf("Nod gasit:\n");
    printNode(n);
    printf("Date noi:\n");
    n->data = readFilm();
    printf("Modificat.\n");
}

void modifyStackRecursive(TreeNode *root, const char *name) {
    TreeNode *n = searchStackRecursive(root, name);
    if (!n) {
        printf("Nu a fost gasit nodul: \"%s\"\n", name);
        return;
    }

    printf("Nod gasit:\n");
    printNode(n);
    printf("Date noi:\n");
    n->data = readFilm();
    printf("Modificat.\n");
}

int countRecursive(TreeNode *root) {
    if (!root) return 0;
    return 1 + countRecursive(root->left) + countRecursive(root->right);
}

static int countQueueHelper(Queue *q) {
    TreeNode *cur;
    if (isQueueEmpty(q)) return 0;

    cur = dequeue(q);
    if (cur->left) enqueue(q, cur->left);
    if (cur->right) enqueue(q, cur->right);
    return 1 + countQueueHelper(q);
}

int countQueueRecursive(TreeNode *root) {
    Queue q;
    if (!root) return 0;

    initQueue(&q);
    enqueue(&q, root);
    return countQueueHelper(&q);
}

static int countStackHelper(StackNode **st) {
    TreeNode *cur;
    if (isStackEmpty(*st)) return 0;

    cur = pop(st);
    if (cur->right) push(st, cur->right);
    if (cur->left) push(st, cur->left);
    return 1 + countStackHelper(st);
}

int countStackRecursive(TreeNode *root) {
    StackNode *st = NULL;
    if (!root) return 0;

    push(&st, root);
    return countStackHelper(&st);
}

static int maxInt(int a, int b) {
    return (a > b) ? a : b;
}

int heightRecursive(TreeNode *root) {
    if (!root) return 0;
    return 1 + maxInt(heightRecursive(root->left), heightRecursive(root->right));
}

static int freeTreePostorder(TreeNode *root) {
    int cnt;
    if (!root) return 0;
    cnt = freeTreePostorder(root->left) + freeTreePostorder(root->right) + 1;
    free(root);
    return cnt;
}

void freeTree(TreeNode **root) {
    int cnt;
    if (!*root) {
        printf("Arborele este gol.\n");
        return;
    }

    cnt = freeTreePostorder(*root);
    *root = NULL;
    printf("Eliberate %d noduri.\n", cnt);
}
