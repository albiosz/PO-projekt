#pragma once

#include "normal.h"
#include "backend.h"
#include "frontend.h"

#include <ncurses.h>
#include <iostream>
#include <string>
#include <cstring>
#include <functional>


class VimLike : public Normal, public Backend {
private:
	char mode;

public:
	VimLike(Frontend*);
	VimLike();
	void runBackend();
	void bind(std::string,std::function<void()>, std::string);
	int findComment(std::string);
    std::string replaceSpecial(std::string);
};