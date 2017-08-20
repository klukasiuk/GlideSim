#version 330 core

layout(location = 0) in vec3 vertexPosition;

out vec3 fragmentColor;

uniform mat4 MVP;
  
void main()
{
	gl_Position =  MVP * vec4(vertexPosition,1);

	fragmentColor = vec3(1.0,1.0,1.0);
}