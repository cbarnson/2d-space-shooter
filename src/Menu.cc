
#include "Menu.h"
#include "Sprite.h"
#include "Timer.h"
#include "State.h"
#include <stdexcept>
#include <iostream>

const int MENU_ANIMATION_DELAY = 2;

Menu::Menu(int fps) : _fps(fps), _mAnim(0)
{
   init();
}


Menu::~Menu() {
   std::cout << "menu deleted\n";
}

void Menu::init() {

   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));
   
   _splash = std::make_shared<Sprite> ("Titlescreen.png"); 
   al_destroy_path(path);
   
   _timer = std::make_shared<Timer> (_fps);
}

void Menu::draw() {
   _splash->draw_menu_anim(_mAnim, 0);
}

// returns true if animation is in progress
// returns false when animation has completed
bool Menu::animation() {
   if (!_timer->isRunning()) {
      _timer->startTimer();
   }
   if (_timer->getCount() > MENU_ANIMATION_DELAY) {
      _splash->draw_menu_anim(_mAnim++, 0);
      if (_mAnim > 6) {
	 _mAnim = 0;
	 _timer->stopTimer();
	 _timer->resetCount();
	 return false; // animation complete
      }
      _timer->resetCount();
   }
   else 
      _splash->draw_menu_anim(_mAnim, 0);
   
   return true;
}

void Menu::handleEvent(const ALLEGRO_EVENT& event, gs::state& st) {
   if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      st = gs::state::EXIT;
      return;
   }

   if (event.type == ALLEGRO_EVENT_TIMER) {
      if (st == gs::state::LOAD) {
	 if (!animation()) {
	    st = gs::state::PLAY;
	    return;
	 }
	 al_flip_display();
      }
      else {
	 draw();
	 al_flip_display();
      }
   }

   
}

void Menu::handleKey(const ALLEGRO_KEYBOARD_STATE& kb, gs::state& st) {
   if (st == gs::state::EXIT) {
      return;
   }

   else if (al_key_down(&kb, ALLEGRO_KEY_ESCAPE)) {
      st = gs::state::EXIT;
   }
   
   else if (al_key_down(&kb, ALLEGRO_KEY_1)) {
      st = gs::state::LOAD;
   }
}
