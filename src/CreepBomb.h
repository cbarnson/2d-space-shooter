/**
 * @file Creep.h
 * @brief derived class of Enemy- main implementation of Enemy type
 *
 * @author
 * @bug
 **/

#ifndef CREEPBOMB_H
#define CREEPBOMB_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <memory>
#include <iostream>
#include <stdexcept>

#include "Enemy.h"
#include "Drawable.h"
#include "Updateable.h"
#include "Point.h"
#include "Vector.h"
#include "Sprite.h"
//#include "Timer.h"
#include "Root.h"

struct Point;
struct Vector;
class Timer;

class CreepBomb : public Enemy {
   
  private:
   std::shared_ptr<Timer> fireDelay;
   Vector projSpeed;//not actually used in this class
   int size;/**< size of the enemy-- used for hitbox detection */
   int row, col;/**<rows and column of the animation to be played */
   int lives;/**<lives of the enemy-- how many hits it takes to be destroyed */
   int dAnim;/**<counter to play frames of the death animation */
   bool dAnim_complete;/**<bool flag for death animation- used to delete dead enemies in Single*/   
   // int fireSpeed;//pretty sure not needed   
   bool fire, fired, fire2;/**<bool flags to decide when to fire lasers */
	
  public:
   CreepBomb(Point cen, ALLEGRO_COLOR col, Vector spd);
   ~CreepBomb();
   /*
   void load_assets();
   void update(double dt);
   void deathAnim(std::shared_ptr<Sprite>);
   void hit();
   void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death);
   */
   void setFire(bool f);	
   ALLEGRO_COLOR getColor();
   Vector getProjSpeed(); 
   int getSize();    
   Point getCentre();
   bool getDead(); 
   bool getFire();    
   void update(double dt);
   void load_assets();
   
   /** @fn deathAnim(shared_ptr<Sprite>)
    * @param d sprite to be used for death explosion animation
    */
   void deathAnim(std::shared_ptr<Sprite> d);
   void hit();
   
   /** @fn draw(shared_ptr<Sprite> ship, shared_ptr<Sprite> death>
    * function inherited from Drawable- draws either the ship or the explosion
    * @param ship Animation for enemy ship
    * @param death Animation for death
    */
   void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death);
   bool getdAnim_complete();
   
};

#endif
