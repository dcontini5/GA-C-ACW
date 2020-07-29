#include "ResourceManager.h"


#include <iostream>
#include <string>
ResourceManager* ResourceManager::mInstance = nullptr;



std::string ResourceManager::ParseData(const std::vector<glm::vec3>& pPosList){

	std::string data;
	for(const auto& pos : pPosList){

		data.append(std::to_string(pos.x));
		data += ",";
		
		data.append(std::to_string(pos.y));
		data += ",";
		
		data.append(std::to_string(pos.z));
		data += ",";
		
	}

	return data;
	
}

void ResourceManager::ParseMessage(std::string& pMessage){

	std::vector<glm::vec3> posList;

	auto divider = 0;
	auto i = 0;
	
	while (i != pMessage.size()){

		
		divider = pMessage.find(',', (i + 1));
		auto x = std::stof(pMessage.substr(i, divider - i));

		i = divider + 1;
		divider = pMessage.find(',', (i + 1));
		auto y = std::stof(pMessage.substr(i, divider - i));

		i = divider + 1;
		divider = pMessage.find(',', (i + 1));
		auto z = std::stof(pMessage.substr(i, divider - i));

		i = divider + 1;

		posList.emplace_back(x, y, z);
		
	}

	
}

std::vector<WORD> ResourceManager::GenerateIndices(){
	
	std::vector<WORD> indices = {
		0, 1, 2, // -x
		2, 3, 0,

		//4,5,6, // +x
		//5,7,6,
		//
		//0,1,5, // -y
		//0,5,4,
		//
		//2,6,7, // +y
		//2,7,3,
		//
		//0,4,6, // -z
		//0,6,2,
		//
		//1, 3, 7, // +z
		//1, 7, 5,

	};

	mIndicesNo = indices.size();
	
	return indices;
}

std::vector<SimpleVertex> ResourceManager::GenerateVertices(){

	std::vector<SimpleVertex> vertices;
	
	vertices.push_back({DirectX::XMFLOAT3(-1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f) });
	vertices.push_back({DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) });
	vertices.push_back({DirectX::XMFLOAT3(1.0f, -1.0f, 0.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) });
	vertices.push_back({DirectX::XMFLOAT3(-1.0f, -1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f) });

	//vertices.push_back({ XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) });
	//vertices.push_back({ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) });
	//vertices.push_back({ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) });
	//vertices.push_back({ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) });
	//
	//vertices.push_back({ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) });
	//vertices.push_back({ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) });
	//vertices.push_back({ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) });
	//vertices.push_back({ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) });
	//
	//vertices.push_back({ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) });
	//vertices.push_back({ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) });
	//vertices.push_back({ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) });
	//vertices.push_back({ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) });
	//
	//vertices.push_back({ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) });
	//vertices.push_back({ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) });
	//vertices.push_back({ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) });
	//vertices.push_back({ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) });
	//
	//vertices.push_back({ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) });
	//vertices.push_back({ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) });
	//vertices.push_back({ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) });
	//vertices.push_back({ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) });

	return vertices;
	
}

