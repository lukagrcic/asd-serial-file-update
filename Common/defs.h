#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_PROIZVODA 500
#define MAX_TRANSAKCIJA 200


typedef struct proizvod {
    unsigned Id;
    char Naziv[15];
    unsigned Kolicina;
} PROIZVOD;

typedef enum promena {
    IZLAZ = -1,
    ULAZ = 1
} PROMENA;

typedef struct transakcija {
    unsigned Id;
    PROMENA Promena;
    unsigned Kolicina;
} TRANSAKCIJA;


extern char mat_dat[256];
extern char tran_dat[256];
extern char mat_nova[256];
extern char mat_tek[256];
extern char tran_tek[256];
extern char prom_rpt[256];
extern char err_kol_rpt[256];
extern char nov_pro_rpt[256];
extern char err_pro_rpt[256];


#endif