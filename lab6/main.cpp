#include <stdio.h>
#include <stdlib.h>
#include <time.h>


long long comparatii, schimbari;


void schimba(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
    schimbari++;
}

void heapify(int *v, int n, int i) {
    int mic = i;
    int st  = 2*i + 1;
    int dr  = 2*i + 2;

    if (st < n) { comparatii++; if (v[st] < v[mic]) mic = st; }
    if (dr < n) { comparatii++; if (v[dr] < v[mic]) mic = dr; }

    if (mic != i) {
        schimba(&v[i], &v[mic]);
        heapify(v, n, mic);
    }
}

void heap_sort_desc(int *v, int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(v, n, i);

    for (int i = n - 1; i > 0; i--) {
        schimba(&v[0], &v[i]);
        heapify(v, i, 0);
    }
}


void afiseaza(int *v, int n) {
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
}

void ruleaza_test(int *v, int n, const char *eticheta) {
    comparatii = schimbari = 0;
    clock_t start = clock();
    heap_sort_desc(v, n);
    double timp = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("  %-32s | Timp: %8.4f s | Comp: %12lld | Schimb: %12lld\n",
           eticheta, timp, comparatii, schimbari);
}

void gen_random(int *v, int n) {
    for (int i = 0; i < n; i++) v[i] = rand() % 1000000;
}
void gen_crescator(int *v, int n) {
    for (int i = 0; i < n; i++) v[i] = i + 1;
}
void gen_descrescator(int *v, int n) {
    for (int i = 0; i < n; i++) v[i] = n - i;
}

int cmp_asc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void asteapta_si_curata(void) {
    printf("\n  Apasati ENTER pentru a continua...");
    fflush(stdout);
    getchar();
    getchar();
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void opt1_demo(void) {
    int n;
    printf("  Introduceti n (5-20): ");
    scanf("%d", &n);
    if (n < 5)  n = 5;
    if (n > 20) n = 20;

    int v[20];
    printf("  Introduceti %d valori intregi: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &v[i]);

    printf("  Inainte:   "); afiseaza(v, n);
    comparatii = schimbari = 0;
    clock_t t1 = clock();
    heap_sort_desc(v, n);
    double timp = (double)(clock() - t1) / CLOCKS_PER_SEC;
    printf("  Dupa:      "); afiseaza(v, n);
    printf("  Timp: %.6f s  |  Comparatii: %lld  |  Schimbari: %lld\n",
           timp, comparatii, schimbari);
}

void opt_tablouri(void (*gen)(int*, int), const char *tip) {
    int dimensiuni[] = {10000, 100000, 1000000};
    printf("\n  --- %s ---\n", tip);
    for (int s = 0; s < 3; s++) {
        int n = dimensiuni[s];
        int *v = (int*)malloc(n * sizeof(int));
        if (!v) { printf("  Memorie insuficienta!\n"); return; }
        srand(12345);          
        gen(v, n);
        char etich[50];
        sprintf(etich, "n = %7d", n);
        ruleaza_test(v, n, etich);
        free(v);
    }
}

void opt5_comparatie(void) {
    int dimensiuni[] = {10000, 100000, 1000000};
    printf("\n  --- Comparatie: HeapSort(desc) vs qsort(asc) ---\n");
    printf("  %-10s | %-10s | %-10s\n", "n", "HeapSort", "qsort");
    printf("  %s\n", "--------------------------------------");

    for (int s = 0; s < 3; s++) {
        int n = dimensiuni[s];
        int *a = (int*)malloc(n * sizeof(int));
        int *b = (int*)malloc(n * sizeof(int));
        if (!a || !b) { free(a); free(b); return; }

        srand(12345);
        gen_random(a, n);
        for (int i = 0; i < n; i++) b[i] = a[i];

        comparatii = schimbari = 0;
        clock_t t1 = clock();
        heap_sort_desc(a, n);
        double t_heap = (double)(clock() - t1) / CLOCKS_PER_SEC;

        clock_t t2 = clock();
        qsort(b, n, sizeof(int), cmp_asc);
        double t_q = (double)(clock() - t2) / CLOCKS_PER_SEC;

        printf("  n=%7d  |  HeapSort: %.4f s  |  qsort: %.4f s"
               "  |  Comp: %lld  |  Schimb: %lld\n",
               n, t_heap, t_q, comparatii, schimbari);

        free(a); free(b);
    }
}


int main(void) {
    int opt;
    do {
        printf("\n========================================\n");
        printf("  Lab 12 – Heap Sort Descendent (var.35)\n");
        printf("========================================\n");
        printf("  1. Tablou demonstrativ (5 <= n <= 20)\n");
        printf("  2. Tablou cu valori aleatorii\n");
        printf("  3. Tablou sortat crescator\n");
        printf("  4. Tablou sortat descrescator\n");
        printf("  5. Comparatie HeapSort vs qsort()\n");
        printf("  0. Iesire\n");
        printf("  Alegeti: ");
        scanf("%d", &opt);

        switch (opt) {
            case 1: opt1_demo();                                    break;
            case 2: opt_tablouri(gen_random,      "Valori random"); break;
            case 3: opt_tablouri(gen_crescator,   "Sortat crescator"); break;
            case 4: opt_tablouri(gen_descrescator,"Sortat descrescator"); break;
            case 5: opt5_comparatie();                              break;
            case 0: printf("  La revedere!\n");                    break;
            default: printf("  Optiune invalida.\n");
        }
        if (opt != 0) asteapta_si_curata();
    } while (opt != 0);

    return 0;
}
