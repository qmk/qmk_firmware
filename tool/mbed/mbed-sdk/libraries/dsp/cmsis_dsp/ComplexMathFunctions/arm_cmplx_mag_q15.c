/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_cmplx_mag_q15.c    
*    
* Description:	Q15 complex magnitude.    
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
 * @addtogroup cmplx_mag    
 * @{    
 */


/**    
 * @brief  Q15 complex magnitude    
 * @param  *pSrc points to the complex input vector    
 * @param  *pDst points to the real output vector    
 * @param  numSamples number of complex samples in the input vector    
 * @return none.    
 *    
 * <b>Scaling and Overflow Behavior:</b>    
 * \par    
 * The function implements 1.15 by 1.15 multiplications and finally output is converted into 2.14 format.    
 */

void arm_cmplx_mag_q15(
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t numSamples)
{
  q31_t acc0, acc1;                              /* Accumulators */

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */
  uint32_t blkCnt;                               /* loop counter */
  q31_t in1, in2, in3, in4;
  q31_t acc2, acc3;


  /*loop Unrolling */
  blkCnt = numSamples >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {

    /* C[0] = sqrt(A[0] * A[0] + A[1] * A[1]) */
    in1 = *__SIMD32(pSrc)++;
    in2 = *__SIMD32(pSrc)++;
    in3 = *__SIMD32(pSrc)++;
    in4 = *__SIMD32(pSrc)++;

    acc0 = __SMUAD(in1, in1);
    acc1 = __SMUAD(in2, in2);
    acc2 = __SMUAD(in3, in3);
    acc3 = __SMUAD(in4, in4);

    /* store the result in 2.14 format in the destination buffer. */
    arm_sqrt_q15((q15_t) ((acc0) >> 17), pDst++);
    arm_sqrt_q15((q15_t) ((acc1) >> 17), pDst++);
    arm_sqrt_q15((q15_t) ((acc2) >> 17), pDst++);
    arm_sqrt_q15((q15_t) ((acc3) >> 17), pDst++);

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the numSamples is not a multiple of 4, compute any remaining output samples here.    
   ** No loop unrolling is used. */
  blkCnt = numSamples % 0x4u;

  while(blkCnt > 0u)
  {
    /* C[0] = sqrt(A[0] * A[0] + A[1] * A[1]) */
    in1 = *__SIMD32(pSrc)++;
    acc0 = __SMUAD(in1, in1);

    /* store the result in 2.14 format in the destination buffer. */
    arm_sqrt_q15((q15_t) (acc0 >> 17), pDst++);

    /* Decrement the loop counter */
    blkCnt--;
  }

#else

  /* Run the below code for Cortex-M0 */
  q15_t real, imag;                              /* Temporary variables to hold input values */

  while(numSamples > 0u)
  {
    /* out = sqrt(real * real + imag * imag) */
    real = *pSrc++;
    imag = *pSrc++;

    acc0 = (real * real);
    acc1 = (imag * imag);

    /* store the result in 2.14 format in the destination buffer. */
    arm_sqrt_q15((q15_t) (((q63_t) acc0 + acc1) >> 17), pDst++);

    /* Decrement the loop counter */
    numSamples--;
  }

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

}

/**    
 * @} end of cmplx_mag group    
 */
