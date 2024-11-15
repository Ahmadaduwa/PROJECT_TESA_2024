/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_predictSignal_api.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 10:15:10
 */

#ifndef _CODER_PREDICTSIGNAL_API_H
#define _CODER_PREDICTSIGNAL_API_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef typedef_categorical
#define typedef_categorical
typedef struct {
  uint8_T codes;
  char_T categoryNames[2];
} categorical;
#endif /* typedef_categorical */

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void predictSignal(real_T inputFeature[3], categorical *label);

void predictSignal_api(const mxArray *prhs, const mxArray **plhs);

void predictSignal_atexit(void);

void predictSignal_initialize(void);

void predictSignal_terminate(void);

void predictSignal_xil_shutdown(void);

void predictSignal_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_predictSignal_api.h
 *
 * [EOF]
 */
