#pragma once
#include <ncurses.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <functional>
#include <map>

#include "help.h"
#include "frontend.h"

#define ENTER 10
#define ESC 27

struct Command{
	std::string entry;
	bool edit_mode;
	std::function<void()> function;
};

//adsfasdf

class Normal : public Help {
private:
	int columns,rows; // rozmiary okna
	std::string write();
	void printMode(std::string);

protected:
	std::function<void()> edition;
	std::function<void()> refreshRoutine;
    std::map<std::string, Command> commands;
    Frontend *frontend;

public:
	Normal(Frontend* front);
	char normalMode();
	void editMode();
	bool chooseFunction(std::string com);
	void eraseChar();
	char quit();
    std::string oneCharHandling(int c);
};