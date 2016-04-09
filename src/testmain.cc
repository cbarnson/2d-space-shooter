#include <cppunit/ui/text/TestRunner.h>
#include "TestGame.h"

int main() {
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(TestGame::suite());
	runner.run();
	return 0;
}
