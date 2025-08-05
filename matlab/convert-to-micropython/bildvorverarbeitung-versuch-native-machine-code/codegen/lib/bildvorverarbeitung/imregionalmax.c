/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * imregionalmax.c
 *
 * Code generation for function 'imregionalmax'
 *
 */

/* Include files */
#include "imregionalmax.h"
#include "rt_nonfinite.h"
#include "libmwimregionalmax.h"
#include <emmintrin.h>

/* Function Definitions */
void imregionalmax(const double varargin_1[921600], boolean_T BW[921600])
{
  __m128d r;
  double connSizeT[2];
  double imSizeT[2];
  int i;
  boolean_T conn[9];
  connSizeT[0] = 0.0;
  connSizeT[1] = 1.0;
  r = _mm_loadu_pd(&connSizeT[0]);
  _mm_storeu_pd(&imSizeT[0], _mm_add_pd(_mm_set1_pd(1280.0),
                                        _mm_mul_pd(_mm_set1_pd(-560.0), r)));
  for (i = 0; i < 9; i++) {
    conn[i] = true;
  }
  connSizeT[0] = 3.0;
  connSizeT[1] = 3.0;
  imregionalmax_real64(&varargin_1[0], &BW[0], 2.0, &imSizeT[0], &conn[0], 2.0,
                       &connSizeT[0]);
}

/* End of code generation (imregionalmax.c) */
