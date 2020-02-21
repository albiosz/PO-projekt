#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pytanie.h"
#define PROG 75
#define PYT 25

int wynik = 0;
int l_pytan;


void zdaneczynie(float a,int b)
{
    float procent;
    procent = a/b*100;
    if (procent >= PROG)
    {
        cout << "Brawo, zaliczyles test! :)" << endl;
    }
    else {cout << "Niestety, nie zaliczyles testu :(" << endl;}
    cout << "Twoja suma punktow: " << a << "\n" << "Twoj wynik procentowy: " << procent << "%" << endl;
    cout << "Aby zdac test powinienes uzyskac przynajmniej " << PROG << "%" << endl;
}

//funkcja do zczytania z pliku quizu

void wprowadz(class Pytanie *p)
{   int i;
    for (i = 0; i <= 9; i++) {
        p[i].nr_pytania = i + 1;
        p[i].wczytaj();
    }
    l_pytan = 9; //pytan jest o 1 wiecej ale w tablicy obiektow numerujemy od zera
}

// funkcja przeprowadza test i sumuje uzyskana liczbe punktow
int rozw_quiz(class Pytanie *p)
{
    int i;
    int suma_pkt = 0; //suma zdobytych punktow
    for (i = 0; i <= l_pytan; i++) {
        p[i].zadaj();
        p[i].sprawdz();
        suma_pkt += p[i].punkt;
    } // tworzymy liste obietkow, czyli pytan ;)
    wynik = suma_pkt;

    cout << "KONIEC QUIZU!\n";
    zdaneczynie(suma_pkt,i);

}
// funkcja sprawdz, czy uzytkownik zdal test czy nie


int otworz(string nazwa) {
    fstream plik;
    plik.open(nazwa, ios::out | ios::app);
    if (plik.good() == true) {
        cout << "Udalo sie otworzyc plik pomyslnie! :D" << endl;
    }
}


void dodaj_pyt(class Pytanie *wsk)
{
    string buf;
    char buff[512];
    l_pytan++;
    getline(cin,buf);
    cout << "Zadaj pytanie:" << endl;
    getline(cin,buf);
    wsk[l_pytan].tresc=buf;
    wsk[l_pytan].nr_pytania = l_pytan+1;
    cout << "Podaj pierwsza odpowiedz" <<endl;
    getline(cin,buf);
    strcpy(buff,"a) ");
    strcat(buff,buf.c_str());
    wsk[l_pytan].a = buff;
    cout << "Podaj druga odpowiedz" <<endl;
    getline(cin,buf);
    strcpy(buff,"b) ");
    strcat(buff,buf.c_str());
    wsk[l_pytan].b = buff;
    cout << "Podaj trzecia odpowiedz" <<endl;
    getline(cin,buf);
    strcpy(buff,"c) ");
    strcat(buff,buf.c_str());
    wsk[l_pytan].c = buff;
    cout << "Podaj czwarta odpowiedz" <<endl;
    getline(cin,buf);
    strcpy(buff,"d) ");
    strcat(buff,buf.c_str());
    wsk[l_pytan].d = buff;
    cout << "Podaj poprawna odpowiedz: a dla pierwszej podanej odpowiedzi...d dla czwartej podanej odpowiedzi" <<endl;
    getline(cin,buf);
    wsk[l_pytan].odp_pop = buf;
}

int main(int argv, char *argc[])
{
    Pytanie pytania[PYT];
    int tryb;
    char funkcja;
    wprowadz(pytania);
    cout << "Witaj w QUIZIE!";
    while (1) {
        cout <<  "\n\nWybierz co chcesz zrobic poprzez wpisanie na klawiaturze odpowiedniej cyfry i zatwierdzenie jej ENTEREM" << endl;
        cout << "1 - Tryb edycji pytan\n" << "2 - Tryb rozwiazywania quizu\n" << "3 - Wyjdz z programu\n" << endl;
        cout << "Wybieram tryb:" << endl;
        cin >> tryb;
        if (tryb==1)
        {
            //cout << "Wybierz co chcesz zrobic poprzez wpisanie na klawiaturze odpowiedniej litery i zatwierdzenie jej ENTEREM" << endl;
            //cout << "a - Dodaj nowe pytanie do quizu\n";
            //cin >> funkcja;
            //if (funkcja=='a') dodaj_pyt(pytania);
            dodaj_pyt(pytania);
        }

        else if (tryb==2)
        {
            //cout << "Wybierz co chcesz zrobic poprzez wpisanie na klawiaturze odpowiedniej litery i zatwierdzenie jej ENTEREM" << endl;
            //cout << "a - Rozwiaz quiz\n";
            //cin >> funkcja;
            //if (funkcja=='a') rozw_quiz(pytania);
            rozw_quiz(pytania);
        }
        else if (tryb==3)
        {
            exit(0);
        }
    }


    return 0;
}