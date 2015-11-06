/*
 * Creatable.h
 *
 *  Created on: 2014/12/17
 *      Author: kryozahiro
 */

#ifndef CPPUTIL_CREATABLE_H_
#define CPPUTIL_CREATABLE_H_

namespace cpputil {

//! createできるクラスのインターフェース
template <class CreateType, class... Args>
class Creatable {
public:
	typedef CreateType create_type;
	virtual ~Creatable() = default;
	virtual CreateType* create(Args... args) = 0;
};

#define CPPUTIL_CREATABLE\
	virtual create_type* create() override {\
		typedef std::remove_pointer<decltype(this)>::type this_type;\
		return new this_type;\
	}

}

#endif /* CPPUTIL_CREATABLE_H_ */
