# ASD – Ažuriranje serijske (sortirane redne) datoteke

## Pokretanje projekta

### Zahtevi

- Visual Studio 2022 (ili noviji)
- Windows operativni sistem

### Pokretanje

1. Klonirati repozitorijum
2. Otvoriti `ASD.sln`
3. **Retargetovati solution** – desni klik na solution u Solution Explorer-u → `Retarget Solution` → stiklirati sve projekte (`Slucaj1` – `Slucaj5`) → `OK`
   > Ovaj korak je neophodan ako se koristi novija verzija Visual Studio-a od one u kojoj je projekat kreiran (npr. VS 2026). Bez toga dolazi do greške `MSB8020 – Platform Toolset v143 cannot be found`.
4. Podesiti `Working Directory` za svaki projekat – desni klik na projekat → `Properties` → `Debugging` → `Working Directory` → promeniti na `$(SolutionDir)`
   > Projekat koristi relativne putanje ka `ASD/` folderu koji se nalazi u root-u solution-a. Bez ovog podešavanja program ne može da pronađe ni kreira potrebne datoteke.
5. Izgraditi solution – `Build` → `Build Solution` (`Ctrl+Shift+B`)
6. Izabrati željeni scenario (`Slucaj1` – `Slucaj5`)
7. Postaviti projekat kao `Startup Project`
8. Pokrenuti aplikaciju

### Napomena

Projekat koristi relativne putanje za rad sa datotekama, zbog čega struktura foldera mora ostati nepromenjena.

---

## Uvod

Aplikacija ASD je konzolna aplikacija napisana u programskom jeziku C.  
Namenjena je obradi podataka zasnovanoj na datotekama (file-based data processing), sa fokusom na ažuriranje serijske (sortirane redne) datoteke proizvoda.

Svaki proizvod je jedinstveno identifikovan pomoću ID vrednosti i ima pridružen naziv i količinu.

---

## Tehnologije

- C
- Visual Studio
- Rad sa binarnim datotekama
- Sekvencijalna obrada podataka
- Konzolni korisnički interfejs

---

## Organizacija podataka

Aplikacija koristi dve osnovne datoteke:

### Matična datoteka (`maticna.dat`)

Sadrži trenutne podatke o proizvodima:
- ID proizvoda
- naziv proizvoda
- raspoloživu količinu

Datoteka je sortirana po ID-ju proizvoda u rastućem redosledu.

### Transakciona datoteka (`transakciona.dat`)

Sadrži hronološki zapis promena nad proizvodima.

Promene mogu biti tipa:

- `ULAZ` – povećanje količine proizvoda
- `IZLAZ` – smanjenje količine proizvoda

Na osnovu transakcione datoteke kreira se sumarna i sortirana datoteka promena koja se koristi za ažuriranje matične datoteke.

---

## Postupak ažuriranja

Proces ažuriranja sastoji se iz sledećih koraka:

1. Transakciona datoteka se obrađuje i sabira po ID-ju proizvoda
2. Kreira se sumarna transakciona datoteka sortirana po ID-ju
3. Matična datoteka i datoteka promena obrađuju se sekvencijalno
4. Za svaki proizvod proverava se:
   - da li proizvod postoji u matičnoj datoteci
   - tip promene (`ULAZ` ili `IZLAZ`)
   - validnost količine
5. Na osnovu ishoda ažuriranja kreiraju se odgovarajući izveštaji

---

## Slučajevi ažuriranja

Aplikacija obuhvata pet slučajeva ažuriranja:

### 1. Osnovni slučaj

Ažurira se postojeći proizvod, a količine su uvek odgovarajuće.

### 2. Nepostojeća količina

Pokušava se izdavanje veće količine nego što je dostupno.  
Operacija se odbija i evidentira kao greška.

### 3. Nov proizvod

Prima se količina proizvoda koji ne postoji u matičnoj datoteci.  
Proizvod se dodaje u novu matičnu datoteku.

### 4. Nepostojeći proizvod

Pokušava se izdavanje količine za proizvod koji ne postoji.  
Operacija se odbija i evidentira kao greška.

### 5. Sveobuhvatni slučaj

Kombinacija svih prethodnih slučajeva ažuriranja.

---

## Izveštaji

Tokom ažuriranja mogu se kreirati sledeći izveštaji:

### `prom_*.rpt`

Izveštaj o uspešno izvršenim promenama nad postojećim proizvodima.

### `nov_pro_*.rpt`

Izveštaj o novim proizvodima koji su dodati u matičnu datoteku.

### `err_kol_*.rpt`

Izveštaj o greškama nastalim zbog nepostojeće količine proizvoda.

### `err_pro_*.rpt`

Izveštaj o greškama nastalim zbog nepostojećeg proizvoda.

---

## Struktura direktorijuma

```text
ROOT/
│
├── ASD/
│   ├── DATA/
│   │   ├── maticna.dat
│   │   ├── transakciona.dat
│   │   └── OLD/
│   │       ├── mat_<datum>.dat
│   │       └── tran_<datum>.dat
│   ├── DEMO/
│   ├── ERR/
│   │   ├── err_kol_<datum>.rpt
│   │   └── err_pro_<datum>.rpt
│   ├── RPT/
│   │   ├── prom_<datum>.rpt
│   │   └── nov_pro_<datum>.rpt
│   └── info.txt
│
├── Common/
├── Slucaj1/
├── Slucaj2/
├── Slucaj3/
├── Slucaj4/
├── Slucaj5/
│
├── ASD.sln
└── README.md
```

---

## Autor i mentor

### Softverski inženjer

- Luka Grčić

### Mentor / Domenski inženjer

- Saša D. Lazarević

Fakultet organizacionih nauka
