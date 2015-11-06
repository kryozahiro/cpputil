/*
 * TestUtil.h
 *
 *  Created on: 2015/06/28
 *      Author: kryozahiro
 */

#ifndef CPPUTIL_TESTUTIL_H_
#define CPPUTIL_TESTUTIL_H_

#include <boost/test/unit_test.hpp>

//! std::complexのテスト
#define CPPUTIL_CHECK_CLOSE_COMPLEX(left, right, tolerance)\
	BOOST_CHECK_CLOSE((left).real(), (right).real(), tolerance);\
	BOOST_CHECK_CLOSE((left).imag(), (right).imag(), tolerance);

#endif /* CPPUTIL_TESTUTIL_H_ */
