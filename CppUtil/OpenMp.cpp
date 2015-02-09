/*
 * OpenMp.cpp
 *
 *  Created on: 2015/02/07
 *      Author: kryozahiro
 */

#include <omp.h>
#include "OpenMp.h"

namespace cpputil {

void initOpenMp(int threads) {
	omp_set_dynamic(1);

	//スレッド数の決定
	if (threads > 0) {
		omp_set_num_threads(threads);
	} else if (omp_get_num_procs() + threads > 0) {
		omp_set_num_threads(omp_get_num_procs() + threads);
	} else {
		omp_set_num_threads(1);
	}
}

}
