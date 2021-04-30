#pragma once
#include <chrono>
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <DirectXColors.h>
#include <wrl.h>
#include <memory>
#include <thread>

#include "Resource.h"

#include "VBO_DX.h"
#include "Renderer.h"

#include "ThreadManager.h"


struct ConstantBuffer
{
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mView;
	DirectX::XMMATRIX mProjection;
	float time;
	DirectX::XMVECTOR lightPos;
	DirectX::XMVECTOR Eye;
};


class DX_Renderer : public Renderer {

	//Structors
public:
	DX_Renderer(const HWND pHWindow,  const UINT& pHeight, const UINT& pWidth) : Renderer(pHeight, pWidth),
	                                                                             mHWindow(pHWindow), mWorld(DirectX::XMMatrixIdentity()), mView(DirectX::XMMatrixIdentity()),
	                                                                             mProjection(DirectX::XMMatrixIdentity()){}

	DX_Renderer(const DX_Renderer&);
	DX_Renderer(DX_Renderer&&); //exchange members here;
	~DX_Renderer() = default;

	

	
	//Accessors
public:
	
	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() const { return mD3D11Device; }
	
	//Mutators
public:

	// Public Functions
public:
	void Render(std::shared_ptr<Mesh>& pMesh,const glm::vec3 pPos,const glm::vec3 pScale) override;
	void InitRenderer() override;
	void Cleanup() override;
	void StopRunning() override { mRun = false; }
	void Run() override {};
	void ClearScreen() override;
	void Present() override;
	void InitUi() override;
	void RenderUI() override;


	
	
	
	// Private Functions
private:

	void CreateDevice();
	void DefineDeviceProperties();
	void CreateSwapChain();
	void CreateRenderTargetView();
	void CreateShaders();
	void CreateMVPM();
	void CreateVBO();
	
	HRESULT CompileShaderFromFile(const LPCWSTR& pFileName,const LPCSTR& pEntryPoint,const LPCSTR& pShaderModel, ID3DBlob** const pBlobOut);


	
	//Operators
public:
	DX_Renderer& operator=(const DX_Renderer& pOther) = delete;

	DX_Renderer& operator=(const DX_Renderer&& pOther) = delete;

	//Data:
private:
	HWND      mHWindow = nullptr;
	
	
	D3D_DRIVER_TYPE									mDriverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL								mFeatureLevel = D3D_FEATURE_LEVEL_11_0;
	Microsoft::WRL::ComPtr<ID3D11Device>			mD3D11Device = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Device1>			mD3D11Device1 = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>		mD3D11ImmediateContext = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1>	mD3D11ImmediateContext1 = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain>			mDXGISwapChain = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain1>			mDXGISwapChain1 = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	mD3D11RenderTargetView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	mD3D11DepthStencilView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>			mD3D11DepthStencil = nullptr;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>      mD3D11VertexShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>       mD3D11PixelShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>		mD3D11VertexLayout = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>			mD3D11ConstantBuffer = nullptr;

	
	std::shared_ptr<VBO_DX>							mVBO = nullptr;
	//std::shared_ptr<VBO_DX> mVbo = nullptr;
	//VBO_DX* mVbo = nullptr;

	bool											mRun = true;
	
	DirectX::XMMATRIX								mWorld;
	DirectX::XMMATRIX								mView;
	DirectX::XMMATRIX								mProjection;
	
};


