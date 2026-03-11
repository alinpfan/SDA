#include "list.h"

static Node* createNode(Film f) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { printf("Eroare: memorie insuficienta!\n"); exit(1); }
    n->data = f;
    n->next = NULL;
    return n;
}

static Node* getNodeAt(Node *head, int pos) {
    for (int i = 1; head && i < pos; i++) head = head->next;
    return head;
}

static void appendNode(Node **head, Node *newNode) {
    if (!*head) { *head = newNode; return; }
    Node *t = *head;
    while (t->next) t = t->next;
    t->next = newNode;
}

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

Node* createList(void) {
    int n;
    printf("Numarul de elemente: "); scanf("%d", &n); while (getchar() != '\n');
    Node *head = NULL;
    for (int i = 0; i < n; i++) {
        printf("\n--- Filmul %d ---\n", i + 1);
        appendNode(&head, createNode(readFilm()));
    }
    printf("Lista creata (%d elemente).\n", n);
    return head;
}

void inputList(Node **head) {
    int n;
    printf("Cate elemente adaugati? "); scanf("%d", &n); while (getchar() != '\n');
    for (int i = 0; i < n; i++) {
        printf("\n--- Filmul nou %d ---\n", i + 1);
        appendNode(head, createNode(readFilm()));
    }
    printf("Adaugate %d elemente.\n", n);
}

void displayList(Node *head) {
    if (!head) { printf("Lista este goala.\n"); return; }
    int i = 1;
    for (Node *c = head; c; c = c->next, i++) {
        printf("\n[%d] Adr: %p | Next: %p\n", i, (void*)c, (void*)c->next);
        printFilm(c->data);
    }
    printf("\nTotal: %d\n", i - 1);
}

Node* searchByName(Node *head, const char *name) {
    int p = 1;
    for (Node *c = head; c; c = c->next, p++)
        if (strcmp(c->data.denumirea, name) == 0) {
            printf("Gasit la pozitia %d (adr: %p):\n", p, (void*)c);
            printFilm(c->data);
            return c;
        }
    printf("Nu a fost gasit: \"%s\"\n", name);
    return NULL;
}

void modifyElement(Node *head) {
    if (!head) { printf("Lista este goala.\n"); return; }
    int pos;
    printf("Pozitia de modificat: "); scanf("%d", &pos); while (getchar() != '\n');
    Node *n = getNodeAt(head, pos);
    if (!n) { printf("Pozitie invalida!\n"); return; }
    printf("Date curente:\n"); printFilm(n->data);
    printf("Date noi:\n"); n->data = readFilm();
    printf("Modificat.\n");
}

Node* getLastElement(Node *head) {
    if (!head) { printf("Lista este goala.\n"); return NULL; }
    Node *c = head;
    while (c->next) c = c->next;
    printf("Ultimul element (adr: %p):\n", (void*)c);
    printFilm(c->data);
    return c;
}

int getLength(Node *head) {
    int len = 0;
    for (Node *c = head; c; c = c->next) len++;
    return len;
}

void swapElements(Node **head, int pos1, int pos2) {
    if (pos1 == pos2) return;
    Node *prev1 = NULL, *n1 = *head;
    for (int i = 1; n1 && i < pos1; i++) { prev1 = n1; n1 = n1->next; }
    Node *prev2 = NULL, *n2 = *head;
    for (int i = 1; n2 && i < pos2; i++) { prev2 = n2; n2 = n2->next; }
    if (!n1 || !n2) { printf("Pozitie invalida!\n"); return; }
    if (prev1) prev1->next = n2; else *head = n2;
    if (prev2) prev2->next = n1; else *head = n1;
    Node *tmp = n1->next; n1->next = n2->next; n2->next = tmp;
    printf("Interschimbate: %d <-> %d\n", pos1, pos2);
}

void sortList(Node **head) {
    if (!*head || !(*head)->next) return;
    int sw;
    do {
        sw = 0;
        for (Node *c = *head; c->next; c = c->next)
            if (c->data.anul > c->next->data.anul) {
                Film t = c->data; c->data = c->next->data; c->next->data = t;
                sw = 1;
            }
    } while (sw);
    printf("Lista sortata dupa an.\n");
}

