/*
 * Reflection.cpp
 *
 *  Created on: 2015/11/07
 *      Author: kryozahiro
 */

#include "Reflection.h"
using namespace std;
using namespace cpputil;

std::shared_ptr<Scope> Reflection::getGlobal() {
	return global;
}

Reflection::Reflection() {
	global = make_shared<Scope>(Scope::NAMESPACE);
}
