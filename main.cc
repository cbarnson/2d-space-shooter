/**
 * @file main.cc
 * @brief
 * 
 * @author
 * @bug
 */

#include "Display.h"
#include "Simulator.h"
#include "gameSimulator.h"
#include "Hotkeys.h"
#include "Player.h"
#include "Point.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>
#include <list>
#include <string>
#include <iostream>
#include <cstdlib>

int main() {   
   Display disp;   
   gameSimulator game(disp, 30); // 2nd param is fps 

   // hotkeys player 1
   std::vector<int> h1;
   h1.push_back(ALLEGRO_KEY_UP);
   h1.push_back(ALLEGRO_KEY_DOWN);
   h1.push_back(ALLEGRO_KEY_RIGHT);
   h1.push_back(ALLEGRO_KEY_LEFT);
   h1.push_back(ALLEGRO_KEY_PAD_0);
   std::shared_ptr<Hotkeys> H1 = std::make_shared<Hotkeys> (h1);
   
   // hotkeys player 2
   std::vector<int> h2;
   h2.push_back(ALLEGRO_KEY_W);
   h2.push_back(ALLEGRO_KEY_S);
   h2.push_back(ALLEGRO_KEY_D);
   h2.push_back(ALLEGRO_KEY_A);
   h2.push_back(ALLEGRO_KEY_SPACE);
   std::shared_ptr<Hotkeys> H2 = std::make_shared<Hotkeys> (h2);
   
   // sets up the player, provide parameters: start point on the display, and size of player
   std::shared_ptr<Player> player1 =
      std::make_shared<Player> (Point(200, 240), 50, al_map_rgb(0,204,0), H1);
   game.addPlayer(player1); game.addDrawable(player1); game.addUpdateable(player1);

   std::shared_ptr<Player> player2 =
      std::make_shared<Player> (Point(400, 240), -50, al_map_rgb(255,0,0), H2);
   game.addPlayer(player2); game.addDrawable(player2); game.addUpdateable(player2);
   
   // start the game, close the display to end
   game.run();
   
}
