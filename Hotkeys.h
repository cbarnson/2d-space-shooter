/**
 * @file Hotkeys.h
 * @brief Declaration of Hotkeys class
 * @author Cody Barnson
 * @bug
 */
#ifndef HOTKEYS_H
#define HOTKEYS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>

using std::vector;

// provide key mappings for a player - 5 keys
class Hotkeys {
  public:
   vector<int> control;
   vector<bool> keys;
   
  Hotkeys(const vector<int>& v) : control(v)
   {
      for (int i = 0; i < 5; i++) {
	 keys.push_back(false);
      }
   }
   
};

#endif
