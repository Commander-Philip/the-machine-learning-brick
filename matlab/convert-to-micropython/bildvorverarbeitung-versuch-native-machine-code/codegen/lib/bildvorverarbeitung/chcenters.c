/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * chcenters.c
 *
 * Code generation for function 'chcenters'
 *
 */

/* Include files */
#include "chcenters.h"
#include "bildvorverarbeitung_emxutil.h"
#include "bildvorverarbeitung_types.h"
#include "imhmax.h"
#include "imregionalmax.h"
#include "medfilt2.h"
#include "regionprops.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "omp.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
void chcenters(const creal_T varargin_1[921600], emxArray_real_T *centers,
               emxArray_real_T *metric)
{
  static double Hd[921600];
  static double accumMatrixRe[921600];
  static double b_Hd[921600];
  static boolean_T bw[921600];
  emxArray_int32_T *iidx;
  emxArray_real_T *b_x;
  emxArray_real_T *x;
  emxArray_struct_T *s;
  struct_T *s_data;
  double a;
  double b;
  double b_accumMatrixRe;
  double c_x;
  double *b_x_data;
  double *centers_data;
  double *metric_data;
  double *x_data;
  int b_i;
  int b_idx;
  int b_k;
  int c_k;
  int i;
  int idx;
  int k;
  int *iidx_data;
  boolean_T exitg1;
  boolean_T flat;
  centers->size[0] = 0;
  centers->size[1] = 0;
  metric->size[0] = 0;
  metric->size[1] = 0;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(b, a)

  for (k = 0; k < 921600; k++) {
    a = fabs(varargin_1[k].re);
    b = fabs(varargin_1[k].im);
    if (a < b) {
      a /= b;
      accumMatrixRe[k] = b * sqrt(a * a + 1.0);
    } else if (a > b) {
      b /= a;
      accumMatrixRe[k] = a * sqrt(b * b + 1.0);
    } else if (rtIsNaN(b)) {
      accumMatrixRe[k] = rtNaN;
    } else {
      accumMatrixRe[k] = a * 1.4142135623730951;
    }
  }
  b_accumMatrixRe = accumMatrixRe[0];
#pragma omp parallel for num_threads(omp_get_max_threads())

  for (i = 0; i < 921600; i++) {
    bw[i] = (accumMatrixRe[i] == b_accumMatrixRe);
  }
  flat = true;
  b_k = 0;
  exitg1 = false;
  while ((!exitg1) && (b_k < 921600)) {
    if (!bw[b_k]) {
      flat = false;
      exitg1 = true;
    } else {
      b_k++;
    }
  }
  if (!flat) {
    medfilt2(accumMatrixRe, Hd);
    memcpy(&b_Hd[0], &Hd[0], 921600U * sizeof(double));
    imhmax(b_Hd, Hd);
    imregionalmax(Hd, bw);
    emxInit_struct_T(&s);
    regionprops(bw, accumMatrixRe, s);
    s_data = s->data;
    if (s->size[0] != 0) {
      int i1;
      int loop_ub;
      int nrows;
      i1 = s->size[0];
      b_k = centers->size[0] * centers->size[1];
      centers->size[0] = s->size[0];
      centers->size[1] = 2;
      emxEnsureCapacity_real_T(centers, b_k);
      centers_data = centers->data;
      for (idx = 0; idx < i1; idx++) {
        centers_data[idx] = s_data[idx].WeightedCentroid[0];
        centers_data[idx + centers->size[0]] = s_data[idx].WeightedCentroid[1];
      }
      loop_ub = centers->size[0] - 1;
      for (b_idx = 0; b_idx < i1; b_idx++) {
        b_k = loop_ub - b_idx;
        if (rtIsNaN(centers_data[b_k]) ||
            rtIsNaN(centers_data[b_k + centers->size[0]])) {
          nrows = centers->size[0];
          for (idx = 0; idx < 2; idx++) {
            for (b_i = b_k + 1; b_i < nrows; b_i++) {
              centers_data[(b_i + centers->size[0] * idx) - 1] =
                  centers_data[b_i + centers->size[0] * idx];
            }
          }
          if (centers->size[0] - 1 < 1) {
            nrows = 0;
          } else {
            nrows = centers->size[0] - 1;
          }
          for (idx = 0; idx < 2; idx++) {
            for (b_i = 0; b_i < nrows; b_i++) {
              centers_data[b_i + nrows * idx] =
                  centers_data[b_i + centers->size[0] * idx];
            }
          }
          b_k = centers->size[0] * centers->size[1];
          centers->size[0] = nrows;
          centers->size[1] = 2;
          emxEnsureCapacity_real_T(centers, b_k);
          centers_data = centers->data;
        }
      }
      if (centers->size[0] != 0) {
        emxInit_real_T(&x, 1);
        loop_ub = centers->size[0];
        b_k = x->size[0];
        x->size[0] = centers->size[0];
        emxEnsureCapacity_real_T(x, b_k);
        x_data = x->data;
        nrows = centers->size[0];
        emxInit_real_T(&b_x, 1);
        b_k = b_x->size[0];
        b_x->size[0] = centers->size[0];
        emxEnsureCapacity_real_T(b_x, b_k);
        b_x_data = b_x->data;
        if (centers->size[0] < 400) {
          for (c_k = 0; c_k < loop_ub; c_k++) {
            c_x = centers_data[c_k + centers->size[0]];
            if (fabs(c_x) < 4.503599627370496E+15) {
              if (c_x >= 0.5) {
                c_x = floor(c_x + 0.5);
              } else if (c_x > -0.5) {
                c_x *= 0.0;
              } else {
                c_x = ceil(c_x - 0.5);
              }
            }
            x_data[c_k] = c_x;
            c_x = centers_data[c_k];
            if (fabs(c_x) < 4.503599627370496E+15) {
              if (c_x >= 0.5) {
                c_x = floor(c_x + 0.5);
              } else if (c_x > -0.5) {
                c_x *= 0.0;
              } else {
                c_x = ceil(c_x - 0.5);
              }
            }
            b_x_data[c_k] = c_x;
          }
        } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(c_x)

          for (c_k = 0; c_k < nrows; c_k++) {
            c_x = centers_data[c_k + centers->size[0]];
            if (fabs(c_x) < 4.503599627370496E+15) {
              if (c_x >= 0.5) {
                c_x = floor(c_x + 0.5);
              } else if (c_x > -0.5) {
                c_x *= 0.0;
              } else {
                c_x = ceil(c_x - 0.5);
              }
            }
            x_data[c_k] = c_x;
            c_x = centers_data[c_k];
            if (fabs(c_x) < 4.503599627370496E+15) {
              if (c_x >= 0.5) {
                c_x = floor(c_x + 0.5);
              } else if (c_x > -0.5) {
                c_x *= 0.0;
              } else {
                c_x = ceil(c_x - 0.5);
              }
            }
            b_x_data[c_k] = c_x;
          }
        }
        b_k = metric->size[0] * metric->size[1];
        metric->size[0] = loop_ub;
        metric->size[1] = 1;
        emxEnsureCapacity_real_T(metric, b_k);
        metric_data = metric->data;
        for (idx = 0; idx < loop_ub; idx++) {
          metric_data[idx] =
              Hd[((int)x_data[idx] + 1280 * ((int)b_x_data[idx] - 1)) - 1];
        }
        emxFree_real_T(&b_x);
        emxFree_real_T(&x);
        emxInit_int32_T(&iidx, 2);
        sort(metric, iidx);
        iidx_data = iidx->data;
        emxInit_real_T(&metric, 2);
        nrows = iidx->size[0];
        b_k = metric->size[0] * metric->size[1];
        metric->size[0] = iidx->size[0];
        metric->size[1] = 2;
        emxEnsureCapacity_real_T(metric, b_k);
        x_data = metric->data;
        for (idx = 0; idx < 2; idx++) {
          for (b_i = 0; b_i < nrows; b_i++) {
            x_data[b_i + metric->size[0] * idx] =
                centers_data[(iidx_data[b_i] + centers->size[0] * idx) - 1];
          }
        }
        b_k = centers->size[0] * centers->size[1];
        centers->size[0] = iidx->size[0];
        emxFree_int32_T(&iidx);
        centers->size[1] = 2;
        emxEnsureCapacity_real_T(centers, b_k);
        centers_data = centers->data;
        b_k = metric->size[0] * 2;
        for (idx = 0; idx < b_k; idx++) {
          centers_data[idx] = x_data[idx];
        }
        emxFree_real_T(&metric);
      }
    }
    emxFree_struct_T(&s);
  }
}

/* End of code generation (chcenters.c) */
