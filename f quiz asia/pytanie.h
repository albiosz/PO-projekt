//
// Created by Joanna Adamczyk on 2019-12-23.
//
#ifndef PROGRAMOWANIE_OBIEKTOWE_PYTANIE_H
#define PROGRAMOWANIE_OBIEKTOWE_PYTANIE_H

#include <iostream>

using namespace std;

class Pytanie
{
public:
    string tresc; //przechowuje tresc pytania
    string a,b,c,d; //przechowuje odpowiedzi
    int nr_pytania; //przechowuje nr pytania
    string odp_pop; //przechowuje poprawna odpowiedz
    string odp_usr; //przechowuje odpowiedz podana przez uzytkownika
    int punkt; //0 lub 1, zla lub dobra odpowiedz


    void wczytaj(); //fcja wczytuje dane z pliku
    void zadaj(); //fcja zada pytanie uzytkownikowi, wyswietli je na ekranie
    void sprawdz(); //fcja sprawdzi, czy uzytkownik dobrze odpowiedzial
};



#endif //PROGRAMOWANIE_OBIEKTOWE_PYTANIE_H
