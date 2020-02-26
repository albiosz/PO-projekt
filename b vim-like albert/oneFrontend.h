#pragma once
#include "frontend.h"

class OneFrontend : public Frontend {
private:
    int test_var;
    int rows, columns;
	static void eraseChar(){
        int x,y;
        getyx(curscr,y,x);
        move(y,--x);
        delch();
	}

public:
    OneFrontend(){
	    test_var = 125;
	}
	//void setEntry(std::string entry, std::string entry_value) override {std::cout << "Entry's been set. " << "Entry: " << entry << " Entry value: " << entry_value << std::endl;}
	void setEntry(std::string entry, std::string entry_value) override {move(1,0); printw("Entry set: %s\n", entry_value.c_str());}
	std::string getEntry(std::string) override {move(1,0); printw("Entry get\n"); return "YES";}

	static void methA(){
		move(0,0);
	    printw("%s\n", "method A");
	}

	void editMode2(){
	    int y, x;
	    getyx(stdscr, y, x);
		printw("Welcome in eddition mode! Type whatever you want%d!\n",test_var);
	}

    void testFunc(){
        move(0,0);
        printw("%s\n", "testFunc");
    }

    void testFunc1(){
        move(0,0);
        printw("%s\n", "testFunc1");
    }

    void refreshRoutine(){
	    static int refreshed = 0;
        getmaxyx( stdscr, rows, columns ); //Fetching window size to variables rows and columns
        move(5, 0);
        printw("Refreshed%d!",refreshed);
        refreshed++;
	}

    void setBackend( Backend * back){
        back -> setRefreshRoutine([&]() mutable {this -> refreshRoutine();});

        back -> bind("<EDITION>", [&]() mutable {this -> editMode2();}, "Edition mode");
        back -> bind("#vim#:a<ENTER>%some comment", [&]() mutable {this -> testFunc();},"This is sample instruction which prints 'testFunc'");
        back -> bind("#vim#:a<ENTER>", [&]() mutable {this -> testFunc1();},"This is sample instruction which prints 'testFunc'");
        back -> bind("#vim#a",[&]() mutable {this -> testFunc1();},"This is sample instruction which prints 'testFunc1'");
        back -> bind(":c<ENTER>.some comment",[&]() mutable {this -> testFunc();},"This is sample instruction which prints 'testFunc'");
        back -> bind(".:d<ENTER>.some comment",[&]() mutable {this -> testFunc();},"This is sample instruction which prints 'testFunc'");
        back -> bind("#nano#:ab",[&]() mutable {this -> testFunc();},"This is sample instruction which prints 'testFunc'");
        back -> bind("#nano#:ab",[&]() mutable {this -> testFunc();},"This is sample instruction which prints 'testFunc'");
        back -> bind("#vim#:open ${FILE_NAME}<ENTER>", &OneFrontend::methA, "Open a file from class");
        back -> bind("#vim#:save ${FILE_NAME}<ENTER>",[&]() mutable {this -> testFunc();}, "Open a file");// <-- the same command but different function
        back -> bind("<ENTER>!EDIT", [&]() mutable {this -> testFunc();}, "Open a file ctrl R");
        back -> bind("<CTRL>A!EDIT", [&]() mutable {this -> testFunc();}, "Open a file ctrl R");
        back -> bind("<UP>", [&]() mutable {this -> testFunc();}, "Open a file ctrl R");
        back -> bind("<DOWN>!EDIT", [&]() mutable {this -> testFunc();}, "Open a file ctrl R");
        back -> bind("<LEFT>", [&]() mutable {this -> testFunc();}, "Open a file ctrl R");
        back -> bind("<RIGHT>", [&]() mutable {this -> testFunc();}, "Open a file ctrl R");
        back -> bind("1", [&]() mutable {this -> testFunc();}, "Open a file ctrl R");


    };
};