/**
 * @file Display.h
 * @brief Declaration of Display class
 *
 * @authors Cody, Josh, and Dawson
 * @bug
 */
#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <allegro5/allegro.h>

/**
 * @class Display
 * @brief initializes allegro and the following addons:
 *        allegro_primitives
 *        allegro_font
 *        allegro_ttf
 *        allegro_image
 *
 *        A single Display object must be instantiated prior to attempting any
 *        kind of drawing
 */
class Display {
private:
	ALLEGRO_DISPLAY *display;
	int width, height;
public:
	/**
	 * @fn Display(int, int)
	 * @brief Constructor
	 *        Initializes allegro, allegro addons, and creates a window of the
	 *        given size
	 */	 
	Display(int w = 800, int h = 600);

	/**
	 * @fn ~Display()
	 * @brief Destructor
	 *        Closes the window and frees the allegro resources
	 */
	~Display();

	/**
	 * @fn getW()
	 * @brief returns the width of the window in pixels
	 */
	int getW() const { return width; };

	/**
	 * @fn getH()
	 * @brief returns the height of the window in pixels
	 */
	int getH() const { return height; };

	/**
	 * @fn getAllegroDisplay()
	 * @brief returns a pointer to the Allegro display
	 */
	ALLEGRO_DISPLAY * getAllegroDisplay() const { return display; }
};


#endif
