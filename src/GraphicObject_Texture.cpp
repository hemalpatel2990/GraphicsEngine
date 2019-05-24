#include "GraphicObject_Texture.h"
#include "Model.h"
#include "ShaderTexture.h"
#include <assert.h>

GraphicObject_Texture::GraphicObject_Texture(ShaderTexture* shader,  Model* mod, Texture* inTex)
{
	SetModel(mod );
	pShader = shader;

	this->SetTexture(inTex);
	World = Matrix(IDENTITY);
}

GraphicObject_Texture::~GraphicObject_Texture()
{

}

void GraphicObject_Texture::SetTexture(Texture* inTex) 
{
	pTexture = inTex;
}

void GraphicObject_Texture::SetWorld(const Matrix& m) 
{ 
	World = m;
}

void GraphicObject_Texture::Render()
{
	pShader->SetTextureResourceAndSampler(pTexture);
	pShader->SendWorld(World);
	pModel->SetToContext(pShader->GetContext());
	pModel->Render(pShader->GetContext());
}