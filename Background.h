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
   Point centre;
   Vector speed;
   const char* filename;
   shared_ptr<Sprite> bg;
  public:
  Background(Vector s, const char* f): speed(s), filename(f)
   {
      origin.x=800;
      origin.y=300;
      centre=origin;
      load_assets();
   }
   void load_assets();
   void draw();
   void update(double dt);
};

#endif   
