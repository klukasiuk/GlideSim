#include "model.h"

#include "error.h"

void Model::processNode(aiNode * node, const aiScene * scene)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	vector<unsigned short> indices;
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		glm::vec3 vertex;
		glm::vec2 UV;
		glm::vec3 normal;

		vertex.x = mesh->mVertices[i].x;
		vertex.y = mesh->mVertices[i].y;
		vertex.z = mesh->mVertices[i].z;

		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			UV.x = mesh->mTextureCoords[0][i].x;
			UV.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			UV.x = 0.0f;
			UV.y = 0.0f;
		}

		normal.x = mesh->mNormals[i].x;
		normal.y = mesh->mNormals[i].y;
		normal.z = mesh->mNormals[i].z;

		vertices.push_back(vertex);
		uvs.push_back(UV);
		normals.push_back(normal);
	}


	// Indices

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// TODO Textures

	if (mesh->mMaterialIndex >= 0)
	{
		//aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		//
		//vector<Texture> diffuseMaps = loadMaterialTextures(material,aiTextureType_DIFFUSE, "texture_diffuse");
		//
		//textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		//
		//vector<Texture> specularMaps = loadMaterialTextures(material,aiTextureType_SPECULAR, "texture_specular");
		//
		//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}


	return Mesh(indices,vertices, uvs, normals, vector<glm::vec3>());
}

Model::Model(char * path)
{
	model_path = string(path);

	Assimp::Importer importer;

	unsigned int loader_flags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_OptimizeMeshes;

	const aiScene *scene = importer.ReadFile(path, loader_flags);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		error::msg(importer.GetErrorString(), "Assimp loading error");
		return;
	}

	directory = model_path.substr(0, model_path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::draw(Shader * shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].draw(shader);
}
