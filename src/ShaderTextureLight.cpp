#include "ShaderTextureLight.h"
#include "d3dUtil.h"
#include <d3d11.h>
#include <assert.h>
#include "Texture.h"

ShaderTextureLight::ShaderTextureLight(ID3D11Device* dev)
	: ShaderBase(dev, L"../Assets/Shaders/TextureLight.hlsl")
{
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
 		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);
	this->CreateInputLayout(layout, numElements);

	HRESULT hr = S_OK;

	// View Projection buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CamMatrices);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferCamMatrices);
	assert(SUCCEEDED(hr));

	// light param
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_LightParams);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferLightParams);
	assert(SUCCEEDED(hr));

	// Color buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_WorldAndMaterial);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffWordAndMaterial);
	assert(SUCCEEDED(hr));

	// Zeroing the light data
	ZeroMemory(&DirLightData, sizeof(DirLightData));
	ZeroMemory(&PointLightData, sizeof(PointLightData));
	ZeroMemory(&SpotLightData, sizeof(SpotLightData));
	ZeroMemory(&FogDt, sizeof(FogDt));
}

ShaderTextureLight::~ShaderTextureLight()
{
	ReleaseAndDeleteCOMobject(mpBuffWordAndMaterial);
	ReleaseAndDeleteCOMobject(mpBufferLightParams);
	ReleaseAndDeleteCOMobject(mpBufferCamMatrices);
}

void ShaderTextureLight::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	CamMatrices	mCamMatrices;
	mCamMatrices.View = view;
	mCamMatrices.Projection = proj;

	this->GetContext()->UpdateSubresource(mpBufferCamMatrices, 0, nullptr, &mCamMatrices, 0, 0);
}

void ShaderTextureLight::SetDirectionalLightParameters(const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp)
{
	DirLightData.Light.Ambient = amb;
	DirLightData.Light.Diffuse = dif;
	DirLightData.Light.Specular = sp;
	DirLightData.Direction = dir;
}

void ShaderTextureLight::SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	PointLightData[0].Light.Ambient = amb;
	PointLightData[0].Light.Diffuse = dif;
	PointLightData[0].Light.Specular = sp;
	PointLightData[0].Position = pos;
	PointLightData[0].Attenuation = att;
	PointLightData[0].Range = r;
}

void ShaderTextureLight::SetPointLightParameters1(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	PointLightData[1].Light.Ambient = amb;
	PointLightData[1].Light.Diffuse = dif;
	PointLightData[1].Light.Specular = sp;
	PointLightData[1].Position = pos;
	PointLightData[1].Attenuation = att;
	PointLightData[1].Range = r;
}

void ShaderTextureLight::SetPointLightParameters2(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	PointLightData[2].Light.Ambient = amb;
	PointLightData[2].Light.Diffuse = dif;
	PointLightData[2].Light.Specular = sp;
	PointLightData[2].Position = pos;
	PointLightData[2].Attenuation = att;
	PointLightData[2].Range = r;
}

void ShaderTextureLight::SetPointLightParameters3(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	PointLightData[3].Light.Ambient = amb;
	PointLightData[3].Light.Diffuse = dif;
	PointLightData[3].Light.Specular = sp;
	PointLightData[3].Position = pos;
	PointLightData[3].Attenuation = att;
	PointLightData[3].Range = r;
}

void ShaderTextureLight::SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	SpotLightData[0].Light.Ambient = amb;
	SpotLightData[0].Light.Diffuse = dif;
	SpotLightData[0].Light.Specular = sp;
	SpotLightData[0].Position = pos;
	SpotLightData[0].Direction = dir;
	SpotLightData[0].Attenuation = att;
	SpotLightData[0].Range = r;
	SpotLightData[0].SpotExp = spotExp;
}

void ShaderTextureLight::SetSpotLightParameters1(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	SpotLightData[1].Light.Ambient = amb;
	SpotLightData[1].Light.Diffuse = dif;
	SpotLightData[1].Light.Specular = sp;
	SpotLightData[1].Position = pos;
	SpotLightData[1].Direction = dir;
	SpotLightData[1].Attenuation = att;
	SpotLightData[1].Range = r;
	SpotLightData[1].SpotExp = spotExp;
}

void ShaderTextureLight::SetSpotLightParameters2(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	SpotLightData[2].Light.Ambient = amb;
	SpotLightData[2].Light.Diffuse = dif;
	SpotLightData[2].Light.Specular = sp;
	SpotLightData[2].Position = pos;
	SpotLightData[2].Direction = dir;
	SpotLightData[2].Attenuation = att;
	SpotLightData[2].Range = r;
	SpotLightData[2].SpotExp = spotExp;
}

void ShaderTextureLight::SetSpotLightParameters3(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	SpotLightData[3].Light.Ambient = amb;
	SpotLightData[3].Light.Diffuse = dif;
	SpotLightData[3].Light.Specular = sp;
	SpotLightData[3].Position = pos;
	SpotLightData[3].Direction = dir;
	SpotLightData[3].Attenuation = att;
	SpotLightData[3].Range = r;
	SpotLightData[3].SpotExp = spotExp;
}
void ShaderTextureLight::SendLightParameters( const Vect& eyepos)
{
	Data_LightParams dl;
	dl.DirLight = DirLightData;
	dl.PntLight = PointLightData[0];
	dl.PntLight1 = PointLightData[1];
	dl.PntLight2 = PointLightData[2];
	dl.PntLight3 = PointLightData[3];
	dl.SptLight = SpotLightData[0];
	dl.SptLight1 = SpotLightData[1];
	dl.SptLight2 = SpotLightData[2];
	dl.SptLight3 = SpotLightData[3];
	dl.EyePosWorld = eyepos;

	this->GetContext()->UpdateSubresource(mpBufferLightParams, 0, nullptr, &dl, 0, 0);
}

void ShaderTextureLight::SendFogData(const Vect & fogColor, float fogStart, float fogRange)
{
	FogDt.FogColor = fogColor;
	FogDt.FogStart = fogStart;
	FogDt.FogRange = fogRange;
}

void ShaderTextureLight::SendWorldAndMaterial(const Matrix& world, const Vect& amb, const Vect& dif, const Vect& sp)
{
	Data_WorldAndMaterial wm;
	wm.World = world;
	wm.WorlInv = world.getInv();
	wm.Mat.Ambient = amb;
	wm.Mat.Diffuse = dif;
	wm.Mat.Specular = sp;
	wm.FgData = FogDt;
	this->GetContext()->UpdateSubresource(mpBuffWordAndMaterial, 0, nullptr, &wm, 0, 0);
}

void ShaderTextureLight::SetToContext(ID3D11DeviceContext* devcon)
{
	ShaderBase::SetContext(devcon);
	ShaderBase::SetToContext_VS_PS_InputLayout();

	devcon->VSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->VSSetConstantBuffers(1, 1, &mpBufferLightParams);
	devcon->VSSetConstantBuffers(2, 1, &mpBuffWordAndMaterial);

	devcon->PSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->PSSetConstantBuffers(1, 1, &mpBufferLightParams);
	devcon->PSSetConstantBuffers(2, 1, &mpBuffWordAndMaterial);
}

void ShaderTextureLight::SetTextureResourceAndSampler(Texture *inTex)
{
	inTex->SetToContext(this->GetContext());
}