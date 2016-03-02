#include <iostream>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

class InvalidTimeExcept {
};  // an empty class, just for exceptions


class Time24 {
private:
	int hour, min;
public:
	Time24(int h=0, int m=0) {
		hour = h; min = m;
	}

	// a.minutes2(b) = nr of minutes elapsed from time a to time b
	// if b is earlier than a, then b is considered next day.
	int minutes2(Time24) const;
};

int Time24::minutes2(Time24 to) const {
	return to.hour*60+to.min - hour*60 - min;
}


class TestTime24_fixture : public CppUnit::TestFixture {
public:
CPPUNIT_TEST_SUITE(TestTime24_fixture);
CPPUNIT_TEST(testSameDay);
CPPUNIT_TEST(testNextDay);
CPPUNIT_TEST_EXCEPTION(testInvalidInstance, InvalidTimeExcept);
CPPUNIT_TEST_SUITE_END();

private:
  Time24 *t1, *t2;

public:

void setUp() {
  t1 = new Time24;
  t2 = new Time24(1, 10);
}

void tearDown() {
  delete t1;  delete t2;
}

	// a test function
	void testSameDay() {
		CPPUNIT_ASSERT(t1->minutes2(*t2) == 70);
	}

  void testNextDay() {
    CPPUNIT_ASSERT(t2->minutes2(*t1) == 23*60-10);
  }

void testInvalidInstance() {
Time24(25, 0);
}
};

int main() {
   CppUnit::TextUi::TestRunner runner;
   runner.addTest(TestTime24_fixture::suite());
   runner.run();
 
  return 0;
}
