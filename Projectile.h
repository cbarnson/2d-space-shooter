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
   void draw() {

   }

   void update(double dt) {

   }

};

#endif
