#ifndef VEKTOR_H
#define VEKTOR_H
	
#include "defs.h"


int insert_proizvod(PROIZVOD niz[], int* n, PROIZVOD p);
int nadji_proizvod(PROIZVOD niz[], int n, unsigned id);
int delete_proizvod(PROIZVOD niz[], int* n, unsigned id);
int nadji_transakciju(TRANSAKCIJA niz[], int n, unsigned id);
void sortiraj_transakcionu(TRANSAKCIJA niz[], int n);
void dodaj_ili_saberi(TRANSAKCIJA sum[], int* n, unsigned id, PROMENA prom, unsigned kol);


#endif
