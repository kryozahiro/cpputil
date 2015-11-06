/*
 * Scope.cpp
 *
 *  Created on: 2015/11/06
 *      Author: kryozahiro
 */

#include "Scope.h"
using namespace std;
using namespace cpputil;

Scope::Scope(Type type) : type(type) {

}

Scope::Type Scope::getType() const {
	return type;
}

std::shared_ptr<Scope> Scope::getScope(const std::string& name) {
	return scopes.at(name);
}

std::shared_ptr<Scope> Scope::addScope(Scope::Type type, const std::string& name) {
	auto itr = scopes.find(name);
	if (itr != scopes.end()) {
		return itr->second;
	}
	return scopes[name] = make_shared<Scope>(type);
}
