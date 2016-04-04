#include <stdexcept>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "Engine.h"
#include "Input.h"
#include "State.h"
#include "Action.h"
using namespace act;


Engine::Engine(int w, int h, int fps) : displayWidth(w), displayHeight(h), framesPerSec(fps),
					timer(NULL), eventQueue(NULL), running(true),
					gameState(state::MENU)
{
      
}

Engine::~Engine() {
   // clean up some allegro objects
   if (timer != NULL) al_destroy_timer(timer);
   if (eventQueue != NULL) al_destroy_event_queue(eventQueue);
   al_destroy_display(display);
}

void Engine::run() {
   while (gameState == state::MENU) {
      if (!menuLoop())
	 break;
   }
   while (gameState == state::PLAY) {
      gameLoop();
   }
   
}

void Engine::gameLoop() {
   bool redraw = true;
   double crtTime, prevTime = 0;
   ALLEGRO_EVENT ev;
   al_wait_for_event(eventQueue, &ev);

   if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      switch (gameInput.handleKeyDown(ev)) {
	 default:
	    break;
      }
   }
   
   if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      gameState = state::EXIT;
      return;
   }
   
   if (ev.type == ALLEGRO_EVENT_TIMER) {
      crtTime = al_current_time();
      update(crtTime - prevTime);
      prevTime = crtTime;
      redraw = true;
   }

   if (redraw && al_is_event_queue_empty(eventQueue)) {
      draw();
      redraw = false;
   }
   
   
}

// returns false if menuLoop should terminate
bool Engine::menuLoop() {
   ALLEGRO_EVENT ev;
   al_wait_for_event(eventQueue, &ev);

   if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      switch (gameInput.handleKeyDown(ev)) {
	 case action::PLAY_SINGLE:
	    gameState = state::PLAY;
	    return false;
	 case action::QUIT_GAME:
	    gameState = state::EXIT;
	    return false;
	 case action::NO_ACTION:
	    break;
      }
   }      
   if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      gameState = state::EXIT;
      return false;
   }
   if (ev.type == ALLEGRO_EVENT_TIMER) {
      menuMessage();
   }
   
   return true;
}


void Engine::update(double dt) {
   
}

void Engine::draw() {

}


// initialize Allegro, the display window, the addons, the timers, and event sources
void Engine::init() {
   al_init();

   if ((display = al_create_display(width, height)) == NULL) {
      std::cerr << "Cannot initialize the display\n";
      exit(1); // non-zero argument means "trouble"
   }

   // initialize addons
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();

   // initialize our timers
   if ((timer = al_create_timer(1.0 / fps)) == NULL)
      throw std::runtime_error("Cannot create allegro timer");
   if ((eventQueue = al_create_event_queue()) == NULL)
      throw std::runtime_error("Cannot create event queue");

   // register our allegro eventQueue
   al_register_event_source(eventQueue,
			    al_get_display_event_source(d.getAllegroDisplay()));   
   al_register_event_source(eventQueue, al_get_timer_event_source(timer));
   al_start_timer(timer);  

   al_register_keyboard();
   al_register_event_source(eventQueue, al_get_keyboard_event_source());
}
   
