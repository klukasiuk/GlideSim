#pragma once

#include <string>

#include "platform.h"
#include "time.h"


using std::string;


namespace logger
{
	void init();
	void init(string init_msg);
	void release();

	void msg(char * msg);
	void msg(string msg);

	void msg(char * msg, int errorCode);
	void msg(string msg, int errorCode);

	void logSystemInfo();
};
