#include "ModelTools.h"
//#include "Enum.h"
//#include <math.h>
#include "Matrix.h"
#include <assert.h>
#include "Model.h"
#include "d3dUtil.h"


/// Creates the unit box centered at the origin
void ModelTools::CreateUnitBox(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 8;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(-0.5f, -0.5f, -0.5f, Colors::Black);
	pVerts[1].set(-0.5f, +0.5f, -0.5f, Colors::Lime);
	pVerts[2].set(+0.5f, +0.5f, -0.5f, Colors::Yellow);
	pVerts[3].set(+0.5f, -0.5f, -0.5f, Colors::Red );
	pVerts[4].set(-0.5f, -0.5f, +0.5f, Colors::Blue);
	pVerts[5].set(-0.5f, +0.5f, +0.5f, Colors::Cyan);
	pVerts[6].set(+0.5f, +0.5f, +0.5f, Colors::White);
	pVerts[7].set(+0.5f, -0.5f, +0.5f, Colors::Magenta);

	// back face
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	// front face
	pTriList[2].set(4, 6, 5);
	pTriList[3].set(4, 7, 6);

	// left face
	pTriList[4].set(4, 5, 1);
	pTriList[5].set(4, 1, 0);

	// right face
	pTriList[6].set(3, 2, 6);
	pTriList[7].set(3, 6, 7);

	// top face
	pTriList[8].set(1, 5, 6);
	pTriList[9].set(1, 6, 2);

	// bottom face
	pTriList[10].set(4, 0, 3);
	pTriList[11].set(4, 3, 7);
}

void ModelTools::CreateUnitBoxRepTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 1 );
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 1, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0, 0, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0, 1, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 1, 0, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 1, 1, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0, 1, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 1, 1, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitPyramid(StandardVertex *& pVerts, int & nverts, TriangleByIndex *& pTriList, int & ntri)
{
	nverts = 5;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(0.0f, +0.5f, 0.0f, Colors::Black);
	pVerts[1].set(+0.5f, 0.0f, 0.0f, Colors::Lime);
	pVerts[2].set(0.0f, 0.0f, -0.5f, Colors::Yellow);
	pVerts[3].set(-0.5f, 0.0f, 0.0f, Colors::Red);
	pVerts[4].set(0.0f, 0.0f, +0.5f, Colors::Blue);

	// top faces
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);
	pTriList[2].set(0, 3, 4);
	pTriList[3].set(0, 4, 1);

	// base
	pTriList[4].set(4, 2, 1);
	pTriList[5].set(4, 3, 2);
}



void ModelTools::CreateUnitSphere(int vslice, int hslice, StandardVertex *& pVerts, int & nverts, TriangleByIndex *& pTriList, int & ntri)
{
	nverts = vslice * (hslice - 1) + 2;
	pVerts = new StandardVertex[nverts];
	ntri = (2 * hslice - 2) * vslice;
	pTriList = new TriangleByIndex[ntri];

	float radius = 1.0f;

	pVerts[0].set(Vect(0, radius, 0), Colors::Red);
	pVerts[0].normal.set(pVerts[0].Pos.getNorm());
	pVerts[nverts - 1].set(Vect(0, -radius, 0), Colors::Red);
	pVerts[nverts - 1].normal.set(pVerts[nverts - 1].Pos.getNorm());

	float angle = (MATH_PI) / hslice;
	angle = ((MATH_PI) / 2) - angle;

	int count = 0;
	for (int i = 1; i < nverts - 1; i++)
	{
		Vect temp = Vect(1.0f, 0.0f, 0.0f);
		temp = temp * Matrix(RotType::ROT_Z, angle) * Matrix(RotType::ROT_Y, count * (2 * MATH_PI / vslice));
		pVerts[i].set(temp, Colors::Red);
		pVerts[i].normal.set(temp.getNorm());

		count++;
		if (count >= vslice)
		{
			count = 0;
			angle = angle - (MATH_PI / hslice);
		}
	}

	for (int i = 0; i < hslice - 1; i++)
	{
		for (int j = 0; j < vslice; j++)
		{
			int vert_number = i * vslice + j;
			if (i == 0)
			{
				if (j == vslice - 1)
				{
					pTriList[vert_number].set(vert_number + 1, 1, 0);
				}
				else
				{
					pTriList[vert_number].set(vert_number + 1, vert_number + 2, 0);
				}
			}
			else
			{
				if (j == vslice - 1)
				{
					pTriList[vert_number].set(vert_number + 1, i * vslice + 1, vert_number + 1 - vslice);
				}
				else
				{
					pTriList[vert_number].set(vert_number + 1, vert_number + 2, vert_number + 1 - vslice);
				}
			}

			if (i == hslice - 2)
			{
				if (j == vslice - 1)
				{
					pTriList[vert_number + ntri / 2].set(vert_number + 1, nverts - 1, i * vslice + 1);
				}
				else
				{
					pTriList[vert_number + ntri / 2].set(vert_number + 1, nverts - 1, vert_number + 2);
				}
			}
			else
			{
				if (j == vslice - 1)
				{
					pTriList[vert_number + ntri / 2].set(vert_number + 1, i * vslice + 1 + vslice, i * vslice + 1);
				}
				else
				{
					pTriList[vert_number + ntri / 2].set(vert_number + 1, vert_number + 2 + vslice, vert_number + 2);
				}
			}
		}
	}
}

