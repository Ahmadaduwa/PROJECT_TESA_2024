/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: predictSignal_internal_types.h
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 10:15:10
 */

#ifndef PREDICTSIGNAL_INTERNAL_TYPES_H
#define PREDICTSIGNAL_INTERNAL_TYPES_H

/* Include Files */
#include "predictSignal_types.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef c_enum_c_classreg_learning_code
#define c_enum_c_classreg_learning_code
enum c_classreg_learning_coderutils_
{
  Logit = 0, /* Default value */
  Doublelogit,
  Invlogit,
  Ismax,
  Sign,
  Symmetric,
  Symmetricismax,
  Symmetriclogit,
  Identity
};
#endif /* c_enum_c_classreg_learning_code */
#ifndef c_typedef_c_classreg_learning_c
#define c_typedef_c_classreg_learning_c
typedef enum c_classreg_learning_coderutils_ c_classreg_learning_coderutils_;
#endif /* c_typedef_c_classreg_learning_c */

#endif
/*
 * File trailer for predictSignal_internal_types.h
 *
 * [EOF]
 */
