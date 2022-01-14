//-------------------------------------------------------
//
// Box.cpp
//
//  Implimentation file for a box class.
//
//
//  Copyright (c) 2020 Reagan Burke
//
//
//--------------------------------------------------------

#include "Box.h"
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace pba;

Box::Box(){
	lowerLeft = Vector(3, -3, -3);
	upperRight = Vector(-3, 3, 3);

	planes[0] = Plane(lowerLeft, Vector(0, 1, 0));
	planes[1] = Plane(lowerLeft, Vector(-1, 0, 0));
	planes[2] = Plane(upperRight, Vector(0, -1, 0));
	planes[3] = Plane(upperRight, Vector(1, 0, 0));
	planes[4] = Plane(upperRight, Vector(0, 0, -1));
	planes[5] = Plane(lowerLeft, Vector(0, 0, 1));

	sortPlaneCorners();
}

Box::Box(Vector llc, Vector urc){
	lowerLeft = llc;
	upperRight = urc;

	planes[0] = Plane(lowerLeft, Vector(0, 1, 0));
	planes[1] = Plane(lowerLeft, Vector(-1, 0, 0));
	planes[2] = Plane(upperRight, Vector(0, -1, 0));
	planes[3] = Plane(upperRight, Vector(1, 0, 0));
	planes[4] = Plane(upperRight, Vector(0, 0, -1));
	planes[5] = Plane(lowerLeft, Vector(0, 0, 1));

	sortPlaneCorners();
}

// This function reassigns the corners in each of the planes
// comprising the box based on the normals of the planes.
// Since this is an axis aligned bounding box, the normals
// of the walls of the box should not change.
void Box::sortPlaneCorners(){
	for(int i = 0; i < 6; i++){
		if(planes[i].getNormal() == Vector(0, -1, 0)){
				planes[i].setCorner(0, upperRight);
				planes[i].setCorner(1, Vector(lowerLeft.X(), upperRight.Y(), upperRight.Z()));
				planes[i].setCorner(2, Vector(lowerLeft.X(), upperRight.Y(), lowerLeft.Z()));
				planes[i].setCorner(3, Vector(upperRight.X(), upperRight.Y(), lowerLeft.Z()));
		}

		if(planes[i].getNormal() == Vector(1, 0, 0)){
				planes[i].setCorner(0, upperRight);
				planes[i].setCorner(1, Vector(upperRight.X(), upperRight.Y(), lowerLeft.Z()));
				planes[i].setCorner(2, Vector(upperRight.X(), lowerLeft.Y(), lowerLeft.Z()));
				planes[i].setCorner(3, Vector(upperRight.X(), lowerLeft.Y(), upperRight.Z()));
		}

		if(planes[i].getNormal() == Vector(0, 0, -1)){
				planes[i].setCorner(0, upperRight);
				planes[i].setCorner(1, Vector(lowerLeft.X(), upperRight.Y(), upperRight.Z()));
				planes[i].setCorner(2, Vector(lowerLeft.X(), lowerLeft.Y(), upperRight.Z()));
				planes[i].setCorner(3, Vector(upperRight.X(), lowerLeft.Y(), upperRight.Z()));
		}

		if(planes[i].getNormal() == Vector(0, 1, 0)){
				planes[i].setCorner(0, lowerLeft);
				planes[i].setCorner(1, Vector(upperRight.X(), lowerLeft.Y(), lowerLeft.Z()));
				planes[i].setCorner(2, Vector(upperRight.X(), lowerLeft.Y(), upperRight.Z()));
				planes[i].setCorner(3, Vector(lowerLeft.X(), lowerLeft.Y(), upperRight.Z()));
		}

		if(planes[i].getNormal() == Vector(-1, 0, 0)){
				planes[i].setCorner(0, lowerLeft);
				planes[i].setCorner(1, Vector(lowerLeft.X(), lowerLeft.Y(), upperRight.Z()));
				planes[i].setCorner(2, Vector(lowerLeft.X(), upperRight.Y(), upperRight.Z()));
				planes[i].setCorner(3, Vector(lowerLeft.X(), upperRight.Y(), lowerLeft.Z()));
		}

		if(planes[i].getNormal() == Vector(0, 0, 1)){
				planes[i].setCorner(0, lowerLeft);
				planes[i].setCorner(1, Vector(lowerLeft.X(), upperRight.Y(), lowerLeft.Z()));
				planes[i].setCorner(2, Vector(upperRight.X(), upperRight.Y(), lowerLeft.Z()));
				planes[i].setCorner(3, Vector(upperRight.X(), lowerLeft.Y(), lowerLeft.Z()));

		}
	}

}

void Box::drawBox(){
	for(int i = 0; i < 5; i++){
		planes[i].drawPlane();
	}
}

int Box::checkCollision(ParticleState& particle){
	std::vector<int> index;
	//Determine if there are any collisions
	for(int i = 0; i < 6; i++){
		if(planes[i].checkCollision(particle)){
			index.push_back(i);
		}
	}
	//If not, return
	if(index.size() == 0){
		return -1;
	}
	//If there is one collision, return the wall index
	else if(index.size() == 1){
		return index[0];
	}
	//If there is more than one collision return the wall index closest to the particle
	else if(index.size() > 1){
		int smallestIndex = index[0];
		float smallestDistance = planes[index[0]].findLocation(particle);
		for(unsigned int i = 0; i < index.size(); i++){
			float total = planes[index[i]].findLocation(particle);
			if(total < smallestDistance){
				smallestIndex = index[i];
				smallestDistance = total;
			}
		}
		return smallestIndex;
	}
	return -1;
}

//Handle the inelastic collision by calling the appropriate plane handling function
void Box::handleInelasticCollision(ParticleState& particle, float drag, float deltaTime){
		int closestCollision = checkCollision(particle);
		float dt = deltaTime;
		while(closestCollision != -1){
			planes[closestCollision].handleInelasticCollision(particle, drag, dt);
			closestCollision = checkCollision(particle);
		}
}

Vector Box::getLowerLeft(){
	return lowerLeft;
}

Vector Box::getUpperRight(){
	return upperRight;
}

Plane Box::getPlane(int i){
	return planes[i];
}

void Box::setRestitution(float r){
	for(int i = 0; i < 6; i++){
		planes[i].setRestitution(r);
	}
}

float Box::getRestitution(){
	float avg = 0;
	for(int i = 0; i < 6; i++){
		avg += planes[i].getRestitution();
	}
	avg /= 6;
	return avg;
}
