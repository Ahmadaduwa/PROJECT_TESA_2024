/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: predictSignal.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 10:15:10
 */

/* Include Files */
#include "predictSignal.h"
#include "ClassificationKNN.h"
#include "predictSignal_data.h"
#include "predictSignal_initialize.h"
#include "predictSignal_internal_types.h"
#include "predictSignal_types.h"
#include "rt_nonfinite.h"

/* Type Definitions */
#ifndef typedef_ClassificationKNN
#define typedef_ClassificationKNN
typedef struct {
  int ClassNamesLength[2];
  c_classreg_learning_coderutils_ ScoreTransform;
  double Prior[2];
  bool ClassLogicalIndices[2];
  double Cost[4];
  double X[936];
  unsigned int YIdx[312];
  double W[312];
} ClassificationKNN;
#endif /* typedef_ClassificationKNN */

/* Variable Definitions */
static bool knnModel_not_empty;

/* Function Definitions */
/*
 * Arguments    : const double inputFeature[3]
 *                categorical *label
 * Return Type  : void
 */
void predictSignal(const double inputFeature[3], categorical *label)
{
  static ClassificationKNN knnModel;
  if (!isInitialized_predictSignal) {
    predictSignal_initialize();
  }
  /*  ฟังก์ชัน predictSignal.m */
  if (!knnModel_not_empty) {
    c_ClassificationKNN_Classificat(knnModel.ClassNamesLength,
                                    &knnModel.ScoreTransform, knnModel.Prior,
                                    knnModel.ClassLogicalIndices, knnModel.Cost,
                                    knnModel.X, knnModel.YIdx, knnModel.W);
    knnModel_not_empty = true;
    /*  โหลดโมเดลที่บันทึกไว้ */
  }
  label->codes = ClassificationKNN_predict(
      knnModel.Prior, knnModel.Cost, knnModel.X, knnModel.YIdx, knnModel.W,
      inputFeature, label->categoryNames);
  /*  ทำนายผล */
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void predictSignal_init(void)
{
  knnModel_not_empty = false;
}

/*
 * File trailer for predictSignal.c
 *
 * [EOF]
 */
