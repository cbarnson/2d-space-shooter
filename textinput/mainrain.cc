//////////////////////////////////////////////////////////////////////////////////
/* Josh Mohan
/ CPSC 2720- Assignment 1
/ Feb 23, 2016
/ MAINRAIN: Main file that runs the "rain" simulation
/
/
///////////////////////////////////////////////////////////////////////////////*/
#include "rainsimulator.h"
#include<memory>
#include<allegro5/allegro.h>

int main(void) {
   // shared_ptr<Triangle> tr = make_shared<Triangle>(30, 100);//1st arg=speed 2nd=size
   

      
   
	Display disp;  // create a 800x600 window
	rainsimulator simul(disp, 60);// 1st arg = disp, 2nd arg = fps

	   shared_ptr<Triangle> tr = make_shared<Triangle>(100, 30);//1st arg= speed(in pixels)
	   simul.addDrawable(tr);
	   simul.addMovable(tr); 
       
	simul.run();
}
