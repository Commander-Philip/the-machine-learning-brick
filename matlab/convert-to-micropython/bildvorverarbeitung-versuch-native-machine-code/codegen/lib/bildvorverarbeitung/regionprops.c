/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * regionprops.c
 *
 * Code generation for function 'regionprops'
 *
 */

/* Include files */
#include "regionprops.h"
#include "bildvorverarbeitung_emxutil.h"
#include "bildvorverarbeitung_types.h"
#include "bwconncomp.h"
#include "rt_nonfinite.h"
#include "sum.h"
#include "omp.h"
#include <emmintrin.h>
#include <string.h>

/* Function Declarations */
static void binary_expand_op(double in1[2], int in2,
                             const b_emxArray_struct_T *in3, int in4,
                             double in5);

/* Function Definitions */
static void binary_expand_op(double in1[2], int in2,
                             const b_emxArray_struct_T *in3, int in4,
                             double in5)
{
  const b_struct_T *in3_data;
  emxArray_real_T *b_in3;
  double *b_in3_data;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  in3_data = in3->data;
  stride_1_0 = in3_data[in4].PixelList->size[0];
  emxInit_real_T(&b_in3, 1);
  i = in3_data[in4].PixelValues->size[0];
  if (i == 1) {
    loop_ub = stride_1_0;
  } else {
    loop_ub = i;
  }
  stride_0_0 = b_in3->size[0];
  b_in3->size[0] = loop_ub;
  emxEnsureCapacity_real_T(b_in3, stride_0_0);
  b_in3_data = b_in3->data;
  stride_0_0 = (stride_1_0 != 1);
  stride_1_0 = (i != 1);
  if (loop_ub < 400) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_in3_data[i1] =
          in3_data[in4]
              .PixelList
              ->data[i1 * stride_0_0 + in3_data[in4].PixelList->size[0] * in2] *
          in3_data[in4].PixelValues->data[i1 * stride_1_0];
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads())

    for (i1 = 0; i1 < loop_ub; i1++) {
      b_in3_data[i1] =
          in3_data[in4]
              .PixelList
              ->data[i1 * stride_0_0 + in3_data[in4].PixelList->size[0] * in2] *
          in3_data[in4].PixelValues->data[i1 * stride_1_0];
    }
  }
  in1[in2] = sum(b_in3) / in5;
  emxFree_real_T(&b_in3);
}

