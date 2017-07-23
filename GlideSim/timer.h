#pragma once

#include "time.h"

class Timer
{
private :

	double startTime;
	double elapsedTime;

	bool running;

public :

	Timer();
   ~Timer();

	void start();
	void stop();
	void reset();

	double getElapsedTime();
};

class FpsCounter
{
private :

	double startTime;
	double lastTime;
	double deltaTime;

	double fps;

	int interval;

	int ticks;

	bool running;

public :

	FpsCounter();
   ~FpsCounter();

   void start();
   void stop();

   void frameTick();

   double getFPS();

   double getDeltaTime();
};

class FpsGovernor
{
private:

	double startTime;
	double lastTime;
	double deltaTime;

	float fps_limit;

	bool running;

	int frame_count;

public:

	FpsGovernor();
   ~FpsGovernor();

	void start();
	void stop();

	void frameTick();

	void setLimit(float limit);

	double getDeltaTime();
};