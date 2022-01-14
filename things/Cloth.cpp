//-------------------------------------------------------
//
//  Cloth.cpp
//
//  Header file for the springy cloth mesh.
//
//  Copyright (c) 2020 Reagan Burke
//
//
//--------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include "Cloth.h"

using namespace std;
using namespace pba;

Cloth::Cloth(){

}

Cloth::Cloth(int size, float d, float sForce, float sFriction){
	// Delete all particles on screen and make a new vector of them
	size_t size2 = pow(size, 2);
	particles.clear();
	particles.resize(size2);
	for(size_t i = 0; i <= particles.size(); i++){
		particles[i].velocity = Vector(0, 0, 0);
		particles[i].color = Color(0, 0, 0, 1);
		particles[i].position = Vector(0, 0, 0);
		particles[i].pinned = false;
		particles[i].mass = 1;
	}

	int rows = size;
	int cols = size;
	distBetweenParticles = d;

	//Define corners
	corners[0] = &particles[0];
	corners[1] = &particles[size2 - 1];
	corners[2] = &particles[cols - 1];
	corners[3] = &particles[(cols - 1) * rows];

	corners[0]->position = Vector(1, 0, 0);
	corners[1]->position = Vector(-1, 0, 0);
	corners[2]->position = Vector(0, 1, 0);
	corners[3]->position = Vector(0, -1, 0);

	cornerPos = corners[0]->position;
	cornerAmp = 1;
	cornerSpeed = 1;
	cornerLoc = 0;

	cout << "Cloth made" << endl;
}


void Cloth::calculateForces(){
	for(int i = 0; i < (int)springs.size(); i++){
		springs[i].calculateSpringForces();
	}
}

void Cloth::drawCloth(){
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	for(int i = 0; i < (int)springs.size(); i++){
		glVertex3f(springs[i].getParticlePos(1).X(), springs[i].getParticlePos(1).Y(), springs[i].getParticlePos(1).Z());
		glVertex3f(springs[i].getParticlePos(2).X(), springs[i].getParticlePos(2).Y(), springs[i].getParticlePos(2).Z());
	}
	glEnd();
}

void Cloth::displacePoints(int num, float amp){
	for(int i=0; i < (int)springs.size(); i++){
		if((int)(drand48()*1000.0) % num == 2){
			float newX = springs[i].getParticlePos(1).X() + (amp * (1 - 2 * drand48()));
			float newY = springs[i].getParticlePos(1).Y() + (amp * (1 - 2 * drand48()));
			float newZ = springs[i].getParticlePos(1).Z() + (amp * (1 - 2 * drand48()));

			springs[i].setParticlePosition(1, Vector(newX, newY, newZ));
		}
	}
}

void Cloth::stapleCorners(){
	for(int i = 0; i < 4; i++){
		corners[i]->pinned = true;
	}
}

Spring Cloth::getSpring(int i){
	return springs[i];
}

int Cloth::getSpringSize(){
	return springSize;
}

void Cloth::updateCorner(float dt){
	float newX = cornerPos.X() + sin(cornerLoc * dt * cornerSpeed) * cornerAmp;
	float newY = cornerPos.Y() + sin(cornerLoc * dt * cornerSpeed) * cornerAmp;
	float newZ = cornerPos.Z() + cos(cornerLoc * dt * cornerSpeed) * cornerAmp;
	corners[0]->position = Vector(newX, newY, newZ);
	cornerLoc++;
}

ParticleState Cloth::getParticle(int i){
	return particles[i];
}
