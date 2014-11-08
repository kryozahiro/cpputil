/*
 * ThreadPool.cpp
 *
 *  Created on: 2013/03/20
 *      Author: khiro
 */

#include "ThreadPool.h"
using namespace std;
using namespace cpputil;

ThreadPool::ThreadPool(int size) {
	if (size <= 0) {
		size = boost::thread::hardware_concurrency() - 1;
		if (size <= 0) {
			size = 1;
		}
	}
	for (int i = 0; i < size; ++i) {
		threadGroup.create_thread([&](){ThreadPool::run();});
	}
}

int ThreadPool::getThreadCount() const {
	return threadGroup.size();
}

void ThreadPool::put(function<void ()> task) {
	boost::mutex::scoped_lock lock(taskMutex);
	tasks.push(task);
	taskCondition.notify_all();
}

function<void ()> ThreadPool::take() {
	boost::mutex::scoped_lock lock(taskMutex);

	while (tasks.empty()) {
		taskCondition.wait(lock);
	}
	function<void ()> f = tasks.front();
	tasks.pop();
	return f;
}

void ThreadPool::run() {
	while (true) {
		take()();
	}
}
