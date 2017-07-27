#pragma once

#include <vector>
#include <string>

#include <assimp/Importer.hpp>				// C++ importer interface
#include <assimp/scene.h>					// Output data structure
#include <assimp/postprocess.h>				// Post processing flags

#include "mesh.h"
#include "shader.h"

using std::vector;
using std::string;


class Model
{
private :

	string model_path;
	string directory;

	vector<Mesh>  meshes;

	vector<int> texture_ids;


	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);

public :

	Model(char * path);

	void draw(Shader * shader);
};