/*
 * Cloneable.h
 *
 *  Created on: 2014/09/19
 *      Author: khiro
 */

#ifndef CLONEABLE_H_
#define CLONEABLE_H_

namespace cpputil {

//! cloneできるクラスのインターフェース
template <class CloneType>
class Cloneable {
public:
	typedef CloneType clone_type;
	virtual ~Cloneable() = default;
	virtual CloneType* clone() = 0;
};

#define CPPUTIL_CLONEABLE\
	virtual clone_type* clone() override {\
		typedef std::remove_pointer<decltype(this)>::type this_type;\
		return new this_type(*this);\
	}

}

#endif /* CLONEABLE_H_ */
