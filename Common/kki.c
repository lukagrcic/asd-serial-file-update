#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "kki.h"
#include "defs.h"
#include "adts.h"
#include "util.h"
#include "vektor.h"



void prikazi_glavni_meni(int slucaj) {
    int izbor;


    char datum[9];
    char g[5], m[3], d[3];

    get_date(datum);
    izvuci_datum_str(datum, g, m, d);

    do {
        ocisti_ekran();
        printf("***********************************************\n");
        printf("* Aplikacija: ASD                             \n");
        printf("* Opis      : Azuriranje serijske datoteke     \n");
        printf("* Verzija   : 1.0                              \n");
        printf("* Upotreba  : asd.exe [-d[1|2|3|4|5]]          \n");
        printf("                %d - demo za %d. slucaj azuriranja \n", slucaj, slucaj);
        printf("* Datum     : %s.%s.%s                    \n", d, m, g);
        printf("* Autor     : Luka Grcic                        \n");
        printf("* Mentor    : Sasa D. Lazarevic, slazar@fon.rs    \n");
        printf("***********************************************\n");
        printf("\n===========================\n");
        printf("        GLAVNI MENI         \n");
        printf("===========================\n\n");

        printf("0. Kraj rada\n\n");
        printf("1. Rad sa transakcionom datotekom\n");
        printf("2. Rad sa maticnom datotekom\n");
        printf("3. Pomoc\n");
        printf("\n===========================\n");
        printf("Izbor: ");

        izbor = ucitaj_ceo_broj("");

        switch (izbor) {
        case 0:
            printf("\nHvala sto ste koristili ASD aplikaciju!\n");
            break;
        case 1:
            prikazi_transakcije_meni();
            break;
        case 2:
            prikazi_maticna_meni(slucaj);
            break;
        case 3:
            prikazi_pomoc_meni();
            break;
        default:
            prikazi_poruku("Nevalidan izbor. Pokusajte ponovo.", 1);
            cekaj_enter();
        }
    } while (izbor != 0);
}



void prikazi_transakcije_meni(void) {
    int izbor;

    do {
        ocisti_ekran();
        printf("======================================================\n");
        printf("  MENI Transakciona datoteka\n");
        printf("======================================================\n\n");

        printf("0. Povratak\n\n");
        printf("1. Create     ::- Kreiranje nove transakcione datoteke\n");
        printf("2. Drop       ::- Unistavanje postojece transakcione datoteke\n");
        printf("3. Insert     ::- Dodavanje nove transakcije\n");
        printf("4. Select All ::- Prikazivanje svih transakcija\n");
        printf("5. Select Id  ::- Prikazivanje transakcija jednog proizvoda\n");
        printf("\nIzbor: ");

        izbor = ucitaj_ceo_broj("");

        switch (izbor) {
        case 0:
            break;
        case 1:
            transakciona_create();
            cekaj_enter();
            break;
        case 2:
            if (transakciona_drop() == 1) {
                printf("INFO: Transakciona datoteka je obrisana.\n");
            };
            cekaj_enter();
            break;
        case 3:
            transakciona_insert();
            cekaj_enter();
            break;
        case 4:
            transakciona_select_all();
            cekaj_enter();
            break;
        case 5:
            transakciona_select_id();
            cekaj_enter();
            break;
        default:
            prikazi_poruku("Nevalidan izbor. Pokusajte ponovo.", 1);
            cekaj_enter();
        }
    } while (izbor != 0);
}

void prikazi_maticna_meni(int slucaj) {
    int izbor;


    do {
        ocisti_ekran();
        printf("======================================================\n");
        printf("    MENI Maticna datoteka  \n");
        printf("======================================================\n\n");

        printf("0. Povratak\n\n");
        printf("1. Create     ::- Kreiranje nove maticne datoteke\n");
        printf("2. Drop       ::- Unistavanje postojece maticne datoteke\n");
        printf("3. Insert     ::- Dodavanje novog proizvoda\n");
        printf("4. Delete     ::- Brisanje postojeceg proizvoda\n");
        printf("5. Update All ::- Azuriranje maticne datoteke\n");
        printf("6. Update Id  ::- Azuriranje jednog proizvoda\n");
        printf("7. Select All ::- Prikazivanje svih proizvoda\n");
        printf("8. Select Id  ::- Prikazivanje jednog proizvoda\n");
        printf("\nIzbor: ");

        izbor = ucitaj_ceo_broj("");

        switch (izbor) {
        case 0:
            break;
        case 1:
            maticna_create();
            cekaj_enter();
            break;
        case 2:
            maticna_drop();
            cekaj_enter();
            break;
        case 3:
            maticna_insert();
            cekaj_enter();
            break;
        case 4:
            maticna_delete();
            cekaj_enter();
            break;
        case 5:
            
            if (maticna_update_all(slucaj) == 0) {
                printf("Update All nije izvrsen.\n");
                cekaj_enter();
                break;
            }

            printf("Sledi prikaz izvestaja o azuriranju.\n");
            cekaj_enter();
            prikazi_izvestaje(slucaj);
            break;
            
        case 6:
            maticna_update_id();
            cekaj_enter();
            break;
        case 7:
            maticna_select_all();
            cekaj_enter();
            break;
        case 8:
            maticna_select_id();
            cekaj_enter();
            break;
        default:
            prikazi_poruku("Nevalidan izbor. Pokusajte ponovo.", 1);
            cekaj_enter();
        }
    } while (izbor != 0);
}
    
void prikazi_pomoc_meni(void) {
    int izbor;

    do {
        ocisti_ekran();
        printf("===========================\n");
        printf("        MENI Pomoc         \n");
        printf("===========================\n\n");

        printf("0. Povratak\n\n");
        printf("1. O azuriranju serijske datoteke\n");
        printf("2. Uputstvo za rad sa transakcionom datotekom\n");
        printf("3. Uputstvo za rad sa maticnom datotekom\n");
        printf("4. Demo\n");
        printf("5. O nama\n");
        printf("\nIzbor: ");

        izbor = ucitaj_ceo_broj("");

        switch (izbor) {
        case 0:
            break;
        case 1:
            ocisti_ekran();
            pomoc_o_azuriranju();
            cekaj_enter();
            break;
        case 2:
            ocisti_ekran();
            pomoc_o_transakcionoj_datoteci();
            cekaj_enter();
            break;
        case 3:
            ocisti_ekran();
            pomoc_o_maticnoj_datoteci();
            cekaj_enter();
            break;
        case 4:
            prikazi_demo_meni();
            break;
        case 5:
            ocisti_ekran();
            pomoc_o_nama();
            cekaj_enter();
            break;
        default:
            prikazi_poruku("Nevalidan izbor. Pokusajte ponovo.", 1);
            cekaj_enter();
        }
    } while (izbor != 0);
}

