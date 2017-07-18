#include "platform.h"

#include <thread>

#ifdef _WIN32 

#include <Windows.h>
#include <VersionHelpers.h>

#endif


#ifdef __linux__

#include <SDL.h>

#endif

void MsgBox(const char * msg, const char * tittle)
{
#ifdef _WIN32
	MessageBoxA(NULL, msg, tittle, MB_ICONERROR | MB_OK);
#endif

#ifdef __linux__
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, tittle, msg);
#endif
}

std::string getCpuString()
{
#ifdef _WIN32
	// Get extended ids.
	int CPUInfo[4] = { -1 };
	CpuIdEx(CPUInfo, 0x80000000,0);
	unsigned int nExIds = CPUInfo[0];

	// Get the information associated with each extended ID.
	char CPUBrandString[0x40] = { 0 };
	for (unsigned int i = 0x80000000; i <= nExIds; ++i)
	{
		CpuIdEx(CPUInfo, i,0);

		// Interpret CPU brand string and cache information.
		if (i == 0x80000002)
		{
			memcpy(CPUBrandString,
				CPUInfo,
				sizeof(CPUInfo));
		}
		else if (i == 0x80000003)
		{
			memcpy(CPUBrandString + 16,
				CPUInfo,
				sizeof(CPUInfo));
		}
		else if (i == 0x80000004)
		{
			memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
		}
	}

	return std::string(CPUBrandString);
#endif

#ifdef __linux__

#endif
}

std::string getCpuCores()
{
#ifdef _WIN32

	return std::to_string(std::thread::hardware_concurrency());

#endif

#ifdef __linux__

#endif
}

std::string getRamString()
{
#ifdef _WIN32

	MEMORYSTATUSEX mem;
	mem.dwLength = sizeof(mem);
	GlobalMemoryStatusEx(&mem);

	std::string ram = "RAM : " + std::to_string(mem.ullTotalPhys / (1024 * 1024)) + " MB";

	return ram;

#endif

#ifdef __linux__

#endif
}

std::string getOsVersion()
{
#ifdef _WIN32


	if (IsWindows10OrGreater())
	return std::string("Windows 10");

	if (IsWindows8Point1OrGreater())
	return std::string("Windows 8.1");

	if (IsWindows8OrGreater())
	return std::string("Windows 8");

	if (IsWindows7OrGreater())
	return std::string("Windows 7");

	return std::string("Older Windows");

#endif

#ifdef __linux__
	return std::string("Linux");
#endif
}