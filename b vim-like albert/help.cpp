#include "help.h"


Help::Help(){
	addHelpLine(":q or :quit", "exit from application");
	addHelpLine(":h or :help", "get help about commands");
}


void Help::addHelpLine(std::string command, std::string instruction, std::string comment) {
	std::string newCommand = command;
    for (unsigned int i = 0; i < helplines.size(); i++){

        if (helplines[i].com == command) {
            auto it = helplines.begin() + i;
            helplines.erase(it);
            continue;
        }
        else if (helplines[i].instr == instruction){
            newCommand = helplines[i].com + " or " + command;
            auto it = helplines.begin() + i;
            helplines.erase(it);
        }

    }
    HelpLine hline = {newCommand,comment,instruction};
    helplines.push_back(hline);
}

void Help::printHelp(){
    clear();
    move(0,0);
    printw("Help section. Commands with description:\n");
    for (HelpLine hline : helplines){
    	char com[hline.com.size() + hline.comment.size() + 1];
    	char instr[hline.instr.size() + 1];
    	strcpy(com, (hline.com + hline.comment).c_str());
    	strcpy(instr, hline.instr.c_str());
        printw("%s - %s\n",com,instr);
    }
    printw("\n\nPress a KEY to exit help section!");
    getch();
    clear();
}
