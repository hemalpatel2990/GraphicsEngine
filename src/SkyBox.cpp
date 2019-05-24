#include "SkyBox.h"
#include "Model.h"
#include "d3dUtil.h"

SkyBox::SkyBox(ID3D11Device* dev, float len)
{
	int nverts = 24;
	StandardVertex* pVerts = new StandardVertex[nverts];

	int ntri = 12;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	float vthird = 0.333f;
	float vtwoThird = 0.667f;
	float uquarter = 0.25f;
	float uhalf = 0.50f;
	float uthreeQuarter = 0.75f;
	float vfull = 1.0f;
	float ufull = 1.0f;
	float vCorrection = 0.0020f;

	int vind = 0;
	int tind = 0;

	// Forward
	pVerts[vind].set    ( 0.5f * len,  0.5f * len, 0.5f * len, uquarter, vthird);
	pVerts[vind + 1].set(-0.5f * len,  0.5f * len, 0.5f * len, uhalf, vthird);
	pVerts[vind + 2].set(-0.5f * len, -0.5f * len, 0.5f * len, uhalf, vtwoThird);
	pVerts[vind + 3].set( 0.5f * len, -0.5f * len, 0.5f * len, uquarter, vtwoThird);
	pTriList[tind].set(vind + 2, vind + 1, vind    );
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set    ( 0.5f * len,  0.5f * len, -0.5f * len, ufull - vCorrection, vthird + vCorrection);
	pVerts[vind + 1].set(-0.5f * len,  0.5f * len, -0.5f * len, uthreeQuarter, vthird + vCorrection);
	pVerts[vind + 2].set(-0.5f * len, -0.5f * len, -0.5f * len, uthreeQuarter, vtwoThird - vCorrection);
	pVerts[vind + 3].set( 0.5f * len, -0.5f * len, -0.5f * len, ufull - vCorrection, vtwoThird - vCorrection);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set    (0.5f * len,  0.5f * len, -0.5f * len, 0.0f, vthird + vCorrection);
	pVerts[vind + 1].set(0.5f * len,  0.5f * len,  0.5f * len, uquarter, vthird + vCorrection);
	pVerts[vind + 2].set(0.5f * len, -0.5f * len,  0.5f * len, uquarter, vtwoThird - vCorrection);
	pVerts[vind + 3].set(0.5f * len, -0.5f * len, -0.5f * len, 0.0f, vtwoThird - vCorrection);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set    (-0.5f * len,  0.5f * len,  0.5f * len, uhalf, vthird + vCorrection);
	pVerts[vind + 1].set(-0.5f * len,  0.5f * len, -0.5f * len, uthreeQuarter, vthird + vCorrection);
	pVerts[vind + 2].set(-0.5f * len, -0.5f * len, -0.5f * len, uthreeQuarter, vtwoThird - vCorrection);
	pVerts[vind + 3].set(-0.5f * len, -0.5f * len,  0.5f * len, uhalf, vtwoThird - vCorrection);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set    ( 0.5f * len, 0.5f * len, -0.5f * len, uquarter + vCorrection, vCorrection);
	pVerts[vind + 1].set(-0.5f * len, 0.5f * len, -0.5f * len, uhalf - vCorrection, vCorrection);
	pVerts[vind + 2].set(-0.5f * len, 0.5f * len,  0.5f * len, uhalf - vCorrection, vthird);
	pVerts[vind + 3].set( 0.5f * len, 0.5f * len,  0.5f * len, uquarter + vCorrection, vthird);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set    ( 0.5f * len, -0.5f * len,  0.5f * len, uquarter + vCorrection, vtwoThird);
	pVerts[vind + 1].set(-0.5f * len, -0.5f * len,  0.5f * len, uhalf - vCorrection, vtwoThird);
	pVerts[vind + 2].set(-0.5f * len, -0.5f * len, -0.5f * len, uhalf - vCorrection, vfull - vCorrection);
	pVerts[vind + 3].set( 0.5f * len, -0.5f * len, -0.5f * len, uquarter + vCorrection, vfull - vCorrection);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	pBox = new Model(dev, pVerts, nverts, pTriList, ntri);
}

Model* SkyBox::GetModel()
{
	return pBox;
}

SkyBox::~SkyBox()
{
	delete pBox;
}

void SkyBox::Render(ID3D11DeviceContext* context)
{
	pBox->SetToContext(context);
	pBox->Render(context);
}