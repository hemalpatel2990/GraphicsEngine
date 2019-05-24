#include "DXApp.h"
#include <windows.h>
#include <sstream>
#include <assert.h>
#include "d3dUtil.h"

// needed to load shaders from file
#include <d3dcompiler.h>

#include "Model.h"
#include "ShaderColor.h"
#include "DirectXTex.h"
#include "Texture.h"
#include "FlatPlane.h"
#include "TerrainModel.h"
#include "GraphicObject_ColorLight.h"
#include "GraphicObject_TextureLight.h"
#include "GraphicObject_Texture.h"
#include "ShaderTextureLight.h"
#include "ShaderTexture.h"
#include "SkyBox.h"

void DXApp::InitDemo()
{
	//-------------------- Texture Initialization ---------------------------------
	pTex1   = new Texture(md3dDevice, L"../Assets/Textures/WoodCabin.tga");
	pTex2   = new Texture(md3dDevice, L"../Assets/Textures/Dice.tga");
	pTexSkybox = new Texture(md3dDevice, L"../Assets/Textures/skybox3.tga");
	pGrassTex = new Texture(md3dDevice, L"../Assets/Textures/ground.tga", D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT);
	pWater = new Texture(md3dDevice, L"../Assets/Textures/water.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	pMountain = new Texture(md3dDevice, L"../Assets/Textures/mountainTexture.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	pWatchTowerTex = new Texture(md3dDevice, L"../Assets/Textures/watchtower.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	pWatchGroundTex = new Texture(md3dDevice, L"../Assets/Textures/groundwatch.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	pBoatTex = new Texture(md3dDevice, L"../Assets/Textures/Textureboat.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	pFrigateTex = new Texture(md3dDevice, L"../Assets/Textures/space_frigate.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	//-------------------- Shader Initialization ----------------------------------
	pShaderColLight = new ShaderColorLight(md3dDevice);
	pShaderColLight->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(),
		.2 * Vect(1, 1, 1), .3 * Vect(1, 1, 1), Vect(1, 1, 1));
	pShaderColLight->SetPointLightParameters(Vect(0, 10, 0), 100, .2 * Vect(0, 1, 0),
		.4 * Vect(1, 1, 1), 1 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	pShaderTexLight = new ShaderTextureLight(md3dDevice);
	pShaderTexLight->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(),
		.2 * Vect(1, 1, 1), .2 * Vect(1, 1, 1), .5 * Vect(1, 1, 1));

	//-------------------- Model Initialization-------------------------------------
	pSkyBox  = new SkyBox(md3dDevice, 500);
	pTerrain = new TerrainModel(md3dDevice, L"../Assets/Textures/HMGS.tga", 200, 2, -7.5, 10, 10);
	pWaterTerrain = new TerrainModel(md3dDevice, L"../Assets/Textures/HMGS.tga", 200, 0, -7, 10, 10);
	pMountainTerrain = new TerrainModel(md3dDevice, L"../Assets/Textures/mountain.tga", 100, 50, -9, 5, 5);
	pWatchTower = new Model(md3dDevice, "../Assets/Models/watchtower.azul");
	pWatchGround = new Model(md3dDevice, "../Assets/Models/Ground.azul");
	pWoodBoat = new Model(md3dDevice, "../Assets/Models/woodboat.azul");
	pModel1 = new Model(md3dDevice, "../Assets/Models/space_frigate.azul");
	pModel2 = new Model(md3dDevice, "../Assets/Models/WoodenCabin1.azul");

	//------------------- Graphic Object Initialization ---------------------------
	GraphObjSkyBox = new GraphicObject_TextureLight(pShaderTexLight, pSkyBox->GetModel(), pTexSkybox);
	
	GraphTerrain = new GraphicObject_TextureLight(pShaderTexLight, pTerrain->GetModel(), pGrassTex);
	GraphTerrain->SetWorld(pTerrain->GetWorldMat());
	GraphTerrain->SetFogData(Colors::Gray, 100.0f, 100.0f);
	
	GraphWater = new GraphicObject_TextureLight(pShaderTexLight, pWaterTerrain->GetModel(), pWater);
	GraphWater->SetWorld(pWaterTerrain->GetWorldMat());
	GraphWater->SetFogData(Colors::Gray, 50.0f, 100.0f);
	
	GraphMountain = new GraphicObject_TextureLight(pShaderTexLight, pMountainTerrain->GetModel(), pMountain);
	Matrix mountWorld = pMountainTerrain->GetWorldMat() * Matrix(TRANS, 0, 0, 75);
	GraphMountain->SetWorld(mountWorld);

	GraphObj1 = new GraphicObject_TextureLight(pShaderTexLight, pModel2, pTex1);
	GraphObj1->SetMaterial(0.5f * Colors::White, 0.5f * Colors::White, Vect(.5f, .5f, .5f, 500));
	GraphObj1->SetTexture(pTex1);
	GraphObj1->SetFogData(Colors::White, 100.0f, 100.0f);

	GraphObj2 = new GraphicObject_TextureLight(pShaderTexLight, pModel2, pTex1);
	GraphObj2->SetMaterial(0.5f * Colors::White, 0.5f * Colors::White, Vect(.5f, .5f, .5f, 500));
	GraphObj2->SetTexture(pTex1);
	GraphObj2->SetFogData(Colors::White, 100.0f, 100.0f);

	GraphObj3 = new GraphicObject_TextureLight(pShaderTexLight, pModel2, pTex1);
	GraphObj3->SetMaterial(0.5f * Colors::White, 0.5f * Colors::White, Vect(.5f, .5f, .5f, 500));
	GraphObj3->SetTexture(pTex1);
	GraphObj3->SetFogData(Colors::White, 100.0f, 100.0f);

	GraphObj4 = new GraphicObject_TextureLight(pShaderTexLight, pModel2, pTex1);
	GraphObj4->SetMaterial(0.5f * Colors::White, 0.5f * Colors::White, Vect(.5f, .5f, .5f, 500));
	GraphObj4->SetTexture(pTex1);
	GraphObj4->SetFogData(Colors::White, 100.0f, 100.0f);

	GraphObj5 = new GraphicObject_TextureLight(pShaderTexLight, pModel2, pTex1);
	GraphObj5->SetMaterial(0.5f * Colors::White, 0.5f * Colors::White, Vect(.5f, .5f, .5f, 500));
	GraphObj5->SetTexture(pTex1);
	GraphObj5->SetFogData(Colors::White, 100.0f, 100.0f);

	GraphObj6 = new GraphicObject_TextureLight(pShaderTexLight, pModel2, pTex1);
	GraphObj6->SetMaterial(0.5f * Colors::White, 0.5f * Colors::White, Vect(.5f, .5f, .5f, 500));
	GraphObj6->SetTexture(pTex1);
	GraphObj6->SetFogData(Colors::White, 100.0f, 100.0f);

	GraphObj7 = new GraphicObject_TextureLight(pShaderTexLight, pModel2, pTex1);
	GraphObj7->SetMaterial(0.5f * Colors::White, 0.5f * Colors::Red, Vect(.5f, .5f, .5f, 500));
	GraphObj7->SetTexture(pTex1);
	GraphObj7->SetFogData(Colors::White, 100.0f, 100.0f);

	GraphObj8 = new GraphicObject_TextureLight(pShaderTexLight, pModel2, pTex1);
	GraphObj8->SetMaterial(0.5f * Colors::White, 0.5f * Colors::Red, Vect(.5f, .5f, .5f, 500));
	GraphObj8->SetTexture(pTex1);
	GraphObj8->SetFogData(Colors::White, 100.0f, 100.0f);

	GraphWatchTower = new GraphicObject_TextureLight(pShaderTexLight, pWatchTower, pWatchTowerTex);
	GraphWatchTower->SetMaterial(0.5f * Colors::White, 0.5f * Colors::White, Vect(.5f, .5f, .5f, 500));
	GraphWatchTower->SetTexture(pWatchTowerTex);

	GraphGround = new GraphicObject_TextureLight(pShaderTexLight, pWatchGround, pWatchGroundTex);
	GraphGround->SetMaterial(0.5f * Colors::White, 0.5f * Colors::White, Vect(.5f, .5f, .5f, 500));
	GraphGround->SetTexture(pWatchGroundTex);

	GraphWatchTower1 = new GraphicObject_TextureLight(pShaderTexLight, pWatchTower, pWatchTowerTex);
	GraphWatchTower1->SetMaterial(0.5f * Colors::White, 0.5f * Colors::White, Vect(.5f, .5f, .5f, 500));
	GraphWatchTower1->SetTexture(pWatchTowerTex);

	GraphGround1 = new GraphicObject_TextureLight(pShaderTexLight, pWatchGround, pWatchGroundTex);
	GraphGround1->SetMaterial(0.5f * Colors::White, 0.5f * Colors::White, Vect(.5f, .5f, .5f, 500));
	GraphGround1->SetTexture(pWatchGroundTex);

	GraphBoat = new GraphicObject_TextureLight(pShaderTexLight, pWoodBoat, pBoatTex);
	GraphBoat->SetMaterial(0.5f * Colors::White, 0.5f * Colors::White, Vect(.5f, .5f, .5f, 500));
	GraphBoat->SetTexture(pBoatTex);

	GraphBoat1 = new GraphicObject_TextureLight(pShaderTexLight, pWoodBoat, pBoatTex);
	GraphBoat1->SetMaterial(0.5f * Colors::White, 0.5f * Colors::White, Vect(.5f, .5f, .5f, 500));
	GraphBoat1->SetTexture(pBoatTex);

	GraphSpace = new GraphicObject_TextureLight(pShaderTexLight, pModel1, pFrigateTex);

	// Initialize the world matrix
	mWorld1 = Matrix(TRANS, 50, -6, 50) * Matrix(ROT_Y, 3.0f);
	mWorld2 = Matrix(TRANS, 50, 60, 50) * Matrix(ROT_Y, 3.0f);
	GraphObj1->SetWorld(mWorld1);

	mWorld1 = Matrix(TRANS, 50, -6, 45) * Matrix(ROT_Y, 3.0f);
	GraphObj2->SetWorld(mWorld1);

	mWorld1 = Matrix(TRANS, 50, -6, 55) * Matrix(ROT_Y, 3.0f);
	GraphObj3->SetWorld(mWorld1);

	mWorld1 = Matrix(TRANS, 55, -6, 55) * Matrix(ROT_Y, 3.0f);
	GraphObj4->SetWorld(mWorld1);

	mWorld1 = Matrix(TRANS, 60, -6, 55) * Matrix(ROT_Y, 3.0f);
	GraphObj5->SetWorld(mWorld1);

	mWorld1 = Matrix(TRANS, 65, -6, 55) * Matrix(ROT_Y, 3.0f);
	GraphObj6->SetWorld(mWorld1);

	mWorld1 = Matrix(TRANS, 65, -6, 50) * Matrix(ROT_Y, 3.0f);
	GraphObj7->SetWorld(mWorld1);

	mWorld1 = Matrix(TRANS, 65, -6, 45) * Matrix(ROT_Y, 3.0f);
	GraphObj8->SetWorld(mWorld1);

	Matrix mWorld3 = Matrix(TRANS, -20, -6.5, 22);
	GraphWatchTower->SetWorld(mWorld3);
	GraphGround->SetWorld(mWorld3);

	Matrix mWorld4 = Matrix(TRANS, -68, -6, -68);
	GraphWatchTower1->SetWorld(mWorld4);
	GraphGround1->SetWorld(mWorld4);

	GraphBoat->SetWorld(Matrix(TRANS, 2, -6.5, 2) * Matrix(ROT_Y, -1.0f));
	GraphBoat1->SetWorld(Matrix(TRANS, 25, -6.5, -25) * Matrix(ROT_Y, -1.5f));

	GraphSpace->SetWorld(mWorld2);
	//------------------------- Setting Point Lights -------------------------------------------
	pShaderTexLight->SetPointLightParameters(mWorld4.get(MatrixRowType::ROW_3) * Matrix(TRANS, 0, 5, 0), 5, .3 * Vect(1, 1, 1),
		.5 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), .2 * Vect(1, 1, 1));

	Vect temPos = mWorld1.get(MatrixRowType::ROW_3) * Matrix(TRANS, 0, 2, 0);
	pShaderTexLight->SetPointLightParameters1(temPos, 3, 0.5f * Vect(0, 1, 1),
		.5 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), .5 * Vect(1, 1, 1));
	
	pShaderTexLight->SetPointLightParameters2(mWorld3.get(MatrixRowType::ROW_3) * Matrix(TRANS, -1, 5, 1), 1, 0.1f * Vect(0, 1, 1),
		.5 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), .5 * Vect(1, 1, 1));

	pShaderTexLight->SetPointLightParameters3((Matrix(TRANS, 25, -5.0, -25) * Matrix(ROT_Y, -1.5f)).get(MatrixRowType::ROW_3), 2, 1.0f * Vect(0, 1, 1),
		.5 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), .5 * Vect(1, 1, 1));

	//------------------------- Setting Spot Lights ---------------------------------------------
	// WatchTower SpotLight
	temPos = mWorld3.get(MatrixRowType::ROW_3) * Matrix(TRANS, 0, 1, 0);
	pShaderTexLight->SetSpotLightParameters1(temPos, 40, .5 * Vect(1, 0, 0),
		-temPos.getNorm(), 50,
		1 * Colors::White, 3 * Vect(1, 1, 1), 1 * Vect(1, 1, 1, 150));

	temPos = mWorld4.get(MatrixRowType::ROW_3) * Matrix(TRANS, 0, 1, 0);
	pShaderTexLight->SetSpotLightParameters2(temPos, 40, .5 * Vect(1, 0, 0),
		-temPos.getNorm(), 50,
		1 * Colors::White, 3 * Vect(1, 1, 1), 1 * Vect(1, 1, 1, 150));

	// Initialize the projection matrix
	mCam.setPerspective( 3.14159/3, mClientWidth / (float)mClientHeight, 1.0f, 1000.0f);
	mCam.setOrientAndPosition(Vect(0, 1, 0), Vect(0, 0, 0), Vect(0, 3, -5));

	// Initialize gimmicky mouse control values
	mTheta = .5;
	mPhi = 3.1415f / 8;
	mRadius = 6;

	mTimer.Reset();
}

