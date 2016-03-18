/**
 * @file engine.cc
 * @brief
 * @author
 */

#include "engine.h"

engine::~engine() {
   al_destroy_font(menuFont);
   al_destroy_font(modeFont);
   //delete menu;
}


void engine::load_assets() {
   cout << "loading assets\n";
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));
   menuFont = al_load_font("DavidCLM-Medium.ttf", 48, 0);
   modeFont = al_load_font("ipag.ttf", 32, 0);   

   //menu = new Sprite("space.png");
   menu = make_shared<Sprite> ("space.png");

   cout << "assets loaded\n";
   al_destroy_path(path);
}


void engine::reset_game() {
   root.clear();
   cout << "game reset\n";
}


bool engine::is_game_over() {
   for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	++it) {
      //return ((*it)->is_game_over()) ? true : false;
      if ((*it)->is_game_over())
	 return true;      
   }
   return false;
}

   
void engine::menuMessage() {
   menu->drawToOrigin();
   al_draw_text(menuFont, al_map_rgb(0, 204, 204), 0.5 * windowWidth,
		0.5 * windowHeight, ALLEGRO_ALIGN_CENTRE,
		"ASSEROIDS");
   al_draw_text(modeFont, al_map_rgb(0, 204, 102), 0.5 * windowWidth,
		0.7 * windowHeight, ALLEGRO_ALIGN_CENTRE,
		"[ 1 ] SINGLE PLAYER   [ 2 ] MULTI PLAYER");
   al_flip_display();
}

   

void engine::single_player() {
   cout << "creating single from engine\n";
   root.push_back(make_shared<Single> (game_fps));
   cout << "created single from engine\n";
}

   
void engine::multi_player() {
   root.push_back(make_shared<Versus> (game_fps));
}

   
void engine::setRoot(int code) {
   for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	++it) {
      (*it)->set(code);
   }
}


void engine::resetRoot(int code) {
   for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	++it) {
      (*it)->reset(code);
   }
}


void engine::collisionRoot() {
   for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	++it) {
      (*it)->collision();
      (*it)->clean();
   }
}


void engine::controlRoot() {
   for (list< shared_ptr<Root> >::iterator it = root.begin(); it != root.end();
	++it) {
      (*it)->updatePlayer();
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
