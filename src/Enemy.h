/**
 * @file Enemy.h
 * @brief Declaration of Enemy class
 *
 * @author
 * @bug
 */

#ifndef ENEMY_H
#define ENEMY_H

#include <allegro5/allegro.h>

#include <memory>

#include "Updateable.h"
#include "Point.h"
#include "Vector.h"

class Sprite;

class Enemy : public Updateable {

  public:
   Point centre;
   ALLEGRO_COLOR color;
   Vector speed;
   bool dead;
      
  Enemy(Point p, ALLEGRO_COLOR c, Vector s) : centre(p), color(c), speed(s), dead(false)
   { }

   virtual ~Enemy() { }

   void update(double dt) { }

   virtual void setFire(bool f) = 0;
   virtual ALLEGRO_COLOR getColor() = 0;
   virtual Vector getProjSpeed() = 0; 
   virtual Point getCentre() = 0;
   virtual int getSize() = 0;    
   virtual bool getdAnim_complete() = 0; 
   virtual bool getDead() = 0;
   virtual bool getFire() = 0;
   virtual void hit() = 0;
   virtual void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death) = 0;

};

#endif
   
/*private:
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
*/
//};

