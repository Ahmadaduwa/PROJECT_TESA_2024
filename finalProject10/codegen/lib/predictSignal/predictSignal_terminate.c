/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: predictSignal_terminate.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 10:15:10
 */

/* Include Files */
#include "predictSignal_terminate.h"
#include "predictSignal_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void predictSignal_terminate(void)
{
  omp_destroy_nest_lock(&predictSignal_nestLockGlobal);
  isInitialized_predictSignal = false;
}

/*
 * File trailer for predictSignal_terminate.c
 *
 * [EOF]
 */
