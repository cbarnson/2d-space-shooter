#ifndef CONTROLS_H
#define CONTROLS_H

//#include <vector>

class Controls {
  public:
   virtual void updatePlayer() = 0;
   virtual void set(int) = 0;
   virtual void reset(int) = 0;
};

#endif
