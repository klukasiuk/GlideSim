#include "shader.h"

#include <string>
#include <fstream>
#include <vector>


using std::string;
using std::ifstream;


Shader::Shader(char * vertex_file_path, char * fragment_file_path)
{
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);										// Creating Shaders
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	string VertexShaderCode;
	string FragmentShaderCode;

	string Line;

	GLint Result = GL_FALSE;																		// For opengl error checking
	int InfoLogLength;


	ifstream VertexShaderFile(vertex_file_path, std::ios::in);										// Open file with Vertex Shader

	if (VertexShaderFile.is_open() == false)														// Checking if file is opened
	{
		error::critical("Impossible to open : " + string(vertex_file_path), "Shader Loading Error");
		return;
	}

	while (getline(VertexShaderFile, Line))															// Reading vertex shader
		VertexShaderCode += Line + "\n";

	VertexShaderFile.close();																		// Close after reading


	ifstream FragmentShaderFile(fragment_file_path, std::ios::in);									// Open file with Fragment Shader

	if (FragmentShaderFile.is_open() == false)														// Checking if file is opened
	{
		error::critical("Impossible to open : " + string(fragment_file_path), "Shader Loading Error");

		return;
	}

	while (getline(FragmentShaderFile, Line))														// Reading fragment shader
		FragmentShaderCode += Line + "\n";

	FragmentShaderFile.close();																		// Close after reading



	char const * VertexSourcePointer = VertexShaderCode.c_str();									// Compiling Vertex Shader
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);										// Checking if shader compiled
	if (Result == GL_FALSE)
	{
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);

		glDeleteShader(VertexShaderID);

		string error_info;

		for (unsigned int i = 0; i < VertexShaderErrorMessage.size(); i++)
			error_info += VertexShaderErrorMessage[i];

		error::critical(error_info, "Shader Compiling Error");

		return;
	}



	char const * FragmentSourcePointer = FragmentShaderCode.c_str();								// Compiling Fragment Shader
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);									// Checking if shader compiled
	if (Result == GL_FALSE)
	{
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);

		glDeleteShader(FragmentShaderID);

		string error_info;

		for (unsigned int i = 0; i < FragmentShaderErrorMessage.size(); i++)
			error_info += FragmentShaderErrorMessage[i];

		error::critical(error_info, "Shader Compiling Error");

		return;;
	}



	GLuint ProgramID = glCreateProgram();															// Creating program
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);												// Checking program
	if (Result == GL_FALSE)
	{
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);

		glDeleteProgram(ProgramID);

		error::critical("Cannot link shader program", "Shader Program Error");

		return;
	}


	glDetachShader(ProgramID, VertexShaderID);														// Cleaning up
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	programID = ProgramID;
	vertex_shader_path = vertex_file_path;
	fragment_shader_path = fragment_file_path;
}

Shader::~Shader()
{
	glDeleteProgram(programID);
}

void Shader::use()
{
	glUseProgram(programID);
}

void Shader::reload()
{
	glDeleteProgram(programID);

	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);										// Creating Shaders
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	string VertexShaderCode;
	string FragmentShaderCode;

	string Line;

	GLint Result = GL_FALSE;																		// For opengl error checking
	int InfoLogLength;


	ifstream VertexShaderFile(vertex_shader_path.c_str(), std::ios::in);							// Open file with Vertex Shader

	if (VertexShaderFile.is_open() == false)														// Checking if file is opened
	{
		error::critical("Impossible to open : " + vertex_shader_path, "Shader Loading Error");
		return;
	}

	while (getline(VertexShaderFile, Line))															// Reading vertex shader
		VertexShaderCode += Line + "\n";

	VertexShaderFile.close();																		// Close after reading


	ifstream FragmentShaderFile(fragment_shader_path.c_str(), std::ios::in);									// Open file with Fragment Shader

	if (FragmentShaderFile.is_open() == false)														// Checking if file is opened
	{
		error::critical("Impossible to open : " + fragment_shader_path, "Shader Loading Error");

		return;
	}

	while (getline(FragmentShaderFile, Line))														// Reading fragment shader
		FragmentShaderCode += Line + "\n";

	FragmentShaderFile.close();																		// Close after reading



	char const * VertexSourcePointer = VertexShaderCode.c_str();									// Compiling Vertex Shader
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);										// Checking if shader compiled
	if (Result == GL_FALSE)
	{
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);

		glDeleteShader(VertexShaderID);

		error::critical("Impossible to compile shader : " + vertex_shader_path, "Shader Compiling Error");

		return;
	}



	char const * FragmentSourcePointer = FragmentShaderCode.c_str();								// Compiling Fragment Shader
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);									// Checking if shader compiled
	if (Result == GL_FALSE)
	{
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);

		glDeleteShader(FragmentShaderID);

		error::critical("Impossible to compile shader : " + fragment_shader_path, "Shader Compiling Error");

		return;;
	}



	GLuint ProgramID = glCreateProgram();															// Creating program
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);												// Checking program
	if (Result == GL_FALSE)
	{
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);

		glDeleteProgram(ProgramID);

		error::critical("Cannot link shader program", "Shader Program Error");

		return;
	}


	glDetachShader(ProgramID, VertexShaderID);														// Cleaning up
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	programID = ProgramID;
}

GLuint Shader::getID()
{
	return programID;
}

void Shader::setBool(string &name, bool value)
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void Shader::setInt(string &name, int value)
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setFloat(string &name, float value)
{
	glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setVec2(string &name, glm::vec2 &value)
{
	glUniform2fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(string &name, float x, float y)
{
	glUniform2f(glGetUniformLocation(programID, name.c_str()), x, y);
}

void Shader::setVec3(string &name, glm::vec3 &value)
{
	glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(string &name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
}

void Shader::setVec4(string &name, glm::vec4 &value)
{
	glUniform4fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(string &name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(programID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(string &name, glm::mat2 &mat)
{
	glUniformMatrix2fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(string &name, glm::mat3 &mat)
{
	glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(string &name, glm::mat4 &mat)
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
