#include "Mesh.h"



void Mesh::CreateResources(const std::shared_ptr<Renderer>& pRenderer){

	//todo: Create Dx11 vbo and ib
	
}

void Mesh::LoadFromFile(const std::string& pFileName){


	Assimp::Importer importer;
	const aiScene* const scene = importer.ReadFile(pFileName, aiProcess_Triangulate);
	const aiMesh* const mesh = scene->mMeshes[0];


	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {

		Vertex vertex{};

		vertex.Position.x = mesh->mVertices[i].x;
		vertex.Position.y = mesh->mVertices[i].y;
		vertex.Position.z = mesh->mVertices[i].z;
		vertex.Color.r = mesh->mColors[i]->r;
		vertex.Color.g = mesh->mColors[i]->g;
		vertex.Color.b = mesh->mColors[i]->b;
		vertex.Color.a = mesh->mColors[i]->a;
		vertex.Normal.x = mesh->mNormals[i].x;
		vertex.Normal.y = mesh->mNormals[i].y;
		vertex.Normal.z = mesh->mNormals[i].z;
		//vertex.TexCoord.x = mesh->mTextureCoords[0][i].x;
		//vertex.TexCoord.y = mesh->mTextureCoords[0][i].y;

		mVertices.push_back(vertex);
		
	}


	const std::vector<WORD> indices;

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {

		const aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++) mIndices.push_back(face.mIndices[j]);


	}

	delete scene;
	delete mesh;
	
}
