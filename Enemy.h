#ifndef ENEMY_H
#define ENEMY_H

#include "Drawable.h"
#include "Updateable.h"
#include "Point.h"
#include "Vector.h"

class Enemy : public Drawable, public Updateable {
  private:
   Point start, current, end;
   Vector speed;
   
  public:
  Enemy(Point s, Point c, Point e, Vector spd) : start(s.x, s.y), current(c.x, c.y),
      end(e.x, e.y), speed(spd.x, spd.y) { }

   // draw image to display of enemy ship
   void draw() {

   }

   // update position of enemy ships
   void update(double dt) {

   }

};


#endif
