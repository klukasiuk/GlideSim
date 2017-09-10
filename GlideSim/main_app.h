#pragma once

#include <vector>
#include <thread>
#include <string>

#include "timer.h"
#include "render_thread.h"
#include "physics_thread.h"
#include "loader_thread.h"

using std::vector;
using std::thread;
using std::string;


class MainApplication
{
private :

	string app_name = "GlideSim";
	string version  = "dev06";

	int window_width = 1200;
	int window_height = 800;

	bool run;

	vector<AppThread> app_threads;

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