void DXApp::UpdateScene()
{
	mWorld2 *= Matrix(ROT_Y, -0.0002);
	pos = mWorld2.get(MatrixRowType::ROW_3);
	GraphSpace->SetWorld(mWorld2);

	float camSpeed = 0.004f;
	if (GetKeyState('W') & 0x08000)
	{
		mCam.TranslateFwdBack(camSpeed);
	}
	else if (GetKeyState('S') & 0x08000)
	{
		mCam.TranslateFwdBack(-camSpeed);
	}

	if (GetKeyState('A') & 0x08000)
	{
		mCam.TranslateLeftRight(-camSpeed);
	}
	else if (GetKeyState('D') & 0x08000)
	{
		mCam.TranslateLeftRight(camSpeed);
	}

	float rotSpeed = 0.0005f;
	if (GetKeyState(VK_LEFT) & 0x08000)
	{
		mCam.TurnLeftRight(rotSpeed);
	}
	else if (GetKeyState(VK_RIGHT) & 0x08000)
	{
		mCam.TurnLeftRight(-rotSpeed);
	}

	if (GetKeyState(VK_UP) & 0x08000)
	{
		mCam.TiltUpDown(rotSpeed);
	}
	else if (GetKeyState(VK_DOWN) & 0x08000)
	{
		mCam.TiltUpDown(-rotSpeed);
	}

	mCam.updateCamera();
}

