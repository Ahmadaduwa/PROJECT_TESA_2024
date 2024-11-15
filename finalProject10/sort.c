/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: sort.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 10:15:10
 */

/* Include Files */
#include "sort.h"
#include "rt_nonfinite.h"
#include "sortIdx.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : double x_data[]
 *                const int *x_size
 *                int idx_data[]
 * Return Type  : int
 */
int sort(double x_data[], const int *x_size, int idx_data[])
{
  double vwork_data[312];
  int b;
  int b_b;
  int b_i;
  int dim;
  int i;
  int i1;
  int idx_size;
  int j;
  int k;
  int vstride;
  int vwork_size;
  dim = 2;
  if (*x_size != 1) {
    dim = 1;
  }
  if (dim <= 1) {
    vwork_size = *x_size;
  } else {
    vwork_size = 1;
  }
  idx_size = *x_size;
  vstride = 1;
  i = dim - 2;
  for (k = 0; k <= i; k++) {
    vstride *= *x_size;
  }
  for (b_i = 0; b_i < 1; b_i++) {
    for (j = 0; j < vstride; j++) {
      int iidx_data[312];
      for (k = 0; k < vwork_size; k++) {
        vwork_data[k] = x_data[j + k * vstride];
        iidx_data[k] = 0;
      }
      if (vwork_size != 0) {
        double xwork_data[312];
        double x4[4];
        int iwork_data[312];
        int bLen;
        int bLen2;
        int i2;
        int i3;
        int i4;
        int iidx_tmp;
        int wOffset_tmp;
        short idx4[4];
        x4[0] = 0.0;
        idx4[0] = 0;
        x4[1] = 0.0;
        idx4[1] = 0;
        x4[2] = 0.0;
        idx4[2] = 0;
        x4[3] = 0.0;
        idx4[3] = 0;
        bLen2 = 0;
        dim = 0;
        for (k = 0; k < vwork_size; k++) {
          iwork_data[k] = 0;
          if (rtIsNaN(vwork_data[k])) {
            iidx_tmp = (vwork_size - bLen2) - 1;
            iidx_data[iidx_tmp] = k + 1;
            xwork_data[iidx_tmp] = vwork_data[k];
            bLen2++;
          } else {
            dim++;
            idx4[dim - 1] = (short)(k + 1);
            x4[dim - 1] = vwork_data[k];
            if (dim == 4) {
              double d;
              double d1;
              dim = k - bLen2;
              if (x4[0] <= x4[1]) {
                i1 = 1;
                i2 = 2;
              } else {
                i1 = 2;
                i2 = 1;
              }
              if (x4[2] <= x4[3]) {
                i3 = 3;
                i4 = 4;
              } else {
                i3 = 4;
                i4 = 3;
              }
              d = x4[i1 - 1];
              d1 = x4[i3 - 1];
              if (d <= d1) {
                d = x4[i2 - 1];
                if (d <= d1) {
                  i = i1;
                  bLen = i2;
                  i1 = i3;
                  i2 = i4;
                } else if (d <= x4[i4 - 1]) {
                  i = i1;
                  bLen = i3;
                  i1 = i2;
                  i2 = i4;
                } else {
                  i = i1;
                  bLen = i3;
                  i1 = i4;
                }
              } else {
                d1 = x4[i4 - 1];
                if (d <= d1) {
                  if (x4[i2 - 1] <= d1) {
                    i = i3;
                    bLen = i1;
                    i1 = i2;
                    i2 = i4;
                  } else {
                    i = i3;
                    bLen = i1;
                    i1 = i4;
                  }
                } else {
                  i = i3;
                  bLen = i4;
                }
              }
              iidx_data[dim - 3] = idx4[i - 1];
              iidx_data[dim - 2] = idx4[bLen - 1];
              iidx_data[dim - 1] = idx4[i1 - 1];
              iidx_data[dim] = idx4[i2 - 1];
              vwork_data[dim - 3] = x4[i - 1];
              vwork_data[dim - 2] = x4[bLen - 1];
              vwork_data[dim - 1] = x4[i1 - 1];
              vwork_data[dim] = x4[i2 - 1];
              dim = 0;
            }
          }
        }
        wOffset_tmp = vwork_size - bLen2;
        if (dim > 0) {
          signed char perm[4];
          perm[1] = 0;
          perm[2] = 0;
          perm[3] = 0;
          if (dim == 1) {
            perm[0] = 1;
          } else if (dim == 2) {
            if (x4[0] <= x4[1]) {
              perm[0] = 1;
              perm[1] = 2;
            } else {
              perm[0] = 2;
              perm[1] = 1;
            }
          } else if (x4[0] <= x4[1]) {
            if (x4[1] <= x4[2]) {
              perm[0] = 1;
              perm[1] = 2;
              perm[2] = 3;
            } else if (x4[0] <= x4[2]) {
              perm[0] = 1;
              perm[1] = 3;
              perm[2] = 2;
            } else {
              perm[0] = 3;
              perm[1] = 1;
              perm[2] = 2;
            }
          } else if (x4[0] <= x4[2]) {
            perm[0] = 2;
            perm[1] = 1;
            perm[2] = 3;
          } else if (x4[1] <= x4[2]) {
            perm[0] = 2;
            perm[1] = 3;
            perm[2] = 1;
          } else {
            perm[0] = 3;
            perm[1] = 2;
            perm[2] = 1;
          }
          i = (unsigned char)dim;
          for (k = 0; k < i; k++) {
            iidx_tmp = (wOffset_tmp - dim) + k;
            bLen = perm[k];
            iidx_data[iidx_tmp] = idx4[bLen - 1];
            vwork_data[iidx_tmp] = x4[bLen - 1];
          }
        }
        dim = bLen2 >> 1;
        for (k = 0; k < dim; k++) {
          i1 = wOffset_tmp + k;
          i2 = iidx_data[i1];
          iidx_tmp = (vwork_size - k) - 1;
          iidx_data[i1] = iidx_data[iidx_tmp];
          iidx_data[iidx_tmp] = i2;
          vwork_data[i1] = xwork_data[iidx_tmp];
          vwork_data[iidx_tmp] = xwork_data[i1];
        }
        if (((unsigned int)bLen2 & 1U) != 0U) {
          dim += wOffset_tmp;
          vwork_data[dim] = xwork_data[dim];
        }
        dim = 2;
        if (wOffset_tmp > 1) {
          if (vwork_size >= 256) {
            int nBlocks;
            nBlocks = wOffset_tmp >> 8;
            if (nBlocks > 0) {
              for (b = 0; b < nBlocks; b++) {
                double xwork[256];
                short iwork[256];
                i4 = (b << 8) - 1;
                for (b_b = 0; b_b < 6; b_b++) {
                  bLen = 1 << (b_b + 2);
                  bLen2 = bLen << 1;
                  i = 256 >> (b_b + 3);
                  for (k = 0; k < i; k++) {
                    i2 = (i4 + k * bLen2) + 1;
                    for (i1 = 0; i1 < bLen2; i1++) {
                      dim = i2 + i1;
                      iwork[i1] = (short)iidx_data[dim];
                      xwork[i1] = vwork_data[dim];
                    }
                    i3 = 0;
                    i1 = bLen;
                    dim = i2 - 1;
                    int exitg1;
                    do {
                      exitg1 = 0;
                      dim++;
                      if (xwork[i3] <= xwork[i1]) {
                        iidx_data[dim] = iwork[i3];
                        vwork_data[dim] = xwork[i3];
                        if (i3 + 1 < bLen) {
                          i3++;
                        } else {
                          exitg1 = 1;
                        }
                      } else {
                        iidx_data[dim] = iwork[i1];
                        vwork_data[dim] = xwork[i1];
                        if (i1 + 1 < bLen2) {
                          i1++;
                        } else {
                          dim -= i3;
                          for (i1 = i3 + 1; i1 <= bLen; i1++) {
                            iidx_tmp = dim + i1;
                            iidx_data[iidx_tmp] = iwork[i1 - 1];
                            vwork_data[iidx_tmp] = xwork[i1 - 1];
                          }
                          exitg1 = 1;
                        }
                      }
                    } while (exitg1 == 0);
                  }
                }
              }
              dim = nBlocks << 8;
              i1 = wOffset_tmp - dim;
              if (i1 > 0) {
                merge_block(iidx_data, vwork_data, dim, i1, 2, iwork_data,
                            xwork_data);
              }
              dim = 8;
            }
          }
          merge_block(iidx_data, vwork_data, 0, wOffset_tmp, dim, iwork_data,
                      xwork_data);
        }
      }
      for (k = 0; k < vwork_size; k++) {
        i = j + k * vstride;
        x_data[i] = vwork_data[k];
        idx_data[i] = iidx_data[k];
      }
    }
  }
  return idx_size;
}

/*
 * File trailer for sort.c
 *
 * [EOF]
 */
