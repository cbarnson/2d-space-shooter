/**
 * @file main-line.cc
 * @brief
 *
 * @author Cody Barnson
 * @bug No known bugs
 */

#include "Display.h"
#include "Trunk.h"
#include "mySimulator.h"
#include "Point.h"
#include "Line.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <list>
#include <memory>			

int main() {

   Display disp;
   mySimulator tree(disp, 30);
   int uniform_angle = rand() % 30 + 10;   
   std::shared_ptr<Trunk> root = std::make_shared<Trunk> (Point(400,500),
							  Point(400,25), 4.0, 0.5,
							  uniform_angle, 4);   
   tree.addDrawable(root);
   tree.addUpdateable(root);
   tree.run();   
}
