/**
 * @file main.cc
 * @brief
 * 
 * @author Cody, Josh, Dawson
 * @bug none :P
 */


#include "Engine.h"
#include <allegro5/allegro.h>
#include <ctime>
#include <cstdlib>

int main() {
   srand(time(0));

   Engine shooty(800, 600, 60);
   shooty.init();
   shooty.run();

   return 0;

}

