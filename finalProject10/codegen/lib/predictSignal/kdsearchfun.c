/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: kdsearchfun.c
 *
 * MATLAB Coder version            : 24.2
 * C/C++ source code generated on  : 15-Nov-2024 10:15:10
 */

/* Include Files */
#include "kdsearchfun.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Type Definitions */
#ifndef struct_emxArray_real_T_312
#define struct_emxArray_real_T_312
struct emxArray_real_T_312 {
  double data[312];
  int size[1];
};
#endif /* struct_emxArray_real_T_312 */
#ifndef typedef_emxArray_real_T_312
#define typedef_emxArray_real_T_312
typedef struct emxArray_real_T_312 emxArray_real_T_312;
#endif /* typedef_emxArray_real_T_312 */

#ifndef struct_emxArray_uint32_T_312
#define struct_emxArray_uint32_T_312
struct emxArray_uint32_T_312 {
  unsigned int data[312];
};
#endif /* struct_emxArray_uint32_T_312 */
#ifndef typedef_emxArray_uint32_T_312
#define typedef_emxArray_uint32_T_312
typedef struct emxArray_uint32_T_312 emxArray_uint32_T_312;
#endif /* typedef_emxArray_uint32_T_312 */

#ifndef typedef_b_struct_T
#define typedef_b_struct_T
typedef struct {
  emxArray_real_T_312 D;
  emxArray_uint32_T_312 b_I;
} b_struct_T;
#endif /* typedef_b_struct_T */

/* Function Declarations */
static int getNodeFromArray(const unsigned int idxAll[312],
                            const double idxDim_data[], double this_node,
                            unsigned int node_idx_this_data[]);

static void search_node(const double X[936], const double queryPt[3],
                        const unsigned int node_idx_start_data[],
                        int node_idx_start_size, int numNN, b_struct_T *pq);

/* Function Definitions */
/*
 * Arguments    : const unsigned int idxAll[312]
 *                const double idxDim_data[]
 *                double this_node
 *                unsigned int node_idx_this_data[]
 * Return Type  : int
 */
static int getNodeFromArray(const unsigned int idxAll[312],
                            const double idxDim_data[], double this_node,
                            unsigned int node_idx_this_data[])
{
  double d;
  int k;
  int node_idx_this_size;
  d = idxDim_data[(int)this_node - 1];
  if (d == 0.0) {
    node_idx_this_size = 0;
  } else if (this_node == 1.0) {
    if (idxDim_data[0] < 1.0) {
      node_idx_this_size = 0;
    } else {
      node_idx_this_size = (int)idxDim_data[0];
    }
    if (node_idx_this_size - 1 >= 0) {
      memcpy(&node_idx_this_data[0], &idxAll[0],
             (unsigned int)node_idx_this_size * sizeof(unsigned int));
    }
  } else {
    double y;
    int vlen;
    vlen = (int)(this_node - 1.0);
    y = idxDim_data[0];
    for (k = 2; k <= vlen; k++) {
      y += idxDim_data[k - 1];
    }
    k = (int)y + (int)d;
    if ((int)y + 1 > k) {
      vlen = 0;
      k = 0;
    } else {
      vlen = (int)y;
    }
    node_idx_this_size = k - vlen;
    for (k = 0; k < node_idx_this_size; k++) {
      node_idx_this_data[k] = idxAll[vlen + k];
    }
  }
  return node_idx_this_size;
}

/*
 * Arguments    : const double X[936]
 *                const double queryPt[3]
 *                const unsigned int node_idx_start_data[]
 *                int node_idx_start_size
 *                int numNN
 *                b_struct_T *pq
 * Return Type  : void
 */
