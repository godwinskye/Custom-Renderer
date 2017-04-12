#pragma once
#include "LineRender.h"
#include "../Matrix/Matrix.h"

namespace LineRenderer {
	void LiDDArender(Drawable *drawable, int x1, int y1, int x2, int y2, unsigned int color1, unsigned int color2);

	//Octant Renders with Linear Interpolation
	void LiRenderOctant1Or8(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2);
	void LiRenderOctant2Or3(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2);
	void LiRenderOctant4Or5(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2);
	void LiRenderOctant6Or7(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2);


	/***************************************************************************************************/
	/********************************Line Rendering with Z-Component************************************/
	/***************************************************************************************************/
	void LiDDArender3D(Drawable *drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix& zBuffer, unsigned int color1, unsigned int color2);
	//overloaded function
	void LiDDArender3D(Drawable *drawable, int x1, int y1, int z1, int x2, int y2, int z2, Matrix& zBuffer, unsigned int color1, unsigned int color2);
	void LiDDArender3D(Drawable *drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix& zBuffer, unsigned int color1, unsigned int color2, ViewFrustum view);

	//Octant Renders
	void RenderOctant3D1Or8(Drawable *drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix& zBuffer, double gradient, unsigned int color1, unsigned int color2);
	void RenderOctant3D2Or3(Drawable *drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix& zBuffer, double gradient, unsigned int color1, unsigned int color2);
	void RenderOctant3D4Or5(Drawable *drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix& zBuffer, double gradient, unsigned int color1, unsigned int color2);
	void RenderOctant3D6Or7(Drawable *drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix& zBuffer, double gradient, unsigned int color1, unsigned int color2);

	//overloaded octant renders
	void RenderOctant3D1Or8(Drawable *drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix& zBuffer, double gradient, unsigned int color1, unsigned int color2, ViewFrustum view);
	void RenderOctant3D2Or3(Drawable *drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix& zBuffer, double gradient, unsigned int color1, unsigned int color2, ViewFrustum view);
	void RenderOctant3D4Or5(Drawable *drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix& zBuffer, double gradient, unsigned int color1, unsigned int color2, ViewFrustum view);
	void RenderOctant3D6Or7(Drawable *drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix& zBuffer, double gradient, unsigned int color1, unsigned int color2, ViewFrustum view);
}