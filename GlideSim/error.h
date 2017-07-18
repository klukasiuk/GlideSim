#pragma once

#include "platform.h"
#include "logger.h"

namespace error
{
	void msg(string msg, string tittle);

	void msg(char * msg, char * tittle);

	void msg(string msg, string tittle , int errorCode);

	void msg(char * msg, char * tittle , int errorCode);


	void critical(string msg, string tittle);

	void critical(char * msg, char * tittle);

	void critical(string msg, string tittle, int errorCode);

	void critical(char * msg, char * tittle, int errorCode);

	void forceExit();

	void setShowMsgBox(bool flag);
	void setLogErrors(bool flag);
}