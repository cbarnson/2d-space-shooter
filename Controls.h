#ifndef CONTROLS_H
#define CONTROLS_H

#include "Updateable.h"
#include <vector>

class Controls : public Updateable {
  public:
   void updatePlayer(std::vector<bool>);

};


#endif
