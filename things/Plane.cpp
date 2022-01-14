//-------------------------------------------------------
//
// Plane.cpp
//
//  Implimentation file for an infinite plane class.
//
//
//  Copyright (c) 2020 Reagan Burke
//
//
//--------------------------------------------------------
#include "Plane.h"

using namespace std;
using namespace pba;

// Draws a plane based on the array of "corner" vectors
void Plane::drawPlane(){
		glBegin(GL_POLYGON);
		glColor3f(color.X(), color.Y(), color.Z());
		for(int i = 0; i < 4; i++){
			glVertex3f(corners[i].X(), corners[i].Y(), corners[i].Z());
		}
		glEnd();
}

Vector Plane::getPoint(){
	return point;
}

Vector Plane::getNormal(){
	return normal;
}

// Default constructor. The corners are randomly selected and lie on the plane
// This does not mean that they are ordered correctly, or that they will draw
//correctly.
Plane::Plane(){
	point = Vector(0, 0, 0);
	normal = Vector(0, 1, 0);
	restitution = 1;
	stickiness = 1;

	corners[0] = Vector(-1, 0, -1);
	corners[1] = Vector(1, 0, -1);
	corners[2] = Vector(1, 0, 1);
	corners[3] = Vector(-1, 0, 1);

	color = Vector(drand48(), drand48(), drand48());
}

// This constructor randomly selects corner values. This does not mean
// that the corner points are ordered correctly or will draw correctly.
Plane::Plane(Vector p, Vector n){
	point = p;
	normal = n;
	restitution = 1;
	stickiness = 1;

	for(int i = 0; i < 4; i++){
		Vector random = Vector(2*drand48()-1, 2*drand48()-1, 2*drand48()-1);
		random -= normal * (normal * random);
		corners[i] = point + random;
	}

	color = Vector(drand48(), drand48(), drand48());
}

void Plane::setCorner(int index, Vector p){
		corners[index] = p;
}

// Determine the distace a point is from the nearest point on the plane
float Plane::distanceFromPlane(Vector& particlePos){
	return normal * (particlePos - point);
}

// Determine if a collision has occurred between the last frame and the current one
bool Plane::checkCollision(ParticleState& particle){
	float signCheck = distanceFromPlane(particle.lastPos) * distanceFromPlane(particle.position);
	if(signCheck < 0){
		return true;
	}
	else{
		return false;
	}
}

// Determine where on the plane a collision has occured.
Vector Plane::collisionLocation(ParticleState& particle, float total, float deltaTime){
	return particle.lastPos + total * (particle.position - particle.lastPos);
}

// Bounce the particle off of the plane
void Plane::handleInelasticCollision(ParticleState& particle, float drag, float& deltaTime){
	while(checkCollision(particle)){
		float total = findLocation(particle);

		Vector collision = collisionLocation(particle, total, deltaTime);

		particle.velocity = stickiness * particle.velocity - (stickiness + restitution) * normal * (normal * particle.velocity);
		particle.lastPos = collision + (normal * 0.00001);
		particle.position = collision + particle.velocity * deltaTime * (1 - total);
		deltaTime *= 1.0 - total;

	}
}

void Plane::setColor(Vector c){
	color = c;
}

// A debug function
void Plane::printCollision(int i){
	cout << "Collided with " << i << endl;
}

void Plane::setStickiness(float s){
	stickiness = s;
}

void Plane::setRestitution(float r){
	restitution = r;
}

float Plane::getStickiness(){
	return stickiness;
}

float Plane::getRestitution(){
	return restitution;
}

float Plane::findLocation(ParticleState& particle){
		float newDist = distanceFromPlane(particle.position);
		float oldDist = distanceFromPlane(particle.lastPos);
		float total = oldDist / (oldDist - newDist);
		return total;
}
