/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: predictSignal.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 10:15:10
 */

#ifndef PREDICTSIGNAL_H
#define PREDICTSIGNAL_H

/* Include Files */
#include "predictSignal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void predictSignal(const double inputFeature[3], categorical *label);

void predictSignal_init(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for predictSignal.h
 *
 * [EOF]
 */