void DXApp::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, VasA(BackgroundColor));
	md3dImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	// Shader Texture Light
	pShaderTexLight->SetSpotLightParameters(pos, 100, .5 * Vect(1, 1, 1),
		Vect(0, -1, 0), 200,
		1 * Colors::White, 1 * Vect(1, 1, 1), 1 * Vect(1, 1, 1, 150));

	pShaderTexLight->SetSpotLightParameters3(pos, 50, .5 * Vect(1, 0, 0),
		-pos.getNorm(), 200,
		.2 * Colors::White, .1 * Vect(1, 1, 1), 0.5 * Vect(1, 1, 1, 150));

	pShaderTexLight->SetToContext(md3dImmediateContext);
	pShaderTexLight->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());

	Vect eyepos;
	mCam.getPos(eyepos);
	pShaderTexLight->SendLightParameters(eyepos);
	//pShaderTex->SetToContext(md3dImmediateContext);
	//pShaderTex->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());

	//---------------- SkyBox ---------------------------------
	GraphObjSkyBox->Render();

	//================ Terrain ===================================
	GraphTerrain->Render();
	GraphWater->Render();
	GraphMountain->Render();

	// --- Render Object #1;
	GraphObj1->Render();
	GraphObj2->Render();
	GraphObj3->Render();
	GraphObj4->Render();
	GraphObj5->Render();
	GraphObj6->Render();
	GraphObj7->Render();
	GraphObj8->Render();
	GraphWatchTower->Render();
	GraphGround->Render();
	GraphWatchTower1->Render();
	GraphGround1->Render();
	GraphBoat->Render();
	GraphBoat1->Render();
	GraphSpace->Render();

	// --- Render Object #2
	pShaderColLight->SetSpotLightParameters(pos, 300, .5 * Vect(1, 0, 0),
		-pos, 50,
		.2 * Colors::Red, 3 * Vect(1, 1, 1), 1 * Vect(1, 1, 1, 150));
	pShaderColLight->SetToContext(md3dImmediateContext);
	pShaderColLight->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());

	pShaderColLight->SendLightParameters(eyepos);

	// Switches the display to show the now-finished back-buffer
	mSwapChain->Present(0, 0);
}