void ModelTools::CreateUnitPyramidRep(StandardVertex *& pVerts, int & nverts, TriangleByIndex *& pTriList, int & ntri)
{
	nverts = 16;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];
	Vect norm(0.0f, 0.0f, 0.0f, 0.0f);

	Vect v0(0.0f, +0.5f, 0.0f);
	Vect v1(-0.5f, -0.5f, +0.5f);
	Vect v2(+0.5f, -0.5f, +0.5f);
	Vect v3(-0.5f, -0.5f, -0.5f);
	Vect v4(+0.5f, -0.5f, -0.5f);

	// Forward
	norm = GetNormal(v0, v1, v2);
	norm.W() = 0.0f;
	pVerts[0].set(0.0f, +0.5f, 0.0f, 0.5f, 0, norm, Colors::Red);
	pVerts[1].set(-0.5f, -0.5f, +0.5f, 0, 1, norm, Colors::Red);
	pVerts[2].set(+0.5f, -0.5f, +0.5f, 1, 1, norm, Colors::Red);
	pTriList[0].set(0, 1, 2);

	// Right
	norm.set(GetNormal(v0, v2, v4));
	norm.W() = 0.0f;
	pVerts[3].set(0.0f, +0.5f, 0.0f, 0.5f, 0, norm, Colors::Red);
	pVerts[4].set(+0.5f, -0.5f, +0.5f, 0, 1, norm, Colors::Red);
	pVerts[5].set(+0.5f, -0.5f, -0.5f, 1, 1, norm, Colors::Red);
	pTriList[1].set(3, 4, 5);

	// Left
	norm.set(GetNormal(v0, v3, v1));
	norm.W() = 0.0f;
	pVerts[6].set(0.0f, +0.5f, 0.0f, 0.5f, 0, norm, Colors::Red);
	pVerts[7].set(-0.5f, -0.5f, -0.5f, 0, 1, norm, Colors::Red);
	pVerts[8].set(-0.5f, -0.5f, +0.5f, 1, 1, norm, Colors::Red);
	pTriList[2].set(6, 7, 8);

	// Back
	norm.set(GetNormal(v0, v4, v3));
	norm.W() = 0.0f;
	pVerts[9].set(0.0f, +0.5f, 0.0f, 0.5f, 0, norm, Colors::Red);
	pVerts[10].set(-0.5f, -0.5f, -0.5f, 0, 1, norm, Colors::Red);
	pVerts[11].set(+0.5f, -0.5f, -0.5f, 1, 1, norm, Colors::Red);
	pTriList[3].set(11, 10, 9);

	// Base Square
	pVerts[12].set(+0.5f, -0.5f, +0.5f, 0, 0, -1, 0);
	pVerts[13].set(-0.5f, -0.5f, +0.5f, 0, 0, -1, 0);
	pVerts[14].set(-0.5f, -0.5f, -0.5f, 0, 0, -1, 0);
	pVerts[15].set(+0.5f, -0.5f, -0.5f, 0, 0, -1, 0);

	pTriList[4].set(12, 13, 14);
	pTriList[5].set(12, 14, 15);
}

Vect ModelTools::GetNormal(Vect v0, Vect v1, Vect v2)
{
	Vect n = (v1 - v0).cross(v2 - v0);
	return n.getNorm();
}