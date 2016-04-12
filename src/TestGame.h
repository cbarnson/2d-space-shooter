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
#include "Menu.h"
#include "Projectile.h"
#include "Laser.h"

class TestGame: public CppUnit::TestFixture {
   
   CPPUNIT_TEST_SUITE(TestGame);
   CPPUNIT_TEST(PointConstTest);
   CPPUNIT_TEST(testDefPoint);
   CPPUNIT_TEST(testPointPointAddition);
   CPPUNIT_TEST(testPointVectorAddition);
   CPPUNIT_TEST(testDefVector);
   CPPUNIT_TEST(testVectorVectorAddition);
   CPPUNIT_TEST(testVectorReflectX);
   
   CPPUNIT_TEST(testInitAllegro);
   CPPUNIT_TEST(testLoadFont);
   CPPUNIT_TEST(testCreateTimer);
   CPPUNIT_TEST(testTimerStarted);
   CPPUNIT_TEST(testTimerStopped);

   CPPUNIT_TEST(testPlayerPosition);
   CPPUNIT_TEST(testPlayerDead);
   CPPUNIT_TEST(testPlayerBounds);

   CPPUNIT_TEST(testLaserBounds);
   
   CPPUNIT_TEST_SUITE_END();
   
  private:
   Point *p1, *p2;
   Vector *v1, *v2;
   Font *f1;
   Timer *timer1;
   Player *player, *player2;
   Projectile *proj;
   
  public:
   void setUp() {
      p1 = new Point(300, 200);
      p2 = new Point;
      v1 = new Vector(100, 0);
      v2 = new Vector;
      
      f1 = new Font("resources/ipag.ttf", 10);
      timer1 = new Timer(60);
      
      player = new Player(Point(300, 300), al_map_rgb(0, 200, 0));
      player2 = new Player(Point(-1, 300), al_map_rgb(0, 200, 0));

      proj = new Laser(Point(900, 300), al_map_rgb(200, 0, 0), Vector(50, 0));
   }
   
   void tearDown() {
      delete p1;
      delete p2;
      delete v1;
      delete v2;
      delete f1;
      delete timer1;
      delete player;
      delete player2;
      delete proj;
   }
   
   void PointConstTest() {
      //ensure Point constructor works as intended
      CPPUNIT_ASSERT(p1->x == 300 && p1->y == 200);
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
   
   void testTimerStarted() {
      timer1->create();
      timer1->startTimer();
      CPPUNIT_ASSERT(timer1->isRunning());
   }

   void testTimerStopped() {
      timer1->create();
      timer1->startTimer();
      timer1->stopTimer();
      CPPUNIT_ASSERT(!timer1->isRunning());
   }

   void testPlayerPosition() {
      CPPUNIT_ASSERT(player->centre.x == 300);
   }

   void testPlayerDead() {
      player->hit(1);
      player->hit(1);
      player->hit(1);
      CPPUNIT_ASSERT(player->dead == true);
   }

   void testPlayerBounds() {
      player2->update(1);
      CPPUNIT_ASSERT(player2->centre.x == PLAYER_SIZE);
   }

   void testLaserBounds() {
      proj->update(1);
      CPPUNIT_ASSERT(proj->live == false);
   }



};
#endif
  
