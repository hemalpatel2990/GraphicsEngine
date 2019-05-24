#include "GraphicObject_TextureLight.h"
#include "Model.h"
#include "ShaderTextureLight.h"
#include "Texture.h"
#include <assert.h>

GraphicObject_TextureLight::GraphicObject_TextureLight(ShaderTextureLight* shader,  Model* mod, Texture* inTex)
{
	SetModel(mod );
	pShader = shader;

	int n = mod->GetMeshCount();
	pMaterial = new Material[n];
	pTexture = new Texture*[n];
	for (int i = 0; i < n; i++)
	{
		pTexture[i] = inTex;
		pMaterial[i].ambient = Vect(1, 1, 1);
		pMaterial[i].diffuse = Vect(1, 1, 1);
		pMaterial[i].specular = Vect(1, 1, 1);
	}
	
	pFogData.FogColor = Vect(1, 1, 1);
	pFogData.FogStart = 10000;
	pFogData.FogRange = 0;
	pFogCheck = false;
	Color = Vect(1, 1, 1);
	World = Matrix(IDENTITY);
}

GraphicObject_TextureLight::~GraphicObject_TextureLight()
{

}

void GraphicObject_TextureLight::SetMaterial(const Vect & amb, const Vect & diff, const Vect & spec)
{
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pMaterial[i].ambient = amb;
		pMaterial[i].diffuse = diff;
		pMaterial[i].specular = spec;
	}
}

void GraphicObject_TextureLight::SetMaterial(const Vect & amb, const Vect & diff, const Vect & spec, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	pMaterial[meshnum].ambient = amb;
	pMaterial[meshnum].diffuse = diff;
	pMaterial[meshnum].specular = spec;
}

void GraphicObject_TextureLight::SetTexture(Texture * inTex)
{
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pTexture[i] = inTex;
	}
}

void GraphicObject_TextureLight::SetTexture(Texture * inTex, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	pTexture[meshnum] = inTex;
}

void GraphicObject_TextureLight::SetWorld(const Matrix& m) 
{ 
	World = m;
}

void GraphicObject_TextureLight::SetFogData(const Vect & _fogColor, float _fogStart, float _fogRange)
{
	pFogData.FogColor = _fogColor;
	pFogData.FogStart = _fogStart;
	pFogData.FogRange = _fogRange;
}

void GraphicObject_TextureLight::Render()
{
	pModel->SetToContext(pShader->GetContext());

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SetTextureResourceAndSampler(pTexture[i]);
		pShader->SendFogData(pFogData.FogColor, pFogData.FogStart, pFogData.FogRange);
		pShader->SendWorldAndMaterial(this->World, pMaterial[i].ambient, pMaterial[i].diffuse, pMaterial[i].specular);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}