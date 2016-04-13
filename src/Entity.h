#ifndef ENTITY_H
#define ENTITY_H

#include <allegro5/allegro.h>

#include "Point.h"
#include "Vector.h"
#include "Type.h"

class Entity {

 public:
  Point _centre;
  ALLEGRO_COLOR _color;
  Vector _speed;
  id::type _entityID;

 Entity(Point centre, ALLEGRO_COLOR color, Vector speed, id::type entityID) :
  _centre(centre), _color(color), _speed(speed), _entityID(entityID) {}

  virtual ~Entity() {}


};


#endif
