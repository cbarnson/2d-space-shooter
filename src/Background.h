/**
 * @file Background.h
 * @brief Declaration of Background class
 *
 * @author
 * @bug
 */
#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "Drawable.h"
#include "Updateable.h"

#include <allegro5/allegro.h>
#include <memory>

struct Point;
struct Vector;
class Sprite;

class Background : public Drawable, public Updateable {
   // important members
   Point bgMid;
   Point fgMid;   
   Vector bgSpeed;
   Vector fgSpeed;
   std::shared_ptr<Sprite> bg;
   std::shared_ptr<Sprite> fg;
   
  public:
   Background(Vector bg_, Vector fg_);   
   void draw();
   void update(double dt);
   
  private:
   void load_assets();
   
};

#endif   
