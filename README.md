# lygiagretieji_nd_3_1

### 1. Parašykite C++ gijų programą, kurią vykdant susidaro aklavietės.

- Modeliuokite mažiausiai trijų tipų resursus.
- Parinkite parametrus, kad aklavietės susidarytų dažnai, bet nebūtinai iš karto.
- Jei aklavietės sėkmingai užkertamos ar šalinamos, programa turėtų veikti amžinai.

### 2. Parašykite programą ar funkciją, kuri atpažįsta galimas aklavietes ir užkerta joms kelią.

- Kokia informacija iš gijų ir kokios galios jas valdyti bus reikalingos jūsų algoritmui?

### 3. Parašykite programą ar funkciją, kuri atpažįsta susidariusias aklavietes ir jas pašalina.

- Kokia informacija iš gijų ir kokios galios jas valdyti bus reikalingos jūsų algoritmui?
- Atminkite, kad laukimą prie mutekso galima modeliuoti kartojant neblokuojančio užrakto tikrinimą. Čia gija gali, pvz., tikrinti, ar neatėjo žinutė iš pašalinimo algoritmo.

# Programos vekimas

## Pradinės vertės

main.cpp[24-27] yra 4 kodo eilutės, kuriose galima nustatyti pagrindinius kintamuosius:

    int mutex_count = 8;
    int worker_count = 8;
    int lock_after = 10;
    int random_after = 10;

- _mutex_count_ nurodo, kiek atskirų resursų bus modeliuojama
- _worker_count_ nurodo, kiek gijų (thread) bus naudojama
- _lock_after_ nurodo, po kiek pagrindinio ciklo iteracijų bus sudaroma aklavietė
- _random_after_ nurodo, po kiek pagrindinio ciklo iteracijų bus naudojamas atsitiktinis resursų rakinimas

### Pavyzdys

Rakinimo seka bus vaizduojama matrica, kurios stulpelių skaičius lygus _mutex_count_, o eilučių - _worker_count_. Vienetas reiškia užrakinamą resursą, nulis - nerakinamą:

    1 0 0 0
    0 1 0 0
    0 0 1 0
    0 0 0 1

Tarkime mūsų pradinės sąlygos yra tokios:

    int mutex_count = 4;
    int worker_count = 4;
    int lock_after = 10;
    int random_after = 5;

- Pirmasias 4 iteracijas programa rakins resursus taip, kad visi resursai būtų naudojami tik vienoje gijoje:

      1 0 0 0
      0 1 0 0
      0 0 1 0
      0 0 0 1

- Nuo 5 iteracijos programa pradės generuoti atsitiktines matricas, pvz.:

      0 1 1 0
      1 0 0 0
      1 1 0 1
      0 1 0 1

- Pasiekus 10 iteraciją, programa užrakins visus resursus visoms matricoms, garantuodama aklavietę (deadlock):

      1 1 1 1
      1 1 1 1
      1 1 1 1
      1 1 1 1

---
## Bankininko algoritmas

Programos metu susidaro situacijos, kada gijai reikia daugiau resursų, nei šiuo metu pasiekiama. Tačiau ji pasiimdama visus, kuriuos gali, tačiau laukdama kitų, gali sudaryti aklavietę. Apsisaugoti nuo tokios situacijos galima naudojant bankininko algoritmą. Jis užtikrina, kad gijos, kurios negali pasiimti visų reikiamų resursų, nesudarys aklavietės. 

### Algoritmo paaiškinimas praktiniu pavyzdžiu

Tarkime, kad programoje yra 4 modeliuojami duomenys. Programos pradžioje jig visi bus laisvi. Šią informaciją galime atvaizduoti vektoriumi su 4 duomenimis, kurių būsena gali būti 1 arba 0:

    1 1 1 1

Paleidus gijas, jos pradeda kreiptis į bankininką, prašydamos užrakinti joms reikalingus duomenis. Šiuos duomenis taip pat galime atvaizduoti vektoriumis su 4 binariais elementais. 

Tarkime, kad _gija1_ kreipiasi į bankininką ir prašo užrakinti pirmąjį resursą, pateikdama prašymą:

    1 0 0 0

Bankininkas patikrina, ar reikalingi resursai yra laisvi, lygindamas prašymą su laisvų resursų vektoriumi. Šiuo atveju resursai laisvi, todėl bankininkas užrakina resursą, paleidžia giją ir pasižymi, kad resursas užimtas. Dabar laisvų resursų vektorius atrdodo taip:

    0 1 1 1

Atėjus antrai gijai _gija2_ ir pareikalavus 2 ir 3 resursų:
    
    0 1 1 0
    
bankininkas juos taip pat užrakina, pasižymi ir paleidžia giją. Dabar laisvų resursų vektorius atrodo taip:

    0 0 0 1

Atėjus trečiai gijai _gija3_ ir pareikalavus duoti resursus:

    1 0 0 1

bankininkas aptinka, kad neturi visų reikiamų resursų, kurių reikalauja gija3, todėl _gija3_ lieka laukti, kol šie resursai atsilaisvins. 

Tačiau kai ateina _gija4_ ir pareikalauja:

    0 0 0 1

bankininkas užrakina resursą ir pasižymėjęs, paleidžia giją.

Dabar _gija3_ turi laukti, kol savo vykdymą pabaigs _gija1_ ir _gija4_.

### Implementacija

Kiekviena gija prieš kritinės sekcijos pradžią ir jos gale kreipiasi į objekto _banker_ metodus _lock(request)_ ir _unlock(request)_ ir paduoda vektorių _true/false_ verčių, kurios nurodo, kurių resursų gijai reikia. Metodo _lock_ viduje, gija patenka į begalinį ciklą, kuriame laukia, kol bus atlaisvinti visi reikalingi resursai. Tik tada užrakinami gijai reikalingi resursai ir gija gali toliau vykdyti savo darbą.

---
## Išvedimas

Programos vykdymo metu, konsolės lange galima stebėti išvedamus duomenis, kurie leidžia įvertinti programos būseną. Išvestis atrodo taip:

    ------- THREAD 0 -------
    Working... 
    Iteration:  0
    Locking at: 16
    Random at:  12
    ------------------------
    ------- THREAD 0 -------
    Working... 
    Iteration:  1
    Locking at: 16
    Random at:  12
    ------------------------

 Pirmoje eilutėje nuorodomas gijos skaičius, kurios statusas spausdinamas. Vėliau nurodomas iteracijos skaičius (jis skaičiuojamas bendrai tarp visų gijų). Sekančiose eilutėse spausdinama informacija apie tai, kada bus rakinamos gijos ar generuojamos atsitiktinės rakinimo sąlygos.

---

## Informacija II ir III grupėms

### II grupei

Programoje naudomajas mock'inta _Banker_ implementacija, įterpiant failą _banker.h_. Jūsų _banker.h_ faile turi būti aprašyta klasė Banker su konstruktoriumi, priimančiu modeliuojamų duomenų kiekį _mutex_count_. _Banker_ klasės objektas turi turėti pasiekiamus metodus _.lock(int id)_, _.unlock(int id)_ ir _.cleanup()_. Pavyzdys pateiktas _banker.h_ faile.

 ### III grupei

Irgi rekomenduoju naudoti klasę, kurios objektai turės pasiekiamus metodus. Šiuo metu programoje neturiu implementavęs mock'into jūsų modulio, nes nežinau, kaip veikia jūsų dalies logika. Kai turėsit veikiantį modelį, pranėškit - atnaujinsiu kodą taip, kad irgi užtektų tik įdėti jūsų failą.