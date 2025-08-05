/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * bildvorverarbeitung_terminate.c
 *
 * Code generation for function 'bildvorverarbeitung_terminate'
 *
 */

/* Include files */
#include "bildvorverarbeitung_terminate.h"
#include "bildvorverarbeitung_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
void bildvorverarbeitung_terminate(void)
{
  omp_destroy_nest_lock(&bildvorverarbeitung_nestLockGlobal);
  isInitialized_bildvorverarbeitung = false;
}

/* End of code generation (bildvorverarbeitung_terminate.c) */
