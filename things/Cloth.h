//-------------------------------------------------------
//
//  Cloth.h
//
//  Header file for the springy cloth mesh.
//
//  Copyright (c) 2020 Reagan Burke
//
//
//--------------------------------------------------------

#include "Spring.h"

using namespace std;

namespace pba{

class Cloth{

	public:
		Cloth();
		Cloth(int size, float d, float sForce, float sFriction);
		void calculateForces();
		void drawCloth();
		void stapleCorners();
		void displacePoints(int num, float amp);
		Spring getSpring(int i);
		int getSpringSize();
		void updateCorner(float dt);
		ParticleState getParticle(int i);
		std::vector<ParticleState> particles;

	private:
		std::vector<Spring> springs;
		int rows;
		int cols;
		float cornerLoc;
		float cornerSpeed;
		float cornerAmp;
		Vector cornerPos;
		int springSize;
		float distBetweenParticles;
		float strutForce;
		float strutFriction;
		ParticleState *corners[4];

};

}
