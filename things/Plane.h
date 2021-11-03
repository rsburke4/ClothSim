//-------------------------------------------------------
//
// Plane.h
//
//  Header file for an infinite plane class.
//
//
//  Copyright (c) 2020 Reagan Burke
//
//
//--------------------------------------------------------
#include "Solver.h"
#include <cstdlib>
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.
#include <iostream>

using namespace std;
namespace pba{

class Plane{
	public:
		Plane();
		Plane(Vector p, Vector n);
		Vector getPoint();
		Vector getNormal();
		void setCorner(int index, Vector p);
		void setColor(Vector c);
		bool checkCollision(ParticleState& particle);
		Vector collisionLocation(ParticleState& particle, float total, float deltaTime);
		float distanceFromPlane(Vector& particlePos);
		void handleInelasticCollision(ParticleState& particle, float drag, float& deltaTime);
		void drawPlane();
		void printCollision(int i);
		void setStickiness(float s);
		void setRestitution(float r);
		float getStickiness();
		float getRestitution();
		float findLocation(ParticleState& particle);

	private:
		Vector normal;
		Vector point;
		Vector corners[4];
		Vector color;
		float restitution;
		float stickiness;

};
}
