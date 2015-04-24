/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_cmplx_conj_q15.c    
*    
* Description:	Q15 complex conjugate.    
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
 * @addtogroup cmplx_conj    
 * @{    
 */

/**    
 * @brief  Q15 complex conjugate.    
 * @param  *pSrc points to the input vector    
 * @param  *pDst points to the output vector    
 * @param  numSamples number of complex samples in each vector    
 * @return none.    
 *    
 * <b>Scaling and Overflow Behavior:</b>    
 * \par    
 * The function uses saturating arithmetic.    
 * The Q15 value -1 (0x8000) will be saturated to the maximum allowable positive value 0x7FFF.    
 */

void arm_cmplx_conj_q15(
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t numSamples)
{

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */
  uint32_t blkCnt;                               /* loop counter */
  q31_t in1, in2, in3, in4;
  q31_t zero = 0;

  /*loop Unrolling */
  blkCnt = numSamples >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* C[0]+jC[1] = A[0]+ j (-1) A[1] */
    /* Calculate Complex Conjugate and then store the results in the destination buffer. */
    in1 = *__SIMD32(pSrc)++;
    in2 = *__SIMD32(pSrc)++;
    in3 = *__SIMD32(pSrc)++;
    in4 = *__SIMD32(pSrc)++;

#ifndef ARM_MATH_BIG_ENDIAN

    in1 = __QASX(zero, in1);
    in2 = __QASX(zero, in2);
    in3 = __QASX(zero, in3);
    in4 = __QASX(zero, in4);

#else

    in1 = __QSAX(zero, in1);
    in2 = __QSAX(zero, in2);
    in3 = __QSAX(zero, in3);
    in4 = __QSAX(zero, in4);

#endif //       #ifndef ARM_MATH_BIG_ENDIAN

    in1 = ((uint32_t) in1 >> 16) | ((uint32_t) in1 << 16);
    in2 = ((uint32_t) in2 >> 16) | ((uint32_t) in2 << 16);
    in3 = ((uint32_t) in3 >> 16) | ((uint32_t) in3 << 16);
    in4 = ((uint32_t) in4 >> 16) | ((uint32_t) in4 << 16);

    *__SIMD32(pDst)++ = in1;
    *__SIMD32(pDst)++ = in2;
    *__SIMD32(pDst)++ = in3;
    *__SIMD32(pDst)++ = in4;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the numSamples is not a multiple of 4, compute any remaining output samples here.    
   ** No loop unrolling is used. */
  blkCnt = numSamples % 0x4u;

  while(blkCnt > 0u)
  {
    /* C[0]+jC[1] = A[0]+ j (-1) A[1] */
    /* Calculate Complex Conjugate and then store the results in the destination buffer. */
    *pDst++ = *pSrc++;
    *pDst++ = __SSAT(-*pSrc++, 16);

    /* Decrement the loop counter */
    blkCnt--;
  }

#else

  q15_t in;

  /* Run the below code for Cortex-M0 */

  while(numSamples > 0u)
  {
    /* realOut + j (imagOut) = realIn+ j (-1) imagIn */
    /* Calculate Complex Conjugate and then store the results in the destination buffer. */
    *pDst++ = *pSrc++;
    in = *pSrc++;
    *pDst++ = (in == (q15_t) 0x8000) ? 0x7fff : -in;

    /* Decrement the loop counter */
    numSamples--;
  }

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

}

/**    
 * @} end of cmplx_conj group    
 */
