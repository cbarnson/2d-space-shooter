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
#include "Player.h"
#include "Point.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>
#include <list>
#include <string>
#include <iostream>
#include <cstdlib>

int main() {   
   Display disp;   
   gameSimulator game(disp, 30); // 2nd param is fps

   // sets up the player, provide parameters: start point on the display, and size of player
   std::shared_ptr<Player> p = std::make_shared<Player> (Point(320, 240), 50);
   game.addPlayer(p); game.addDrawable(p);

   // start the game, close the display to end
   game.run();
   
}
