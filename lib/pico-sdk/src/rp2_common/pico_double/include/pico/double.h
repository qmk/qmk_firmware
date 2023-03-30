/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_DOUBLE_H
#define _PICO_DOUBLE_H

#include <math.h>
#include "pico.h"
#include "pico/bootrom/sf_table.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file double.h
*  \defgroup pico_double pico_double
*
* Optimized double-precision floating point functions
*
* (Replacement) optimized implementations are provided of the following compiler built-ins
* and math library functions:
*
* - __aeabi_dadd, __aeabi_ddiv, __aeabi_dmul, __aeabi_drsub, __aeabi_dsub, __aeabi_cdcmpeq, __aeabi_cdrcmple, __aeabi_cdcmple, __aeabi_dcmpeq, __aeabi_dcmplt, __aeabi_dcmple, __aeabi_dcmpge, __aeabi_dcmpgt, __aeabi_dcmpun, __aeabi_i2d, __aeabi_l2d, __aeabi_ui2d, __aeabi_ul2d, __aeabi_d2iz, __aeabi_d2lz, __aeabi_d2uiz, __aeabi_d2ulz, __aeabi_d2f
* - sqrt, cos, sin, tan, atan2, exp, log, ldexp, copysign, trunc, floor, ceil, round, asin, acos, atan, sinh, cosh, tanh, asinh, acosh, atanh, exp2, log2, exp10, log10, pow,, hypot, cbrt, fmod, drem, remainder, remquo, expm1, log1p, fma
* - powint, sincos (GNU extensions)
*
* The following additional optimized functions are also provided:
*
* - fix2double, ufix2double, fix642double, ufix642double, double2fix, double2ufix, double2fix64, double2ufix64, double2int, double2int64, double2int_z, double2int64_z
*/

double fix2double(int32_t m, int e);
double ufix2double(uint32_t m, int e);
double fix642double(int64_t m, int e);
double ufix642double(uint64_t m, int e);

// These methods round towards -Infinity.
int32_t double2fix(double f, int e);
uint32_t double2ufix(double f, int e);
int64_t double2fix64(double f, int e);
uint64_t double2ufix64(double f, int e);
int32_t double2int(double f);
int64_t double2int64(double f);

// These methods round towards 0.
int32_t double2int_z(double f);
int64_t double2int64_z(double f);

double exp10(double x);
void sincos(double x, double *sinx, double *cosx);
double powint(double x, int y);

#ifdef __cplusplus
}
#endif

#endif