#ifndef TESTGAME_H
#define TESTGAME_H

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
//#include"../src/Engine.h"
#include "../src/Point.h"
//#include "../src/Vector.h"
//#include "../src/Action.h"
//#include "../src/Background.h"
//#include "../src/Drawable.h"
#include "../src/Enemy.h"
//#include "../src/Input.h"
//#include "../src/Menu.h"
#include "../src/Updateable.h"
#include "../src/Player.h"
//#include "../src/Missile.h"
//#include "../src/Root.h"
//#include "../src/Projectile.h"
#include <allegro5/allegro.h>
#include<memory>

class TestGame: public CppUnit::TestFixture{
   CPPUNIT_TEST_SUITE(TestGame);
   CPPUNIT_TEST(DummyTest);
   CPPUNIT_TEST_SUITE_END();
  private:
   std::shared_ptr<Player> pla;
   std::shared_ptr<Enemy> en;
   Point *pt;
   //Player *pla;
   // ALLEGRO_COLOR *red;
  public:
   void setUp(){
      pt = new Point(300, 300);
      // pla = std::make_shared<Player>((*pt), al_map_rgb(255, 0, 0), 1);
      //Engine g(800, 600, 60);
      en= std::make_shared<Enemy>(Point(300,300), al_map_rgb(255, 255, 255), Vector(-50, 50));
      
   }
   void tearDown(){
      // delete g;
      delete pt;
      //  delete pla;
      en.reset();
   }
   void DummyTest(){
     
      CPPUNIT_ASSERT(1==1);
   }
};
#endif
  
