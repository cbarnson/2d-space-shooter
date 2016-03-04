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
   void draw() {

   }

   void update(double dt) {

   }

};


#endif
