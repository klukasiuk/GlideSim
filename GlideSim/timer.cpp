#include "timer.h"

#include "math.h"


Timer::Timer()
{
	startTime = 0.0;
	elapsedTime = 0.0;

	running = false;
}

Timer::~Timer()
{
}

void Timer::start()
{
	running = true;

	startTime = getTime();
}

void Timer::stop()
{
	running = false;

	elapsedTime += getTime() - startTime;
}

void Timer::reset()
{
	startTime = 0.0;
	elapsedTime = 0.0;

	running = false;
}

double Timer::getElapsedTime()
{
	if (running)
		return elapsedTime + (getTime() - startTime);
	else
		return elapsedTime;
}


FpsCounter::FpsCounter()
{
	startTime = 0.0;
	deltaTime = 0.0;
	lastTime = 0.0;

	interval = 100;

	fps = 0.0;

	running = false;
}

FpsCounter::~FpsCounter()
{
}

void FpsCounter::start()
{
	running = true;
	startTime = getTime();
	lastTime = startTime;
}

void FpsCounter::stop()
{
	running = false;
	startTime = 0;
}

void FpsCounter::frameTick()
{
	if (running == false)
	return;

	ticks++;

	double actualTime = getTime();

	if (ticks == interval)
	{
		fps = ticks / ((getTime() - startTime)/1000);

		interval = (int)fps;

		clamp(interval, 1, 100);

		startTime = actualTime;
		ticks = 0;
	}

	deltaTime = actualTime - lastTime;
	lastTime = getTime();
}

double FpsCounter::getFPS()
{
	return fps;
}

double FpsCounter::getDeltaTime()
{
	return deltaTime;
}


FpsGovernor::FpsGovernor()
{
	startTime = 0.0;
	deltaTime = 0.0;
	lastTime = 0.0;

	running = false;

	fps_limit = 0.0f;

	frame_count = 0;
}

FpsGovernor::~FpsGovernor()
{
}

void FpsGovernor::start()
{
	running = true;

	startTime = getTime();
	lastTime = startTime;
}

void FpsGovernor::stop()
{
	running = false;
}

void FpsGovernor::frameTick()
{
	if (running == false)
		return;

	double actualTime = getTime();

	double deltaTime = actualTime - lastTime;

	if (deltaTime < 1000/fps_limit)
	sleep((int)((1000 / fps_limit) - deltaTime));

	lastTime = getTime();
}

void FpsGovernor::setLimit(float limit)
{
	fps_limit = limit;
}

double FpsGovernor::getDeltaTime()
{
	return deltaTime;
}
