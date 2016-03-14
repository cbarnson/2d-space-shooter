/**
 * @file main.cc
 * @brief
 * 
 * @author
 * @bug
 */

#include "Display.h"
#include "Simulator.h"
#include "engine.h"
#include "Hotkeys.h"
#include "Player.h"
#include "Root.h"
#include "Point.h"
#include "Vector.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <memory>
#include <list>


int main() {   
   Display disp;
/*
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));
   
   ALLEGRO_FONT *menuFont = al_load_font("ipag.ttf", 48, 0);
   ALLEGRO_FONT *modeFont = al_load_font("DavidCLM-Bold.ttf", 32, 0);
   
   //al_remove_path_component(path, -1); // maybe -2?
   //al_append_path_component(path, "resources/
   
   ALLEGRO_BITMAP *space = al_load_bitmap("space.png");   
   al_destroy_path(path);
*/ 
   int fps = 30;
   engine game(disp, fps); 

   // call either single_player() or multi_player() before run() to select mode
   // this sets the root to initialize the game with either 1 or 2 players
   
   //game.single_player();
   //game.multi_player();
      
   // start the game, close the display to end
   game.run();
   
}

