/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sort.c
 *
 * Code generation for function 'sort'
 *
 */

/* Include files */
#include "sort.h"
#include "bildvorverarbeitung_types.h"
#include "rt_nonfinite.h"
#include "sortIdx.h"

/* Function Definitions */
void sort(emxArray_real_T *x, emxArray_int32_T *idx)
{
  sortIdx(x, idx);
}

/* End of code generation (sort.c) */
