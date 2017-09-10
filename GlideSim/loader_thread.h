#pragma once

#include "app_thread.h"


class LoaderThread : AppThread
{
private:

	void load();

public:

	LoaderThread();

	void start();
	void stop();
};