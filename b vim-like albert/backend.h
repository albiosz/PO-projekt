#pragma once
#include <string>
#include <functional>

class Backend
{
public:
	virtual void runBackend() = 0;
	virtual void bind(std::string, std::function<void()>, std::string) = 0;
	virtual void setRefreshRoutine(std::function<void()>) = 0;
};
