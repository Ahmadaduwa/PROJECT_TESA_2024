/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: knnsearch.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 10:15:10
 */

/* Include Files */
#include "knnsearch.h"
#include "kdsearchfun.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include <math.h>
#include <string.h>

/* Type Definitions */
#ifndef struct_emxArray_int32_T_1x312
#define struct_emxArray_int32_T_1x312
struct emxArray_int32_T_1x312 {
  int data[312];
  int size[2];
};
#endif /* struct_emxArray_int32_T_1x312 */
#ifndef typedef_emxArray_int32_T_1x312
#define typedef_emxArray_int32_T_1x312
typedef struct emxArray_int32_T_1x312 emxArray_int32_T_1x312;
#endif /* typedef_emxArray_int32_T_1x312 */

#ifndef typedef_cell_wrap_46
#define typedef_cell_wrap_46
typedef struct {
  emxArray_int32_T_1x312 f1;
} cell_wrap_46;
#endif /* typedef_cell_wrap_46 */

#ifndef c_typedef_emxArray_cell_wrap_46
#define c_typedef_emxArray_cell_wrap_46
typedef struct {
  cell_wrap_46 data[15];
} emxArray_cell_wrap_46_15;
#endif /* c_typedef_emxArray_cell_wrap_46 */

#ifndef typedef_struct_T
#define typedef_struct_T
typedef struct {
  double X[936];
  emxArray_int32_T_1x312 wasnanIdx;
  double nx_nonan;
} struct_T;
#endif /* typedef_struct_T */

/* Function Declarations */
static void cast(const double t0_X[936], const int t0_wasnanIdx_data[],
                 const int t0_wasnanIdx_size[2], struct_T *r);

/* Function Definitions */
/*
 * Arguments    : const double t0_X[936]
 *                const int t0_wasnanIdx_data[]
 *                const int t0_wasnanIdx_size[2]
 *                struct_T *r
 * Return Type  : void
 */
static void cast(const double t0_X[936], const int t0_wasnanIdx_data[],
                 const int t0_wasnanIdx_size[2], struct_T *r)
{
  int loop_ub;
  memcpy(&r->X[0], &t0_X[0], 936U * sizeof(double));
  r->wasnanIdx.size[0] = 1;
  loop_ub = t0_wasnanIdx_size[1];
  r->wasnanIdx.size[1] = t0_wasnanIdx_size[1];
  if (loop_ub - 1 >= 0) {
    memcpy(&r->wasnanIdx.data[0], &t0_wasnanIdx_data[0],
           (unsigned int)loop_ub * sizeof(int));
  }
  r->nx_nonan = 312.0;
}

/*
 * Arguments    : const double X[936]
 *                const double Y[3]
 *                int Idx_data[]
 *                int Idx_size[2]
 *                double D_data[]
 *                int D_size[2]
 * Return Type  : void
 */
