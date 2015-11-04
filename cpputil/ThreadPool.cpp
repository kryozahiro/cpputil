/*
 * ThreadPool.cpp
 *
 *  Created on: 2013/03/20
 *      Author: khiro
 */

#include "ThreadPool.h"
using namespace std;
using namespace cpputil;

ThreadPool::ThreadPool(int size) : idleThreads(0), end(false) {
	if (size <= 0) {
		size = max(static_cast<unsigned int>(0), std::thread::hardware_concurrency() - 1);
	}
	for (int i = 0; i < size; ++i) {
		shared_ptr<thread> th = make_shared<thread>([&](){
			ThreadPool::run();
		});
		pool.push_back(th);
	}
}

ThreadPool::~ThreadPool() {
	end = true;
	activate.notify_all();
	for (shared_ptr<thread>& th : pool) {
		th->join();
	}
}

int ThreadPool::getThreadSize() const {
	return pool.size();
}

void ThreadPool::addTask(function<void ()> task) {
	{
		lock_guard<mutex> lock(taskMutex);
		tasks.push(task);
	}
	activate.notify_one();
}

void ThreadPool::waitTasks() {
	unique_lock<mutex> lock(taskMutex);
	while (doNextTask(lock)) {
		//do nothing
	}
	if (idleThreads != pool.size()) {
		allIdle.wait(lock);
	}
}

void ThreadPool::run() {
	unique_lock<mutex> lock(taskMutex);
	while (!end) {
		if (!doNextTask(lock)) {
			++idleThreads;
			if (idleThreads == pool.size()) {
				allIdle.notify_one();
			}
			activate.wait(lock);
			--idleThreads;
		}
	}
}

bool ThreadPool::doNextTask(unique_lock<mutex>& lock) {
	if (tasks.empty()) {
		return false;
	}
	function<void ()> task = tasks.front();
	tasks.pop();
	lock.unlock();
	task();
	lock.lock();
	return true;
}
