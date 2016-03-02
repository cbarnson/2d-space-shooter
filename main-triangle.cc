/**
 * @file main-triangle.cc
 * @brief
 *
 * @author Cody Barnson
 * @bug no known bugs
 */

#include "Display.h"
#include "mySimulator.h"
#include "Triangle.h"
#include <ctime>
#include <cstdlib>
#include <list>
#include <memory>

int main(void) {
   srand(time(NULL));
   Display disp;  
   mySimulator rain(disp, 30);
   int number = 40; 

   for (int i = 0; i < number; i++) {
      std::shared_ptr<Triangle> tp = std::make_shared<Triangle> (disp.getW(), disp.getH());
      rain.addDrawable(tp);
      rain.addUpdateable(tp);      
   }
   rain.run();
}
