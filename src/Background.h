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
#include "Point.h"
#include "Vector.h"
#include <allegro5/allegro.h>
#include <memory>

class Sprite;

class Background : public Drawable, public Updateable {
   // important members
   Point bgMid;/**<point used by the background to draw from */
   Point fgMid;
   Point fg2Mid;
   Vector bgSpeed;/**<background movement speed */
   Vector fgSpeed;
   std::shared_ptr<Sprite> bg;/**<shared pointer to background animation */
    std::shared_ptr<Sprite> fg;
   
  public:
    /** @fn Constructor
	@ brief initializes the background movement
	@ param bg_ speed of the background as a vector
	@ param fg_ speed of the foreground as a vector
    */
 Background(Vector bg_, Vector fg_) : bgSpeed(bg_), fgSpeed(fg_) {
     load_assets();
   }  
   void draw();
   void update(double dt);
   
  private:
   void load_assets();
   
};

#endif   
