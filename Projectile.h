#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Drawable.h"
#include "Updateable.h"
#include "Point.h"
#include "Vector.h"

class Projectile : public Drawable, public Updateable {
  private:
   Point start;
   Vector speed;   
   
   
  public:
  Projectile(Point p, Vector s) : start(p.x, p.y), speed(s.x, s.y) { }
   
   void draw() {

   }

   void update(double dt) {

   }

};

#endif
