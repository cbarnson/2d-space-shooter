/**
 * @file Drawable.h
 * @brief Definition of the Drawable abstract class
 *
 * @author Cody Barnson
 * @bug no known bugs
 */

#ifndef DRAWABLE_H
#define DRAWABLE_H

/**
 * @class Drawable
 * @brief interface for drawable objects
 *
 * provides the declaration of the draw function
 */
class Drawable {
  public:
   /**
    * @fn virtual void draw()
    * @brief virtual function to draw derived objects
    */ 
   virtual void draw() = 0;
};

#endif
