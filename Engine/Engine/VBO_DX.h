#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

#include "ResourceManager.h"
#include "VBO.h"

class VBO_DX : public VBO {

	//Structors
public:
	VBO_DX() : VBO() {}
	VBO_DX(const VBO_DX&);
	VBO_DX(VBO_DX&&); //exchange members here;
	~VBO_DX() = default;

	//Accessors
public:
	int GetNumberOfIndices() const { return mNumberOfIndices; }
	//Mutators
public:

	// Public Functions
public:

	void Create(std::shared_ptr<Renderer>& pRenderer, const std::string& pMeshName) override;
	void Draw() override { return; }

	void Set(Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pD3D11ImmediateContext) {
		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;
		pD3D11ImmediateContext->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
		pD3D11ImmediateContext->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
		
	}

	// Private Functions
private:

	//Operators
public:
	VBO_DX& operator=(const VBO_DX& pOther) = delete;

	VBO_DX& operator=(const VBO_DX&& pOther) = delete;

	//Data:
private:

	Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer = nullptr;
	int mNumberOfIndices = 0;
	
};

