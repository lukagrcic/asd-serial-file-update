#ifndef ADTS_H
#define ADTS_H

#include "defs.h"


int maticna_create(void);
int maticna_drop(void);
int maticna_insert(void);
int maticna_delete(void);
int maticna_update_id(void);
int maticna_update_all(int slucaj);


int transakciona_create(void);
int transakciona_drop(void);
int transakciona_insert(void);
int unos_transakcije(TRANSAKCIJA* t);


int obradi_transakcije_slucaj_jedan(PROIZVOD niz[], int* n, int slucaj);
int obradi_transakcije_slucaj_dva(PROIZVOD niz[], int* n, int slucaj);
int obradi_transakcije_slucaj_tri(PROIZVOD niz[], int* n, int slucaj);
int obradi_transakcije_slucaj_cetiri(PROIZVOD niz[], int* n, int slucaj);
int obradi_transakcije_slucaj_pet(PROIZVOD niz[], int* n, int slucaj);


int formiraj_sumiranu_transakcionu(void);
int maticna_ucitaj(PROIZVOD niz[], int max);
int maticna_upisi_novu(PROIZVOD niz[], int n);
int arhiviraj_maticnu(void);
int arhiviraj_transakcionu(TRANSAKCIJA sum[], int n);


#endif