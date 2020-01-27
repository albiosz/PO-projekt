#pragma once
#include <string>
#include <vector>
#include <ncurses.h>
#include <iostream>
#include <cstring>

struct HelpLine{
	std::string com;
	std::string comment;
	std::string instr;
};


class Help{
private:
	std::vector<HelpLine> helplines;

public:
	Help();
	void addHelpLine(std::string,std::string, std::string="");
	void printHelp();
};