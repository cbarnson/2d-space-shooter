#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <allegro5/allegro.h>

/// Class to initialize allegro and open the main window.
/**
 Class Display initializes allegro and the primitives add-on in the
 constructor. A single object must be instantiated prior to attempting
 any kind of drawing. The instantiated object can be used to retrieve
 the dimensions of the window.
*/ 
class Display {
private:
	ALLEGRO_DISPLAY *display;
	int width, height;
public:
	/// Initializes allegro and constructs a window of given size.
	/** Exactly one object must be created before any allegro functions
		 can be used. Both allegro and the primitives add-on (for drawing)
		 are initialized, and a window is displayed.
		 \param w the width of the window displayed in pixels
		 \param h the height of the window displayed in pixels
	 */
	Display(int w=800, int h=600);

	/// Frees allegro resources
	/**
		 The allegro window is closed and the allegro resources are
		 freed. Drawing is not possible afterwards.
	 */
	~Display();

	/// Returns the width of the window
	/**
		 \ret the width of the window in pixels
	*/
	int getW() const { return width; };

	/// Returns the height of the window
	/**
		 \ret the height of the window in pixels
	*/
	int getH() const { return height; };

	/// Returns the Allegro display
	/**
		 \ret a pointer to the Allegro display structure that can be
		 passed to allegro functions requiring an Allegro display argument
	 **/
	ALLEGRO_DISPLAY * getAllegroDisplay() const { return display; }
};


#endif
