/**
 * @file Simulator.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Simulator.h"
#include "Hotkeys.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>

// constructor
Simulator::Simulator(const Display & d, int fps) :
   framesPerSec(fps), timer(NULL), eventQueue(NULL) {

   if ((timer = al_create_timer(1.0 / fps)) == NULL)
      throw std::runtime_error("Cannot create allegro timer");
   if ((eventQueue = al_create_event_queue()) == NULL)
      throw std::runtime_error("Cannot create event queue");

   al_register_event_source(eventQueue, al_get_display_event_source(d.getAllegroDisplay()));   
   al_register_event_source(eventQueue, al_get_timer_event_source(timer));
   al_start_timer(timer);
   
}

// destructor
Simulator::~Simulator() {
   if (timer != NULL)
      al_destroy_timer(timer);
   if (eventQueue != NULL)
      al_destroy_event_queue(eventQueue);
}


void Simulator::run() {

   bool mode_selected = false;
   bool redraw = true;
   double crtTime, prevTime = 0;
   al_install_keyboard();
   al_register_event_source(eventQueue, al_get_keyboard_event_source());

  
   while(1) {
   
      // MENU LOOP
      while(1) {
	 ALLEGRO_EVENT ev;
	 al_wait_for_event(eventQueue, &ev);	

	 if (ev.type == ALLEGRO_EVENT_KEY_DOWN) 	 
	    switch (ev.keyboard.keycode) {
	       
	       case ALLEGRO_KEY_ESCAPE:
		  return;
		  
	       case ALLEGRO_KEY_1: // single player mode
		  single_player();
		  mode_selected = true;
		  break;
		  
	       case ALLEGRO_KEY_2: // multi player mode
		  mode_selected = true;
		  multi_player();
		  break;
		  
	       default:
		  break;
	    }
	 
	 
	 if (ev.type == ALLEGRO_EVENT_TIMER) 
	    menuMessage();	 	 
	 else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
	    return;

	 
	 if (mode_selected)
	    break;      
      } // end of menu loop


      
      // GAME LOOP //////////////////////////////////////////////
      while(1) {
	 
	 ALLEGRO_EVENT ev;
	 al_wait_for_event(eventQueue, &ev);
	 if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
	    if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
	       return;	       
	    setRoot(ev.keyboard.keycode);
	 }
	 else if (ev.type == ALLEGRO_EVENT_KEY_UP) 
	    resetRoot(ev.keyboard.keycode);
	 

	 // check the event type and call the update functions
	 if(ev.type == ALLEGRO_EVENT_TIMER) {	 
	    crtTime = al_current_time();
	    controlRoot();
	    updateRoot(crtTime - prevTime);
	    collisionRoot();
	    prevTime = crtTime;
	 
	    if (is_game_over()) {
	       mode_selected = false;
	       break;
	    }
	    // set redraw flag to avoid redrawing an empty event_queue
	    redraw = true;
	 }
	 // if the display is closed, end the program
	 else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
	    return;

	 
	 if(redraw && al_is_event_queue_empty(eventQueue)) {
	    drawRoot();
	    redraw = false;
	 }
	 
      } // end of game loop ///////////////////////////////////

   }
   
  
}

