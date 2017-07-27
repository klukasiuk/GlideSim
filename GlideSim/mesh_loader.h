#pragma once

#include <vector>

#include <GLM/glm.hpp>

using std::vector;

bool loadObjCustom(char * path, vector<glm::vec3>& out_vertices, vector<glm::vec2>& out_uvs, vector<glm::vec3>& out_normals);

bool loadMeshAssimp(char * path, vector<unsigned short> & indices, vector<glm::vec3> & vertices, vector<glm::vec2> & uvs, vector<glm::vec3> & normals);