DXApp::DXApp(HWND hwnd)
{
	assert(hwnd);
	mhMainWnd = hwnd;

	BackgroundColor = Colors::MidnightBlue;

	md3dDevice = nullptr;
	md3dImmediateContext = nullptr;
	mSwapChain = nullptr;
	mRenderTargetView = nullptr;

	// Get window data through the window handle
	RECT rc;
	BOOL err = GetClientRect(mhMainWnd, &rc);  // Seriously MS: Redifining BOOL as int? Confusing much?
	assert(err);

	// get width/hight
	mClientWidth = rc.right - rc.left;
	mClientHeight = rc.bottom - rc.top;

	// Get window caption
	const int MAX_LABEL_LENGTH = 100; // probably overkill...
	WCHAR str[MAX_LABEL_LENGTH];
	GetWindowText(mhMainWnd, str, MAX_LABEL_LENGTH);
	mMainWndCaption = str;

	// Initialize DX11
	this->InitDirect3D();

	// Demo initialization
	this->InitDemo();
}

DXApp::~DXApp()
{
	delete pModel1;
	delete pModel2;
	delete pSkyBox;
	delete pTerrain;
	delete pWaterTerrain;
	delete pMountainTerrain;
	delete pWatchTower;
	delete pWatchGround;
	delete pWoodBoat;
	
	delete pShaderColLight;
	delete pShaderTexLight;

	delete GraphObjSkyBox;
	delete GraphTerrain;
	delete GraphObj1;
	delete GraphObj2;
	delete GraphObj3;
	delete GraphObj4;
	delete GraphObj5;
	delete GraphObj6;
	delete GraphObj7;
	delete GraphObj8;
	delete GraphWater;
	delete GraphMountain;
	delete GraphWatchTower;
	delete GraphGround;
	delete GraphWatchTower1;
	delete GraphGround1;
	delete GraphBoat;
	delete GraphBoat1;
	delete GraphSpace;

	delete pTex1;
	delete pTex2;
	delete pTexSkybox;
	delete pGrassTex;
	delete pWater;
	delete pMountain;
	delete pWatchTowerTex;
	delete pWatchGroundTex;
	delete pBoatTex;
	delete pFrigateTex;

	ReleaseAndDeleteCOMobject(mRenderTargetView);
	ReleaseAndDeleteCOMobject(mpDepthStencilView);
	ReleaseAndDeleteCOMobject(mSwapChain);
	ReleaseAndDeleteCOMobject(md3dImmediateContext);

	// Must be done BEFORE the device is released
	ReportLiveDXObjects();		// See http://masterkenth.com/directx-leak-debugging/

	ReleaseAndDeleteCOMobject(md3dDevice);
}

