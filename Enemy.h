#ifndef ENEMY_H
#define ENEMY_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Drawable.h"
#include "Updateable.h"
#include "Point.h"
#include "Vector.h"
#include <memory>
#include<stdexcept>

class Enemy : public Drawable, public Updateable {
  private:
   Point centre, end; 
   ALLEGRO_COLOR color;
   Vector speed, projSpeed;
   int intspeed=4;
   int size;
   int lives;
   bool dead;
   bool fire;
   ALLEGRO_TIMER *fireDelayE=NULL;
   
   
  public:
  Enemy(Point s, ALLEGRO_COLOR c, Vector sp) : centre(s), color(c), speed(sp)
   {//change 30 to game fps
      if((fireDelayE = al_create_timer(1.0/30))==NULL)
	 throw std::runtime_error("cannot create fireDelat timer");
      al_start_timer(fireDelayE);
      lives = 1;
      dead = false;
      size = 10;
      fire=false;
      projSpeed.x=1.5*speed.x;
      projSpeed.y=1.5*speed.y;
   }
   ~Enemy(){
      if(fireDelayE!=NULL)
	 al_destroy_timer(fireDelayE);
   }
   void setFireE(bool f) { fire=f; }
   bool getFireE(){return fire;}
   Point getCentreE(){return centre; }
   ALLEGRO_COLOR getColorE(){return color;}
   Vector getSpeedE(){ return projSpeed;}
    Enemy(Point s, Point e, ALLEGRO_COLOR c): centre(s), end(e), color(c)
   {
    lives=1;
    dead=false;
    size=20;
    speed.x=(end.x/centre.x)/intspeed;
    speed.y=(end.y/centre.y)/intspeed;
    }

   int getSize() { return size; }
   Point getCentre() { return centre; }
   bool getDead(){return dead; }

   void hit() {
      lives = lives - 1;
      if (lives < 1)
	 dead = true;
   }
   
   // draw image to display of enemy ship
   void draw() {
      al_draw_rectangle(centre.x - size, centre.y - size,
			centre.x + size, centre.y + size,
			color, 3);
   }

   // update position of enemy ships
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

      //int randE=rand()%500;
      if(al_get_timer_count(fireDelayE)>80){
	 fire=true;
	 al_stop_timer(fireDelayE);
	 al_set_timer_count(fireDelayE, 0);
	 al_start_timer(fireDelayE);
      }    
      
      
   }
   


};


#endif
