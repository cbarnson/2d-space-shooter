/**
 * @file main.cc
 * @brief
 * 
 * @author
 * @bug
 */

#include "Display.h"
#include "Simulator.h"
#include "gameSimulator.h"
#include "Hotkeys.h"
#include "Player.h"
#include "Point.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>
#include <list>
#include <string>
#include <iostream>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;
using std::vector;


int main() {   
   Display disp;   
   gameSimulator game(disp, 30); // 2nd param is fps 

   // hotkeys player 1
   vector<int> h1;
   h1.push_back(ALLEGRO_KEY_UP);
   h1.push_back(ALLEGRO_KEY_DOWN);
   h1.push_back(ALLEGRO_KEY_RIGHT);
   h1.push_back(ALLEGRO_KEY_LEFT);
   h1.push_back(ALLEGRO_KEY_PAD_0);
      
   // sets up the player, provide parameters: start point on the display, and size of player
   shared_ptr<Player> player1 =
      make_shared<Player> (Point(200, 240), al_map_rgb(0,204,0), h1, true, 1);
   std::shared_ptr<Player> player1 = std::make_shared<Player> (Point(320, 240), 50);

   game.addPlayer(player1); game.addDrawable(player1); game.addUpdateable(player1);
   
   // start the game, close the display to end
   game.run();
   
}
