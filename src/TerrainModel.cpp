#include "TerrainModel.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>


TerrainModel::TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width);

	side = hgtmap->height;	// the image should be square
	pixel_width = 4;			// 4 bytes RGBA per pixel
	//uint8_t h_val = hgtmap->pixels[ TexelIndex(3, 5) ]; // the 'R' byte of the pixel at (3,5)
	WorldMat = Matrix(TRANS, 0.0f, ytrans, 0.0f);

	// ** much work to add below **

	int nVerts = side * side;
	int nTris = (side - 1) * (side - 1) * 2;
	int vertInd = 0;
	int triInd = 0;
	float repU = (float)RepeatU / (side - 1);
	float repV = (float)RepeatV / (side - 1);

	float posX = len * 0.5f;
	float posZ = len * 0.5f;

	float incXZ = len / side;

	StandardVertex* pVerts = new StandardVertex[nVerts];
	TriangleByIndex* pTriList = new TriangleByIndex[nTris];

	for (int i = 0; i < (int)side; i++)
	{
		for (int j = 0; j < (int)side; j++)
		{
			float posY = hgtmap->pixels[TexelIndex(j, i)] * maxheight / 256;
			pVerts[vertInd].set(posX, posY, posZ, j * repU, i * repV);
			posX -= incXZ;
			vertInd++;
		}

		posZ -= incXZ;
		posX = len * 0.5f;
	}

	vertInd = 0;
	for (int i = 0; i < (int)side - 1; i++)
	{
		for (int j = 0; j < (int)side - 1; j++)
		{
			pTriList[triInd].set(vertInd, vertInd + side + 1, vertInd + 1);
			triInd++;
			pTriList[triInd].set(vertInd, vertInd + side, vertInd + side + 1);
			triInd++;

			vertInd++;
		}
		vertInd++;
	}

	Vect norm;
	// Left Top Corner
	norm = GetNormal(pVerts[0].Pos, pVerts[side + 1].Pos, pVerts[1].Pos) + GetNormal(pVerts[0].Pos, pVerts[side].Pos, pVerts[side + 1].Pos);
	pVerts[0].normal = norm * 0.5f;

	// Bottom Right Corner
	pVerts[side - 1].normal = GetNormal(pVerts[side - 2].Pos, pVerts[side - 2 + side + 1].Pos, pVerts[side - 1].Pos);

	// Bottom Left Corner
	pVerts[nVerts - side].normal = GetNormal(pVerts[nVerts - side].Pos, pVerts[nVerts - side + 1].Pos, pVerts[nVerts - side - side].Pos);

	// Bottom Right Corner
	norm = GetNormal(pVerts[nVerts - 1].Pos, pVerts[nVerts - 2].Pos, pVerts[nVerts - 2 - side].Pos) +
		GetNormal(pVerts[nVerts - 1].Pos, pVerts[nVerts - side - 2].Pos, pVerts[nVerts - 1 - side].Pos);
	pVerts[nVerts - 1].normal = norm * 0.5f;

	// Edges Top
	for (int i = 1; i < (int)side - 1; ++i)
	{
		norm = GetNormal(pVerts[i - 1].Pos, pVerts[i].Pos, pVerts[i + side].Pos) +
			GetNormal(pVerts[i].Pos, pVerts[i + side + 1].Pos, pVerts[i + side].Pos) +
			GetNormal(pVerts[i].Pos, pVerts[i + 1].Pos, pVerts[i + side + 1].Pos);
		pVerts[i].normal = norm * (1.0f / 3.0f);
	}

	// Edges Bottom
	for (int i = nVerts - (int)side + 1; i < nVerts - 1; i++)
	{
		norm = GetNormal(pVerts[i - 1].Pos, pVerts[i - side - 1].Pos, pVerts[i].Pos) +
			GetNormal(pVerts[i].Pos, pVerts[i - side - 1].Pos, pVerts[i - side].Pos) +
			GetNormal(pVerts[i].Pos, pVerts[i - side].Pos, pVerts[i + 1].Pos);
		pVerts[i].normal = norm * (1.0f / 3.0f);
	}

	// Left Edge
	for (int i = (int)side; i < nVerts - (int)side; i += (int)side)
	{
		norm = GetNormal(pVerts[i].Pos, pVerts[i - side].Pos, pVerts[i + 1].Pos) +
			GetNormal(pVerts[i].Pos, pVerts[i + 1].Pos, pVerts[i + 1 + side].Pos) +
			GetNormal(pVerts[i].Pos, pVerts[i + 1 + side].Pos, pVerts[i + 1].Pos);
		pVerts[i].normal = norm * (1.0f / 3.0f);
	}

	// Right Edge
	for (int i = (int)side * 2 - 1; i < nVerts - 1; i += side)
	{
		norm = GetNormal(pVerts[i].Pos, pVerts[i - side - 1].Pos, pVerts[i - side].Pos) +
			GetNormal(pVerts[i].Pos, pVerts[i - 1].Pos, pVerts[i - 1 - side].Pos) +
			GetNormal(pVerts[i - 1].Pos, pVerts[i].Pos, pVerts[i + side].Pos);
		pVerts[i].normal = norm * (1.0f / 3.0f);
	}

	// All the Middle Normal
	for (int i = 1; i < (int)side - 1; i++)
	{
		for (int j = 1; j < (int)side - 1; j++)
		{
			int ind = side * i + j;

			norm = GetNormal(pVerts[ind].Pos, pVerts[ind - 1].Pos, pVerts[ind + side].Pos) +
				GetNormal(pVerts[ind - 1].Pos, pVerts[ind].Pos, pVerts[ind - 1 - side].Pos) +
				GetNormal(pVerts[ind].Pos, pVerts[ind - 1 - side].Pos, pVerts[ind - side].Pos) +
				GetNormal(pVerts[ind].Pos, pVerts[ind - side].Pos, pVerts[ind + 1].Pos) +
				GetNormal(pVerts[ind].Pos, pVerts[ind + 1].Pos, pVerts[ind + 1 + side].Pos) +
				GetNormal(pVerts[ind].Pos, pVerts[ind + side - 1].Pos, pVerts[ind + side].Pos);

			pVerts[ind].normal = norm * (1.0f / 6.0f);
		}
	}


	pModTerrain = new Model(dev, pVerts, nVerts, pTriList, nTris);
}

TerrainModel::~TerrainModel()
{
	delete pModTerrain;
}

void TerrainModel::Render(ID3D11DeviceContext* context)
{
	pModTerrain->SetToContext(context);
	pModTerrain->Render(context);
}

Model * TerrainModel::GetModel()
{
	return this->pModTerrain;
}

int TerrainModel::TexelIndex(int i, int j) const
{
	return (int)pixel_width * (j * side + i);
}

Vect TerrainModel::GetNormal(Vect v0, Vect v1, Vect v2)
{
	Vect n = (v1 - v0).cross(v2 - v0);
	return n.getNorm();
}