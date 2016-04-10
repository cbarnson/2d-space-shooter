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
#include "HighScore.h"
using namespace act;
using namespace gs;

Engine::Engine(int w, int h, int fps) : _displayWidth(w), _displayHeight(h), 
					_fps(fps), _gameScore(-1),
					_timer(NULL), eventQueue(NULL), running(true),
					_state(state::MENU)
{ }

Engine::~Engine() {
   if (_timer != NULL) al_destroy_timer(_timer);
   if (eventQueue != NULL) al_destroy_event_queue(eventQueue);
   if (display != NULL) al_destroy_display(display);  
}


// initialize Allegro, the display window, the addons, the timers, and event 
// sources
void Engine::init() {
   al_init();
   if ((display = al_create_display(_displayWidth, _displayHeight)) == NULL) {
      std::cerr << "Cannot initialize the display\n";
      exit(1); // non-zero argument means "trouble"
   }
   // initialize addons
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();
   // initialize our timers
   if ((_timer = al_create_timer(1.0 / _fps)) == NULL)
      throw std::runtime_error("Cannot create allegro timer");
   if ((eventQueue = al_create_event_queue()) == NULL)
      throw std::runtime_error("Cannot create event queue");
   // register our allegro eventQueue
   al_register_event_source(eventQueue, al_get_display_event_source(display)); 
   al_register_event_source(eventQueue, al_get_timer_event_source(_timer));
   al_start_timer(_timer);
   // install keyboard
   if (!al_install_keyboard()) {
      std::cerr << "Could not install keyboard\n";
   }
   // register keyboard
   al_register_event_source(eventQueue, al_get_keyboard_event_source());
   
   _menu = std::make_shared<Menu> (_fps);
   //scores = std::make_shared<HighScore> ("Highscore.txt");
}




// repeatedly call the state manager function until the _state is EXIT
void Engine::run() {
   float prevTime = 0;
   // main engine loop
   while (_state != state::EXIT) {
      processGameLogic(prevTime, _state);
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
	 //case state::GAME_OVER:
	 //return; // for now
      case state::EXIT:
	 return;
   }
}

// process a single frame for the menu
void Engine::menuLoop() {
   ALLEGRO_EVENT event;
   ALLEGRO_KEYBOARD_STATE kb;
   al_wait_for_event(eventQueue, &event);
   al_get_keyboard_state(&kb);

   _menu->handleEvent(event, _state);
   _menu->handleKey(kb, _state);
   if (_state == state::LOAD && !_root)
      addSingle();
}

void Engine::addSingle() {
   _root = std::make_shared<Single> (_displayWidth, _displayHeight, _fps);
}

void Engine::gameLoop(float& prevTime) {
   ALLEGRO_EVENT event;
   ALLEGRO_KEYBOARD_STATE kb;
   bool redraw = true;
   float crtTime;
   // input
   al_get_keyboard_state(&kb);      
   _root->input(kb);
   // get event
   al_wait_for_event(eventQueue, &event);
   // display closes
   if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      _state = state::EXIT;
      return;
   }
   // timer
   if (event.type == ALLEGRO_EVENT_TIMER) {
      crtTime = al_current_time();
      update(crtTime - prevTime);
      prevTime = crtTime;
      redraw = true;
   }
   // render
   if (redraw && al_is_event_queue_empty(eventQueue)) {
      redraw = false;      
      draw(); 
      al_flip_display();
   }   
   // check if game over
   if (_root->is_game_over()) {
      _state = state::MENU;
   }   
}

// update the game mode
void Engine::update(double dt) {
   if (_root) {
      _root->update(dt);
      _gameScore = _root->getScore();
   }
}

// draws for the game mode
void Engine::draw() {
   if (_root) {
      _root->draw();
   }
}



   
