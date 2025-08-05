/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_bildvorverarbeitung_mex.c
 *
 * Code generation for function 'bildvorverarbeitung'
 *
 */

/* Include files */
#include "_coder_bildvorverarbeitung_mex.h"
#include "_coder_bildvorverarbeitung_api.h"

/* Function Definitions */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  mexAtExit(&bildvorverarbeitung_atexit);
  bildvorverarbeitung_initialize();
  unsafe_bildvorverarbeitung_mexFunction(nlhs, plhs, nrhs, prhs);
  bildvorverarbeitung_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1,
                           NULL, "windows-1252", true);
  return emlrtRootTLSGlobal;
}

void unsafe_bildvorverarbeitung_mexFunction(int32_T nlhs, mxArray *plhs[1],
                                            int32_T nrhs,
                                            const mxArray *prhs[1])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  const mxArray *outputs;
  st.tls = emlrtRootTLSGlobal;
  /* Check for proper number of arguments. */
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        19, "bildvorverarbeitung");
  }
  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 19,
                        "bildvorverarbeitung");
  }
  /* Call the function. */
  bildvorverarbeitung_api(prhs[0], &outputs);
  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, &plhs[0], &outputs);
}

/* End of code generation (_coder_bildvorverarbeitung_mex.c) */
