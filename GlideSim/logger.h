#pragma once

#include <string>

#include "platform.h"
#include "time.h"

using std::string;

namespace logger
{
	enum msgLevel
	{
		info,
		error,
		critical
	};

	void init();

	void release();

	void msg(char * msg);
	void msg(string msg);

	void msg(char * msg, msgLevel level);
	void msg(string msg, msgLevel level);

	void msg(char * msg, int errorCode , msgLevel level);
	void msg(string msg, int errorCode , msgLevel level);

	void logSystemInfo();
};


