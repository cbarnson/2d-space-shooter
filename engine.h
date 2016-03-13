/**
 * @file engine.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef ENGINE_H
#define ENGINE_H

#include "Simulator.h"
#include "Root.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <memory>

using std::shared_ptr;

class engine : public Simulator {
  private:
   shared_ptr<Root> root;
   ALLEGRO_FONT *menuFont;
   ALLEGRO_FONT *modeFont;
   ALLEGRO_BITMAP *space;
   int game_fps;
   int windowWidth;
   int windowHeight;
   //bool select_left;

  public:
  engine(const Display& d, int fps) : Simulator(d, fps), game_fps(fps)
   {
      windowWidth = d.getW();
      windowHeight = d.getH();
      menuFont = al_load_font("/usr/share/fonts/dejavu/DejaVuSerif.ttf", 48, 0);
      modeFont = al_load_font("/usr/share/fonts/culmus/DavidCLM-Bold.ttf", 32, 0);
      space = al_load_bitmap("/home/mohj2720/images/space.png");
   }

   ~engine() {
      al_destroy_font(menuFont);
      al_destroy_font(modeFont);
      al_destroy_bitmap(space);      
   }
   
   void menuMessage() {
      //al_clear_to_color(al_map_rgb(0,0,0));
      al_draw_bitmap(space, 0, 0, 0);
      al_draw_text(menuFont, al_map_rgb(0, 204, 204), 0.5 * windowWidth,
		   0.5 * windowHeight, ALLEGRO_ALIGN_CENTRE,
		   "ASSEROIDS");
      al_draw_text(modeFont, al_map_rgb(0, 204, 102), 0.5 * windowWidth,
		   0.7 * windowHeight, ALLEGRO_ALIGN_CENTRE,
		   "[ 1 ] SINGLE PLAYER   [ 2 ] MULTI PLAYER");
      al_flip_display();
   }

   // menuSelection was planned to be a selection box that would enclose the
   // text "single player" or "multi player" at the beginning of the game
   // you would be able to use the arrow keys to go back and forth between the two modes
   // then hit enter to start the game
/*
   void menuSelection(int code) {
      if (code == ALLEGRO_KEY_LEFT)
	 select_left = true;
      if (code == ALLEGRO_KEY_RIGHT)
	 select_left = false;
      if (code == ALLEGRO_KEY_ENTER) {
	 switch (select_left) {
	    case true:
	       single_player(); break;
	    case false:
	       multi_player(); break;
	 }
      }	 
   }
*/	
   void single_player() { root = make_shared<Root> (1, game_fps); }
   void multi_player() { root = make_shared<Root> (2, game_fps); }
   void setRoot(int code) { root->set(code); }
   void resetRoot(int code) { root->reset(code); }
   void collisionRoot() { root->collision(); root->clean(); }
   
   void controlRoot() { root->updatePlayer(); }
   void updateRoot(double dt) { root->update(dt); }

   void drawRoot() {
      al_clear_to_color(al_map_rgb(0,0,0));
      root->draw();
      al_flip_display();
   }


};

#endif
