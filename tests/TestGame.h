#ifndef TESTGAME_H
#define TESTGAME_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

//#include "Vector.h"
#include "Point.h"

class TestGame : public CppUnit::TestFixture {

   CPPUNIT_TEST_SUITE(TestGame);
   CPPUNIT_TEST(testPoint);
   CPPUNIT_TEST(DummyTest);
   CPPUNIT_TEST_SUITE_END();
   
  private:
   Point *pt;


  public:
   void setUp() {
      pt = new Point(0, 0);
   }
   void tearDown() {
      delete pt;
   }

   void testPoint() {
      CPPUNIT_ASSERT(pt->x == 0);
   }
   
   void DummyTest() {     
      CPPUNIT_ASSERT(1 == 1);
   }
};
#endif
  
