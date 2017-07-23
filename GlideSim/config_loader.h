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
private:

	const char * default_config_filename = "config.txt";

	string config_file_name;

	vector<Param> params_vec;

public:

	ConfigLoader();
	~ConfigLoader();

	void load(string filename);
	void reload();

	void create_default_config();

	int    get_int(string param_name);
	float  get_float(string param_name);
	string get_string(string param_name);

	vector<Param> get_section(string section_name);
};