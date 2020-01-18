#pragma once
#include <ncurses.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <functional>

#include "help.h"
#include "frontend.h"

#define ENTER 10
#define BS 127
#define ESC 27

struct Command{
	std::string com;
	std::string entry;
	bool edit_mode;
	std::function<void()> function;
};

struct Key
{
    std::string text;
    int num;
};

const Key keys[] {Key{"<ENTER>", 10}, Key{"<ESC>", 27}};

class Normal : public Help {
private:
	int columns,rows; // rozmiary okna
	std::vector<Command> commands;
	std::string write();
	Frontend *frontend;
	void printMode(std::string);

protected:
	std::function<void()> edition;

public:
	Normal(Frontend* front);
	char normalMode();
	void editMode();
	void addCommand(std::string, std::string, bool edit_mode, std::function<void()>);
	bool chooseFunction(std::string com);
	void eraseChar();
	char quit();
    std::string ctrlAndArrowsHandling(char c);
};