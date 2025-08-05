/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * bildvorverarbeitung_types.h
 *
 * Code generation for function 'bildvorverarbeitung'
 *
 */

#ifndef BILDVORVERARBEITUNG_TYPES_H
#define BILDVORVERARBEITUNG_TYPES_H

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_struct_T
#define typedef_struct_T
typedef struct {
  double WeightedCentroid[2];
} struct_T;
#endif /* typedef_struct_T */

#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_real_T */
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /* typedef_emxArray_real_T */

#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T
struct emxArray_boolean_T {
  boolean_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_boolean_T */
#ifndef typedef_emxArray_boolean_T
#define typedef_emxArray_boolean_T
typedef struct emxArray_boolean_T emxArray_boolean_T;
#endif /* typedef_emxArray_boolean_T */

#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T
struct emxArray_int32_T {
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_int32_T */
#ifndef typedef_emxArray_int32_T
#define typedef_emxArray_int32_T
typedef struct emxArray_int32_T emxArray_int32_T;
#endif /* typedef_emxArray_int32_T */

#ifndef typedef_emxArray_creal_T
#define typedef_emxArray_creal_T
typedef struct {
  creal_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
} emxArray_creal_T;
#endif /* typedef_emxArray_creal_T */

#ifndef struct_emxArray_int16_T
#define struct_emxArray_int16_T
struct emxArray_int16_T {
  short *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_int16_T */
#ifndef typedef_emxArray_int16_T
#define typedef_emxArray_int16_T
typedef struct emxArray_int16_T emxArray_int16_T;
#endif /* typedef_emxArray_int16_T */

#ifndef struct_emxArray_real32_T
#define struct_emxArray_real32_T
struct emxArray_real32_T {
  float *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_real32_T */
#ifndef typedef_emxArray_real32_T
#define typedef_emxArray_real32_T
typedef struct emxArray_real32_T emxArray_real32_T;
#endif /* typedef_emxArray_real32_T */

#ifndef typedef_emxArray_struct_T
#define typedef_emxArray_struct_T
typedef struct {
  struct_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
} emxArray_struct_T;
#endif /* typedef_emxArray_struct_T */

#ifndef typedef_cell_wrap_42
#define typedef_cell_wrap_42
typedef struct {
  emxArray_real_T *f1;
} cell_wrap_42;
#endif /* typedef_cell_wrap_42 */

#ifndef typedef_emxArray_cell_wrap_42
#define typedef_emxArray_cell_wrap_42
typedef struct {
  cell_wrap_42 *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
} emxArray_cell_wrap_42;
#endif /* typedef_emxArray_cell_wrap_42 */

#ifndef struct_emxArray_boolean_T_0x0
#define struct_emxArray_boolean_T_0x0
struct emxArray_boolean_T_0x0 {
  int size[2];
};
#endif /* struct_emxArray_boolean_T_0x0 */
#ifndef typedef_emxArray_boolean_T_0x0
#define typedef_emxArray_boolean_T_0x0
typedef struct emxArray_boolean_T_0x0 emxArray_boolean_T_0x0;
#endif /* typedef_emxArray_boolean_T_0x0 */

#ifndef struct_emxArray_real_T_1x0
#define struct_emxArray_real_T_1x0
struct emxArray_real_T_1x0 {
  int size[2];
};
#endif /* struct_emxArray_real_T_1x0 */
#ifndef typedef_emxArray_real_T_1x0
#define typedef_emxArray_real_T_1x0
typedef struct emxArray_real_T_1x0 emxArray_real_T_1x0;
#endif /* typedef_emxArray_real_T_1x0 */

#ifndef typedef_b_struct_T
#define typedef_b_struct_T
typedef struct {
  double Area;
  double Centroid[2];
  double BoundingBox[4];
  double MajorAxisLength;
  double MinorAxisLength;
  double Eccentricity;
  double Orientation;
  emxArray_boolean_T_0x0 Image;
  emxArray_boolean_T_0x0 FilledImage;
  double FilledArea;
  double EulerNumber;
  double Extrema[16];
  double EquivDiameter;
  double Extent;
  emxArray_real_T *PixelIdxList;
  emxArray_real_T *PixelList;
  double Perimeter;
  double Circularity;
  emxArray_real_T *PixelValues;
  double WeightedCentroid[2];
  double MeanIntensity;
  double MinIntensity;
  double MaxIntensity;
  emxArray_real_T_1x0 SubarrayIdx;
  double SubarrayIdxLengths[2];
} b_struct_T;
#endif /* typedef_b_struct_T */

#ifndef typedef_b_emxArray_struct_T
#define typedef_b_emxArray_struct_T
typedef struct {
  b_struct_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
} b_emxArray_struct_T;
#endif /* typedef_b_emxArray_struct_T */

#endif
/* End of code generation (bildvorverarbeitung_types.h) */
