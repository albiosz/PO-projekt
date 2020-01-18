#include "help.h"


Help::Help(){
	addHelpLine(":q or :quit", "exit from application");
	addHelpLine(":h or :help", "get help about commands");
}


void Help::addHelpLine(std::string command, std::string instruction) {
	std::string newCommand = command;
    for (unsigned int i = 0; i < helplines.size(); i++){

        if (helplines[i].com == command) {
            std::vector<HelpLine>::iterator it = helplines.begin() + i;
            helplines.erase(it);
            continue;
        }
        else if (helplines[i].instr == instruction){
            std::vector<HelpLine>::iterator it = helplines.begin() + i;
            newCommand = helplines[i].com + " or " + command;
            helplines.erase(it);
        }

    }
    HelpLine hline = {newCommand,instruction};
    helplines.push_back(hline);
}

void Help::printHelp(){
    clear();
    move(0,0);
    printw("Help section. Commands with description:\n");
    for (HelpLine hline : helplines){
    	char com[hline.com.size() + 1];
    	char instr[hline.instr.size() + 1];
    	strcpy(com, hline.com.c_str());
    	strcpy(instr, hline.instr.c_str());
        printw("%s - %s\n",com,instr);
    }
    printw("\n\nPress a KEY to exit help section!");
    getch();
    clear();
}
