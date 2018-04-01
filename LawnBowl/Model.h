#pragma once
#include "Mesh.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <iostream>
#include <string>
#include <vector>

class Model
{
	std::vector<Texture> textures_loaded;
	std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	void LoadModel(std::string const &path);
public:
	std::string directory;
	std::vector<Mesh> meshes;
	bool gammaCorrection;
	Model();
	Model(std::string const &path, bool gamma = false);
	void AddNewMesh(std::vector<Vertex>& verts, std::vector<unsigned int>& inds);
	~Model();

	void Draw() const;
};

