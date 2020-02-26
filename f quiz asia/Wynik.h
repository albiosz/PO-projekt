#pragma once

#include "stdafx.h"
#include "pytanie.h"
#include "backend.h"

using namespace std;

#define PROG 75
#define PYT 50
#define ENTER 10
int l_pytan;
Pytanie pytania[PYT];

class Quiz : public Pytanie
{


public:
    int wynik = 0;

    fstream plik;


    void zdaneczynie(float a,int b)
    {
        float procent;
        procent = a/b*100;
        if (procent >= PROG)
        {
            cout << "Brawo, zaliczyles test! :)" << endl << "\r";
        }
        else {cout << "Niestety, nie zaliczyles testu :(" << endl << "\r";}
        cout << "Twoja suma punktow: " << a << "\n\r" << "Twoj wynik procentowy: " << procent << "%" << endl << "\r";
        cout << "Aby zdac test powinienes uzyskac przynajmniej " << PROG << "%" << endl << "\r";
    }



    int otworz(string nazwa) {
        plik.open(nazwa, ios::out | ios::trunc);
        if (plik.good()) {
            printw("%s\n\r","Udalo sie otworzyc plik pomyslnie! :D");
        } else
            printw("%s\n\r","Nie udalo sie otworzyc pliku");

        return 0;
    }






};

class Interfejs : public Quiz
{
public:

    int tryb;
    char funkcja;
    int rows, columns;
    static void eraseChar(){
        int x,y;
        getyx(curscr,y,x);
        move(y,--x);
        delch();
    }

    void zapisz_plik(Pytanie *p,const std::string& nazwa)
    {
        int i;
        string buf;
        zeruj();
        otworz(nazwa);
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
        printw("%s\n\r","Wcisnij ENTER zeby kontynuowac");
        buf = edycja();
        clear();
    }

    void wprowadz(Pytanie *p, const std::string& nazwa)
    {   int i;
        int count = 0;
        l_pytan = 0;
        string linia;
        plik.open(nazwa,ios::in);
        while (getline(plik,linia)) { count++;}
        for (i=0;i<count/5;i++) {
            p[i].nr_pytania = i + 1;
            p[i].wczytaj(nazwa);
        }
        plik.close();

        l_pytan = count/6-1 ; //pytan jest o 1 wiecej ale w tablicy obiektow numerujemy od zera
    }

    void witaj()
    {
        cout << "Witaj w QUIZIE!\n\r";
        cout << "\n\rWybierz co chcesz zrobic poprzez wpisanie odpowiedniej komendy na klawiaturze\n\r";
        cout << ":d nazwa_quizu.txt - Tryb edycji pytan\n\r";
        cout << ":r nazwa_quizu.txt - Tryb rozwiazywania quizu\n\r";
        cout << ":z /pelna/sciezka/quizu.txt lub nazwa_quizu.txt - Zapisywanie quizu\n\r";
        cout << ":s nazwa_quizu.txt - Zaladuj quiz z pliku do struktury\n\r";
        cout << "c - Odswierz ekran\n\r";


    }

    int rozw_quiz(Pytanie *p, const std::string& nazwa)
    {
        int i;
        int suma_pkt = 0; //suma zdobytych punktow
        static int x=0,y=0;// position of a cursor
        int a;
        string buf;
        getmaxyx( stdscr, rows, columns );//Fetching window size to variables rows and columns
        a = rows-1;
        clear();
        move(a,0);
        printw("-- Rozwiazywanie quizu --");
        move(y,x);
        wprowadz(p,nazwa);
        for (i = 0; i <= l_pytan; i++) {
            refresh();
            p[i].zadaj();
            p[i].sprawdz();
            suma_pkt += p[i].punkt;
        } // tworzymy liste obietkow, czyli pytan ;)
        wynik = suma_pkt;
        cout << endl << "\r" << "KONIEC QUIZU!\n\r";
        zdaneczynie(suma_pkt,i);
        printw("%s\n\r","Wcisnij ENTER zeby wyjsc z trybu rozwiazywania quizu");
        buf = edycja();
        clear();


        return 0;
    }

