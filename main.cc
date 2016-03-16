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
//#include "Hotkeys.h"
//#include "Player.h"
//#include "Root.h"
//#include "Point.h"
//#include "Vector.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
//#include <memory>
//#include <list>

#include <ctime>
#include <cstdlib>

int main() {
   srand(time(0));
   
   Display disp;
   int fps = 30;
   engine game(disp, fps);

   // start the game, close the display to end
   game.run();

}

