#version 330 core
layout (location = 0) in vec3 VertexPos;
layout (location = 2) in vec3 VertexNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 ModelMat;
uniform mat4 ViewMat;
uniform mat4 ProjMat;

void main()
{
    FragPos = vec3(ModelMat * vec4(VertexPos, 1.0));
    Normal = VertexNormal;  
    
    gl_Position = ProjMat * ViewMat * vec4(FragPos, 1.0);
}