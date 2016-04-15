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
#include <string>
#include <iostream>

int main() {
   srand(time(0));

   std::cout << "Welcome to Call of Shooty!\n=========================\n";
   std::cout << "Please enter your name: ";
   std::string name;
   std::cin >> name;
   
   Engine shooty(800, 600, 60);
   shooty.init();
   shooty.setName(name);
   shooty.run();

   return 0;

}


