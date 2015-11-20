/*
 * GenericIoTest.cpp
 *
 *  Created on: 2015/07/30
 *      Author: kryozahiro
 */

#include <boost/lexical_cast.hpp>
#include "TestUtil.h"
#include "GenericIo.h"

BOOST_AUTO_TEST_SUITE(GenericIoSuite)

BOOST_AUTO_TEST_CASE(PairIoCase) {
	const std::string str("(1, 2.5)");
	std::pair<int, double> p;

	//stream read
	std::stringstream ss;
	ss << str;
	ss >> p;
	BOOST_CHECK_EQUAL(p, (std::pair<int, double>(1, 2.5)));

	//stream write
	ss.str("");
	ss << p;
	BOOST_CHECK_EQUAL(str, ss.str());

	//lexical_cast
	BOOST_CHECK_EQUAL(p, (boost::lexical_cast<std::pair<int, double>>(str)));
	BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(p), str);
}

using namespace std;

BOOST_AUTO_TEST_CASE(TupleIoCase) {
	const string str("(1, 2.5, a)");
	tuple<int, double, char> t;

	//stream read
	stringstream ss;
	ss << str;
	ss >> t;
	BOOST_CHECK_EQUAL(t, (tuple<int, double, char>(1, 2.5, 'a')));

	//stream write
	ss.str("");
	ss << t;
	BOOST_CHECK_EQUAL(str, ss.str());

	//lexical_cast
	BOOST_CHECK_EQUAL(t, (boost::lexical_cast<tuple<int, double, char>>(str)));
	BOOST_CHECK_EQUAL(boost::lexical_cast<string>(t), str);
}

using namespace cpputil;

BOOST_AUTO_TEST_CASE(ContainerIoCase) {
	const string str("[1, 2, 3]");
	vector<int> v;

	//stream read
	stringstream ss;
	ss << str;
	ss >> v;
	BOOST_CHECK_EQUAL(v, vector<int>({1, 2, 3}));

	//stream write
	ss.str("");
	ss << v;
	BOOST_CHECK_EQUAL(str, ss.str());

	//lexical_cast
	BOOST_CHECK_EQUAL(v, boost::lexical_cast<vector<int>>(str));
	BOOST_CHECK_EQUAL(boost::lexical_cast<string>(v), str);
}

BOOST_AUTO_TEST_SUITE_END()
