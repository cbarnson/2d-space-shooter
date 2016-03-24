/**
 * @file main.cc
 * @brief
 * 
 * @author Cody, Josh, Dawson
 * @bug none :P
 */


#include "Display.h"
#include "Simulator.h"
#include "engine.h"
#include <allegro5/allegro.h>
#include <ctime>
#include <cstdlib>

//#define FPS 60

int main() {
   srand(time(0));
   
   Display disp(800, 600);
   //int fps = 60;
   engine game(disp, 60);

   // start the game, close the display to end
   game.run();

}

