﻿#include "VBO_DX.h"

#include "Renderer_DX.h"


void VBO_DX::Create(std::shared_ptr<Renderer>& pRenderer, const std::string& pMeshName) {

	// Create vertex buffer

	auto dxRenderer = std::dynamic_pointer_cast<DX_Renderer> (pRenderer);
	
	auto vertices = ResourceManager::Instance()->GenerateVertices();


	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * vertices.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &vertices[0];
	auto device = dxRenderer->GetDevice();
	device->CreateBuffer(&bd, &InitData, &mVertexBuffer);

	auto indices = ResourceManager::Instance()->GenerateIndices();

	// Create index buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * indices.size();        // 36 vertices needed for 12 triangles in a triangle list
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = &indices[0];
	device->CreateBuffer(&bd, &InitData, &mIndexBuffer);
	
	mNumberOfIndices = indices.size(); 
	
}
