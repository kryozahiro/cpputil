/*
 * CreatableTest.cpp
 *
 *  Created on: 2015/07/16
 *      Author: kryozahiro
 */

#include "Creatable.h"
#include "TestUtil.h"
using namespace std;
using namespace cpputil;

BOOST_AUTO_TEST_SUITE(CreatableSuite)

class A : public Creatable<A> {
public:
	A() : x(0) {};
	virtual ~A() = default;
	CPPUTIL_CREATABLE;
	int x;
};

class B : public A {
public:
	B() {
		++x;
	};
	virtual ~B() = default;
	CPPUTIL_CREATABLE;
};

class P : public Creatable<P, int> {
public:
	P(int y = 0) : y(y) {};
	virtual ~P() = default;
	P* create(int y) {
		return new P(y);
	}
	int y;
};

class Q : public P {
public:
	Q(int y2 = 1) {
		y = y2;
	};
	virtual ~Q() = default;
	P* create(int y) {
		return new Q(y);
	}
};

BOOST_AUTO_TEST_CASE(CreatableCase) {
	A a1;
	B b1;
	std::shared_ptr<A> a2(a1.create());
	std::shared_ptr<A> b2(b1.create());
	BOOST_CHECK_EQUAL(a2->x, 0);
	BOOST_CHECK_EQUAL(b2->x, 1);

	P p1;
	Q q1;
	std::shared_ptr<P> p2(p1.create(2));
	std::shared_ptr<P> q2(q1.create(3));
	BOOST_CHECK_EQUAL(p2->y, 2);
	BOOST_CHECK_EQUAL(q2->y, 3);
}

BOOST_AUTO_TEST_SUITE_END()
