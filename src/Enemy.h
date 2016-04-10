/**
 * @file Enemy.h
 * @brief Declaration of Enemy class
 *
 * @author
 * @bug
 */
#ifndef ENEMY_H
#define ENEMY_H

#include "Updateable.h"
#include "Point.h"
#include "Vector.h"

#include <allegro5/allegro.h>
#include <memory>

class Sprite;

class Enemy : public Updateable {
  private:
   Point centre, end; 
   ALLEGRO_COLOR color;
   Vector speed;
	
   ALLEGRO_TIMER *fireDelay;
   
   Vector projSpeed;
   int size;
   int lives;
   int dAnim;
   int fireSpeed;
   
   bool dAnim_complete;
   bool dead;
   bool fire;
	
  public:
   // CONSTRUCTOR 1
   Enemy(Point p, ALLEGRO_COLOR c, Vector s);
   ~Enemy();
   
   void setFire(bool f);	
   ALLEGRO_COLOR getColor();
   Vector getProjSpeed(); 
   Point getCentre();
   int getSize();    
   bool getdAnim_complete(); 
   bool getDead(); 
   bool getFire();    
   void update(double dt);
   void deathAnim(std::shared_ptr<Sprite>);
   void hit();
   void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death);
};


#endif
