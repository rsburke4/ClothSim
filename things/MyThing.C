//-------------------------------------------------------
//
//  MyThing.C
//
//  PbaThing for a collection of particles
//  each doing a random walk.
//
//  Copyright (c) 2017 Jerry Tessendorf
//
//
//--------------------------------------------------------

#include "MyThing.h"
#include <cstdlib>
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.
#include <iostream>



using namespace std;

using namespace pba;





MyThing::MyThing(const std::string nam) :
 PbaThingyDingy (nam),
 emit       (false)
{
    Reset();
    std::cout << name << " constructed\n";
}

MyThing::~MyThing(){}

void MyThing::Init( const std::vector<std::string>& args ) {
	gravity = -9.8;
	drag = 0.0;
}
    
void MyThing::Display() 
{
   glPointSize(5.0);
   glBegin(GL_POINTS);
   for( size_t i=0;i<particles.size();i++ )
   {
      const Vector& P = cloth.particles[i].position;
      const Color& ci = cloth.particles[i].color;
      glColor3f( ci.red(), ci.green(), ci.blue() );
      glVertex3f( P.X(), P.Y(), P.Z() );
   }
	
   glEnd();


}

void MyThing::Keyboard( unsigned char key, int x, int y )
{
       PbaThingyDingy::Keyboard(key,x,y);
       if( key == 'e' ){ emit = !emit; }
			 if( key == 'G' ){
					gravity -= 0.1;
					cout << "gravity " << gravity << endl;
				}
			 if( key == 'g' ){
					gravity += 0.1;
					cout << "gravity " << gravity << endl;
				}
}


void MyThing::solve()
{

	for(size_t i = 0; i < particles.size(); i++){
		if(!cloth.particles[i].pinned){
			Solver::positionSolveLF(cloth.particles[i], dt/2);
		}
	}

	for(size_t i = 0; i < particles.size(); i++){
		if(!cloth.particles[i].pinned){
			Solver::velocitySolveLF(cloth.particles[i], drag, dt);
		}
	}

	for(size_t i = 0; i < particles.size(); i++){
		if(!cloth.particles[i].pinned){
			Solver::positionSolveLF(cloth.particles[i], dt/2);
		}
	}


   if(emit)
   {
      size_t nbincrease = 10;
      particles.resize(particles.size()+nbincrease);
      Vector P, V;
      Color C;
      std::cout << "Total Points " << particles.size() << std::endl;
      for(size_t i=particles.size()-nbincrease;i<particles.size();i++)
      {
         double s = 2.0*drand48() - 1.0;
         double ss = std::sqrt( 1.0 - s*s );
         double theta = 2.0*3.14159265*drand48();
         pba::Vector P( ss*std::cos(theta), s, ss*std::sin(theta) );
         P *= std::pow( drand48(), 1.0/6.0 );
         cloth.particles[i].position = P;
         cloth.particles[i].color = pba::Color(drand48(),drand48(),drand48(),0);
         cloth.particles[i].velocity = pba::Vector(drand48()-0.5,drand48()-0.5,drand48()-0.5);
      }
   }
}



void MyThing::Reset()
{
   // Distribute particles with random positions
	cloth = Cloth(32, 2.0f, 300.0f, 100.0f);
}

void MyThing::Usage()
{
   PbaThingyDingy::Usage();
   cout << "=== " << name << " ===\n";
   cout << "e            toggle particle emission on/off\n";
	 cout << "g/G          decrease/increase the amount of gravity\n";
	 cout << "c/C          decrease/increase the coef of restitution\n";
}


pba::PbaThing pba::CreateMyThing(){ return PbaThing( new MyThing() ); }