void knnsearch(const double X[936], const double Y[3], int Idx_data[],
               int Idx_size[2], double D_data[], int D_size[2])
{
  emxArray_cell_wrap_46_15 idxTemp1;
  struct_T expl_temp;
  double cgstruct_lowerBounds_data[45];
  double cgstruct_upperBounds_data[45];
  double lowerBoundsTemp_data[45];
  double upperBoundsTemp_data[45];
  double cgstruct_cutDim_data[15];
  double cgstruct_leftChild_data[15];
  double cgstruct_rightChild_data[15];
  double cutValTemp_data[15];
  double tempDim_data[15];
  double c;
  double cc;
  double p;
  unsigned int cgstruct_idxAll[312];
  int iidx_data[312];
  int t3_wasnanIdx_data[312];
  unsigned int leftChildTemp_data[15];
  unsigned int rightChildTemp_data[15];
  int cgstruct_upperBounds_size[2];
  int currentNode;
  int eint;
  int i;
  int loop_ub;
  int loop_ub_tmp;
  int nextUnusedNode;
  short notnan_data[312];
  signed char cutDimTemp_data[15];
  bool leafNodeTemp_data[15];
  for (i = 0; i < 312; i++) {
    notnan_data[i] = (short)(i + 1);
  }
  cgstruct_upperBounds_size[0] = 1;
  cgstruct_upperBounds_size[1] = 0;
  frexp(6.24, &eint);
  c = pow(2.0, 4.0);
  eint = (int)(pow(2.0, 4.0) - 1.0);
  if (eint - 1 >= 0) {
    memset(&cutDimTemp_data[0], 0, (unsigned int)eint * sizeof(signed char));
    memset(&cutValTemp_data[0], 0, (unsigned int)eint * sizeof(double));
  }
  loop_ub_tmp = (int)(c - 1.0) * 3;
  for (i = 0; i < loop_ub_tmp; i++) {
    upperBoundsTemp_data[i] = rtInf;
    lowerBoundsTemp_data[i] = rtMinusInf;
  }
  if (eint - 1 >= 0) {
    memset(&leftChildTemp_data[0], 0,
           (unsigned int)eint * sizeof(unsigned int));
    memset(&rightChildTemp_data[0], 0,
           (unsigned int)eint * sizeof(unsigned int));
    memset(&leafNodeTemp_data[0], 0, (unsigned int)eint * sizeof(bool));
  }
  idxTemp1.data[0].f1.size[0] = 1;
  idxTemp1.data[0].f1.size[1] = 312;
  for (i = 0; i < 312; i++) {
    idxTemp1.data[0].f1.data[i] = notnan_data[i];
  }
  currentNode = 0;
  nextUnusedNode = 1;
  while ((unsigned int)(currentNode + 1) < (unsigned int)(nextUnusedNode + 1)) {
    loop_ub = idxTemp1.data[currentNode].f1.size[1];
    if (loop_ub <= 50) {
      leafNodeTemp_data[currentNode] = true;
    } else {
      double y_data[312];
      double minval[3];
      double temp[3];
      double temp_tmp;
      int half;
      unsigned int qY;
      for (eint = 0; eint < 3; eint++) {
        cc = X[(idxTemp1.data[currentNode].f1.data[0] + 312 * eint) - 1];
        temp[eint] = cc;
        minval[eint] = cc;
        for (loop_ub_tmp = 2; loop_ub_tmp <= loop_ub; loop_ub_tmp++) {
          p = X[(idxTemp1.data[currentNode].f1.data[loop_ub_tmp - 1] +
                 312 * eint) -
                1];
          if (temp[eint] < p) {
            temp[eint] = p;
          }
          if (minval[eint] > p) {
            minval[eint] = p;
          }
        }
        temp[eint] -= minval[eint];
      }
      cc = temp[0];
      eint = 0;
      if (temp[0] < temp[1]) {
        cc = temp[1];
        eint = 1;
      }
      if (cc < temp[2]) {
        eint = 2;
      }
      for (i = 0; i < loop_ub; i++) {
        y_data[i] = X[(idxTemp1.data[currentNode].f1.data[i] + 312 * eint) - 1];
      }
      loop_ub_tmp = sort(y_data, &loop_ub, iidx_data);
      for (i = 0; i < loop_ub_tmp; i++) {
        notnan_data[i] =
            (short)idxTemp1.data[currentNode].f1.data[iidx_data[i] - 1];
      }
      half = (int)ceil((double)loop_ub / 2.0);
      p = (y_data[half - 1] + y_data[half]) / 2.0;
      cutDimTemp_data[currentNode] = (signed char)(eint + 1);
      cutValTemp_data[currentNode] = p;
      qY = (unsigned int)nextUnusedNode + 2U;
      if ((unsigned int)nextUnusedNode + 2U <
          (unsigned int)(nextUnusedNode + 1)) {
        qY = MAX_uint32_T;
      }
      leftChildTemp_data[currentNode] = (unsigned int)(nextUnusedNode + 1);
      rightChildTemp_data[currentNode] = qY;
      temp[0] = upperBoundsTemp_data[currentNode];
      cc = upperBoundsTemp_data[currentNode + (int)(c - 1.0)];
      temp[1] = cc;
      temp_tmp = upperBoundsTemp_data[currentNode + (int)(c - 1.0) * 2];
      temp[2] = temp_tmp;
      upperBoundsTemp_data[(int)qY - 1] = upperBoundsTemp_data[currentNode];
      upperBoundsTemp_data[((int)qY + (int)(c - 1.0)) - 1] = cc;
      upperBoundsTemp_data[((int)qY + (int)(c - 1.0) * 2) - 1] = temp_tmp;
      temp[eint] = p;
      upperBoundsTemp_data[nextUnusedNode] = temp[0];
      temp[0] = lowerBoundsTemp_data[currentNode];
      upperBoundsTemp_data[nextUnusedNode + (int)(c - 1.0)] = temp[1];
      cc = lowerBoundsTemp_data[currentNode + (int)(c - 1.0)];
      temp[1] = cc;
      upperBoundsTemp_data[nextUnusedNode + (int)(c - 1.0) * 2] = temp[2];
      temp_tmp = lowerBoundsTemp_data[currentNode + (int)(c - 1.0) * 2];
      temp[2] = temp_tmp;
      lowerBoundsTemp_data[nextUnusedNode] = lowerBoundsTemp_data[currentNode];
      lowerBoundsTemp_data[nextUnusedNode + (int)(c - 1.0)] = cc;
      lowerBoundsTemp_data[nextUnusedNode + (int)(c - 1.0) * 2] = temp_tmp;
      temp[eint] = p;
      lowerBoundsTemp_data[(int)qY - 1] = temp[0];
      lowerBoundsTemp_data[((int)qY + (int)(c - 1.0)) - 1] = temp[1];
      lowerBoundsTemp_data[((int)qY + (int)(c - 1.0) * 2) - 1] = temp[2];
      idxTemp1.data[currentNode].f1.size[0] = 1;
      idxTemp1.data[currentNode].f1.size[1] = 0;
      idxTemp1.data[nextUnusedNode].f1.size[0] = 1;
      idxTemp1.data[nextUnusedNode].f1.size[1] = half;
      for (i = 0; i < half; i++) {
        idxTemp1.data[nextUnusedNode].f1.data[i] = notnan_data[i];
      }
      if (half + 1 > loop_ub_tmp) {
        half = 0;
        loop_ub_tmp = 0;
      }
      idxTemp1.data[(int)qY - 1].f1.size[0] = 1;
      loop_ub = loop_ub_tmp - half;
      idxTemp1.data[(int)qY - 1].f1.size[1] = loop_ub;
      for (i = 0; i < loop_ub; i++) {
        idxTemp1.data[(int)qY - 1].f1.data[i] = notnan_data[half + i];
      }
      nextUnusedNode += 2;
    }
    currentNode++;
  }
  cast(X, t3_wasnanIdx_data, cgstruct_upperBounds_size, &expl_temp);
  for (i = 0; i < nextUnusedNode; i++) {
    cgstruct_cutDim_data[i] = cutDimTemp_data[i];
  }
  cgstruct_upperBounds_size[0] = nextUnusedNode;
  cgstruct_upperBounds_size[1] = 3;
  for (i = 0; i < 3; i++) {
    for (eint = 0; eint < nextUnusedNode; eint++) {
      cgstruct_lowerBounds_data[eint + nextUnusedNode * i] =
          lowerBoundsTemp_data[eint + (int)(c - 1.0) * i];
      cgstruct_upperBounds_data[eint + nextUnusedNode * i] =
          upperBoundsTemp_data[eint + (int)(c - 1.0) * i];
    }
  }
  memset(&cgstruct_idxAll[0], 0, 312U * sizeof(unsigned int));
  cc = 1.0;
  for (loop_ub_tmp = 0; loop_ub_tmp < nextUnusedNode; loop_ub_tmp++) {
    eint = idxTemp1.data[loop_ub_tmp].f1.size[1];
    tempDim_data[loop_ub_tmp] = eint;
    if (eint > 0) {
      p = (cc + (double)eint) - 1.0;
      if (cc > p) {
        i = 0;
        eint = 0;
      } else {
        i = (int)cc - 1;
        eint = (int)p;
      }
      loop_ub = eint - i;
      for (eint = 0; eint < loop_ub; eint++) {
        cgstruct_idxAll[i + eint] =
            (unsigned int)idxTemp1.data[loop_ub_tmp].f1.data[eint];
      }
      cc += tempDim_data[loop_ub_tmp];
    }
    cgstruct_leftChild_data[loop_ub_tmp] = leftChildTemp_data[loop_ub_tmp];
    cgstruct_rightChild_data[loop_ub_tmp] = rightChildTemp_data[loop_ub_tmp];
  }
  kdsearchfunCG(expl_temp.X, expl_temp.wasnanIdx.data, cgstruct_cutDim_data,
                cutValTemp_data, cgstruct_lowerBounds_data,
                cgstruct_upperBounds_size, cgstruct_upperBounds_data,
                cgstruct_upperBounds_size, cgstruct_leftChild_data,
                cgstruct_rightChild_data, leafNodeTemp_data, expl_temp.nx_nonan,
                cgstruct_idxAll, tempDim_data, Y, Idx_data, Idx_size, D_data,
                D_size);
}

/*
 * File trailer for knnsearch.c
 *
 * [EOF]
 */
