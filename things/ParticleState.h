#include "Vector.h"
#include "Color.h"
#include <cstdlib>
#include <iostream>

using namespace std;
namespace pba{

class ParticleState
{
  public:
    ParticleState() :
     position(Vector(0,0,0)),
 velocity(Vector(0,0,0)),
 color(Color(1,1,1,1)),
 mass(1.0)
{};
   ~ParticleState(){};

   Vector position;
   Vector velocity;
   Color color;
   float mass;
   Vector currentForce;
   Vector lastPos;
	 bool pinned;
};

}
