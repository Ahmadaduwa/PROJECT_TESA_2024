/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: sound_freq.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 13-Nov-2024 11:48:35
 */

/* Include Files */
#include "sound_freq.h"
#include "FFTImplementationCallback.h"
#include "abs.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double X[4096]
 *                double spectrum[2048]
 * Return Type  : void
 */
void sound_freq(const double X[4096], double spectrum[2048])
{
  creal_T yCol[4096];
  double dv[4096];
  /* complex num */
  /*  abs sulute  */
  c_FFTImplementationCallback_doH(X, yCol);
  b_abs(yCol, dv);
  memcpy(&spectrum[0], &dv[0], 2048U * sizeof(double));
  /*  หา magnitude  */
}

/*
 * File trailer for sound_freq.c
 *
 * [EOF]
 */
