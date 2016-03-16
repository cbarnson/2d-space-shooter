#ifndef SPRITE_H
#define SPRITE_H

#include "Point.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
//#include <string>
//using std::string;

class Sprite {
  private:
   ALLEGRO_BITMAP* image;
   int width;
   int height;
   
  public:

   // x and y are the origin points of the bitmap
   // filename is where the image is located, must have set path
  Sprite(const char* filename) {
      image = al_load_bitmap(filename);
      width = al_get_bitmap_width(image);
      height = al_get_bitmap_height(image);
   }

   ~Sprite() {
      al_destroy_bitmap(image);
   }

   void drawToOrigin() {
      al_draw_bitmap(image, 0, 0, 0);
   }

   //void convert() {
   // al_convert_mask_to_alpha(image, al_get_pixel(image, 0, 0));
   //}
   
   // draw image centred at parameter position
   // flags can be
   // ALLEGRO_FLIP_HORIZONTAL
   // ALLEGRO_FLIP_VERTICAL
   void draw(Point p, int f) {
      al_draw_bitmap(image, p.x - width/2, p.y - height/2, f);
   }

   void draw_region(int r, int c, Point destination, int f) {
      al_draw_bitmap_region(image,
			    c * 47.0, r * 40.0,
			    47.0, 40.0,
			    destination.x - 47.0 / 2,
			    destination.y - 40.0 / 2, f);
   }

   
};

#endif