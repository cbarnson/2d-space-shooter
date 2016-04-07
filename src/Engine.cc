#include <stdexcept>
#include <iostream>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "Engine.h"
#include "Menu.h"
#include "State.h"
#include "Action.h"
#include "Root.h"
#include "Single.h"
using namespace act;
using namespace gs;

Engine::Engine(int w, int h, int fps) : displayWidth(w), displayHeight(h), 
					framesPerSec(fps), _timer(NULL), 
					eventQueue(NULL), running(true),
					gameState(state::MENU)
{
   init();
   gameMenu = new Menu(framesPerSec);
}

Engine::~Engine() {
   delete gameMenu;
}
// initialize Allegro, the display window, the addons, the timers, and event 
// sources
void Engine::init() {
   al_init();

   if ((display = al_create_display(displayWidth, displayHeight)) == NULL) {
      std::cerr << "Cannot initialize the display\n";
      exit(1); // non-zero argument means "trouble"
   }

   // initialize addons
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();

   // initialize our timers
   if ((_timer = al_create_timer(1.0 / framesPerSec)) == NULL)
      throw std::runtime_error("Cannot create allegro timer");
   if ((eventQueue = al_create_event_queue()) == NULL)
      throw std::runtime_error("Cannot create event queue");

   // register our allegro eventQueue
   al_register_event_source(eventQueue, al_get_display_event_source(display)); 
   al_register_event_source(eventQueue, al_get_timer_event_source(_timer));
   al_start_timer(_timer);

   if (!al_install_keyboard()) {
      std::cerr << "Could not install keyboard\n";
   }
   al_register_event_source(eventQueue, al_get_keyboard_event_source());

}



// clean up some allegro resources
void Engine::shutdown() {
   // clean up some allegro objects
   if (_timer != NULL) al_destroy_timer(_timer);
   if (eventQueue != NULL) al_destroy_event_queue(eventQueue);
   if (display != NULL) al_destroy_display(display);  
}




// repeatedly call the state manager function until the gameState is EXIT
void Engine::run() {
   float prevTime = 0;

   while (gameState != state::EXIT) {
      processGameLogic(prevTime, gameState);
   }
}




void Engine::processGameLogic(float& prevTime, gs::state currentState) {
   switch (currentState) {
      case state::PLAY:
	 gameLoop(prevTime);
	 break;
      case state::MENU:
	 menuLoop();
	 break;
      case state::LOAD:
	 menuLoop();
	 break;
      case state::GAME_OVER:
	 return; // for now
      case state::EXIT:
	 return;
   }
}

// process a single frame for the menu
// returns false if menuLoop should terminate
void Engine::menuLoop() {
   ALLEGRO_EVENT event;
   ALLEGRO_KEYBOARD_STATE kb;
   al_wait_for_event(eventQueue, &event);

   if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      gameState = state::EXIT;
      shutdown();
      return;
   }

   if (event.type == ALLEGRO_EVENT_TIMER) {
      if (gameState == state::LOAD) { // triggers load animation
	 if (!gameMenu->animation()) { // load animation complete
	    gameState = state::PLAY; // move into PLAY state
	    return;
	 }
	 al_flip_display();
      }
      else {
	 gameMenu->draw(); // static menu image
	 al_flip_display();
      }
   }
    
   al_get_keyboard_state(&kb);
   if (al_key_down(&kb, ALLEGRO_KEY_1)) {
      gameState = state::LOAD;
      if (!root) {
	 root = std::make_shared<Single> (displayWidth, displayHeight, 
					  framesPerSec);    
      }
      return;
   }
   if (al_key_down(&kb, ALLEGRO_KEY_ESCAPE)) {
      gameState = state::EXIT;
      shutdown();
      return;
   }
}

void Engine::gameLoop(float& prevTime) {
   ALLEGRO_EVENT event;
   ALLEGRO_KEYBOARD_STATE kb;
   bool redraw = true;
   float crtTime;

   al_wait_for_event(eventQueue, &event);
  
   if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      gameState = state::EXIT;
      shutdown();
      return;
   }
   
   if (event.type == ALLEGRO_EVENT_TIMER) {
      crtTime = al_current_time();
      update(crtTime - prevTime);
      prevTime = crtTime;
      redraw = true;
   }

   
   al_get_keyboard_state(&kb);
   root->input(kb);  
  
   if (redraw && al_is_event_queue_empty(eventQueue)) {
      redraw = false;      
      draw(); // render our imagery
      al_flip_display();
   }   

   if (root->is_game_over()) {
      gameState = state::MENU;
      root.reset();
   }
  
}


void Engine::update(double dt) {
   if (root) {
      root->update(dt);
   }
}


void Engine::draw() {
   if (root) {
      root->draw();
      //al_flip_display();
   }
}



   
