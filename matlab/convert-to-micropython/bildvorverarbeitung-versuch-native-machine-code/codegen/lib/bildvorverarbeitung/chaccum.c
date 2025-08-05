/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * chaccum.c
 *
 * Code generation for function 'chaccum'
 *
 */

/* Include files */
#include "chaccum.h"
#include "bildvorverarbeitung_emxutil.h"
#include "bildvorverarbeitung_types.h"
#include "graythresh.h"
#include "imfilter.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>
#include <xmmintrin.h>

/* Function Definitions */
void chaccum(const unsigned char varargin_1[921600],
             creal_T accumMatrix[921600], float gradientImg[921600])
{
  static creal_T out[921600];
  static cuint8_T accumMatrix_tmp[921600];
  static const double dv[71] = {
      -3.1415926535897931,  -2.9704720666079436, -2.8047848068496704,
      -2.6441964339912492,  -2.4884024669150024, -2.3371249088846806,
      -2.1901092623422276,  -2.04712195280168,   -1.9079480963550781,
      -1.772389557217489,   -1.640263251236727,  -1.511399658914504,
      -1.3856415176371151,  -1.262842667806672,  -1.1428670316381808,
      -1.0255877067292847,  -0.910886159263188,  -0.79865150398524021,
      -0.68877985998915925, -0.581173772932003,  -0.4757416956237841,
      -0.37239752005449356, -0.2710601548644207, -0.17165314306304857,
      -0.07410431548171692, 0.02165452397476253, 0.1156878847159506,
      0.20805685050543277,  0.29881931779774362, 0.3880302137015339,
      0.4757416956237841,   0.56200333441215022, 0.64686228260563317,
      0.73036342922339337,  0.81254954236390642, 0.89346140074852265,
      0.97313791522232851,  1.0516162411185253,  1.1289318822985743,
      1.205118787597323,    1.2802094403288935,  1.354234941443984,
      1.4272250868713492,   1.4992084395249092,  1.5702123964118968,
      1.6402632512367266,   1.7093862528584989,  1.7776056599274401,
      1.8449447919960882,   1.9114260773747409,  1.9770710979768502,
      2.041900631378792,    2.1059346902990734,  2.1691925596846664,
      2.2316928315764617,   2.2934534379115181,  2.3544916814069046,
      2.4148242646582521,   2.4744673175753933,  2.5334364232678839,
      2.5917466424842921,   2.6494125367012,     2.7064481899503887,
      2.7628672294661447,   2.818682845228337,   2.8739078084714418,
      2.9285544892244149,   2.9826348729417465,  3.0361605762815724,
      3.0891428620828369,   3.1415926535897931};
  static const double dv1[71] = {
      94.247779607693786, 97.389372261283583, 100.53096491487338,
      103.67255756846318, 106.81415022205297, 109.95574287564276,
      113.09733552923255, 116.23892818282235, 119.38052083641213,
      122.52211349000193, 125.66370614359172, 128.80529879718151,
      131.94689145077132, 135.0884841043611,  138.23007675795088,
      141.37166941154069, 144.51326206513048, 147.65485471872029,
      150.79644737231007, 153.93804002589985, 157.07963267948966,
      160.22122533307945, 163.36281798666926, 166.50441064025904,
      169.64600329384882, 172.78759594743863, 175.92918860102841,
      179.0707812546182,  182.212373908208,   185.35396656179779,
      188.49555921538757, 191.63715186897738, 194.77874452256717,
      197.92033717615698, 201.06192982974676, 204.20352248333654,
      207.34511513692635, 210.48670779051614, 213.62830044410595,
      216.76989309769573, 219.91148575128551, 223.05307840487532,
      226.1946710584651,  229.33626371205489, 232.4778563656447,
      235.61944901923448, 238.76104167282426, 241.90263432641407,
      245.04422698000386, 248.18581963359367, 251.32741228718345,
      254.46900494077323, 257.610597594363,   260.75219024795285,
      263.89378290154264, 267.03537555513242, 270.1769682087222,
      273.318560862312,   276.46015351590177, 279.60174616949161,
      282.74333882308139, 285.88493147667117, 289.02652413026095,
      292.16811678385073, 295.30970943744057, 298.45130209103036,
      301.59289474462014, 304.73448739820992, 307.8760800517997,
      311.01767270538954, 314.15926535897933};
  static float A[921600];
  static float Gx[921600];
  static float Gy[921600];
  static boolean_T x[921600];
  emxArray_boolean_T *inside;
  emxArray_boolean_T *rows_to_keep;
  emxArray_creal_T *w;
  emxArray_creal_T *wkeep;
  emxArray_int16_T *Ex_chunk;
  emxArray_int16_T *b_jj;
  emxArray_int32_T *Ey_chunk;
  emxArray_int32_T *idxE_chunk;
  emxArray_int32_T *ii;
  emxArray_int32_T *ndx;
  emxArray_int32_T *xckeep;
  emxArray_int32_T *yckeep;
  emxArray_real32_T *xc;
  emxArray_real32_T *yc;
  emxArray_real_T *y;
  creal_T *w_data;
  creal_T *wkeep_data;
  float a;
  float b;
  float *xc_data;
  float *yc_data;
  int b_i;
  int b_k;
  int i;
  int i1;
  int i2;
  int idx;
  int idx1;
  int k;
  int *Ey_chunk_data;
  int *idxE_chunk_data;
  int *ii_data;
  int *ndx_data;
  short *Ex_chunk_data;
  short *jj_data;
  boolean_T exitg1;
  boolean_T flat;
  boolean_T *inside_data;
  boolean_T *rows_to_keep_data;
  idx = varargin_1[0];
#pragma omp parallel for num_threads(omp_get_max_threads())

  for (i = 0; i < 921600; i++) {
    x[i] = (varargin_1[i] == idx);
  }
  flat = true;
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (idx < 921600)) {
    if (!x[idx]) {
      flat = false;
      exitg1 = true;
    } else {
      idx++;
    }
  }
  if (flat) {
    memset(&accumMatrix[0], 0, 921600U * sizeof(creal_T));
    memset(&gradientImg[0], 0, 921600U * sizeof(float));
  } else {
    creal_T Opca[71];
    double b_b;
    float Gmax;
    float f;
    int b_idx;
    int i3;
    int jj;
#pragma omp parallel for num_threads(omp_get_max_threads())

    for (i1 = 0; i1 < 921600; i1++) {
      A[i1] = (float)varargin_1[i1] / 255.0F;
    }
    imfilter(A, Gx);
    b_imfilter(A, Gy);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(b, a)

    for (k = 0; k < 921600; k++) {
      a = fabsf(Gx[k]);
      b = fabsf(Gy[k]);
      if (a < b) {
        a /= b;
        gradientImg[k] = b * sqrtf(a * a + 1.0F);
      } else if (a > b) {
        b /= a;
        gradientImg[k] = a * sqrtf(b * b + 1.0F);
      } else if (rtIsNaNF(b)) {
        gradientImg[k] = rtNaNF;
      } else {
        gradientImg[k] = a * 1.41421354F;
      }
    }
    if (!rtIsNaNF(gradientImg[0])) {
      idx = 1;
    } else {
      idx = 0;
      jj = 2;
      exitg1 = false;
      while ((!exitg1) && (jj < 921601)) {
        if (!rtIsNaNF(gradientImg[jj - 1])) {
          idx = jj;
          exitg1 = true;
        } else {
          jj++;
        }
      }
    }
    if (idx == 0) {
      Gmax = gradientImg[0];
    } else {
      Gmax = gradientImg[idx - 1];
      idx++;
      for (b_k = idx; b_k < 921601; b_k++) {
        f = gradientImg[b_k - 1];
        if (Gmax < f) {
          Gmax = f;
        }
      }
    }
    for (b_k = 0; b_k <= 921596; b_k += 4) {
      __m128 r;
      r = _mm_loadu_ps(&gradientImg[b_k]);
      _mm_storeu_ps(&A[b_k], _mm_div_ps(r, _mm_set1_ps(Gmax)));
    }
    b_b = graythresh(A);
    Gmax *= (float)b_b;
    b_idx = 0;
    emxInit_int32_T(&ii, 1);
    idx = ii->size[0];
    ii->size[0] = 921600;
    emxEnsureCapacity_int32_T(ii, idx);
    ii_data = ii->data;
    emxInit_int16_T(&b_jj);
    idx = b_jj->size[0];
    b_jj->size[0] = 921600;
    emxEnsureCapacity_int16_T(b_jj, idx);
    jj_data = b_jj->data;
    idx = 1;
    jj = 1;
    exitg1 = false;
    while ((!exitg1) && (jj <= 720)) {
      boolean_T guard1;
      guard1 = false;
      if (gradientImg[(idx + 1280 * (jj - 1)) - 1] > Gmax) {
        b_idx++;
        ii_data[b_idx - 1] = idx;
        jj_data[b_idx - 1] = (short)jj;
        if (b_idx >= 921600) {
          exitg1 = true;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
      if (guard1) {
        idx++;
        if (idx > 1280) {
          idx = 1;
          jj++;
        }
      }
    }
    if (b_idx < 1) {
      b_idx = 0;
    }
    idx = ii->size[0];
    ii->size[0] = b_idx;
    emxEnsureCapacity_int32_T(ii, idx);
    ii_data = ii->data;
    idx = b_jj->size[0];
    b_jj->size[0] = b_idx;
    emxEnsureCapacity_int16_T(b_jj, idx);
    jj_data = b_jj->data;
    emxInit_int32_T(&ndx, 1);
    idx = ndx->size[0];
    ndx->size[0] = b_idx;
    emxEnsureCapacity_int32_T(ndx, idx);
    ndx_data = ndx->data;
    if (b_idx < 400) {
      for (i2 = 0; i2 < b_idx; i2++) {
        ndx_data[i2] = ii_data[i2] + 1280 * (jj_data[i2] - 1);
      }
    } else {
#pragma omp parallel for num_threads(omp_get_max_threads())

      for (i2 = 0; i2 < b_idx; i2++) {
        ndx_data[i2] = ii_data[i2] + 1280 * (jj_data[i2] - 1);
      }
    }
    for (b_k = 0; b_k < 71; b_k++) {
      double br;
      double im;
      double re;
      im = dv[b_k];
      b_b = cos(im);
      im = sin(im);
      br = dv1[b_k];
      if (im == 0.0) {
        re = b_b / br;
        b_b = 0.0;
      } else if (b_b == 0.0) {
        re = 0.0;
        b_b = im / br;
      } else {
        re = b_b / br;
        b_b = im / br;
      }
      Opca[b_k].re = re;
      Opca[b_k].im = b_b;
    }
    memset(&accumMatrix_tmp[0], 0, 921600U * sizeof(cuint8_T));
    memset(&accumMatrix[0], 0, 921600U * sizeof(creal_T));
    i3 = (int)(((double)b_jj->size[0] + 14083.0) / 14084.0);
    emxInit_int16_T(&Ex_chunk);
    emxInit_int32_T(&Ey_chunk, 1);
    emxInit_int32_T(&idxE_chunk, 1);
    emxInit_real32_T(&xc);
    emxInit_real32_T(&yc);
    emxInit_creal_T(&w, 2);
    emxInit_boolean_T(&inside, 2);
    emxInit_boolean_T(&rows_to_keep, 1);
    emxInit_int32_T(&xckeep, 1);
    emxInit_int32_T(&yckeep, 1);
    emxInit_creal_T(&wkeep, 1);
    emxInit_real_T(&y, 2);
    for (b_i = 0; b_i < i3; b_i++) {
      int loop_ub;
      b_idx = b_i * 14084;
      idx = (int)fmin(((double)(b_idx + 1) + 14084.0) - 1.0, b_jj->size[0]);
      if (idx < b_idx + 1) {
        y->size[1] = 0;
      } else {
        jj = y->size[0] * y->size[1];
        y->size[1] = idx - b_idx;
        emxEnsureCapacity_real_T(y, jj);
      }
      loop_ub = y->size[1];
      idx = Ex_chunk->size[0];
      Ex_chunk->size[0] = y->size[1];
      emxEnsureCapacity_int16_T(Ex_chunk, idx);
      Ex_chunk_data = Ex_chunk->data;
      idx = Ey_chunk->size[0];
      Ey_chunk->size[0] = y->size[1];
      emxEnsureCapacity_int32_T(Ey_chunk, idx);
      Ey_chunk_data = Ey_chunk->data;
      idx = idxE_chunk->size[0];
      idxE_chunk->size[0] = y->size[1];
      emxEnsureCapacity_int32_T(idxE_chunk, idx);
      idxE_chunk_data = idxE_chunk->data;
      for (b_k = 0; b_k < loop_ub; b_k++) {
        idx = b_idx + b_k;
        Ex_chunk_data[b_k] = jj_data[idx];
        Ey_chunk_data[b_k] = ii_data[idx];
        idxE_chunk_data[b_k] = ndx_data[idx];
      }
      idx = xc->size[0] * xc->size[1];
      xc->size[0] = y->size[1];
      xc->size[1] = 71;
      emxEnsureCapacity_real32_T(xc, idx);
      xc_data = xc->data;
      idx = yc->size[0] * yc->size[1];
      yc->size[0] = y->size[1];
      yc->size[1] = 71;
      emxEnsureCapacity_real32_T(yc, idx);
      yc_data = yc->data;
      idx = w->size[0] * w->size[1];
      w->size[0] = y->size[1];
      w->size[1] = 71;
      emxEnsureCapacity_creal_T(w, idx);
      w_data = w->data;
      idx = inside->size[0] * inside->size[1];
      inside->size[0] = y->size[1];
      inside->size[1] = 71;
      emxEnsureCapacity_boolean_T(inside, idx);
      inside_data = inside->data;
      idx = rows_to_keep->size[0];
      rows_to_keep->size[0] = y->size[1];
      emxEnsureCapacity_boolean_T(rows_to_keep, idx);
      rows_to_keep_data = rows_to_keep->data;
      for (b_k = 0; b_k < loop_ub; b_k++) {
        rows_to_keep_data[b_k] = false;
      }
      for (b_k = 0; b_k < 71; b_k++) {
        for (idx1 = 0; idx1 < loop_ub; idx1++) {
          float f1;
          Gmax = (float)-(0.5 * (double)b_k + 15.0);
          f = gradientImg[idxE_chunk_data[idx1] - 1];
          f1 = roundf((float)Ex_chunk_data[idx1] +
                      Gmax * (Gx[idxE_chunk_data[idx1] - 1] / f));
          xc_data[idx1 + xc->size[0] * b_k] = f1;
          Gmax = roundf((float)Ey_chunk_data[idx1] +
                        Gmax * (Gy[idxE_chunk_data[idx1] - 1] / f));
          yc_data[idx1 + yc->size[0] * b_k] = Gmax;
          w_data[idx1 + w->size[0] * b_k] = Opca[b_k];
          flat = ((f1 >= 1.0F) && (f1 <= 720.0F) && (Gmax >= 1.0F) &&
                  (Gmax <= 1280.0F));
          inside_data[idx1 + inside->size[0] * b_k] = flat;
          if (flat) {
            rows_to_keep_data[idx1] = true;
          }
        }
      }
      jj = xc->size[0] * 71;
      idx = xckeep->size[0];
      xckeep->size[0] = jj;
      emxEnsureCapacity_int32_T(xckeep, idx);
      Ey_chunk_data = xckeep->data;
      idx = yckeep->size[0];
      yckeep->size[0] = jj;
      emxEnsureCapacity_int32_T(yckeep, idx);
      idxE_chunk_data = yckeep->data;
      idx = wkeep->size[0];
      wkeep->size[0] = jj;
      emxEnsureCapacity_creal_T(wkeep, idx);
      wkeep_data = wkeep->data;
      jj = -1;
      for (b_k = 0; b_k < 71; b_k++) {
        for (idx1 = 0; idx1 < loop_ub; idx1++) {
          if (rows_to_keep_data[idx1] &&
              inside_data[idx1 + inside->size[0] * b_k]) {
            jj++;
            Ey_chunk_data[jj] = (int)xc_data[idx1 + xc->size[0] * b_k];
            idxE_chunk_data[jj] = (int)yc_data[idx1 + yc->size[0] * b_k];
            wkeep_data[jj] = w_data[idx1 + w->size[0] * b_k];
          }
        }
      }
      for (b_k = 0; b_k < 921600; b_k++) {
        out[b_k].re = 0.0;
        out[b_k].im = accumMatrix_tmp[b_k].im;
      }
      for (b_k = 0; b_k <= jj; b_k++) {
        idx = (idxE_chunk_data[b_k] + 1280 * (Ey_chunk_data[b_k] - 1)) - 1;
        out[idx].re += wkeep_data[b_k].re;
        out[idx].im += wkeep_data[b_k].im;
      }
      for (b_k = 0; b_k < 921600; b_k++) {
        accumMatrix[b_k].re += out[b_k].re;
        accumMatrix[b_k].im += out[b_k].im;
      }
    }
    emxFree_int16_T(&b_jj);
    emxFree_int32_T(&ii);
    emxFree_real_T(&y);
    emxFree_int32_T(&ndx);
    emxFree_creal_T(&wkeep);
    emxFree_int32_T(&yckeep);
    emxFree_int32_T(&xckeep);
    emxFree_boolean_T(&rows_to_keep);
    emxFree_boolean_T(&inside);
    emxFree_creal_T(&w);
    emxFree_real32_T(&yc);
    emxFree_real32_T(&xc);
    emxFree_int32_T(&idxE_chunk);
    emxFree_int32_T(&Ey_chunk);
    emxFree_int16_T(&Ex_chunk);
  }
}

/* End of code generation (chaccum.c) */
