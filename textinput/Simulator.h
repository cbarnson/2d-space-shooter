#ifndef __SIMULATOR_H
#define __SIMULATOR_H

#include "Display.h"
#include <allegro5/allegro.h>


/// Class responsible for setting up the Allegro library for some basic animation.
/**
Initializes the Allegro timer that controls rendering, sets up a
common Allegro event queue, and provides a rendering loop function for
the animation.
 **/
class Simulator {
private:
	int framesPerSec; /// the rendering frequency

	ALLEGRO_EVENT_QUEUE *eventQueue;  /// event storage 
	ALLEGRO_TIMER *timer;  /// generates events for the simulation


public:
	/// The constructor initializes the Allegro library
	/**
		 \param d the display object; needed so that the Simulator object
		 recognizes when the "close window" button is pressed and the
		 simulation needs to stop.
		 \param fps the number of frames per second. This is the rate at
		 which both the simulation and the rendering are performed.
	 **/
	Simulator(const Display & d, int fps);

	/// The destructor frees all the Allegro resources allocated by the
	/// constructor 
	~Simulator();

	/// the rendering loop
	/**
		 Must be invoked to start the simulation. The function exits when
		 the user closes the display window
	 **/
	void run();

	/// called whenever the state of the objects need updating.
	/**
		 Subclass and provide an implementation for this function that
		 specifies how the model used in the simulation is updated. It
		 is called by run().
		 \param dt is the time in seconds since the most recent
		 model update. The model needs to be changed to a state that
		 reflects the passing of dt seconds after the current state. It is
		 possible that dt is zero or negative.
	 **/
	virtual void updateModel(double dt) = 0;

	/// called whenever the model needs to be displayed.
	/**
		 Subclass and provide an implementation for this function that
		 cntains the drawing code.
	 **/
	virtual void drawModel() = 0;
};

#endif
