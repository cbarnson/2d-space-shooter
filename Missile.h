#ifndef MISSILE_H
#define MISSILE_H

#include "Projectile.h"
#include "Point.h"
#include "Vector.h"
#include "Drawable.h"
#include "Updateable.h"
#include "Sprite.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;
using std::vector;

class Missile : public Projectile {
  private:
   vector< shared_ptr<Sprite> > mvec;
   int mAnim;
   //bool mAnim_complete;

  public:
   Missile (Point p, ALLEGRO_COLOR c, Vector s)
      : Projectile(p, c, s)
   {      
      load_assets();
      mAnim = 0;
      //mAnim_complete = false;
   }

   void load_assets();
   void draw();
   //void draw_anim();
   void update(double dt);
   
   bool in_bound();



   

};


#endif
