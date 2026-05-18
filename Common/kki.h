#ifndef KKI_H
#define KKI_H

#include "defs.h"


void prikazi_glavni_meni(int slucaj);


void prikazi_transakcije_meni(void);
void prikazi_maticna_meni(int slucaj);
void prikazi_pomoc_meni(void);
void prikazi_demo_meni(void);
void prikazi_izvestaje(int slucaj);


void maticna_select_all(void);
void maticna_select_id(void);
void transakciona_select_all(void);
void transakciona_select_id(void);


void prikazi_rpt_fajl(const char* putanja);


void demo_prvi_slucaj(void);
void demo_drugi_slucaj(void);
void demo_treci_slucaj(void);
void demo_cetvrti_slucaj(void);
void demo_peti_slucaj(void);


void pomoc_o_transakcionoj_datoteci(void);
void pomoc_o_maticnoj_datoteci(void);
void pomoc_o_azuriranju(void);
void pomoc_o_nama(void);


int ucitaj_ceo_broj(const char* poruka);
void cekaj_enter(void);
void ocisti_ekran(void);
void prikazi_poruku(const char* poruka, int je_greska);
void nova_strana(void);


#endif