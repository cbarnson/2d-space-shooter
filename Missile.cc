#include "Missile.h"

void Missile::load_assets() {
   centre = centre + speed * 0.1; // so it doesn't hit its own projectile

   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));
   //laser = make_shared<Sprite> ("redLaserRay.png");
   mvec.push_back(make_shared<Sprite> ("m1.png"));
   mvec.push_back(make_shared<Sprite> ("m2.png"));
   mvec.push_back(make_shared<Sprite> ("m3.png"));
   mvec.push_back(make_shared<Sprite> ("m4.png"));
   mvec.push_back(make_shared<Sprite> ("m5.png"));
   mvec.push_back(make_shared<Sprite> ("m6.png"));
   mvec.push_back(make_shared<Sprite> ("m7.png"));
   mvec.push_back(make_shared<Sprite> ("m8.png"));
   
   al_destroy_path(path);
}

void Missile::update(double dt) {
   centre = centre + speed * dt;
   if (!in_bound())
      live = false;
}

void Missile::draw() {
   mvec[mAnim++]->draw_rotated(centre, color, 0);
   if (mAnim > 7)
      mAnim = 0; // go through vector again
}

bool Missile::in_bound() {
   if ((centre.x > 800) ||
       (centre.x < 0) ||
       (centre.y > 600) ||
       (centre.y < 0))
      return false;
   return true;
}
