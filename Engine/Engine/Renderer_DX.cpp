#include "Renderer_DX.h"
#include "Mesh.h"
#include <iostream>
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"


void DX_Renderer::InitRenderer(){

	CreateDevice();
	DefineDeviceProperties();
	CreateSwapChain();
	CreateRenderTargetView();
	CreateShaders();
	CreateMVPM();
	CreateVBO();
	InitUi();

}

void DX_Renderer::Cleanup(){


	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	mUI->CleanUI();
}

void DX_Renderer::ClearScreen(){

	//
	// Clear the back buffer
	//
	mD3D11ImmediateContext->OMSetRenderTargets(1, mD3D11RenderTargetView.GetAddressOf(), mD3D11DepthStencilView.Get());
	mD3D11ImmediateContext->ClearRenderTargetView(mD3D11RenderTargetView.Get(), DirectX::Colors::LightBlue);
	mD3D11ImmediateContext->ClearDepthStencilView(mD3D11DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	
	
}

void DX_Renderer::Present(){

	mDXGISwapChain->Present(0, 0);
	
}

void DX_Renderer::InitUi(){

	mUI->Init();
	ImGui_ImplWin32_Init(mHWindow);
	ImGui_ImplDX11_Init(mD3D11Device.Get(), mD3D11ImmediateContext.Get());

	
}

void DX_Renderer::RenderUI(){

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	mUI->DrawFrame();
	
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
}

void DX_Renderer::CreateDevice(){


	//RECT rc;
	//GetClientRect(mHWindow, &rc);
	//UINT width = rc.right - rc.left;
	//UINT height = rc.bottom - rc.top;


	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);
	auto hr = S_OK;
	
	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		mDriverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(nullptr, mDriverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &mD3D11Device, &mFeatureLevel, &mD3D11ImmediateContext);
		

		if (hr == E_INVALIDARG)
		{
			// DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
			hr = D3D11CreateDevice(nullptr, mDriverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
				D3D11_SDK_VERSION, &mD3D11Device, &mFeatureLevel, &mD3D11ImmediateContext);
		}

		if (SUCCEEDED(hr))
			break;
	}

}

void DX_Renderer::DefineDeviceProperties(){

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterState = nullptr;

	D3D11_RASTERIZER_DESC rasterDesc;

	rasterDesc.CullMode = D3D11_CULL_NONE;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.ScissorEnable = false;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	mD3D11Device->CreateRasterizerState(&rasterDesc, &rasterState);
	mD3D11ImmediateContext->RSSetState(rasterState.Get());

	mD3D11ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	
	// Create the constant buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	mD3D11Device->CreateBuffer(&bd, nullptr, &mD3D11ConstantBuffer);

}


void DX_Renderer::CreateSwapChain(){


	// Obtain DXGI factory from device (since we used nullptr for pAdapter above)
	Microsoft::WRL::ComPtr<IDXGIFactory1> dxgiFactory = nullptr;
	{
		Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice = nullptr;
		;
		if (SUCCEEDED(mD3D11Device->QueryInterface(__uuidof(IDXGIDevice), &dxgiDevice)))
		{
			IDXGIAdapter* adapter = nullptr;
			if (SUCCEEDED(dxgiDevice->GetAdapter(&adapter)))
			{
				adapter->GetParent(__uuidof(IDXGIFactory1), &dxgiFactory);
				adapter->Release();
			}
			dxgiDevice->Release();
		}
	}


	// Create swap chain
	Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory2 = nullptr;
	dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), &dxgiFactory2);
	if (dxgiFactory2)
	{
		// DirectX 11.1 or later
		;
		if (SUCCEEDED(mD3D11Device->QueryInterface(__uuidof(ID3D11Device1), &mD3D11Device1)))
		{
			mD3D11ImmediateContext->QueryInterface(__uuidof(ID3D11DeviceContext1), &mD3D11ImmediateContext1);
		}

		DXGI_SWAP_CHAIN_DESC1 sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.Width = mWidth;
			sd.Height = mHeight;
			sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
			//sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;

		if (SUCCEEDED(dxgiFactory2->CreateSwapChainForHwnd(mD3D11Device1.Get(), mHWindow, &sd, nullptr, nullptr, &mDXGISwapChain1)))
		{
			mDXGISwapChain1->QueryInterface(__uuidof(IDXGISwapChain), &mDXGISwapChain);
		}

		dxgiFactory2->Release();
	}
	else
	{
		// DirectX 11.0 systems
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Width = mWidth;
		sd.BufferDesc.Height = mHeight;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = mHWindow;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;

		dxgiFactory->CreateSwapChain(mD3D11Device.Get(), &sd, &mDXGISwapChain);
	}

	// Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
	dxgiFactory->MakeWindowAssociation(mHWindow, DXGI_MWA_NO_ALT_ENTER);

	dxgiFactory->Release();

	
}

