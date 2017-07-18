#pragma once

#include <string>

// Platform depended functions

// MessageBox with error icon and ok button
void MsgBox(const char * msg, const char * tittle);

std::string getCpuString();

std::string getCpuCores();

std::string getRamString();

std::string getOsVersion();