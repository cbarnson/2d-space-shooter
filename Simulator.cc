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

	 // INPUT
	 if (ev.type == ALLEGRO_EVENT_KEY_DOWN) 	 
	    switch (ev.keyboard.keycode) {
	       
	       case ALLEGRO_KEY_ESCAPE: // EXIT GAME
		  return;
		  
	       case ALLEGRO_KEY_1: // SINGLE PLAYER
		  single_player();
		  mode_selected = true;
		  break;
		  
	       case ALLEGRO_KEY_2: // MULTI PLAYER
		  mode_selected = true;
		  multi_player();
		  break;
		  
	       default:
		  break;
	    }
	 // ENTER GAME LOOP
	 if (mode_selected)
	    break;      
	 
	 // MENU SCENE
	 if (ev.type == ALLEGRO_EVENT_TIMER) 
	    menuMessage();
	 // DISPLAY CLOSES
	 else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
	    return;

      } // end of menu loop


      
      // GAME LOOP //////////////////////////////////////////////
      while(1) {	 
	 ALLEGRO_EVENT ev;
	 al_wait_for_event(eventQueue, &ev);

	 // INPUT
	 if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {	    
	    if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
	       return;	    
	    setRoot(ev.keyboard.keycode);
	 }
	 else if (ev.type == ALLEGRO_EVENT_KEY_UP) 
	    resetRoot(ev.keyboard.keycode);
	 

	 // DO EVERYTHING FOR GAME
	 if(ev.type == ALLEGRO_EVENT_TIMER) {	 
	    crtTime = al_current_time();
	    controlRoot();
	    updateRoot(crtTime - prevTime);
	    collisionRoot();
	    prevTime = crtTime;		    
	    redraw = true;
	 }

	 // DISPLAY CLOSES
	 else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
	    return;

	 // DRAW
	 if(redraw && al_is_event_queue_empty(eventQueue)) {
	    drawRoot();
	    redraw = false;
	 }

	 // CHECK GAME OVER
	 if (is_game_over()) {
	    mode_selected = false;
	    reset_game();
	    break;
	 }
 
      } // end of game loop //
      // RETURN TO MENU SCENE

   }
   
  
}

