/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1  
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_var_q15.c    
*    
* Description:	Variance of an array of Q15 type.    
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
 * @ingroup groupStats    
 */

/**    
 * @addtogroup variance    
 * @{    
 */

/**    
 * @brief Variance of the elements of a Q15 vector.    
 * @param[in]       *pSrc points to the input vector    
 * @param[in]       blockSize length of the input vector    
 * @param[out]      *pResult variance value returned here    
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


void arm_var_q15(
  q15_t * pSrc,
  uint32_t blockSize,
  q31_t * pResult)
{
  q31_t sum = 0;                                 /* Accumulator */
  q31_t meanOfSquares, squareOfMean;             /* Mean of square and square of mean */
  q15_t mean;                                    /* mean */
  uint32_t blkCnt;                               /* loop counter */
  q15_t t;                                       /* Temporary variable */
  q63_t sumOfSquares = 0;                        /* Accumulator */

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */

  q31_t in;                                      /* Input variable */
  q15_t in1;                                     /* Temporary variable */

  /*loop Unrolling */
  blkCnt = blockSize >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1])  */
    /* Compute Sum of squares of the input samples    
     * and then store the result in a temporary variable, sum. */
    in = *__SIMD32(pSrc)++;
    sum += ((in << 16) >> 16);
    sum += (in >> 16);
    sumOfSquares = __SMLALD(in, in, sumOfSquares);
    in = *__SIMD32(pSrc)++;
    sum += ((in << 16) >> 16);
    sum += (in >> 16);
    sumOfSquares = __SMLALD(in, in, sumOfSquares);

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.    
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4u;

  while(blkCnt > 0u)
  {
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1]) */
    /* Compute Sum of squares of the input samples    
     * and then store the result in a temporary variable, sum. */
    in1 = *pSrc++;
    sum += in1;
    sumOfSquares = __SMLALD(in1, in1, sumOfSquares);

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* Compute Mean of squares of the input samples    
   * and then store the result in a temporary variable, meanOfSquares. */
  t = (q15_t) ((1.0f / (float32_t) (blockSize - 1u)) * 16384);
  sumOfSquares = __SSAT((sumOfSquares >> 15u), 16u);

  meanOfSquares = (q31_t) ((sumOfSquares * t) >> 14u);

#else

  /* Run the below code for Cortex-M0 */

  q15_t in;                                      /* Temporary variable */
  /* Loop over blockSize number of values */
  blkCnt = blockSize;

  while(blkCnt > 0u)
  {
    /* C = (A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1]) */
    /* Compute Sum of squares of the input samples     
     * and then store the result in a temporary variable, sumOfSquares. */
    in = *pSrc++;
    sumOfSquares += (in * in);

    /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) */
    /* Compute sum of all input values and then store the result in a temporary variable, sum. */
    sum += in;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* Compute Mean of squares of the input samples     
   * and then store the result in a temporary variable, meanOfSquares. */
  t = (q15_t) ((1.0f / (float32_t) (blockSize - 1u)) * 16384);
  sumOfSquares = __SSAT((sumOfSquares >> 15u), 16u);
  meanOfSquares = (q31_t) ((sumOfSquares * t) >> 14u);

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

  /* Compute mean of all input values */
  t = (q15_t) ((1.0f / (float32_t) (blockSize * (blockSize - 1u))) * 32768);
  mean = __SSAT(sum, 16u);

  /* Compute square of mean */
  squareOfMean = ((q31_t) mean * mean) >> 15;
  squareOfMean = (q31_t) (((q63_t) squareOfMean * t) >> 15);

  /* Compute variance and then store the result to the destination */
  *pResult = (meanOfSquares - squareOfMean);

}

/**    
 * @} end of variance group    
 */
