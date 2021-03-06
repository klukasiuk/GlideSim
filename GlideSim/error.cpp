#include "error.h"

#include <stdio.h>

void release() {};

bool showMsgBox     = true;
bool logErrors      = true;

#ifdef _DEBUG
bool printToConsole = true;
#else
bool printToConsole = false;
#endif

void error::msg(string msg, string tittle)
{
	error::msg((char*)msg.c_str(), (char*)tittle.c_str());
}

void error::msg(char * msg, char * tittle)
{
	if (printToConsole)
	printf("ERROR OCCURED -> %s : %s\n", tittle, msg);

	if (logErrors)
	logger::msg("ERROR : " + string(tittle) + " -- " + string(msg));

	if (showMsgBox)
	MsgBox(msg, tittle);
}

void error::msg(string msg, string tittle, int errorCode)
{
	error::msg((char*)msg.c_str() , (char*)tittle.c_str(),errorCode);
}

void error::msg(char * msg, char * tittle, int errorCode)
{
	if (printToConsole)
	printf("ERROR OCCURED -> %s : %s CODE %d\n", tittle, msg, errorCode);

	if (logErrors)
	logger::msg("ERROR : " + string(tittle) + " -- " + string(msg), errorCode);

	if (showMsgBox)
	MsgBox(msg, tittle);
}


void error::critical(string msg, string tittle)
{
	error::critical((char*)msg.c_str(), (char*)tittle.c_str());
}

void error::critical(char * msg, char * tittle)
{
	logger::msg("CRITICAL ERROR : " + string(tittle) + " -- " + string(msg));

	if (printToConsole)
	printf("CRITICAL ERROR -> %s : %s\n", tittle, msg);

	MsgBox(msg, tittle);

	forceExit();
}

void error::critical(string msg, string tittle, int errorCode)
{
	error::critical((char*)msg.c_str(), (char*)tittle.c_str(), errorCode);
}

void error::critical(char * msg, char * tittle, int errorCode)
{
	logger::msg("CRITICAL ERROR : " + string(tittle) + " -- " + string(msg), errorCode);

	if (printToConsole)
	printf("CRITICAL ERROR -> %s : %s CODE %d\n", tittle, msg, errorCode);

	MsgBox(msg, tittle);

	forceExit();
}


void error::forceExit()
{
	logger::msg("Force Exit");

	logger::msg("Releasing memory");

	// TODO : GLOBAL RELEASE FUNCTION

	logger::msg("Exiting program");

	exit(EXIT_FAILURE);
}


void error::setShowMsgBox(bool flag)
{
	showMsgBox = flag;
}

void error::setLogErrors(bool flag)
{
	logErrors = flag;
}
