/*
 * GenericIoTest.cpp
 *
 *  Created on: 2015/07/30
 *      Author: kryozahiro
 */

#include <boost/lexical_cast.hpp>
#include "TestUtil.h"
#include "GenericIo.h"
using namespace std;
using namespace cpputil;

BOOST_AUTO_TEST_SUITE(GenericIoSuite)

BOOST_AUTO_TEST_CASE(PairIoCase) {
	const string str("(1, 2.5)");
	pair<int, double> p;

	//stream
	stringstream ss(str);
	ss >> p;
	ss.str("");
	ss << p;
	assert((p == pair<int, double>(1, 2.5)));
	assert(ss.str() == str);

	//lexical_cast
	assert((p == boost::lexical_cast<pair<int, double>>(str)));
	assert(boost::lexical_cast<string>(p) == str);
}

BOOST_AUTO_TEST_CASE(TupleIoCase) {
	const string str("(1, 2.5, a)");
	tuple<int, double, char> t;

	//stream
	stringstream ss(str);
	ss >> t;
	ss.str("");
	ss << t;
	assert((t == tuple<int, double, char>(1, 2.5, 'a')));
	assert(ss.str() == str);

	//lexical_cast
	assert((t == boost::lexical_cast<tuple<int, double, char>>(str)));
	assert(boost::lexical_cast<string>(t) == str);
}

BOOST_AUTO_TEST_CASE(ContainerIoCase) {
	const string str("[1, 2, 3]");
	vector<int> vec;

	//stream
	stringstream ss(str);
	ss >> vec;
	ss.str("");
	ss << vec;
	assert(vec == vector<int>({1, 2, 3}));
	assert(ss.str() == str);

	//lexical_cast
	assert(vec == boost::lexical_cast<vector<int>>(str));
	assert(boost::lexical_cast<string>(vec) == str);
}

BOOST_AUTO_TEST_SUITE_END()
