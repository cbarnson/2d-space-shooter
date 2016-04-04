#ifndef TESTGAME_H
#define TESTGAME_H

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../src/Point.h"
#include "Vector.h"
#include <allegro5/allegro.h>
#include "Enemy.h"
class TestGame: public CppUnit::TestFixture{
   CPPUNIT_TEST_SUITE(TestGame);
   CPPUNIT_TEST(DummyTest);
   CPPUNIT_TEST_SUITE_END();
  private:
   Enemy *en;
  public:
   void setUp(){
      en= new Enemy(Point(300,300), al_map_rgb(255, 255, 255), Vector(-50, 50));
   }
   void tearDown(){
      
   }
   void DummyTest(){
      CPPUNIT_ASSERT(1==1);
   }
};
#endif
  
