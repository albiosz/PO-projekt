#pragma once
#include <ncurses.h>

class Backend;

class Frontend {
  public:
  	virtual void setEntry(std::string,std::string) = 0;
  	virtual std::string getEntry(std::string) = 0;
  	virtual void setBackend( Backend * obj) = 0;
};