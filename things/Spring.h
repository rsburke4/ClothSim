//-------------------------------------------------------
//
//  Spring.h
//
//  Header file for the spring object.
//
//  Copyright (c) 2020 Reagan Burke
//
//
//--------------------------------------------------------
#include "Box.h"


using namespace std;

namespace pba{

class Spring{

	public:
		Spring();
		Spring(ParticleState* p1, ParticleState* p2, float sForce, float sFriction);
		//~Spring();
		void calculateSpringForces();
		Vector getParticlePos(int particleNum);
		void setParticlePosition(int i, Vector v);
		void setStrutForce(float sForce);
		void setStrutFriction(float sFriction);
		float getStrutForce();
		float getStrutFriction();

	private:
		ParticleState* particle1;
		ParticleState* particle2;
		float strutForce;
		float strutFriction;
		float restPos;
		float criticalDampening;

};

}
