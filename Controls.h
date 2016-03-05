#ifndef CONTROLS_H
#define CONTROLS_H

//#include "Updateable.h"
#include <vector>

class Controls {
  public:
   virtual void updatePlayer(std::vector<bool>&, double) = 0;
};

#endif
