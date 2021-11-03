//-------------------------------------------------------
//
// Solver.cpp
//
//  Implimentation of the Solver Class
//
//
//  Copyright (c) 2020 Reagan Burke
//
//
//--------------------------------------------------------

#include "Solver.h"
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace pba;


//Solver for particles that utilizes pointers. DO NOT USE! DOES NOT ACCOUNT FOR COLLISIONS
void Solver::leapFrog(ParticleState& particle, float drag, float deltaTime){
	Vector oldVel = particle.velocity;
	particle.lastPos = particle.position;

	particle.position += (deltaTime/2) * particle.velocity;
	particle.velocity += particle.currentForce / particle.mass * deltaTime;
	particle.velocity -= (drag / particle.mass) * oldVel * deltaTime;
	particle.lastPos = particle.position;
	particle.position += (deltaTime/2) * particle.velocity;

	particle.currentForce *= 0;
}

//Velocity partical solver that resets the force acting on the particle
void Solver::velocitySolveLF(ParticleState& particle, float drag, float deltaTime){
	Vector oldVel = particle.velocity;
	particle.velocity += particle.currentForce / particle.mass * deltaTime;
	particle.velocity -= drag / particle.mass  * oldVel * deltaTime;
	particle.currentForce *= 0;
}

//Position particle solver
Vector Solver::positionSolveLF(ParticleState& particle, float deltaTime){
	particle.lastPos = particle.position;
	particle.position += (deltaTime) * particle.velocity;
	return particle.position;
}



void Solver::accelerate(ParticleState& particle, Vector acc){
    //Add acceleration value to the current force via F = MA
    particle.currentForce += acc * particle.mass;
}

void Solver::addForce(ParticleState& particle, Vector force){
    //Add the accelleration based on the equation F = MA to the particle
    particle.currentForce += force;
}