void prikazi_demo_meni(void) {
    int izbor;

    do {
        ocisti_ekran();
        printf("===========================\n");
        printf("        MENI Demo          \n");
        printf("===========================\n\n");

        printf("0. Povratak\n\n");
        printf("1. Osnovni slucaj\n");
        printf("2. Nepostojeca kolicina\n");
        printf("3. Nov proizvod\n");
        printf("4. Nepostojeci proizvod\n");
        printf("5. Sveobuhvatni slucaj\n");
        printf("\nIzbor: ");

        izbor = ucitaj_ceo_broj("");

        switch (izbor) {
        case 0:
            break;
        case 1:
            ocisti_ekran();
            demo_prvi_slucaj();
            cekaj_enter();
            break;
        case 2:
            ocisti_ekran();
            demo_drugi_slucaj();
            cekaj_enter();
            break;
        case 3:
            ocisti_ekran();
            demo_treci_slucaj();
            cekaj_enter();
            break;
        case 4:
            ocisti_ekran();
            demo_cetvrti_slucaj();
            cekaj_enter();
            break;
        case 5:
            ocisti_ekran();
            demo_peti_slucaj();
            cekaj_enter();
            break;
        default:
            prikazi_poruku("Nevalidan izbor. Pokusajte ponovo.", 1);
            cekaj_enter();
        }
    } while (izbor != 0);
}

void prikazi_izvestaje(int slucaj) {

    ocisti_ekran();
    prikazi_rpt_fajl(prom_rpt);

    ocisti_ekran();
    if (slucaj == 4 || slucaj == 5) {
        prikazi_rpt_fajl(err_pro_rpt);
    }

    ocisti_ekran();
    if (slucaj == 3 || slucaj == 5) {
        prikazi_rpt_fajl(nov_pro_rpt);
    }

    ocisti_ekran();
    if (slucaj == 2 || slucaj == 5) {
        prikazi_rpt_fajl(err_kol_rpt);
    }

}



void maticna_select_all(void)
{
    FILE* maticna_pok = fopen(mat_dat, "rb");
    if (!maticna_pok) {
        printf("ERROR: Ne mogu da otvorim maticnu datoteku.\n");
        return;
    }

    PROIZVOD p;
    int brojac = 0;
    char c;

    system("cls");

    printf("ID\tNaziv\tKolicina\n");
    printf("--------------------------\n");
    while (fread(&p, sizeof(PROIZVOD), 1, maticna_pok) == 1) {
        printf("%u\t%s\t%u\n", p.Id, p.Naziv, p.Kolicina);
        brojac++;

        if (brojac % 10 == 0) {
            printf("\n-- Pritisnite ENTER za nastavak --\n");
            fflush(stdout);
            while ((c = getchar()) != '\n' && c != EOF);

            system("cls");
            printf("ID\tNaziv\tKolicina\n");
            printf("--------------------------\n");
        }

    }

    fclose(maticna_pok);
}

void maticna_select_id(void) {
    unsigned id;
    PROIZVOD p;
    int pronadjen = 0;

    printf("Unesite ID proizvoda: ");
    scanf("%u", &id);
    ocisti_bafer();

    FILE* maticna_pok = fopen(mat_dat, "rb");
    if (!maticna_pok) {
        printf("ERROR: Ne mogu da otvorim maticnu datoteku.\n");
        return;
    }


    while (fread(&p, sizeof(PROIZVOD), 1, maticna_pok) == 1) {
        if (p.Id == id) {
            printf("ID: %u\n", p.Id);
            printf("Naziv: %s\n", p.Naziv);
            printf("Kolicina: %u\n", p.Kolicina);

            pronadjen = 1;
            break;
        }
    }

    if (!pronadjen) {
        printf("Ne postoji proizvod sa ID=%u.\n", id);
    }

    fclose(maticna_pok);
}

void transakciona_select_all(void) {
    TRANSAKCIJA t;
    FILE* transakciona_pok = fopen(tran_dat, "rb");
    if (!transakciona_pok) {
        printf("Transakciona datoteka ne postoji.\n");
        return;
    }

    printf("ID\tPromena\tKolicina\n");
    printf("-------------------------\n");

    while (fread(&t, sizeof(TRANSAKCIJA), 1, transakciona_pok) == 1) {
        printf("%u\t%s\t%u\n", t.Id, t.Promena == 1 ? "ULAZ" : "IZLAZ", t.Kolicina);
    }
    fclose(transakciona_pok);
}

void transakciona_select_id(void) {
    unsigned id;
    TRANSAKCIJA t;
    int pronadjen = 0;

    printf("Unesite ID proizvoda: ");
    scanf("%u", &id);
    printf("\n");
    ocisti_bafer();

    FILE* transakciona_pok = fopen(tran_dat, "rb");
    if (!transakciona_pok) {
        printf("GRESKA: Ne mogu da otvorim transakcionu datoteku.\n");
        return;
    }

    printf("Transakcije za proizvod ID=%u:\n\n", id);
    printf("Promena\tKolicina\n");
    printf("-----------------\n");


    while (fread(&t, sizeof(TRANSAKCIJA), 1, transakciona_pok) == 1) {
        if (t.Id == id) {
            printf("%s\t%u\n", t.Promena == ULAZ ? "ULAZ" : "IZLAZ", t.Kolicina);
            pronadjen = 1;
        }
    }

    if (!pronadjen) {
        printf("Ne postoje transakcije za proizvod sa ID=%u.\n", id);
    }

    fclose(transakciona_pok);
}



void prikazi_rpt_fajl(const char* putanja)
{
    FILE* f;
    char linija[256];

    f = fopen(putanja, "r");
    if (!f) {
        return;
    }

    printf("\n===== %s =====\n\n", putanja);

    while (fgets(linija, sizeof(linija), f)) {
        printf("%s", linija);
    }

    fclose(f);

    printf("\n--- Pritisnite ENTER za nastavak ---");
    getchar();
}



