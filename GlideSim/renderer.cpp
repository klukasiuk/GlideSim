#include "renderer.h"

#include <vector>

#include "bmp_loader.h"
#include "mesh_loader.h"
#include "height_map.h"
#include "primitives.h"


using std::vector;

void Renderer::init()
{
	plane = new Model("Assets//raptor.obj");

	map = new HeightMap;

	object_shader = new Shader("Shaders//std_shading_vertex.glsl", "Shaders//std_shading_fragment.glsl");

	light_cube_shader = new Shader("Shaders//light_cube_vertex.glsl", "Shaders//light_cube_fragment.glsl");

	terrain_shader = new Shader("Shaders//terrain_vertex.glsl", "Shaders//terrain_fragment.glsl");

	core::camera.setPosTarg(glm::vec3(0, 24, 14), glm::vec3(0, 20, 0));

	Texture = loadBMP("Assets//suz.bmp");

	pointLight.position = glm::vec3(0, 50, 0);
	pointLight.ambient = glm::vec3(1.0, 1.0, 1.0);

	plane_mat.ambient = glm::vec3(0.5, 0.5, 0.5);
}

void Renderer::release()
{
	delete object_shader;
	delete light_cube_shader;
	delete terrain_shader;
	delete plane;
	delete map;
}

void Renderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	object_shader->use();

	object_shader->setVec3("objectColor", plane_mat.ambient);
	object_shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	object_shader->setVec3("lightPos", pointLight.position);
	
	glm::mat4 model_mat = glm::mat4(1.0f);
	model_mat = glm::rotate(model_mat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model_mat = glm::translate(model_mat, glm::vec3(0.0f, 0.0f, 20.0f));

	glm::mat4 MVP = core::camera.getProj() * core::camera.getView() * model_mat;
	
	object_shader->setMat4("M", model_mat);
	object_shader->setMat4("V", core::camera.getView());
	object_shader->setMat4("MVP", MVP);

	plane->draw(object_shader);


	terrain_shader->use();

	map->render(terrain_shader);


	light_cube_shader->use();

	render_cube(pointLight.position, 0.2f, light_cube_shader);
}

void Renderer::update()
{
	map->update();

}
