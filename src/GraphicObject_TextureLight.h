
#ifndef _GraphicObject_TextureLight
#define _GraphicObject_TextureLight

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderTextureLight.h"

class GraphicObject_TextureLight : public GraphicObject_Base
{
friend class ShaderTextureLight;

public:
	GraphicObject_TextureLight(const GraphicObject_TextureLight&) = delete;				 // Copy constructor
	GraphicObject_TextureLight(GraphicObject_TextureLight&&) = default;                    // Move constructor
	GraphicObject_TextureLight& operator=(const GraphicObject_TextureLight&) & = default;  // Copy assignment operator
	GraphicObject_TextureLight& operator=(GraphicObject_TextureLight&&) & = default;       // Move assignment operator
	~GraphicObject_TextureLight();		  											 // Destructor

	GraphicObject_TextureLight() = delete;

	void SetMaterial(const Vect& amb, const Vect& diff, const Vect& spec);
	void SetMaterial(const Vect& amb, const Vect& diff, const Vect& spec, int meshnum);
	void SetTexture(Texture* inTex);
	void SetTexture(Texture* inTex, int meshnum);
	void SetWorld(const Matrix& m);
	void SetFogData(const Vect& _fogColor, float _fogStart, float _fogRange);
	virtual void Render() override;

	GraphicObject_TextureLight(ShaderTextureLight* shader, Model* mod, Texture* inTex);

private:

	struct Material : public Align16
	{
		Vect ambient;
		Vect diffuse;
		Vect specular;
	};

	struct FogData
	{
		Vect FogColor;
		float FogStart;
		float FogRange;
	};

	ShaderTextureLight*				pShader;
	Texture**						pTexture;
	Vect							Color;
	Matrix							World;
	Material*						pMaterial;
	FogData							pFogData;
	bool							pFogCheck;
};

#endif _GraphicObject_TextureLight
