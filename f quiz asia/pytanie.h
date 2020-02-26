//
// Created by Joanna Adamczyk on 2019-12-23.
//
#pragma once
#include "stdafx.h"
#define ENTER 10

using namespace std;

string edycja()
{
    string a="";
    char c;
    while(ENTER != (c = getch()))
    {
        printw("%c",c);
        a += c;
        if(c == ESC)
        {
            printw("\n\r");
            break;
        }
    }
    return a;

}

class Pytanie
{
public:
    string tresc; //przechowuje tresc pytania
    string a,b,c,d; //przechowuje odpowiedzi
    int nr_pytania; //przechowuje nr pytania
    string odp_pop; //przechowuje poprawna odpowiedz
    string odp_usr; //przechowuje odpowiedz podana przez uzytkownika
    int punkt; //0 lub 1, zla lub dobra odpowiedz



    void wczytaj(string nazwa); //fcja wczytuje dane z pliku
    void zadaj(); //fcja zada pytanie uzytkownikowi, wyswietli je na ekranie
    void sprawdz(); //fcja sprawdzi, czy uzytkownik dobrze odpowiedzial
};

void Pytanie::wczytaj(string nazwa)
{
    fstream plik;
    plik.open(nazwa,ios::in);

    if(!plik.good())
    {
        cout<<"Nie mozna otworzyc pliku!";
        exit(0); //konczymy prace programu
    }

    int nr_linii=(nr_pytania-1)*6+1;
    int aktualny_nr=1;
    string linia;

    while(getline(plik,linia))
    {
        if(aktualny_nr==nr_linii) tresc=linia;
        if(aktualny_nr==nr_linii+1) a=linia;
        if(aktualny_nr==nr_linii+2) b=linia;
        if(aktualny_nr==nr_linii+3) c=linia;
        if(aktualny_nr==nr_linii+4) d=linia;
        if(aktualny_nr==nr_linii+5) odp_pop=linia;
        aktualny_nr++;
    }

    plik.close();

}

void Pytanie::zadaj()
{
    cout << endl << "\r" << tresc << endl << "\r";
    cout << a << endl << "\r";
    cout << b << endl << "\r";
    cout << c << endl << "\r";
    cout << d << endl << "\r";
    cout<< "------------------------" << endl << "\r";
    cout<< "Odpowiedz: ";
    //cin >> odp_usr;
    odp_usr = edycja();

}




void Pytanie::sprawdz()
{
    transform(odp_usr.begin(),odp_usr.end(),odp_usr.begin(),::tolower); //gdyby uzytkownik mial wlaczony capslock, fcja zmieni duza litere na mala
    if(odp_usr==odp_pop)
    {
        punkt=1;
    }
    else punkt=0;
}
