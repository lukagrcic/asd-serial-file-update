#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "adts.h"
#include "defs.h"
#include "vektor.h"



int maticna_create(void) {

	char odgovor;

	FILE* maticna_pok = fopen(mat_dat, "rb");
	if (maticna_pok != NULL) {

		fclose(maticna_pok);

		printf("U folderu sa podacima vec postoji maticna datoteka.\n");
		printf("Da li zelite da je obrisete i kreirate novu maticnu datoteku? (D/N) ");
		scanf(" %c", &odgovor);
		ocisti_bafer();

		if (odgovor != 'D' && odgovor != 'd') {
			printf("Kreiranje maticne datoteke je ponisteno.\n");
			return 0;
		}

		if (remove(mat_dat) != 0) {
			printf("ERROR: Ne mogu da obrisem postojecu matičnu datoteku.\n");
			return 0;
		}
	}

	maticna_pok = fopen(mat_dat, "wb");
	if (!maticna_pok) {
		printf("ERROR: Ne mogu da kreiram novu maticnu datoteku.\n");
		return 0;
	}

	fclose(maticna_pok);
	printf("Nova maticna datoteka je uspesno kreirana.\n");
	return 1;
}

int maticna_drop(void) {

	FILE* maticna_pok = fopen(mat_dat, "rb");

	if (maticna_pok == NULL) {
		printf("ERROR: Maticna datoteka ne postoji.\n");
		return 0;
	}
	
	fclose(maticna_pok);

	if (remove(mat_dat) == 0) {
		printf("INFO: Maticna datoteka je obrisana.\n");
		return 1;
	}
	else {
		printf("ERROR: Maticna datoteka nije obrisana.\n");
		return 0;
	}

}

int maticna_insert(void)
{
	PROIZVOD niz[MAX_PROIZVODA];
	PROIZVOD p;
	int n;

	printf("Unesite ID proizvoda: ");
	scanf("%u", &p.Id);
	ocisti_bafer();

	printf("Unesite naziv proizvoda: ");
	scanf("%s", p.Naziv);
	ocisti_bafer();

	printf("Unesite kolicinu: ");
	scanf("%u", &p.Kolicina);
	ocisti_bafer();

	n = maticna_ucitaj(niz, MAX_PROIZVODA);

	if (!insert_proizvod(niz, &n, p)) {
		printf("ERROR: Proizvod sa tim ID vec postoji.\n");
		return 0;
	}

	maticna_upisi_novu(niz, n);
	printf("INFO: Proizvod je dodat.\n");

	return 1;
}

int maticna_delete(void) {
	unsigned id;
	int index;
	char odgovor;

	PROIZVOD niz[MAX_PROIZVODA];
	int n;


	n = maticna_ucitaj(niz, MAX_PROIZVODA);

	printf("Unesite ID proizvoda za brisanje: ");
	scanf("%u", &id);
	ocisti_bafer();

	index = nadji_proizvod(niz, n, id);
	if (index == -1) {
		printf("Proizvod sa zadatim identifikatorom ne postoji.\n");
		return 0;
	}


	printf("ID: %u\n", niz[index].Id);
	printf("Naziv: %s\n", niz[index].Naziv);
	printf("Kolicina: %u\n", niz[index].Kolicina);

	printf("Da li ste sigurni da zelite da obrisete navedeni proizvod? D(a) / N(e): ");
	scanf(" %c", &odgovor);
	ocisti_bafer();
	
	if (odgovor != 'D' && odgovor != 'd') {
		printf("Brisanje je ponisteno.\n");
		return 0;
	}

	delete_proizvod(niz, &n, id);
	maticna_upisi_novu(niz,n);

	printf("INFO: Proizvod je uspesno obrisan.\n");
	return 1;
}