static void search_node(const double X[936], const double queryPt[3],
                        const unsigned int node_idx_start_data[],
                        int node_idx_start_size, int numNN, b_struct_T *pq)
{
  double diffAllDim_data[936];
  double tmp_data[315];
  double aDistOut_data[312];
  unsigned int b_tmp_data[315];
  int iidx_data[312];
  int aDistOut_size;
  int acoef;
  int b_k;
  int i;
  int k;
  if (node_idx_start_size != 0) {
    acoef = (node_idx_start_size != 1);
    for (k = 0; k < 3; k++) {
      for (b_k = 0; b_k < node_idx_start_size; b_k++) {
        diffAllDim_data[b_k + node_idx_start_size * k] =
            X[((int)node_idx_start_data[acoef * b_k] + 312 * k) - 1] -
            queryPt[k];
      }
    }
  }
  acoef = node_idx_start_size * 3;
  for (i = 0; i < acoef; i++) {
    double d;
    d = diffAllDim_data[i];
    d *= d;
    diffAllDim_data[i] = d;
  }
  if (node_idx_start_size == 0) {
    aDistOut_size = 0;
  } else {
    aDistOut_size = node_idx_start_size;
    memcpy(&aDistOut_data[0], &diffAllDim_data[0],
           (unsigned int)node_idx_start_size * sizeof(double));
    for (k = 0; k < 2; k++) {
      acoef = (k + 1) * node_idx_start_size;
      for (b_k = 0; b_k < node_idx_start_size; b_k++) {
        aDistOut_data[b_k] += diffAllDim_data[acoef + b_k];
      }
    }
  }
  acoef = sort(aDistOut_data, &aDistOut_size, iidx_data);
  if (pq->D.size[0] == 0) {
    if (aDistOut_size <= numNN) {
      pq->D.size[0] = aDistOut_size;
      if (aDistOut_size - 1 >= 0) {
        memcpy(&pq->D.data[0], &aDistOut_data[0],
               (unsigned int)aDistOut_size * sizeof(double));
      }
      for (i = 0; i < acoef; i++) {
        pq->b_I.data[i] = node_idx_start_data[iidx_data[i] - 1];
      }
    } else {
      pq->D.size[0] = numNN;
      for (i = 0; i < numNN; i++) {
        pq->D.data[i] = aDistOut_data[i];
        pq->b_I.data[i] = node_idx_start_data[iidx_data[i] - 1];
      }
    }
  } else {
    int cD1;
    int cD2;
    bool exitg1;
    cD1 = 0;
    cD2 = 0;
    acoef = pq->D.size[0] + aDistOut_size;
    if (acoef > numNN) {
      b_k = numNN;
    } else {
      b_k = acoef;
    }
    if (b_k - 1 >= 0) {
      memset(&tmp_data[0], 0, (unsigned int)b_k * sizeof(double));
      memset(&b_tmp_data[0], 0, (unsigned int)b_k * sizeof(unsigned int));
    }
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= (unsigned short)b_k - 1)) {
      if (pq->D.data[cD1] <= aDistOut_data[cD2]) {
        tmp_data[k] = pq->D.data[cD1];
        b_tmp_data[k] = pq->b_I.data[cD1];
        cD1++;
        if (cD1 + 1 > pq->D.size[0]) {
          i = k + 2;
          for (aDistOut_size = i; aDistOut_size <= b_k; aDistOut_size++) {
            acoef = ((cD2 + aDistOut_size) - k) - 2;
            tmp_data[aDistOut_size - 1] = aDistOut_data[acoef];
            b_tmp_data[aDistOut_size - 1] =
                node_idx_start_data[iidx_data[acoef] - 1];
          }
          exitg1 = true;
        } else {
          k++;
        }
      } else {
        tmp_data[k] = aDistOut_data[cD2];
        b_tmp_data[k] = node_idx_start_data[iidx_data[cD2] - 1];
        cD2++;
        if (cD2 + 1 > aDistOut_size) {
          i = k + 2;
          for (aDistOut_size = i; aDistOut_size <= b_k; aDistOut_size++) {
            acoef = ((cD1 + aDistOut_size) - k) - 2;
            tmp_data[aDistOut_size - 1] = pq->D.data[acoef];
            b_tmp_data[aDistOut_size - 1] = pq->b_I.data[acoef];
          }
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    pq->D.size[0] = b_k;
    if (b_k - 1 >= 0) {
      memcpy(&pq->D.data[0], &tmp_data[0], (unsigned int)b_k * sizeof(double));
      memcpy(&pq->b_I.data[0], &b_tmp_data[0],
             (unsigned int)b_k * sizeof(unsigned int));
    }
  }
}

/*
 * Arguments    : const double obj_X[936]
 *                const int obj_wasnanIdx_data[]
 *                const double obj_cutDim_data[]
 *                const double obj_cutVal_data[]
 *                const double obj_lowerBounds_data[]
 *                const int obj_lowerBounds_size[2]
 *                const double obj_upperBounds_data[]
 *                const int obj_upperBounds_size[2]
 *                const double obj_leftChild_data[]
 *                const double obj_rightChild_data[]
 *                const bool obj_leafNode_data[]
 *                double obj_nx_nonan
 *                const unsigned int obj_idxAll[312]
 *                const double obj_idxDim_data[]
 *                const double Y[3]
 *                int idx_data[]
 *                int idx_size[2]
 *                double dist_data[]
 *                int dist_size[2]
 * Return Type  : void
 */
void kdsearchfunCG(
    const double obj_X[936], const int obj_wasnanIdx_data[],
    const double obj_cutDim_data[], const double obj_cutVal_data[],
    const double obj_lowerBounds_data[], const int obj_lowerBounds_size[2],
    const double obj_upperBounds_data[], const int obj_upperBounds_size[2],
    const double obj_leftChild_data[], const double obj_rightChild_data[],
    const bool obj_leafNode_data[], double obj_nx_nonan,
    const unsigned int obj_idxAll[312], const double obj_idxDim_data[],
    const double Y[3], int idx_data[], int idx_size[2], double dist_data[],
    int dist_size[2])
{
  b_struct_T r;
  double b_obj_rightChild_data[32];
  double nodeStack_data[32];
  double minval_tmp;
  unsigned int tmp_data[312];
  int i;
  int j;
  int k;
  int n_tmp;
  int nodeStack_size;
  int yk;
  short noNanCol_data[3];
  bool x_data[312];
  bool exitg1;
  bool wasNaNY;
  x_data[0] = rtIsNaN(Y[0]);
  x_data[1] = rtIsNaN(Y[1]);
  x_data[2] = rtIsNaN(Y[2]);
  wasNaNY = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= 2)) {
    if (x_data[k]) {
      wasNaNY = true;
      exitg1 = true;
    } else {
      k++;
    }
  }
  minval_tmp = fmin(3.0, obj_nx_nonan);
  if ((int)minval_tmp > 0) {
    idx_size[0] = 1;
    idx_size[1] = 3;
    dist_size[0] = 1;
    dist_size[1] = 3;
    idx_data[0] = 0;
    dist_data[0] = 0.0;
    idx_data[1] = 0;
    dist_data[1] = 0.0;
    idx_data[2] = 0;
    dist_data[2] = 0.0;
    n_tmp = (unsigned char)((int)minval_tmp - 1) + 1;
    noNanCol_data[0] = 1;
    yk = 1;
    for (k = 2; k <= n_tmp; k++) {
      yk++;
      noNanCol_data[k - 1] = (short)yk;
    }
    for (j = 0; j < 1; j++) {
      if (wasNaNY) {
        for (i = 0; i < n_tmp; i++) {
          short i1;
          i1 = noNanCol_data[i];
          dist_data[i1 - 1] = rtNaN;
          idx_data[(short)(i1 - 1)] = i1;
        }
      } else {
        double b_pRadIn[3];
        double pRadIn[3];
        double currentNode;
        double start_node;
        bool ballIsWithinBounds;
        start_node = 1.0;
        while (!obj_leafNode_data[(int)start_node - 1]) {
          if (Y[(int)obj_cutDim_data[(int)start_node - 1] - 1] <=
              obj_cutVal_data[(int)start_node - 1]) {
            start_node = obj_leftChild_data[(int)start_node - 1];
          } else {
            start_node = obj_rightChild_data[(int)start_node - 1];
          }
        }
        r.D.size[0] = 0;
        yk =
            getNodeFromArray(obj_idxAll, obj_idxDim_data, start_node, tmp_data);
        search_node(obj_X, Y, tmp_data, yk, (int)minval_tmp, &r);
        if (r.D.size[0] != 0) {
          currentNode = Y[0] - obj_lowerBounds_data[(int)start_node - 1];
          b_pRadIn[0] = Y[0] - obj_upperBounds_data[(int)start_node - 1];
          currentNode *= currentNode;
          pRadIn[0] = currentNode;
          currentNode =
              Y[1] -
              obj_lowerBounds_data[((int)start_node + obj_lowerBounds_size[0]) -
                                   1];
          b_pRadIn[1] =
              Y[1] -
              obj_upperBounds_data[((int)start_node + obj_upperBounds_size[0]) -
                                   1];
          currentNode *= currentNode;
          pRadIn[1] = currentNode;
          currentNode =
              Y[2] - obj_lowerBounds_data[((int)start_node +
                                           obj_lowerBounds_size[0] * 2) -
                                          1];
          b_pRadIn[2] =
              Y[2] - obj_upperBounds_data[((int)start_node +
                                           obj_upperBounds_size[0] * 2) -
                                          1];
          currentNode *= currentNode;
          pRadIn[2] = currentNode;
          currentNode = r.D.data[r.D.size[0] - 1];
          if (minimum(pRadIn) <= currentNode) {
            ballIsWithinBounds = false;
          } else {
            b_pRadIn[0] *= b_pRadIn[0];
            b_pRadIn[1] *= b_pRadIn[1];
            b_pRadIn[2] *= b_pRadIn[2];
            if (minimum(b_pRadIn) <= currentNode) {
              ballIsWithinBounds = false;
            } else {
              ballIsWithinBounds = true;
            }
          }
        } else {
          ballIsWithinBounds = false;
        }
        if ((r.D.size[0] != (int)minval_tmp) || (!ballIsWithinBounds)) {
          nodeStack_size = 1;
          nodeStack_data[0] = 1.0;
          while (nodeStack_size != 0) {
            double sumDist;
            currentNode = nodeStack_data[0];
            for (k = 0; k <= nodeStack_size - 2; k++) {
              nodeStack_data[k] = nodeStack_data[k + 1];
            }
            k = nodeStack_size - 1;
            nodeStack_size--;
            pRadIn[0] = obj_lowerBounds_data[(int)currentNode - 1];
            b_pRadIn[0] = obj_upperBounds_data[(int)currentNode - 1];
            pRadIn[1] = obj_lowerBounds_data[((int)currentNode +
                                              obj_lowerBounds_size[0]) -
                                             1];
            b_pRadIn[1] = obj_upperBounds_data[((int)currentNode +
                                                obj_upperBounds_size[0]) -
                                               1];
            pRadIn[2] = obj_lowerBounds_data[((int)currentNode +
                                              obj_lowerBounds_size[0] * 2) -
                                             1];
            b_pRadIn[2] = obj_upperBounds_data[((int)currentNode +
                                                obj_upperBounds_size[0] * 2) -
                                               1];
            ballIsWithinBounds = true;
            sumDist = 0.0;
            yk = 0;
            exitg1 = false;
            while ((!exitg1) && (yk < 3)) {
              if (Y[yk] < pRadIn[yk]) {
                double c_pRadIn;
                c_pRadIn = Y[yk] - pRadIn[yk];
                sumDist += c_pRadIn * c_pRadIn;
              } else if (Y[yk] > b_pRadIn[yk]) {
                double c_pRadIn;
                c_pRadIn = Y[yk] - b_pRadIn[yk];
                sumDist += c_pRadIn * c_pRadIn;
              }
              if (sumDist > r.D.data[r.D.size[0] - 1]) {
                ballIsWithinBounds = false;
                exitg1 = true;
              } else {
                yk++;
              }
            }
            if ((r.D.size[0] < (int)minval_tmp) || ballIsWithinBounds) {
              if (!obj_leafNode_data[(int)currentNode - 1]) {
                if (Y[(int)obj_cutDim_data[(int)currentNode - 1] - 1] <=
                    obj_cutVal_data[(int)currentNode - 1]) {
                  yk = k + 2;
                  b_obj_rightChild_data[0] =
                      obj_leftChild_data[(int)currentNode - 1];
                  b_obj_rightChild_data[1] =
                      obj_rightChild_data[(int)currentNode - 1];
                  if (k - 1 >= 0) {
                    memcpy(&b_obj_rightChild_data[2], &nodeStack_data[0],
                           (unsigned int)k * sizeof(double));
                  }
                  nodeStack_size = k + 2;
                  memcpy(&nodeStack_data[0], &b_obj_rightChild_data[0],
                         (unsigned int)yk * sizeof(double));
                } else {
                  yk = k + 2;
                  b_obj_rightChild_data[0] =
                      obj_rightChild_data[(int)currentNode - 1];
                  b_obj_rightChild_data[1] =
                      obj_leftChild_data[(int)currentNode - 1];
                  if (k - 1 >= 0) {
                    memcpy(&b_obj_rightChild_data[2], &nodeStack_data[0],
                           (unsigned int)k * sizeof(double));
                  }
                  nodeStack_size = k + 2;
                  memcpy(&nodeStack_data[0], &b_obj_rightChild_data[0],
                         (unsigned int)yk * sizeof(double));
                }
              } else if (currentNode != start_node) {
                yk = getNodeFromArray(obj_idxAll, obj_idxDim_data, currentNode,
                                      tmp_data);
                search_node(obj_X, Y, tmp_data, yk, (int)minval_tmp, &r);
              }
            }
          }
        }
        i = r.D.size[0];
        for (k = 0; k < i; k++) {
          r.D.data[k] = sqrt(r.D.data[k]);
        }
        for (i = 0; i < n_tmp; i++) {
          unsigned int u;
          short i1;
          i1 = noNanCol_data[i];
          dist_data[(short)(i1 - 1)] = r.D.data[i];
          u = r.b_I.data[i];
          if (u > 2147483647U) {
            u = 2147483647U;
          }
          idx_data[(short)(i1 - 1)] = (int)u;
        }
      }
    }
  } else {
    idx_size[0] = 1;
    idx_size[1] = 0;
    dist_size[0] = 1;
    dist_size[1] = 0;
  }
  if (3 - (int)minval_tmp > 0) {
    if ((int)minval_tmp + 1 > 3) {
      i = 0;
      n_tmp = 0;
    } else {
      i = (int)minval_tmp;
      n_tmp = 3;
    }
    yk = n_tmp - i;
    for (n_tmp = 0; n_tmp < yk; n_tmp++) {
      idx_data[i + n_tmp] = obj_wasnanIdx_data[n_tmp];
    }
    if (wasNaNY) {
      if ((int)minval_tmp + 1 > 3) {
        i = -1;
        n_tmp = -1;
        k = 0;
        yk = 0;
      } else {
        i = (int)minval_tmp - 1;
        n_tmp = 2;
        k = (int)minval_tmp;
        yk = 3;
      }
      n_tmp -= i;
      for (nodeStack_size = 0; nodeStack_size < n_tmp; nodeStack_size++) {
        noNanCol_data[nodeStack_size] =
            (short)((short)((i + nodeStack_size) + 1) + 1);
      }
      yk -= k;
      for (i = 0; i < yk; i++) {
        idx_data[k + i] = noNanCol_data[i];
      }
    }
    if ((int)minval_tmp + 1 > 3) {
      i = 0;
      n_tmp = 0;
    } else {
      i = (int)minval_tmp;
      n_tmp = 3;
    }
    yk = n_tmp - i;
    for (n_tmp = 0; n_tmp < yk; n_tmp++) {
      dist_data[i + n_tmp] = rtNaN;
    }
  }
}

/*
 * File trailer for kdsearchfun.c
 *
 * [EOF]
 */
