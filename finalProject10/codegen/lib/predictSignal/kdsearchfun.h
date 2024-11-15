/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: kdsearchfun.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 10:15:10
 */

#ifndef KDSEARCHFUN_H
#define KDSEARCHFUN_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void kdsearchfunCG(
    const double obj_X[936], const int obj_wasnanIdx_data[],
    const double obj_cutDim_data[], const double obj_cutVal_data[],
    const double obj_lowerBounds_data[], const int obj_lowerBounds_size[2],
    const double obj_upperBounds_data[], const int obj_upperBounds_size[2],
    const double obj_leftChild_data[], const double obj_rightChild_data[],
    const bool obj_leafNode_data[], double obj_nx_nonan,
    const unsigned int obj_idxAll[312], const double obj_idxDim_data[],
    const double Y[3], int idx_data[], int idx_size[2], double dist_data[],
    int dist_size[2]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for kdsearchfun.h
 *
 * [EOF]
 */
