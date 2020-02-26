#include "stdafx.h"

#include "vimLike.h"
#include "Wynik.h"
#include "frontend.h"
#include "oneFrontend.h"

int main(){


    //Interfejs zmienna;
    //zmienna.start();
    Wynik frontend;
    VimLike backend(&frontend);
    backend.runBackend();

    //OneFrontend frontend;
    //VimLike backend(&frontend);
    //backend.runBackend();


    return 0;
}