#pragma once
#include "./frontend.h"
#include "./mainForMerge.cpp"
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
        auto refresh = [this]() { this->tooldvc.refreshR(); };
        auto addLetter = [this]() { this->tooldvc.mainFoo(entries["KEY"]);};
        auto start = [](){};

        obj->setRefreshRoutine(refresh);
        obj->bind("<EDITION>", addLetter, "text editing");
        obj->bind("<ENTER>!EDIT", start, "hello");
    }
};