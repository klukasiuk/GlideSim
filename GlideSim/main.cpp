#include "simple_window.h"

const int Width = 640;
const int Height = 480;

GLuint VertexArrayID;
GLuint vertexbuffer;
GLuint uvbuffer;

GLuint MatrixID;
glm::mat4 mvp;

GLuint TextureID;
GLuint Texture;

glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;

std::vector<glm::mat4> modelMatrix;

Shader * myShader;

Camera myCam;

FpsCounter  fpsCounter;
FpsGovernor fpsGovernor;

// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};

// One color for each vertex. They were generated randomly.
// Two UV coordinatesfor each vertex. They were created withe Blender.
static const GLfloat g_uv_buffer_data[] = {
	0.000059f, 1.0f - 0.000004f,
	0.000103f, 1.0f - 0.336048f,
	0.335973f, 1.0f - 0.335903f,
	1.000023f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.336024f, 1.0f - 0.671877f,
	0.667969f, 1.0f - 0.671889f,
	1.000023f, 1.0f - 0.000013f,
	0.668104f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.000059f, 1.0f - 0.000004f,
	0.335973f, 1.0f - 0.335903f,
	0.336098f, 1.0f - 0.000071f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.336024f, 1.0f - 0.671877f,
	1.000004f, 1.0f - 0.671847f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.668104f, 1.0f - 0.000013f,
	0.335973f, 1.0f - 0.335903f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.668104f, 1.0f - 0.000013f,
	0.336098f, 1.0f - 0.000071f,
	0.000103f, 1.0f - 0.336048f,
	0.000004f, 1.0f - 0.671870f,
	0.336024f, 1.0f - 0.671877f,
	0.000103f, 1.0f - 0.336048f,
	0.336024f, 1.0f - 0.671877f,
	0.335973f, 1.0f - 0.335903f,
	0.667969f, 1.0f - 0.671889f,
	1.000004f, 1.0f - 0.671847f,
	0.667979f, 1.0f - 0.335851f
};

void init()
{
	logger::init();

	srand((unsigned int)time(NULL));

	initWindow(Width, Height);

	initOGL();



	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);


	myShader = new Shader("Shaders//texture_vertex.glsl", "Shaders//texture_fragment.glsl");


	myCam.setPosTarg(glm::vec3(0,0,-10),glm::vec3(0,0,0));

	// Model matrix : an identity matrix (model will be at the origin)
	Model = glm::mat4(1.0f);

	//Model = glm::rotate(Model, 10.0f, glm::vec3(0, 0, 1));

	// Our ModelViewProjection : multiplication of our 3 matrices
	mvp = myCam.getViewProj() * Model; // Remember, matrix multiplication is the other way around


	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	MatrixID = glGetUniformLocation(myShader->getID(), "MVP");

	Texture = loadBMP_custom("uvtemplate.bmp");

	TextureID = glGetUniformLocation(myShader->getID(), "myTextureSampler");

	for (int i = 0; i < 10; i++)
	modelMatrix.push_back(glm::mat4(1.0f));

	for (int i = 0; i < 10; i++)
	modelMatrix[i] = glm::translate(modelMatrix[i], glm::vec3(-10 + rand() % 20,-10 + rand() % 20, rand()%10));

	fpsCounter.Start();

	fpsGovernor.setLimit(30);
	fpsGovernor.Start();

	logger::logSystemInfo();

	logger::msg("Initializing done");

}

void release()
{
	closeWindow();

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);

	delete myShader;

	logger::msg("Exiting ...",logger::info);

	exit(EXIT_SUCCESS);
}

void input()
{
	glfwPollEvents();
} 

void update()
{
	for (int i = 0; i < 10; i++)
	{
		modelMatrix[i] = glm::rotate(modelMatrix[i], 0.04f, glm::vec3(0, 1, 0));
		modelMatrix[i] = glm::rotate(modelMatrix[i], 0.03f, glm::vec3(1, 0, 0));
		modelMatrix[i] = glm::rotate(modelMatrix[i], 0.01f, glm::vec3(0, 0, 1));
	}

	myCam.zoom(1.001f);

	fpsCounter.frameTick();
	fpsGovernor.frameTick();

	//logger::msg("Fps = " + std::to_string(fpsCounter.getFPS()));
	printf("FPS = %lf\n", fpsCounter.getFPS());
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	myShader->use();

	for (int i = 0; i < 10; i++)
	{
		mvp = myCam.getViewProj() * modelMatrix[i];

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

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}

	swapBuffer();
}

void timer()
{
	sleep(16);
}

int main()
{
	init();

	while (!shouldClose())
	{
		input();

		update();

		draw();

		timer();
	}

	release();
}