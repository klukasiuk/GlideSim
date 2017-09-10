#include "physics_thread.h"

#include "time.h"


void PhysicsThread::physicsLoop()
{
	while (run)
	{
		sleep(100);
	}
}

PhysicsThread::PhysicsThread()
{
	app_thread = NULL;
	run = false;
}

void PhysicsThread::start()
{
	run = true;
	app_thread = new thread(&PhysicsThread::physicsLoop, this);
}

void PhysicsThread::stop()
{
	run = false;
	app_thread->join();

	delete app_thread;
}