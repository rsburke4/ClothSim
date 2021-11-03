//-------------------------------------------------------
//
// Solver.h
//
//  Header file for a solver class.
//
//
//  Copyright (c) 2020 Reagan Burke
//
//
//--------------------------------------------------------

#include "ParticleState.h"
#include <cstdlib>
#include <iostream>

using namespace std;
namespace pba{

class MyThing;

class Solver{
    public:
        static void addForce(ParticleState& particle, Vector force);
        static void accelerate(ParticleState& particle, Vector acc);
				static void leapFrog(ParticleState& particle, float drag, float deltaTime);
				static void velocitySolveLF(ParticleState& particle, float drag, float deltaTime);
				static Vector positionSolveLF(ParticleState& particle, float deltaTime);

};


}
