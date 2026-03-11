#include "list.h"

void printMenu(void) {
    system("clear");
    printf("\n============================================\n"
           "   TAD \"Lista simplu inlantuita\" - Film\n"
           "============================================\n"
           "  1. Crearea listei\n"
           "  2. Introducerea elementelor\n"
           "  3. Afisarea elementelor\n"
           "  4. Cautarea elementului\n"
           "  5. Modificarea unui element\n"
           "  6. Adresa ultimului element\n"
           "  7. Lungimea listei\n"
           "  8. Interschimbarea a doua elemente\n"
           "  9. Sortarea listei\n"
           " 10. Adaugare la sfarsit\n"
           " 11. Adaugare la inceput\n"
           " 12. Inserare dupa pozitia indicata\n"
           " 13. Inserare inaintea pozitiei indicate\n"
           " 14. Stergerea elementului\n"
           " 15. Divizarea listei\n"
           " 16. Concatenarea listelor\n"
           " 17. Salvare in fisier\n"
           " 18. Citire din fisier\n"
           " 19. Eliberarea memoriei\n"
           "  0. Iesire\n"
           "============================================\n"
           "Optiunea: ");
}

int main(void) {
    Node *head = NULL, *head2 = NULL;
    int opt, pos, pos1, pos2;
    char buf[MAX_STR];

    do {
        printMenu();
        scanf("%d", &opt); while (getchar() != '\n');

        switch (opt) {
        case 1:
            if (head) printf("Lista exista deja. Eliberati memoria (opt. 19).\n");
            else head = createList();
            break;
        case 2: inputList(&head); break;
        case 3: displayList(head); break;
        case 4:
            printf("Denumirea de cautat: "); fgets(buf, MAX_STR, stdin); buf[strcspn(buf, "\n")] = '\0';
            searchByName(head, buf);
            break;
        case 5: modifyElement(head); break;
        case 6: getLastElement(head); break;
        case 7: printf("Lungimea: %d\n", getLength(head)); break;
        case 8:
            printf("Pozitia 1: "); scanf("%d", &pos1);
            printf("Pozitia 2: "); scanf("%d", &pos2); while (getchar() != '\n');
            swapElements(&head, pos1, pos2);
            break;
        case 9: sortList(&head); break;
        case 10: addElement(&head, 1); break;
        case 11: addElement(&head, 0); break;
        case 12:
            printf("Pozitia dupa care se insereaza: "); scanf("%d", &pos); while (getchar() != '\n');
            insertElement(&head, pos, 1);
            break;
        case 13:
            printf("Pozitia inaintea careia se insereaza: "); scanf("%d", &pos); while (getchar() != '\n');
            insertElement(&head, pos, 0);
            break;
        case 14:
            printf("Pozitia de sters: "); scanf("%d", &pos); while (getchar() != '\n');
            deleteElement(&head, pos);
            break;
        case 15:
            printf("Pozitia de divizare: "); scanf("%d", &pos); while (getchar() != '\n');
            if (head2) printf("Lista secundara exista deja.\n");
            else {
                splitList(head, &head, &head2, pos);
                printf("\n--- Lista 1 ---\n"); displayList(head);
                printf("\n--- Lista 2 ---\n"); displayList(head2);
            }
            break;
        case 16:
            if (!head2) printf("Nu exista lista secundara.\n");
            else { concatenateLists(&head, head2); head2 = NULL; displayList(head); }
            break;
        case 17:
            printf("Fisierul: "); fgets(buf, MAX_STR, stdin); buf[strcspn(buf, "\n")] = '\0';
            saveToFile(head, buf);
            break;
        case 18:
            printf("Fisierul: "); fgets(buf, MAX_STR, stdin); buf[strcspn(buf, "\n")] = '\0';
            loadFromFile(&head, buf);
            break;
        case 19: freeList(&head); if (head2) freeList(&head2); break;
        case 0: printf("La revedere!\n"); break;
        default: printf("Optiune invalida!\n"); break;
        }
        if (opt != 0) {
            printf("\nApasati Enter pentru a continua...");
            while (getchar() != '\n');
        }
    } while (opt != 0);

    freeList(&head);
    freeList(&head2);
    return 0;
}