void addElement(Node **head, int where) {
    printf("Datele filmului nou:\n");
    Node *n = createNode(readFilm());
    if (where == 0) {
        n->next = *head; *head = n;
        printf("Adaugat la inceput.\n");
    } else {
        appendNode(head, n);
        printf("Adaugat la sfarsit.\n");
    }
}

void insertElement(Node **head, int pos, int after) {
    if (!after) {
        if (pos <= 0) { printf("Pozitie invalida!\n"); return; }
        printf("Datele filmului nou (inaintea poz. %d):\n", pos);
        Node *n = createNode(readFilm());
        if (pos == 1) { n->next = *head; *head = n; }
        else {
            Node *prev = getNodeAt(*head, pos - 1);
            if (!prev || !prev->next) { printf("Pozitie invalida!\n"); free(n); return; }
            n->next = prev->next; prev->next = n;
        }
        printf("Inserat inaintea poz. %d.\n", pos);
    } else {
        Node *node = getNodeAt(*head, pos);
        if (!node) { printf("Pozitie invalida!\n"); return; }
        printf("Datele filmului nou (dupa poz. %d):\n", pos);
        Node *n = createNode(readFilm());
        n->next = node->next; node->next = n;
        printf("Inserat dupa poz. %d.\n", pos);
    }
}

void deleteElement(Node **head, int pos) {
    if (!*head) { printf("Lista este goala.\n"); return; }
    if (pos <= 0) { printf("Pozitie invalida!\n"); return; }
    Node *del;
    if (pos == 1) { del = *head; *head = (*head)->next; }
    else {
        Node *prev = getNodeAt(*head, pos - 1);
        if (!prev || !prev->next) { printf("Pozitie invalida!\n"); return; }
        del = prev->next; prev->next = del->next;
    }
    printf("Sters poz. %d: ", pos); printFilm(del->data);
    free(del);
}

void splitList(Node *head, Node **first, Node **second, int pos) {
    if (!head) { printf("Lista goala.\n"); *first = *second = NULL; return; }
    *first = head;
    Node *n = getNodeAt(head, pos);
    if (!n) { printf("Pozitie invalida!\n"); *second = NULL; return; }
    *second = n->next; n->next = NULL;
    printf("Divizata dupa poz. %d.\n", pos);
}

void concatenateLists(Node **first, Node *second) {
    if (!*first) *first = second;
    else { Node *t = *first; while (t->next) t = t->next; t->next = second; }
    printf("Listele concatenate.\n");
}

void saveToFile(Node *head, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) { printf("Eroare deschidere fisier!\n"); return; }
    int c = 0;
    for (Node *n = head; n; n = n->next, c++)
        fprintf(fp, "%s\n%s\n%s\n%s\n%d\n", n->data.denumirea, n->data.tara,
                n->data.regizorul, n->data.genul, n->data.anul);
    fclose(fp);
    printf("Salvate %d elemente in \"%s\".\n", c, filename);
}

void loadFromFile(Node **head, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { printf("Eroare deschidere fisier!\n"); return; }
    freeList(head);
    int c = 0;
    Film f;
    while (fgets(f.denumirea, MAX_STR, fp)) {
        f.denumirea[strcspn(f.denumirea, "\n")] = '\0';
        if (!fgets(f.tara, MAX_STR, fp)) break;
        f.tara[strcspn(f.tara, "\n")] = '\0';
        if (!fgets(f.regizorul, MAX_STR, fp)) break;
        f.regizorul[strcspn(f.regizorul, "\n")] = '\0';
        if (!fgets(f.genul, MAX_STR, fp)) break;
        f.genul[strcspn(f.genul, "\n")] = '\0';
        if (fscanf(fp, "%d", &f.anul) != 1) break;
        fgetc(fp);
        appendNode(head, createNode(f));
        c++;
    }
    fclose(fp);
    printf("Citite %d elemente din \"%s\".\n", c, filename);
}

void freeList(Node **head) {
    int c = 0;
    while (*head) { Node *t = *head; *head = t->next; free(t); c++; }
    if (c) printf("Eliberate %d elemente.\n", c);
}
