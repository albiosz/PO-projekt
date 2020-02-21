#pragma once
#include <string>

class Backend
{
public:
    virtual void runBackend() = 0;
    virtual void bind(std::string, std::function<void()>, std::string) = 0;
    virtual void setRefreshRoutine(std::function<void()>) = 0;
};