int maticna_update_id(void) {

	unsigned id;
	int index;

	PROIZVOD niz[MAX_PROIZVODA];
	int n;

	n = maticna_ucitaj(niz, MAX_PROIZVODA);

	printf("Unesite ID proizvoda za azuriranje: ");
	scanf("%u", &id);
	ocisti_bafer();

	index = nadji_proizvod(niz, n, id);
	if (index == -1) {
		printf("Proizvod sa zadatim identifikatorom ne postoji.\n");
		return 0;
	}

	printf("\nTrenutni podaci:\n");
	printf("ID: %u\n", niz[index].Id);
	printf("Naziv: %s\n", niz[index].Naziv);
	printf("Kolicina: %u\n", niz[index].Kolicina);


	printf("\nUnesite novi naziv: ");
	scanf(" %15[^\n]", niz[index].Naziv);
	ocisti_bafer();

	printf("Unesite novu kolicinu: ");
	scanf("%u", &niz[index].Kolicina);
	ocisti_bafer();

	maticna_upisi_novu(niz, n);

	printf("INFO: Proizvod je uspesno azuriran.\n");
	return 1;
}

int maticna_update_all(int slucaj) {

	PROIZVOD niz[MAX_PROIZVODA];
	int n;

	if (!obezbedi_maticnu_iz_demo()) {
		printf("GRESKA: Ne postoji maticna.dat i ne moze se kopirati iz DEMO.\n");
		return 0;
	}

	if (!obezbedi_transakcionu_iz_demo(slucaj)) {
		printf("GRESKA: Ne postoji transakciona.dat za SLUC_%d.\n", slucaj);
		return 0;
	}
		
	if (!arhiviraj_maticnu()) {
		printf("GRESKA: Neuspesno arhiviranje maticne datoteke.\n");
		return 0;
	}

	if (!formiraj_sumiranu_transakcionu()) {
		printf("GRESKA: Neuspesno formiranje sumarirane transakcione.\n");
		return 0;
	}

	n = maticna_ucitaj(niz, MAX_PROIZVODA);
	if (n < 0) {
		printf("ERROR: Ne mogu da ucitam maticnu datoteku u memoriju.\n");
		return 0;
	}

	if (n == 0) {
		printf("INFO: Maticna je prazna (nema proizvoda).\n");
	}



	switch (slucaj) {
	case 1:
		if (!obradi_transakcije_slucaj_jedan(niz, &n, slucaj)) {
			printf("ERROR: Obrada transakcija nije uspesna.\n");
			return 0;
		}
		break;

	case 2:
		if (!obradi_transakcije_slucaj_dva(niz, &n, slucaj)) {
			printf("ERROR: Obrada transakcija nije uspesna.\n");
			return 0;
		}
		break;

	case 3:
		if (!obradi_transakcije_slucaj_tri(niz, &n, slucaj)) {
			printf("ERROR: Obrada transakcija nije uspesna.\n");
			return 0;
		}
		break;

	case 4:
		if (!obradi_transakcije_slucaj_cetiri(niz, &n, slucaj)) {
			printf("ERROR: Obrada transakcija nije uspesna.\n");
			return 0;
		}
		break;

	case 5:
		if (!obradi_transakcije_slucaj_pet(niz, &n, slucaj)) {
			printf("ERROR: Obrada transakcija nije uspesna.\n");
			return 0;
		}
		break;

	default:
		printf("GRESKA: Nepoznat slucaj (%d)\n", slucaj);
		break;
	}

	

	if (!maticna_upisi_novu(niz, n)) {
		return 0;
	}

	if (!transakciona_drop()) {
		return 0;
	}


	printf("Update All je uspesno zavrsen.\n\n");

	return 1;
}



int transakciona_create(void) {

	char odgovor;

	FILE* transakciona_pok = fopen(tran_dat, "rb");


	if (transakciona_pok != NULL) {

		fclose(transakciona_pok);

		printf("U folderu sa podacima vec postoji transakciona datoteka.\n");
		printf("Da li zelite da je obrisete i kreirate novu transakcionu datoteku? (D/N) ");
		scanf(" %c", &odgovor);
		ocisti_bafer();

		if (odgovor != 'D' && odgovor != 'd') {
			printf("Kreiranje transakcione datoteke prekinuto.\n");
			return 0;
		}

		if (remove(tran_dat) != 0) {
			perror("Ne mogu da obrisem postojecu transakcionu datoteku.\n");
			return 0;
		}

	}



	transakciona_pok = fopen(tran_dat, "wb");

	if (!transakciona_pok) {
		perror("Ne mogu da kreiram novu transakcionu datoteku.\n");
		return 0;
	}

	fclose(transakciona_pok);
	printf("Nova transakciona datoteka je uspesno kreirana.\n");

	return 1;
}

