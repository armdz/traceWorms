//
//  Particle.cpp
//  LineasRepulsivas
//
//  Created by lolo on 2/13/17.
//
//

#include "Particle.hpp"

Particle::Particle()
{
  
}

Particle::~Particle()
{
  
}

void  Particle::born(float _x,float _y)
{
  alive = true;
  set(_x,_y);
  direction = direction_dest = ofRandom(360.0f);
  life = 0;
  easing = .2f;
}

void  Particle::update()
{
  if(alive){
    if(ofRandom(100) > direction_change_rule)
    {
      direction_dest+=ofRandom(-random_direction,random_direction);
    }
    direction+=(direction_dest-direction)*easing;
    float angle_rad = ofDegToRad(direction);
    x+=cos(angle_rad)*direction_mult;
    y+=sin(angle_rad)*direction_mult;
    life++;
    life_norm = ofClamp(1.0f-(float)life/(float)max_life,0.0f,1.0f);
    if(life > max_life)
    {
      alive = false;
    }
  }
  
}
