#include "GraphicObject_ColorLight.h"
#include "Model.h"
#include "ShaderColorLight.h"
#include <assert.h>

GraphicObject_ColorLight::GraphicObject_ColorLight(ShaderColorLight* shader,  Model* mod)
{
	SetModel(mod );
	pShader = shader;

	int n = mod->GetMeshCount();
	pMaterial = new Material[n];
	for (int i = 0; i < n; i++)
	{
		pMaterial[i].ambient = Vect(1, 1, 1);
		pMaterial[i].diffuse = Vect(1, 1, 1);
		pMaterial[i].specular = Vect(1, 1, 1);
	}
	
	pFogData.FogColor = Vect(1, 1, 1);
	pFogData.FogStart = 10000;
	pFogData.FogRange = 0;
	
	World = Matrix(IDENTITY);
}

GraphicObject_ColorLight::~GraphicObject_ColorLight()
{

}

void GraphicObject_ColorLight::SetMaterial(const Vect & amb, const Vect & diff, const Vect & spec)
{
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pMaterial[i].ambient = amb;
		pMaterial[i].diffuse = diff;
		pMaterial[i].specular = spec;
	}
}

void GraphicObject_ColorLight::SetMaterial(const Vect & amb, const Vect & diff, const Vect & spec, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));

	pMaterial[meshnum].ambient = amb;
	pMaterial[meshnum].diffuse = diff;
	pMaterial[meshnum].specular = spec;
}

void GraphicObject_ColorLight::SetFogData(const Vect & _fogColor, float _fogStart, float _fogRange)
{
	pFogData.FogColor = _fogColor;
	pFogData.FogStart = _fogStart;
	pFogData.FogRange = _fogRange;
}

void GraphicObject_ColorLight::SetWorld(const Matrix& m) 
{ 
	World = m;
}

void GraphicObject_ColorLight::Render()
{
	pModel->SetToContext(pShader->GetContext());

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendFogData(pFogData.FogColor, pFogData.FogStart, pFogData.FogRange);
		pShader->SendWorldAndMaterial(this->World, pMaterial[i].ambient, pMaterial[i].diffuse, pMaterial[i].specular);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}