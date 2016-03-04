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
};

#endif
