/*
 * ThreadPool.h
 *
 *  Created on: 2013/03/20
 *      Author: khiro
 */

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <queue>

namespace cpputil {

//スレッドプール
class ThreadPool {
public:
	//size個のスレッドのプールを作成する
	//size == 0ならハードウェア依存の数にする
	ThreadPool(int size = 0);

	virtual ~ThreadPool();

	//スレッド数を取得する
	int getThreadSize() const;

	//タスクを追加する
	void addTask(std::function<void ()> task);

	//全てのタスクの完了を待つ
	void waitTasks();

private:
	//管理している全てのスレッド
	std::vector<std::shared_ptr<std::thread>> pool;
	std::condition_variable activate;
	std::condition_variable allIdle;
	std::atomic_uint idleThreads;

	//タスクのキュー
	std::queue<std::function<void ()>> tasks;
	std::mutex taskMutex;

	//全スレッドの停止フラグ
	std::atomic_bool end;

	//個別スレッドのメインループ
	void run();

	//未処理のタスクがあれば一つ消費する
	bool doNextTask(std::unique_lock<std::mutex>& lock);
};

}

#endif /* THREADPOOL_H_ */
