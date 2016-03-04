/**
   Author: Josh Mohan
   Date: Mar 4, 2016

   purpose: Get that user input, move things on the screen

 **/
#ifndef INPUT_H
#define INPUT_H
#include "Display.h"
class input {
   bool complete=false;
  public:
   enum KEYS{up, down, left, right};
   bool keys[4]={false, false, false, false};
   input() {
      al_init_primitives_addon();
      al_install_keyboard();
      event_queue=al_create_event_queue();
      al_register_event_source(event_queue, al_get_keyboard_event_source());
      //event source needs display component
      //al_register_event_source(event_queue, al_get_display_event_source(disp));
	 ALLEGRO_EVENT ev;
	 al_wait_for_event(event_queue, &ev);
	 
	 //key press has started
	 if(ev.type== ALLEGRO_EVENT_KEY_DOWN)
	    switch(ev.keyboard.keycode)
	    {
	       case ALLEGRO_KEY_UP:
		  keys[up]=true;
		  break;
	       case ALLEGRO_KEY_DOWN:
		  keys[down]=true;
		  break;
	       case ALLEGRO_KEY_RIGHT:
		  keys[right]=true;
		  break;
	       case ALLEGRO_KEY_LEFT:
		  keys[left]=true;
		  break;
	    }
	 
	 //key press has finished
	 else if(ev.type==ALLEGRO_EVENT_KEY_UP)
	    switch(ev.keyboard.keycode)
	    {
	        case ALLEGRO_KEY_UP:
		  keys[up]=false;
		  break;
	       case ALLEGRO_KEY_DOWN:
		  keys[down]=false;
		  break;
	       case ALLEGRO_KEY_RIGHT:
		  keys[right]=false;
		  break;
	       case ALLEGRO_KEY_LEFT:
		  keys[left]=false;
		  break;
	    }
	 //this is the line that needs display
	 //else if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
	 //{
	    //do something that makes the display close?

	 // }
   }
};
      
      

      
      
