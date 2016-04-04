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
   act::action handleKeyDown_MENU(ALLEGRO_EVENT& ev);
   act::action handleKeyDown_PLAY(ALLEGRO_EVENT& ev);
   act::action handleKeyUp_PLAY(ALLEGRO_EVENT& ev);
};

#endif
