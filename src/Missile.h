/**
 * @file Missile.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef MISSILE_H
#define MISSILE_H

#include "Projectile.h"
#include "Point.h"
#include "Vector.h"
#include "Drawable.h"
#include "Updateable.h"
#include "Sprite.h"

#include <allegro5/allegro.h>
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;
using std::vector;

class Missile : public Projectile {
  private:
   vector< shared_ptr<Sprite> > mvec;
   int mAnim;

  public:
   Missile (Point p, ALLEGRO_COLOR c, Vector s)
      : Projectile(p, c, s)
   {      
      load_assets();
      mAnim = 0;
   }

   void load_assets();
   void draw();
   void update(double dt);
   
   bool in_bound();



   

};


#endif
