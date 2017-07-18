#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <SOIL/SOIL.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <vector>

#include "error.h"
#include "shader.h"
#include "camera.h"
#include "timer.h"

void initWindow(int width , int height);

void initOGL();

void closeWindow();

bool shouldClose();

void swapBuffer();

GLuint loadBMP_custom(const char * imagepath);