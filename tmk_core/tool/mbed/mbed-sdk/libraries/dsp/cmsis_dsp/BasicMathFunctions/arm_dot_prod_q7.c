/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_dot_prod_q7.c    
*    
* Description:	Q7 dot product.    
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
 * @ingroup groupMath    
 */

/**    
 * @addtogroup dot_prod    
 * @{    
 */

/**    
 * @brief Dot product of Q7 vectors.    
 * @param[in]       *pSrcA points to the first input vector    
 * @param[in]       *pSrcB points to the second input vector    
 * @param[in]       blockSize number of samples in each vector    
 * @param[out]      *result output result returned here    
 * @return none.    
 *    
 * <b>Scaling and Overflow Behavior:</b>    
 * \par    
 * The intermediate multiplications are in 1.7 x 1.7 = 2.14 format and these    
 * results are added to an accumulator in 18.14 format.    
 * Nonsaturating additions are used and there is no danger of wrap around as long as    
 * the vectors are less than 2^18 elements long.    
 * The return result is in 18.14 format.    
 */

void arm_dot_prod_q7(
  q7_t * pSrcA,
  q7_t * pSrcB,
  uint32_t blockSize,
  q31_t * result)
{
  uint32_t blkCnt;                               /* loop counter */

  q31_t sum = 0;                                 /* Temporary variables to store output */

#ifndef ARM_MATH_CM0_FAMILY

/* Run the below code for Cortex-M4 and Cortex-M3 */

  q31_t input1, input2;                          /* Temporary variables to store input */
  q31_t inA1, inA2, inB1, inB2;                  /* Temporary variables to store input */



  /*loop Unrolling */
  blkCnt = blockSize >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* read 4 samples at a time from sourceA */
    input1 = *__SIMD32(pSrcA)++;
    /* read 4 samples at a time from sourceB */
    input2 = *__SIMD32(pSrcB)++;

    /* extract two q7_t samples to q15_t samples */
    inA1 = __SXTB16(__ROR(input1, 8));
    /* extract reminaing two samples */
    inA2 = __SXTB16(input1);
    /* extract two q7_t samples to q15_t samples */
    inB1 = __SXTB16(__ROR(input2, 8));
    /* extract reminaing two samples */
    inB2 = __SXTB16(input2);

    /* multiply and accumulate two samples at a time */
    sum = __SMLAD(inA1, inB1, sum);
    sum = __SMLAD(inA2, inB2, sum);

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.    
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4u;

  while(blkCnt > 0u)
  {
    /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */
    /* Dot product and then store the results in a temporary buffer. */
    sum = __SMLAD(*pSrcA++, *pSrcB++, sum);

    /* Decrement the loop counter */
    blkCnt--;
  }

#else

  /* Run the below code for Cortex-M0 */



  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

  while(blkCnt > 0u)
  {
    /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */
    /* Dot product and then store the results in a temporary buffer. */
    sum += (q31_t) ((q15_t) * pSrcA++ * *pSrcB++);

    /* Decrement the loop counter */
    blkCnt--;
  }

#endif /* #ifndef ARM_MATH_CM0_FAMILY */


  /* Store the result in the destination buffer in 18.14 format */
  *result = sum;
}

/**    
 * @} end of dot_prod group    
 */
