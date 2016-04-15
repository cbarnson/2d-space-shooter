#include "Engine.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdexcept>
#include <iostream>

#include "Menu.h"
#include "State.h"
#include "Action.h"
#include "Root.h"
#include "Single.h"
#include "Versus.h"
#include "Timer.h"

Engine::Engine(int w, int h, int fps) : _displayWidth(w), _displayHeight(h), 
					_fps(fps),
					_gameScore(-1),
					_state(gs::state::MENU),
					_timer(NULL),
					_eventQueue(NULL)
{
   
}

Engine::~Engine() {
   if (_timer != NULL) al_destroy_timer(_timer);
   if (_eventQueue != NULL) al_destroy_event_queue(_eventQueue);
   if (_display != NULL) al_destroy_display(_display);
   _root.reset();
   _menu.reset();
}


// initialize Allegro, the _display window, the addons, the timers, and event 
// sources
void Engine::init() {
   // initialize allegro
   al_init();
   // create the display
   if ((_display = al_create_display(_displayWidth, _displayHeight)) == NULL) {
      std::cout << "Cannot initialize the display\n";
      exit(1); 
   }   
   // initialize addons
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();
   // initialize our timers
   if ((_timer = al_create_timer(1.0 / _fps)) == NULL) {
      std::cout << "error, could not create timer\n";
      exit(1);
   }
   if ((_eventQueue = al_create_event_queue()) == NULL) {
      std::cout << "error, could not create event queue\n";
      exit(1);
   }
   // register our allegro _eventQueue
   al_register_event_source(_eventQueue, al_get_display_event_source(_display)); 
   al_register_event_source(_eventQueue, al_get_timer_event_source(_timer));
   al_start_timer(_timer);
   // install keyboard
   if (!al_install_keyboard()) {
      std::cerr << "Could not install keyboard\n";
   }
   
   // register keyboard
   al_register_event_source(_eventQueue, al_get_keyboard_event_source());
}


// repeatedly call the state manager function until the _state is EXIT
void Engine::run() {
   float prevTime = 0;
   // main engine loop
   while (_state != gs::state::EXIT) {
      processGameLogic(prevTime, _state);
   }
}


void Engine::processGameLogic(float& prevTime, gs::state currentState) {
   switch (currentState) {
      case gs::state::PLAY:
	 if (_root && _menu) {
	    _menu.reset();
	 }
	 gameLoop(prevTime);
	 break;
      case gs::state::MENU:
	 if (!_menu) {
	    addMenu();
	 }
	 menuLoop();
	 break;
      case gs::state::LOAD:
	 menuLoop();
	 break;
      case gs::state::LOAD_VERSUS:
	 menuLoop();
	 break;
      case gs::state::EXIT:
	 return;
   }
}

// process a single frame for the menu
void Engine::menuLoop() {
   ALLEGRO_EVENT event;
   ALLEGRO_KEYBOARD_STATE kb;
   al_wait_for_event(_eventQueue, &event);
   al_get_keyboard_state(&kb);

   _menu->handleEvent(event, _state);
   _menu->handleKey(kb, _state);
   if (_state == gs::state::LOAD && !_root) {
      addSingle();
   }
   else if (_state == gs::state::LOAD_VERSUS && !_root) {
      addVersus();
   }
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
   al_wait_for_event(_eventQueue, &event);
   
   // _display closes
   if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      _state = gs::state::EXIT;
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
   if (redraw && al_is_event_queue_empty(_eventQueue)) {
      redraw = false;      
      draw(); 
      al_flip_display();
   }
   
   // check if game over
   if (_root->is_game_over()) {
      _state = gs::state::MENU;
      _root.reset();
   }   
}

// update the game mode
void Engine::update(double dt) {
   if (_root) {
      _root->update(dt);
   }
}

// draws for the game mode
void Engine::draw() {
   if (_root) {
      _root->draw();
   }
}


void Engine::addSingle() {
   _root = std::make_shared<Single> (_displayWidth, _displayHeight, _fps, _playerName);
   _root->init();
}

void Engine::addVersus() {
   _root = std::make_shared<Versus> (_displayWidth, _displayHeight, _fps);
   _root->init();
}

void Engine::addMenu() {
   _menu = std::make_shared<Menu> (_fps);
   _menu->init();
}



   
