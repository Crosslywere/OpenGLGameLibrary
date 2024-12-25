#pragma once

#include <string>

class GameApp {
public:
	bool Create(const std::string& title, uint32_t width, uint32_t height);
	void Run();
protected:
	virtual void OnCreate() = 0;
	virtual void OnUpdate(double dt) = 0;
	virtual void OnRender() = 0;
};