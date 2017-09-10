#include "render_thread.h"

RenderThread::RenderThread()
{
	app_thread = NULL;
	run = false;
}

void RenderThread::init()
{
}

void RenderThread::release()
{
}

void RenderThread::render_loop()
{
	init();

	while (run)
	{
		printf("Dupa\n");
	}

	release();
}

void RenderThread::start()
{
	run = true;
	app_thread = new thread(&RenderThread::render_loop, this);
}

void RenderThread::stop()
{
	run = false;
	app_thread->join();

	delete app_thread;
}