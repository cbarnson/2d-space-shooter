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

#include "Updateable.h"
#include "Projectile.h"
#include "Action.h"


struct Point;
struct Vector;
class Sprite;

extern const int PLAYER_SIZE;
extern const int PLAYER_TRAVEL_SPEED;
extern const float MAX_LIFE;

class Player : public Updateable {
  public:
   Point centre;        /**< ship position */
   ALLEGRO_COLOR color; /**< ship color */
   
   Vector speed;        /**< movement speed in any direction */
   float lives;         /**< lives remaining of Player object before destroyed */
   int row;             /**<row of animation to be played */
   int col;             /**< column of animation to be played */
   bool dead;           /**< signals Player object has been killed */

   /**
    * @fn Constructor
    * @param p centre point of player
    * @param c color of player represented as an al_map_rgb(r, g, b)
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
    * @brief renders the player
    * @param std::shared_ptr<Sprite>
    */
   void draw(std::shared_ptr<Sprite> sprite, int flags);

   
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
   act::action inputPlayer2(ALLEGRO_KEYBOARD_STATE&); // only used in versus mode

  private:
   // HELPER FUNCTIONS 
   void selectShipAnimation();
   void checkBoundary();
   void drawRemainingLife();
   
};

#endif

