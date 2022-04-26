#include "model3d.h"
#include <list>

using namespace std;

Model3D& Model3D::Home(float floorWidth, float floorDepth, float wallHeight, float peakRelativeHeight)
{

	
}

Model3D& Model3D::Table(float footerHeight, float feetSize, float feetMargin, float surfaceWidth, float surfaceDepth, float surfaceHeigth)
{
	
	
	auto points = new list<Vetor3D>();
	
	
	addBox(*points, Vetor3D(feetMargin, 0.f, feetMargin), Vetor3D(feetMargin, footerHeight, feetMargin));

	
}

void addBox( list<Vetor3D>& pointList, Vetor3D min, Vetor3D max) {
	pointList.push_back(Vetor3D(
		min.x,
		min.y,
		min.z));
	pointList.push_back(Vetor3D(
		min.x + max.x,
		min.y,
		min.z
	));
	pointList.push_back(Vetor3D(
		min.x + max.x,
		min.y,
		min.z + max.z
	));
	pointList.push_back(Vetor3D(
		min.x,
		min.y,
		min.z + max.z
	));

}

Model3D::Model3D(bool randomColors) : Object()
{

}

Model3D::~Model3D() {

}