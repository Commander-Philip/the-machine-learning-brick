/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * bildvorverarbeitung.c
 *
 * Code generation for function 'bildvorverarbeitung'
 *
 */

/* Include files */
#include "bildvorverarbeitung.h"
#include "bildvorverarbeitung_data.h"
#include "bildvorverarbeitung_emxutil.h"
#include "bildvorverarbeitung_initialize.h"
#include "bildvorverarbeitung_types.h"
#include "imfindcircles.h"
#include "rt_nonfinite.h"
#include "libmwrgb2gray_tbb.h"

/* Function Definitions */
void bildvorverarbeitung(const unsigned char img[2764800],
                         emxArray_real_T *output)
{
  static unsigned char grayImage[921600];
  emxArray_real_T *centers;
  emxArray_real_T *radii;
  double *centers_data;
  double *output_data;
  double *radii_data;
  int i;
  int i1;
  int loop_ub;
  int result;
  signed char input_sizes_idx_1;
  signed char sizes_idx_1;
  boolean_T b;
  boolean_T empty_non_axis_sizes;
  if (!isInitialized_bildvorverarbeitung) {
    bildvorverarbeitung_initialize();
  }
  rgb2gray_tbb_uint8(&img[0], 921600.0, &grayImage[0], true);
  emxInit_real_T(&centers, 2);
  emxInit_real_T(&radii, 2);
  imfindcircles(grayImage, centers, radii);
  radii_data = radii->data;
  centers_data = centers->data;
  b = ((centers->size[0] != 0) && (centers->size[1] != 0));
  if (b) {
    result = centers->size[0];
  } else if ((radii->size[0] != 0) && (radii->size[1] != 0)) {
    result = radii->size[0];
  } else {
    result = centers->size[0];
    if (radii->size[0] > centers->size[0]) {
      result = radii->size[0];
    }
  }
  empty_non_axis_sizes = (result == 0);
  if (empty_non_axis_sizes || b) {
    input_sizes_idx_1 = (signed char)centers->size[1];
  } else {
    input_sizes_idx_1 = 0;
  }
  if (empty_non_axis_sizes ||
      ((radii->size[0] != 0) && (radii->size[1] != 0))) {
    sizes_idx_1 = (signed char)radii->size[1];
  } else {
    sizes_idx_1 = 0;
  }
  loop_ub = output->size[0] * output->size[1];
  output->size[0] = result;
  output->size[1] = input_sizes_idx_1 + sizes_idx_1;
  emxEnsureCapacity_real_T(output, loop_ub);
  output_data = output->data;
  loop_ub = input_sizes_idx_1;
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < result; i1++) {
      output_data[i1 + output->size[0] * i] = centers_data[i1 + result * i];
    }
  }
  emxFree_real_T(&centers);
  loop_ub = sizes_idx_1;
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < result; i1++) {
      output_data[i1 + output->size[0] * input_sizes_idx_1] = radii_data[i1];
    }
  }
  emxFree_real_T(&radii);
}

/* End of code generation (bildvorverarbeitung.c) */
