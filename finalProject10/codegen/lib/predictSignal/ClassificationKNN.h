/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: ClassificationKNN.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 10:15:10
 */

#ifndef CLASSIFICATIONKNN_H
#define CLASSIFICATIONKNN_H

/* Include Files */
#include "predictSignal_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
unsigned char ClassificationKNN_predict(
    const double obj_Prior[2], const double obj_Cost[4],
    const double obj_X[936], const unsigned int obj_YIdx[312],
    const double obj_W[312], const double Xin[3], char labels_categoryNames[2]);

double c_ClassificationKNN_Classificat(
    int obj_ClassNamesLength[2],
    c_classreg_learning_coderutils_ *obj_ScoreTransform, double obj_Prior[2],
    bool obj_ClassLogicalIndices[2], double obj_Cost[4], double obj_X[936],
    unsigned int obj_YIdx[312], double obj_W[312]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for ClassificationKNN.h
 *
 * [EOF]
 */
