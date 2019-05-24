
#ifndef _GraphicObject_ColorLight
#define _GraphicObject_ColorLight

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColorLight.h"

class GraphicObject_ColorLight : public GraphicObject_Base
{
friend class ShaderColorLight;

public:
	GraphicObject_ColorLight(const GraphicObject_ColorLight&) = delete;				 // Copy constructor
	GraphicObject_ColorLight(GraphicObject_ColorLight&&) = default;                    // Move constructor
	GraphicObject_ColorLight& operator=(const GraphicObject_ColorLight&) & = default;  // Copy assignment operator
	GraphicObject_ColorLight& operator=(GraphicObject_ColorLight&&) & = default;       // Move assignment operator
	~GraphicObject_ColorLight();		  											 // Destructor

	GraphicObject_ColorLight() = delete;

	void SetMaterial(const Vect& amb, const Vect& diff, const Vect& spec);
	void SetMaterial(const Vect& amb, const Vect& diff, const Vect& spec, int meshnum);
	void SetWorld(const Matrix& m);
	void SetFogData(const Vect& _fogColor, float _fogStart, float _fogRange);
	virtual void Render() override;

	GraphicObject_ColorLight(ShaderColorLight* shader, Model* mod);

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

	ShaderColorLight*				pShader;
	Matrix							World;
	Material*						pMaterial;
	FogData							pFogData;
};

#endif _GraphicObject_ColorLight
