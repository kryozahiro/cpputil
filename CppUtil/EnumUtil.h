/*
 * EnumUtil.h
 *
 *  Created on: 2015/07/08
 *      Author: kryozahiro
 */

#ifndef CPPUTIL_ENUMUTIL_H_
#define CPPUTIL_ENUMUTIL_H_

#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include "ReadWritable.h"

namespace cpputil {

namespace detail {
	template <class T>
	void initRegistry(boost::bimaps::bimap<boost::bimaps::unordered_set_of<T>, boost::bimaps::unordered_set_of<std::string>>& registry, std::string args) {
		//,で分解する
		std::vector<std::string> lines;
		boost::algorithm::split(lines, args, boost::is_any_of(","));

		int value = 0;
		for (std::string& line : lines) {
			boost::algorithm::trim(line);

			//=で分解を試みる
			std::vector<std::string> terms;
			boost::algorithm::split(terms, line, boost::is_any_of(" ="), boost::algorithm::token_compress_on);
			if (terms.size() >= 2) {
				//分解できれば値を更新
				value = atoi(terms[1].c_str());
			}
			registry.insert(typename boost::bimaps::bimap<boost::bimaps::unordered_set_of<T>, boost::bimaps::unordered_set_of<std::string>>::value_type(static_cast<T>(value), terms[0]));
			++value;
		}
	}
}

//文字列変換付きenum
//使用例：CPPUTIL_ENUM(Fruit, APPLE, BANANA = 3, ORANGE);
#define CPPUTIL_ENUM(Name, ...)\
class Name : public virtual cpputil::ReadWritable {\
public:\
	enum Enum {\
		__VA_ARGS__\
	};\
	Name() : Name(static_cast<Enum>(0)){\
	}\
	Name(Enum value) : value(value) {\
	}\
	explicit Name(int value) : value(static_cast<Enum>(value)) {\
	}\
	explicit operator int() {\
		return value;\
	}\
	virtual void read(std::istream& is) {\
		std::string buf;\
		is >> buf;\
		value = getRegistry().right.at(buf);\
	}\
	virtual void write(std::ostream& os) const {\
		os << getRegistry().left.at(value);\
	}\
private:\
	typedef boost::bimaps::bimap<boost::bimaps::unordered_set_of<Enum>, boost::bimaps::unordered_set_of<std::string>> registry_type;\
	struct RegistryHolder {\
		RegistryHolder() {\
			cpputil::detail::initRegistry(registry, #__VA_ARGS__);\
		}\
		registry_type registry;\
	};\
	static registry_type& getRegistry() {\
		static RegistryHolder registryHolder;\
		return registryHolder.registry;\
	}\
	Enum value;\
};

}

#endif /* CPPUTIL_ENUMUTIL_H_ */
