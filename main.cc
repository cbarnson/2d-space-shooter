/**
 * @file main.cc
 * @brief
 * 
 * @author
 * @bug
 */

#include "Display.h"
#include "Simulator.h"
#include "engine.h"
#include "Hotkeys.h"
#include "Player.h"
#include "Root.h"
#include "Point.h"
#include "Vector.h"

#include <memory>
#include <list>

int main() {   
   Display disp;
   int fps = 30;
   engine game(disp, fps); 

   // call either single_player() or multi_player() before run() to select mode
   // this sets the root to initialize the game with either 1 or 2 players
   
   //game.single_player();
   game.multi_player();
      
   // start the game, close the display to end
   game.run();
   
}

