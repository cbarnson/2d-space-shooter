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
#include "Single.h"
#include "Versus.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <memory>
#include <list>

using std::shared_ptr;
using std::make_shared;
using std::list;

class engine : public Simulator {
  private:
   list< shared_ptr<Root> > root;
   //shared_ptr<Root> root;
   //bool game_over;
   int game_fps;
   int windowWidth;
   int windowHeight;
   
   ALLEGRO_FONT *menuFont;
   ALLEGRO_FONT *modeFont;
   ALLEGRO_BITMAP *space;
   
  public:
  engine(const Display& d, int fps) : Simulator(d, fps), game_fps(fps)
   {
      ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
      al_append_path_component(path, "resources");
      al_change_directory(al_path_cstr(path, '/'));
      
      space = al_load_bitmap("space.png");
      menuFont = al_load_font("DavidCLM-BoldItalic.ttf", 48, 0);
      modeFont = al_load_font("DavidCLM-Medium.ttf", 24, 0);
      
      al_destroy_path(path);
      
      windowWidth = d.getW();
      windowHeight = d.getH();
      //game_over = false;
   }

   ~engine() {
      al_destroy_font(menuFont);
      al_destroy_font(modeFont);
      al_destroy_bitmap(space);
   }

   void reset_game() {
      root.clear();
   }
   
   bool is_game_over() {
      for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	   ++it) 
	 return ((*it)->is_game_over()) ? true : false;
      return true;
	 /*
	 if ((*it)->is_game_over()) 
	    return true;	 
	 else
	 return false;*/
      
   }
   
   void menuMessage() {
      //al_clear_to_color(al_map_rgb(0,0,0));
      al_draw_bitmap(space, 0, 0, 0);
      //al_set_target_bitmap(space);
      al_draw_text(menuFont, al_map_rgb(0, 204, 204), 0.5 * windowWidth,
		   0.5 * windowHeight, ALLEGRO_ALIGN_CENTRE,
		   "ASSEROIDS");
      al_draw_text(modeFont, al_map_rgb(0, 204, 102), 0.5 * windowWidth,
		   0.7 * windowHeight, ALLEGRO_ALIGN_CENTRE,
		   "[ 1 ] SINGLE PLAYER   [ 2 ] MULTI PLAYER");
      al_flip_display();
   }
   

   void single_player() {
      root.push_back(make_shared<Single> (game_fps));
      for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	   ++it) {
	 (*it)->setup();
      }
      //root = make_shared<Single> (game_fps);
      //root->setup();
   }

   
   void multi_player() {
      root.push_back(make_shared<Versus> (game_fps));
      for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	   ++it) {
	 (*it)->setup();
      }
      //root = make_shared<Versus> (game_fps);
      //root->setup();
   }

   
   void setRoot(int code) {
      for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	   ++it) {
	 (*it)->set(code);
      }
      //root->set(code);
   }
   void resetRoot(int code) {
      for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	   ++it) {
	 (*it)->reset(code);
      }
      //root->reset(code);
   }
   void collisionRoot() {
      for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	   ++it) {
	 (*it)->collision();
	 (*it)->clean();
      }
      //root->collision();
      //root->clean();
   }   
   void controlRoot() {
      for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	   ++it) {
	 (*it)->updatePlayer();
      }
      //root->updatePlayer();
   }
   void updateRoot(double dt) {
      for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	   ++it) {
	 (*it)->update(dt);
      }
      //root->update(dt);
   }
   
   void drawRoot() {
      al_clear_to_color(al_map_rgb(0,0,0));
      for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	   ++it) {
	 (*it)->draw();
      }
      //root->draw();
      al_flip_display();
   }


};

#endif
