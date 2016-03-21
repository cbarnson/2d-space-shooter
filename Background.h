/**
 * @file Background.h
 * @brief Declaration of Background class
 *
 * @author
 * @bug
 */
#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "Point.h"
#include "Vector.h"
#include "Drawable.h"
#include "Updateable.h"
#include "Sprite.h"

#include <allegro5/allegro.h>
#include <memory>

using std::shared_ptr;
using std::make_shared;

class Background : public Drawable, public Updateable {
  private:
   Point origin;   
   Point bgCentre;
   Point fgCentre;
   
   Vector bgSpeed;
   Vector fgSpeed;
   shared_ptr<Sprite> bg;
   shared_ptr<Sprite> fg;
   
  public:
  Background(Vector bgs, Vector fgs): bgSpeed(bgs), fgSpeed(fgs)
   {
      load_assets();
   }
   
   void load_assets();
   
   void draw();
   void update(double dt);
};

#endif   
