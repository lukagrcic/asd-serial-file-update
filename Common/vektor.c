#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"



int insert_proizvod(PROIZVOD niz[], int* n, PROIZVOD p)
{
	int i, j;

	for (i = 0; i < *n; i++) {
		if (niz[i].Id == p.Id)
			return 0; 
	}

	for (i = 0; i < *n; i++) {
		if (niz[i].Id > p.Id)
			break;
	}

	for (j = *n; j > i; j--) {
		niz[j] = niz[j - 1];
	}

	niz[i] = p;
	(*n)++;

	return 1;
}

int nadji_proizvod(PROIZVOD niz[], int n, unsigned id) {

	int i;

	for (i = 0; i < n; i++) {
		if (niz[i].Id == id) {
			return i;
		}
	}
	return -1;
}

int delete_proizvod(PROIZVOD niz[], int* n, unsigned id) {

	int i, j;

	i = nadji_proizvod(niz, *n, id);

	if (i == -1) {
		return 0;
	}

	for (j = i; j < *n - 1; j++) {
		niz[j] = niz[j + 1];
	}

	(*n)--;
	return 1;
}

int nadji_transakciju(TRANSAKCIJA niz[], int n, unsigned id) {
	for (int i = 0; i < n; i++) {
		if (niz[i].Id == id) {
			return i;
		}
	}
	return -1;
}

void sortiraj_transakcionu(TRANSAKCIJA niz[], int n) {

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (niz[i].Id > niz[j].Id) {
				TRANSAKCIJA t = niz[i];
				niz[i] = niz[j];
				niz[j] = t;
			}
		}
	}

}

void dodaj_ili_saberi(TRANSAKCIJA sum[], int* n, unsigned id, PROMENA prom, unsigned kol) {

	int index = nadji_transakciju(sum, *n, id);
	int delta = prom * (int)kol;

	if (index != -1) {
		int neto = sum[index].Promena * (int)sum[index].Kolicina + delta;

		if (neto >= 0) {
			sum[index].Promena = ULAZ;
			sum[index].Kolicina = (unsigned)neto;
		}
		else {
			sum[index].Promena = IZLAZ;
			sum[index].Kolicina = (unsigned)(-neto);
		}
	}
	else {
		sum[*n].Id = id;

		if (delta >= 0) {
			sum[*n].Promena = ULAZ;
			sum[*n].Kolicina = (unsigned)delta;
		}
		else {
			sum[*n].Promena = IZLAZ;
			sum[*n].Kolicina = (unsigned)(-delta);
		}

		(*n)++;
	}



}