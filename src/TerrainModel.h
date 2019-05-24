#ifndef _TerrainModel
#define _TerrainModel

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class TerrainModel : public Align16
{

private:
	Model* pModTerrain;
	Matrix WorldMat;
	size_t pixel_width;
	size_t side;

public:
	TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV);
	~TerrainModel();
	Matrix GetWorldMat() { return WorldMat; }
	int TexelIndex(int i, int j) const;
	void Render(ID3D11DeviceContext* context);
	Model* GetModel();

	static Vect GetNormal(Vect v0, Vect v1, Vect v2);
};



#endif _TerrainModel