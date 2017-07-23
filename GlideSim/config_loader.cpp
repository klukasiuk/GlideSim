#include "config_loader.h"

#include <fstream>

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

string get_section(string line)
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
	std::ifstream config_file(filename.c_str());

	if (config_file.is_open() == false)
	return;

	config_file_name = filename;

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
			section = get_section(line);
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
}

void ConfigLoader::reload()
{
}
