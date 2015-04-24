/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1  
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_rms_q15.c    
*    
* Description:	Root Mean Square of the elements of a Q15 vector.  
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
 * @addtogroup RMS    
 * @{    
 */

/**    
 * @brief Root Mean Square of the elements of a Q15 vector.    
 * @param[in]       *pSrc points to the input vector    
 * @param[in]       blockSize length of the input vector    
 * @param[out]      *pResult rms value returned here    
 * @return none.    
 *    
 * @details    
 * <b>Scaling and Overflow Behavior:</b>    
 *    
 * \par    
 * The function is implemented using a 64-bit internal accumulator.    
 * The input is represented in 1.15 format.    
 * Intermediate multiplication yields a 2.30 format, and this    
 * result is added without saturation to a 64-bit accumulator in 34.30 format.    
 * With 33 guard bits in the accumulator, there is no risk of overflow, and the    
 * full precision of the intermediate multiplication is preserved.    
 * Finally, the 34.30 result is truncated to 34.15 format by discarding the lower     
 * 15 bits, and then saturated to yield a result in 1.15 format.    
 *    
 */

void arm_rms_q15(
  q15_t * pSrc,
  uint32_t blockSize,
  q15_t * pResult)
{
  q63_t sum = 0;                                 /* accumulator */

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */

  q31_t in;                                      /* temporary variable to store the input value */
  q15_t in1;                                     /* temporary variable to store the input value */
  uint32_t blkCnt;                               /* loop counter */

  /* loop Unrolling */
  blkCnt = blockSize >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1]) */
    /* Compute sum of the squares and then store the results in a temporary variable, sum */
    in = *__SIMD32(pSrc)++;
    sum = __SMLALD(in, in, sum);
    in = *__SIMD32(pSrc)++;
    sum = __SMLALD(in, in, sum);

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.    
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4u;

  while(blkCnt > 0u)
  {
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1]) */
    /* Compute sum of the squares and then store the results in a temporary variable, sum */
    in1 = *pSrc++;
    sum = __SMLALD(in1, in1, sum);

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* Truncating and saturating the accumulator to 1.15 format */
  in = (q31_t)(sum >> 15);

  in1 = __SSAT(in / blockSize, 16);

  /* Store the result in the destination */
  arm_sqrt_q15(in1, pResult);

#else

  /* Run the below code for Cortex-M0 */

  q15_t in;                                      /* temporary variable to store the input value */
  q31_t tmp;                                     /* temporary variable to store the input value */
  uint32_t blkCnt;                               /* loop counter */

  /* Loop over blockSize number of values */
  blkCnt = blockSize;

  while(blkCnt > 0u)
  {
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1]) */
    /* Compute sum of the squares and then store the results in a temporary variable, sum */
    in = *pSrc++;
    sum += ((q31_t) in * in);

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* Truncating and saturating the accumulator to 1.15 format */
  tmp = (q31_t)(sum >> 15);

  in = __SSAT(tmp / blockSize, 16);

  /* Store the result in the destination */
  arm_sqrt_q15(in, pResult);

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

}

/**    
 * @} end of RMS group    
 */
