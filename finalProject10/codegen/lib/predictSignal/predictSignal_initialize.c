/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: predictSignal_initialize.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 10:15:10
 */

/* Include Files */
#include "predictSignal_initialize.h"
#include "predictSignal.h"
#include "predictSignal_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void predictSignal_initialize(void)
{
  omp_init_nest_lock(&predictSignal_nestLockGlobal);
  predictSignal_init();
  isInitialized_predictSignal = true;
}

/*
 * File trailer for predictSignal_initialize.c
 *
 * [EOF]
 */