// See http://masterkenth.com/directx-leak-debugging/
void DXApp::ReportLiveDXObjects()
{
#ifdef _DEBUG
	HRESULT hr = S_OK;

	// Now we set up the Debug interface, to be queried on shutdown
	ID3D11Debug* debugDev;
	hr = md3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDev));

	debugDev->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	ReleaseAndDeleteCOMobject(debugDev);
#endif
}

void DXApp::InitDirect3D()
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// This is a *greatly* simplified process to create a DX device and context:
	// We force the use of DX11 feature level since that's what CDM labs are limited to.
	// For real-life applications would need to test what's the best feature level and act accordingly
	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, nullptr, 0, D3D11_SDK_VERSION, &md3dDevice, nullptr, &md3dImmediateContext);
	assert(SUCCEEDED(hr));

	// Now we obtain the associated DXGIfactory1 with our device 
	// Many steps...
	IDXGIDevice* dxgiDevice = nullptr;
	hr = md3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
	assert(SUCCEEDED(hr));

	IDXGIAdapter* adapter = nullptr;
	hr = dxgiDevice->GetAdapter(&adapter);
	assert(SUCCEEDED(hr));

	IDXGIFactory1* dxgiFactory1 = nullptr;
	hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory1));
	assert(SUCCEEDED(hr));
	// See also note on weird stuff with factories and swap chains (1s and 2s)
	// https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

	// We are done with these now...
	ReleaseAndDeleteCOMobject(adapter);
	ReleaseAndDeleteCOMobject(dxgiDevice);

	// Controls MSAA option:
	// - 4x count level garanteed for all DX11 
	// - MUST be the same for depth buffer!
	// - We _need_ to work with the depth buffer because reasons... (see below)
	DXGI_SAMPLE_DESC sampDesc;
	sampDesc.Count = 1;
	sampDesc.Quality = static_cast<UINT>(D3D11_CENTER_MULTISAMPLE_PATTERN);  // MS: what's with the type mismtach?

	DXGI_MODE_DESC buffdesc;				// https://msdn.microsoft.com/en-us/library/windows/desktop/bb173064(v=vs.85).aspx
	ZeroMemory(&buffdesc, sizeof(buffdesc));
	buffdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Next we create a swap chain. 
	// Useful thread: http://stackoverflow.com/questions/27270504/directx-creating-the-swapchain
	// Note that this is for a DirectX 11.0: in a real app, we should test the feature levels and act accordingly

	DXGI_SWAP_CHAIN_DESC sd;				// See MSDN: https://msdn.microsoft.com/en-us/library/windows/desktop/bb173075(v=vs.85).aspx
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;						// Much confusion about this number... see http://www.gamedev.net/topic/633807-swap-chain-buffer-count/
	sd.BufferDesc = buffdesc;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = mhMainWnd;
	sd.SampleDesc = sampDesc;
	sd.Windowed = TRUE;

	hr = dxgiFactory1->CreateSwapChain(md3dDevice, &sd, &mSwapChain);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(dxgiFactory1);

	// Create a render target view		https://msdn.microsoft.com/en-us/library/windows/desktop/ff476582(v=vs.85).aspx
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	assert(SUCCEEDED(hr));;

	hr = md3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mRenderTargetView);
	ReleaseAndDeleteCOMobject(pBackBuffer);
	assert(SUCCEEDED(hr));

	/**********************************************************/

	// First we fix what it means for triangles to be front facing.
	// Requires setting a whole new rasterizer state
	//*
	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_SOLID;  // Also: D3D11_FILL_WIREFRAME
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = true; // true for RH forward facing
	rd.DepthBias = 0;
	rd.SlopeScaledDepthBias = 0.0f;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.ScissorEnable = false;
	rd.MultisampleEnable = true;  // Does not in fact turn on/off multisample: https://msdn.microsoft.com/en-us/library/windows/desktop/ff476198(v=vs.85).aspx
	rd.AntialiasedLineEnable = true;

	ID3D11RasterizerState* rs;
	md3dDevice->CreateRasterizerState(&rd, &rs);

	md3dImmediateContext->RSSetState(rs);
	ReleaseAndDeleteCOMobject(rs); // we can release this resource since we won't be changing it any further
	//*/

	// We must turn on the abilty to process depth during rendering.
	// Done through depth stencils (see https://msdn.microsoft.com/en-us/library/windows/desktop/bb205074(v=vs.85).aspx)
	// Below is a simplified version
	//*
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = mClientWidth;
	descDepth.Height = mClientHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc = sampDesc;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	ID3D11Texture2D* pDepthStencil;
	hr = md3dDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	assert(SUCCEEDED(hr));

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0;;

	hr = md3dDevice->CreateDepthStencilView(pDepthStencil, &descDSV, &mpDepthStencilView);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(pDepthStencil);
	//*/

	/**********************************************************/

	//md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, nullptr);  // to use without depth stencil
	md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mpDepthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)mClientWidth;
	vp.Height = (FLOAT)mClientHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	md3dImmediateContext->RSSetViewports(1, &vp);
}

