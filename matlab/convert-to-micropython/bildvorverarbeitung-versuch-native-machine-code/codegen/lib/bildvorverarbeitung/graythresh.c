/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * graythresh.c
 *
 * Code generation for function 'graythresh'
 *
 */

/* Include files */
#include "graythresh.h"
#include "rt_nonfinite.h"
#include "libmwgetnumcores.h"
#include "libmwgrayto8.h"
#include "libmwtbbhist.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <string.h>

/* Function Definitions */
double graythresh(const float b_I[921600])
{
  static unsigned char c_I[921600];
  double counts[256];
  double localBins1[256];
  double localBins2[256];
  double localBins3[256];
  double idx;
  double level;
  double maxval;
  double num_maxval;
  double p;
  int i;
  int k;
  grayto8_real32(&b_I[0], &c_I[0], 921600.0);
  level = 1.0;
  getnumcores(&level);
  if (level > 1.0) {
    boolean_T nanFlag;
    boolean_T rngFlag;
    nanFlag = false;
    rngFlag = false;
    tbbhist_uint8(&c_I[0], 921600.0, 921600.0, 1.0, &counts[0], 256.0, 256.0,
                  &rngFlag, &nanFlag);
  } else {
    memset(&counts[0], 0, 256U * sizeof(double));
    memset(&localBins1[0], 0, 256U * sizeof(double));
    memset(&localBins2[0], 0, 256U * sizeof(double));
    memset(&localBins3[0], 0, 256U * sizeof(double));
    for (i = 0; i + 4 <= 921600; i += 4) {
      int localBins2_tmp;
      localBins1[c_I[i]]++;
      localBins2_tmp = c_I[i + 1];
      localBins2[localBins2_tmp]++;
      localBins2_tmp = c_I[i + 2];
      localBins3[localBins2_tmp]++;
      localBins2_tmp = c_I[i + 3];
      counts[localBins2_tmp]++;
    }
    while (i + 1 <= 921600) {
      counts[c_I[i]]++;
      i++;
    }
    for (k = 0; k <= 254; k += 2) {
      __m128d r;
      __m128d r1;
      __m128d r2;
      __m128d r3;
      r = _mm_loadu_pd(&counts[k]);
      r1 = _mm_loadu_pd(&localBins1[k]);
      r2 = _mm_loadu_pd(&localBins2[k]);
      r3 = _mm_loadu_pd(&localBins3[k]);
      _mm_storeu_pd(&counts[k],
                    _mm_add_pd(_mm_add_pd(_mm_add_pd(r, r1), r2), r3));
    }
  }
  level = 0.0;
  for (k = 0; k < 256; k++) {
    level += counts[k];
  }
  localBins1[0] = counts[0] / level;
  localBins2[0] = localBins1[0];
  for (k = 0; k < 255; k++) {
    p = counts[k + 1] / level;
    localBins1[k + 1] = localBins1[k] + p;
    localBins2[k + 1] = localBins2[k] + p * ((double)k + 2.0);
  }
  maxval = rtMinusInf;
  idx = 0.0;
  num_maxval = 0.0;
  for (k = 0; k < 255; k++) {
    level = localBins1[k];
    p = localBins2[255] * level - localBins2[k];
    level = p * p / (level * (1.0 - level));
    if (level > maxval) {
      maxval = level;
      idx = (double)k + 1.0;
      num_maxval = 1.0;
    } else if (level == maxval) {
      idx += (double)k + 1.0;
      num_maxval++;
    }
  }
  if (!rtIsInf(maxval)) {
    idx /= num_maxval;
    level = (idx - 1.0) / 255.0;
  } else {
    level = 0.0;
  }
  return level;
}

/* End of code generation (graythresh.c) */
