#pragma once

#include <string>

using std::string;

class ConfigLoader
{
private :

	string config_file_name;

public :

	ConfigLoader();

	void load(string filename);

};