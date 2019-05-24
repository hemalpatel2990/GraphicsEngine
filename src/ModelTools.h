// ModelTools
// Support tools to compute bounding volumes on models

#ifndef _ModelTools
#define _ModelTools

#include "Vect.h"

struct StandardVertex;
struct TriangleByIndex;

class ModelTools
{

public:
	static void CreateUnitBox(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri);
	static void CreateUnitBoxRepTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri);

	static void CreateUnitPyramid(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri);
	static void CreateUnitSphere(int vslice, int hslice, StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri);
	static void CreateUnitPyramidRep(StandardVertex *& pVerts, int & nverts, TriangleByIndex *& pTriList, int & ntri);

	static Vect GetNormal(Vect v0, Vect v1, Vect v2);
};



#endif _ModelTools