void demo_prvi_slucaj(void)
{


    printf("============================================================\n");
    printf("DEMO - OSNOVNI SLUCAJ AZURIRANJA SERIJSKE DATOTEKE\n");
    printf("============================================================\n\n");

    printf("Ovo je osnovni (prvi) slucaj azuriranja.\n");
    printf("Azurira se proizvod koji POSTOJI u maticnoj datoteci,\n");
    printf("a sve promene kolicina su ODGOVARAJUCE.\n\n");

    printf("Moguci scenariji:\n");
    printf(" - Postojeci proizvod + ULAZ  -> uspesno azuriranje\n");
    printf(" - Postojeci proizvod + IZLAZ -> uspesno azuriranje\n\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("STARA MATICNA DATOTEKA (maticna.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Naziv    Kolicina\n");
    printf("20   Pro_20   100\n");
    printf("30   Pro_30   150\n");
    printf("40   Pro_40   200\n");
    printf("50   Pro_50   250\n");
    printf("60   Pro_60   300\n");
    printf("70   Pro_70   350\n");
    printf("80   Pro_80   400\n");
    printf("90   Pro_90   450\n\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("TRANSAKCIONA DATOTEKA - HRONOLOSKI ZAPIS (transakciona.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Promena   Kolicina\n");
    printf("60   ULAZ       150\n");
    printf("40   ULAZ        80\n");
    printf("60   ULAZ        50\n");
    printf("60   IZLAZ      100\n");
    printf("40   IZLAZ       50\n");
    printf("60   IZLAZ      150\n");
    printf("60   ULAZ       200\n");
    printf("40   IZLAZ       80\n");
    printf("60   ULAZ        20\n");
    printf("60   IZLAZ      120\n");
    printf("40   ULAZ       100\n");
    printf("60   IZLAZ      100\n");
    printf("70   ULAZ        50\n");
    printf("70   IZLAZ       50\n\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("SUMARNA TRANSAKCIONA DATOTEKA (tran_210429.dat)\n");
    printf("(sabrane i sortirane dnevne promene)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Promena   Kolicina\n");
    printf("40   ULAZ        50\n");
    printf("60   IZLAZ       50\n");
    printf("70   ULAZ         0\n\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("OBJASNJENJE PROMENA\n");
    printf("------------------------------------------------------------\n");
    printf("Id 40 : 200 + 50 = 250\n");
    printf("Id 60 : 300 - 50 = 250\n");
    printf("Id 70 : 350 +  0 = 350\n\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("NOVA MATICNA DATOTEKA (maticna.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Naziv    Kolicina\n");
    printf("20   Pro_20   100\n");
    printf("30   Pro_30   150\n");
    printf("40   Pro_40   250\n");
    printf("50   Pro_50   250\n");
    printf("60   Pro_60   250\n");
    printf("70   Pro_70   350\n");
    printf("80   Pro_80   400\n");
    printf("90   Pro_90   450\n\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("IZVESTAJ O PROMENAMA (prom_210429.rpt)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   StaraKol  Naziv      Tip     Promena  NovaKol\n");
    printf("40   200       Pro_40     +       50       250\n");
    printf("60   300       Pro_60     -       50       250\n");
    printf("70   350       Pro_70     +       0        350\n\n");

    nova_strana();

    printf("Zakljucak:\n");
    printf(" - Sve promene su uspesno obradjene\n");
    printf(" - Nema gresaka\n");
    printf(" - Ne kreiraju se error izvestaji\n\n");

}

void demo_drugi_slucaj(void)
{
    printf("============================================================\n");
    printf("DEMO - DRUGI SLUCAJ: NEPOSTOJECA KOLICINA (err_kol)\n");
    printf("============================================================\n\n");

    printf("Azurira se proizvod koji POSTOJI u maticnoj datoteci,\n");
    printf("ali se moze desiti IZLAZ nepostojece kolicine.\n\n");

    printf("Moguci ishodi:\n");
    printf(" - Postojeci proizvod + ULAZ  -> uspesno azuriranje\n");
    printf(" - Postojeci proizvod + IZLAZ (manje od raspolozive) -> uspesno\n");
    printf(" - Postojeci proizvod + IZLAZ (nije manje / vece ili jednako) -> GRESKA\n");
    printf("   Operacija se odbija i upisuje se u err_kol_*.rpt\n\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("STARA MATICNA DATOTEKA (maticna.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Naziv    Kolicina\n");
    printf("20   Pro_20   100\n");
    printf("30   Pro_30   150\n");
    printf("40   Pro_40   200\n");
    printf("50   Pro_50   250\n");
    printf("60   Pro_60   300\n");
    printf("70   Pro_70   350\n");
    printf("80   Pro_80   400\n");
    printf("90   Pro_90   450\n\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("TRANSAKCIONA DATOTEKA - HRONOLOSKI ZAPIS (transakciona.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Promena   Kolicina\n");
    printf("80   IZLAZ       50\n");
    printf("70   IZLAZ      400\n");
    printf("80   ULAZ       100\n");
    printf("90   IZLAZ      800\n");
    printf("60   IZLAZ      500\n");
    printf("20   IZLAZ      500\n");
    printf("30   ULAZ       100\n");
    printf("20   IZLAZ      300\n");
    printf("60   IZLAZ      300\n");
    printf("40   ULAZ       150\n");
    printf("50   IZLAZ      200\n");
    printf("40   IZLAZ      100\n");
    printf("50   IZLAZ      300\n");
    printf("50   IZLAZ      300\n");
    printf("30   IZLAZ       50\n");
    printf("90   ULAZ       800\n");
    printf("70   ULAZ       200\n\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("SUMARNA I SORTIRANA TRANSAKCIONA (tran_210429.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Promena   Kolicina\n");
    printf("20   IZLAZ      800\n");
    printf("30   ULAZ        50\n");
    printf("40   ULAZ        50\n");
    printf("50   IZLAZ      800\n");
    printf("60   IZLAZ      800\n");
    printf("70   IZLAZ      200\n");
    printf("80   ULAZ        50\n");
    printf("90   ULAZ         0\n\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("OBJASNJENJE (sta prolazi, a sta je greska)\n");
    printf("------------------------------------------------------------\n");
    printf("USPEH:\n");
    printf("Id 30 : 150 +  50 = 200\n");
    printf("Id 40 : 200 +  50 = 250\n");
    printf("Id 70 : 350 - 200 = 150  (izlaz je manji od raspolozive)\n");
    printf("Id 80 : 400 +  50 = 450\n");
    printf("Id 90 : 450 +   0 = 450\n\n");

    printf("GRESKA (nepostojece kolicine):\n");
    printf("Id 20 : pokusaj 100 - 800 -> ODBIJENO (upis u err_kol)\n");
    printf("Id 50 : pokusaj 250 - 800 -> ODBIJENO (upis u err_kol)\n");
    printf("Id 60 : pokusaj 300 - 800 -> ODBIJENO (upis u err_kol)\n\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("NOVA MATICNA DATOTEKA (maticna.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Naziv    Kolicina\n");
    printf("20   Pro_20   100\n");
    printf("30   Pro_30   200\n");
    printf("40   Pro_40   250\n");
    printf("50   Pro_50   250\n");
    printf("60   Pro_60   300\n");
    printf("70   Pro_70   150\n");
    printf("80   Pro_80   450\n");
    printf("90   Pro_90   450\n\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("IZVESTAJ O PROMENAMA (prom_210429.rpt)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   StaraKol  Naziv    Tip     Promena  NovaKol\n");
    printf("30   150       Pro_30   +       50       200\n");
    printf("40   200       Pro_40   +       50       250\n");
    printf("70   350       Pro_70   -       200      150\n");
    printf("80   400       Pro_80   +       50       450\n");
    printf("90   450       Pro_90   +       0        450\n\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("IZVESTAJ O GRESKAMA (err_kol_210429.rpt)\n");
    printf("------------------------------------------------------------\n");
    printf("Id      Kolicina   Naziv        Tip   Promena   Greska \n");
    printf("20      100        Pro_20       -     800       Nepostojeca kolicina proizvoda.\n");
    printf("50      250        Pro_50       -     800       Nepostojeca kolicina proizvoda.\n");
    printf("60      300        Pro_60       -     800       Nepostojeca kolicina proizvoda.\n\n");

    nova_strana();

    printf("Zakljucak:\n");
    printf(" - Uspesne promene su upisane u prom_*.rpt\n");
    printf(" - Neuspesne (nepostojece kolicine) su upisane u err_kol_*.rpt\n");
    printf(" - Za proizvode sa greskom, kolicina u maticnoj ostaje nepromenjena\n\n");
}

void demo_treci_slucaj(void)
{
    ocisti_ekran();

    printf("============================================================\n");
    printf("DEMO - TRECI SLUCAJ: NOV PROIZVOD (nov_pro)\n");
    printf("============================================================\n\n");

    printf("Azurira se maticna datoteka, uz mogucnost da se desi:\n");
    printf(" - ULAZ kolicine za proizvod koji NE POSTOJI u maticnoj.\n");
    printf("Tada se taj proizvod DODAJE u novu maticnu datoteku,\n");
    printf("a upis ide i u izvestaj nov_pro_*.rpt.\n\n");

    printf("Moguci scenariji:\n");
    printf(" - Postojeci proizvod + ULAZ  -> uspesno\n");
    printf(" - Postojeci proizvod + IZLAZ -> uspesno (ako je kolicina ok)\n");
    printf(" - Nepostojeci proizvod + ULAZ -> dodaje se novi proizvod (uspesno)\n\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("STARA MATICNA DATOTEKA (maticna.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Naziv    Kolicina\n");
    printf("20   Pro_20   100\n");
    printf("30   Pro_30   150\n");
    printf("40   Pro_40   200\n");
    printf("50   Pro_50   250\n");
    printf("60   Pro_60   300\n");
    printf("70   Pro_70   350\n");
    printf("80   Pro_80   400\n");
    printf("90   Pro_90   450\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("TRANSAKCIONA DATOTEKA - HRONOLOSKI ZAPIS (transakciona.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Promena   Kolicina\n");
    printf("55   ULAZ       205\n");
    printf("95   ULAZ       295\n");
    printf("55   ULAZ        50\n");
    printf("45   ULAZ       245\n");
    printf("95   IZLAZ       15\n");
    printf("15   ULAZ       230\n");
    printf("10   ULAZ       190\n");
    printf("20   IZLAZ      100\n");
    printf("30   IZLAZ       50\n");
    printf("20   ULAZ        50\n");
    printf("35   ULAZ       285\n");
    printf("36   ULAZ       236\n");
    printf("35   IZLAZ       50\n");
    printf("37   ULAZ       240\n");
    printf("37   IZLAZ        3\n");
    printf("70   ULAZ       100\n");
    printf("10   IZLAZ       20\n");
    printf("10   ULAZ        40\n");
    printf("15   IZLAZ       15\n");
    printf("95   ULAZ        15\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("SUMARNA I SORTIRANA TRANSAKCIONA (tran_210429.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Promena   Kolicina\n");
    printf("10   ULAZ       210\n");
    printf("15   ULAZ       215\n");
    printf("20   IZLAZ      100\n");
    printf("30   IZLAZ       50\n");
    printf("35   ULAZ       235\n");
    printf("36   ULAZ       236\n");
    printf("37   ULAZ       237\n");
    printf("45   ULAZ       245\n");
    printf("55   ULAZ       255\n");
    printf("70   ULAZ       100\n");
    printf("95   ULAZ       295\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("OBJASNJENJE KLJUCNIH PROMENA\n");
    printf("------------------------------------------------------------\n");
    printf("POSTOJECI proizvodi iz stare maticne koji se menjaju:\n");
    printf("Id 20 : 100 - 100 = 0, pa zatim + 50 => 50\n");
    printf("Id 30 : 150 - 50 = 100\n");
    printf("Id 70 : 350 + 100 = 450\n\n");

    printf("NOVI proizvodi (nisu postojali u staroj maticnoj):\n");
    printf("Id 10 => 210\n");
    printf("Id 15 => 215\n");
    printf("Id 35 => 235\n");
    printf("Id 36 => 236\n");
    printf("Id 37 => 237\n");
    printf("Id 45 => 245\n");
    printf("Id 55 => 255\n");
    printf("Id 95 => 295\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("NOVA MATICNA DATOTEKA (maticna.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Naziv    Kolicina\n");
    printf("10   Pro_10   210\n");
    printf("15   Pro_15   215\n");
    printf("20   Pro_20    50\n");
    printf("30   Pro_30   100\n");
    printf("35   Pro_35   235\n");
    printf("36   Pro_36   236\n");
    printf("37   Pro_37   237\n");
    printf("40   Pro_40   200\n");
    printf("45   Pro_45   245\n");
    printf("50   Pro_50   250\n");
    printf("55   Pro_55   255\n");
    printf("60   Pro_60   300\n");
    printf("70   Pro_70   450\n");
    printf("80   Pro_80   400\n");
    printf("90   Pro_90   450\n");
    printf("95   Pro_95   295\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("IZVESTAJ O PROMENAMA (prom_210429.rpt)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   StaraKol  Naziv      Tip    Promena  NovaKol\n");
    printf("20   100       Pro_20     -      50       50\n");
    printf("30   150       Pro_30     -      50       100\n");
    printf("70   350       Pro_70     +      100      450\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("IZVESTAJ O NOVIM PROIZVODIMA (nov_pro_210429.rpt)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Proizvod  Kolicina\n");
    printf("10   Pro_10    210\n");
    printf("15   Pro_15    215\n");
    printf("35   Pro_35    235\n");
    printf("36   Pro_36    236\n");
    printf("37   Pro_37    237\n");
    printf("45   Pro_45    245\n");
    printf("55   Pro_55    255\n");
    printf("95   Pro_95    295\n\n");

    nova_strana();

    printf("Zakljucak:\n");
    printf(" - Postojeci proizvodi su azurirani i upisani u prom_*.rpt\n");
    printf(" - Novi proizvodi su dodati u maticnu i upisani u nov_pro_*.rpt\n\n");
}

void demo_cetvrti_slucaj(void)
{
    ocisti_ekran();

    printf("============================================================\n");
    printf("DEMO - CETVRTI SLUCAJ: NEPOSTOJECI PROIZVOD (err_pro)\n");
    printf("============================================================\n\n");

    printf("Azurira se maticna datoteka, ali se uzima u obzir da moze doci do:\n");
    printf(" - IZLAZA (izdavanja) kolicine za proizvod koji NE POSTOJI u maticnoj.\n");
    printf("Takva operacija je GRESKA, odbija se i upisuje u err_pro_*.rpt.\n\n");

    printf("Moguci scenariji:\n");
    printf(" - Postojeci proizvod + ULAZ  -> uspesno\n");
    printf(" - Postojeci proizvod + IZLAZ -> uspesno (ako je kolicina ok)\n");
    printf(" - Nepostojeci proizvod + IZLAZ -> GRESKA (err_pro)\n\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("STARA MATICNA DATOTEKA (maticna.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Naziv    Kolicina\n");
    printf("20   Pro_20   100\n");
    printf("30   Pro_30   150\n");
    printf("40   Pro_40   200\n");
    printf("50   Pro_50   250\n");
    printf("60   Pro_60   300\n");
    printf("70   Pro_70   350\n");
    printf("80   Pro_80   400\n");
    printf("90   Pro_90   450\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("TRANSAKCIONA DATOTEKA - HRONOLOSKI ZAPIS (transakciona.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Promena   Kolicina\n");
    printf("30   ULAZ      100\n");
    printf("92   IZLAZ      40\n");
    printf("30   IZLAZ      20\n");
    printf("23   IZLAZ      40\n");
    printf("50   ULAZ       20\n");
    printf("12   IZLAZ      40\n");
    printf("22   IZLAZ      20\n");
    printf("22   IZLAZ      20\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("SUMARNA I SORTIRANA TRANSAKCIONA (tran_210429.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Promena   Kolicina\n");
    printf("12   IZLAZ      40\n");
    printf("22   IZLAZ      40\n");
    printf("23   IZLAZ      40\n");
    printf("30   ULAZ       80\n");
    printf("50   ULAZ       20\n");
    printf("92   IZLAZ      40\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("OBJASNJENJE KLJUCNIH PROMENA\n");
    printf("------------------------------------------------------------\n");
    printf("USPEH (postoje u maticnoj):\n");
    printf("Id 30 : 150 + 80 = 230\n");
    printf("Id 50 : 250 + 20 = 270\n\n");

    printf("GRESKA (ne postoje u maticnoj, a trazi se IZLAZ):\n");
    printf("Id 12 : IZLAZ 40 -> ODBIJENO (err_pro)\n");
    printf("Id 22 : IZLAZ 40 -> ODBIJENO (err_pro)\n");
    printf("Id 23 : IZLAZ 40 -> ODBIJENO (err_pro)\n");
    printf("Id 92 : IZLAZ 40 -> ODBIJENO (err_pro)\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("NOVA MATICNA DATOTEKA (maticna.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Naziv    Kolicina\n");
    printf("20   Pro_20   100\n");
    printf("30   Pro_30   230\n");
    printf("40   Pro_40   200\n");
    printf("50   Pro_50   270\n");
    printf("60   Pro_60   300\n");
    printf("70   Pro_70   350\n");
    printf("80   Pro_80   400\n");
    printf("90   Pro_90   450\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("IZVESTAJ O PROMENAMA (prom_210429.rpt)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   StaraKol  Naziv    Tip  Promena  NovaKol\n");
    printf("30   150       Pro_30   +       80      230\n");
    printf("50   250       Pro_50   +       20      270\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("IZVESTAJ O GRESKAMA (err_pro_210429.rpt)\n");
    printf("------------------------------------------------------------\n");
    printf("Id    Kolicina   Naziv    Tip   Promena   Greska\n");
    printf("12    X          X        -     40        Nepostojeci proizvod.\n");
    printf("22    X          X        -     40        Nepostojeci proizvod.\n");
    printf("23    X          X        -     40        Nepostojeci proizvod.\n");
    printf("92    X          X        -     40        Nepostojeci proizvod.\n\n");

    nova_strana();

    printf("Zakljucak:\n");
    printf(" - Uspesne promene su upisane u prom_*.rpt\n");
    printf(" - Neuspesne (nepostojeci proizvod) su upisane u err_pro_*.rpt\n");
    printf(" - Za proizvode sa greskom, maticna se ne menja\n\n");
}

void demo_peti_slucaj(void)
{
    ocisti_ekran();

    printf("============================================================\n");
    printf("DEMO - PETI SLUCAJ: SVEOBUHVATNI (kombinacija svih slucajeva)\n");
    printf("============================================================\n\n");

    printf("U ovom slucaju su obuhvaceni svi moguci ishodi:\n");
    printf(" - Postojeci proizvod + ULAZ  -> uspesno\n");
    printf(" - Postojeci proizvod + IZLAZ -> uspesno (ako je kolicina ok)\n");
    printf(" - Postojeci proizvod + IZLAZ -> GRESKA (nepostojeca kolicina) -> err_kol\n");
    printf(" - Nepostojeci proizvod + ULAZ -> novi proizvod -> nov_pro\n");
    printf(" - Nepostojeci proizvod + IZLAZ -> GRESKA (nepostojeci proizvod) -> err_pro\n\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("STARA MATICNA DATOTEKA (maticna.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Naziv    Kolicina\n");
    printf("20   Pro_20   100\n");
    printf("30   Pro_30   150\n");
    printf("40   Pro_40   200\n");
    printf("50   Pro_50   250\n");
    printf("60   Pro_60   300\n");
    printf("70   Pro_70   350\n");
    printf("80   Pro_80   400\n");
    printf("90   Pro_90   450\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("TRANSAKCIONA DATOTEKA - HRONOLOSKI ZAPIS (transakciona.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Promena   Kolicina\n");
    printf("20   ULAZ       50\n");
    printf("70   IZLAZ      50   (osnovni slucaj)\n");
    printf("90   IZLAZ      50\n");
    printf("50   IZLAZ     800   (nepostojeca kolicina)\n");
    printf("60   IZLAZ     800\n");
    printf("35   ULAZ      150   (nov proizvod)\n");
    printf("15   ULAZ      150\n");
    printf("22   IZLAZ     175   (nepostojeci proizvod)\n");
    printf("92   IZLAZ     175\n");
    printf("20   ULAZ       50\n");
    printf("70   IZLAZ      50   (osnovni slucaj)\n");
    printf("90   ULAZ       50\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("SUMARNA I SORTIRANA TRANSAKCIONA (tran_210429.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Promena   Kolicina\n");
    printf("15   ULAZ      150\n");
    printf("20   ULAZ      100\n");
    printf("22   IZLAZ     175\n");
    printf("35   ULAZ      150\n");
    printf("50   IZLAZ     800\n");
    printf("60   IZLAZ     800\n");
    printf("70   IZLAZ     100\n");
    printf("90   ULAZ        0\n");
    printf("92   IZLAZ     175\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("OBJASNJENJE KLJUCNIH ISHODA\n");
    printf("------------------------------------------------------------\n");
    printf("USPEH - postojeci proizvodi:\n");
    printf("Id 20 : 100 + 100 = 200\n");
    printf("Id 70 : 350 - 100 = 250\n");
    printf("Id 90 : 450 +   0 = 450\n\n");

    printf("NOVI PROIZVODI (nepostojeci + ULAZ):\n");
    printf("Id 15 => 150 (dodaje se u maticnu)\n");
    printf("Id 35 => 150 (dodaje se u maticnu)\n\n");

    printf("GRESKE:\n");
    printf("Id 50 : 250 - 800 -> ODBIJENO (err_kol)\n");
    printf("Id 60 : 300 - 800 -> ODBIJENO (err_kol)\n");
    printf("Id 22 : IZLAZ 175 -> ODBIJENO (err_pro)\n");
    printf("Id 92 : IZLAZ 175 -> ODBIJENO (err_pro)\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("NOVA MATICNA DATOTEKA (maticna.dat)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Naziv    Kolicina\n");
    printf("15   Pro_15   150\n");
    printf("20   Pro_20   200\n");
    printf("30   Pro_30   150\n");
    printf("35   Pro_35   150\n");
    printf("40   Pro_40   200\n");
    printf("50   Pro_50   250\n");
    printf("60   Pro_60   300\n");
    printf("70   Pro_70   250\n");
    printf("80   Pro_80   400\n");
    printf("90   Pro_90   450\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("IZVESTAJ O PROMENAMA (prom_210429.rpt)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   StaraKol  Naziv    Tip    Promena  NovaKol\n");
    printf("20   100       Pro_20   +      100      200\n");
    printf("70   350       Pro_70   +      100      250\n");
    printf("90   450       Pro_90   -      0        450\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("IZVESTAJ O NOVIM PROIZVODIMA (nov_pro_210429.rpt)\n");
    printf("------------------------------------------------------------\n");
    printf("Id   Proizvod  Kolicina\n");
    printf("15   Pro_15    150\n");
    printf("35   Pro_35    150\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("IZVESTAJ O GRESKAMA - NEPOSTOJECA KOLICINA (err_kol_210429.rpt)\n");
    printf("------------------------------------------------------------\n");
    printf("Id    Kolicina   Naziv    Tip   Promena   Greska\n");
    printf("50    250        Pro_50   -     800       Nepostojeca kolicina proizvoda.\n");
    printf("60    300        Pro_60   -     800       Nepostojeca kolicina proizvoda.\n");

    nova_strana();

    printf("------------------------------------------------------------\n");
    printf("IZVESTAJ O GRESKAMA - NEPOSTOJECI PROIZVOD (err_pro_210429.rpt)\n");
    printf("------------------------------------------------------------\n");
    printf("Id    Kolicina   Naziv    Tip   Promena   Greska\n");
    printf("22    X          X        -     175       Nepostojeci proizvod.\n");
    printf("92    X          X        -     175       Nepostojeci proizvod.\n\n");

    nova_strana();

    printf("Zakljucak:\n");
    printf(" - U prom_*.rpt su upisane uspesne promene postojecih proizvoda\n");
    printf(" - U nov_pro_*.rpt su upisani novi proizvodi\n");
    printf(" - U err_kol_*.rpt su greske zbog nepostojece kolicine\n");
    printf(" - U err_pro_*.rpt su greske zbog nepostojeceg proizvoda\n\n");
}



void pomoc_o_transakcionoj_datoteci(void)
{
    ocisti_ekran();

    printf("==== UPUTSTVO ZA RAD SA TRANSAKCIONOM DATOTEKOM ====\n\n");
    printf("1. Create     ::- Sistem ce da napravi novu, praznu datoteku u kojoj cemo da belezimo sve\n");
    printf("promene raspolozive kolicine proizvoda za neku prodavnicu tog dana.\n");
    printf("Ukoliko pokusamo da napravimo datoteku a vec postoji jedna, dobicemo\n");
    printf("opciju da odustanemo od akcije ili da obrisemo vec postojecu datoteku i\n");
    printf("napravimo novu.\n");
    printf("\n");
    nova_strana();

    printf("==== UPUTSTVO ZA RAD SA TRANSAKCIONOM DATOTEKOM ====\n\n");
    printf("2. Drop       ::- Sistem ce da obrise datoteku ukoliko ona postoji, ako datoteka ne postoji,\n");
    printf("dobicemo poruku o tome i nece se nista desiti.\n");
    printf("\n");
    nova_strana();

    printf("==== UPUTSTVO ZA RAD SA TRANSAKCIONOM DATOTEKOM ====\n\n");
    printf("3. Insert     ::- Koristi se za dodavanje novih transakcija u datoteku. Unosimo sifru\n");
    printf("proizvoda, promenu (1 = ULAZ, -1 = IZLAZ) i kolicinu.\n");
    printf("Ako pokusamo da dodamo transakciju za nepostojeci proizvod, sistem ce nas\n");
    printf("obavestiti o tome.\n");
    printf("\n");
    nova_strana();

    printf("==== UPUTSTVO ZA RAD SA TRANSAKCIONOM DATOTEKOM ====\n\n");
    printf("4. Select All ::- Koristi se za brisanje transakcija iz datoteke. Unosimo sifru proizvoda cije\n");
    printf("transakcije zelimo da obrisemo.\n");
    printf("\n");
    nova_strana();

    printf("==== UPUTSTVO ZA RAD SA TRANSAKCIONOM DATOTEKOM ====\n\n");
    printf("5. Select Id  ::- Ispisuje sve transakcije koje se nalaze u datoteci. Ukoliko u datoteci ne\n");
    printf("postoji ni jedna transakcija, tabela ce biti prazna. Ako prilikom poziva ove\n");
    printf("funkcionalnosti ne postoji napravljena datoteka, ispisace nam se poruka da\n");
    printf("sistem ne moze da otvori datoteku.\n");
    printf("\n");
}

void pomoc_o_maticnoj_datoteci(void)
{
    ocisti_ekran();

    printf("==== UPUTSTVO ZA RAD SA MATICNOM DATOTEKOM ====\n\n");
    printf("1. Create     ::- Sistem kreira novu datoteku u kojoj ce sluziti za skladistenje podataka o\n");
    printf("raspolozivoj kolicini svakog proizvoda u prodavnici. Ukoliko prilikom izbora\n");
    printf("ove opcije vec postoji napravljena datoteka, dobicemo mogucnost da izaberemo\n");
    printf("da li cemo da obrisemo staru datoteku i da napravimo novu ili cemo da\n");
    printf("odustanemo od pravljenja nove datoteke.\n");
    printf("\n");
    nova_strana();

    printf("==== UPUTSTVO ZA RAD SA MATICNOM DATOTEKOM ====\n\n");
    printf("2. Drop       ::- Sistem ce da obrise datoteku ukoliko ona postoji, ako datoteka ne postoji,\n");
    printf("dobicemo poruku o tome i nece se nista desiti.\n");
    printf("\n");
    nova_strana();

    printf("==== UPUTSTVO ZA RAD SA MATICNOM DATOTEKOM ====\n\n");
    printf("3. Insert     ::- Koristi se za dodavanje novih proizvoda u datoteku. Unosimo sifru proizvoda,\n");
    printf("naziv i raspolozivu kolicinu proizvoda. Ako pokusamo da dodamo vec postojeci\n");
    printf("proizvod, ispisace nam se poruka o tome i novi proizvod nece biti dodat u\n");
    printf("datoteku.\n");
    printf("\n");
    nova_strana();

    printf("==== UPUTSTVO ZA RAD SA MATICNOM DATOTEKOM ====\n\n");
    printf("4. Delete     ::- Koristi se za brisanje proizvoda iz datoteke. Unosimo sifru proizvoda koji\n");
    printf("zelimo da obrisemo. Ukoliko taj proizvod postoji u datoteci, ispisace nam se\n");
    printf("podaci o njemu i sistem ce nas pitati da potvrdimo odluku o njegovom brisanju.\n");
    printf("Ako proizvod koji zelimo da obrisemo ne postoji u datoteci ispisace nam se\n");
    printf("poruka o tome i nista se nece desiti.\n");
    printf("\n");
    nova_strana();

    printf("==== UPUTSTVO ZA RAD SA MATICNOM DATOTEKOM ====\n\n");
    printf("5. Update All ::- Ova funkcionalnost se koristi da bismo na kraju svakog dana azurirali podatke\n");
    printf("o raspolozivoj kolicini svakog proizvoda iz maticne datoteke. To se radi na\n");
    printf("osnovu podataka iz transakcione datoteke, tj. na osnovu svih promena\n");
    printf("raspolozive kolicine svakog proizvoda tog dana. Prilikom pozivanja ove\n");
    printf("funkcionalnosti transakciona datoteka se arhivira i brise, a maticna se\n");
    printf("arhivira i azurira. Arhivirane datoteke se cuvaju u ./ASD/DATA/OLD kao mat_<ggmmdd>.dat i tran_<ggmmdd>.dat.\n");
    printf("Kada se dodaje odredjena kolicina ili se oduzima kolicina koja je manja od trenutno\n");
    printf("raspolozive kolicine nekog proizvoda koji se nalazi u datoteci, promena se\n");
    printf("desava i podaci o tome se zapisuju u izvestaj i prikazuju nam se na prvom\n");
    printf("slajdu, taj izvestaj se cuva u ./ASD/RPT kao prom_<ggmmdd>.rpt. Kada je potrebno oduzeti odredjenu\n");
    printf("kolicinu proizvoda koji se ne nalazi u datoteci, promena se ne desava i\n");
    printf("podaci o tome se zapisuju u izvestaj i prikazuju nam se na drugom slajdu, taj\n");
    printf("izvestaj se cuva u ./ASD/ERR kao err_pro_<ggmmdd>.rpt. Ukoliko treba da se doda nova kolicina proizvoda koji\n");
    printf("nije u datoteci, sistem nam daje da unesemo naziv tog proizvoda i on se\n");
    printf("dodaje u datoteku. Podaci o novim proizvodima se zapisuju u izvestaj i\n");
    printf("prikazuju nam se na trecem slajdu, taj izvestaj se cuva u ./ASD/RPT nov_pro_<ggmmdd>.rpt. Kada je\n");
    printf("potrebno oduzeti odredjenu kolicinu proizvoda koji se nalazi u datoteci, ali\n");
    printf("ta kolicina je veca nego sto je trenutno raspoloziva kolicina tog proizvoda,\n");
    printf("promena se ne desava i podaci o tome se zapisuju u izvestaj i prikazuju nam\n");
    printf("se na cetvrtom slajdu, taj izvestaj se cuva u ./ASD/ERR err_kol_<ggmmdd>.rpt.\n");
    printf("\n");
    nova_strana();

    printf("==== UPUTSTVO ZA RAD SA MATICNOM DATOTEKOM ====\n\n");
    printf("6. Update Id  ::- Koristi se za menjanje podataka o proizvodu koji se nalazi u datoteci.\n");
    printf("Unosimo sifru proizvoda koji zelimo da izmenimo. Ukoliko taj proizvod postoji\n");
    printf("u datoteci, ispisace nam se podaci o njemu i sistem ce nas prvo pitati da\n");
    printf("unesemo novi naziv proizvoda, a zatim da unesemo novu raspolozivu kolicinu\n");
    printf("proizvoda. Ako proizvod koji zelimo da izmenimo ne postoji u datoteci\n");
    printf("ispisace nam se poruka o tome i nece se nista desiti.\n");
    printf("\n");
    nova_strana();

    printf("==== UPUTSTVO ZA RAD SA MATICNOM DATOTEKOM ====\n\n");
    printf("7. Select All ::- Ispisace nam se podaci o svim proizvodima koji se nalaze u datoteci.\n");
    printf("Ukoliko u datoteci ne postoji ni jedan proizvod, tabela ce biti prazna.\n");
    printf("Ako prilikom poziva ove funkcionalnosti ne postoji napravljena datoteka,\n");
    printf("ispisace nam se poruka da sistem ne moze da otvori datoteku.\n");
    printf("\n");
    nova_strana();

    printf("==== UPUTSTVO ZA RAD SA MATICNOM DATOTEKOM ====\n\n");
    printf("8. Select Id  ::- Koristi se da nam se ispisi podaci o odredjenom proizvodu. Unosimo sifru\n");
    printf("proizvoda koji hocemo da nam se prikaze. Ukoliko proizvod postoji u datoteci,\n");
    printf("ispisace nam se njegova sifra, naziv i raspoloziva kolicina tog proizvoda.\n");
    printf("Ako proizvod ne postoji u datoteci, ispisace nam se poruka o tome. Ako\n");
    printf("prilikom poziva ove funkcionalnosti ne postoji napravljena datoteka,\n");
    printf("ispisace nam se poruka da sistem ne moze da otvori datoteku.\n");
    printf("\n");
}

void pomoc_o_azuriranju(void)
{
    ocisti_ekran();

    printf("==== O AZURIRANJU SERIJSKE DATOTEKE ====\n\n");

    printf("Serijska (sortirana redna) datoteka je datoteka u kojoj su\n");
    printf("slogovi uredjeni po vrednosti kljuca.\n");
    printf("U ovom projektu kljuc je ID proizvoda.\n\n");

    printf("Maticna datoteka sadrzi trenutne podatke o proizvodima:\n");
    printf("ID, naziv i kolicinu.\n\n");

    printf("Transakciona datoteka sadrzi promene nad proizvodima\n");
    printf("(ULAZ - povecanje kolicine, IZLAZ - smanjenje kolicine).\n\n");

    nova_strana();

    printf("==== POSTUPAK AZURIRANJA ====\n\n");

    printf("1. Transakciona datoteka se prvo sabira i sortira po ID-u.\n");
    printf("   Dobija se sumarna transakciona datoteka (datoteka promena).\n\n");

    printf("2. Maticna datoteka i datoteka promena se obradjuju\n");
    printf("   sekvencijalno, slog po slog.\n\n");

    printf("3. Za svaki proizvod proverava se:\n");
    printf("   - da li proizvod postoji u maticnoj datoteci\n");
    printf("   - da li je promena ULAZ ili IZLAZ\n");
    printf("   - da li je kolicina validna\n\n");

    nova_strana();

    printf("==== ISHODI AZURIRANJA ====\n\n");

    printf("Uspesno azuriranje:\n");
    printf(" - kolicina proizvoda se menja\n");
    printf(" - promena se upisuje u izvestaj o promenama (prom_*.rpt)\n\n");

    printf("Neuspesno azuriranje:\n");
    printf(" - operacija se odbija\n");
    printf(" - upisuje se odgovarajuci izvestaj o greskama:\n");
    printf("   * err_kol_*.rpt - nepostojeca kolicina\n");
    printf("   * err_pro_*.rpt - nepostojeci proizvod\n\n");

    nova_strana();

    printf("==== SLUCAJEVI AZURIRANJA ====\n\n");

    printf("1. Osnovni slucaj\n");
    printf("2. Nepostojeca kolicina\n");
    printf("3. Nov proizvod\n");
    printf("4. Nepostojeci proizvod\n");
    printf("5. Sveobuhvatni slucaj\n\n");

    printf("Za svaki slucaj postoji odgovarajuci DEMO primer\n");
    printf("sa prikazom ulaznih i izlaznih datoteka.\n\n");
}

void pomoc_o_nama(void)
{
    ocisti_ekran();

    printf("============================================================\n");
    printf("                    O NAMA\n");
    printf("============================================================\n\n");

    printf("Softverski inzenjer:\n");
    printf(" - Luka Grcic\n");
    printf(" Fakultet organizacionih nauka\n");
    printf(" Univerzitet u Beogradu\n\n");

    printf("Domenski inzenjer:\n");
    printf(" - Sasa D. Lazarevic\n");
    printf(" E-mail: slazar@fon.rs\n");
    printf(" Profesor na Fakultetu organizacionih nauka\n\n");

    printf("Aplikacija:\n");
    printf(" - Naziv   : ASD\n");
    printf(" - Opis    : Azuriranje serijske (sortirane redne) datoteke\n");
    printf(" - Verzija : 1.0\n\n");
}



int ucitaj_ceo_broj(const char* poruka) {
    int broj;
    char buffer[100];

    if (strlen(poruka) > 0) {
        printf("%s", poruka);
    }

    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return -1;
        }

        if (sscanf(buffer, "%d", &broj) == 1) {
            return broj;
        }

        printf("Nevalidan unos. Unesite ceo broj: ");
    }
}

void cekaj_enter(void) {
    printf("\nPritisnite Enter za nastavak...");

    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void ocisti_ekran(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void prikazi_poruku(const char* poruka, int je_greska) {
    if (je_greska) {
        printf("\n[GRESKA] %s\n", poruka);
    }
    else {
        printf("\n[INFO] %s\n", poruka);
    }
}

void nova_strana(void)
{
    cekaj_enter();
    ocisti_ekran();
}


