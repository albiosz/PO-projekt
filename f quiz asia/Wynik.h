#pragma once

#include "stdafx.h"
#include "pytanie.h"
#include "backend.h"

#define PROG 75
#define PYT 50


class Quiz : public Pytanie
{


public:
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


    // funkcja sprawdz, czy uzytkownik zdal test czy nie


    int otworz(string nazwa) {
        plik.open(nazwa, ios::out | ios::trunc);
        if (plik.good()) {
            cout << "Udalo sie otworzyc plik pomyslnie! :D" << endl;
        } else cout << "Nie udalo sie otworzyc pliku" << endl;

        return 0;
    }


    void wprowadz(Pytanie *p, string nazwa)
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

// funkcja przeprowadza test i sumuje uzyskana liczbe punktow
int rozw_quiz(Pytanie *p)
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

    void dodaj_pyt(Pytanie *wsk)
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

    void zapisz_plik(Pytanie *p)
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



};

class Interfejs : public Quiz
{
public:
    Pytanie pytania[PYT];
    int tryb;
    char funkcja;
    int rows, columns;
    static void eraseChar(){
        int x,y;
        getyx(curscr,y,x);
        move(y,--x);
        delch();
    }



    void start()
    {
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
    }

    void wprowadz(Pytanie *p, string nazwa)
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
        move(0,0);
        printw("%s\n", "Witaj w QUIZIE!");
        printw("%s\n", "\nWybierz co chcesz zrobic poprzez wpisanie na klawiaturze odpowiedniej cyfry i zatwierdzenie jej ENTEREM");
        printw("%s\n", "1 - Tryb edycji pytan");
        printw("%s\n", "2 - Tryb rozwiazywania quizu");
        printw("%s\n", "3 - Wyjdz z programu");
    }

    void edycja(const std::string& quiz) {
        move(7, 0);
        printw("%s\n", "Ktory chcesz zedytowac quiz?");
        wprowadz(pytania, quiz);

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

    void dodaj_pyt(Pytanie *wsk)
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

};


class Wynik : public Frontend
{
public:

    Pytanie pytania[PYT];
    int rows, columns;

    void refreshRoutine(){
        static int refreshed = 0;
        getmaxyx( stdscr, rows, columns ); //Fetching window size to variables rows and columns
        move(10, 0);
        printw("Refreshed%d!",refreshed);
        refreshed++;
    }


    void setEntry(std::string key, std::string value) override {
        entries[key] = value;
    }

    std::string getEntry(std::string string) override {
        return entries[string];
    }

    void setBackend(Backend *obj) override {

        auto witaj = [&]() { this->res.witaj();};
        auto edycja = [this](){ this->res.edycja(entries["filename"]);};
        auto edit = [this](){ this->res.editMode();};
        auto dodaj = [this](){ this->res.dodaj_pyt(pytania);};


        obj -> setRefreshRoutine([&]()mutable {this -> refreshRoutine();});
        obj -> bind("w", witaj, "Powitalny tekst");
        obj -> bind("e",edit,"Tryb edytowania");
        obj -> bind("1 ${filename}<ENTER>", edycja, "Edycja pytan");
        obj -> bind("2",dodaj,"Dodaj pytanie");
    }
private:

    Interfejs res;
    Quiz wsk;
    std::map<std::string, std::string> entries;


};

