#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

// Platform depended functions

// MessageBox with error icon and ok button
void MsgBox(const char * msg, const char * tittle);

string getCpuString();

string getCpuCores();

string getRamString();

string getOsVersion();

// File and directory manipulation

void createDir(char * dir_name);

string getLocalPath();

vector<string> getDirectoryFilenames(string& directoryName);

vector<string> getSubDirectories(string& directoryName);

vector<string> getFilesRecursively(string & directoryName, int level);

vector<string> getSubDirectoriesRecursively(string & directoryName, int level);
