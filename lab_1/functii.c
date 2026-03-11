#include "header.h"
#define CHECK(cond, msg) do { if (!(cond)) { puts(msg); return 0; } } while (0)

int getstr(FILE *in, const char *prompt, char *dst, size_t dstsz) {
    if (prompt) puts(prompt);
    if (!fgets(dst, (int)dstsz, in)) return 0;
    dst[strcspn(dst, "\n")] = 0;
    return 1;
}

int getint(FILE *in, const char *prompt, int *x) {
    char line[64];
    if (prompt) puts(prompt);
    if (!fgets(line, sizeof(line), in)) return 0;
    *x = (int)strtol(line, NULL, 10);
    return 1;
}



void alocare(Restaurant **a, int *n) {
    if (*a) { puts("Memoria deja alocata. Elibereaza mai intai."); return; }
    int k;
    if (!getint(stdin, "Cate restaurante doriti sa alocati?", &k) || k <= 0) {
        puts("Numar invalid.");
        return;
    }
    *a = (Restaurant *)calloc((size_t)k, sizeof(Restaurant));
    if (!*a) { puts("Memorie insuficienta."); return; }
    *n = 0;
    printf("Memorie alocata pentru %d restaurante.\n", k);
}

void eliberare(Restaurant **a, int *n) {
    free(*a);
    *a = NULL;
    *n = 0;
    puts("Memorie eliberata.");
}


int read_restaurant(Restaurant *r, FILE *in) {
    int tty = (in == stdin);
    if (!getstr(in, tty ? "Denumire:" : NULL, r->denumire, sizeof(r->denumire))) return 0;
    if (!getstr(in, tty ? "Adresa:" : NULL, r->adresa, sizeof(r->adresa))) return 0;
    if (!getstr(in, tty ? "Telefon:" : NULL, r->telefon, sizeof(r->telefon))) return 0;
    if (!getstr(in, tty ? "Categoria:" : NULL, r->categoria, sizeof(r->categoria))) return 0;
    if (!getint(in, tty ? "Locuri:" : NULL, &r->locuri)) return 0;
    if (!getstr(in, tty ? "Specializarea:" : NULL, r->specializarea, sizeof(r->specializarea))) return 0;
    return 1;
}

void afisare(const Restaurant *a, int n) {
    if (!a || n <= 0) { puts("Nu sunt elemente."); return; }

    for (int i = 0; i < n; i++) {
        printf("\n--- [%d] ---\n", i + 1);
        printf("Denumire: %s\n", a[i].denumire);
        printf("Adresa: %s\n", a[i].adresa);
        printf("Telefon: %s\n", a[i].telefon);
        printf("Categoria: %s\n", a[i].categoria);
        printf("Locuri: %d\n", a[i].locuri);
        printf("Specializarea: %s\n", a[i].specializarea);
    }
}


int introducere(Restaurant **a, int *n, FILE *in) {
    int k;
    if (!getint(in, "Cate restaurante introduci?", &k) || k <= 0) {
        puts("Numar invalid.");
        return 0;
    }

    Restaurant *p = realloc(*a, (size_t)(*n + k) * sizeof(Restaurant));
    if (!p) {
        puts("Memorie insuficienta.");
        return 0;
    }
    *a = p;

    for (int i = 0; i < k; i++) {
        printf("=== Restaurant nou [%d] ===\n", i+1);
        if (!read_restaurant(&(*a)[*n], in)) {
            puts("Eroare la citire.");
            return 0;
        }
        (*n)++;
    }
    return 1;
}

int cautare(const Restaurant *a, int n, const char *denumire) {
    if (!a || !denumire) return -1;

    for (int i = 0; i < n; i++) {
        if (strcmp(a[i].denumire, denumire) == 0)
            return i;
    }
    return -1;
}

