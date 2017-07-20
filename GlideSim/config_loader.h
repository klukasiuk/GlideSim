#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

enum ParamType
{
	param_int,
	param_float,
	param_string
};

struct Param
{
	string key;

	string section;

	ParamType type;

	void * value;
};

// Loads config from INI file
class ConfigLoader
{
private :

	string config_file_name;

	vector<Param> params_vec;

public :

	ConfigLoader();
   ~ConfigLoader();

	void load(string filename);

	void reload();
};