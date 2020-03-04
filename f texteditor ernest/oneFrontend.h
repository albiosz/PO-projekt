#pragma once
#include "./frontend.h"
#include "./mainForMerge2.cpp"
class OneFrontend : public Frontend{
private:
    texteditor tooldvc;
    std::map<std::string, std::string> entries;
public:
    void setEntry(std::string key, std::string value) override {
        entries[key] = value;
    }

    std::string getEntry(std::string string) override {
        return entries[string];
    }

    void setBackend(Backend *obj) {
        auto jumper = [this](){this->tooldvc.jumpToline(entries["FILE_NAME"]);};
        auto entLdPath = [this](){this->tooldvc.setPathl(entries["FILE_NAME"]);};
        auto entSvPath = [this](){this->tooldvc.setPaths(entries["FILE_NAME"]);};
        auto refresh = [this]() { this->tooldvc.refreshR();};
        auto undo = [this](){this->tooldvc.undo();};
        auto undoundo = [this](){this->tooldvc.undoUndo();};
        auto addLetter = [this]() { this->tooldvc.mainFoo(entries["KEY"]);};
        auto save = [this](){this->tooldvc.saving();};
        auto load = [this](){this->tooldvc.load();};
        auto findIT = [this](){this->tooldvc.findIT(entries["FILE_NAME"]);};
        auto start = [](){};

        obj->setRefreshRoutine(refresh);
        obj->bind("#vim#:f ${FILE_NAME}<ENTER>",findIT,"allows to check if given pattern is in the text");
        obj->bind("#vim#:udud<ENTER>", undoundo, "undo last undo");
        obj->bind("#vim#:ud<ENTER>",undo,"this command undo last change of a buffer");
        obj->bind("#vim#:j ${FILE_NAME}<ENTER>",jumper,"jumping to given line");
        obj->bind("#vim#:l<ENTER>",load,"loading buffer from a chosen location");
        obj->bind("#vim#:s<ENTER>",save,"saving state of the buffer in a chosen document");
        obj->bind("#vim#:elp ${FILE_NAME}<ENTER>",entLdPath, "allows to enter wanted path for loading");
        obj->bind("#vim#:esp ${FILE_NAME}<ENTER>",entSvPath,"allows to enter wanted path for saving");
        obj->bind("<EDITION>", addLetter, "text editing");
        obj->bind("<ENTER>!EDIT", start, "hello");
    }
};