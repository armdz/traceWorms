//
//  Particle.hpp
//  LineasRepulsivas
//
//  Created by lolo on 2/13/17.
//
//

#ifndef Particle_hpp
#define Particle_hpp

#include "ofMain.h"

class Particle : public ofVec2f {
public:
  Particle();
  ~Particle();
  void  born(float _x,float _y);
  void  update();
  float random_direction;
  float direction_change_rule;  //  over random(0,100)
  float direction_mult;
  int   max_life;
  bool  alive;
  float life_norm;
private:
  float direction;
  float direction_dest;
  float easing;
  int   life;
  
};

#endif /* Particle_hpp */
