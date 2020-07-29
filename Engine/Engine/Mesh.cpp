#include "Mesh.h"
#include "VBO_DX.h"

void Mesh::CreateVBO(std::shared_ptr<Renderer>& pRenderer, const std::string& pMeshName){

	mVBO = std::make_shared<VBO_DX>();

	auto RM = ResourceManager::Instance();
	mVBO->Create(pRenderer, pMeshName);
	
}