int transakciona_drop(void) {

	FILE* transakciona_pok = fopen(tran_dat, "rb");

	if (transakciona_pok == NULL) {
		printf("ERROR: Transakciona datoteka ne postoji.\n");
		return 0;
	}

	fclose(transakciona_pok);


	if (remove(tran_dat) != 0) {
		perror("ERROR: Тransakciona datoteka nije obrisana.\n");
		return 0;
	}


	//printf("INFO: Transakciona datoteka je obrisana.\n");
	
	return 1;
}

int transakciona_insert(void) {

	TRANSAKCIJA t;

	if (unos_transakcije(&t) == 0) {
		return 0;
	}

	FILE* transakciona_pok = fopen(tran_dat, "ab");
	if (!transakciona_pok) {
		printf("ERROR: Ne mogu da otvorim transakcionu datoteku.\n");
		return 0;
	}

	fwrite(&t, sizeof(TRANSAKCIJA), 1, transakciona_pok);
	fclose(transakciona_pok);

	printf("INFO: Transakcija je dodata.\n");
	return 1;

}

int unos_transakcije(TRANSAKCIJA* t) {

	char potvrda;

	printf("Unesite ID proizvoda:");
	scanf("%u", &t->Id);
	ocisti_bafer();

	int i = 0;

	do {

		if (i > 0) {
			printf("\nGRESKA: Morate uneti iskljucivo 1 ili -1.\n\n");
		}

		printf("Unesite promenu (1 = ULAZ, -1 = IZLAZ): ");
		scanf("%d", &t->Promena);
		ocisti_bafer();

		i++;
	} while (t->Promena != 1 && t->Promena != -1);

	printf("Unesite kolicinu: ");
	scanf("%u", &t->Kolicina);
	ocisti_bafer();



	printf("\nUneta transakcija:\n");
	printf("ID: %u\n", t->Id);
	printf("Promena: %s\n", t->Promena == ULAZ ? "ULAZ" : "IZLAZ");
	printf("Kolicina: %u\n", t->Kolicina);

	printf("\nDa li zelite da sacuvate transakciju? (D/N): ");
	scanf(" %c", &potvrda);
	ocisti_bafer();

	if (potvrda != 'D' && potvrda != 'd') {
		printf("Unos transakcije je ponisten.\n");
		return 0;
	}

	return 1;

}



int obradi_transakcije_slucaj_jedan(PROIZVOD niz[], int* n, int slucaj) {

	postavi_putanje_izvestaja(slucaj);

	FILE* promene = fopen(prom_rpt, "w");

	if (!promene) {
		printf("Greska pri otvaranju RPT fajlova\n");
		return 0;
	}

	fprintf(promene,
		"%-5s %-14s %-10s %-5s %-8s %-14s\n\n",
		"Id", "StaraKolicina", "Naziv", "Tip", "Promena", "NovaKolicina");



	TRANSAKCIJA t;
	int index;
	PROIZVOD p;

	//TREBA OTVORITI SUMARNU TRANSAKCIONU!!!
	FILE* tran_tek_pok = fopen(tran_tek, "rb");

	if (!tran_tek_pok) {
		perror("Ne mogu da otvorim transakcionu datoteku.\n");
		return 0;
	}

	//OVDE JE KLJUCNO DA POREDI SA SUMARNOM TRANSAKCIONOM!!!
	while (fread(&t, sizeof(TRANSAKCIJA), 1, tran_tek_pok)) {

		index = nadji_proizvod(niz, *n, t.Id);


		unsigned stara_kolicina = niz[index].Kolicina;

		if (t.Promena == ULAZ) {
			niz[index].Kolicina += t.Kolicina;

			fprintf(promene,
				"%-5u %-14u %-10s %-5c %-8u %-14u\n",
				niz[index].Id,
				stara_kolicina,
				niz[index].Naziv,
				(t.Promena == ULAZ ? '+' : '-'),
				t.Kolicina,
				niz[index].Kolicina
			);


		}

		if (t.Promena == IZLAZ) {
			
			niz[index].Kolicina -= t.Kolicina;

			fprintf(promene,
				"%-5u %-14u %-10s %-5c %-8u %-14u\n",
				niz[index].Id,
				stara_kolicina,
				niz[index].Naziv,
				(t.Promena == ULAZ ? '+' : '-'),
				t.Kolicina,
				niz[index].Kolicina
			);
			
		}
	}

	fclose(tran_tek_pok);

	fclose(promene);


	return 1;
}

