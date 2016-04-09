#ifndef TESTGAME_H
#define TESTGAME_H

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
//#include"../src/Engine.h"
#include "Point.h"
//#include "../src/Vector.h"
//#include "../src/Action.h"
//#include "../src/Background.h"
//#include "../src/Drawable.h"
#include "Enemy.h"
//#include "../src/Input.h"
//#include "../src/Menu.h"
#include "Updateable.h"
#include "Player.h"
#include "Missile.h"
//#include "../src/Root.h"
//#include "../src/Projectile.h"
#include <allegro5/allegro.h>
#include<memory>

class TestGame: public CppUnit::TestFixture{
   CPPUNIT_TEST_SUITE(TestGame);
   CPPUNIT_TEST(DummyTest);
   CPPUNIT_TEST(PointConstTest);
   CPPUNIT_TEST(PlayerConstTest);
   CPPUNIT_TEST(MissileConstTest);
   CPPUNIT_TEST_SUITE_END();
  private:
   // std::shared_ptr<Player> pla;
   // Enemy *en;
   Point *pt;
   Player *pla;
   Missile *mis;
   // ALLEGRO_COLOR *red;
  public:
   void setUp(){
      pt = new Point(300, 200);
      pla= new Player((*pt), al_map_rgb(255, 0,0));
      // mis= new Missile((*pt), al_map_rgb(255, 255, 255), Vector(50, 50));
      //  en= new Enemy(Point(300,300), al_map_rgb(255, 255, 255), Vector(-50, 50));
      
   }
   void tearDown(){
      // delete g;
      delete pt;
      delete pla;
      // delete en;
      //delete mis;
      // en.reset();
   }
   void DummyTest(){
      //CPPUNIT_ASSERT((*en).getProjSpeed().x==-500);     
      CPPUNIT_ASSERT(1==1);
   }
   void PointConstTest(){
      //ensure Point constructor works as intended
      CPPUNIT_ASSERT(pt->x==300&&pt->y==200);
   }
   void PlayerConstTest(){
      //spawn location is set to 300, 200
      CPPUNIT_ASSERT(pla->centre.x==300&&pla->centre.y==200);
      //assert initial velocity is 0
      CPPUNIT_ASSERT(pla->speed.x==0&&pla->speed.y==0);
   }
   void MissileConstTest(){
      // CPPUNIT_ASSERT(mis->in_bound()==true);
   }
};
#endif
  
