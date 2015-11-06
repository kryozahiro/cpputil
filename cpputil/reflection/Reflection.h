/*
 * Reflection.h
 *
 *  Created on: 2015/11/05
 *      Author: kryozahiro
 */

#ifndef CPPUTIL_REFLECTION_H_
#define CPPUTIL_REFLECTION_H_

#include <boost/serialization/singleton.hpp>
#include "../AtStart.h"
#include "Scope.h"

namespace cpputil {

//! リフレクション情報を保持するクラス
class Reflection : public boost::serialization::singleton<Reflection> {
public:
	std::shared_ptr<Scope> getGlobal();
protected:
	Reflection();
	virtual ~Reflection() = default;
private:
	std::shared_ptr<Scope> global;
};

}

#endif /* CPPUTIL_REFLECTION_H_ */
