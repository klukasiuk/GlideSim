#include "loader_thread.h"

#include "time.h"

void LoaderThread::load()
{
	while (run)
	{
		sleep(100);
	}
}

LoaderThread::LoaderThread()
{
	app_thread = NULL;
	run = false;
}

void LoaderThread::start()
{
	run = true;
	app_thread = new thread(&LoaderThread::load, this);
}

void LoaderThread::stop()
{
	run = false;
	app_thread->join();

	delete app_thread;
}