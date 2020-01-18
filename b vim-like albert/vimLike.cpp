#include <functional>
#include "vimLike.h"

VimLike::VimLike(Frontend* front) : Normal(front){
	mode = 0;
}

void VimLike::runBackend(){
	initscr(); //start
	noecho();
    normalMode();
    endwin();
}

void VimLike::bind(std::string key_comb, std::function<void()> func, std::string instr){
	std::string key_comb1 = key_comb;

	if (key_comb.length() <= 0) return; // if there are no characters just quit the func

	int idxOfComment = findComment(key_comb);
	if (idxOfComment == 0) return; // if it's all comment, quit
	else if (idxOfComment > 0) key_comb1 = key_comb1.substr(0,idxOfComment); // cut comment from command

	if (key_comb1.substr(0,5) == "#vim#" or key_comb[0] != '#'){

		if (key_comb1.substr(0,5) == "#vim#") // erase #vim# from command
			key_comb1 = key_comb1.substr(5);

		if (key_comb1 == "<EDITION>") {
			edition = func;
			return;
		}

		bool edit_mode = false;
		if (key_comb1.length() > 5 && key_comb1.substr(key_comb1.length()-5) == "!EDIT") {
            edit_mode = true;
            key_comb1 = key_comb1.substr(0, key_comb1.length() - 5);
        }

		addHelpLine(key_comb1,instr);

        key_comb1 = replaceSpecial(key_comb1);

		int pos_$ = key_comb1.find('$');
		if (pos_$ != std::string::npos){
			std::string entry = key_comb1.substr(pos_$);
			int start = entry.find('{');
			int length = entry.find('}') - start - 1;
			entry = entry.substr(start+1,length);

			key_comb1 = key_comb1.substr(0,pos_$ - 1);
			//std::cout << key_comb1 << "," << entry <<std::endl;

			addCommand(key_comb1, entry, edit_mode, func);

		}
		else addCommand(key_comb1, "", edit_mode, func);
	}

}

std::string VimLike::replaceSpecial(std::string key_comb){

    std::string key_comb1 = key_comb;
    if (key_comb1.length() >= 7 && key_comb1.substr(key_comb1.length()-7) == "<ENTER>"){ // erase <ENTER> from command
        key_comb1 = key_comb1.substr(0,key_comb1.length()-7);
    }

    if (key_comb1.empty()){
        std::cout << key_comb1 << " ";
        key_comb1 = "\n";
    }

    return key_comb1;
}

int VimLike::findComment(std::string command){
	for (int i = 0; i < command.length(); i++)
		if (command[i] == '%' || command[i] == '.')
			return i;

	return -1;
}