/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_sin_q31.c    
*    
* Description:	Fast sine calculation for Q31 values.   
*    
* Target Processor: Cortex-M4/Cortex-M3/Cortex-M0
*  
* Redistribution and use in source and binary forms, with or without 
* modification, are permitted provided that the following conditions
* are met:
*   - Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   - Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the 
*     distribution.
*   - Neither the name of ARM LIMITED nor the names of its contributors
*     may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.    
* -------------------------------------------------------------------- */

#include "arm_math.h"

/**    
 * @ingroup groupFastMath    
 */

 /**    
 * @addtogroup sin    
 * @{    
 */

/**   
 * \par    
 * Table values are in Q31 (1.31 fixed-point format) and generation is done in 
 * three steps.  First,  generate sin values in floating point:    
 * <pre>
 * tableSize = 256;      
 * for(n = -1; n < (tableSize + 1); n++)    
 * {    
 *	sinTable[n+1]= sin(2*pi*n/tableSize);    
 * } </pre>    
 * where pi value is  3.14159265358979    
 * \par    
 * Second, convert floating-point to Q31 (Fixed point):
 *	(sinTable[i] * pow(2, 31))    
 * \par    
 * Finally, round to the nearest integer value:
 * 	sinTable[i] += (sinTable[i] > 0 ? 0.5 :-0.5);    
 */

