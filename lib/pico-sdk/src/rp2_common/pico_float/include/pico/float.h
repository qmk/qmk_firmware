/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_FLOAT_H
#define _PICO_FLOAT_H

#include <math.h>
#include <float.h>
#include "pico.h"
#include "pico/bootrom/sf_table.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file float.h
* \defgroup pico_float pico_float
*
* Optimized single-precision floating point functions
*
* (Replacement) optimized implementations are provided of the following compiler built-ins
* and math library functions:
*
* - __aeabi_fadd, __aeabi_fdiv, __aeabi_fmul, __aeabi_frsub, __aeabi_fsub, __aeabi_cfcmpeq, __aeabi_cfrcmple, __aeabi_cfcmple, __aeabi_fcmpeq, __aeabi_fcmplt, __aeabi_fcmple, __aeabi_fcmpge, __aeabi_fcmpgt, __aeabi_fcmpun, __aeabi_i2f, __aeabi_l2f, __aeabi_ui2f, __aeabi_ul2f, __aeabi_f2iz, __aeabi_f2lz, __aeabi_f2uiz, __aeabi_f2ulz, __aeabi_f2d, sqrtf, cosf, sinf, tanf, atan2f, expf, logf
* - ldexpf, copysignf, truncf, floorf, ceilf, roundf, asinf, acosf, atanf, sinhf, coshf, tanhf, asinhf, acoshf, atanhf, exp2f, log2f, exp10f, log10f, powf, hypotf, cbrtf, fmodf, dremf, remainderf, remquof, expm1f, log1pf, fmaf
* - powintf, sincosf (GNU extensions)
*
* The following additional optimized functions are also provided:
*
* - fix2float, ufix2float, fix642float, ufix642float, float2fix, float2ufix, float2fix64, float2ufix64, float2int, float2int64, float2int_z, float2int64_z
*/

float fix2float(int32_t m, int e);
float ufix2float(uint32_t m, int e);
float fix642float(int64_t m, int e);
float ufix642float(uint64_t m, int e);

// These methods round towards -Infinity.
int32_t float2fix(float f, int e);
uint32_t float2ufix(float f, int e);
int64_t float2fix64(float f, int e);
uint64_t float2ufix64(float f, int e);
int32_t float2int(float f);
int64_t float2int64(float f);

// These methods round towards 0.
int32_t float2int_z(float f);
int64_t float2int64_z(float f);

float exp10f(float x);
void sincosf(float x, float *sinx, float *cosx);
float powintf(float x, int y);

#ifdef __cplusplus
}
#endif

#endif