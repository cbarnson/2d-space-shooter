/**
 * @file Player.h
 * @brief class definition of the Player class
 *
 * This class inherits public members of Controls and Drawable
 *
 * @author
 * @bug
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "Updateable.h"
#include "Projectile.h"
#include "Action.h"

#include <memory>

struct Point;
struct Vector;
class Sprite;
class Input;

extern const int PLAYER_SIZE;
extern const int PLAYER_TRAVEL_SPEED;
extern const float MAX_LIFE;

class Player : public Updateable {
  public:
   Point centre;        /**< ship position */
   ALLEGRO_COLOR color; /**< ship color */
   
   Vector speed;        /**< movement speed in any direction */
   float lives;           /**< lives remaining of Player object before destroyed */
   int row; /**<row of animation to be played */
   int col;/**< column of animation to be played */
   bool dead;           /**< signals Player object has been killed */

   /**@fn Constructor
    * @param p centre point of player
    * @param c color of player
    */
   Player(Point p, ALLEGRO_COLOR c);

   /**
    * @destructor
    */
   ~Player();

   /**
    * @fn hit(int)
    * @brief reduces player life on hit
    * @param int to reduce life by
    */
   void hit(int);

   
   /**
    * @fn draw(...)
    * @brief
    * @param
    */
   void draw(std::shared_ptr<Sprite>);

   
   /**
    * @fn update(double)
    * @brief
    * @param
    */
   void update(double);

   
   /**
    * @fn input(...)
    * @brief
    * @param
    */
   act::action input(ALLEGRO_KEYBOARD_STATE&);

  private:
   // HELPER FUNCTIONS 
   void selectShipAnimation();
   void checkBoundary();
   void drawRemainingLife();
   
};

#endif

