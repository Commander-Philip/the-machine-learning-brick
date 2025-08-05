/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_bildvorverarbeitung_api.c
 *
 * Code generation for function 'bildvorverarbeitung'
 *
 */

/* Include files */
#include "_coder_bildvorverarbeitung_api.h"
#include "_coder_bildvorverarbeitung_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;

emlrtContext emlrtContextGlobal = {
    true,                                                 /* bFirstTime */
    false,                                                /* bInitialized */
    131674U,                                              /* fVersionInfo */
    NULL,                                                 /* fErrorFunction */
    "bildvorverarbeitung",                                /* fFunctionName */
    NULL,                                                 /* fRTCallStack */
    false,                                                /* bDebugMode */
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, /* fSigWrd */
    NULL                                                  /* fSigMem */
};

/* Function Declarations */
static uint8_T (
    *b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                        const emlrtMsgIdentifier *parentId))[2764800];

static uint8_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                    const emlrtMsgIdentifier *msgId))[2764800];

static void emlrtExitTimeCleanupDtorFcn(const void *r);

static uint8_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *nullptr,
                                  const char_T *identifier))[2764800];

static const mxArray *emlrt_marshallOut(emxArray_real_T *u);

static void emxFree_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray);

static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray);

/* Function Definitions */
static uint8_T (
    *b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                        const emlrtMsgIdentifier *parentId))[2764800]
{
  uint8_T(*y)[2764800];
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static uint8_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                    const emlrtMsgIdentifier *msgId))[2764800]
{
  static const int32_T dims[3] = {1280, 720, 3};
  int32_T iv[3];
  uint8_T(*ret)[2764800];
  boolean_T bv[3] = {false, false, false};
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "uint8", false, 3U,
                            (const void *)&dims[0], &bv[0], &iv[0]);
  ret = (uint8_T(*)[2764800])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void emlrtExitTimeCleanupDtorFcn(const void *r)
{
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

static uint8_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *nullptr,
                                  const char_T *identifier))[2764800]
{
  emlrtMsgIdentifier thisId;
  uint8_T(*y)[2764800];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(nullptr), &thisId);
  emlrtDestroyArray(&nullptr);
  return y;
}

static const mxArray *emlrt_marshallOut(emxArray_real_T *u)
{
  static const int32_T iv[2] = {0, 0};
  const mxArray *m;
  const mxArray *y;
  real_T *u_data;
  u_data = u->data;
  y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, &u_data[0]);
  emlrtSetDimensions((mxArray *)m, &u->size[0], 2);
  u->canFreeData = false;
  emlrtAssign(&y, m);
  return y;
}

static void emxFree_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (real_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }
    emlrtFreeMex((*pEmxArray)->size);
    emlrtRemoveHeapReference((emlrtCTX)sp, (void *)pEmxArray);
    emlrtFreeEmxArray(*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocEmxArray(sizeof(emxArray_real_T));
  emlrtPushHeapReferenceStackEmxArray((emlrtCTX)sp, true, (void *)pEmxArray,
                                      (void *)&emxFree_real_T, NULL, NULL,
                                      NULL);
  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = 2;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T) * 2U);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < 2; i++) {
    emxArray->size[i] = 0;
  }
}

void bildvorverarbeitung_api(const mxArray *prhs, const mxArray **plhs)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  emxArray_real_T *output;
  uint8_T(*img)[2764800];
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  /* Marshall function inputs */
  img = emlrt_marshallIn(&st, emlrtAlias(prhs), "img");
  /* Invoke the target function */
  emxInit_real_T(&st, &output);
  bildvorverarbeitung(*img, output);
  /* Marshall function outputs */
  output->canFreeData = false;
  *plhs = emlrt_marshallOut(output);
  emxFree_real_T(&st, &output);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

void bildvorverarbeitung_atexit(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtPushHeapReferenceStackR2021a(
      &st, false, NULL, (void *)&emlrtExitTimeCleanupDtorFcn, NULL, NULL, NULL);
  emlrtEnterRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  bildvorverarbeitung_xil_terminate();
  bildvorverarbeitung_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void bildvorverarbeitung_initialize(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, NULL);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void bildvorverarbeitung_terminate(void)
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (_coder_bildvorverarbeitung_api.c) */
