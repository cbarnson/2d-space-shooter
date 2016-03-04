/**
 * @file main.cc
 * @brief
 * 
 * @author Cody Barnson
 * @bug
 */

//#include "Display.h"
//#include "gameSimulator.h"
//#include "Message.h"
#include "Display.h"
#include "Simulator.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>
#include <list>
#include <string>
#include <iostream>
#include <cstdlib>

int main() {
   
   Display disp;
   gameSimulator game(disp, 30);
   //shared_ptr<Message> m = make_shared<Message> ("Hello World", 24);
   //game.addDrawable(m);
   
   game.run();
   
}