int obradi_transakcije_slucaj_dva(PROIZVOD niz[], int* n, int slucaj) {

	postavi_putanje_izvestaja(slucaj);

	FILE* promene = fopen(prom_rpt, "w");
	FILE* err_kolicina = fopen(err_kol_rpt, "w");

	if (!promene || !err_kolicina) {
		printf("Greska pri otvaranju RPT fajlova\n");
		return 0;
	}

	fprintf(promene,
		"%-5s %-14s %-10s %-5s %-8s %-14s\n\n",
		"Id", "StaraKolicina", "Naziv", "Tip", "Promena", "NovaKolicina");

	fprintf(err_kolicina,
		"%-5s %-10s %-10s %-5s %-10s %s\n\n",
		"Id", "Kolicina", "Naziv", "Tip", "Promena", "Greska");


	TRANSAKCIJA t;
	int index;
	PROIZVOD p;

	//TREBA OTVORITI SUMARNU TRANSAKCIONU!!!
	FILE* tran_tek_pok = fopen(tran_tek, "rb");

	if (!tran_tek_pok) {
		perror("Ne mogu da otvorim transakcionu datoteku.\n");
		return 0;
	}

	//OVDE JE KLJUCNO DA POREDI SA SUMARNOM TRANSAKCIONOM!!!
	while (fread(&t, sizeof(TRANSAKCIJA), 1, tran_tek_pok)) {

		index = nadji_proizvod(niz, *n, t.Id);


		unsigned stara_kolicina = niz[index].Kolicina;

		if (t.Promena == ULAZ) {
			niz[index].Kolicina += t.Kolicina;

			fprintf(promene,
				"%-5u %-14u %-10s %-5c %-8u %-14u\n",
				niz[index].Id,
				stara_kolicina,
				niz[index].Naziv,
				(t.Promena == ULAZ ? '+' : '-'),
				t.Kolicina,
				niz[index].Kolicina
			);


		}
		else if (t.Promena == IZLAZ) {
			if (niz[index].Kolicina < t.Kolicina) {

				fprintf(err_kolicina,
					"%-5u %-10u %-10s %-5c %-10u %s\n",
					niz[index].Id,
					niz[index].Kolicina,
					niz[index].Naziv,
					'-',
					t.Kolicina,
					"Nepostojeca kolicina proizvoda."
				);
			}
			else {
				niz[index].Kolicina -= t.Kolicina;

				fprintf(promene,
					"%-5u %-14u %-10s %-5c %-8u %-14u\n",
					niz[index].Id,
					stara_kolicina,
					niz[index].Naziv,
					(t.Promena == ULAZ ? '+' : '-'),
					t.Kolicina,
					niz[index].Kolicina
				);
			}
		}
	}

	fclose(tran_tek_pok);

	fclose(promene);
	fclose(err_kolicina);


	return 1;
}

