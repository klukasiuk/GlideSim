#include "renderer.h"

#include <vector>

#include "bmp_loader.h"
#include "mesh_loader.h"
#include "height_map.h"


using std::vector;

void Renderer::init()
{
	plane = new Model("Assets//raptor.obj");

	map = new HeightMap;

	myShader = new Shader("Shaders//texture_vertex.glsl", "Shaders//texture_fragment.glsl");
	//myShader = new Shader("Shaders//color_vertex.glsl", "Shaders//color_fragment.glsl");

	cam.setPosTarg(glm::vec3(0, 8, -14), glm::vec3(0, 0, 0));

	Texture = loadBMP("Assets//suz.bmp");
}

void Renderer::release()
{
	delete myShader;
	delete plane;
	delete map;
}

void Renderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	myShader->use();

	int MvpID = glGetUniformLocation(myShader->getID(), "MVP");
	int TextureID = glGetUniformLocation(myShader->getID(), "myTextureSampler");

	glm::mat4 model_mat = glm::mat4(1.0f);

	model_mat = glm::rotate(model_mat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 mvp = cam.getViewProj() * model_mat;

	glUniformMatrix4fv(MvpID, 1, GL_FALSE, &mvp[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);

	glUniform1i(TextureID, 0);

	plane->draw(myShader);

	map->render(myShader);
}

void Renderer::update()
{
	map->update();

}
