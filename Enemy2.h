/**
 * @file Enemy2.h
 * @brief Definition of Enemy2 class, the second type of enemy
 *
 * 
 * @author
 * @bug
 */

#ifndef ENEMY2_H
#define ENEMY2_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Drawable.h"
#include "Updateable.h"
#include "Point.h"
#include "Vector.h"
#include "Enemy.h"
#include <memory>
#include<stdexcept>


class Enemy2: public Enemy{
  private:
   Point centre; 
   ALLEGRO_COLOR color;
   Point end;
   Vector speed, projSpeed;
   int intspeed=4;
   int size;
   int rDepth;
   int lives;
   bool dead;
   bool fire;
   ALLEGRO_TIMER *fireDelayE=NULL;
   
  Enemy2(Point s, ALLEGRO_COLOR c, Point e, int rDepth): Enemy(s, c, e), rDepth(rDepth)
   {
      if((fireDelayE = al_create_timer(1.0/30))==NULL)
	 throw std::runtime_error("cannot create fireDelat timer");
      al_start_timer(fireDelayE);
      lives = 1;
      dead = false;
      size = 10;
      fire=false;
      projSpeed.x=1.5*speed.x;
      projSpeed.y=0;
      if(rDepth==3)
      { speed.x=-150; speed.y=0; }
      if (rDepth==2)
      { speed.x=-150; speed.y=-50;}
      if (rDepth==1)
      { speed.x= -180; speed.y=-80; }
   }
   int getrDepth(){return rDepth;}
   /*
   void hit() {
      lives = lives - 1;
      if (lives < 1)
	 dead = true;
	 }*/
   //*******************************/
   //Getters and setters
   //******************************/
   /*
   void setFireE(bool f) { fire=f; }
   bool getFireE(){return fire;}
   Point getCentreE(){return centre; }
   ALLEGRO_COLOR getColorE(){return color;}
   Vector getSpeedE(){ return projSpeed;}
   int getSize() { return size; }
   Point getCentre() { return centre; }
   bool getDead(){return dead; }  
   
   // draw image to display of enemy ship
   void draw() {
      al_draw_rectangle(centre.x - size, centre.y - size,
			centre.x + size, centre.y + size,
			color, 3);
   }
   */
   // update position of enemy ships
   /*
   void update(double dt) {
      Point newCentre= centre;
      newCentre=centre+speed*dt;
      if(newCentre.y<=0)
      {
	 this->speed.y=speed.y*-1.0;
      }
      if(newCentre.y>=600-size)
      {
	 this->speed.y=speed.y*-1.0;
      }
      if(newCentre.x<0)
      {
	 dead=true;
      }
      centre=newCentre;

      int randE=rand()%50;
      if(al_get_timer_count(fireDelayE)>(randE+20)){
	 fire=true;
	 al_stop_timer(fireDelayE);
	 al_set_timer_count(fireDelayE, 0);
	 al_start_timer(fireDelayE);
	 }     
	 }*/

};
#endif
