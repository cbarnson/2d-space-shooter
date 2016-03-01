/**
 * @file Updateable.h
 * @brief Definition of the Updateable abstract class
 *
 * @author Cody Barnson
 * @bug no known bugs
 */
#ifndef UPDATEABLE_H
#define UPDATEABLE_H

/**
 * @class Updateable
 * @brief interface for updateable objects
 *
 * provides the declaration of the update function
 */
class Updateable {
  public:
   /**
    * @fn virtual void update(double)
    * @brief virtual function declaration of update, updates the position of derived objects
    * @param t the change in time since the last position update
    */
   virtual void update(double t) = 0;
};

#endif
