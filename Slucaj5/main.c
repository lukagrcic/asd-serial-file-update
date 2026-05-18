#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <direct.h>
#include "defs.h"
#include "util.h"
#include "adts.h"
#include "kki.h" 



void transakciona_select_sumarnu(void);

void maticna_select_arhiviranu(void);



int main(void) {

	

	prikazi_glavni_meni(5);


	//transakciona_select_sumarnu();

	//maticna_select_arhiviranu();


	return 0;
}



void transakciona_select_sumarnu(void) {
	TRANSAKCIJA t;
	FILE* tran_tek_pok = fopen(".\\ASD\\DATA\\OLD\\tran_20260126.dat", "rb");
	if (!tran_tek_pok) {
		printf("Transakciona datoteka ne postoji.\n");
		return;
	}

	printf("ID\tPromena\tKolicina\n");
	printf("-------------------------\n");

	while (fread(&t, sizeof(TRANSAKCIJA), 1, tran_tek_pok) == 1) {
		printf("%u\t%s\t%u\n", t.Id, t.Promena == 1 ? "ULAZ" : "IZLAZ", t.Kolicina);
	}
	fclose(tran_tek_pok);
}

void maticna_select_arhiviranu(void)
{
	FILE* mat_tek_pok = fopen(".\\ASD\\DATA\\OLD\\mat_20260126.dat", "rb");
	if (!mat_tek_pok) {
		printf("ERROR: Ne mogu da otvorim maticnu datoteku.\n");
		return;
	}

	PROIZVOD p;
	int brojac = 0;
	char c;

	printf("ID\tNaziv\tKolicina\n");
	printf("--------------------------\n");
	while (fread(&p, sizeof(PROIZVOD), 1, mat_tek_pok) == 1) {
		printf("%u\t%s\t%u\n", p.Id, p.Naziv, p.Kolicina);
		brojac++;

		if (brojac % 10 == 0) {
			printf("\n-- Pritisnite ENTER za nastavak --");
			while ((c = getchar()) != '\n' && c != EOF);
			getchar();
		}
	}

	fclose(mat_tek_pok);
}

