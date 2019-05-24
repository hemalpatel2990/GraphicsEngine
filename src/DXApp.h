
// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "ShaderColor.h"
#include "ShaderColorLight.h"
#include "ShaderTexture.h"

class Model;
class Texture;
class FlatPlane;
class SkyBox;
class TerrainModel;
class GraphicObject_ColorLight;
class ShaderTextureLight;
class GraphicObject_TextureLight;
class GraphicObject_Texture;

class DXApp : public Align16
{
private:	
	// Main window handle
	HWND      mhMainWnd;

	Vect BackgroundColor;

	// DX application elements
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					// image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations

	GameTimer mTimer;
	std::wstring mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

	void InitDirect3D();
	void InitDemo();
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	// Shader loading utility. SHould be moved elsewhere later...
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// Debug utility
	void ReportLiveDXObjects();

	// Demo specific additions
	Camera mCam;

	Model*			pModel1;
	Model*			pModel2;
	Model*			pWatchTower;
	Model*			pWatchGround;
	Model*			pWoodBoat;
	SkyBox*			pSkyBox;
	TerrainModel*	pTerrain;
	TerrainModel*	pWaterTerrain;
	TerrainModel*	pMountainTerrain;

	Matrix mWorld1;
	Matrix mWorld2;
	Vect	   pos;

	ShaderColorLight*		pShaderColLight;
	ShaderTextureLight*		pShaderTexLight;
	
	GraphicObject_TextureLight*	GraphObj2;
	GraphicObject_TextureLight*	GraphObj1;
	GraphicObject_TextureLight* GraphObj3;
	GraphicObject_TextureLight* GraphObj4;
	GraphicObject_TextureLight* GraphObj5;
	GraphicObject_TextureLight* GraphObj6;
	GraphicObject_TextureLight* GraphObj7;
	GraphicObject_TextureLight* GraphObj8;

	GraphicObject_TextureLight* GraphTerrain;
	GraphicObject_TextureLight*	GraphObjSkyBox;
	GraphicObject_TextureLight* GraphWater;
	GraphicObject_TextureLight* GraphMountain;

	GraphicObject_TextureLight* GraphWatchTower;
	GraphicObject_TextureLight* GraphWatchTower1;
	GraphicObject_TextureLight* GraphGround;
	GraphicObject_TextureLight* GraphGround1;

	GraphicObject_TextureLight* GraphBoat;
	GraphicObject_TextureLight* GraphBoat1;
	GraphicObject_TextureLight* GraphSpace;

	Texture*				pTex1;
	Texture*				pTex2;
	Texture*				pTexSkybox;
	Texture*				pGrassTex;
	Texture*				pWater;
	Texture*				pMountain;
	Texture*				pWatchTowerTex;
	Texture*				pWatchGroundTex;
	Texture*				pBoatTex;
	Texture*				pFrigateTex;

	// gimmicky mouse control
	Vect MousePos;		
	float mTheta;
	float mPhi;
	float mRadius;
	
public:
	DXApp(HWND hwnd);
	virtual ~DXApp();
	
	void FrameTick();

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);
	void OnMouseWheel(short delta);


};

#endif _DXApp