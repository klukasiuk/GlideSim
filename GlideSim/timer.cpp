#include "timer.h"

#include "math.h"



Timer::Timer()
{
	StartTime = 0.0;
	ElapsedTime = 0.0;

	running = false;
}

Timer::~Timer()
{
}

void Timer::Start()
{
	running = true;

	StartTime = getTime();
}

void Timer::Stop()
{
	running = false;

	ElapsedTime += getTime() - StartTime;
}

void Timer::Reset()
{
	StartTime = 0.0;
	ElapsedTime = 0.0;

	running = false;
}

double Timer::getElapsedTime()
{
	if (running)
		return ElapsedTime + (getTime() - StartTime);
	else
		return ElapsedTime;
}



FpsCounter::FpsCounter()
{
	StartTime = 0.0;

	interval = 100;

	fps = 0.0;

	running = false;

	DeltaTime = 0.0;
	LastTime = 0.0;
}

FpsCounter::~FpsCounter()
{
}

void FpsCounter::Start()
{
	running = true;
	StartTime = getTime();
	LastTime = StartTime;
}

void FpsCounter::Stop()
{
	running = false;
	StartTime = 0;
}

void FpsCounter::frameTick()
{
	if (running == false)
	return;

	ticks++;

	double ActualTime = getTime();

	if (ticks == interval)
	{
		fps = ticks / ((getTime() - StartTime)/1000);

		interval = (int)fps;

		clamp(interval, 1, 100);

		StartTime = ActualTime;
		ticks = 0;
	}

	DeltaTime = ActualTime - LastTime;
	LastTime = getTime();
}

double FpsCounter::getFPS()
{
	return fps;
}

double FpsCounter::getDeltaTime()
{
	return 0.0;
}



FpsGovernor::FpsGovernor()
{
	StartTime = 0.0;

	running = false;

	fps_limit = 0.0f;

	frame_count = 0;

	DeltaTime = 0.0;
	LastTime = 0.0;
}

FpsGovernor::~FpsGovernor()
{
}

void FpsGovernor::Start()
{
	running = true;

	StartTime = getTime();
	LastTime = StartTime;
}

void FpsGovernor::Stop()
{
	running = false;
}

void FpsGovernor::frameTick()
{
	if (running == false)
		return;

	double ActualTime = getTime();

	double DeltaTime = ActualTime - LastTime;

	if (DeltaTime < 1000/fps_limit)
	sleep((int)((1000 / fps_limit) - DeltaTime));

	LastTime = getTime();
}

void FpsGovernor::setLimit(float limit)
{
	fps_limit = limit;
}

double FpsGovernor::getDeltaTime()
{
	return 0.0;
}
