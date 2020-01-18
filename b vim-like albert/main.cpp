#include <ncurses.h>

#include "vimLike.h"
#include "oneFrontend.h"

int main(){

    OneFrontend front;
    VimLike vim(&front);
    //VimLike vim;
    Backend* back = &vim;
    back -> bind("<EDITION>", [&]() mutable {front.editMode2();}, "Edition mode");
    back -> bind("#vim#:a<ENTER>%some comment", [&]() mutable {front.testFunc1();},"This is sample instruction which prints 'testFunc'");
    back -> bind("#vim#:a<ENTER>",[&]() mutable {front.testFunc1();},"This is sample instruction which prints 'testFunc1'");
    back -> bind(":c<ENTER>.some comment",[&]() mutable {front.testFunc();},"This is sample instruction which prints 'testFunc'");
    back -> bind(".:d<ENTER>.some comment",[&]() mutable {front.testFunc();},"This is sample instruction which prints 'testFunc'");
    back -> bind("#nano#:ab",[&]() mutable {front.testFunc();},"This is sample instruction which prints 'testFunc'");
    back -> bind("#nano#:ab",[&]() mutable {front.testFunc();},"This is sample instruction which prints 'testFunc'");
    back -> bind("#vim#:open ${FILE_NAME}<ENTER>", &OneFrontend::methA, "Open a file from class");
    back -> bind("#vim#:save ${FILE_NAME}<ENTER>",[&]() mutable {front.testFunc();}, "Open a file");// <-- the same command but different function
    back -> bind("<ENTER>!EDIT", &OneFrontend::methA, "Open a file ctrl R");
    back -> bind("<CTRL>A", &OneFrontend::methA, "Open a file ctrl R");

    back -> bind("<CTRL>W", &OneFrontend::methA, "Open a file ctrl R");
    back -> bind("#vim#:edit!EDIT", &OneFrontend::methA, "Enter edit mode but first run methA");

    back -> runBackend();

    return 0;
}