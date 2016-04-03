
#include "Menu.h"
#include "Sprite.h"
#include <stdexcept>

#define MENU_ANIMATION_DELAY 2

Menu::Menu(int fps) : framesPerSec(fps), timer(NULL), mAnim(0)
{
  init();
}

void Menu::init() {

  if ((timer = al_create_timer(1.0 / framesPerSec)) == NULL) 
    throw std::runtime_error("Cannot create allegro menu timer");

  ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
  al_append_path_component(path, "resources");
  al_change_directory(al_path_cstr(path, '/'));
   
  splash = std::make_shared<Sprite> ("Titlescreen.png"); 
  al_destroy_path(path);


}

void Menu::draw() {
  splash->draw_menu_anim(mAnim, 0);
}

bool Menu::animation() {
    if (!al_get_timer_started(timer)) {
      al_start_timer(timer);
    }
    if (al_get_timer_count(timer) > MENU_ANIMATION_DELAY) {
      splash->draw_menu_anim(mAnim++, 0);
      if (mAnim > 6) {
	mAnim = 0;
	return false; // animation complete, reset mAnim
      }
      al_set_timer_count(timer, 0);
    }
    else 
      splash->draw_menu_anim(mAnim, 0);    
    return true;
}
