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


// provide key mappings for a player - 5 keys
class Hotkeys {
  public:
   std::vector<int> control;
   std::vector<bool> keys;
   
  Hotkeys(const std::vector<int>& v) : control(v)
   {
      for (int i = 0; i < 5; i++) {
	 keys.push_back(false);
      }
   }
   
};

#endif
