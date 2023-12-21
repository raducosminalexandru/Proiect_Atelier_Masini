#include "atelier.h"
#include <iostream>

Atelier::Atelier() {
    numAngajati = 0;
    numMasini = 0;
    numMasiniAsteptare = 0;

    for(int i = 0; i < MAX_ANGAJATI; i++){
        angajati[i] = nullptr;
    }

    for(int i = 0; i < MAX_MASINI; i++){
        masini[i] = nullptr;
    }

    for(int i = 0; i < MAX_MASINI_ASTEPTARE; i++){
        masini_asteptare[i] = nullptr;
    }
}

void Atelier::AdaugaAngajat(Angajat* angajat) {
    if(numAngajati < MAX_ANGAJATI){
        angajati[numAngajati++] = angajat;
    } else {
        std::cout << "Atelierul a atins numarul maxim de angajati!\n";
    }
}

void Atelier::AdaugaMasina(Masina* masina, bool raman) {
    if(numMasini < MAX_MASINI){
        masini[numMasini++] = masina;
    }

    else{
        AdaugaMasinaAsteptare(masina,raman);
    }
}

void Atelier::AdaugaMasinaAsteptare(Masina* masina, bool raman) {
    if(numMasiniAsteptare < MAX_MASINI_ASTEPTARE && raman == 1){
        masini_asteptare[numMasiniAsteptare++] = masina;
    }

    else if(numMasiniAsteptare >= MAX_MASINI_ASTEPTARE){
        std::cout << "S-a atins numarul maxim de masini care asteapta la coada.\n";
    }

    else if(raman == 0){
        std::cout << "Clientul a decis sa plece.\n";
    }
}

bool Atelier::esteDeschis() const {
    if(numAngajati == 0){
        return false;
    }

    else return true;
}

bool Atelier::VerificaTipuriMasini(Masina* masina1, Masina* masina2, Masina* masina3, Masina* masina4) {
    int contorMasiniStandard = 0;
    int contorMasiniNestandard = 0;

    auto verificaTipMasina = [&](Masina* masina) {
        if(masina != nullptr) {
            if (masina->tipMasina() == "Standard") {
                contorMasiniStandard++;
            } else if (masina->tipMasina() == "Autobuz" || masina->tipMasina() == "Camion") {
                contorMasiniNestandard++;
            }
        }
    };

    verificaTipMasina(masina1);
    verificaTipMasina(masina2);
    verificaTipMasina(masina3);
    verificaTipMasina(masina4);

    return (contorMasiniNestandard <= 1 && contorMasiniStandard <= 3);
}

void Atelier::luare_in_primire_masini(Angajat* angajat, bool raman, Masina* PrimaMasina, Masina* aDouaMasina, Masina* aTreiaMasina, Masina* aPatraMasina) {
    AdaugaAngajat(angajat);

    if (VerificaTipuriMasini(PrimaMasina, aDouaMasina, aTreiaMasina, aPatraMasina)) {
        if(PrimaMasina != nullptr) AdaugaMasina(PrimaMasina, raman);
        if(aDouaMasina != nullptr) AdaugaMasina(aDouaMasina, raman);
        if(aTreiaMasina != nullptr) AdaugaMasina(aTreiaMasina, raman);
        if(aPatraMasina != nullptr) AdaugaMasina(aPatraMasina, raman);
        std::cout << "Masinile au fost luate in primire de catre un angajat!\n";

        if(PrimaMasina == nullptr){
            numMasini++;
        }

        if(aDouaMasina == nullptr){
            numMasini++;
        }

        if(aTreiaMasina == nullptr){
            numMasini++;
        }

        if(aPatraMasina == nullptr){
            numMasini++;
        }
    }

    else {
        std::cout << "Angajatul nu poate avea in primire atatea masini de genul, el poate avea cel mult 3 masini standard si cel mult o masina nestandard!\n";
    }
}

void Atelier::optiune_asteptare(Masina* masina, int nr_angajat, bool raman) {
    for(int i = 0; i < 4; i++){
        if(masini[4 * nr_angajat + i] == nullptr){
            return;
        }
    }

    for(int i = 0; i < 4; i++){
        if(masini_asteptare[4 * nr_angajat + i] == nullptr){
            if (angajati[nr_angajat] != nullptr) {
                cout << "Mașina a fost adăugată la coada angajatului " << nr_angajat << ".\n";
                AdaugaMasinaAsteptare(masina, raman);
            } else {
                cout << "Angajatul " << nr_angajat << " nu este disponibil. Mașina a fost adăugată în mod automat la primul angajat liber.\n";
                AdaugaMasina(masina, raman);
            }
            return;
        }
    }

    std :: cout << "Angajatul " << nr_angajat << " a atins numărul maxim de mașini în atelier și la coadă! ";
    return;
}


Atelier::~Atelier() {
    for(int i = 0; i < MAX_ANGAJATI; i++){
        delete angajati[i];
    }

    for(int j = 0; j < MAX_MASINI; j++){
        delete masini[j];
    }
}



