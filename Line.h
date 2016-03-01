/**
 * @file Line.h
 * @brief Definition of the Line class
 *
 * This class uses two Point objects to represent a straight line with a certain slope
 *
 * @author Cody Barnsonn
 * @bug No known bugs
 */

#ifndef _LINE
#define _LINE

#define PI 3.14159265
#include "Point.h"
#include <cmath>


/**
 * @struct _line
 * @brief represents a straight line from the Point object _start to the Point object _end
 * with a certain slope
 */

struct _line {

   
   /**
    * @var Point _start
    * represents the start point
    * @var Point _end
    * represents the end point
    */
   Point _start, _end;
   
   _line();
_line(Point a, Point b) : _start(a), _end(b) {};
   
   
   /**
    * @fn length()
    * @brief finds the scalar distance between the two points
    * @param none
    * @return value of type double
    */
   double length() {
      return sqrt(pow(_end.y - _start.y, 2) + pow(_end.x - _start.x, 2));
   }

   
   /**
    * @fn get_angle_ccw(double change_in_angle)
    * @brief calculates the new angle (in radians)
    * @param change_in_angle the change in angle (added; counter-clockwise change)
    * @return double value representing radians in the range [-PI, PI]
    */
   double get_angle_ccw(double change_in_angle) {
      return -(atan2(_start.y - _end.y, _end.x - _start.x) + change_in_angle);
   }

   
   /**
    * @fn get_angle_cw(double change_in_angle)
    * @brief calculates the new angle (in radians)
    * @param change_in_angle the change in angle (subtracted; clockwise change)
    * @return double value representing radians in the range [-PI, PI]
    */
   double get_angle_cw(double change_in_angle) {
      return -(atan2(_start.y - _end.y, _end.x - _start.x) - change_in_angle);
   }

   
   /**
    * @fn get_endpoint_ccw(double change_in_angle, double new_length)
    * @brief calculates the position of the endpoint for the new line with some change in angle
    * @param change_in_angle the change in angle (radians)
    * @param new_length the straight line distance from start to end for the new line
    * @return Point object
    */
   Point get_endpoint_ccw(double change_in_angle, double new_length) {
      return Point(_end.x - new_length * cos(get_angle_ccw(change_in_angle)),
		   _end.y - new_length * sin(get_angle_ccw(change_in_angle)));
   }

   
   /**
    * @fn get_endpoint_cw(double change_in_angle, double new_length)
    * @brief calculates the position of the endpoint for the new line with some change in angle
    * @param change_in_angle the change in angle (radians)
    * @param new_length the straight line distance from start to end for the new line
    * @return Point object
    */
   Point get_endpoint_cw(double change_in_angle, double new_length) {      
      return Point(_end.x - new_length * cos(get_angle_cw(change_in_angle)),
		   _end.y - new_length * sin(get_angle_cw(change_in_angle)));
   }

};

#endif
