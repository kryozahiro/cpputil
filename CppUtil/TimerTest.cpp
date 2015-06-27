/*
 * TimerTest.cpp
 *
 *  Created on: 2015/06/28
 *      Author: kryozahiro
 */

#include "TestUtil.h"
#include "Timer.h"
using namespace std;
using namespace cpputil;

BOOST_AUTO_TEST_SUITE(TimerSuite)

BOOST_AUTO_TEST_CASE(profileCase) {
	int elapsed = Timer::profile([](){},10);
	BOOST_CHECK_GE(elapsed, 0);
}

BOOST_AUTO_TEST_CASE(startCase) {
	Timer timer;
	timer.start();
	int t1 = timer.elapsed();
	int t2 = timer.elapsed();
	BOOST_CHECK_GE(t1, 0);
	BOOST_CHECK_GE(t2, t1);
}

BOOST_AUTO_TEST_CASE(stopCase) {
	Timer timer;
	int t1 = timer.stop();
	int t2 = timer.elapsed();
	BOOST_CHECK_GE(t1, 0);
	BOOST_CHECK_EQUAL(t2, t1);
}

BOOST_AUTO_TEST_CASE(resumeCase) {
	Timer timer;
	int t1 = timer.stop();
	timer.resume();
	int t2 = timer.elapsed();
	BOOST_CHECK_GE(t2, t1);
}

BOOST_AUTO_TEST_CASE(elapsedCase) {
	Timer timer;
	BOOST_CHECK_GE(timer.elapsed(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
