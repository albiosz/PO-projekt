#include "normal.h"

Normal::Normal(Frontend* front){
    getmaxyx( stdscr, rows, columns ); //Pobieranie wartości okna do zmiennych
    frontend = front;
}

char Normal::normalMode(){
	do{
        std::string command="";
        printMode("normal");
        getmaxyx( stdscr, rows, columns ); //Pobieranie wartości okna do zmiennych

        int c;
        move(rows-1,0);
        c = getch();
    	switch (c){
            case 'Z': // press double 'Z' to exit
                if (getch() == 'Z') return quit();
                break;
    		case ':':
    			command = write(); // command which starting with : and confirmed by enter
    			break;
    		default:
    		    command = oneCharHandling(c);
    		    break;
    	}

    	if (!command.empty()){
    		if (command == ":q" || command == ":quit")
    		    return quit();
            else if (command ==":h" || command == ":help")
                printHelp();
            else
                chooseFunction(command);
    	}

    	clear();
        refreshRoutine();

    } while(true);
}

bool Normal::chooseFunction(const std::string com){

    std::string comI = com.substr(0,com.find(' '));

    if (commands.find(comI) != commands.end()){
        if (commands[comI].entry.length() > 0){

            unsigned int pos = com.find(' ');
            if (pos != std::string::npos){
                std::string entry_value = com.substr(pos + 1);
                frontend -> setEntry(commands[comI].entry, entry_value);
            } else {
                getmaxyx( stdscr, rows, columns ); //Pobieranie wartości okna do zmiennych
                move(rows-2,0);
                clrtoeol();
                printw("ERROR: Invoked function without parameter!");
                return false;
            }
        }

        commands[comI].function();

        if (commands[comI].edit_mode){
            printMode("edit");
            editMode();
        }

        return true;
    }
    return false;
}

char Normal::quit(){
    if (frontend -> getEntry("IS_SAVED") == "NO"){
        move(rows-1,0);
        clrtoeol();
        printw("Unsaved files! If you want to exit press 'y': ");
        char c = getch();
        if (c != 'y') return 0;
    }
    return -1;
}

std::string Normal::write(){
	move(rows-1,0);
    clrtoeol();
    printw(":");
    std::string text = ":";
	while(true){
		int c = getch();
		switch(c){
			case ESC:
				return "";
			case KEY_BACKSPACE:
			    if (text.length() > 1) {
                    eraseChar();
                    text = text.substr(0, text.size() - 1);
                }
                break;
    		case ENTER:
    			return text;
    		default:
                printw("%c",c);
                text += c;
		}
	}
}


void Normal::printMode(std::string mode){
    int x, y;
    getyx(stdscr, y, x);
    getmaxyx( stdscr, rows, columns ); //Pobieranie wartości okna do zmiennych
    move(rows-1,columns - 17);
    clrtoeol();
    if (mode == "normal")
        printw("-- Normal Mode --");
    else if (mode == "edit")
        printw("-- Edit Mode --");
    move(y,x);
}

void Normal::eraseChar(){
    int x,y;
    getyx(curscr,y,x);
    move(y,--x);
    delch();
}

void Normal::editMode() {
    while (true) {
        int c;
        c = getch();
        switch (c) {
            case ESC:
                return;
            default:
                frontend->setEntry("KEY", oneCharHandling(c));
                edition();
        }
        clear();
        refreshRoutine();
    }
}

std::string Normal::oneCharHandling(int c) {
    printw("%d",c);
    switch(c){
        case KEY_UP:
            return "<UP>";
        case KEY_DOWN:
            return "<DOWN>";
        case KEY_LEFT:
            return "<LEFT>";
        case KEY_RIGHT:
            return "<RIGHT>";
        case KEY_BACKSPACE:
            return "<BACKSPACE>";
        default: // it is considered as a ctrl by default
            if (c == ENTER)
                return "<ENTER>";
            else if (c>=0 && c<=31)
                return "<CTRL>" + std::string(1,c+64);
            else if (c >= 32 && c <= 126)
                return std::string(1,c);
    }
}
