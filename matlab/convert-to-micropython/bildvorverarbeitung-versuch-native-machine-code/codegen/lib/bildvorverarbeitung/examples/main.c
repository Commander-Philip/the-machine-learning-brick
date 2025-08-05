/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.c
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include files */
#include "main.h"
#include "bildvorverarbeitung.h"
#include "bildvorverarbeitung_emxAPI.h"
#include "bildvorverarbeitung_initialize.h"
#include "bildvorverarbeitung_terminate.h"
#include "bildvorverarbeitung_types.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void argInit_1280x720x3_uint8_T(unsigned char result[2764800]);

static unsigned char argInit_uint8_T(void);

/* Function Definitions */
static void argInit_1280x720x3_uint8_T(unsigned char result[2764800])
{
  int idx0;
  int idx1;
  int idx2;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 1280; idx0++) {
    for (idx1 = 0; idx1 < 720; idx1++) {
      for (idx2 = 0; idx2 < 3; idx2++) {
        /* Set the value of the array element.
Change this value to the value that the application requires. */
        result[(idx0 + 1280 * idx1) + 921600 * idx2] = argInit_uint8_T();
      }
    }
  }
}

static unsigned char argInit_uint8_T(void)
{
  return 0U;
}

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* Initialize the application.
You do not need to do this more than one time. */
  bildvorverarbeitung_initialize();
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_bildvorverarbeitung();
  /* Terminate the application.
You do not need to do this more than one time. */
  bildvorverarbeitung_terminate();
  return 0;
}

void main_bildvorverarbeitung(void)
{
  static unsigned char uv[2764800];
  emxArray_real_T *output;
  /* Initialize function 'bildvorverarbeitung' input arguments. */
  /* Initialize function input argument 'img'. */
  /* Call the entry-point 'bildvorverarbeitung'. */
  emxInitArray_real_T(&output, 2);
  argInit_1280x720x3_uint8_T(uv);
  bildvorverarbeitung(uv, output);
  emxDestroyArray_real_T(output);
}

/* End of code generation (main.c) */
