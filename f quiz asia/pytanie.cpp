//
// Created by Joanna Adamczyk on 2019-12-23.
//
#include <iostream>
#include "pytanie.h"
#include <fstream>
#include <cstdlib>


void Pytanie::wczytaj()
{
    fstream plik;
    plik.open("quiz.txt",ios::in);

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
    cout << endl << tresc << endl;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << d << endl;
    cout<< "------------------------" << endl;
    cout<< "Odpowiedz: ";
    cin >> odp_usr;
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