void DXApp::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::wostringstream outs;
		outs.precision(6);
		outs << mMainWndCaption << L"    "
			<< L"FPS: " << fps << L"    "
			<< L"Frame Time: " << mspf << L" (ms)";
		SetWindowText(mhMainWnd, outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

void DXApp::FrameTick()
{
	mTimer.Tick();
	CalculateFrameStats();

	this->UpdateScene();
	this->DrawScene();
}

void DXApp::OnMouseDown(WPARAM btnState, int xval, int yval)
{
	// Gimmicky mouse control
	if (btnState & MK_LBUTTON)
	{
		MousePos[x] = static_cast<float>(xval);
		MousePos[y] = static_cast<float>(yval);
	}
}

void DXApp::OnMouseUp(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseMove(WPARAM btnState, int xval, int yval)
{
	// Gimmicky mouse control
	if (btnState & MK_LBUTTON)
	{
		float dx = 0.01f*(MousePos[x] - xval);
		float dy = 0.01f*(MousePos[y] - yval);

		// Update angles based on input to orbit camera around box.
		mTheta += dx;
		mPhi -= dy;

		static float verticalMax = MATH_PI2 - 0.2f;

		if (mPhi > verticalMax)
			mPhi = verticalMax;
		else if (mPhi < -verticalMax)
			mPhi = -verticalMax;

		// Build the view matrix using gimmicky trick
		Vect target = Vect(0, 0, 0, 0);
		Vect up = Vect(0, 1, 0, 0);
		Vect pos = Vect(0, 0, -mRadius) * Matrix(ROT_Y, mTheta) * Matrix(ROT_X, mPhi);
		mCam.setOrientAndPosition(up, target, pos);
	}

	MousePos[x] = static_cast<float>(xval);
	MousePos[y] = static_cast<float>(yval);
}

void  DXApp::OnMouseWheel(short delta)
{
	if (delta > 0)
	{
		mRadius -= 1;
	}
	else
	{
		mRadius += 1;
	}
}


// Shader loading utility. Will be moved elsewhere later...
// Needs to be moved. Requires
HRESULT DXApp::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
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
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
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

	return S_OK;
}