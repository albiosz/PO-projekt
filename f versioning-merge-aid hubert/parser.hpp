//
// Created by hubert on 1/4/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_PARSER_HPP
#define MERGE_CONFLICTS_RESOLVER_PARSER_HPP

#include <vector>
#include <memory>
#include "conflicts.hpp"
#include "parsedCode.hpp"

parsedCode parseConflicts(const stringVector &lines)
{
    stringVector code;
    conflictsVector conflicts;

    auto isStartOfConflict = [](const std::string& line){ return line.find("<<<<<<<") != std::string::npos; };
    auto isEndOfConflict = [](const std::string& line){ return line.find(">>>>>>>") != std::string::npos; };

    auto iter = lines.begin();
    while (iter != lines.end())
    {
        auto start = std::find_if(iter, lines.end(), isStartOfConflict);
        auto end = std::find_if(start, lines.end(), isEndOfConflict);

        code.insert(code.end(), iter, start);

        iter = end;

        if (start != end) {
            stringVector tmp{start, end + 1};
            conflicts.push_back(std::make_shared<conflict>(tmp, code.size()));
            iter++;
        }
    }

    return parsedCode{std::move(code), std::move(conflicts)};
}
#endif //MERGE_CONFLICTS_RESOLVER_PARSER_HPP
