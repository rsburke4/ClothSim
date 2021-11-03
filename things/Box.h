//-------------------------------------------------------
//
// Box.h
//
//  Header file for a box class.
//
//
//  Copyright (c) 2020 Reagan Burke
//
//
//--------------------------------------------------------

#include "Plane.h"
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;
namespace pba{

class Box{
	public:
		Box();
		Box(Vector llc, Vector urc);
		int checkCollision(ParticleState& particle);
		void drawBox();
		void handleInelasticCollision(ParticleState& particle, float drag, float deltaTime);
		void sortPlaneCorners();
		void setRestitution(float r);
		float getRestitution();
		Vector getLowerLeft();
		Vector getUpperRight();
		Plane getPlane(int i);


	private:
		Vector lowerLeft;
		Vector upperRight;
		Plane planes[6];
};

}
