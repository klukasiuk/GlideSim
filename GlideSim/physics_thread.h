#pragma once

#include "app_thread.h"


class PhysicsThread : AppThread
{
private:

	void physicsLoop();

public:

	PhysicsThread();

	void start();
	void stop();
};