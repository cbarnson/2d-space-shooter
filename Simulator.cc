/**
 * @file Simulator.cc
 * @brief Implementation for Simulator class- runs main game loop
 *
 * @author
 * @bug
 */

#include "Simulator.h"

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

	 if (!mode_selected) {
	    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
	       switch (ev.keyboard.keycode) {
		  case ALLEGRO_KEY_ESCAPE:
		     return;
		  case ALLEGRO_KEY_1:
		     single_player(); // run single player mode
		     mode_selected = true;
		     break;
		  case ALLEGRO_KEY_2:
		     multi_player(); // run multi player mode
		     mode_selected = true;
		     break;		     
	       }
	    }
	 }	
	 
	 switch (ev.type) {
	    case ALLEGRO_EVENT_TIMER:
	       menuMessage(); // display menu
	       break;
	       
	    case ALLEGRO_EVENT_DISPLAY_CLOSE:
	       return; // exit
	 }
	 
	 if (mode_selected && al_is_event_queue_empty(eventQueue)) {

	    if (gameReady()) { // condition to enter game loop
	       mode_selected = false;
	       break;
	    }
	 }

      } 
      
      // GAME LOOP //////////////////////////////////////////////
      while(1) {	 
	 ALLEGRO_EVENT ev;
	 al_wait_for_event(eventQueue, &ev);
	 
	 // INPUT
	 getInput(ev);

	 switch (ev.type) {	    
	    case ALLEGRO_EVENT_TIMER:
	       crtTime = al_current_time();
	       updateRoot(crtTime - prevTime); // update game
	       prevTime = crtTime;		    
	       redraw = true;
	       break;
	       
	    case ALLEGRO_EVENT_DISPLAY_CLOSE:
	       return; // exit
	       
	 }

	 // DRAW
	 if(redraw && al_is_event_queue_empty(eventQueue)) {
	    drawRoot();
	    redraw = false;
	 }

	 // CHECK GAME OVER
	 if (is_game_over()) {
	    reset_game();
	    break;
	 }
 
      } 
      // RETURN TO MENU SCENE
   }
}
