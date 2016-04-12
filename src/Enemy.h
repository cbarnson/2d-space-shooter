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
   Point centre;/**<centre point of the enemy */
   ALLEGRO_COLOR color;/**<color of the enemy-- used in Single as an identifier */
   Vector speed;/**<movement speed of enemy */
   bool dead;


   /** @fn Constructor
    * @ brief destructor for Enemy interface
    * @param p Point that represents the centre of the enemy
    * @param c Color of the enemy-- used in Single as an identifier
    * @param s Speed of the enemy
    */
  Enemy(Point p, ALLEGRO_COLOR c, Vector s) : centre(p), color(c), speed(s), dead(false)
   { }

   virtual ~Enemy() { }

   void update(double dt) { }

   
   /** @fn set fire
    * @brief used to reset the boolean flag that represents when an enemy is able to fire
    * @param f boolean value to Fire to
    */
   virtual void setFire(bool f) = 0;
   
   
   /** @fn getColor
    * @brief getter method to return the color value of an enemy
    */
   virtual ALLEGRO_COLOR getColor() = 0;
   

   /** @fn getProjSpeed
    *   @return returns a vector representing Projectile Speed
    */
   virtual Vector getProjSpeed() = 0;
   
   /** @fn getCentre
    *   @return returns the centre point
    */
   virtual Point getCentre() = 0;

   /** @fn getSize
    *   @return returns size integer
    */
   virtual int getSize() = 0;    

   /** @fn getdAnim_complete
    *   @return returns bool value of dAnim
    */
   virtual bool getdAnim_complete() = 0; 

   /** @fn getDead
    *   @return returns bool value of dead
    */
   virtual bool getDead() = 0;

   /** @fn getFire
    *   @return returns bool value of Fire
    */
   virtual bool getFire() = 0;

   /** @fn hit
    *   @brief function that updates enemy when it is hit- generally decreases life
    */
   virtual void hit() = 0;

   
   virtual void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death) = 0;

};

#endif
