/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * imhmax.c
 *
 * Code generation for function 'imhmax'
 *
 */

/* Include files */
#include "imhmax.h"
#include "rt_nonfinite.h"
#include "libmwippreconstruct.h"
#include <emmintrin.h>

/* Function Definitions */
void imhmax(const double b_I[921600], double J[921600])
{
  double dv[2];
  double imSizeT[2];
  int i;
  for (i = 0; i <= 921598; i += 2) {
    _mm_storeu_pd(&J[i], _mm_sub_pd(_mm_loadu_pd(&b_I[i]),
                                    _mm_set1_pd(0.099999999999999964)));
  }
  __m128d r;
  dv[0] = 0.0;
  dv[1] = 1.0;
  r = _mm_loadu_pd(&dv[0]);
  _mm_storeu_pd(&imSizeT[0], _mm_add_pd(_mm_set1_pd(1280.0),
                                        _mm_mul_pd(_mm_set1_pd(-560.0), r)));
  ippreconstruct_real64(&J[0], &b_I[0], &imSizeT[0], 2.0);
}

/* End of code generation (imhmax.c) */
