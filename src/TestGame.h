#ifndef TESTGAME_H
#define TESTGAME_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <memory>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Point.h"
#include "Vector.h"
#include "Updateable.h"
#include "Player.h"
#include "Font.h"
#include "Timer.h"

class TestGame: public CppUnit::TestFixture {
   
   CPPUNIT_TEST_SUITE(TestGame);
   CPPUNIT_TEST(PointConstTest);
   CPPUNIT_TEST(PlayerConstTest);
   CPPUNIT_TEST(testDefPoint);
   CPPUNIT_TEST(testPointPointAddition);
   CPPUNIT_TEST(testPointVectorAddition);
   CPPUNIT_TEST(testDefVector);
   CPPUNIT_TEST(testVectorVectorAddition);
   CPPUNIT_TEST(testVectorReflectX);
   
   //CPPUNIT_TEST(testInitAllegro);
   //CPPUNIT_TEST(testLoadFont);
   //CPPUNIT_TEST(testCreateTimer);
   
   //CPPUNIT_TEST(MissileConstTest);
   
   CPPUNIT_TEST_SUITE_END();
   
  private:
   Point *p1, *p2;
   Vector *v1, *v2;
   Player *pla;
   Font *f1;
   Timer *timer1;
   
   
  public:
   void setUp() {
      p1 = new Point(300, 200);
      p2 = new Point;
      v1 = new Vector(100, 0);
      v2 = new Vector;
      pla = new Player((*p1), al_map_rgb(255, 0,0));

      //f1 = new Font("resources/ipag.ttf", 10);
      //timer1 = new Timer(60);
   }
   
   void tearDown() {
      delete p1;
      delete p2;
      delete v1;
      delete v2;
      delete pla;
      delete f1;
      delete timer1;
   }
   
   void PointConstTest() {
      //ensure Point constructor works as intended
      CPPUNIT_ASSERT(p1->x == 300 && p1->y == 200);
   }
   
   void PlayerConstTest() {
      CPPUNIT_ASSERT(pla->centre.x == 300 && pla->centre.y == 200);
      CPPUNIT_ASSERT(pla->speed.x == 0 && pla->speed.y == 0);
   }

   void testDefPoint() {
      CPPUNIT_ASSERT(p2->x == 0.0);
   }

   void testPointPointAddition() {
      Point p = *p1 + *p2;
      CPPUNIT_ASSERT(p.x == 300);
   }
   
   void testPointVectorAddition() {
      Point p = *p2 + *v1;
      CPPUNIT_ASSERT(p.x == 100);
   }

   void testDefVector() {
      CPPUNIT_ASSERT(v2->y == 0.0);
   }

   void testVectorVectorAddition() {
      Vector v = *v1 + *v2;
      CPPUNIT_ASSERT(v.x == 100);
   }

   void testVectorReflectX() {
      v1->reflectX();
      CPPUNIT_ASSERT(v1->x = -100);
   }
/*
   void testInitAllegro() {
      al_init();
      CPPUNIT_ASSERT(al_is_system_installed());
   }
   
   void testLoadFont() {
      al_init_font_addon();
      al_init_ttf_addon();
      f1->load();
      CPPUNIT_ASSERT(f1->isLoaded());
   }

   void testCreateTimer() {
      CPPUNIT_ASSERT(!timer1->isCreated());
   }
   
   
*/
   /*
   void MissileConstTest(){
      // CPPUNIT_ASSERT(mis->in_bound()==true);
      }*/
};
#endif
  
