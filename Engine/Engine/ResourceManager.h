﻿#pragma once
#include <Windows.h>
#include <directxmath.h>
#include <vector>
#include <glm.hpp>


struct SimpleVertex
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 texCoord;
};


class ResourceManager {

	//Private Structors
private:
	ResourceManager() = default;

	//Public Structors
public:
	~ResourceManager() = default;

	static ResourceManager* Instance(){

		if (!mInstance){ mInstance = new ResourceManager(); }

		return mInstance;
	}

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:

	std::string ParseData(const std::vector<glm::vec3>& pPosList);
	void ParseMessage(std::string&);
	std::vector<WORD> GenerateIndices();
	std::vector<SimpleVertex> GenerateVertices();
	int GetIndNo() const { return mIndicesNo; }
	// Private Functions
private:

	//Data:
private:
	static ResourceManager* mInstance;
	int mIndicesNo = 0;
	//std::string  mParsedData = ""; //todo use it maybe?
	
};
