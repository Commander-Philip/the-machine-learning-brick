/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * medfilt2.c
 *
 * Code generation for function 'medfilt2'
 *
 */

/* Include files */
#include "medfilt2.h"
#include "rt_nonfinite.h"
#include "libmwordfilt2.h"
#include <emmintrin.h>
#include <string.h>

/* Function Definitions */
void medfilt2(const double varargin_1[921600], double b[921600])
{
  static double Apad[929616];
  static const int offsets[25] = {
      -2570, -2569, -2568, -2567, -2566, -1286, -1285, -1284, -1283,
      -1282, -2,    -1,    0,     1,     2,     1282,  1283,  1284,
      1285,  1286,  2566,  2567,  2568,  2569,  2570};
  double domainSizeT[2];
  double dv[2];
  double sizeB[2];
  double startIdxT[2];
  int j;
  for (j = 0; j < 2568; j++) {
    Apad[j] = 0.0;
    Apad[j + 927048] = 0.0;
  }
  for (j = 0; j < 720; j++) {
    int Apad_tmp;
    Apad_tmp = 1284 * (j + 2);
    Apad[Apad_tmp] = 0.0;
    Apad[Apad_tmp + 1282] = 0.0;
    Apad[Apad_tmp + 1] = 0.0;
    Apad[Apad_tmp + 1283] = 0.0;
    memcpy(&Apad[Apad_tmp + 2], &varargin_1[j * 1280], 1280U * sizeof(double));
  }
  __m128d r;
  _mm_storeu_pd(&startIdxT[0], _mm_set1_pd(2.0));
  _mm_storeu_pd(&domainSizeT[0], _mm_set1_pd(5.0));
  dv[0] = 0.0;
  dv[1] = 1.0;
  r = _mm_loadu_pd(&dv[0]);
  _mm_storeu_pd(&sizeB[0], _mm_add_pd(_mm_set1_pd(1280.0),
                                      _mm_mul_pd(_mm_set1_pd(-560.0), r)));
  ordfilt2_real64(&Apad[0], 1284.0, &startIdxT[0], &offsets[0], 25.0,
                  &domainSizeT[0], 12.0, &b[0], &sizeB[0], true);
}

/* End of code generation (medfilt2.c) */
