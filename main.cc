/**
 * @file main.cc
 * @brief
 * 
 * @author
 * @bug
 */
/*
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//using namespace allegro_font;

int main(void)
{
   int width = 640;
   int height = 480;
   
   bool done = false;
   int count = 0;

   int FPS = 60;
   
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   
   if(!al_init()) //initialize Allegro
      return -1;
   
   display = al_create_display(width, height); //create our display object
   
   if(!display)	//test display object
      return -1;
   
   al_init_font_addon();
   al_init_ttf_addon();
   
   ALLEGRO_FONT *font18 = al_load_font("arial.ttf", 18, 0);
   
   timer = al_create_timer(1.0 / FPS);
   event_queue = al_create_event_queue();
   
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   
   al_start_timer(timer);
   
   while(!done)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
      
      count++;
      
      al_draw_textf(font18, al_map_rgb(255, 255, 255), width / 2, height / 2, ALLEGRO_ALIGN_CENTRE,
		    "Frames: %i", count);
      
      al_flip_display();
      al_clear_to_color(al_map_rgb(0,0,0));
   }
   
   al_destroy_event_queue(event_queue);
   al_destroy_timer(timer);
   al_destroy_display(display);						//destroy our display object
   
   return 0;
}

*/





#include "Display.h"
#include "Simulator.h"
#include "gameSimulator.h"
#include "Hotkeys.h"
#include "Player.h"
#include "Point.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>
#include <list>
#include <string>
#include <iostream>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;
using std::vector;


int main() {   
   Display disp;   
   gameSimulator game(disp, 30); // 2nd param is fps 

   // hotkeys player 1
   vector<int> h1;
   h1.push_back(ALLEGRO_KEY_UP);
   h1.push_back(ALLEGRO_KEY_DOWN);
   h1.push_back(ALLEGRO_KEY_RIGHT);
   h1.push_back(ALLEGRO_KEY_LEFT);
   h1.push_back(ALLEGRO_KEY_PAD_0);
   
   // hotkeys player 2
   //vector<int> h2;
   //h2.push_back(ALLEGRO_KEY_W);
   //h2.push_back(ALLEGRO_KEY_S);
   //h2.push_back(ALLEGRO_KEY_D);
   //h2.push_back(ALLEGRO_KEY_A);
   //h2.push_back(ALLEGRO_KEY_SPACE);

   //shared_ptr<Player> player2 =
   //  make_shared<Player> (Point(400, 240), al_map_rgb(255,0,0), h2, true);
   //game.addPlayer(player2); game.addDrawable(player2); game.addUpdateable(player2);
   
   // sets up the player, provide parameters: start point on the display, and size of player
   shared_ptr<Player> player1 =
      make_shared<Player> (Point(200, 240), al_map_rgb(0,204,0), h1, true, 1);
   game.addPlayer(player1); game.addDrawable(player1); game.addUpdateable(player1);

   
   // start the game, close the display to end
   game.run();
   
   }

