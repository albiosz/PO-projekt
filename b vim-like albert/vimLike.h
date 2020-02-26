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
    void runBackend() override;
	void bind(std::string,std::function<void()>, std::string) override;
	void setRefreshRoutine(std::function<void()>) override;
	int findComment(std::string);
    std::string replaceSpecial(std::string);
    void addCommand(std::string, std::string, bool edit_mode, std::function<void()>);
};