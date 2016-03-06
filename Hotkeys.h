/**
 * @file Hotkeys.h
 * @brief
 * @author Cody Barnson
 * @bug
 */
#ifndef HOTKEYS_H
#define HOTKEYS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>


// provide key mappings for a player
class Hotkeys {
   // 5 keys
   
  public:
   //std::vector<bool> keys {false, false, false, false, false};   
   std::vector<int> control;
   std::vector<bool> keys;
   
  Hotkeys(const std::vector<int>& v) : control(v)
   {
      for (int i = 0; i < 5; i++) {
	 keys.push_back(false);
      }
   }
   /*
   // called when ALLEGRO_EVENT_KEY_UP
   void setPlayer(int code) {
      for (int i = 0; i < 5; i++) {
	 if (code == control[i])
	    keys[i] = true;
      }
   }

   // called when ALLEGRO_EVENT_KEY_DOWN
   void resetPlayer(int code) {
      for (int i = 0; i < 5; i++) {
	 if (code == control[i])
	     keys[i] = false;
      }
      }
   */
   
};

#endif