static const q31_t sinTableQ31[259] = {
  0xfcdbd541, 0x0, 0x3242abf, 0x647d97c, 0x96a9049, 0xc8bd35e, 0xfab272b,
  0x12c8106f,
  0x15e21445, 0x18f8b83c, 0x1c0b826a, 0x1f19f97b, 0x2223a4c5, 0x25280c5e,
  0x2826b928, 0x2b1f34eb,
  0x2e110a62, 0x30fbc54d, 0x33def287, 0x36ba2014, 0x398cdd32, 0x3c56ba70,
  0x3f1749b8, 0x41ce1e65,
  0x447acd50, 0x471cece7, 0x49b41533, 0x4c3fdff4, 0x4ebfe8a5, 0x5133cc94,
  0x539b2af0, 0x55f5a4d2,
  0x5842dd54, 0x5a82799a, 0x5cb420e0, 0x5ed77c8a, 0x60ec3830, 0x62f201ac,
  0x64e88926, 0x66cf8120,
  0x68a69e81, 0x6a6d98a4, 0x6c242960, 0x6dca0d14, 0x6f5f02b2, 0x70e2cbc6,
  0x72552c85, 0x73b5ebd1,
  0x7504d345, 0x7641af3d, 0x776c4edb, 0x78848414, 0x798a23b1, 0x7a7d055b,
  0x7b5d039e, 0x7c29fbee,
  0x7ce3ceb2, 0x7d8a5f40, 0x7e1d93ea, 0x7e9d55fc, 0x7f0991c4, 0x7f62368f,
  0x7fa736b4, 0x7fd8878e,
  0x7ff62182, 0x7fffffff, 0x7ff62182, 0x7fd8878e, 0x7fa736b4, 0x7f62368f,
  0x7f0991c4, 0x7e9d55fc,
  0x7e1d93ea, 0x7d8a5f40, 0x7ce3ceb2, 0x7c29fbee, 0x7b5d039e, 0x7a7d055b,
  0x798a23b1, 0x78848414,
  0x776c4edb, 0x7641af3d, 0x7504d345, 0x73b5ebd1, 0x72552c85, 0x70e2cbc6,
  0x6f5f02b2, 0x6dca0d14,
  0x6c242960, 0x6a6d98a4, 0x68a69e81, 0x66cf8120, 0x64e88926, 0x62f201ac,
  0x60ec3830, 0x5ed77c8a,
  0x5cb420e0, 0x5a82799a, 0x5842dd54, 0x55f5a4d2, 0x539b2af0, 0x5133cc94,
  0x4ebfe8a5, 0x4c3fdff4,
  0x49b41533, 0x471cece7, 0x447acd50, 0x41ce1e65, 0x3f1749b8, 0x3c56ba70,
  0x398cdd32, 0x36ba2014,
  0x33def287, 0x30fbc54d, 0x2e110a62, 0x2b1f34eb, 0x2826b928, 0x25280c5e,
  0x2223a4c5, 0x1f19f97b,
  0x1c0b826a, 0x18f8b83c, 0x15e21445, 0x12c8106f, 0xfab272b, 0xc8bd35e,
  0x96a9049, 0x647d97c,
  0x3242abf, 0x0, 0xfcdbd541, 0xf9b82684, 0xf6956fb7, 0xf3742ca2, 0xf054d8d5,
  0xed37ef91,
  0xea1debbb, 0xe70747c4, 0xe3f47d96, 0xe0e60685, 0xdddc5b3b, 0xdad7f3a2,
  0xd7d946d8, 0xd4e0cb15,
  0xd1eef59e, 0xcf043ab3, 0xcc210d79, 0xc945dfec, 0xc67322ce, 0xc3a94590,
  0xc0e8b648, 0xbe31e19b,
  0xbb8532b0, 0xb8e31319, 0xb64beacd, 0xb3c0200c, 0xb140175b, 0xaecc336c,
  0xac64d510, 0xaa0a5b2e,
  0xa7bd22ac, 0xa57d8666, 0xa34bdf20, 0xa1288376, 0x9f13c7d0, 0x9d0dfe54,
  0x9b1776da, 0x99307ee0,
  0x9759617f, 0x9592675c, 0x93dbd6a0, 0x9235f2ec, 0x90a0fd4e, 0x8f1d343a,
  0x8daad37b, 0x8c4a142f,
  0x8afb2cbb, 0x89be50c3, 0x8893b125, 0x877b7bec, 0x8675dc4f, 0x8582faa5,
  0x84a2fc62, 0x83d60412,
  0x831c314e, 0x8275a0c0, 0x81e26c16, 0x8162aa04, 0x80f66e3c, 0x809dc971,
  0x8058c94c, 0x80277872,
  0x8009de7e, 0x80000000, 0x8009de7e, 0x80277872, 0x8058c94c, 0x809dc971,
  0x80f66e3c, 0x8162aa04,
  0x81e26c16, 0x8275a0c0, 0x831c314e, 0x83d60412, 0x84a2fc62, 0x8582faa5,
  0x8675dc4f, 0x877b7bec,
  0x8893b125, 0x89be50c3, 0x8afb2cbb, 0x8c4a142f, 0x8daad37b, 0x8f1d343a,
  0x90a0fd4e, 0x9235f2ec,
  0x93dbd6a0, 0x9592675c, 0x9759617f, 0x99307ee0, 0x9b1776da, 0x9d0dfe54,
  0x9f13c7d0, 0xa1288376,
  0xa34bdf20, 0xa57d8666, 0xa7bd22ac, 0xaa0a5b2e, 0xac64d510, 0xaecc336c,
  0xb140175b, 0xb3c0200c,
  0xb64beacd, 0xb8e31319, 0xbb8532b0, 0xbe31e19b, 0xc0e8b648, 0xc3a94590,
  0xc67322ce, 0xc945dfec,
  0xcc210d79, 0xcf043ab3, 0xd1eef59e, 0xd4e0cb15, 0xd7d946d8, 0xdad7f3a2,
  0xdddc5b3b, 0xe0e60685,
  0xe3f47d96, 0xe70747c4, 0xea1debbb, 0xed37ef91, 0xf054d8d5, 0xf3742ca2,
  0xf6956fb7, 0xf9b82684,
  0xfcdbd541, 0x0, 0x3242abf
};


/**   
 * @brief Fast approximation to the trigonometric sine function for Q31 data.
 * @param[in] x Scaled input value in radians.
 * @return  sin(x).
 *
 * The Q31 input value is in the range [0 +0.9999] and is mapped to a radian value in the range [0 2*pi). */

