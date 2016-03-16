/**
 * @file Simulator.cc
 * @brief
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
   //cout << "now entering menu loop\n";
   
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
		  //cout << "sim - selected single\n";
		  mode_selected = true;
		  break;
		  
	       case ALLEGRO_KEY_2: // MULTI PLAYER
		  multi_player();
		  //cout << "sim - selected multi\n";
		  mode_selected = true;
		  break;
		  
	       default:
		  break;
	    }
	 
	 // MENU SCENE
	 if (ev.type == ALLEGRO_EVENT_TIMER) 
	    menuMessage();
	 // DISPLAY CLOSES
	 else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
	    return;

	 
	 // ENTER GAME LOOP
	 if (mode_selected && al_is_event_queue_empty(eventQueue)) {
	    //cout << "mode has been selected\n";
	    break;
	 }

      } // end of menu loop

      //cout << "now entering game loop\n";
      if (al_is_keyboard_installed())
	 //cout << "keyboard is installed\n";

      
      // GAME LOOP //////////////////////////////////////////////
      while(1) {	 
	 ALLEGRO_EVENT ev;
	 al_wait_for_event(eventQueue, &ev);
	 //cout << "waiting for input\n";
	 // INPUT
	 if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {	    
	    if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
	    	return;
	    //cout << "key event down\n";
	    setRoot(ev.keyboard.keycode);
	 }
	 else if (ev.type == ALLEGRO_EVENT_KEY_UP) 
	    resetRoot(ev.keyboard.keycode);
	 
	 //cout << "I am past input set/reset section\n";
	 
	 // DO EVERYTHING FOR GAME
	 if(ev.type == ALLEGRO_EVENT_TIMER) {	 
	    crtTime = al_current_time();
	    controlRoot();
	    updateRoot(crtTime - prevTime);
	    collisionRoot();
	    prevTime = crtTime;		    
	    redraw = true;
	 }

	 //cout << "I am past allegro event timer section\n";
	 
	 // DISPLAY CLOSES
	 if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
	    return;
	 }

	 //cout << "about to enter redraw section\n";
	 
	 // DRAW
	 if(redraw && al_is_event_queue_empty(eventQueue)) {
	    //al_clear_to_color(al_map_rgb(0, 0, 0));
	    drawRoot();
	    //al_flip_display();
	    redraw = false;
	 }

	 //cout << "now checking if game is over\n";
	 
	 // CHECK GAME OVER
	 if (is_game_over()) {
	    //cout << "game over\n";
	    mode_selected = false;
	    reset_game();
	    break;
	 }
 
      } // end of game loop //
      // RETURN TO MENU SCENE
      //cout << "end of game loop\n";
      }
   
  
}