void regionprops(const boolean_T varargin_1[921600],
                 const double varargin_2[921600], emxArray_struct_T *outstats)
{
  __m128i r1;
  __m128i r3;
  b_emxArray_struct_T *stats;
  b_struct_T statsOneObj;
  b_struct_T *stats_data;
  emxArray_cell_wrap_42 *expl_temp;
  emxArray_int32_T *idxCount;
  emxArray_int32_T *regionLengths;
  emxArray_real_T *CC_RegionIndices;
  struct_T s;
  struct_T *outstats_data;
  double wc[2];
  double sumIntensity;
  double *CC_RegionIndices_data;
  int b_iv[4];
  int b_k;
  int b_loop_ub;
  int c_loop_ub;
  int d_loop_ub;
  int k;
  int loop_ub;
  int n;
  int *idxCount_data;
  int *regionLengths_data;
  emxInit_real_T(&CC_RegionIndices, 1);
  emxInit_int32_T(&regionLengths, 1);
  emxInit_cell_wrap_42(&expl_temp);
  bwconncomp(varargin_1, wc, CC_RegionIndices, regionLengths, expl_temp,
             &sumIntensity);
  regionLengths_data = regionLengths->data;
  CC_RegionIndices_data = CC_RegionIndices->data;
  emxFree_cell_wrap_42(&expl_temp);
  s.WeightedCentroid[0] = 0.0;
  s.WeightedCentroid[1] = 0.0;
  loop_ub = (int)sumIntensity;
  b_loop_ub = outstats->size[0];
  outstats->size[0] = (int)sumIntensity;
  emxEnsureCapacity_struct_T(outstats, b_loop_ub);
  outstats_data = outstats->data;
  for (k = 0; k < loop_ub; k++) {
    outstats_data[k] = s;
  }
  emxInitStruct_struct_T(&statsOneObj);
  statsOneObj.Area = 0.0;
  statsOneObj.Centroid[0] = 0.0;
  statsOneObj.Centroid[1] = 0.0;
  statsOneObj.BoundingBox[0] = 0.0;
  statsOneObj.BoundingBox[1] = 0.0;
  statsOneObj.BoundingBox[2] = 0.0;
  statsOneObj.BoundingBox[3] = 0.0;
  statsOneObj.MajorAxisLength = 0.0;
  statsOneObj.MinorAxisLength = 0.0;
  statsOneObj.Eccentricity = 0.0;
  statsOneObj.Orientation = 0.0;
  statsOneObj.Image.size[0] = 0;
  statsOneObj.Image.size[1] = 0;
  statsOneObj.FilledImage.size[0] = 0;
  statsOneObj.FilledImage.size[1] = 0;
  statsOneObj.FilledArea = 0.0;
  statsOneObj.EulerNumber = 0.0;
  memset(&statsOneObj.Extrema[0], 0, 16U * sizeof(double));
  statsOneObj.EquivDiameter = 0.0;
  statsOneObj.Extent = 0.0;
  statsOneObj.PixelIdxList->size[0] = 0;
  statsOneObj.PixelList->size[0] = 0;
  statsOneObj.PixelList->size[1] = 2;
  statsOneObj.Perimeter = 0.0;
  statsOneObj.Circularity = 0.0;
  statsOneObj.PixelValues->size[0] = 0;
  statsOneObj.MeanIntensity = 0.0;
  statsOneObj.MinIntensity = 0.0;
  statsOneObj.MaxIntensity = 0.0;
  statsOneObj.SubarrayIdx.size[0] = 1;
  statsOneObj.SubarrayIdx.size[1] = 0;
  statsOneObj.WeightedCentroid[0] = 0.0;
  statsOneObj.SubarrayIdxLengths[0] = 0.0;
  statsOneObj.WeightedCentroid[1] = 0.0;
  statsOneObj.SubarrayIdxLengths[1] = 0.0;
  emxInit_struct_T1(&stats);
  b_loop_ub = stats->size[0];
  stats->size[0] = (int)sumIntensity;
  emxEnsureCapacity_struct_T1(stats, b_loop_ub);
  stats_data = stats->data;
  for (k = 0; k < loop_ub; k++) {
    emxCopyStruct_struct_T(&stats_data[k], &statsOneObj);
  }
  emxFreeStruct_struct_T(&statsOneObj);
  emxInit_int32_T(&idxCount, 1);
  if (sumIntensity != 0.0) {
    if ((regionLengths->size[0] != 1) && (regionLengths->size[0] != 0) &&
        (regionLengths->size[0] != 1)) {
      b_loop_ub = regionLengths->size[0];
      for (k = 0; k <= b_loop_ub - 2; k++) {
        regionLengths_data[k + 1] += regionLengths_data[k];
      }
    }
    b_loop_ub = idxCount->size[0];
    idxCount->size[0] = regionLengths->size[0] + 1;
    emxEnsureCapacity_int32_T(idxCount, b_loop_ub);
    idxCount_data = idxCount->data;
    idxCount_data[0] = 0;
    b_loop_ub = regionLengths->size[0];
    for (k = 0; k < b_loop_ub; k++) {
      idxCount_data[k + 1] = regionLengths_data[k];
    }
    for (b_k = 0; b_k < loop_ub; b_k++) {
      b_loop_ub = idxCount_data[b_k + 1];
      if (idxCount_data[b_k] + 1 > b_loop_ub) {
        c_loop_ub = 0;
        b_loop_ub = 0;
      } else {
        c_loop_ub = idxCount_data[b_k];
      }
      d_loop_ub = b_loop_ub - c_loop_ub;
      b_loop_ub = stats_data[b_k].PixelIdxList->size[0];
      stats_data[b_k].PixelIdxList->size[0] = d_loop_ub;
      emxEnsureCapacity_real_T(stats_data[b_k].PixelIdxList, b_loop_ub);
      for (k = 0; k < d_loop_ub; k++) {
        stats_data[b_k].PixelIdxList->data[k] =
            CC_RegionIndices_data[c_loop_ub + k];
      }
    }
  }
  for (b_k = 0; b_k < loop_ub; b_k++) {
    c_loop_ub = stats_data[b_k].PixelIdxList->size[0];
    if (c_loop_ub != 0) {
      b_loop_ub = regionLengths->size[0];
      regionLengths->size[0] = c_loop_ub;
      emxEnsureCapacity_int32_T(regionLengths, b_loop_ub);
      regionLengths_data = regionLengths->data;
      for (k = 0; k < c_loop_ub; k++) {
        regionLengths_data[k] = (int)stats_data[b_k].PixelIdxList->data[k] - 1;
      }
      b_loop_ub = idxCount->size[0];
      idxCount->size[0] = c_loop_ub;
      emxEnsureCapacity_int32_T(idxCount, b_loop_ub);
      idxCount_data = idxCount->data;
      d_loop_ub = (regionLengths->size[0] / 4) << 2;
      b_loop_ub = d_loop_ub - 4;
      for (k = 0; k <= b_loop_ub; k += 4) {
        b_iv[0] = regionLengths_data[k] / 1280;
        b_iv[1] = regionLengths_data[k + 1] / 1280;
        b_iv[2] = regionLengths_data[k + 2] / 1280;
        b_iv[3] = regionLengths_data[k + 3] / 1280;
        r1 = _mm_loadu_si128((const __m128i *)&b_iv[0]);
        _mm_storeu_si128((__m128i *)&idxCount_data[k], r1);
        b_iv[0] *= 1280;
        b_iv[1] *= 1280;
        b_iv[2] *= 1280;
        b_iv[3] *= 1280;
        r1 = _mm_loadu_si128((const __m128i *)&regionLengths_data[k]);
        r3 = _mm_loadu_si128((const __m128i *)&b_iv[0]);
        _mm_storeu_si128((__m128i *)&regionLengths_data[k],
                         _mm_sub_epi32(r1, r3));
      }
      for (k = d_loop_ub; k < c_loop_ub; k++) {
        b_loop_ub = regionLengths_data[k] / 1280;
        idxCount_data[k] = b_loop_ub;
        regionLengths_data[k] -= b_loop_ub * 1280;
      }
      d_loop_ub = idxCount->size[0];
      b_loop_ub = stats_data[b_k].PixelList->size[0] *
                  stats_data[b_k].PixelList->size[1];
      stats_data[b_k].PixelList->size[0] = idxCount->size[0];
      stats_data[b_k].PixelList->size[1] = 2;
      emxEnsureCapacity_real_T(stats_data[b_k].PixelList, b_loop_ub);
      for (k = 0; k < d_loop_ub; k++) {
        stats_data[b_k].PixelList->data[k] = idxCount_data[k] + 1;
        stats_data[b_k]
            .PixelList->data[k + stats_data[b_k].PixelList->size[0]] =
            regionLengths_data[k] + 1;
      }
    } else {
      stats_data[b_k].PixelList->size[0] = 0;
      stats_data[b_k].PixelList->size[1] = 2;
    }
  }
  for (b_k = 0; b_k < loop_ub; b_k++) {
    d_loop_ub = stats_data[b_k].PixelIdxList->size[0];
    b_loop_ub = stats_data[b_k].PixelValues->size[0];
    stats_data[b_k].PixelValues->size[0] = d_loop_ub;
    emxEnsureCapacity_real_T(stats_data[b_k].PixelValues, b_loop_ub);
    c_loop_ub = stats_data[b_k].PixelIdxList->size[0];
    b_loop_ub = regionLengths->size[0];
    regionLengths->size[0] = c_loop_ub;
    emxEnsureCapacity_int32_T(regionLengths, b_loop_ub);
    regionLengths_data = regionLengths->data;
    for (k = 0; k < d_loop_ub; k++) {
      regionLengths_data[k] = (int)stats_data[b_k].PixelIdxList->data[k] - 1;
    }
    b_loop_ub = idxCount->size[0];
    idxCount->size[0] = c_loop_ub;
    emxEnsureCapacity_int32_T(idxCount, b_loop_ub);
    idxCount_data = idxCount->data;
    d_loop_ub = (regionLengths->size[0] / 4) << 2;
    b_loop_ub = d_loop_ub - 4;
    for (k = 0; k <= b_loop_ub; k += 4) {
      b_iv[0] = regionLengths_data[k] / 1280;
      b_iv[1] = regionLengths_data[k + 1] / 1280;
      b_iv[2] = regionLengths_data[k + 2] / 1280;
      b_iv[3] = regionLengths_data[k + 3] / 1280;
      r1 = _mm_loadu_si128((const __m128i *)&b_iv[0]);
      _mm_storeu_si128((__m128i *)&idxCount_data[k], r1);
      b_iv[0] *= 1280;
      b_iv[1] *= 1280;
      b_iv[2] *= 1280;
      b_iv[3] *= 1280;
      r1 = _mm_loadu_si128((const __m128i *)&regionLengths_data[k]);
      r3 = _mm_loadu_si128((const __m128i *)&b_iv[0]);
      _mm_storeu_si128((__m128i *)&regionLengths_data[k],
                       _mm_sub_epi32(r1, r3));
    }
    for (k = d_loop_ub; k < c_loop_ub; k++) {
      b_loop_ub = regionLengths_data[k] / 1280;
      idxCount_data[k] = b_loop_ub;
      regionLengths_data[k] -= b_loop_ub * 1280;
    }
    b_loop_ub = regionLengths->size[0];
    d_loop_ub = (regionLengths->size[0] / 4) << 2;
    c_loop_ub = d_loop_ub - 4;
    for (k = 0; k <= c_loop_ub; k += 4) {
      r1 = _mm_loadu_si128((const __m128i *)&regionLengths_data[k]);
      r3 = _mm_set1_epi32(1);
      _mm_storeu_si128((__m128i *)&regionLengths_data[k],
                       _mm_add_epi32(r1, r3));
      r1 = _mm_loadu_si128((const __m128i *)&idxCount_data[k]);
      _mm_storeu_si128((__m128i *)&idxCount_data[k], _mm_add_epi32(r1, r3));
    }
    for (k = d_loop_ub; k < b_loop_ub; k++) {
      regionLengths_data[k]++;
      idxCount_data[k]++;
    }
    b_loop_ub = stats_data[b_k].PixelValues->size[0];
    for (k = 0; k < b_loop_ub; k++) {
      stats_data[b_k].PixelValues->data[k] =
          varargin_2[(regionLengths_data[k] + 1280 * (idxCount_data[k] - 1)) -
                     1];
    }
  }
  emxFree_int32_T(&idxCount);
  emxFree_int32_T(&regionLengths);
  for (b_k = 0; b_k < loop_ub; b_k++) {
    sumIntensity = sum(stats_data[b_k].PixelValues);
    for (n = 0; n < 2; n++) {
      c_loop_ub = stats_data[b_k].PixelList->size[0];
      if (c_loop_ub == stats_data[b_k].PixelValues->size[0]) {
        b_loop_ub = CC_RegionIndices->size[0];
        CC_RegionIndices->size[0] = c_loop_ub;
        emxEnsureCapacity_real_T(CC_RegionIndices, b_loop_ub);
        CC_RegionIndices_data = CC_RegionIndices->data;
        b_loop_ub = (c_loop_ub / 2) << 1;
        d_loop_ub = b_loop_ub - 2;
        for (k = 0; k <= d_loop_ub; k += 2) {
          __m128d r;
          __m128d r2;
          r = _mm_loadu_pd(
              &stats_data[b_k]
                   .PixelList
                   ->data[k + stats_data[b_k].PixelList->size[0] * n]);
          r2 = _mm_loadu_pd(&stats_data[b_k].PixelValues->data[k]);
          _mm_storeu_pd(&CC_RegionIndices_data[k], _mm_mul_pd(r, r2));
        }
        for (k = b_loop_ub; k < c_loop_ub; k++) {
          CC_RegionIndices_data[k] =
              stats_data[b_k]
                  .PixelList->data[k + stats_data[b_k].PixelList->size[0] * n] *
              stats_data[b_k].PixelValues->data[k];
        }
        wc[n] = sum(CC_RegionIndices) / sumIntensity;
      } else {
        binary_expand_op(wc, n, stats, b_k, sumIntensity);
      }
    }
    stats_data[b_k].WeightedCentroid[0] = wc[0];
    stats_data[b_k].WeightedCentroid[1] = wc[1];
  }
  emxFree_real_T(&CC_RegionIndices);
  b_loop_ub = stats->size[0];
  for (k = 0; k < b_loop_ub; k++) {
    outstats_data[k].WeightedCentroid[0] = stats_data[k].WeightedCentroid[0];
    outstats_data[k].WeightedCentroid[1] = stats_data[k].WeightedCentroid[1];
  }
  emxFree_struct_T1(&stats);
}

/* End of code generation (regionprops.c) */
