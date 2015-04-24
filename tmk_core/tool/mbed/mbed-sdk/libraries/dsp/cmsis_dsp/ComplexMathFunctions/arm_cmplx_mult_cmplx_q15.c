/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:	    arm_cmplx_mult_cmplx_q15.c    
*    
* Description:	Q15 complex-by-complex multiplication    
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
 * @ingroup groupCmplxMath    
 */

/**    
 * @addtogroup CmplxByCmplxMult    
 * @{    
 */

/**    
 * @brief  Q15 complex-by-complex multiplication    
 * @param[in]  *pSrcA points to the first input vector    
 * @param[in]  *pSrcB points to the second input vector    
 * @param[out]  *pDst  points to the output vector    
 * @param[in]  numSamples number of complex samples in each vector    
 * @return none.    
 *    
 * <b>Scaling and Overflow Behavior:</b>    
 * \par    
 * The function implements 1.15 by 1.15 multiplications and finally output is converted into 3.13 format.    
 */

void arm_cmplx_mult_cmplx_q15(
  q15_t * pSrcA,
  q15_t * pSrcB,
  q15_t * pDst,
  uint32_t numSamples)
{
  q15_t a, b, c, d;                              /* Temporary variables to store real and imaginary values */

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */
  uint32_t blkCnt;                               /* loop counters */

  /* loop Unrolling */
  blkCnt = numSamples >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */
    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    /* store the result in 3.13 format in the destination buffer. */
    *pDst++ =
      (q15_t) (q31_t) (((q31_t) a * c) >> 17) - (((q31_t) b * d) >> 17);
    /* store the result in 3.13 format in the destination buffer. */
    *pDst++ =
      (q15_t) (q31_t) (((q31_t) a * d) >> 17) + (((q31_t) b * c) >> 17);

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    /* store the result in 3.13 format in the destination buffer. */
    *pDst++ =
      (q15_t) (q31_t) (((q31_t) a * c) >> 17) - (((q31_t) b * d) >> 17);
    /* store the result in 3.13 format in the destination buffer. */
    *pDst++ =
      (q15_t) (q31_t) (((q31_t) a * d) >> 17) + (((q31_t) b * c) >> 17);

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    /* store the result in 3.13 format in the destination buffer. */
    *pDst++ =
      (q15_t) (q31_t) (((q31_t) a * c) >> 17) - (((q31_t) b * d) >> 17);
    /* store the result in 3.13 format in the destination buffer. */
    *pDst++ =
      (q15_t) (q31_t) (((q31_t) a * d) >> 17) + (((q31_t) b * c) >> 17);

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    /* store the result in 3.13 format in the destination buffer. */
    *pDst++ =
      (q15_t) (q31_t) (((q31_t) a * c) >> 17) - (((q31_t) b * d) >> 17);
    /* store the result in 3.13 format in the destination buffer. */
    *pDst++ =
      (q15_t) (q31_t) (((q31_t) a * d) >> 17) + (((q31_t) b * c) >> 17);

    /* Decrement the blockSize loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.    
   ** No loop unrolling is used. */
  blkCnt = numSamples % 0x4u;

  while(blkCnt > 0u)
  {
    /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */
    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    /* store the result in 3.13 format in the destination buffer. */
    *pDst++ =
      (q15_t) (q31_t) (((q31_t) a * c) >> 17) - (((q31_t) b * d) >> 17);
    /* store the result in 3.13 format in the destination buffer. */
    *pDst++ =
      (q15_t) (q31_t) (((q31_t) a * d) >> 17) + (((q31_t) b * c) >> 17);

    /* Decrement the blockSize loop counter */
    blkCnt--;
  }

#else

  /* Run the below code for Cortex-M0 */

  while(numSamples > 0u)
  {
    /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */
    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    /* store the result in 3.13 format in the destination buffer. */
    *pDst++ =
      (q15_t) (q31_t) (((q31_t) a * c) >> 17) - (((q31_t) b * d) >> 17);
    /* store the result in 3.13 format in the destination buffer. */
    *pDst++ =
      (q15_t) (q31_t) (((q31_t) a * d) >> 17) + (((q31_t) b * c) >> 17);

    /* Decrement the blockSize loop counter */
    numSamples--;
  }

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

}

/**    
 * @} end of CmplxByCmplxMult group    
 */
