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

class ThreadPool {
public:
	ThreadPool(int size);
	int getThreadCount() const;
	void put(std::function<void ()> task);

private:
	std::queue<std::function<void ()> > tasks;
	boost::thread_group threadGroup;
	boost::mutex taskMutex;
	boost::condition_variable taskCondition;

	std::function<void ()> take();
	void run();
};

}

#endif /* THREADPOOL_H_ */
