#include "header.h"

static void menu(void) {
    puts("\n===== MENIU =====");
    puts("1.  Alocarea dinamica a memoriei");
    puts("2.  Introducerea elementelor tabloului");
    puts("3.  Afisarea elementelor tabloului");
    puts("4.  Cautarea elementului in tablou");
    puts("5.  Modificarea campurilor unui element");
    puts("6.  Interschimbarea a doua elemente");
    puts("7.  Sortarea tabloului (dupa denumire)");
    puts("8.  Adaugarea unui element la sfarsit");
    puts("9.  Adaugarea unui element la inceput");
    puts("10. Inserarea unui element dupa elementul indicat");
    puts("11. Inserarea unui element inainte elementul indicat");
    puts("12. Stergerea elementului indicat");
    puts("13. Salvarea in fisier");
    puts("14. Citirea din fisier");
    puts("15. Eliberarea memoriei");
    puts("0.  Iesire");
}

int main(void) {
    Restaurant *a = NULL;
    int n = 0;

    int op;
    while (1) {
        menu();
        if (!getint(stdin, "Alege optiunea:", &op)) {
            puts("Eroare la citire.");
            continue;
        }

        switch (op) {
            case 1:
                alocare(&a, &n);
                break;

            case 2:
                introducere(&a, &n, stdin);
                break;

            case 3:
                afisare(a, n);
                break;

            case 4: {
                char den[64];
                if (!getstr(stdin, "Denumire cautata:", den, sizeof(den))) break;
                int idx = cautare(a, n, den);
                if (idx < 0) puts("Nu a fost gasit.");
                else printf("Gasit la index %d\n", idx + 1);
                break;
            }

            case 5:
                redactare(a, n, stdin);
                break;

            case 6: {
                int i, j;
                if (!getint(stdin, "Indexul primului element (1..n):", &i)) break;
                if (!getint(stdin, "Indexul celui de-al doilea element (1..n):", &j)) break;
                interschimbare(a, n, i - 1, j - 1);
                break;
            }

            case 7:
                sortare(a, n);
                break;

            case 8:
                adauga(&a, &n, n, stdin);
                break;

            case 9:
                adauga(&a, &n, 0, stdin);
                break;

            case 10: {
                int idx;
                if (!getint(stdin, "Dupa care element inserati (1..n):", &idx)) break;
                adauga(&a, &n, idx, stdin);
                break;
            }

            case 11: {
                int idx;
                if (!getint(stdin, "Inainte de care element inserati (1..n):", &idx)) break;
                adauga(&a, &n, idx - 1, stdin);
                break;
            }

            case 12: {
                int idx;
                if (!getint(stdin, "Index pentru eliminare (1..n):", &idx)) break;
                elimina_index(&a, &n, idx - 1);
                break;
            }

            case 13: {
                char fis[256];
                if (!getstr(stdin, "Nume fisier:", fis, sizeof(fis))) break;
                salvare_fisier(a, n, fis);
                break;
            }

            case 14: {
                char fis[256];
                if (!getstr(stdin, "Nume fisier:", fis, sizeof(fis))) break;
                if (!citire_fisier(&a, &n, fis)) puts("Eroare la citire din fisier.");
                break;
            }

            case 15:
                eliberare(&a, &n);
                break;

            case 0:
                eliberare(&a, &n);
                puts("Iesire.");
                return 0;

            default:
                puts("Optiune invalida.");
                break;
        }
    }
}
