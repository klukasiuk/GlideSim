#include "mesh.h"


Mesh::Mesh(vector<unsigned short> Indices, vector<glm::vec3> Vertices, vector<glm::vec2> UVs, vector<glm::vec3> Normals, vector<glm::vec3> Colors)
{
	indices = Indices;
	vertices = Vertices;
	uvs = UVs;
	normals = Normals;
	colors = Colors;

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glGenBuffers(1, &vertexBufferID);
	glGenBuffers(1, &uvBufferID);
	glGenBuffers(1, &normalBufferID);
	glGenBuffers(1, &colorBufferID);

	if (vertices.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	}

	if (uvs.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	}

	if (normals.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	}

	if (colors.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
		glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);
	}

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

Mesh::~Mesh()
{
	//glDeleteVertexArrays(1, &vertexArrayID);

	//glDeleteBuffers(1, &vertexBufferID);
	//glDeleteBuffers(1, &uvBufferID);
	//glDeleteBuffers(1, &vertexBufferID);
	//glDeleteBuffers(1, &uvBufferID);
}

void Mesh::draw(Shader * shader)
{
	glBindVertexArray(vertexArrayID);

	if (indices.size() > 0)
	{
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	}
}
