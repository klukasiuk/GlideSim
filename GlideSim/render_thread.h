#pragma once

#include "app_thread.h"

class RenderThread : AppThread
{
private :

	void init();
	void release();

	void render_loop();

public :

	RenderThread();

	void start();
	void stop();
};