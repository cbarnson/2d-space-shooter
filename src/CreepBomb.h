/**
 * @file Creep.h
 * @brief derived class of Enemy- main implementation of Enemy type
 *
 * @author
 * @bug
 **/

#ifndef CREEPBOMB_H
#define CREEPBOMB_H

#include "Enemy.h"
#include "Drawable.h"
#include "Updateable.h"
#include "Point.h"
#include "Vector.h"
#include "Sprite.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>
#include <iostream>
#include <stdexcept>
#include "Timer.h"
#include "Root.h"

using std::shared_ptr;
using std::make_shared;

class CreepBomb : public Enemy {
  private:
   Point centre, end; 
   ALLEGRO_COLOR color;/**<Color of enemy*/
   Vector speed; /**<Speed of enemy */
   int size;/**< Size of enemy- used for hitbox detection*/
   int lives;/**< lives of the enemy--how many hits it takes to be destroyed*/
   int dAnim;/**<int counter to play frames of death animation */
   int row, col;/**< rows and columns of the animation to be played*/
   bool fire1, fire2;/**< bool flags to  set its fire behaviour */ 
   bool dAnim_complete;/**< bool flag for death animation- used to delete dead enemies in Single*/
   //bool dead;
   bool fire;/**< flag used in Single to decide when to fire lasers */
   std::shared_ptr<Timer> fireDelay;/**< shared pointer to timer class to handle fire timing */
	
  public:
   /** @fn CreepBomb(Point P, Al_Color C, Vector s)
    * @brief Constructor for CreepBomb class
    * @param p Origin point
    * @param c Creep color- used for colission detection in Single
    * @param s Movement speed
    * 
    */
  CreepBomb(Point p, ALLEGRO_COLOR c, Vector s)
     : Enemy(p, c, s), centre(p), color(c), speed(s)
   {
      row=0; col=0;
      fireDelay=std::make_shared<Timer> (60);
      fireDelay->startTimer();
      lives = 3;
      size = 20;
      dAnim = 0;      
      dAnim_complete = false;
      fire = false;
      fire1=false; fire2=false;
   }

   ~CreepBomb();
   
   void setFire(bool f);	
   ALLEGRO_COLOR getColor();
   Vector getProjSpeed(); 
   Point getCentre();
   int getSize();    
   bool getdAnim_complete(); 
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
    * @param ship Animation for enemy ship
    * @param death Animation for death
    */
   void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death);
   
};
#endif
