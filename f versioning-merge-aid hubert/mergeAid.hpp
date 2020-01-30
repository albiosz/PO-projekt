//
// Created by hubert on 1/20/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_MERGEAID_HPP
#define MERGE_CONFLICTS_RESOLVER_MERGEAID_HPP

#include <string>
#include <map>
#include "../backend.h"
#include "../frontend.h"
#include "resolver.hpp"

class mergeAid : public Frontend
{
public:
    void setEntry(std::string key, std::string value) override {
        entries[key] = value;
    }

    std::string getEntry(std::string string) override {
        return entries[string];
    }

    void setBackend(Backend *obj) override {
        auto loadFile = [this](){ this->res.load(entries["filename"]);};
        auto writeFile = [this](){ this->res.save(entries["filename"]);};
        auto nextLine =[this](){ this->res.nextLine();};
        auto previousLine =[this](){ this->res.previousLine();};
        auto nextConflict =[this](){ this->res.nextConflict();};
        auto previousConflict =[this](){ this->res.previousConflict();};
        auto revert = [this](){ this->res.revertCurrent();};
        auto toNew = [this](){ this->res.mergeCurrentToNew();};
        auto toOld = [this](){ this->res.mergeCurrentToOld();};
        auto toBoth = [this](){ this->res.mergeCurrentToBoth();};
        auto toBothR = [this](){ this->res.mergeCurrentToBothR();};
        auto find = [this](){ this->res.find(entries["template"]); };
        auto nextFound = [this](){ this->res.nextFound(); };
        auto previousFound = [this](){this->res.previousFound();};
        auto refreshRoutine = [this](){ this->res.printToTerminal();};

        obj->setRefreshRoutine(refreshRoutine);

        obj -> bind("#vim#:o ${filename}<ENTER>", loadFile, "Open and load file");
        obj -> bind("#vim#:wa ${filename}<ENTER>", writeFile, "Write to file given name");
        obj -> bind("#vim#:w<ENTER>", writeFile, "Write to file");
        obj -> bind("#vim#j", nextLine, "Jump to next line");
        obj -> bind("#vim#<DOWN>", nextLine, "Jump to next line");
        obj -> bind("#vim#k", previousLine, "Jump to previous line");
        obj -> bind("#vim#<UP>", previousLine, "Jump to previous line");
        obj -> bind("#vim#l", nextConflict, "Jump to next conflict and select");
        obj -> bind("#vim#<RIGHT>", nextConflict, "Jump to next conflict and select");
        obj -> bind("#vim#h", previousConflict, "Jump to previous conflict and select");
        obj -> bind("#vim#<LEFT>", previousConflict, "Jump to previous conflict and select");
        obj -> bind("#vim#1", revert, "Revert selected conflict to default state");
        obj -> bind("#vim#2", toNew, "Solve selected conflict choosing new version");
        obj -> bind("#vim#3", toOld, "Solve selected conflict choosing old version");
        obj -> bind("#vim#4", toBoth, "Solve selected conflict choosing two options, old first");
        obj -> bind("#vim#5", toBothR, "Solve selected conflict choosing two options, new first");
        obj -> bind("#vim#:f ${template}<ENTER>", find, "Find given template in conflicts");
        obj -> bind("#vim#h", nextFound, "Jump to next found");
        obj -> bind("#vim#d", previousFound, "Jump to next found");
    }

private:
    resolver res;
    std::map<std::string, std::string> entries;
};

#endif //MERGE_CONFLICTS_RESOLVER_MERGEAID_HPP
