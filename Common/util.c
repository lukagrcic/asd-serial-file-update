#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include "defs.h"
#include "util.h"
#include <string.h>
#include <stdio.h>



void get_date(char* buf)
{
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);

    strftime(buf, 9, "%Y%m%d", tm_info);
}

void postavi_putanje_izvestaja(int slucaj) {

    char datum[9];
    get_date(datum);


    sprintf(prom_rpt, ".\\ASD\\RPT\\prom_%s.rpt", datum);

    if (slucaj == 4 || slucaj == 5) {
        sprintf(err_pro_rpt, ".\\ASD\\ERR\\err_pro_%s.rpt", datum);
    }

    if (slucaj == 3 || slucaj == 5) {
        sprintf(nov_pro_rpt, ".\\ASD\\RPT\\nov_pro_%s.rpt", datum);
    }

    if (slucaj == 2 || slucaj == 5) {
        sprintf(err_kol_rpt, ".\\ASD\\ERR\\err_kol_%s.rpt", datum);
    }

}

void ocisti_bafer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void izvuci_datum_str(const char* datum, char* godina, char* mesec, char* dan)
{
    memcpy(godina, datum, 4);
    godina[4] = '\0';

    memcpy(mesec, datum + 4, 2);
    mesec[2] = '\0';

    memcpy(dan, datum + 6, 2);
    dan[2] = '\0';
}

int obezbedi_maticnu_iz_demo(void)
{
    FILE* f;

    f = fopen(".\\ASD\\DATA\\maticna.dat", "rb");
    if (f) {
        fclose(f);
        return 1;  
    }

    return kopiraj_fajl(
        ".\\ASD\\DEMO\\maticna.dat",
        ".\\ASD\\DATA\\maticna.dat"
    );
}

int kopiraj_fajl(const char* src, const char* dst)
{
    FILE* fin;
    FILE* fout;
    char buffer[4096];
    size_t n;

    fin = fopen(src, "rb");
    if (!fin) {
        perror("Ne mogu da otvorim izvorni fajl");
        return 0;
    }

    fout = fopen(dst, "wb");
    if (!fout) {
        perror("Ne mogu da otvorim odredisni fajl");
        fclose(fin);
        return 0;
    }

    while ((n = fread(buffer, 1, sizeof(buffer), fin)) > 0) {
        if (fwrite(buffer, 1, n, fout) != n) {
            perror("Greska pri upisu fajla");
            fclose(fin);
            fclose(fout);
            return 0;
        }
    }

    fclose(fin);
    fclose(fout);

    return 1;   
}

int obezbedi_transakcionu_iz_demo(int slucaj)
{
    FILE* f;
    char src[256];

    if (slucaj < 1 || slucaj > 5)
        return 0;

    f = fopen(".\\ASD\\DATA\\transakciona.dat", "rb");
    if (f) {
        fclose(f);
        return 1;
    }

    sprintf(src, ".\\ASD\\DEMO\\SLUC_%d\\transakciona.dat", slucaj);

    return kopiraj_fajl(src, ".\\ASD\\DATA\\transakciona.dat");
}


