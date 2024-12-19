#pragma once
#include "engine/window.h"
#include "engine/time.h"
#include "engine/log.h"


class Application
{
public:
	Application();
	~Application();
	void run();
private:
	void update(float);
	void render();
private:
	Window m_Window;
};
