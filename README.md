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

main.cpp yra 4 kodo eilutės, kuriose galima nustatyti pagrindinius kintamuosius:

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