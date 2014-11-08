/*
 * ThreadPool.h
 *
 *  Created on: 2013/03/20
 *      Author: khiro
 */

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <queue>
#include <boost/thread.hpp>

namespace cpputil {

//スレッドプール
class ThreadPool {
public:
	ThreadPool(int size);

	//スレッド数を調べる
	int getThreadCount() const;

	//タスクを追加する
	void put(std::function<void ()> task);

private:
	std::queue<std::function<void ()> > tasks;
	boost::thread_group threadGroup;
	boost::mutex taskMutex;
	boost::condition_variable taskCondition;

	//キューからタスクを一つ取り出す
	std::function<void ()> take();

	//個別スレッドのメインループ
	void run();
};

}

#endif /* THREADPOOL_H_ */
