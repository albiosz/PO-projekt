//
// Created by hubert on 1/17/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_COLOREDSTRING_HPP
#define MERGE_CONFLICTS_RESOLVER_COLOREDSTRING_HPP

#include <utility>
#include <vector>
#include <string>

enum textColor {RedText = 10, YellowText, BlueText, WhiteText, CyanText};

struct coloredString
{
    std::string line;
    textColor color;

    coloredString(std::string line, textColor color) : line(std::move(line)), color(color) {}

    bool operator==(const coloredString &rhs) const {
        return line == rhs.line &&
               color == rhs.color;
    }

    bool operator!=(const coloredString &rhs) const {
        return !(rhs == *this);
    }
};

typedef std::vector<std::string> stringVector;
typedef std::vector<coloredString> coloredStringVector;


#endif //MERGE_CONFLICTS_RESOLVER_COLOREDSTRING_HPP
