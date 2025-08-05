/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * bwconncomp.c
 *
 * Code generation for function 'bwconncomp'
 *
 */

/* Include files */
#include "bwconncomp.h"
#include "bildvorverarbeitung_emxutil.h"
#include "bildvorverarbeitung_types.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>

/* Function Definitions */
double bwconncomp(const boolean_T varargin_1[921600], double CC_ImageSize[2],
                  emxArray_real_T *CC_RegionIndices,
                  emxArray_int32_T *CC_RegionLengths,
                  emxArray_cell_wrap_42 *CC_PixelIdxList, double *CC_NumObjects)
{
  __m128d r;
  cell_wrap_42 *CC_PixelIdxList_data;
  emxArray_int16_T *endRow;
  emxArray_int16_T *startCol;
  emxArray_int16_T *startRow_tmp;
  emxArray_int32_T *idxCount;
  emxArray_int32_T *labelsRenumbered;
  emxArray_int32_T *r1;
  emxArray_int32_T *x;
  double dv[2];
  double CC_Connectivity;
  double *CC_RegionIndices_data;
  int col;
  int k;
  int numComponents;
  int numRuns;
  int root_k;
  int root_p;
  int row;
  int runCounter;
  int *CC_RegionLengths_data;
  int *idxCount_data;
  int *labelsRenumbered_data;
  int *r2;
  int *x_data;
  short *endRow_data;
  short *startCol_data;
  short *startRow_tmp_data;
  dv[0] = 0.0;
  dv[1] = 1.0;
  r = _mm_loadu_pd(&dv[0]);
  _mm_storeu_pd(
      &CC_ImageSize[0],
      _mm_add_pd(_mm_set1_pd(1280.0), _mm_mul_pd(_mm_set1_pd(-560.0), r)));
  numRuns = 0;
  for (col = 0; col < 720; col++) {
    if (varargin_1[1280 * col]) {
      numRuns++;
    }
    for (k = 0; k < 1279; k++) {
      runCounter = k + 1280 * col;
      if (varargin_1[runCounter + 1] && (!varargin_1[runCounter])) {
        numRuns++;
      }
    }
  }
  emxInit_int32_T(&r1, 1);
  r2 = r1->data;
  emxInit_int16_T(&endRow);
  emxInit_int16_T(&startCol);
  emxInit_int16_T(&startRow_tmp);
  if (numRuns == 0) {
    numComponents = 0;
    r1->size[0] = 0;
    runCounter = CC_RegionLengths->size[0];
    CC_RegionLengths->size[0] = 1;
    emxEnsureCapacity_int32_T(CC_RegionLengths, runCounter);
    CC_RegionLengths_data = CC_RegionLengths->data;
    CC_RegionLengths_data[0] = 0;
    CC_PixelIdxList->size[0] = 1;
    CC_PixelIdxList->size[1] = 0;
  } else {
    int firstRunOnPreviousColumn;
    int firstRunOnThisColumn;
    int lastRunOnPreviousColumn;
    int nextLabel;
    runCounter = startRow_tmp->size[0];
    startRow_tmp->size[0] = numRuns;
    emxEnsureCapacity_int16_T(startRow_tmp, runCounter);
    startRow_tmp_data = startRow_tmp->data;
    runCounter = endRow->size[0];
    endRow->size[0] = numRuns;
    emxEnsureCapacity_int16_T(endRow, runCounter);
    endRow_data = endRow->data;
    runCounter = startCol->size[0];
    startCol->size[0] = numRuns;
    emxEnsureCapacity_int16_T(startCol, runCounter);
    startCol_data = startCol->data;
    runCounter = 0;
    for (col = 0; col < 720; col++) {
      row = 1;
      while (row <= 1280) {
        while ((row <= 1280) && (!varargin_1[(row + 1280 * col) - 1])) {
          row++;
        }
        if ((row <= 1280) && varargin_1[(row + 1280 * col) - 1]) {
          startCol_data[runCounter] = (short)(col + 1);
          startRow_tmp_data[runCounter] = (short)row;
          while ((row <= 1280) && varargin_1[(row + 1280 * col) - 1]) {
            row++;
          }
          endRow_data[runCounter] = (short)(row - 1);
          runCounter++;
        }
      }
    }
    runCounter = CC_RegionLengths->size[0];
    CC_RegionLengths->size[0] = numRuns;
    emxEnsureCapacity_int32_T(CC_RegionLengths, runCounter);
    CC_RegionLengths_data = CC_RegionLengths->data;
    for (col = 0; col < numRuns; col++) {
      CC_RegionLengths_data[col] = 0;
    }
    runCounter = 0;
    row = 1;
    nextLabel = 1;
    firstRunOnPreviousColumn = -1;
    lastRunOnPreviousColumn = -1;
    firstRunOnThisColumn = 0;
    while (runCounter < numRuns) {
      if (startCol_data[runCounter] == row + 1) {
        firstRunOnPreviousColumn = firstRunOnThisColumn + 1;
        firstRunOnThisColumn = runCounter;
        lastRunOnPreviousColumn = runCounter;
        row = startCol_data[runCounter];
      } else if (startCol_data[runCounter] > row + 1) {
        firstRunOnPreviousColumn = -1;
        lastRunOnPreviousColumn = -1;
        firstRunOnThisColumn = runCounter;
        row = startCol_data[runCounter];
      }
      if (firstRunOnPreviousColumn >= 0) {
        for (numComponents = firstRunOnPreviousColumn - 1;
             numComponents < lastRunOnPreviousColumn; numComponents++) {
          if ((endRow_data[runCounter] >=
               startRow_tmp_data[numComponents] - 1) &&
              (startRow_tmp_data[runCounter] <=
               endRow_data[numComponents] + 1)) {
            if (CC_RegionLengths_data[runCounter] == 0) {
              CC_RegionLengths_data[runCounter] =
                  CC_RegionLengths_data[numComponents];
              nextLabel++;
            } else if (CC_RegionLengths_data[runCounter] !=
                       CC_RegionLengths_data[numComponents]) {
              for (root_k = runCounter;
                   root_k + 1 != CC_RegionLengths_data[root_k];
                   root_k = CC_RegionLengths_data[root_k] - 1) {
                CC_RegionLengths_data[root_k] =
                    CC_RegionLengths_data[CC_RegionLengths_data[root_k] - 1];
              }
              for (root_p = numComponents;
                   root_p + 1 != CC_RegionLengths_data[root_p];
                   root_p = CC_RegionLengths_data[root_p] - 1) {
                CC_RegionLengths_data[root_p] =
                    CC_RegionLengths_data[CC_RegionLengths_data[root_p] - 1];
              }
              if (root_k + 1 != root_p + 1) {
                if (root_p + 1 < root_k + 1) {
                  CC_RegionLengths_data[root_k] = root_p + 1;
                  CC_RegionLengths_data[runCounter] = root_p + 1;
                } else {
                  CC_RegionLengths_data[root_p] = root_k + 1;
                  CC_RegionLengths_data[numComponents] = root_k + 1;
                }
              }
            }
          }
        }
      }
      if (CC_RegionLengths_data[runCounter] == 0) {
        CC_RegionLengths_data[runCounter] = nextLabel;
        nextLabel++;
      }
      runCounter++;
    }
    emxInit_int32_T(&labelsRenumbered, 1);
    runCounter = labelsRenumbered->size[0];
    labelsRenumbered->size[0] = CC_RegionLengths->size[0];
    emxEnsureCapacity_int32_T(labelsRenumbered, runCounter);
    labelsRenumbered_data = labelsRenumbered->data;
    numComponents = 0;
    for (col = 0; col < numRuns; col++) {
      if (CC_RegionLengths_data[col] == col + 1) {
        numComponents++;
        labelsRenumbered_data[col] = numComponents;
      }
      labelsRenumbered_data[col] =
          labelsRenumbered_data[CC_RegionLengths_data[col] - 1];
    }
    runCounter = CC_RegionLengths->size[0];
    CC_RegionLengths->size[0] = numComponents;
    emxEnsureCapacity_int32_T(CC_RegionLengths, runCounter);
    CC_RegionLengths_data = CC_RegionLengths->data;
    for (col = 0; col < numComponents; col++) {
      CC_RegionLengths_data[col] = 0;
    }
    for (col = 0; col < numRuns; col++) {
      CC_RegionLengths_data[labelsRenumbered_data[col] - 1] =
          ((CC_RegionLengths_data[labelsRenumbered_data[col] - 1] +
            endRow_data[col]) -
           startRow_tmp_data[col]) +
          1;
    }
    if (CC_RegionLengths->size[0] == 0) {
      CC_Connectivity = 0.0;
    } else {
      if (CC_RegionLengths->size[0] <= 1024) {
        runCounter = CC_RegionLengths->size[0];
        nextLabel = 0;
        firstRunOnPreviousColumn = 1;
      } else {
        runCounter = 1024;
        firstRunOnPreviousColumn =
            (int)((unsigned int)CC_RegionLengths->size[0] >> 10);
        nextLabel =
            CC_RegionLengths->size[0] - (firstRunOnPreviousColumn << 10);
        if (nextLabel > 0) {
          firstRunOnPreviousColumn++;
        } else {
          nextLabel = 1024;
        }
      }
      CC_Connectivity = CC_RegionLengths_data[0];
      for (col = 2; col <= runCounter; col++) {
        CC_Connectivity += (double)CC_RegionLengths_data[col - 1];
      }
      for (col = 2; col <= firstRunOnPreviousColumn; col++) {
        double bsum;
        runCounter = (col - 1) << 10;
        bsum = CC_RegionLengths_data[runCounter];
        if (col == firstRunOnPreviousColumn) {
          row = nextLabel;
        } else {
          row = 1024;
        }
        for (k = 2; k <= row; k++) {
          bsum += (double)CC_RegionLengths_data[(runCounter + k) - 1];
        }
        CC_Connectivity += bsum;
      }
    }
    runCounter = r1->size[0];
    r1->size[0] = (int)CC_Connectivity;
    emxEnsureCapacity_int32_T(r1, runCounter);
    r2 = r1->data;
    emxInit_int32_T(&x, 1);
    firstRunOnThisColumn = CC_RegionLengths->size[0];
    runCounter = x->size[0];
    x->size[0] = CC_RegionLengths->size[0];
    emxEnsureCapacity_int32_T(x, runCounter);
    x_data = x->data;
    for (col = 0; col < firstRunOnThisColumn; col++) {
      x_data[col] = CC_RegionLengths_data[col];
    }
    if ((CC_RegionLengths->size[0] != 1) && (CC_RegionLengths->size[0] != 0) &&
        (CC_RegionLengths->size[0] != 1)) {
      for (col = 0; col <= firstRunOnThisColumn - 2; col++) {
        x_data[col + 1] += x_data[col];
      }
    }
    emxInit_int32_T(&idxCount, 1);
    lastRunOnPreviousColumn = x->size[0] + 1;
    runCounter = idxCount->size[0];
    idxCount->size[0] = x->size[0] + 1;
    emxEnsureCapacity_int32_T(idxCount, runCounter);
    idxCount_data = idxCount->data;
    idxCount_data[0] = 0;
    for (col = 0; col < firstRunOnThisColumn; col++) {
      idxCount_data[col + 1] = x_data[col];
    }
    for (col = 0; col < numRuns; col++) {
      runCounter = (startCol_data[col] - 1) * 1280;
      row = labelsRenumbered_data[col] - 1;
      nextLabel = startRow_tmp_data[col];
      firstRunOnPreviousColumn = endRow_data[col];
      for (k = nextLabel; k <= firstRunOnPreviousColumn; k++) {
        idxCount_data[row]++;
        r2[idxCount_data[row] - 1] = k + runCounter;
      }
    }
    emxFree_int32_T(&labelsRenumbered);
    runCounter = CC_PixelIdxList->size[0] * CC_PixelIdxList->size[1];
    CC_PixelIdxList->size[0] = 1;
    CC_PixelIdxList->size[1] = numComponents;
    emxEnsureCapacity_cell_wrap_42(CC_PixelIdxList, runCounter);
    CC_PixelIdxList_data = CC_PixelIdxList->data;
    if (numComponents != 0) {
      for (col = 0; col < numComponents; col++) {
        CC_PixelIdxList_data[col].f1->size[0] = 0;
      }
    }
    runCounter = x->size[0];
    x->size[0] = CC_RegionLengths->size[0];
    emxEnsureCapacity_int32_T(x, runCounter);
    x_data = x->data;
    for (col = 0; col < firstRunOnThisColumn; col++) {
      x_data[col] = CC_RegionLengths_data[col];
    }
    if ((CC_RegionLengths->size[0] != 1) && (CC_RegionLengths->size[0] != 0) &&
        (CC_RegionLengths->size[0] != 1)) {
      for (col = 0; col <= firstRunOnThisColumn - 2; col++) {
        x_data[col + 1] += x_data[col];
      }
    }
    runCounter = idxCount->size[0];
    idxCount->size[0] = lastRunOnPreviousColumn;
    emxEnsureCapacity_int32_T(idxCount, runCounter);
    idxCount_data = idxCount->data;
    idxCount_data[0] = 0;
    for (k = 0; k < firstRunOnThisColumn; k++) {
      idxCount_data[k + 1] = x_data[k];
      if (idxCount_data[k] + 1 > x_data[k]) {
        nextLabel = 0;
        runCounter = 0;
      } else {
        nextLabel = idxCount_data[k];
        runCounter = x_data[k];
      }
      row = runCounter - nextLabel;
      runCounter = CC_PixelIdxList_data[k].f1->size[0];
      CC_PixelIdxList_data[k].f1->size[0] = row;
      emxEnsureCapacity_real_T(CC_PixelIdxList_data[k].f1, runCounter);
      for (col = 0; col < row; col++) {
        CC_PixelIdxList_data[k].f1->data[col] = r2[nextLabel + col];
      }
    }
    emxFree_int32_T(&x);
    emxFree_int32_T(&idxCount);
  }
  emxFree_int16_T(&startRow_tmp);
  emxFree_int16_T(&startCol);
  emxFree_int16_T(&endRow);
  row = r1->size[0];
  runCounter = CC_RegionIndices->size[0];
  CC_RegionIndices->size[0] = r1->size[0];
  emxEnsureCapacity_real_T(CC_RegionIndices, runCounter);
  CC_RegionIndices_data = CC_RegionIndices->data;
  for (col = 0; col < row; col++) {
    CC_RegionIndices_data[col] = r2[col];
  }
  emxFree_int32_T(&r1);
  CC_Connectivity = 8.0;
  *CC_NumObjects = numComponents;
  return CC_Connectivity;
}

/* End of code generation (bwconncomp.c) */
