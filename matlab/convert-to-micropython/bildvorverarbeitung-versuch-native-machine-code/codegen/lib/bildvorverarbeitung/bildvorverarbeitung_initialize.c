/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * bildvorverarbeitung_initialize.c
 *
 * Code generation for function 'bildvorverarbeitung_initialize'
 *
 */

/* Include files */
#include "bildvorverarbeitung_initialize.h"
#include "bildvorverarbeitung_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
void bildvorverarbeitung_initialize(void)
{
  omp_init_nest_lock(&bildvorverarbeitung_nestLockGlobal);
  isInitialized_bildvorverarbeitung = true;
}

/* End of code generation (bildvorverarbeitung_initialize.c) */
