#ifndef UTIL_H
#define UTIL_H

#include "defs.h"


void get_date(char* buf);
void izvuci_datum_str(const char* datum, char* godina, char* mesec, char* dan);
int kopiraj_fajl(const char* src, const char* dst);
int obezbedi_maticnu_iz_demo(void);
int obezbedi_transakcionu_iz_demo(int slucaj);
void postavi_putanje_izvestaja(int slucaj);
void ocisti_bafer(void);


#endif