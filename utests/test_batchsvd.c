/* Copyright 2016. Martin Uecker.
 * All rights reserved. Use of this source code is governed by
 * a BSD-style license which can be found in the LICENSE file.
 *
 * Authors: 
 * 2016 Martin Uecker <martin.uecker@med.uni-goettingen.de>
 */

#include <stdlib.h>

#include "lowrank/batchsvd.h"

#include "num/flpmath.h"

#include "misc/debug.h"
#include "misc/misc.h"

#include "minunit.h"



static bool test_batch_svthresh_tall()
{
	complex float inout[1][5][3] = { {

		{ 3., 0., 0. },
		{ 0., 2., 0. },
		{ 0., 0., 1. },
		{ 0., 0., 0. },
		{ 0., 0., 0. },
	} };

	batch_svthresh(3, 5, 1, 1., inout);

	const complex float ref[1][5][3] = { {

		{ 2., 0., 0. },
		{ 0., 1., 0. },
		{ 0., 0., 0. },
		{ 0., 0., 0. },
		{ 0., 0., 0. },
	} };

	long dims[3] = { 3, 5, 1 };

	MU_ASSERT(md_znrmse(3, dims, &ref[0][0][0], &inout[0][0][0]) < TOL);
	
	return true;
}

static bool test_batch_svthresh_wide()
{
	complex float inout[1][3][5] = { {

		{ 3., 0., 0., 0., 0. },
		{ 0., 2., 0., 0., 0. },
		{ 0., 0., 1., 0., 0. },
	} };

	batch_svthresh(5, 3, 1, 1., inout);

	const complex float ref[1][3][5] = { {

		{ 2., 0., 0., 0., 0. },
		{ 0., 1., 0., 0., 0. },
		{ 0., 0., 0., 0., 0. },
	} };

	long dims[3] = { 5, 3, 1 };

	MU_ASSERT(md_znrmse(3, dims, &ref[0][0][0], &inout[0][0][0]) < TOL);
	
	return true;
}



int main(int argc, char* argv[])
{
	UNUSED(argc); UNUSED(argv);

	MU_RUN_TEST(test_batch_svthresh_tall);
	MU_RUN_TEST(test_batch_svthresh_wide);

	debug_printf(DP_INFO, "%d/%d failed.\n", num_tests_failed, num_tests_run);

	bool ret = (0 == num_tests_failed);

	return ret ? 0 : 1;
}


