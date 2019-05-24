#ifndef _SkyBox
#define _SkyBox

#include "Matrix.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;
//class Texture;

class SkyBox : public Align16
{
private:
	Model* pBox;
	
public:
	SkyBox(const SkyBox&) = delete;				// Copy constructor
	SkyBox(Model&&) = delete;						// Move constructor
	SkyBox& operator=(const SkyBox&) & = delete;  // Copy assignment operator
	SkyBox& operator=(SkyBox&&) & = delete;       // Move assignment operator
	~SkyBox();

	SkyBox(ID3D11Device* dev, float len);
	Model* GetModel();
	void Render(ID3D11DeviceContext* context);

};

#endif _SkyBox
