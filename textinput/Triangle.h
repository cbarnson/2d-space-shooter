//////////////////////////////////////////////////////////////////////////////////
/* Josh Mohan
/ CPSC 2720- Assignment 1
/ Feb 23, 2016
/ TRIANGLE.H: Header file and imlpementation for Triangle animations
/
/
///////////////////////////////////////////////////////////////////////////////*/
//#include<iostream>
#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Drawable.h"
#include "Updatable.h"
#include <allegro5/allegro_primitives.h>
#include <random>
using  namespace std;

//Vector and point structs are defined in this file, although are used in Tree as well.
struct Vector {
   double x;
   double y;
   Vector (double a=0.0, double b=0.0) : x(a), y(b) {};
   
   Vector operator * (double scalar) {
      return Vector(x*scalar, y*scalar);
   }
   Vector operator = (Vector A){
      x=A.x;
      y=A.y;
      return *this;
   }
};


struct Point {
   double x;
   double y;
Point(double a=0.0, double b=0.0): x(a), y(b) {};
   Point operator + (Vector v) {
      return Point(x+v.x, y+v.y);
   }
   Point operator = (Point A){
      x=A.x;
      y=A.y;
      return *this;
   }
};

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> randx(0, 780);//random distribution for x and y cooords-
uniform_int_distribution<int> randy(0, 600);//needed because rand() wasn't working well for me




class Triangle: public Updatable, public Drawable{
  private:
   Point origin; // the origin of the triangle
   Point newOrigin;
   Vector crtSpeed; // speed in pixels per sec
   int width, height; // of the window
   int rainsize; // of the drawn block in pixels
   //int ind=10;
   int* A;
   ALLEGRO_EVENT_QUEUE *event_queue;
   bool done=false;

  public:


  Triangle( int speed, int sq): origin(400,300), newOrigin(400,300), crtSpeed(0, 0), rainsize(sq){}
   /*
     void draw: draws the triangle

    */
   void draw()
   {
      al_draw_triangle( static_cast<int>(origin.x), static_cast<int>(origin.y),
			static_cast<int>(origin.x)+(rainsize/2),
			static_cast<int>(origin.y)-(rainsize/2),
			static_cast<int>(origin.x)+rainsize, static_cast<int>(origin.y),
			al_map_rgb(255, 255, 255), 2); 
   }
   /*
     void move: The function that makes the triangle move. Updates current position based on crtSpeed


    */
   void move(double dt)
   {
      //keyboard();
      // Point newOrigin=origin + crtSpeed*dt;
      // if(newOrigin.y>=600){
	 
//	 newOrigin.y=0;
//	 newOrigin.x=randx(gen);
	 //   }
      origin=newOrigin;

   }
   void keyboard()
   {
       al_init_primitives_addon();
      al_install_keyboard();
      event_queue = al_create_event_queue();
      al_register_event_source(event_queue, al_get_keyboard_event_source());

      newOrigin=origin;
  
	 ALLEGRO_EVENT ev;
	 al_wait_for_event(event_queue, &ev);
	 if(ev.type==ALLEGRO_EVENT_KEY_DOWN)
	 {
	    switch(ev.keyboard.keycode)
	    {
	       case ALLEGRO_KEY_LEFT:
		  newOrigin.x-=10;
		  break;
	       case ALLEGRO_KEY_RIGHT:
		  newOrigin.x+=10;
		  break;
	    }
	    origin=newOrigin;
	 }
   }
	 



 
};

#endif
