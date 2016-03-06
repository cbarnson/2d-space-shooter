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
#include <vector>
#include <memory>
#include <list>

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
   // switch to trigger model drawing
   bool redraw=true;
   
   // current time and previous time in seconds; needed so we can try
   // to keep track of the passing of real time.
   double crtTime, prevTime = 0;
   
   // this initializes the keyboard for input from the player
   al_install_keyboard();   
   al_register_event_source(eventQueue, al_get_keyboard_event_source());

   // main while loop
   // gets a key press event, sets the appropriate indices of our bool vector to true
   // then calls updatePlayerControls and updateModel to manipulate the objects
   // with respect to some time fragment
   while(1) {
      ALLEGRO_EVENT ev;
      al_wait_for_event(eventQueue, &ev);

      if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
	 setPlayer(ev.keyboard.keycode);
      }
      else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
	 resetPlayer(ev.keyboard.keycode);
      }
            
      // check the event type and call the update functions
      if(ev.type == ALLEGRO_EVENT_TIMER) {	 
	 crtTime = al_current_time();
	 updatePlayerControls();
	 updateModel(crtTime - prevTime);
	 prevTime = crtTime;
	 
	 // set redraw flag to avoid redrawing an empty event_queue
	 redraw = true;
      }
      // if the display is closed, end the program
      else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
	 break;
      }
      
      if(redraw && al_is_event_queue_empty(eventQueue)) {
	 drawModel();
	 redraw = false;
      }
   }
}

