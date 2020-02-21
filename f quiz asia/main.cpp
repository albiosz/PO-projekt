#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pytanie.h"
#include "backend.h"
#define PROG 75
#define PYT 50

int wynik = 0;
int l_pytan;
fstream plik;

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

void wprowadz(class Pytanie *p,string nazwa)
{   int i;
    int count = 0;
    l_pytan = 0;
    string linia;
    //fstream plik;
    plik.open(nazwa,ios::in);
    while (getline(plik,linia)) { count++;}
    for (i=0;i<count/5;i++) {
        p[i].nr_pytania = i + 1;
        p[i].wczytaj(nazwa);
    }
    plik.close();

    l_pytan = count/6-1 ; //pytan jest o 1 wiecej ale w tablicy obiektow numerujemy od zera
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

    return 0;
}
// funkcja sprawdz, czy uzytkownik zdal test czy nie


int otworz(string nazwa) {
    plik.open(nazwa, ios::out | ios::trunc);
    if (plik.good() == true) {
        cout << "Udalo sie otworzyc plik pomyslnie! :D" << endl;
    } else cout << "Nie udalo sie otworzyc pliku" << endl;

    return 0;
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

void zapisz_plik(class Pytanie *p)
{
    int i;
    string miejsce;
    string nazwa;
    string pelna;
    cout << "Podaj pelna sciezke miejsca, w ktorym chcesz zapisac plik z quizem:" << endl;
    cin >> miejsce;
    cout << "Podaj nazwe pliku z rozszerzeniem .txt:" << endl;
    cin >> nazwa;
    pelna = miejsce+"/"+nazwa;
    cout << pelna << endl;
    otworz(pelna);
    for (i=0; i<=l_pytan; i++)
    {
        plik << p[i].tresc << endl;
        plik << p[i].a << endl;
        plik << p[i].b << endl;
        plik << p[i].c << endl;
        plik << p[i].d << endl;
        plik << p[i].odp_pop << endl;
    }
    plik.close();



}

int main(int argv, char *argc[])
{
    Pytanie pytania[PYT];
    int tryb;
    char funkcja;
    cout << "Witaj w QUIZIE!";
    while (1) {
        cout <<  "\n\nWybierz co chcesz zrobic poprzez wpisanie na klawiaturze odpowiedniej cyfry i zatwierdzenie jej ENTEREM" << endl;
        cout << "1 - Tryb edycji pytan\n" << "2 - Tryb rozwiazywania quizu\n" << "3 - Wyjdz z programu\n" << endl;
        cout << "Wybieram tryb:" << endl;
        cin >> tryb;
        if (tryb==1)
        {
            string quiz;
            string plus = "t";
            cout << "Ktory chcesz zedytowac quiz?" << endl;
            cin >> quiz;
            wprowadz(pytania,quiz);
            while (plus == "t") {
                dodaj_pyt(pytania);
                cout << "Czy chcesz dodac kolejne pytanie? Wpisz \"t\" jesli tak, dowolny znak jesli nie:" << endl;
                cin >> plus;
            }
            cout << "Czy chcesz zapisać zedytowany przez Ciebie quiz?" << endl;
            cout << "Jeśli tak, wpisz na klawiaturze litere \"t\"\nJesli nie, wpisz litere \"n\":\n";
            cin >> funkcja;
            if (funkcja=='t') zapisz_plik(pytania);
            if (funkcja=='n') cout << "Twoj zedytowany plik nie zostal zapisany" << endl;
        }

        else if (tryb==2)
        {
            string quiz;
            cout << "Ktory chcesz uruchomic quiz? (jesli quiz jest spoza tego folderu dodaj sciezke)" << endl;
            cin >> quiz;
            wprowadz(pytania,quiz);
            rozw_quiz(pytania);

        }
        else if (tryb==3)
        {
            exit(0);
        }
    }


    return 0;
}