int obradi_transakcije_slucaj_tri(PROIZVOD niz[], int* n, int slucaj) {

	postavi_putanje_izvestaja(slucaj);

	FILE* promene = fopen(prom_rpt, "w");
	FILE* nov_proizvod = fopen(nov_pro_rpt, "w");

	if (!promene || !nov_proizvod) {
		printf("Greska pri otvaranju RPT fajlova\n");
		return 0;
	}

	fprintf(promene,
		"%-5s %-14s %-10s %-5s %-8s %-14s\n\n",
		"Id", "StaraKolicina", "Naziv", "Tip", "Promena", "NovaKolicina");

	fprintf(nov_proizvod,
		"%-5s %-10s %-10s\n\n",
		"Id", "Proizvod", "Kolicina");


	TRANSAKCIJA t;
	int index;
	PROIZVOD p;

	//TREBA OTVORITI SUMARNU TRANSAKCIONU!!!
	FILE* tran_tek_pok = fopen(tran_tek, "rb");

	if (!tran_tek_pok) {
		perror("Ne mogu da otvorim transakcionu datoteku.\n");
		return 0;
	}

	//OVDE JE KLJUCNO DA POREDI SA SUMARNOM TRANSAKCIONOM!!!
	while (fread(&t, sizeof(TRANSAKCIJA), 1, tran_tek_pok)) {

		index = nadji_proizvod(niz, *n, t.Id);

		if (index < 0) {

			if (t.Promena == ULAZ) {

				p.Id = t.Id;
				p.Kolicina = t.Kolicina;
				printf("Proizvod sa ID = %u je nov proizvod,\nmolim Vas unesite njegov naziv: ", p.Id);
				scanf("%s", &p.Naziv);
				printf("\n");
				ocisti_bafer();

				//sprintf(p.Naziv, "Pro_%u", p.Id);

				insert_proizvod(niz, n, p);

				fprintf(nov_proizvod,
					"%-5u %-10s %-10u\n",
					p.Id,
					p.Naziv,
					p.Kolicina
				);

			}
			
			continue;
		}

		unsigned stara_kolicina = niz[index].Kolicina;

		if (t.Promena == ULAZ) {
			niz[index].Kolicina += t.Kolicina;

			fprintf(promene,
				"%-5u %-14u %-10s %-5c %-8u %-14u\n",
				niz[index].Id,
				stara_kolicina,
				niz[index].Naziv,
				(t.Promena == ULAZ ? '+' : '-'),
				t.Kolicina,
				niz[index].Kolicina
			);

		}
		
		if (t.Promena == IZLAZ) {
			
			niz[index].Kolicina -= t.Kolicina;

			fprintf(promene,
				"%-5u %-14u %-10s %-5c %-8u %-14u\n",
				niz[index].Id,
				stara_kolicina,
				niz[index].Naziv,
				(t.Promena == ULAZ ? '+' : '-'),
				t.Kolicina,
				niz[index].Kolicina
			);
			
		}
	}

	fclose(tran_tek_pok);

	fclose(promene);
	fclose(nov_proizvod);


	return 1;
}

int obradi_transakcije_slucaj_cetiri(PROIZVOD niz[], int* n, int slucaj) {

	postavi_putanje_izvestaja(slucaj);

	FILE* promene = fopen(prom_rpt, "w");
	FILE* err_proizvod = fopen(err_pro_rpt, "w");

	if (!promene || !err_proizvod) {
		printf("Greska pri otvaranju RPT fajlova\n");
		return 0;
	}

	fprintf(promene,
		"%-5s %-14s %-10s %-5s %-8s %-14s\n\n",
		"Id", "StaraKolicina", "Naziv", "Tip", "Promena", "NovaKolicina");

	fprintf(err_proizvod,
		"%-5s %-10s %-10s %-5s %-10s %s\n\n",
		"Id", "Kolicina", "Naziv", "Tip", "Promena", "Greska");



	TRANSAKCIJA t;
	int index;
	PROIZVOD p;

	//TREBA OTVORITI SUMARNU TRANSAKCIONU!!!
	FILE* tran_tek_pok = fopen(tran_tek, "rb");

	if (!tran_tek_pok) {
		perror("Ne mogu da otvorim transakcionu datoteku.\n");
		return 0;
	}

	//OVDE JE KLJUCNO DA POREDI SA SUMARNOM TRANSAKCIONOM!!!
	while (fread(&t, sizeof(TRANSAKCIJA), 1, tran_tek_pok)) {

		index = nadji_proizvod(niz, *n, t.Id);

		if (index < 0) {

			if (t.Promena == IZLAZ) {

				fprintf(err_proizvod,
					"%-5u %-10s %-10s %-5c %-10u %s\n",
					t.Id,
					"X",
					"X",
					'-',
					t.Kolicina,
					"Nepostojeci proizvod."
				);

			}
			
			continue;
		}

		unsigned stara_kolicina = niz[index].Kolicina;

		if (t.Promena == ULAZ) {
			niz[index].Kolicina += t.Kolicina;

			fprintf(promene,
				"%-5u %-14u %-10s %-5c %-8u %-14u\n",
				niz[index].Id,
				stara_kolicina,
				niz[index].Naziv,
				(t.Promena == ULAZ ? '+' : '-'),
				t.Kolicina,
				niz[index].Kolicina
			);


		}

		if (t.Promena == IZLAZ) {
			
			niz[index].Kolicina -= t.Kolicina;

			fprintf(promene,
				"%-5u %-14u %-10s %-5c %-8u %-14u\n",
				niz[index].Id,
				stara_kolicina,
				niz[index].Naziv,
				(t.Promena == ULAZ ? '+' : '-'),
				t.Kolicina,
				niz[index].Kolicina
			);
			
		}
	}

	fclose(tran_tek_pok);

	fclose(promene);
	fclose(err_proizvod);


	return 1;
}

