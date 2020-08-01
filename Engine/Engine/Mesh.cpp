#include "Mesh.h"
#include "VBO_DX.h"
#include "ResourceManager.h"

void Mesh::CreateVBO(std::shared_ptr<Renderer>& pRenderer){

	mVBO = std::make_shared<VBO_DX>();

	auto RM = ResourceManager::Instance();
	mVBO->Create(pRenderer, mVertices, mIndices);
	
}
