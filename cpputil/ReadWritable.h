/*
 * ReadWritable.h
 *
 *  Created on: 2014/01/06
 *      Author: kryozahiro
 */

#ifndef READWRITABLE_H_
#define READWRITABLE_H_

#include <iostream>

namespace cpputil {

class ReadWritable {
public:
	virtual ~ReadWritable() = default;
	virtual void read(std::istream& is) = 0;
	virtual void write(std::ostream& os) const = 0;
};

inline std::istream& operator>>(std::istream& is, ReadWritable& rhs) {
	rhs.read(is);
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const ReadWritable& rhs) {
	rhs.write(os);
	return os;
}

}

#endif /* READWRITABLE_H_ */