int obradi_transakcije_slucaj_pet(PROIZVOD niz[], int* n, int slucaj) {
	
	postavi_putanje_izvestaja(slucaj);

	FILE* promene = fopen(prom_rpt, "w");
	FILE* err_kolicina = fopen(err_kol_rpt, "w");
	FILE* nov_proizvod = fopen(nov_pro_rpt, "w");
	FILE* err_proizvod = fopen(err_pro_rpt, "w");

	if (!promene || !err_kolicina || !nov_proizvod || !err_proizvod) {
		printf("Greska pri otvaranju RPT fajlova\n");
		return 0;
	}

	fprintf(promene,
		"%-5s %-14s %-10s %-5s %-8s %-14s\n\n",
		"Id", "StaraKolicina", "Naziv", "Tip", "Promena", "NovaKolicina");

	fprintf(err_kolicina,
		"%-5s %-10s %-10s %-5s %-10s %s\n\n",
		"Id", "Kolicina", "Naziv", "Tip", "Promena", "Greska");

	fprintf(nov_proizvod,
		"%-5s %-10s %-10s\n\n",
		"Id", "Proizvod", "Kolicina");

	fprintf(err_proizvod,
		"%-5s %-10s %-10s %-5s %-10s %s\n\n",
		"Id", "Kolicina", "Naziv", "Tip", "Promena", "Greska");


	
	TRANSAKCIJA t;
	int index;
	PROIZVOD p;

	//TREBA OTVORITI SUMARNU TRANSAKCIONU!!!
	FILE* tran_tek_pok = fopen(tran_tek, "rb");

	if (!tran_tek_pok) {
		perror("Ne mogu da otvorim transakcionu datoteku.\n");
		return 0;
	}

	//OVDE JE KLJUCNO DA POREDI SA SUMARNOM TRANSAKCIONOM!!!
	while (fread(&t, sizeof(TRANSAKCIJA), 1, tran_tek_pok)) {

		index = nadji_proizvod(niz, *n, t.Id);

		if (index < 0) {

			if (t.Promena == ULAZ) {

				p.Id = t.Id;
				p.Kolicina = t.Kolicina;
				printf("Proizvod sa ID = %u je nov proizvod,\nmolim Vas unesite njegov naziv: ", p.Id);
				scanf("%s", &p.Naziv);
				printf("\n");
				ocisti_bafer();

				//sprintf(p.Naziv, "Pro_%u", p.Id);

				insert_proizvod(niz, n, p);

				fprintf(nov_proizvod,
					"%-5u %-10s %-10u\n",
					p.Id,       
					p.Naziv,  
					p.Kolicina   
				);

			}
			else {

				fprintf(err_proizvod,
					"%-5u %-10s %-10s %-5c %-10u %s\n",
					t.Id,                 
					"X",                
					"X",                  
					'-',                  
					t.Kolicina,           
					"Nepostojeci proizvod."
				);

			}
			continue;
		}

		unsigned stara_kolicina = niz[index].Kolicina;

		if (t.Promena == ULAZ) {
			niz[index].Kolicina += t.Kolicina;

			fprintf(promene,
				"%-5u %-14u %-10s %-5c %-8u %-14u\n",
				niz[index].Id,              
				stara_kolicina,             
				niz[index].Naziv,           
				(t.Promena == ULAZ ? '+' : '-'), 
				t.Kolicina,                 
				niz[index].Kolicina         
			);


		}
		else if (t.Promena == IZLAZ) {
			if (niz[index].Kolicina < t.Kolicina) {

				fprintf(err_kolicina,
					"%-5u %-10u %-10s %-5c %-10u %s\n",
					niz[index].Id,                 
					niz[index].Kolicina,           
					niz[index].Naziv,              
					'-',                            
					t.Kolicina,                    
					"Nepostojeca kolicina proizvoda."
				);
			}
			else {
				niz[index].Kolicina -= t.Kolicina;

				fprintf(promene,
					"%-5u %-14u %-10s %-5c %-8u %-14u\n",
					niz[index].Id,
					stara_kolicina,
					niz[index].Naziv,
					(t.Promena == ULAZ ? '+' : '-'),
					t.Kolicina,
					niz[index].Kolicina
				);
			}
		}
	}

	fclose(tran_tek_pok);

	fclose(promene);
	fclose(err_kolicina);
	fclose(nov_proizvod);
	fclose(err_proizvod);


	return 1;
}



