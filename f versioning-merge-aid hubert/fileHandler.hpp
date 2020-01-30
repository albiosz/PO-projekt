//
// Created by hubert on 1/4/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_FILEHANDLER_HPP
#define MERGE_CONFLICTS_RESOLVER_FILEHANDLER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

std::vector<std::string> readLinesFromFile(const std::string& filename)
{
    std::fstream file(filename, std::ios::in);
    std::vector<std::string> data;

    for (std::string buff; std::getline(file,buff);) {
        data.emplace_back(std::move(buff));
    }

    return data;
}

void writeLinesToFile(const std::vector<std::string>& newData, const std::string& filename)
{
    std::fstream file(filename, std::ios::out | std::ios::trunc);
    std::for_each(newData.begin(), newData.end(), [&file](const std::string& item){ file << item << "\n"; });
}

#endif //MERGE_CONFLICTS_RESOLVER_FILEHANDLER_HPP
