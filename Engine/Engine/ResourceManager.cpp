#include "ResourceManager.h"



#include <fstream>
#include <iostream>
#include <string>
#include "Mesh.h"
#include "Renderer.h"
//#include <glm.hpp>

ResourceManager* ResourceManager::mInstance = nullptr;

void ResourceManager::ParseLine(std::string& line){

	const size_t delim = line.find('=');
	
	const std::string settingName = line.substr(0, delim - 1);
	line.erase(0, delim + 2);
	const std::string settingValue = line.substr(0, line.size());

	if(settingName == "ServerAddress"){

		mSettings.ServerAddress = settingValue;
		return;
	}

	if (settingName == "ClientAddress") {

		mSettings.ClientAddress = settingValue;
		return;
	}

	if (settingName == "Port") {

		mSettings.Port = std::stoi(settingValue);
		return;
	}

	if (settingName == "PyramidHeight") {

		mSettings.PyramidHeight = std::stoi(settingValue);
		return;
	}


	if (settingName == "Height") {

		mSettings.Height = std::stoi(settingValue);
		return;
	}

	if (settingName == "Width") {

		mSettings.Width = std::stoi(settingValue);
		return;
	}

}

void ResourceManager::LoadSettings(){

	std::string line;
	std::ifstream settings("settings.ini");

	if(settings.is_open()){
		
		while (settings.good()){

			std::getline(settings, line);

			if (line[0] == '[') continue;

			ParseLine(line);
			
			
			
		}

		
	}
	
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

void ResourceManager::LoadMesh(const PrefabMeshes& pMeshType, std::shared_ptr<Renderer>& pRenderer){


	if(pMeshType == PLANE){

		const auto vertices = GenerateVertices();
		const auto indices = GenerateIndices();

		
		auto newMesh = std::make_shared<Mesh>(vertices, indices);

		newMesh->CreateVBO(pRenderer);

		if (mMeshes.find("Plane") == mMeshes.end()) {

			mMeshes["Plane"] = newMesh;

		}

		
	}else{

		Vertices vertices;
		Indices indices;
		
		CreateSphereGeometry(vertices, indices, 10, 10);

		auto newMesh = std::make_shared<Mesh>(vertices, indices);

		newMesh->CreateVBO(pRenderer);

		if (mMeshes.find("Sphere") == mMeshes.end()) {

			mMeshes["Sphere"] = newMesh;

		}

		
	}

	
}

std::shared_ptr<Mesh> ResourceManager::GetMesh(const std::string& pName){

	if(mMeshes.find(pName) != mMeshes.end()){

		return mMeshes[pName];
		
	}

	return nullptr;
	
}


std::vector<WORD> ResourceManager::GenerateIndices(){
	
	std::vector<WORD> indices = {
		
		0, 1, 2, // -x
		2, 3, 0,

	};

	mIndicesNo = indices.size();
	
	return indices;
}

std::vector<SimpleVertex> ResourceManager::GenerateVertices(){

	std::vector<SimpleVertex> vertices;

	auto inf = 10000.f;
	
	
	//vertices.push_back({DirectX::XMFLOAT3(-1.0f,  0.0f, 1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f) });
	//vertices.push_back({DirectX::XMFLOAT3(1.0f,  0.0f, 1.0f),  DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f) });
	//vertices.push_back({DirectX::XMFLOAT3(1.0f, 0.0f, -1.0f),  DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) });
	//vertices.push_back({DirectX::XMFLOAT3(-1.0f, 0.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) });

	vertices.push_back({ DirectX::XMFLOAT3(-inf,  0.0f, inf), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) });
	vertices.push_back({ DirectX::XMFLOAT3(inf,  0.0f, inf), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) });
	vertices.push_back({ DirectX::XMFLOAT3(inf, 0.0f, -inf), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f) });
	vertices.push_back({ DirectX::XMFLOAT3(-inf, 0.0f, -inf), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f) });

	return vertices;
	
}


// Code taken from http://www.songho.ca/opengl/gl_sphere.html
void ResourceManager::CreateSphereGeometry(std::vector<SimpleVertex>& vertices, std::vector<WORD>& indices, const  int& pSectorCount = 10, const int& pStackCount = 10 ) {

	auto radius = 1.0f;
	const auto sectorCount = pSectorCount;
	const auto stackCount = pStackCount;

	auto const pi = DirectX::XM_PI;

	
	
	float x, y, z, xy;                              // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
	float s, t;                                     // vertex texCoord

	float sectorStep = 2 * pi / sectorCount;
	float stackStep = pi / stackCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i)
	{

	
		stackAngle = pi / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);             // r * cos(u)
		z = radius * sinf(stackAngle);              // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= sectorCount; ++j)
		{


			SimpleVertex vertex{};
			
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
			vertex.pos = { x, y ,z };


			// normalized vertex normal (nx, ny, nz)
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;

			vertex.normal = { nx, ny, nz };
			

			// vertex tex coord (s, t) range between [0, 1]
			s = (float)j / sectorCount;
			t = (float)i / stackCount;

			vertex.texCoord = { s, t };
			
			vertex.color = { 1.0,1.0,1.0,1.0 };
			
			vertices.push_back(vertex);

		}
	}

	int k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     // beginning of current stack
		k2 = k1 + sectorCount + 1;      // beginning of next stack

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}

}