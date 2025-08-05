/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * imfindcircles.c
 *
 * Code generation for function 'imfindcircles'
 *
 */

/* Include files */
#include "imfindcircles.h"
#include "bildvorverarbeitung_emxutil.h"
#include "bildvorverarbeitung_types.h"
#include "chaccum.h"
#include "chcenters.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>

/* Function Definitions */
void imfindcircles(const unsigned char varargin_1[921600],
                   emxArray_real_T *centers, emxArray_real_T *r_estimated)
{
  static creal_T accumMatrix[921600];
  static float gradientImg[921600];
  emxArray_boolean_T *x;
  emxArray_creal_T *d_x;
  emxArray_int32_T *ii;
  emxArray_real_T *b_centers;
  emxArray_real_T *b_x;
  emxArray_real_T *c_x;
  emxArray_real_T *idx2Keep;
  emxArray_real_T *metric;
  creal_T *b_x_data;
  double e_x;
  double u0;
  double u1;
  double *centers_data;
  double *idx2Keep_data;
  double *r_estimated_data;
  int b_k;
  int c_k;
  int d_k;
  int i;
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  int k;
  int *ii_data;
  boolean_T exitg1;
  boolean_T y;
  boolean_T *x_data;
  centers->size[0] = 0;
  centers->size[1] = 0;
  r_estimated->size[0] = 0;
  r_estimated->size[1] = 0;
  chaccum(varargin_1, accumMatrix, gradientImg);
  y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 921600)) {
    if (((accumMatrix[k].re == 0.0) && (accumMatrix[k].im == 0.0)) ||
        (rtIsNaN(accumMatrix[k].re) || rtIsNaN(accumMatrix[k].im))) {
      k++;
    } else {
      y = true;
      exitg1 = true;
    }
  }
  emxInit_real_T(&idx2Keep, 1);
  emxInit_real_T(&metric, 2);
  emxInit_boolean_T(&x, 2);
  emxInit_int32_T(&ii, 1);
  emxInit_real_T(&b_x, 1);
  emxInit_real_T(&c_x, 1);
  emxInit_creal_T(&d_x, 1);
  emxInit_real_T(&b_centers, 2);
  if (y) {
    chcenters(accumMatrix, centers, metric);
    r_estimated_data = metric->data;
    centers_data = centers->data;
    if ((centers->size[0] != 0) && (centers->size[1] != 0)) {
      int b_nx;
      int idx;
      int nx;
      k = x->size[0] * x->size[1];
      x->size[0] = metric->size[0];
      x->size[1] = metric->size[1];
      emxEnsureCapacity_boolean_T(x, k);
      x_data = x->data;
      nx = metric->size[0] * metric->size[1];
      if (nx < 400) {
        for (i = 0; i < nx; i++) {
          x_data[i] = (r_estimated_data[i] >= 0.099999999999999978);
        }
      } else {
#pragma omp parallel for num_threads(omp_get_max_threads())

        for (i = 0; i < nx; i++) {
          x_data[i] = (r_estimated_data[i] >= 0.099999999999999978);
        }
      }
      idx = 0;
      k = ii->size[0];
      ii->size[0] = nx;
      emxEnsureCapacity_int32_T(ii, k);
      ii_data = ii->data;
      k = 0;
      exitg1 = false;
      while ((!exitg1) && (k <= nx - 1)) {
        if (x_data[k]) {
          idx++;
          ii_data[idx - 1] = k + 1;
          if (idx >= nx) {
            exitg1 = true;
          } else {
            k++;
          }
        } else {
          k++;
        }
      }
      if (nx == 1) {
        if (idx == 0) {
          ii->size[0] = 0;
        }
      } else {
        k = ii->size[0];
        if (idx < 1) {
          ii->size[0] = 0;
        } else {
          ii->size[0] = idx;
        }
        emxEnsureCapacity_int32_T(ii, k);
        ii_data = ii->data;
      }
      b_nx = ii->size[0];
      k = idx2Keep->size[0];
      idx2Keep->size[0] = ii->size[0];
      emxEnsureCapacity_real_T(idx2Keep, k);
      idx2Keep_data = idx2Keep->data;
      for (i1 = 0; i1 < b_nx; i1++) {
        idx2Keep_data[i1] = ii_data[i1];
      }
      nx = centers->size[1];
      k = b_centers->size[0] * b_centers->size[1];
      b_centers->size[0] = ii->size[0];
      b_centers->size[1] = centers->size[1];
      emxEnsureCapacity_real_T(b_centers, k);
      r_estimated_data = b_centers->data;
      for (i1 = 0; i1 < nx; i1++) {
        for (i2 = 0; i2 < b_nx; i2++) {
          r_estimated_data[i2 + b_centers->size[0] * i1] =
              centers_data[((int)idx2Keep_data[i2] + centers->size[0] * i1) -
                           1];
        }
      }
      k = centers->size[0] * centers->size[1];
      centers->size[0] = ii->size[0];
      centers->size[1] = nx;
      emxEnsureCapacity_real_T(centers, k);
      centers_data = centers->data;
      k = b_centers->size[0] * b_centers->size[1];
      for (i1 = 0; i1 < k; i1++) {
        centers_data[i1] = r_estimated_data[i1];
      }
      if (idx2Keep->size[0] == 0) {
        centers->size[0] = 0;
        centers->size[1] = 0;
      } else {
        k = b_x->size[0];
        b_x->size[0] = ii->size[0];
        emxEnsureCapacity_real_T(b_x, k);
        r_estimated_data = b_x->data;
        nx = ii->size[0];
        k = c_x->size[0];
        c_x->size[0] = ii->size[0];
        emxEnsureCapacity_real_T(c_x, k);
        idx2Keep_data = c_x->data;
        idx = (idx2Keep->size[0] < 400);
        if (idx) {
          for (b_k = 0; b_k < b_nx; b_k++) {
            e_x = centers_data[b_k + centers->size[0]];
            if (fabs(e_x) < 4.503599627370496E+15) {
              if (e_x >= 0.5) {
                e_x = floor(e_x + 0.5);
              } else if (e_x > -0.5) {
                e_x *= 0.0;
              } else {
                e_x = ceil(e_x - 0.5);
              }
            }
            r_estimated_data[b_k] = e_x;
            e_x = centers_data[b_k];
            if (fabs(e_x) < 4.503599627370496E+15) {
              if (e_x >= 0.5) {
                e_x = floor(e_x + 0.5);
              } else if (e_x > -0.5) {
                e_x *= 0.0;
              } else {
                e_x = ceil(e_x - 0.5);
              }
            }
            idx2Keep_data[b_k] = e_x;
          }
        } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(e_x)

          for (b_k = 0; b_k < nx; b_k++) {
            e_x = centers_data[b_k + centers->size[0]];
            if (fabs(e_x) < 4.503599627370496E+15) {
              if (e_x >= 0.5) {
                e_x = floor(e_x + 0.5);
              } else if (e_x > -0.5) {
                e_x *= 0.0;
              } else {
                e_x = ceil(e_x - 0.5);
              }
            }
            r_estimated_data[b_k] = e_x;
            e_x = centers_data[b_k];
            if (fabs(e_x) < 4.503599627370496E+15) {
              if (e_x >= 0.5) {
                e_x = floor(e_x + 0.5);
              } else if (e_x > -0.5) {
                e_x *= 0.0;
              } else {
                e_x = ceil(e_x - 0.5);
              }
            }
            idx2Keep_data[b_k] = e_x;
          }
        }
        k = d_x->size[0];
        d_x->size[0] = b_nx;
        emxEnsureCapacity_creal_T(d_x, k);
        b_x_data = d_x->data;
        if (idx) {
          for (i3 = 0; i3 < b_nx; i3++) {
            b_x_data[i3] = accumMatrix[((int)r_estimated_data[i3] +
                                        1280 * ((int)idx2Keep_data[i3] - 1)) -
                                       1];
          }
        } else {
#pragma omp parallel for num_threads(omp_get_max_threads())

          for (i3 = 0; i3 < b_nx; i3++) {
            b_x_data[i3] = accumMatrix[((int)r_estimated_data[i3] +
                                        1280 * ((int)idx2Keep_data[i3] - 1)) -
                                       1];
          }
        }
        k = idx2Keep->size[0];
        idx2Keep->size[0] = b_nx;
        emxEnsureCapacity_real_T(idx2Keep, k);
        idx2Keep_data = idx2Keep->data;
        if (idx) {
          for (c_k = 0; c_k < b_nx; c_k++) {
            u0 = b_x_data[c_k].im;
            u1 = b_x_data[c_k].re;
            if (rtIsNaN(u0) || rtIsNaN(u1)) {
              idx2Keep_data[c_k] = rtNaN;
            } else if (rtIsInf(u0) && rtIsInf(u1)) {
              if (u0 > 0.0) {
                k = 1;
              } else {
                k = -1;
              }
              if (u1 > 0.0) {
                nx = 1;
              } else {
                nx = -1;
              }
              idx2Keep_data[c_k] = atan2(k, nx);
            } else if (u1 == 0.0) {
              if (u0 > 0.0) {
                idx2Keep_data[c_k] = RT_PI / 2.0;
              } else if (u0 < 0.0) {
                idx2Keep_data[c_k] = -(RT_PI / 2.0);
              } else {
                idx2Keep_data[c_k] = 0.0;
              }
            } else {
              idx2Keep_data[c_k] = atan2(u0, u1);
            }
          }
        } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        i4, i5, u1, u0)

          for (c_k = 0; c_k < b_nx; c_k++) {
            u0 = b_x_data[c_k].im;
            u1 = b_x_data[c_k].re;
            if (rtIsNaN(u0) || rtIsNaN(u1)) {
              idx2Keep_data[c_k] = rtNaN;
            } else if (rtIsInf(u0) && rtIsInf(u1)) {
              if (u1 > 0.0) {
                i5 = 1;
              } else {
                i5 = -1;
              }
              if (u0 > 0.0) {
                i4 = 1;
              } else {
                i4 = -1;
              }
              idx2Keep_data[c_k] = atan2(i4, i5);
            } else if (u1 == 0.0) {
              if (u0 > 0.0) {
                idx2Keep_data[c_k] = RT_PI / 2.0;
              } else if (u0 < 0.0) {
                idx2Keep_data[c_k] = -(RT_PI / 2.0);
              } else {
                idx2Keep_data[c_k] = 0.0;
              }
            } else {
              idx2Keep_data[c_k] = atan2(u0, u1);
            }
          }
        }
        k = (idx2Keep->size[0] / 2) << 1;
        nx = k - 2;
        for (i1 = 0; i1 <= nx; i1 += 2) {
          __m128d r;
          r = _mm_loadu_pd(&idx2Keep_data[i1]);
          _mm_storeu_pd(
              &idx2Keep_data[i1],
              _mm_add_pd(
                  _mm_mul_pd(
                      _mm_div_pd(_mm_add_pd(r, _mm_set1_pd(3.1415926535897931)),
                                 _mm_set1_pd(6.2831853071795862)),
                      _mm_set1_pd(1.2039728043259359)),
                  _mm_set1_pd(2.70805020110221)));
        }
        for (i1 = k; i1 < b_nx; i1++) {
          idx2Keep_data[i1] = (idx2Keep_data[i1] + 3.1415926535897931) /
                                  6.2831853071795862 * 1.2039728043259359 +
                              2.70805020110221;
        }
        nx = idx2Keep->size[0];
        if (idx2Keep->size[0] < 400) {
          for (d_k = 0; d_k < nx; d_k++) {
            idx2Keep_data[d_k] = exp(idx2Keep_data[d_k]);
          }
        } else {
#pragma omp parallel for num_threads(omp_get_max_threads())

          for (d_k = 0; d_k < nx; d_k++) {
            idx2Keep_data[d_k] = exp(idx2Keep_data[d_k]);
          }
        }
        k = r_estimated->size[0] * r_estimated->size[1];
        r_estimated->size[0] = nx;
        r_estimated->size[1] = 1;
        emxEnsureCapacity_real_T(r_estimated, k);
        r_estimated_data = r_estimated->data;
        for (i1 = 0; i1 < nx; i1++) {
          r_estimated_data[i1] = idx2Keep_data[i1];
        }
      }
    }
  }
  emxFree_real_T(&b_centers);
  emxFree_creal_T(&d_x);
  emxFree_real_T(&c_x);
  emxFree_real_T(&b_x);
  emxFree_int32_T(&ii);
  emxFree_boolean_T(&x);
  emxFree_real_T(&metric);
  emxFree_real_T(&idx2Keep);
}

/* End of code generation (imfindcircles.c) */
