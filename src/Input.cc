#include "Input.h"
#include "Action.h"
#include "State.h"
using namespace act;
using namespace gs;

Input::Input() {
  
}

act::action Input::handleKeyDown_MENU(ALLEGRO_EVENT& ev) {
  switch (ev.keyboard.keycode) {
  case ALLEGRO_KEY_1:
    return action::PLAY_SINGLE;
  case ALLEGRO_KEY_ESCAPE:
    return action::QUIT_GAME;
  }  
  return action::NO_ACTION; // to make compiler happy
}
act::action Input::handleKeyDown_PLAY(ALLEGRO_EVENT& ev) {
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
  case ALLEGRO_KEY_PAD_0:
    return action::FIRE_PRIMARY;
  case ALLEGRO_KEY_PAD_DELETE:
    return action::FIRE_SECONDARY;
  }     
  return action::NO_ACTION; // to make compiler happy
}

act::action Input::handleKeyUp_PLAY(ALLEGRO_EVENT& ev) {
  switch (ev.keyboard.keycode) {
  case ALLEGRO_KEY_W:
    return action::MOVE_UP;
  case ALLEGRO_KEY_D:
    return action::MOVE_RIGHT;
  case ALLEGRO_KEY_S:
    return action::MOVE_DOWN;
  case ALLEGRO_KEY_A:
    return action::MOVE_LEFT;
  case ALLEGRO_KEY_PAD_0:
    return action::FIRE_PRIMARY;
  case ALLEGRO_KEY_PAD_DELETE:
    return action::FIRE_SECONDARY;
  }     
  return action::NO_ACTION; // to make compiler happy
}