q31_t arm_sin_q31(
  q31_t x)
{
  q31_t sinVal, in, in2;                         /* Temporary variables for input, output */
  int32_t index;                                 /* Index variables */
  q31_t wa, wb, wc, wd;                          /* Cubic interpolation coefficients */
  q31_t a, b, c, d;                              /* Four nearest output values */
  q31_t *tablePtr;                               /* Pointer to table */
  q31_t fract, fractCube, fractSquare;           /* Temporary values for fractional values */
  q31_t oneBy6 = 0x15555555;                     /* Fixed point value of 1/6 */
  q31_t tableSpacing = TABLE_SPACING_Q31;        /* Table spacing */
  q31_t temp;                                    /* Temporary variable for intermediate process */

  in = x;

  /* Calculate the nearest index */
  index = (uint32_t) in / (uint32_t) tableSpacing;

  /* Calculate the nearest value of input */
  in2 = (q31_t) index *tableSpacing;

  /* Calculation of fractional value */
  fract = (in - in2) << 8;

  /* fractSquare = fract * fract */
  fractSquare = ((q31_t) (((q63_t) fract * fract) >> 32));
  fractSquare = fractSquare << 1;

  /* fractCube = fract * fract * fract */
  fractCube = ((q31_t) (((q63_t) fractSquare * fract) >> 32));
  fractCube = fractCube << 1;

  /* Checking min and max index of table */
  if(index < 0)
  {
    index = 0;
  }
  else if(index > 256)
  {
    index = 256;
  }

  /* Initialise table pointer */
  tablePtr = (q31_t *) & sinTableQ31[index];

  /* Cubic interpolation process */
  /* Calculation of wa */
  /* wa = -(oneBy6)*fractCube + (fractSquare >> 1u) - (0x2AAAAAAA)*fract; */
  wa = ((q31_t) (((q63_t) oneBy6 * fractCube) >> 32));
  temp = 0x2AAAAAAA;
  wa = (q31_t) ((((q63_t) wa << 32) + ((q63_t) temp * fract)) >> 32);
  wa = -(wa << 1u);
  wa += (fractSquare >> 1u);

  /* Read first nearest value of output from the sin table */
  a = *tablePtr++;

  /* sinVal = a*wa */
  sinVal = ((q31_t) (((q63_t) a * wa) >> 32));

  /* q31(1.31) Fixed point value of 1 */
  temp = 0x7FFFFFFF;

  /* Calculation of wb */
  wb = ((fractCube >> 1u) - (fractSquare + (fract >> 1u))) + temp;

  /* Read second nearest value of output from the sin table */
  b = *tablePtr++;

  /*  sinVal += b*wb */
  sinVal = (q31_t) ((((q63_t) sinVal << 32) + (q63_t) b * (wb)) >> 32);

  /* Calculation of wc */
  wc = -fractCube + fractSquare;
  wc = (wc >> 1u) + fract;

  /* Read third nearest value of output from the sin table */
  c = *tablePtr++;

  /*      sinVal += c*wc */
  sinVal = (q31_t) ((((q63_t) sinVal << 32) + ((q63_t) c * wc)) >> 32);

  /* Calculation of wd */
  /* wd = (oneBy6) * fractCube - (oneBy6) * fract; */
  fractCube = fractCube - fract;
  wd = ((q31_t) (((q63_t) oneBy6 * fractCube) >> 32));
  wd = (wd << 1u);

  /* Read fourth nearest value of output from the sin table */
  d = *tablePtr++;

  /* sinVal += d*wd; */
  sinVal = (q31_t) ((((q63_t) sinVal << 32) + ((q63_t) d * wd)) >> 32);

  /* convert sinVal in 2.30 format to 1.31 format */
  return (__QADD(sinVal, sinVal));

}

/**    
 * @} end of sin group    
 */
