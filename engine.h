/**
 * @file engine.h
 * @brief Declaration of Engine class
 *
 * @author
 * @bug
 */
#ifndef ENGINE_H
#define ENGINE_H
#include "Simulator.h"
#include "Root.h"
#include "Single.h"
//#include "Versus.h"
#include "Sprite.h"


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <memory>
#include <iostream>
#include <list>

using std::shared_ptr;
using std::make_shared;
using std::list;
using std::cout;

class engine : public Simulator {
  private:
   list< shared_ptr<Root> > root;
   shared_ptr<Sprite> menuPng;
   int game_fps;
   int windowWidth;
   int windowHeight;
   int mAnim;

   // ALLEGRO_FONT *menuFont;
   //ALLEGRO_FONT *modeFont;
   // ALLEGRO_FONT *subMenuFont;
   ALLEGRO_TIMER *menuTimer;
   
  public:
  engine(const Display& d, int fps) : Simulator(d, fps)
   {
      game_fps = fps;
      windowWidth = d.getW();
      windowHeight = d.getH();
      mAnim = 0;
      load_assets();
   }

   ~engine();
   void load_assets();
   void reset_game();
   bool is_game_over();
   void menuMessage();
   void single_player();
   void multi_player();
   void menuAnim();

   void getInput(const ALLEGRO_EVENT&);   
   void updateRoot(double dt);
   void drawRoot();
   bool gameReady();


};

#endif
