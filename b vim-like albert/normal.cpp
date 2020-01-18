#include "normal.h"

Normal::Normal(Frontend* front){
    getmaxyx( stdscr, rows, columns ); //Pobieranie wartości okna do zmiennych
    frontend = front;
}

void Normal::addCommand(std::string com, std::string entry, bool edit_mode, std::function<void()> func){
    for (int i=0; i < commands.size(); i++){
        if (commands[i].com == com){
            auto it = commands.begin() + i;
            commands.erase(it);
            break;
        }
    }
    commands.push_back(Command{com, entry, edit_mode, func});
}

bool Normal::chooseFunction(std::string com){

    std::string comI = com.substr(0,com.find(' '));
    
    for (Command comm : commands){
        if (comm.com == comI){
            if (comm.entry.length() > 0){

                int pos = com.find(' ');
                if (pos != std::string::npos){

                    std::string entry_value = com.substr(com.find(' ') + 1);
                    frontend -> setEntry(comm.entry, entry_value);
                }
            }

            comm.function();

            if (comm.edit_mode){
                edition();
                printMode("edit");
                editMode();
            }
            break;
        }
    }
}

char Normal::normalMode(){

	getmaxyx( stdscr, rows, columns ); //Pobieranie wartości okna do zmiennych
    std::string command="";
	do{
        printMode("normal");
        move(0,0);

        char c;
    	c = getch();
    	switch (c){
            case 'Z': // press double 'Z' to exit
                if (getch() == 'Z') return quit();
                break;
    		case ':':
    			command = write(); // command which starting with : and confirmed by enter
    			break;
    		default:
    		    if ((c>=0 && c<=31 && c!=ENTER) || (c>=65 && c<=68))
    		        command = ctrlAndArrowsHandling(c);
    		    else
                    command = std::string(1,c); // one character command
    		    break;
    	}
        move(0,0);
    	if (!command.empty()){
    		if (command == ":q" || command == ":quit") return quit();
            else if (command ==":h" || command == ":help") printHelp();
            else chooseFunction(command);

    	}
        command = "";

    } while(true);
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
		char c = getch();
		switch(c){
			case ESC:
				return "";
				break;
			case BS:
			    if (text.length() > 1) {
                    eraseChar();
                    text = text.substr(0, text.size() - 1);
                }
                break;
    		case ENTER:
    			return text;
                break;
    		default:
                printw("%c",c);
                text += c;
                // char cstr[text.size()+1];
                // strcpy(cstr, text.c_str());
                break;
		}
	}
}


void Normal::printMode(std::string mode){
    int x, y;
    getyx(stdscr, y, x);
    getmaxyx( stdscr, rows, columns ); //Pobieranie wartości okna do zmiennych
    move(rows-1,0);
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
    char c;
    while(true){
        edition();
        c = getch();
        switch(c) {
            case ESC:
                return;
            default:
                frontend->setEntry("KEY", std::string(1, c));
        }
    }

}

std::string Normal::ctrlAndArrowsHandling(char c) {
    std::string toReturn = "";
    if (c >= 0 && c <= 31)
        toReturn = "<CTRL>" + std::string(1,c+64);

    return toReturn;
}
