/**
 * @file Background.cc
 * @brief Implementation of Background class- draws a moving background image
 *
 * @author
 * @bug
 */
#include "Background.h"

void Background::load_assets(){
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));
   bg = make_shared<Sprite> (filename);
   al_destroy_path(path);  
     
}
void Background::draw(){
   bg->draw(centre, 0);     
}
void Background::update(double dt)
{
   centre=centre+ speed*dt;
   if(centre.x<=0)
   {
      centre.x=origin.x;
      centre.y=origin.y;
   }
}
