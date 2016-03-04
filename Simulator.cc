#include "Simulator.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>
#include <vector>


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
   enum KEYS{up, down, left, right, space};
   //bool keys[4]={false, false, false, false};
   std::vector<bool> keys(5, false);
   
   while(1) {
      ALLEGRO_EVENT ev;
      al_wait_for_event(eventQueue, &ev);

//******************************************************/
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
	    case ALLEGRO_KEY_SPACE:
	       keys[space]=true;
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
	    case ALLEGRO_KEY_SPACE:
	       keys[space]=false;
	       break;
	 }
//************************************************************/
      

      
      if(ev.type == ALLEGRO_EVENT_TIMER) {
	 crtTime = al_current_time();
	 updatePlayerControls(keys);
	 updateModel(crtTime - prevTime); // put key input here
	 prevTime = crtTime;
	 // instead of simply calling drawModel() here, we set this flag so that
	 // we redraw only if the event queue is empty; reason: draw is expensive and
	 // we don't want to delay everything too much
	 redraw = true;
      }
      else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
	 break;
      }
      
      if(redraw && al_is_event_queue_empty(eventQueue)) {
	 drawModel();
	 redraw = false;
      }
   }
}
