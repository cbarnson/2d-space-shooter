#ifndef INPUT_H
#define INPUT_H

#include <allegro5/allegro.h>
#include "Action.h"
#include "State.h"

using namespace act;
using namespace gs;

class Input {
  public:
   Input();
   act::action handleKeyDown(ALLEGRO_EVENT& ev, gs::state st);

};

#endif
