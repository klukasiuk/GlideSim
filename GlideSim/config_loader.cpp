#include "config_loader.h"

#include <fstream>

#include "error.h"


bool blank_line(string line)
{
	if (line.length() == 0)
		return true;

	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] <= 32)							// if char is not printable
			continue;

		return false;								// if at least one char is printable
	}

	return true;
}

bool comment_line(string line)
{
	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] <= 32)							// if char is not printable
			continue;

		if (line[i] == 35 || line[i] == 59)			// if char is "#" or ";"
			return true;
		else
			return false;
	}

	return false;
}

bool sector_line(string line)
{
	bool left_bracket = false;

	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] <= 32)							// if char is not printable
			continue;

		if (line[i] == 91)							// if char is "["
		{
			left_bracket = true;
			break;
		}
	}

	if (left_bracket == false)
		return false;

	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] <= 32)							// if char is not printable
			continue;

		if (line[i] == 93)							// if char is "]"
			return true;
	}

	return false;

}

bool key_value_line(string line)
{
	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] <= 32)							// if char is not printable
			continue;

		if (line[i] == 61)							// if char is "="
			return true;
	}

	return false;
}

string parse_section(string line)
{
	int left_bracket  = 0;
	int right_bracket = 0;

	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] <= 32)							// if char is not printable
			continue;

		if (line[i] == 91)							// if char is "["
		{
			left_bracket = i;
			break;
		}
	}

	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] <= 32)							// if char is not printable
			continue;

		if (line[i] == 93)							// if char is "]"
		{
			right_bracket = i;
			break;
		}
	}

	return line.substr(left_bracket + 1, right_bracket - left_bracket - 1);
}

void parse_line(string line, string * key, string * value)
{
	int equals_char = 0;

	int key_start   = 0;
	int key_end     = 0;

	int value_start = 0;
	int value_end   = 0;


	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] == 61)							// if char is "="
		{
			equals_char = i;
			break;
		}
	}

	for (int i = 0; i < equals_char; i++)
	{
		if (line[i] <= 32)
			continue;

		key_start = i;
		break;
	}

	for (int i = key_start + 1; i < equals_char; i++)
	{
		if (line[i] <= 32)
		{
			key_end = i - 1;
			break;
		}
	}

	for (unsigned int i = equals_char + 1; i < line.length(); i++)
	{
		if (line[i] <= 32)
			continue;

		value_start = i;
		break;
	}

	for (unsigned int i = value_start + 1; i <line.length(); i++)
	{
		if (line[i] <= 32)
		{
			value_end = i - 1;
			break;
		}
	}

	*key   = line.substr(key_start, key_end - key_start + 1);
	*value = line.substr(value_start, value_end - value_start + 1);
}

ParamType check_type(string value)
{
	bool non_digit_character = false;
	bool dot_character       = false;

	for (unsigned int i = 0; i < value.length(); i++)	// check for printable characters
	{
		if (value[i] < 48 || value[i] > 57)
		{
			non_digit_character = true;
		}

		if (value[i] == 46)
		{
			dot_character = true;
		}
	}

	if (non_digit_character == true && dot_character == false)
		return param_string;

	if (non_digit_character == true && dot_character == true)
		return param_float;

	return param_int;
}

void * convert_value(string value, ParamType type)
{
	void * return_value = NULL;

	if (type == param_int)
	{
		return_value = (void*)new int;

		*((int*)return_value) = std::stoi(value);
	}

	if (type == param_float)
	{
		return_value = (void*)new float;

		*((float*)return_value) = std::stof(value);
	}

	if (type == param_string)
	{
		return_value = (void*)new string;

		*((string*)return_value) = value;
	}

	return return_value;
}


ConfigLoader::ConfigLoader()
{
	config_file_name = "none";
}

ConfigLoader::~ConfigLoader()
{
	for (unsigned int i = 0; i < params_vec.size(); i++)
	{
		delete params_vec[i].value;
	}

	params_vec.clear();
}

void ConfigLoader::load(string filename)
{
	config_file_name = filename;

	std::ifstream config_file(filename.c_str());

	if (config_file.is_open() == false)
	{
		error::msg(string("Cannot open config file = ") + filename + "\n Creating default config", string("ConfigLoader error"));
		
		create_default_config();

		config_file_name = default_config_filename;

		config_file.open(default_config_filename);

		if (config_file.is_open() == false)
		{
			error::msg("Still cannot open config file", "ConfigLoader error");
			return;
		}
	}

	string line;

	string section = "";

	while (std::getline(config_file,line))
	{
		if (blank_line(line))
			continue;

		if (comment_line(line))
			continue;

		if (sector_line(line))
		{
			section = parse_section(line);
			continue;
		}

		if (key_value_line(line))
		{
			string key;
			string value;

			parse_line(line, &key, &value);

			ParamType type = check_type(value);

			Param new_param;

			new_param.key = key;
			new_param.section = section;
			new_param.type = type;
			new_param.value = convert_value(value, type);

			params_vec.push_back(new_param);
			continue;
		}

		printf("Config Parser : unknown line content \n");
	}

	config_file.close();
}

void ConfigLoader::reload()
{
	params_vec.clear();
	load(config_file_name);
}

void ConfigLoader::create_default_config()
{
	std::ofstream config_file(default_config_filename);

	if (config_file.is_open() == false)
	{
		error::msg("Cannot create default config file", "ConfigLoader error");
		return;
	}

	config_file << "# Default config file\n";
	config_file << "window_width = 800\n";
	config_file << "window_height = 600\n";

	config_file.close();
}

int ConfigLoader::get_int(string param_name)
{
	for (unsigned int i = 0; i < params_vec.size(); i++)
	{
		if (params_vec[i].type != param_int)
			continue;

		if (params_vec[i].key == param_name)
		{
			return *((int*)params_vec[i].value);
		}
	}

	error::msg(string("Cannot find requested parameter = ") + param_name, string("ConfigLoader error"));
	return 0;
}

float ConfigLoader::get_float(string param_name)
{
	for (unsigned int i = 0; i < params_vec.size(); i++)
	{
		if (params_vec[i].type != param_float)
			continue;

		if (params_vec[i].key == param_name)
		{
			return *((float*)params_vec[i].value);
		}
	}

	error::msg(string("Cannot find requested parameter = ") + param_name, string("ConfigLoader error"));
	return 0.0f;
}

string ConfigLoader::get_string(string param_name)
{
	for (unsigned int i = 0; i < params_vec.size(); i++)
	{
		if (params_vec[i].type != param_string)
			continue;

		if (params_vec[i].key == param_name)
		{
			return *((string*)params_vec[i].value);
		}
	}

	error::msg(string("Cannot find requested parameter = ") + param_name, string("ConfigLoader error"));
	return 0;
}

vector<Param> ConfigLoader::get_section(string section_name)
{
	vector<Param> section_parameters;

	for (unsigned int i = 0; i < params_vec.size(); i++)
	{
		if (params_vec[i].section != section_name)
			continue;

		section_parameters.push_back(params_vec[i]);
	}

	return section_parameters;
}
