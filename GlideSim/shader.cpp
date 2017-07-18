#include "shader.h"

#include <string>
#include <fstream>
#include <vector>


Shader::Shader(const char * vertex_file_path, const char * fragment_file_path)
{
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);										// Creating Shaders
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VertexShaderCode;
	std::string FragmentShaderCode;

	std::string Line;

	GLint Result = GL_FALSE;																		// For opengl error checking
	int InfoLogLength;


	std::ifstream VertexShaderFile(vertex_file_path, std::ios::in);									// Open file with Vertex Shader

	if (VertexShaderFile.is_open() == false)														// Checking if file is opened
	{
		error::critical("Impossible to open : " + string(vertex_file_path), "Shader Loading Error");
		return;
	}

	while (getline(VertexShaderFile, Line))															// Reading vertex shader
		VertexShaderCode += Line + "\n";

	VertexShaderFile.close();																		// Close after reading


	std::ifstream FragmentShaderFile(fragment_file_path, std::ios::in);								// Open file with Fragment Shader

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

		error::critical("Impossible to compile shader : " + string(vertex_file_path), "Shader Compiling Error");

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

		error::critical("Impossible to compile shader : " + string(fragment_file_path), "Shader Compiling Error");

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

Shader::~Shader()
{
	glDeleteProgram(programID);
}

void Shader::use()
{
	glUseProgram(programID);
}

GLuint Shader::getID()
{
	return programID;
}
