#include "renderer.h"

#include <vector>

#include "bmp_loader.h"
#include "obj_loader.h"


using std::vector;

vector<glm::mat4> modelMatrix;

int cubes = 200;

void Renderer::init()
{
	vector< glm::vec3 > vertices;
	vector< glm::vec2 > uvs;
	vector< glm::vec3 > normals;

	bool res = loadOBJ_custom("Assets//cube.obj", vertices, uvs, normals);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec3), &uvs[0], GL_STATIC_DRAW);


	myShader = new Shader("Shaders//texture_vertex.glsl", "Shaders//texture_fragment.glsl");


	cam.setPosTarg(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0));


	Model = glm::mat4(1.0f);

	mvp = cam.getViewProj() * Model; // Remember, matrix multiplication is the other way around

	MatrixID = glGetUniformLocation(myShader->getID(), "MVP");

	Texture = loadBMP("Assets//uvtemplate.bmp");

	TextureID = glGetUniformLocation(myShader->getID(), "myTextureSampler");

	for (int i = 0; i < cubes; i++)
		modelMatrix.push_back(glm::mat4(1.0f));

	for (int i = 0; i < cubes; i++)
		modelMatrix[i] = glm::translate(modelMatrix[i], glm::vec3(-10 + rand() % 20, -10 + rand() % 20, rand() % 30));

}

void Renderer::release()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);

	delete myShader;
}

void Renderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	myShader->use();

	for (int i = 0; i < cubes; i++)
	{
		mvp = cam.getViewProj() * modelMatrix[i];

		// Send our transformation to the currently bound shader, in the "MVP" uniform
		// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);


		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
}

void Renderer::update()
{
	for (int i = 0; i < cubes; i++)
	{
		float rate = 0.01f + 0.03f * ((float)rand()) / RAND_MAX;

		modelMatrix[i] = glm::rotate(modelMatrix[i], rate, glm::vec3(0, 1, 0));
		modelMatrix[i] = glm::rotate(modelMatrix[i], rate, glm::vec3(1, 0, 0));
		modelMatrix[i] = glm::rotate(modelMatrix[i], rate, glm::vec3(0, 0, 1));
	}

	cam.zoom(1.0001f);
}
