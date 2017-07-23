#include "logger.h"

#include <fstream>
#include <iostream>

#include <GLFW/glfw3.h>

#include "platform.h"

using std::ofstream;
using std::cout;


ofstream logFile;

bool logOpen = false;

string logs_dir = "logs//";


void logger::init()
{
	if (logOpen)
	{
		cout << "Logger Error -> Trying to initialize logger second time";
		MsgBox("Trying to initialize logger second time", "Logger Error");
		return;
	}

	createDir((char*)logs_dir.c_str());

	string logName = logs_dir + "log_" + getDateAndHour() + ".txt";

	logFile.open(logName.c_str());

	if (logFile.is_open() == false)
	{
		cout << "Logger Error -> Cannot create log file";
		MsgBox("Cannot create log file", "Logger Error");
	}

	logFile.precision(5);

	logOpen = true;

	logFile << "Log created on " << getDateAndHour() << "\n\n";
}

void logger::init(string init_msg)
{
	if (logOpen)
	{
		cout << "Logger Error -> Trying to initialize logger second time";
		MsgBox("Trying to initialize logger second time", "Logger Error");
		return;
	}

	createDir((char*)logs_dir.c_str());

	string logName = logs_dir + "log_" + getDateAndHour() + ".txt";

	logFile.open(logName.c_str());

	if (logFile.is_open() == false)
	{
		cout << "Logger Error -> Cannot create log file";
		MsgBox("Cannot create log file", "Logger Error");
	}

	logFile.precision(5);

	logOpen = true;

	logFile << init_msg << "\n";

	logFile << "Log created on " << getDateAndHour() << "\n\n";
}

void logger::release()
{
	if (!logOpen)
	{
		cout << "Logger Error -> Trying to release logger second time";
		MsgBox("Trying to release logger second time", "Logger Error");
		return;
	}

	logFile.flush();

	logFile.close();

	logOpen = false;
}

void logger::msg(char * msg)
{
	logFile << getTimeString() << " -> ";
	logFile << msg << "\n";

	logFile.flush();
}

void logger::msg(string msg)
{
	logFile << getTimeString() << " -> ";
	logFile << msg << "\n";

	logFile.flush();
}

void logger::msg(char * msg, int errorCode)
{
	logFile << getTimeString() << " -> ";

	logFile << msg;
	
	logFile << "  Error code :"<< errorCode << "\n";

	logFile.flush();
}

void logger::msg(string msg, int errorCode)
{
	logFile << getTimeString() << " -> ";

	logFile << msg;

	logFile << "  Error code :" << errorCode << "\n";

	logFile.flush();
}

void logger::logSystemInfo()
{
	logFile <<"System info :" << "\n";

	logFile << "OpenGL version : " << glGetString(GL_VERSION) << "\n";
	logFile << "GLFW version : " << glfwGetVersionString()<< "\n";
	logFile << "CPU : " << getCpuString() << "\n";
	logFile << "CPU cores : " << getCpuCores() << "\n";
	logFile << "GPU : " << glGetString(GL_RENDERER) << "\n";
	logFile << "RAM : " << getRamString() << "\n";
	logFile << "OS  : " << getOsVersion() << "\n\n";


	logFile.flush();
}
