#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct {
    char denumire[64];
    char adresa[128];
    char telefon[64];
    char categoria[64];
    int locuri;
    char specializarea[64];
}Restaurant;

int getint(FILE *in, const char *prompt, int *x);
int getstr(FILE *in, const char *prompt, char *dst, size_t dstsz);


void alocare(Restaurant **a, int *n);
void eliberare(Restaurant **a, int *n);

int  introducere(Restaurant **a, int *n, FILE *in);
int  cautare(const Restaurant *a, int n, const char *denumire);
void sortare(Restaurant *a, int n);
int  redactare(Restaurant *a, int n, FILE *in);
int  adauga(Restaurant **a, int *n, int idx, FILE *in);
int  elimina_index(Restaurant **a, int *n, int idx);
void interschimbare(Restaurant *a, int n, int i, int j);


int  salvare_fisier(const Restaurant *a, int n, const char *fis);
int  citire_fisier(Restaurant **a, int *n, const char *fis);
void afisare(const Restaurant *a, int n);