    int dodaj_pyt(Pytanie *wsk,const std::string& nazwa) {
        static int x = 0, y = 0;// position of a cursor
        int a;
        getmaxyx(stdscr, rows, columns);//Fetching window size to variables rows and columns
        clear();
        a = rows - 1;
        move(a, 0);
        clrtoeol();
        printw("-- Edycja quizu --");
        move(x, y);
        wprowadz(wsk, nazwa);
        string buf;
        char buff[512];
            l_pytan++;
            move(0, 0);
            printw("%s\n\r", "Zadaj pytanie");
            //cout << "\n\r" << "Zadaj pytanie:" << endl << "\r";
            buf = edycja();
            wsk[l_pytan].tresc = buf;
            wsk[l_pytan].nr_pytania = l_pytan + 1;
            cout << "\n\r" << "Podaj pierwsza odpowiedz" << endl << "\r";
            getyx(stdscr, rows, columns);
            move(rows, 0);
            buf = edycja();
            strcpy(buff, "a) ");
            strcat(buff, buf.c_str());
            wsk[l_pytan].a = buff;
            cout << "\n\r" << "Podaj druga odpowiedz" << endl << "\r";
            getyx(stdscr, rows, columns);
            move(rows, 0);
            buf = edycja();
            strcpy(buff, "b) ");
            strcat(buff, buf.c_str());
            wsk[l_pytan].b = buff;
            cout << "\n\r" << "Podaj trzecia odpowiedz" << endl << "\r";
            getyx(stdscr, rows, columns);
            move(rows, 0);
            buf = edycja();
            strcpy(buff, "c) ");
            strcat(buff, buf.c_str());
            wsk[l_pytan].c = buff;
            cout << "\n\r" << "Podaj czwarta odpowiedz" << endl << "\r";
            getyx(stdscr, rows, columns);
            move(rows, 0);
            buf = edycja();
            strcpy(buff, "d) ");
            strcat(buff, buf.c_str());
            wsk[l_pytan].d = buff;
            cout << "\n\r"
                 << "Podaj poprawna odpowiedz: a dla pierwszej podanej odpowiedzi...d dla czwartej podanej odpowiedzi"
                 << endl << "\r";
            getyx(stdscr, rows, columns);
            move(rows, 0);
            buf = edycja();
            wsk[l_pytan].odp_pop = buf;

        printw("\n\r%s\n\r", "Wcisnij ENTER zeby wyjsc z trybu edycji quizu");
        buf = edycja();
        clear();

        return 0;
    }

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

    void refreshRoutine(){
        static int refreshed = 0;
        getmaxyx( stdscr, rows, columns ); //Fetching window size to variables rows and columns
        move(5, 0);
        //printw("Refreshed%d!",refreshed);
        refreshed++;
    }


    void editMode(){
        static int x=0,y=0; // position of a cursor
        getmaxyx( stdscr, rows, columns ); //Fetching window size to variables rows and columns
        move(rows-1,0);
        clrtoeol();
        printw("-- Edit Mode --");
        move(y,x);
        char c;
        do{
            c = getch();
            switch (c){
                case 27:
                    getyx(curscr,y,x);
                    return;
                    break;
                case 127:
                    eraseChar();
                    break;
                default:
                    printw("%c",c);
                    break;
            }

        } while(true);
    }

    void zeruj()
    {
        clear();
    }


};


class Wynik : public Frontend
{
public:

    int rows, columns;

    void refreshRoutine(){
        static int refreshed = 0;
        getmaxyx( stdscr, rows, columns ); //Fetching window size to variables rows and columns
        move(0, 0);
        //printw("Refreshed%d!",refreshed);
        refreshed++;
    }


    void setEntry(std::string key, std::string value) override {
        entries[key] = value;
    }

    std::string getEntry(std::string string) override {
        return entries[string];

    }

    void setBackend(Backend *obj) override {

        auto witaj = [this]() { this->res.witaj();};
        auto struktura = [this](){ this->res.wprowadz(pytania,entries["filename"]);};
        auto rozw = [this](){this ->res.rozw_quiz(pytania,entries["filename"]);};
        auto zapisz = [this](){this ->res.zapisz_plik(pytania,entries["filename"]);};
        auto dodaj = [this](){this ->res.dodaj_pyt(pytania,entries["filename"]);};
        auto zer = [this]() { this->res.zeruj();};


        obj -> setRefreshRoutine([&]()mutable {this -> refreshRoutine();});

        obj -> bind("w", witaj, "Powitalny tekst");
        obj -> bind("#vim#:r ${filename}<ENTER>",rozw,"Rozwiaz quiz");
        obj -> bind("#vim#:d ${filename}<ENTER>", dodaj, "Tryb edycji, dodaj pytanie");
        obj -> bind("#vim#:z ${filename}<ENTER>", zapisz, "Zapisuje do pliku");
        obj -> bind("#vim#:s ${filename}<ENTER>", struktura, "Wprowadza pytania do struktury");
        obj -> bind("c", zer, "Wprowadza pytania do struktury");

    }
private:

    Interfejs res;
    Quiz wsk;
    std::map<std::string, std::string> entries;


};

