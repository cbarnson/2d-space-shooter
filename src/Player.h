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

#include <memory>

#include "Entity.h"
#include "Type.h"
#include "Projectile.h"
#include "Action.h"
#include "Point.h"
#include "Vector.h"

class Sprite;
class Input;

extern const int PLAYER_SIZE;
extern const int PLAYER_TRAVEL_SPEED;
extern const float MAX_LIFE;

class Player : public Entity {
  public:
   float lives;         /**< lives remaining of Player object before destroyed*/
   int row;             /**<row of animation to be played */
   int col;             /**< column of animation to be played */
   bool dead;           /**< signals Player object has been killed */

   /**
    * @fn Constructor
    * @param p centre point of player
    * @param c color of player represented as an al_map_rgb(r, g, b)
    */
 Player(Point centre, ALLEGRO_COLOR color, Vector speed) : 
   Entity(centre, color, speed, id::type::PLAYER), lives(3.0), row(0), col(0), 
     dead(false) 
     {
       
     }

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
    * @brief renders the player
    * @param std::shared_ptr<Sprite>
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

