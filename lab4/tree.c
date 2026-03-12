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

TreeNode* createTree(void) {
    printf("Datele radacinii:\n");
    TreeNode *root = createNode(readFilm());

    Queue q; initQueue(&q);
    enqueue(&q, root);

    while (!isQueueEmpty(&q)) {
        TreeNode *cur = dequeue(&q);
        char ans;

        printf("\nNodul curent: \"%s\"\n", cur->data.denumirea);

        printf("Adaugati fiu stang? (d/n): "); scanf(" %c", &ans); while (getchar() != '\n');
        if (ans == 'd' || ans == 'D') {
            printf("Datele fiului stang:\n");
            cur->left = createNode(readFilm());
            enqueue(&q, cur->left);
        }

        printf("Adaugati fiu drept? (d/n): "); scanf(" %c", &ans); while (getchar() != '\n');
        if (ans == 'd' || ans == 'D') {
            printf("Datele fiului drept:\n");
            cur->right = createNode(readFilm());
            enqueue(&q, cur->right);
        }
    }
    printf("Arborele creat.\n");
    return root;
}

void displayBFS(TreeNode *root) {
    if (!root) { printf("Arborele este gol.\n"); return; }
    printf("\n--- Afisare BFS (in latime) ---\n");
    Queue q; initQueue(&q);
    enqueue(&q, root);
    int cnt = 0;
    while (!isQueueEmpty(&q)) {
        TreeNode *cur = dequeue(&q);
        printf("\n[%d]\n", ++cnt);
        printNode(cur);
        if (cur->left)  enqueue(&q, cur->left);
        if (cur->right) enqueue(&q, cur->right);
    }
    printf("\nTotal noduri: %d\n", cnt);
}

void displayDFS(TreeNode *root) {
    if (!root) { printf("Arborele este gol.\n"); return; }
    printf("\n--- Afisare DFS (in adancime, preordine) ---\n");
    StackNode *st = NULL;
    push(&st, root);
    int cnt = 0;
    while (!isStackEmpty(st)) {
        TreeNode *cur = pop(&st);
        printf("\n[%d]\n", ++cnt);
        printNode(cur);
        if (cur->right) push(&st, cur->right);
        if (cur->left)  push(&st, cur->left);
    }
    printf("\nTotal noduri: %d\n", cnt);
}

TreeNode* searchBFS(TreeNode *root, const char *name) {
    if (!root) return NULL;
    Queue q; initQueue(&q);
    enqueue(&q, root);
    int pos = 0;
    while (!isQueueEmpty(&q)) {
        TreeNode *cur = dequeue(&q);
        pos++;
        if (strcmp(cur->data.denumirea, name) == 0) {
            printf("Gasit (BFS, pozitia %d):\n", pos);
            printNode(cur);
            return cur;
        }
        if (cur->left)  enqueue(&q, cur->left);
        if (cur->right) enqueue(&q, cur->right);
    }
    printf("Nu a fost gasit (BFS): \"%s\"\n", name);
    return NULL;
}

TreeNode* searchDFS(TreeNode *root, const char *name) {
    if (!root) return NULL;
    StackNode *st = NULL;
    push(&st, root);
    int pos = 0;
    while (!isStackEmpty(st)) {
        TreeNode *cur = pop(&st);
        pos++;
        if (strcmp(cur->data.denumirea, name) == 0) {
            printf("Gasit (DFS, pozitia %d):\n", pos);
            printNode(cur);
            return cur;
        }
        if (cur->right) push(&st, cur->right);
        if (cur->left)  push(&st, cur->left);
    }
    printf("Nu a fost gasit (DFS): \"%s\"\n", name);
    return NULL;
}

void modifyBFS(TreeNode *root, const char *name) {
    TreeNode *n = searchBFS(root, name);
    if (!n) return;
    printf("Date noi:\n");
    n->data = readFilm();
    printf("Modificat.\n");
}

void modifyDFS(TreeNode *root, const char *name) {
    TreeNode *n = searchDFS(root, name);
    if (!n) return;
    printf("Date noi:\n");
    n->data = readFilm();
    printf("Modificat.\n");
}

int countBFS(TreeNode *root) {
    if (!root) return 0;
    Queue q; initQueue(&q);
    enqueue(&q, root);
    int cnt = 0;
    while (!isQueueEmpty(&q)) {
        TreeNode *cur = dequeue(&q);
        cnt++;
        if (cur->left)  enqueue(&q, cur->left);
        if (cur->right) enqueue(&q, cur->right);
    }
    return cnt;
}

int countDFS(TreeNode *root) {
    if (!root) return 0;
    StackNode *st = NULL;
    push(&st, root);
    int cnt = 0;
    while (!isStackEmpty(st)) {
        TreeNode *cur = pop(&st);
        cnt++;
        if (cur->right) push(&st, cur->right);
        if (cur->left)  push(&st, cur->left);
    }
    return cnt;
}

int heightIterative(TreeNode *root) {
    if (!root) return 0;
    Queue q; initQueue(&q);
    enqueue(&q, root);
    int h = 0;
    while (!isQueueEmpty(&q)) {
        int sz = 0;
        for (QueueNode *tmp = q.front; tmp; tmp = tmp->next) sz++;
        for (int i = 0; i < sz; i++) {
            TreeNode *cur = dequeue(&q);
            if (!cur) continue;
            if (cur->left)  enqueue(&q, cur->left);
            if (cur->right) enqueue(&q, cur->right);
        }
        h++;
    }
    return h;
}

void freeTree(TreeNode **root) {
    if (!*root) { printf("Arborele este gol.\n"); return; }
    StackNode *st = NULL, *out = NULL;
    push(&st, *root);
    while (!isStackEmpty(st)) {
        TreeNode *cur = pop(&st);
        push(&out, cur);
        if (cur->left)  push(&st, cur->left);
        if (cur->right) push(&st, cur->right);
    }
    int cnt = 0;
    while (!isStackEmpty(out)) {
        TreeNode *cur = pop(&out);
        free(cur);
        cnt++;
    }
    *root = NULL;
    printf("Eliberate %d noduri.\n", cnt);
}
