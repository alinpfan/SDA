#include "tree.h"

void printMenu(void) {
    system("clear");
    printf("\n============================================\n"
           "   TAD \"Arbore binar\" - Film (Recursiv)\n"
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
    printf("Metoda: 1-Recursiv prin coada (latime), 2-Recursiv prin stiva (adancime): ");
    scanf("%d", &m); while (getchar() != '\n');
    return m;
}

int main(void) {
    TreeNode *root = NULL;
    int opt;
    int method;
    char buf[MAX_STR];
    TreeNode *found;

    do {
        printMenu();
        scanf("%d", &opt); while (getchar() != '\n');

        switch (opt) {
        case 1:
            if (root) printf("Arborele exista deja. Eliberati memoria (opt. 7).\n");
            else root = createTree();
            break;
        case 2:
            method = chooseMethod();
            if (method == 1) displayQueueRecursive(root);
            else if (method == 2) displayStackRecursive(root);
            else printf("Metoda invalida!\n");
            break;
        case 3:
            method = chooseMethod();
            printf("Denumirea de cautat: "); fgets(buf, MAX_STR, stdin); buf[strcspn(buf, "\n")] = '\0';
            if (method == 1) found = searchQueueRecursive(root, buf);
            else if (method == 2) found = searchStackRecursive(root, buf);
            else {
                printf("Metoda invalida!\n");
                found = NULL;
            }
            if (found) {
                printf("Nod gasit:\n");
                printNode(found);
            } else {
                printf("Nu a fost gasit nodul: \"%s\"\n", buf);
            }
            break;
        case 4:
            method = chooseMethod();
            printf("Denumirea nodului de modificat: "); fgets(buf, MAX_STR, stdin); buf[strcspn(buf, "\n")] = '\0';
            if (method == 1) modifyQueueRecursive(root, buf);
            else if (method == 2) modifyStackRecursive(root, buf);
            else printf("Metoda invalida!\n");
            break;
        case 5:
            method = chooseMethod();
            if (method == 1) printf("Numarul de noduri (coada): %d\n", countQueueRecursive(root));
            else if (method == 2) printf("Numarul de noduri (stiva): %d\n", countStackRecursive(root));
            else printf("Metoda invalida!\n");
            break;
        case 6:
            printf("Inaltimea arborelui: %d\n", heightRecursive(root));
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
