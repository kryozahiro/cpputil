/*
 * MathUtilTest.cpp
 *
 *  Created on: 2015/06/28
 *      Author: kryozahiro
 */

#include "TestUtil.h"
#include "GenericIo.h"
#include "MathUtil.h"
using namespace std;
using namespace cpputil;

BOOST_AUTO_TEST_SUITE(MathUtilSuite)

//----------------------------------------
// 定数
//----------------------------------------

BOOST_AUTO_TEST_CASE(piCase) {
	BOOST_CHECK_CLOSE(pi<double>(), 3.141592, 0.0001);
}

//----------------------------------------
// スケーリング
//----------------------------------------

//----------------------------------------
// 角度
//----------------------------------------

BOOST_AUTO_TEST_CASE(toRadianCase) {
	BOOST_CHECK_CLOSE(toRadian(180.0), pi<double>(), 0.0001);
}

BOOST_AUTO_TEST_CASE(toDegreeCase) {
	BOOST_CHECK_CLOSE(toDegree(pi<double>()), 180.0, 0.0001);
}

BOOST_AUTO_TEST_CASE(normalizeCase) {
	BOOST_CHECK_EQUAL(normalize(0.0), 0.0);

	BOOST_CHECK_CLOSE(normalize(0.5 * pi<double>()),	0.5 * pi<double>(), 0.0001);
	BOOST_CHECK_CLOSE(normalize(pi<double>()),			pi<double>(), 0.0001);
	BOOST_CHECK_CLOSE(normalize(1.5 * pi<double>()),	-0.5 * pi<double>(), 0.0001);
	BOOST_CHECK_CLOSE(normalize(2 * pi<double>()),		0.0, 0.0001);
	BOOST_CHECK_CLOSE(normalize(2.5 * pi<double>()),	0.5 * pi<double>(), 0.0001);

	BOOST_CHECK_CLOSE(normalize(-0.5 * pi<double>()),	-0.5 * pi<double>(), 0.0001);
	BOOST_CHECK_CLOSE(normalize(-pi<double>()),			pi<double>(), 0.0001);
	BOOST_CHECK_CLOSE(normalize(-1.5 * pi<double>()),	0.5 * pi<double>(), 0.0001);
	BOOST_CHECK_CLOSE(normalize(-2 * pi<double>()),		0.0, 0.0001);
	BOOST_CHECK_CLOSE(normalize(-2.5 * pi<double>()),	-0.5 * pi<double>(), 0.0001);
}

BOOST_AUTO_TEST_CASE(rotateCase) {
	BOOST_CHECK_EQUAL(rotate(0.0, 0.0), 0.0);
	BOOST_CHECK_CLOSE(rotate(0.5 * pi<double>(), 0.5 * pi<double>()), pi<double>(), 0.0001);
	BOOST_CHECK_EQUAL(rotate(0.5 * pi<double>(), -0.5 * pi<double>()), 0.0);
}

//----------------------------------------
// 複素数
//----------------------------------------

BOOST_AUTO_TEST_CASE(toComplexCase) {
	BOOST_CHECK_EQUAL(toComplex<double>(pair<double, float>(1.5, 2.5)), complex<double>(1.5, 2.5));
}

BOOST_AUTO_TEST_CASE(toPairCase) {
	auto test = toPair<double, float>(complex<double>(1.5, 2.5));
	auto reference = pair<double, float>(1.5, 2.5);
	BOOST_CHECK_EQUAL(test, reference);
}

BOOST_AUTO_TEST_CASE(normalizeTestComplex) {
	BOOST_CHECK_CLOSE(abs(normalize(complex<double>(1.5, 2.5))), 1.0, 0.0001);

	auto test = normalize(complex<double>(3.0, 4.0));
	auto reference = complex<double>(3.0 / 5.0, 4.0 / 5.0);
	BOOST_CHECK_CLOSE(abs(test - reference), 0.0, 0.0001);
}

//----------------------------------------
// ノルムと距離
//----------------------------------------

//----------------------------------------
// アフィン変換
//----------------------------------------

BOOST_AUTO_TEST_CASE(translateCase) {
	CPPUTIL_CHECK_CLOSE_COMPLEX(translate(complex<double>(1.2, 2.3), complex<double>(3.4, 4.5)), complex<double>(4.6, 6.8), 0.0001);
}

BOOST_AUTO_TEST_CASE(rotateTestAffine) {
	CPPUTIL_CHECK_CLOSE_COMPLEX(rotate(complex<double>(1.0, 0.0), pi<double>()/4.0), complex<double>(1.0/sqrt(2.0), 1.0/sqrt(2.0)), 0.0001);
	CPPUTIL_CHECK_CLOSE_COMPLEX(rotate(complex<double>(1.0, 0.0), -pi<double>()/4.0), complex<double>(1.0/sqrt(2.0), -1.0/sqrt(2.0)), 0.0001);
	CPPUTIL_CHECK_CLOSE_COMPLEX(rotate(complex<double>(1.0/sqrt(2.0), -1.0/sqrt(2.0)), pi<double>()/2.0), complex<double>(1.0/sqrt(2.0), 1.0/sqrt(2.0)), 0.0001);
}

BOOST_AUTO_TEST_CASE(scaleCase) {
	CPPUTIL_CHECK_CLOSE_COMPLEX(scale(complex<double>(2.0, 3.0), complex<double>(4.2, 5.2)), complex<double>(8.4, 15.6), 0.0001);
}

BOOST_AUTO_TEST_CASE(transformCase) {
	CPPUTIL_CHECK_CLOSE_COMPLEX(transform(complex<double>(0.5, 0.0), complex<double>(0.0, 1.0), pi<double>()/4.0, complex<double>(2.0, 2.0)), complex<double>(1.0/sqrt(2.0), 1.0 + 1.0/sqrt(2.0)), 0.0001);
}

BOOST_AUTO_TEST_SUITE(Transformation)
BOOST_AUTO_TEST_CASE(TransformationCase) {
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
