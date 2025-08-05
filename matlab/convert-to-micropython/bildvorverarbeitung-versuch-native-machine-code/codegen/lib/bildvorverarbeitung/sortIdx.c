/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sortIdx.c
 *
 * Code generation for function 'sortIdx'
 *
 */

/* Include files */
#include "sortIdx.h"
#include "bildvorverarbeitung_emxutil.h"
#include "bildvorverarbeitung_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void merge(emxArray_int32_T *idx, emxArray_real_T *x, int offset, int np,
                  int nq, emxArray_int32_T *iwork, emxArray_real_T *xwork);

static void merge_block(emxArray_int32_T *idx, emxArray_real_T *x, int offset,
                        int n, int preSortLevel, emxArray_int32_T *iwork,
                        emxArray_real_T *xwork);

/* Function Definitions */
static void merge(emxArray_int32_T *idx, emxArray_real_T *x, int offset, int np,
                  int nq, emxArray_int32_T *iwork, emxArray_real_T *xwork)
{
  double *x_data;
  double *xwork_data;
  int j;
  int *idx_data;
  int *iwork_data;
  xwork_data = xwork->data;
  iwork_data = iwork->data;
  x_data = x->data;
  idx_data = idx->data;
  if (nq != 0) {
    int iout;
    int n;
    int p;
    int q;
    n = np + nq;
    for (j = 0; j < n; j++) {
      q = offset + j;
      iwork_data[j] = idx_data[q];
      xwork_data[j] = x_data[q];
    }
    p = 0;
    q = np;
    iout = offset - 1;
    int exitg1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork_data[p] >= xwork_data[q]) {
        idx_data[iout] = iwork_data[p];
        x_data[iout] = xwork_data[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx_data[iout] = iwork_data[q];
        x_data[iout] = xwork_data[q];
        if (q + 1 < n) {
          q++;
        } else {
          q = iout - p;
          for (j = p + 1; j <= np; j++) {
            iout = q + j;
            idx_data[iout] = iwork_data[j - 1];
            x_data[iout] = xwork_data[j - 1];
          }
          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

static void merge_block(emxArray_int32_T *idx, emxArray_real_T *x, int offset,
                        int n, int preSortLevel, emxArray_int32_T *iwork,
                        emxArray_real_T *xwork)
{
  int bLen;
  int k;
  int nPairs;
  nPairs = n >> preSortLevel;
  bLen = 1 << preSortLevel;
  while (nPairs > 1) {
    int tailOffset;
    if (((unsigned int)nPairs & 1U) != 0U) {
      int nTail;
      nPairs--;
      tailOffset = bLen * nPairs;
      nTail = n - tailOffset;
      if (nTail > bLen) {
        merge(idx, x, offset + tailOffset, bLen, nTail - bLen, iwork, xwork);
      }
    }
    tailOffset = bLen << 1;
    nPairs >>= 1;
    for (k = 0; k < nPairs; k++) {
      merge(idx, x, offset + k * tailOffset, bLen, bLen, iwork, xwork);
    }
    bLen = tailOffset;
  }
  if (n > bLen) {
    merge(idx, x, offset, bLen, n - bLen, iwork, xwork);
  }
}

void sortIdx(emxArray_real_T *x, emxArray_int32_T *idx)
{
  emxArray_int32_T *iwork;
  emxArray_real_T *b_x;
  double *b_x_data;
  double *x_data;
  double *xwork_data;
  int b;
  int b_b;
  int b_k;
  int i1;
  int k;
  int loop_ub;
  unsigned int unnamed_idx_0;
  int *b_idx_data;
  int *idx_data;
  int *iwork_data;
  x_data = x->data;
  unnamed_idx_0 = (unsigned int)x->size[0];
  i1 = idx->size[0] * idx->size[1];
  idx->size[0] = (int)unnamed_idx_0;
  idx->size[1] = 1;
  emxEnsureCapacity_int32_T(idx, i1);
  idx_data = idx->data;
  loop_ub = (int)unnamed_idx_0;
  for (k = 0; k < loop_ub; k++) {
    idx_data[k] = 0;
  }
  if (x->size[0] != 0) {
    double x4[4];
    int idx4[4];
    int bLen;
    int bLen2;
    int b_loop_ub;
    int i2;
    int i4;
    int ib;
    int nNaNs;
    int quartetOffset;
    int wOffset;
    emxInit_int32_T(&idx, 1);
    i1 = idx->size[0];
    idx->size[0] = (int)unnamed_idx_0;
    emxEnsureCapacity_int32_T(idx, i1);
    b_idx_data = idx->data;
    for (k = 0; k < loop_ub; k++) {
      b_idx_data[k] = 0;
    }
    emxInit_real_T(&b_x, 1);
    b_loop_ub = x->size[0];
    i1 = b_x->size[0];
    b_x->size[0] = b_loop_ub;
    emxEnsureCapacity_real_T(b_x, i1);
    b_x_data = b_x->data;
    for (k = 0; k < b_loop_ub; k++) {
      b_x_data[k] = x_data[k];
    }
    emxInit_int32_T(&iwork, 1);
    i1 = iwork->size[0];
    iwork->size[0] = (int)unnamed_idx_0;
    emxEnsureCapacity_int32_T(iwork, i1);
    iwork_data = iwork->data;
    for (k = 0; k < loop_ub; k++) {
      iwork_data[k] = 0;
    }
    emxInit_real_T(&x, 1);
    i1 = x->size[0];
    x->size[0] = b_loop_ub;
    emxEnsureCapacity_real_T(x, i1);
    xwork_data = x->data;
    x4[0] = 0.0;
    idx4[0] = 0;
    x4[1] = 0.0;
    idx4[1] = 0;
    x4[2] = 0.0;
    idx4[2] = 0;
    x4[3] = 0.0;
    idx4[3] = 0;
    nNaNs = 0;
    ib = 0;
    for (k = 0; k < b_loop_ub; k++) {
      if (rtIsNaN(b_x_data[k])) {
        i1 = (b_loop_ub - nNaNs) - 1;
        b_idx_data[i1] = k + 1;
        xwork_data[i1] = b_x_data[k];
        nNaNs++;
      } else {
        ib++;
        idx4[ib - 1] = k + 1;
        x4[ib - 1] = b_x_data[k];
        if (ib == 4) {
          double d;
          double d1;
          quartetOffset = k - nNaNs;
          if (x4[0] >= x4[1]) {
            i1 = 1;
            i2 = 2;
          } else {
            i1 = 2;
            i2 = 1;
          }
          if (x4[2] >= x4[3]) {
            ib = 3;
            i4 = 4;
          } else {
            ib = 4;
            i4 = 3;
          }
          d = x4[i1 - 1];
          d1 = x4[ib - 1];
          if (d >= d1) {
            double d2;
            d2 = x4[i2 - 1];
            if (d2 >= d1) {
              bLen = i1;
              bLen2 = i2;
              i1 = ib;
              i2 = i4;
            } else if (d2 >= x4[i4 - 1]) {
              bLen = i1;
              bLen2 = ib;
              i1 = i2;
              i2 = i4;
            } else {
              bLen = i1;
              bLen2 = ib;
              i1 = i4;
            }
          } else {
            double d2;
            d2 = x4[i4 - 1];
            if (d >= d2) {
              if (x4[i2 - 1] >= d2) {
                bLen = ib;
                bLen2 = i1;
                i1 = i2;
                i2 = i4;
              } else {
                bLen = ib;
                bLen2 = i1;
                i1 = i4;
              }
            } else {
              bLen = ib;
              bLen2 = i4;
            }
          }
          b_idx_data[quartetOffset - 3] = idx4[bLen - 1];
          b_idx_data[quartetOffset - 2] = idx4[bLen2 - 1];
          b_idx_data[quartetOffset - 1] = idx4[i1 - 1];
          b_idx_data[quartetOffset] = idx4[i2 - 1];
          b_x_data[quartetOffset - 3] = x4[bLen - 1];
          b_x_data[quartetOffset - 2] = x4[bLen2 - 1];
          b_x_data[quartetOffset - 1] = x4[i1 - 1];
          b_x_data[quartetOffset] = x4[i2 - 1];
          ib = 0;
        }
      }
    }
    wOffset = b_x->size[0] - nNaNs;
    if (ib > 0) {
      signed char perm[4];
      perm[1] = 0;
      perm[2] = 0;
      perm[3] = 0;
      if (ib == 1) {
        perm[0] = 1;
      } else if (ib == 2) {
        if (x4[0] >= x4[1]) {
          perm[0] = 1;
          perm[1] = 2;
        } else {
          perm[0] = 2;
          perm[1] = 1;
        }
      } else if (x4[0] >= x4[1]) {
        if (x4[1] >= x4[2]) {
          perm[0] = 1;
          perm[1] = 2;
          perm[2] = 3;
        } else if (x4[0] >= x4[2]) {
          perm[0] = 1;
          perm[1] = 3;
          perm[2] = 2;
        } else {
          perm[0] = 3;
          perm[1] = 1;
          perm[2] = 2;
        }
      } else if (x4[0] >= x4[2]) {
        perm[0] = 2;
        perm[1] = 1;
        perm[2] = 3;
      } else if (x4[1] >= x4[2]) {
        perm[0] = 2;
        perm[1] = 3;
        perm[2] = 1;
      } else {
        perm[0] = 3;
        perm[1] = 2;
        perm[2] = 1;
      }
      i1 = (unsigned char)ib;
      for (k = 0; k < i1; k++) {
        quartetOffset = (wOffset - ib) + k;
        i2 = perm[k];
        b_idx_data[quartetOffset] = idx4[i2 - 1];
        b_x_data[quartetOffset] = x4[i2 - 1];
      }
    }
    i1 = nNaNs >> 1;
    for (k = 0; k < i1; k++) {
      quartetOffset = wOffset + k;
      i2 = b_idx_data[quartetOffset];
      ib = (b_loop_ub - k) - 1;
      b_idx_data[quartetOffset] = b_idx_data[ib];
      b_idx_data[ib] = i2;
      b_x_data[quartetOffset] = xwork_data[ib];
      b_x_data[ib] = xwork_data[quartetOffset];
    }
    if (((unsigned int)nNaNs & 1U) != 0U) {
      i1 += wOffset;
      b_x_data[i1] = xwork_data[i1];
    }
    i1 = 2;
    if (wOffset > 1) {
      if (b_x->size[0] >= 256) {
        int nBlocks;
        nBlocks = wOffset >> 8;
        if (nBlocks > 0) {
          for (b = 0; b < nBlocks; b++) {
            double xwork[256];
            int b_iwork[256];
            i4 = (b << 8) - 1;
            for (b_b = 0; b_b < 6; b_b++) {
              int i;
              bLen = 1 << (b_b + 2);
              bLen2 = bLen << 1;
              i = 256 >> (b_b + 3);
              for (b_k = 0; b_k < i; b_k++) {
                i1 = (i4 + b_k * bLen2) + 1;
                for (k = 0; k < bLen2; k++) {
                  ib = i1 + k;
                  b_iwork[k] = b_idx_data[ib];
                  xwork[k] = b_x_data[ib];
                }
                i2 = 0;
                quartetOffset = bLen;
                ib = i1 - 1;
                int exitg1;
                do {
                  exitg1 = 0;
                  ib++;
                  if (xwork[i2] >= xwork[quartetOffset]) {
                    b_idx_data[ib] = b_iwork[i2];
                    b_x_data[ib] = xwork[i2];
                    if (i2 + 1 < bLen) {
                      i2++;
                    } else {
                      exitg1 = 1;
                    }
                  } else {
                    b_idx_data[ib] = b_iwork[quartetOffset];
                    b_x_data[ib] = xwork[quartetOffset];
                    if (quartetOffset + 1 < bLen2) {
                      quartetOffset++;
                    } else {
                      ib -= i2;
                      for (k = i2 + 1; k <= bLen; k++) {
                        quartetOffset = ib + k;
                        b_idx_data[quartetOffset] = b_iwork[k - 1];
                        b_x_data[quartetOffset] = xwork[k - 1];
                      }
                      exitg1 = 1;
                    }
                  }
                } while (exitg1 == 0);
              }
            }
          }
          i1 = nBlocks << 8;
          quartetOffset = wOffset - i1;
          if (quartetOffset > 0) {
            merge_block(idx, b_x, i1, quartetOffset, 2, iwork, x);
          }
          i1 = 8;
        }
      }
      merge_block(idx, b_x, 0, wOffset, i1, iwork, x);
      xwork_data = x->data;
      iwork_data = iwork->data;
      b_x_data = b_x->data;
      b_idx_data = idx->data;
    }
    if ((nNaNs > 0) && (wOffset > 0)) {
      for (k = 0; k < nNaNs; k++) {
        i1 = wOffset + k;
        xwork_data[k] = b_x_data[i1];
        iwork_data[k] = b_idx_data[i1];
      }
      for (k = wOffset; k >= 1; k--) {
        i1 = (nNaNs + k) - 1;
        b_x_data[i1] = b_x_data[k - 1];
        b_idx_data[i1] = b_idx_data[k - 1];
      }
      for (k = 0; k < nNaNs; k++) {
        b_x_data[k] = xwork_data[k];
        b_idx_data[k] = iwork_data[k];
      }
    }
    emxFree_real_T(&x);
    emxFree_int32_T(&iwork);
    for (k = 0; k < loop_ub; k++) {
      idx_data[k] = b_idx_data[k];
    }
    emxFree_int32_T(&idx);
    for (k = 0; k < b_loop_ub; k++) {
      x_data[k] = b_x_data[k];
    }
    emxFree_real_T(&b_x);
  }
}

/* End of code generation (sortIdx.c) */
