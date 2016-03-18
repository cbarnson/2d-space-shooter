/**
 *  @file Vector.h
 *  @brief Definition of the Vector class
 *
 *
 *  @author Cody Barnson
 *  @bug No known bugs
 */

#ifndef _VECTOR_H
#define _VECTOR_H

/**
 * @struct Vector
 * @brief represents the change in position of x and y
 */

#include <ctime>
#include <cstdlib>


struct Vector {
   double x;
   double y;
   Vector (double a=0.0, double b=0.0) : x(a), y(b) {};
   
   /**
    *  @fn Vector operator * (double scalar);
    *  @brief takes a scalar value and multiplies x and y by it
    *  @param scalar 
    *  @return Vector
    */
   Vector operator * (double scalar) {
      return Vector(x*scalar, y*scalar);
   }

   
   void rollRandom() {
      x = rand() % 200 - 400; // range
      y = rand() % 400 - 200; // range [-200, 200]
   }
   
   // range [-200, 200]
   void rollRandomY() {
      y = rand() % 400 - 200;
   }

   // range [-200,-1]
   void rollRandomX() {
      x = rand() % 200 - 400;
   }
   
   void reflectY() {
      y = -y;
   }

   void reflectX() {
      x = -x;
   }
   
   void xMod(int m) {
      x = x + m;
   }
   void yMod(int m) {
      y = y + m;
   }
   
};

#endif
