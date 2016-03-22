/**
 * @file engine.cc
 * @brief Implementation of engine class- runs main menu, game mode selection
 * @author
 */

#include "engine.h"

engine::~engine() {
   // al_destroy_font(menuFont);
   // al_destroy_font(modeFont);
   // al_destroy_font(subMenuFont);
   al_destroy_timer(menuTimer);
}


void engine::load_assets() {
   menuTimer = al_create_timer(1.0/30.0);
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));
   menuPng = make_shared<Sprite>("Titlescreen.png"); 
   /*
   menuFont = al_load_font("DavidCLM-Medium.ttf", 52, 0);
   subMenuFont = al_load_font("DavidCLM-Medium.ttf", 48, 0);
   modeFont = al_load_font("ipag.ttf", 32, 0);   

   menu = make_shared<Sprite> ("space.png");
   */
   //cout << "assets loaded\n";

   al_destroy_path(path);
}


void engine::reset_game() {
   root.clear();
   //cout << "game reset\n";
}


bool engine::is_game_over() {
   for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	++it) {
      if ((*it)->is_game_over())
	 return true;      
   }
   return false;
}

   
void engine::menuMessage() {
   menuAnim();
 
   // menuAnim->drawMenuAnim(dAnim, 0);
   /*
     al_draw_text(menuFont, al_map_rgb(0, 102, 204), 0.5 * windowWidth,
     0.5 * windowHeight, ALLEGRO_ALIGN_CENTRE,
     "Call of Shooty:");
     al_draw_text(subMenuFont, al_map_rgb(0, 204, 204), 0.5 * windowWidth,
     0.58 * windowHeight, ALLEGRO_ALIGN_CENTRE,
     "Worlds at War");
     al_draw_text(modeFont, al_map_rgb(0, 204, 102), 0.5 * windowWidth,
     0.7 * windowHeight, ALLEGRO_ALIGN_CENTRE,
     "[ 1 ] SINGLE PLAYER   [ 2 ] MULTI PLAYER");
   */
   al_flip_display();
}

bool engine::gameReady(){
   std::cout<<mAnim<<std::endl;
   if(mAnim>6)
      return true; 
   return false;
}
void engine::menuAnim(){
   if(!root.empty()){
      if(!al_get_timer_started(menuTimer))
	 al_start_timer(menuTimer);
      if((al_get_timer_count((menuTimer))< 10))
      {
	 menuPng->draw_menu_anim(mAnim, 0);
	 mAnim++;
	 al_set_timer_count(menuTimer, 0);
      }
   }
   else
      menuPng->draw_menu_anim(mAnim, 0);
}
   
   void engine::single_player() {
      //cout << "creating single from engine\n";
      root.push_back(make_shared<Single> (game_fps));
      //cout << "created single from engine\n";
   }

   
   void engine::multi_player() {
      //root.push_back(make_shared<Versus> (game_fps));
   }


void engine::getInput(const ALLEGRO_EVENT& inputEvent) {
   for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	++it) {
      //cout << "in engine looking for input\n";
      (*it)->input(inputEvent);
   }
}

void engine::updateRoot(double dt) {
   for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	++it) {
      (*it)->update(dt);
   }
   
}


void engine::drawRoot() {
   //cout << "in engine.cc drawRoot pre-call\n";
   for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	++it) {
      (*it)->draw();
   }
   //cout << "in engine.cc drawRoot post-call\n";   
}
