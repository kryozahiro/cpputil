/*
 * EnumUtilTest.cpp
 *
 *  Created on: 2015/07/08
 *      Author: kryozahiro
 */

#include "EnumUtil.h"

#include <boost/lexical_cast.hpp>

#include "TestUtil.h"
using namespace std;
using namespace cpputil;

BOOST_AUTO_TEST_SUITE(EnumUtilSuite)

enum Unscoped {
	FIRST,
	SECOND = 3,
	THIRD,
};
enum class Scoped {
	ALPHA,
	BETA = 3,
	GAMMA,
};
CPPUTIL_ENUM(CppUtil,
	RED,
	GREEN = 3,
	BLUE,
);
class CppUtilHolder {
	CPPUTIL_ENUM(CppUtilHolded,ZERO  ,ONE,   TWO  ,   THREE,FOUR=4  ,FIVE=5,   SIX=6  ,   SEVEN=7,EIGHT  =   8,  NINE   =  9   );
};

BOOST_AUTO_TEST_CASE(CppUtilEnumCase) {
	//enumとしての基本機能
	{	//Unscoped enum
		Unscoped a = SECOND;
		Unscoped b = a;
		Unscoped c; c = b;
		Unscoped d = static_cast<Unscoped>(4);
		int x = d;
		int y = THIRD;
		BOOST_CHECK(SECOND == a and a == b and b == c and c == SECOND);
		BOOST_CHECK(d == x and x == y);
		switch (a) { default: break; }
		switch (THIRD) { case THIRD: break; default: break; }
	}
	{	//Scoped enum
		Scoped a = Scoped::BETA;
		Scoped b = a;
		Scoped c; c = b;
		Scoped d = static_cast<Scoped>(4);
		int x = static_cast<int>(d);
		int y = static_cast<int>(Scoped::GAMMA);
		BOOST_CHECK(Scoped::BETA == a and a == b and b == c and c == Scoped::BETA);
		BOOST_CHECK(static_cast<int>(d) == x and x == y);
		switch (a) { default: break; }
		switch (Scoped::GAMMA) { case Scoped::GAMMA: break; default: break; }
	}
	{	//CPPUTIL_ENUM
		CppUtil a = CppUtil::GREEN;
		CppUtil b = a;
		CppUtil c; c = b;
		CppUtil d = static_cast<CppUtil>(4);
		int x = d;
		int y = CppUtil::BLUE;
		BOOST_CHECK(CppUtil::GREEN == a and a == b and b == c and c == CppUtil::GREEN);
		BOOST_CHECK(d == x and x == y);
		switch (a) { default: break; }
		switch (CppUtil::BLUE) { case CppUtil::BLUE: break; default: break; }
	}

	//比較演算子
	BOOST_CHECK(CppUtil::RED == CppUtil::RED and !(CppUtil::RED == CppUtil::GREEN));
	BOOST_CHECK(!(CppUtil::RED != CppUtil::RED) and CppUtil::RED != CppUtil::GREEN);
	BOOST_CHECK(CppUtil::RED <= CppUtil::RED and CppUtil::RED <= CppUtil::GREEN);
	BOOST_CHECK(!(CppUtil::RED < CppUtil::RED) and CppUtil::RED < CppUtil::GREEN);
	BOOST_CHECK(CppUtil::BLUE >= CppUtil::BLUE and CppUtil::BLUE >= CppUtil::GREEN);
	BOOST_CHECK(!(CppUtil::BLUE > CppUtil::BLUE) and CppUtil::BLUE > CppUtil::GREEN);
	CppUtil green = CppUtil::GREEN;
	BOOST_CHECK(CppUtil::RED < green and green < CppUtil::BLUE);

	//文字列変換
	BOOST_CHECK_EQUAL(CppUtil("BLUE"), CppUtil::BLUE);
	BOOST_CHECK_EQUAL(to_string(CppUtil::BLUE), "4");
	BOOST_CHECK_EQUAL(to_string(CppUtil(CppUtil::BLUE)), "BLUE");
	CppUtil blue = CppUtil::BLUE;
	BOOST_CHECK_EQUAL(to_string(blue), "BLUE");

	//入出力演算子
	BOOST_CHECK_EQUAL(boost::lexical_cast<CppUtil>("BLUE"), CppUtil::BLUE);
	BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(CppUtil(CppUtil::BLUE)), "BLUE");
}

BOOST_AUTO_TEST_SUITE_END()
