#include <ncurses.h>

#include "vimLike.h"
#include "oneFrontend.h"

int main(){

    OneFrontend front;
    VimLike vim(&front);
    vim.runBackend();

    return 0;
}