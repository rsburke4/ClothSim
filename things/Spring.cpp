//-------------------------------------------------------
//
//  Spring.cpp
//
//  Implimentation file for the spring.
//	This can be used for larger systems.
//
//  Copyright (c) 2020 Reagan Burke
//
//
//--------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include "Spring.h"

using namespace std;
using namespace pba;

Spring::Spring(){
	particle1 = NULL;
	particle2 = NULL;

	strutFriction = 0;
	strutForce = 0;
	restPos = 0;
}

Spring::Spring(ParticleState* p1, ParticleState* p2, float sForce, float sFriction){
	particle1 = p1;
	particle2 = p2;
	strutForce = sForce;
	strutFriction = sFriction;

	restPos = (p2->position - p1->position).magnitude();

	criticalDampening = (particle1->mass + particle2->mass) * sqrt(strutForce);

	cout << "made spring: " << particle1->position.X() << " " << particle1->position.Y() << ", " << particle2->position.X() << " " << particle2->position.Y() << endl;
}

void Spring::calculateSpringForces(){
	Vector diff = particle2->position - particle1->position;
	float mag = diff.magnitude();


	Vector result =	strutForce * (mag - restPos) * (diff/mag);
	result += strutFriction * (diff/mag) * ((particle2->velocity - particle1->velocity) * (diff/mag));
	particle1->currentForce += result;
	particle2->currentForce += result * -1;

}

Vector Spring::getParticlePos(int particleNum){
	if(particleNum == 1){
		return particle1->position;
	}
	if(particleNum == 2){
		return particle2->position;
	}
	else{
		cout << "Warning, tried to fetch a bad particle index.";
		cout << "Returning Zero Vector" << endl;
		return Vector(0, 0, 0);
	}
}

void Spring::setParticlePosition(int i, Vector v){
	if(i == 1){
		particle1->position = v;
	}
	if(i == 2){
		particle2->position = v;
	}
}

float Spring::getStrutFriction(){
	return strutFriction;
}

void Spring::setStrutFriction(float sFriction){
	strutFriction = sFriction;
}

void Spring::setStrutForce(float sForce){
	strutForce = sForce;
}

float Spring::getStrutForce(){
	return strutForce;
}
