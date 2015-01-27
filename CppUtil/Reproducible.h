/*
 * Reproducible.h
 *
 *  Created on: 2014/12/20
 *      Author: kryozahiro
 */

#ifndef CPPUTIL_REPRODUCIBLE_H_
#define CPPUTIL_REPRODUCIBLE_H_

#include <ctime>
#include <boost/property_tree/ptree.hpp>

namespace cpputil {

//乱数による挙動を再現可能なクラスのインターフェース
template <class RandomEngine>
class Reproducible {
public:
	static const int EVERY = 1;
	static const int ALWAYS = 0;
	static const int NEVER = -1;

	Reproducible() = default;
	/**
	 * 一定時間ごとにオブジェクトの状態を元に戻す
	 * @param uninitialized 乱数系列を初期化前の状態に戻すサイクル
	 * @param reinitialize 現在の乱数系列の続きで再初期化するサイクル
	 * @param unused 乱数系列を初期化済だが未使用の状態に戻すサイクル
	 * @param seed 乱数シード
	 */
	Reproducible(int uninitialized, int reinitialize, int unused, int seed = INT_MAX) :
			uninitialized(uninitialized), reinitialize(reinitialize), unused(unused) {
		if (seed == INT_MAX) {
			uninitializedEngine = RandomEngine(time(NULL));
		} else {
			uninitializedEngine = RandomEngine(seed);
		}
	}
	Reproducible(const boost::property_tree::ptree& gameTree) {
		std::string seed = gameTree.get<std::string>("Seed");
		if (seed == "Random") {
			uninitializedEngine = RandomEngine(time(NULL));
		} else {
			uninitializedEngine = RandomEngine(atoi(seed.c_str()));
		}

		try {
			std::string uninitializedStr = gameTree.get<std::string>("Uninitialized");
			uninitialized = getCondition(uninitializedStr);
		} catch (std::exception& e) {
			//何もしない
		}
		try {
			std::string reinitializeStr = gameTree.get<std::string>("Reinitialize");
			reinitialize = getCondition(reinitializeStr);
		} catch (std::exception& e) {
			//何もしない
		}
		try {
			std::string unusedStr = gameTree.get<std::string>("Unused");
			unused = getCondition(unusedStr);
		} catch (std::exception& e) {
			//何もしない
		}
	}
	virtual ~Reproducible() = default;

protected:
	//乱数を使用した初期化
	virtual void initialize() = 0;

	//時間を進める
	void advanceTime(int amount) {
		++currentTime;
	}

	//再現
	bool testReproduction() {
		if (prevTime == INT_MAX) {
			randomEngine = uninitializedEngine;
			initialize();
			initializedEngine = randomEngine;
			prevTime = currentTime;
			return true;
		}

		//初期化前へ戻す
		if (uninitialized != NEVER and (uninitialized == ALWAYS or prevTime / uninitialized != currentTime / uninitialized)) {
			randomEngine = uninitializedEngine;
			initialize();
			initializedEngine = randomEngine;
			prevTime = currentTime;
			return true;
		}
		//再初期化する
		if (reinitialize != NEVER and (reinitialize == ALWAYS or prevTime / reinitialize != currentTime / reinitialize)) {
			initialize();
			initializedEngine = randomEngine;
			prevTime = currentTime;
			return true;
		}
		//初期化後へ戻す
		if (unused != NEVER and (unused == ALWAYS or prevTime / unused != currentTime / unused)) {
			randomEngine = initializedEngine;
			prevTime = currentTime;
			return true;
		}
		return false;
	}

	//乱数エンジンを取得
	RandomEngine& getEngine() {
		return randomEngine;
	}

private:
	//各状態の乱数エンジン
	RandomEngine uninitializedEngine;
	RandomEngine initializedEngine;
	RandomEngine randomEngine;

	//各種の初期化条件
	int uninitialized = NEVER;
	int reinitialize = NEVER;
	int unused = NEVER;

	//時間
	int currentTime = 0;
	int prevTime = INT_MAX;

	//文字列から条件を取得
	int getCondition(std::string str) {
		if (str == "Every") {
			return EVERY;
		} else if (str == "Always") {
			return ALWAYS;
		} else if (str == "Never") {
			return NEVER;
		}
		return atoi(str.c_str());
	}
};

}

#endif /* CPPUTIL_REPRODUCIBLE_H_ */