void DX_Renderer::CreateRenderTargetView() {

	auto hr = S_OK;
	// Create a render target view
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer = nullptr;
	//ID3D11Texture2D* pBackBuffer = nullptr;
	mDXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer);


	mD3D11Device->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &mD3D11RenderTargetView);
	//pBackBuffer->Release();

	
	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = mWidth;
	descDepth.Height = mHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = mD3D11Device->CreateTexture2D(&descDepth, nullptr, &mD3D11DepthStencil);


	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = mD3D11Device->CreateDepthStencilView(mD3D11DepthStencil.Get(), &descDSV, &mD3D11DepthStencilView);

	
	
	//mD3D11ImmediateContext->OMSetRenderTargets(1, mD3D11RenderTargetView.GetAddressOf(), mD3D11DepthStencilView.Get());
	
	//mD3D11ImmediateContext->OMSetRenderTargets(1, &mD3D11RenderTargetView, nullptr);
	
	
	

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<FLOAT>(mWidth);
	vp.Height = static_cast<FLOAT>(mHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	mD3D11ImmediateContext->RSSetViewports(1, &vp);

}

void DX_Renderer::CreateShaders(){

	// Compile the vertex shader
	Microsoft::WRL::ComPtr<ID3DBlob> pVSBlob = nullptr;
	
	if (FAILED(CompileShaderFromFile(L"Shaders/VSLight.hlsl", "VS", "vs_4_0", &pVSBlob)))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return;
	}

	// Create the vertex shader
	
	if (FAILED(mD3D11Device->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &mD3D11VertexShader)))
	{
		return;
	}

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	auto hr = mD3D11Device->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &mD3D11VertexLayout);
	if (FAILED(hr))
		return;

	// Set the input layout
	mD3D11ImmediateContext->IASetInputLayout(mD3D11VertexLayout.Get());

	// Compile the pixel shader
	Microsoft::WRL::ComPtr<ID3DBlob>  pPSBlob = nullptr;

	
	if (FAILED(CompileShaderFromFile(L"Shaders/PSLight.hlsl", "PS", "ps_4_0", &pPSBlob)))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return;
	}

	// Create the pixel shader
	hr = mD3D11Device->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &mD3D11PixelShader);
	if (FAILED(hr))
		return;
	
}

void DX_Renderer::CreateMVPM(){

	// Initialize the world matrix
	mWorld = DirectX::XMMatrixIdentity();

	// Initialize the view matrix
	const glm::vec3 camPos = mCamera->GetPos();
	
	DirectX::XMVECTOR Eye = DirectX::XMVectorSet(camPos.x, camPos.y, camPos.z, 0.0f);

	
	//DirectX::XMVECTOR Eye = DirectX::XMVectorSet(0.0f, 8.0f, 6.0f, 0.0f);
	DirectX::XMVECTOR Forward = DirectX::XMVectorSet(0.0f, 3.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	mView = DirectX::XMMatrixLookAtLH(Eye, Forward, Up);

	
	// Initialize the projection matrix
	//
	// 
	//g_Projection = setProjectionMatrix(width / (FLOAT)height, height, 0.01f, 100.0f);

	//g_View = setViewMatrix(Eye, At, Up);

	mProjection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, mWidth / (FLOAT)mHeight, 0.01f, 100.0f);

}

void DX_Renderer::CreateVBO(){

   //
	//mVBO = std::make_shared<VBO_DX>();
	//auto x = this;
	////
	//mVBO->Create(this, 10);
	//mVBO->Set(mD3D11ImmediateContext);
}  //


HRESULT DX_Renderer::CompileShaderFromFile(const LPCWSTR& pFileName, const LPCSTR& pEntryPoint,
                                           const LPCSTR& pShaderModel, ID3DBlob** const pBlobOut) {
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(pFileName, nullptr, nullptr, pEntryPoint, pShaderModel,
		dwShaderFlags, 0, pBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return hr;
	
}

void DX_Renderer::Render(std::shared_ptr<Mesh>& pMesh,const glm::vec3 pPos,const glm::vec3 pScale){

	//
	// Update variables
	//
	ConstantBuffer cb{};

	auto world = mWorld;
	
	world *= DirectX::XMMatrixScaling(pScale.x, pScale.y, pScale.z);
	world *= DirectX::XMMatrixTranslation(pPos.x, pPos.y, pPos.z);
	
	
	cb.mWorld = DirectX::XMMatrixTranspose(world);
	cb.mView = DirectX::XMMatrixTranspose(mView);
	cb.mProjection = DirectX::XMMatrixTranspose(mProjection);
	cb.time = 0;
	cb.lightPos = DirectX::XMVectorSet(0.0f, 12.0f, 0.0f, 0.0f);
	cb.Eye = DirectX::XMVectorSet(0.0f, 3.0f, 3.0f, 0.0f);
	mD3D11ImmediateContext->UpdateSubresource(mD3D11ConstantBuffer.Get(), 0, nullptr, &cb, 0, 0);

	std::shared_ptr<VBO_DX> vbo = std::reinterpret_pointer_cast<VBO_DX>(pMesh->GetVBO());
	
	vbo->Set(mD3D11ImmediateContext);
	
	//
	// Render
	//
	mD3D11ImmediateContext->VSSetShader(mD3D11VertexShader.Get(), nullptr, 0);
	mD3D11ImmediateContext->PSSetShader(mD3D11PixelShader.Get(), nullptr, 0);
	mD3D11ImmediateContext->VSSetConstantBuffers(0, 1, mD3D11ConstantBuffer.GetAddressOf());
	mD3D11ImmediateContext->PSSetConstantBuffers(0, 1, mD3D11ConstantBuffer.GetAddressOf());
	mD3D11ImmediateContext->DrawIndexed(vbo->GetNumberOfIndices(), 0, 0);


	
}