int formiraj_sumiranu_transakcionu(void) {
	TRANSAKCIJA t;
	TRANSAKCIJA sum[MAX_TRANSAKCIJA];
	int n_sum = 0;

	FILE* transakciona_pok = fopen(tran_dat, "rb");
	if (!transakciona_pok) {
		printf("ERROR: Ne mogu da otvorim transakcionu datoteku.\n");
		return 0;
	}

	while (fread(&t, sizeof(TRANSAKCIJA), 1, transakciona_pok) == 1) {
		dodaj_ili_saberi(sum, &n_sum, t.Id, t.Promena, t.Kolicina);
	}

	fclose(transakciona_pok);

	sortiraj_transakcionu(sum, n_sum);

	arhiviraj_transakcionu(sum, n_sum);

	return 1;
}

int maticna_ucitaj(PROIZVOD niz[], int max) {

	int n = 0;

	FILE* maticna_pok = fopen(mat_dat, "rb");
	if (!maticna_pok) {
		//perror("Ne mogu da otvorim maticnu datoteku.\n");
		return -1;
	}

	while (n < max && fread(&niz[n], sizeof(PROIZVOD), 1, maticna_pok) == 1) {
		n++;
	}

	fclose(maticna_pok);
	return n;
}

int maticna_upisi_novu(PROIZVOD niz[], int n) {
	FILE* mat_nova_pok = fopen(mat_nova, "wb");
	if (!mat_nova_pok) {
		perror("Ne mogu da otvorim novu maticnu datoteku.\n");
		return 0;
	}

	for (int i = 0; i < n; i++) {
		fwrite(&niz[i], sizeof(PROIZVOD), 1, mat_nova_pok);
	}

	fclose(mat_nova_pok);
	return 1;
}

int arhiviraj_maticnu(void) {
	PROIZVOD niz[MAX_PROIZVODA];
	int n;

	char datum[9];

	get_date(datum);

	sprintf(mat_tek,
		".\\ASD\\DATA\\OLD\\mat_%s.dat",
		datum);

	n = maticna_ucitaj(niz, MAX_PROIZVODA);

	FILE* mat_tek_pok = fopen(mat_tek, "wb");
	if (!mat_tek_pok) {
		//perror("ERROR: Ne mogu da kreiram sumarnu transakcionu datoteku");
		return 0;
	}


	fwrite(niz, sizeof(PROIZVOD), n, mat_tek_pok);

	fclose(mat_tek_pok);
	return 1;
}

int arhiviraj_transakcionu(TRANSAKCIJA sum[], int n) {
	char datum[9];

	get_date(datum);

	sprintf(tran_tek,
		".\\ASD\\DATA\\OLD\\tran_%s.dat",
		datum);

	FILE* tran_tek_pok = fopen(tran_tek, "wb");
	if (!tran_tek_pok) {
		perror("ERROR: Ne mogu da kreiram sumarnu transakcionu datoteku.\n");
		return 0;
	}

	fwrite(sum, sizeof(TRANSAKCIJA), n, tran_tek_pok);

	fclose(tran_tek_pok);
	return 1;
}