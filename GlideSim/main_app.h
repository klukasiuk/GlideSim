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

	const string app_name = "GlideSim";
	const string version  = "dev05";

	int window_width = 1200;
	int window_height = 800;

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
	void stop();
};