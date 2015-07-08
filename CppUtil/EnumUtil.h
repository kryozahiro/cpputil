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
#include <boost/lexical_cast.hpp>

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
			if (line.size() == 0) {
				continue;
			}

			//=で分解を試みる
			std::vector<std::string> terms;
			boost::algorithm::split(terms, line, boost::is_any_of(" ="), boost::algorithm::token_compress_on);
			if (terms.size() >= 2) {
				//分解できれば値を更新
				value = atoi(terms[1].c_str());
			}

			//値を追加
			registry.insert(typename boost::bimaps::bimap<boost::bimaps::unordered_set_of<T>, boost::bimaps::unordered_set_of<std::string>>::value_type(static_cast<T>(value), terms[0]));
			++value;
		}
	}
}

//SFINAE用の基底クラス
struct CppUtilEnumBase {};

//文字列変換付きenum
//使用例：CPPUTIL_ENUM(Fruit, APPLE, BANANA = 3, ORANGE);
#define CPPUTIL_ENUM(Name, ...)\
class Name : cpputil::CppUtilEnumBase {\
public:\
	enum Enum {\
		__VA_ARGS__\
	};\
	Name() = default;\
	Name(Enum value) {\
		enumHolder.value = value;\
	}\
	explicit Name(int value) {\
		enumHolder.value = static_cast<Enum>(value);\
	}\
	operator Enum() const {\
		return enumHolder.value;\
	}\
	void read(std::istream& is) {\
		std::string buf;\
		is >> buf;\
		enumHolder.value = getRegistry().right.at(buf);\
	}\
	void write(std::ostream& os) const {\
		os << getRegistry().left.at(enumHolder.value);\
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
	struct EnumHolder{\
		Enum value;\
	} enumHolder;\
};\
static_assert(std::is_pod<Name>(), "class Name should be POD");

//入出力演算子
template <class T, class = typename std::enable_if<std::is_base_of<CppUtilEnumBase, T>::value>::type>
inline std::istream& operator>>(std::istream& is, T& rhs) {
	rhs.read(is);
	return is;
}
template <class T, class = typename std::enable_if<std::is_base_of<CppUtilEnumBase, T>::value>::type>
inline std::ostream& operator<<(std::ostream& os, const T& rhs) {
	rhs.write(os);
	return os;
}

}

//ADL対策
//特にlexical_cast出来るようにする
namespace boost {
	using cpputil::operator>>;
	using cpputil::operator<<;

	template <>
	struct has_right_shift<std::istream, cpputil::CppUtilEnumBase> : public true_type {};
	template <>
	struct has_left_shift<std::ostream, cpputil::CppUtilEnumBase> : public true_type {};
}

using cpputil::operator>>;
using cpputil::operator<<;

#endif /* CPPUTIL_ENUMUTIL_H_ */
