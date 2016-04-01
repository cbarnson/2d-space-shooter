/**
 * @file engine.cc
 * @brief Implementation of engine class- runs main menu, game mode selection
 * @author
 */

#include "engine.h"

engine::~engine() {
   al_destroy_timer(menuTimer);
   root.reset();
   menuPng.reset();
}

void engine::load_assets() {
   mAnim = 0;
   menuTimer = al_create_timer(1.0 / game_fps);
   
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));
   
   menuPng = make_shared<Sprite>("Titlescreen.png"); 
   al_destroy_path(path);
}

void engine::reset_game() {
   root.reset();
}

bool engine::is_game_over() {
   if (root) 
      if (root->is_game_over())
	 return true;   
   return false;
}

   
void engine::menuMessage() {
   menuAnim(); 
   al_flip_display();
}

bool engine::gameReady() {
   if(mAnim > 6) {
      mAnim = 0;
      return true;
   }
   return false;
}

void engine::menuAnim() {
   if (root) {
      if(!al_get_timer_started(menuTimer))
	 al_start_timer(menuTimer);
      
      if (al_get_timer_count(menuTimer) > 2) {
	 menuPng->draw_menu_anim(mAnim, 0); mAnim++;
	 al_set_timer_count(menuTimer, 0);
      }
      else 
	 menuPng->draw_menu_anim(mAnim, 0);
   }
   else
      menuPng->draw_menu_anim(mAnim, 0);
}
   
void engine::single_player() {
   root = make_shared<Single> (game_fps, windowWidth, windowHeight);
}

   
void engine::multi_player() {
   //root.push_back(make_shared<Versus> (game_fps));
}


void engine::getInput(const ALLEGRO_EVENT& inputEvent) {
   if (root)
      root->input(inputEvent);
}

void engine::updateRoot(double dt) {
   if (root)
      root->update(dt);
}


void engine::drawRoot() {
   if (root)
      root->draw();
}
