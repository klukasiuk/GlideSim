#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in vec3 vertexColor;

out vec3 fragmentColor;

uniform mat4 MVP;
  
void main()
{
	gl_Position =  MVP * vec4(vertexPosition,1);

	fragmentColor = vertexNormal;
}