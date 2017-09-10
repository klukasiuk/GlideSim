#pragma once

#include <thread>


using std::thread;


class AppThread
{
protected:

	thread * app_thread;

	bool run;

public:

	virtual void start() = 0;
	virtual void stop()  = 0;
};