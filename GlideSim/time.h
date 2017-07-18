#pragma once

#include <string>
#include <chrono>
#include <thread>

using std::string;

// Sleeps thread for given time
void sleep(int miliseconds);

// Time from program start in miliseconds
double getTime();

// String with time from program start
string getTimeString();

// Returns string with actual time
string getHour();

// Returns string with actual date
string getDate();

// Return string with date and time
string getDateAndHour();