int redactare(Restaurant *a, int n, FILE *in) {
    if (!a) { puts("Tablou nealocat."); return 0; }

    char den[64];
    if (!getstr(in, "Restaurant(nume) de redactat:", den, sizeof(den))) return 0;

    int idx = cautare(a, n, den);
    if (idx < 0) {
        puts("Nu a fost gasit.");
        return 0;
    }

    puts("Element gasit. Introdu date noi:");
    if (!read_restaurant(&a[idx], in)) {
        puts("Eroare la citire.");
        return 0;
    }

    puts("Redactat cu succes.");
    return 1;
}

int adauga(Restaurant **a, int *n, int idx, FILE *in) {
    CHECK(a && n, "Parametri invalizi.");
    if (idx < 0) idx = 0;
    if (idx > *n) idx = *n;

    Restaurant *p = realloc(*a, (size_t)(*n + 1) * sizeof(Restaurant));
    CHECK(p, "Memorie insuficienta.");
    *a = p;

    for (int i = *n; i > idx; i--) (*a)[i] = (*a)[i - 1];

    puts("=== Restaurant nou ===");
    CHECK(read_restaurant(&(*a)[idx], in), "Eroare la citire.");

    (*n)++;
    puts("Adaugat cu succes.");
    return 1;
}

void interschimbare(Restaurant *a, int n, int i, int j) {
    if (!a || i < 0 || j < 0 || i >= n || j >= n) {
        puts("Indecsi invalizi.");
        return;
    }
    Restaurant tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
    puts("Interschimbare efectuata.");
}


int elimina_index(Restaurant **a, int *n, int idx) {
    CHECK(a && n && *a, "Tablou nealocat.");
    CHECK(*n > 0, "Nu sunt elemente.");
    CHECK(idx >= 0 && idx < *n, "Index invalid (1..n).");

    for (int i = idx; i < *n - 1; i++) (*a)[i] = (*a)[i + 1];
    (*n)--;

    if (*n == 0) { free(*a); *a = NULL; puts("Eliminat. Tabloul este acum gol."); return 1; }

    Restaurant *p = realloc(*a, (size_t)(*n) * sizeof(Restaurant));
    if (p) *a = p;
    puts("Eliminat cu succes.");
    return 1;
}

static int cmp_denumire(const void *pa, const void *pb) {
    const Restaurant *a = (const Restaurant*)pa;
    const Restaurant *b = (const Restaurant*)pb;
    return strcmp(a->denumire, b->denumire);
}

void sortare(Restaurant *a, int n) {
    if (!a || n <= 1) { puts("Nu sunt suficiente elemente pentru sortare."); return; }
    qsort(a, (size_t)n, sizeof(Restaurant), cmp_denumire);
    puts("Sortare dupa denumire efectuata.");
}


int salvare_fisier(const Restaurant *a, int n, const char *fis) {
    CHECK(fis && *fis, "Nume fisier invalid.");

    FILE *f = fopen(fis, "w");
    CHECK(f, "Nu pot deschide fisierul pentru scriere.");

    fprintf(f, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(f, "%s\n", a[i].denumire);
        fprintf(f, "%s\n", a[i].adresa);
        fprintf(f, "%s\n", a[i].telefon);
        fprintf(f, "%s\n", a[i].categoria);
        fprintf(f, "%d\n", a[i].locuri);
        fprintf(f, "%s\n", a[i].specializarea);
    }

    fclose(f);
    puts("Salvare OK.");
    return 1;
}

int citire_fisier(Restaurant **a, int *n, const char *fis) {
    FILE *f = fopen(fis, "r");
    if (!f) return 0;

    int m;
    if (!getint(f, NULL, &m)) { fclose(f); return 0; }

    Restaurant *p = realloc(*a, (size_t)m * sizeof(Restaurant));
    if (m > 0 && !p) { fclose(f); return 0; }
    *a = p;

    *n = 0;
    for (int i = 0; i < m; i++) {
        if (!read_restaurant(&(*a)[i], f)) break;
        (*n)++;
    }

    fclose(f);
    return 1;
}

