#include "platform.h"

#include <thread>

#ifdef _WIN32 

#include <Windows.h>
#include <VersionHelpers.h>
#include <direct.h>

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

void createDir(char * dir_name)
{
#ifdef _WIN32

	_mkdir(dir_name);

#endif
}

string getLocalPath()
{
#ifdef _WIN32

	string path;

	char buf[100];

	int bytes = GetModuleFileName(NULL, buf, 100);

	for (int i = 0; i<bytes; i++)
		path += buf[i];

	int pos = (int)path.rfind("\\");

	path = path.substr(0, pos + 1);

	return path;

#endif
}

std::vector<std::string> getDirectoryFilenames(std::string& directoryName)
{
#ifdef _WIN32

	vector<string> filenames;

	string searchExpression = directoryName + "\\*.*";

	WIN32_FIND_DATA fileAttributes;

	int result;

	HANDLE handleFile = FindFirstFile(searchExpression.c_str(), &fileAttributes);

	if (handleFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(fileAttributes.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				filenames.push_back(fileAttributes.cFileName);

			result = FindNextFile(handleFile, &fileAttributes);
		} while (result != 0);

		FindClose(handleFile);
	}

	return filenames;

#endif
}

vector<string> getSubDirectories(string& directoryName)
{
#ifdef _WIN32

	vector<string> subdirs;

	string searchExpression = directoryName + "\\*.*";

	WIN32_FIND_DATA fileAttributes;

	int result;

	HANDLE handleFile = FindFirstFile(searchExpression.c_str(), &fileAttributes);

	if (handleFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (fileAttributes.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				subdirs.push_back(fileAttributes.cFileName);

			result = FindNextFile(handleFile, &fileAttributes);
		} while (result != 0);

		FindClose(handleFile);
	}

	if (subdirs.size() >= 2)
	{
		subdirs.erase(subdirs.begin());				// Erasing "." and ".." folders
		subdirs.erase(subdirs.begin());
	}

	return subdirs;

#endif
}

vector<string> getFilesRecursively(string & directoryName, int level = 0)
{
#ifdef _WIN32

	if (level > 8)					// Dont go to deep in recursion
		return vector<string>();

	vector<string> filenames;
	vector<string> filenamesFromSubdir;
	vector<string> subdirs;

	filenames = getDirectoryFilenames(directoryName);
	subdirs = getSubDirectories(directoryName);

	for (unsigned int i = 0; i < subdirs.size(); i++)
	{
		filenamesFromSubdir = getFilesRecursively(directoryName + "\\" + subdirs[i], level + 1);

		for (unsigned int a = 0; a < filenamesFromSubdir.size(); a++)
			filenames.push_back(subdirs[i] + "\\" + filenamesFromSubdir[a]);
	}

	return filenames;

#endif
}

vector<string> getSubDirectoriesRecursively(string & directoryName, int level = 0)
{
#ifdef _WIN32

	if (level > 8)					// Dont go to deep in recursion
		return vector<string>();

	vector<string> subdirs;
	vector<string> result;
	vector<string> subdirsFromSubdir;

	subdirs = getSubDirectories(directoryName);

	for (unsigned int i = 0; i < subdirs.size(); i++)
	{
		subdirsFromSubdir = getSubDirectoriesRecursively(directoryName + "\\" + subdirs[i], level + 1);

		result.push_back(subdirs[i]);

		for (unsigned int a = 0; a < subdirsFromSubdir.size(); a++)
			result.push_back(subdirs[i] + "\\" + subdirsFromSubdir[a]);
	}

	return result;

#endif
}