#pragma once

#include "time.h"

class Timer
{
private :

	double StartTime;
	double ElapsedTime;

	bool running;

public :

	Timer();
   ~Timer();

	void Start();
	void Stop();
	void Reset();

	double getElapsedTime();
};

class FpsCounter
{
private :

	double StartTime;

	int interval;

	int ticks;

	float fps;

	bool running;

	double LastTime;
	double DeltaTime;

public :

	FpsCounter();
   ~FpsCounter();

   void Start();
   void Stop();

   void frameTick();

   float getFPS();

   double getDeltaTime();
};

class FpsGovernor
{
private:

	double StartTime;

	bool running;

	float fps_limit;

	int frame_count;

	double LastTime;
	double DeltaTime;

public:

	FpsGovernor();
   ~FpsGovernor();

	void Start();
	void Stop();

	void frameTick();

	void setLimit(float limit);

	double getDeltaTime();
};