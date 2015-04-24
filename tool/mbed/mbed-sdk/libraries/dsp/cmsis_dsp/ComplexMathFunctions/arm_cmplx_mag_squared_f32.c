/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_cmplx_mag_squared_f32.c    
*    
* Description:	Floating-point complex magnitude squared.    
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
* ---------------------------------------------------------------------------- */
#include "arm_math.h"

/**        
 * @ingroup groupCmplxMath        
 */

/**        
 * @defgroup cmplx_mag_squared Complex Magnitude Squared        
 *        
 * Computes the magnitude squared of the elements of a complex data vector.        
 *       
 * The <code>pSrc</code> points to the source data and        
 * <code>pDst</code> points to the where the result should be written.        
 * <code>numSamples</code> specifies the number of complex samples        
 * in the input array and the data is stored in an interleaved fashion        
 * (real, imag, real, imag, ...).        
 * The input array has a total of <code>2*numSamples</code> values;        
 * the output array has a total of <code>numSamples</code> values.        
 *        
 * The underlying algorithm is used:        
 *        
 * <pre>        
 * for(n=0; n<numSamples; n++) {        
 *     pDst[n] = pSrc[(2*n)+0]^2 + pSrc[(2*n)+1]^2;        
 * }        
 * </pre>        
 *        
 * There are separate functions for floating-point, Q15, and Q31 data types.        
 */

/**        
 * @addtogroup cmplx_mag_squared        
 * @{        
 */


/**        
 * @brief  Floating-point complex magnitude squared        
 * @param[in]  *pSrc points to the complex input vector        
 * @param[out]  *pDst points to the real output vector        
 * @param[in]  numSamples number of complex samples in the input vector        
 * @return none.        
 */

void arm_cmplx_mag_squared_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t numSamples)
{
  float32_t real, imag;                          /* Temporary variables to store real and imaginary values */
  uint32_t blkCnt;                               /* loop counter */

#ifndef ARM_MATH_CM0_FAMILY
  float32_t real1, real2, real3, real4;          /* Temporary variables to hold real values */
  float32_t imag1, imag2, imag3, imag4;          /* Temporary variables to hold imaginary values */
  float32_t mul1, mul2, mul3, mul4;              /* Temporary variables */
  float32_t mul5, mul6, mul7, mul8;              /* Temporary variables */
  float32_t out1, out2, out3, out4;              /* Temporary variables to hold output values */

  /*loop Unrolling */
  blkCnt = numSamples >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.        
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* C[0] = (A[0] * A[0] + A[1] * A[1]) */
    /* read real input sample from source buffer */
    real1 = pSrc[0];
    /* read imaginary input sample from source buffer */
    imag1 = pSrc[1];

    /* calculate power of real value */
    mul1 = real1 * real1;

    /* read real input sample from source buffer */
    real2 = pSrc[2];

    /* calculate power of imaginary value */
    mul2 = imag1 * imag1;

    /* read imaginary input sample from source buffer */
    imag2 = pSrc[3];

    /* calculate power of real value */
    mul3 = real2 * real2;

    /* read real input sample from source buffer */
    real3 = pSrc[4];

    /* calculate power of imaginary value */
    mul4 = imag2 * imag2;

    /* read imaginary input sample from source buffer */
    imag3 = pSrc[5];

    /* calculate power of real value */
    mul5 = real3 * real3;
    /* calculate power of imaginary value */
    mul6 = imag3 * imag3;

    /* read real input sample from source buffer */
    real4 = pSrc[6];

    /* accumulate real and imaginary powers */
    out1 = mul1 + mul2;

    /* read imaginary input sample from source buffer */
    imag4 = pSrc[7];

    /* accumulate real and imaginary powers */
    out2 = mul3 + mul4;

    /* calculate power of real value */
    mul7 = real4 * real4;
    /* calculate power of imaginary value */
    mul8 = imag4 * imag4;

    /* store output to destination */
    pDst[0] = out1;

    /* accumulate real and imaginary powers */
    out3 = mul5 + mul6;

    /* store output to destination */
    pDst[1] = out2;

    /* accumulate real and imaginary powers */
    out4 = mul7 + mul8;

    /* store output to destination */
    pDst[2] = out3;

    /* increment destination pointer by 8 to process next samples */
    pSrc += 8u;

    /* store output to destination */
    pDst[3] = out4;

    /* increment destination pointer by 4 to process next samples */
    pDst += 4u;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the numSamples is not a multiple of 4, compute any remaining output samples here.        
   ** No loop unrolling is used. */
  blkCnt = numSamples % 0x4u;

#else

  /* Run the below code for Cortex-M0 */

  blkCnt = numSamples;

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

  while(blkCnt > 0u)
  {
    /* C[0] = (A[0] * A[0] + A[1] * A[1]) */
    real = *pSrc++;
    imag = *pSrc++;

    /* out = (real * real) + (imag * imag) */
    /* store the result in the destination buffer. */
    *pDst++ = (real * real) + (imag * imag);

    /* Decrement the loop counter */
    blkCnt--;
  }
}

/**        
 * @} end of cmplx_mag_squared group        
 */
