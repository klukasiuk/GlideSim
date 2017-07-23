#include "renderer.h"

#include <vector>

#include "bmp_loader.h"
#include "obj_loader.h"


using std::vector;

vector<glm::mat4> modelMatrix;

int cubes = 200;

void Renderer::init()
{
	cube_mesh.load("Assets//suzanne.obj");

	//myShader = new Shader("Shaders//texture_vertex.glsl", "Shaders//texture_fragment.glsl");
	myShader = new Shader("Shaders//color_vertex.glsl", "Shaders//color_fragment.glsl");

	cam.setPosTarg(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0));

	Texture = loadBMP("Assets//uvtemplate.bmp");

	for (int i = 0; i < cubes; i++)
		modelMatrix.push_back(glm::mat4(1.0f));

	for (int i = 0; i < cubes; i++)
		modelMatrix[i] = glm::translate(modelMatrix[i], glm::vec3(-10 + rand() % 20, -10 + rand() % 20, rand() % 30));

}

void Renderer::release()
{
	delete myShader;
}

void Renderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	myShader->use();

	for (int i = 0; i < cubes; i++)
	{
		int MvpID = glGetUniformLocation(myShader->getID(), "MVP");
		int TextureID = glGetUniformLocation(myShader->getID(), "myTextureSampler");

		glm::mat4 mvp = cam.getViewProj() * modelMatrix[i];

		glUniformMatrix4fv(MvpID, 1, GL_FALSE, &mvp[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);

		glUniform1i(TextureID, 0);

		cube_mesh.draw();
	}
}

void Renderer::update()
{
	for (int i = 0; i < cubes; i++)
	{
		float rate = 0.01f + 0.03f * ((float)rand()) / RAND_MAX;

		glm::vec3 axis = glm::vec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);

		modelMatrix[i] = glm::rotate(modelMatrix[i], rate, axis);
		modelMatrix[i] = glm::rotate(modelMatrix[i], rate, axis);
		modelMatrix[i] = glm::rotate(modelMatrix[i], rate, axis);
	}
}
