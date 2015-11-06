/*
 * Scope.h
 *
 *  Created on: 2015/11/06
 *      Author: kryozahiro
 */

#ifndef CPPUTIL_SCOPE_H_
#define CPPUTIL_SCOPE_H_

#include <string>
#include <memory>
#include <unordered_map>
#include <functional>
#include <experimental/any>

namespace cpputil {

//! スコープ
class Scope {
public:
	enum Type {
		NAMESPACE,
		CLASS,
	};
	Scope(Type type);

	//! スコープの種類を取得する
	Type getType() const;

	//! 子スコープを取得する
	std::shared_ptr<Scope> getScope(const std::string& name);

	//! 子スコープを追加する
	std::shared_ptr<Scope> addScope(Type type, const std::string& name);

	//! 関数またはメンバ関数またはメンバ変数を取得する
	template <class T>
	std::function<T> getFunction(const std::string& name) {
		return std::experimental::any_cast<std::function<T>>(functions.at(name));
	}

	//! 関数またはメンバ関数またはメンバ変数を追加する
	template <class T>
	void addFunction(const std::string& name, std::function<T> f) {
		functions[name] = f;
	}

	//! 変数を取得する
	template <class T>
	T& getVariable(const std::string& name) {
		return *std::experimental::any_cast<T*>(variables.at(name));
	}

	//! 変数を追加する
	template <class T>
	void addVariable(const std::string& name, T* v) {
		variables[name] = v;
	}

private:
	Type type;
	std::unordered_map<std::string, std::shared_ptr<Scope>> scopes;
	std::unordered_map<std::string, std::experimental::any> functions;
	std::unordered_map<std::string, std::experimental::any> variables;
};

}

#endif /* CPPUTIL_SCOPE_H_ */
