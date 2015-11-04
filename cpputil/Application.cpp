/*
 * Application.cpp
 *
 *  Created on: 2015/07/31
 *      Author: kryozahiro
 */

#include "Application.h"

#include <atomic>
using namespace std;

namespace cpputil {

namespace detail {

//終了状態
#if ATOMIC_INT_LOCK_FREE == 2
	static volatile atomic_int end(0);
#else
#error "lock-free atomic type doesn't found"
#endif

	extern "C" void cppUtilExitHandler(int sig) {
		atomic_store(&end, 1);
	}
}

bool isEnd() {
	return detail::end;
}

}
