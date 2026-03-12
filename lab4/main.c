#include "tree.h"

void printMenu(void) {
    system("clear");
    printf("\n============================================\n"
           "   TAD \"Arbore binar\" - Film (Iterativ)\n"
           "============================================\n"
           "  1. Crearea arborelui\n"
           "  2. Afisarea nodurilor\n"
           "  3. Cautarea nodului\n"
           "  4. Modificarea nodului\n"
           "  5. Numarul de noduri\n"
           "  6. Inaltimea arborelui\n"
           "  7. Eliberarea memoriei\n"
           "  0. Iesire\n"
           "============================================\n"
           "Optiunea: ");
}

int chooseMethod(void) {
    int m;
    printf("Metoda: 1-BFS (coada/latime), 2-DFS (stiva/adancime): ");
    scanf("%d", &m); while (getchar() != '\n');
    return m;
}

int main(void) {
    TreeNode *root = NULL;
    int opt;
    char buf[MAX_STR];

    do {
        printMenu();
        scanf("%d", &opt); while (getchar() != '\n');

        switch (opt) {
        case 1:
            if (root) printf("Arborele exista deja. Eliberati memoria (opt. 7).\n");
            else root = createTree();
            break;
        case 2:
            if (chooseMethod() == 1) displayBFS(root);
            else displayDFS(root);
            break;
        case 3:
            printf("Denumirea de cautat: "); fgets(buf, MAX_STR, stdin); buf[strcspn(buf, "\n")] = '\0';
            if (chooseMethod() == 1) searchBFS(root, buf);
            else searchDFS(root, buf);
            break;
        case 4:
            printf("Denumirea nodului de modificat: "); fgets(buf, MAX_STR, stdin); buf[strcspn(buf, "\n")] = '\0';
            if (chooseMethod() == 1) modifyBFS(root, buf);
            else modifyDFS(root, buf);
            break;
        case 5:
            if (chooseMethod() == 1) printf("Numarul de noduri (BFS): %d\n", countBFS(root));
            else printf("Numarul de noduri (DFS): %d\n", countDFS(root));
            break;
        case 6:
            printf("Inaltimea arborelui: %d\n", heightIterative(root));
            break;
        case 7: freeTree(&root); break;
        case 0: printf("La revedere!\n"); break;
        default: printf("Optiune invalida!\n"); break;
        }
        if (opt != 0) {
            printf("\nApasati Enter pentru a continua...");
            while (getchar() != '\n');
        }
    } while (opt != 0);

    freeTree(&root);
    return 0;
}
