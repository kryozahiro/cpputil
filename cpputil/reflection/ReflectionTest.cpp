/*
 * ReflectionTest.cpp
 *
 *  Created on: 2015/11/05
 *      Author: kryozahiro
 */

#include "Reflection.h"
#include "../TestUtil.h"
using namespace std;
using namespace cpputil;

BOOST_AUTO_TEST_SUITE(ReflectionSuite)

int globalVariable = 0;
int globalFunction(char c) {
	return ++globalVariable;
}

class A {
public:
	A(int x) : x(x) {};
	int f(char c) {
		return ++x;
	}
	int x = 0;
};

CPPUTIL_AT_START(A) {
	//global
	shared_ptr<Scope> global = Reflection::get_mutable_instance().getGlobal();
	global->addVariable("globalVariable", &globalVariable);
	global->addFunction("globalFunction", std::function<int(char)>(&globalFunction));

	//class
	shared_ptr<Scope> a = global->addScope(Scope::CLASS, "A");
	a->addFunction("A", std::function<A*()>([](){
		return new A(1);
	}));
	a->addFunction("x", std::function<int&(A&)>(&A::x));
	a->addFunction("f", std::function<int(A&, char)>(&A::f));
}

BOOST_AUTO_TEST_CASE(ReflectionCase) {
	//global
	shared_ptr<Scope> global = Reflection::get_mutable_instance().getGlobal();
	int& gv = global->getVariable<int>("globalVariable");
	auto gf = global->getFunction<int(char)>("globalFunction");
	BOOST_CHECK_EQUAL(global->getType(), Scope::NAMESPACE);
	BOOST_CHECK_EQUAL(gv, 0);
	BOOST_CHECK_EQUAL(gf('a'), 1);
	BOOST_CHECK_EQUAL(gv, 1);
	++gv;
	BOOST_CHECK_EQUAL(gv, 2);

	//class
	shared_ptr<Scope> a = global->getScope("A");
	auto ac = a->getFunction<A*()>("A");
	auto ax = a->getFunction<int&(A&)>("x");
	auto af = a->getFunction<int(A&, char)>("f");
	BOOST_CHECK_EQUAL(a->getType(), Scope::CLASS);
	A& ai = *ac();
	BOOST_CHECK_EQUAL(ax(ai), 1);
	BOOST_CHECK_EQUAL(af(ai, 'a'), 2);
	BOOST_CHECK_EQUAL(ax(ai), 2);
	++ax(ai);
	BOOST_CHECK_EQUAL(ax(ai), 3);
}

BOOST_AUTO_TEST_SUITE_END()
