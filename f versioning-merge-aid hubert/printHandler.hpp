//
// Created by hubert on 1/17/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_PRINTHANDLER_HPP
#define MERGE_CONFLICTS_RESOLVER_PRINTHANDLER_HPP

#include "coloredString.hpp"
#include <ncurses.h>
#include <cmath>

class printHandler
{
private:
    WINDOW * codeWindow;
    WINDOW * numberWindow;
    unsigned int digits;

    static void initializeColorPairs()
    {
        start_color();
        init_pair(textColor::WhiteText, COLOR_WHITE, COLOR_BLACK);
        init_pair(textColor::BlueText, COLOR_BLUE, COLOR_BLACK);
        init_pair(textColor::YellowText, COLOR_YELLOW, COLOR_BLACK);
        init_pair(textColor::RedText, COLOR_RED, COLOR_BLACK);
        init_pair(textColor::CyanText, COLOR_CYAN, COLOR_BLACK);
    }

    void initializeWindows()
    {
        codeWindow = newwin(LINES - 2, COLS, 1, digits+1);
        numberWindow = newwin(LINES - 2, digits+1, 1, 0);
    }

    int getNoDigits(const int & number)
    {
        return number > 0 ? (int) log10 ((double) number) + 1 : 1;
    }

public:
    printHandler() : codeWindow(nullptr), numberWindow(nullptr)
    {

    }

    void setup(unsigned const int & fileLinesCount)
    {
        curs_set(0);
        initializeColorPairs();
        setFileLength(fileLinesCount);
        initializeWindows();
    }

    void printOnScreen(const coloredStringVector & lines, unsigned int index)
    {
        if (terminalResized())
            resizeWindows();

        clearWindows();
        printToWindows(lines, index);
        refreshWindows();
    }

    void printToWindows(const coloredStringVector &lines, unsigned int index) const {
        setColorW(numberWindow, textColor::YellowText);

        const int numberWidowWidth = digits + 1;
        const int codeWindowWidth = (COLS - numberWidowWidth);

        for (unsigned int i = index, printed = 0; printed < LINES - 2 and i < lines.size(); i++)
        {
            auto newLines = lines[i].line.size() / (COLS - digits + 1) + 1;
            printed += newLines;
            auto humanLineIndex = i + 1;

            wprintw(numberWindow, "%*d", digits, humanLineIndex);
            for (; newLines; newLines--, waddch(numberWindow, '\n'));

            setColorW(codeWindow, lines[i].color);
            wprintw(codeWindow, "%s\n", lines[i].line.c_str());
        }
    }

private:

    static void setColorW(WINDOW * win, textColor color)
    {
        wattron(win, COLOR_PAIR(color));
    }

    void clearWindows() const {
        wclear(codeWindow);
        wclear(numberWindow);
    }

    void refreshWindows() const {
        wrefresh(numberWindow);
        wrefresh(codeWindow);
    }

    void setFileLength(unsigned const int & fileLinesCount)
    {
        digits = getNoDigits(fileLinesCount);
    }

    void resizeWindows()
    {
        wresize(codeWindow, LINES - 2, COLS);
        wresize(numberWindow, LINES - 2, digits+1);
    }

    bool terminalResized()
    {
        auto x = getmaxx(codeWindow);
        auto y = getmaxy(codeWindow);
        return x != COLS or y != LINES - 2;
    }

};

#endif //MERGE_CONFLICTS_RESOLVER_PRINTHANDLER_HPP
