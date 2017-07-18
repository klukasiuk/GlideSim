#include "time.h"

using namespace std::chrono;

// This is nearly program boot time
auto StartPoint = high_resolution_clock::now();

// Time from program start in miliseconds
double getTime()
{
	auto TimePoint = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(TimePoint - StartPoint);

	return time_span.count() * 1000;
}

// String with time from program start
string getTimeString()
{
	string time = std::to_string((int)getTime());

	while (time.size() < 6)
		time.insert(0, " ");

	return time;
}

// Sleeps thread for given time
void sleep(int miliseconds)
{
	std::chrono::milliseconds dura(miliseconds);
	std::this_thread::sleep_for(dura);
}

// Returns string with actual time
string getHour()
{
	string s;

	time_t rawtime;
	tm timeinfo;

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	int hour = timeinfo.tm_hour;
	int min = timeinfo.tm_min;
	int sec = timeinfo.tm_sec;

	if (hour < 10)
		s += "0" + std::to_string(hour) + ".";
	else
		s += std::to_string(hour) + ".";

	if (min < 10)
		s += "0" + std::to_string(min) + ".";
	else
		s += std::to_string(min) + ".";

	if (sec < 10)
		s += "0" + std::to_string(sec);
	else
		s += std::to_string(sec);


	return s;
}

// Returns string with actual time
string getDate()
{
	string s;

	time_t rawtime;
	tm timeinfo;

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	int year = timeinfo.tm_year + 1900;
	int day = timeinfo.tm_mday;
	int month = timeinfo.tm_mon + 1;

	s += std::to_string(year) + ".";

	if (month < 10)
		s += "0" + std::to_string(month) + ".";
	else
		s += std::to_string(month) + ".";

	if (day < 10)
		s += "0" + std::to_string(day);
	else
		s += std::to_string(day);

	return s;
}

// Return string with date and time
string getDateAndHour()
{
	string s = getDate() + "_" + getHour();

	return s;
}