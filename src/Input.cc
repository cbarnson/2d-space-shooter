#include "Input.h"
#include "Action.h"
#include "State.h"
using namespace act;
using namespace gs;

Input::Input() {
  
}

act::action Input::handleKeyDown(ALLEGRO_EVENT& ev, gs::state st) {
  if (st == state::PLAY) {
    switch (ev.keyboard.keycode) {
    case ALLEGRO_KEY_ESCAPE:
      return action::QUIT_GAME;
    case ALLEGRO_KEY_W:
      return action::MOVE_UP;
    case ALLEGRO_KEY_D:
      return action::MOVE_RIGHT;
    case ALLEGRO_KEY_S:
      return action::MOVE_DOWN;
    case ALLEGRO_KEY_A:
      return action::MOVE_LEFT;
    default:
      return action::NO_ACTION;
    }   
  }
  if (st == state::MENU) {
    switch (ev.keyboard.keycode) {
    case ALLEGRO_KEY_1:
      return action::PLAY_SINGLE;
    case ALLEGRO_KEY_ESCAPE:
      return action::QUIT_GAME;
    default:
      return action::NO_ACTION;
    }
  }
  return action::NO_ACTION; // to make compiler happy
}
