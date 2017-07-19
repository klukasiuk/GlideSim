#pragma once

#include <vector>
#include <thread>
#include <string>

#include "timer.h"

using std::vector;
using std::thread;
using std::string;


class MainApplication
{
private :

	bool run;

	vector<thread> app_threads;

	FpsCounter  fpsCounter;
	FpsGovernor fpsGovernor;

	void init();
	void release();

	void input();
	void update();
	void render();
	void timer();

public :

	MainApplication();

	void start();
};