/*
 * AtStart.h
 *
 *  Created on: 2015/11/07
 *      Author: kryozahiro
 */

#ifndef CPPUTIL_ATSTART_H_
#define CPPUTIL_ATSTART_H_

namespace cpputil {

/// 起動時に実行する処理を設定する
/** # 使用例
 *  CPPUTIL_AT_START(UniqueNameInWholeProgram) {\n
 *  	//...;\n
 *  }\n
 *  Nameに__LINE__や__COUNTER__は使用できない
 *  # 実装の説明
 *  template class内のstaticメンバの実体はヘッダで定義できる\n
 *  ただしAtStartは他で使用されないので明示的インスタンス化をする必要がある
 */
#define CPPUTIL_AT_START(Name)\
	namespace cpputil_internal {\
		template <class Dummy>\
		class AtStart##Name {\
			static const AtStart##Name<Dummy> atstart;\
			AtStart##Name();\
		};\
		template <class Dummy>\
		const AtStart##Name<Dummy> AtStart##Name<Dummy>::atstart;\
		template class AtStart##Name<void>;\
	}\
	template <class Dummy>\
	cpputil_internal::AtStart##Name<Dummy>::AtStart##Name()

}

#endif /* CPPUTIL_ATSTART_H_ */
