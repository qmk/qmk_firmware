/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1  
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_power_q7.c    
*    
* Description:	Sum of the squares of the elements of a Q7 vector.    
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
 * @addtogroup power    
 * @{    
 */

/**    
 * @brief Sum of the squares of the elements of a Q7 vector.    
 * @param[in]       *pSrc points to the input vector    
 * @param[in]       blockSize length of the input vector    
 * @param[out]      *pResult sum of the squares value returned here    
 * @return none.    
 *    
 * @details    
 * <b>Scaling and Overflow Behavior:</b>    
 *    
 * \par    
 * The function is implemented using a 32-bit internal accumulator.     
 * The input is represented in 1.7 format.   
 * Intermediate multiplication yields a 2.14 format, and this    
 * result is added without saturation to an accumulator in 18.14 format.    
 * With 17 guard bits in the accumulator, there is no risk of overflow, and the    
 * full precision of the intermediate multiplication is preserved.    
 * Finally, the return result is in 18.14 format.     
 *    
 */

void arm_power_q7(
  q7_t * pSrc,
  uint32_t blockSize,
  q31_t * pResult)
{
  q31_t sum = 0;                                 /* Temporary result storage */
  q7_t in;                                       /* Temporary variable to store input */
  uint32_t blkCnt;                               /* loop counter */

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */

  q31_t input1;                                  /* Temporary variable to store packed input */
  q31_t in1, in2;                                /* Temporary variables to store input */

  /*loop Unrolling */
  blkCnt = blockSize >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* Reading two inputs of pSrc vector and packing */
    input1 = *__SIMD32(pSrc)++;

    in1 = __SXTB16(__ROR(input1, 8));
    in2 = __SXTB16(input1);

    /* C = A[0] * A[0] + A[1] * A[1] + A[2] * A[2] + ... + A[blockSize-1] * A[blockSize-1] */
    /* calculate power and accumulate to accumulator */
    sum = __SMLAD(in1, in1, sum);
    sum = __SMLAD(in2, in2, sum);

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.    
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4u;

#else

  /* Run the below code for Cortex-M0 */

  /* Loop over blockSize number of values */
  blkCnt = blockSize;

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

  while(blkCnt > 0u)
  {
    /* C = A[0] * A[0] + A[1] * A[1] + A[2] * A[2] + ... + A[blockSize-1] * A[blockSize-1] */
    /* Compute Power and then store the result in a temporary variable, sum. */
    in = *pSrc++;
    sum += ((q15_t) in * in);

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* Store the result in 18.14 format  */
  *pResult = sum;
}

/**    
 * @} end of power group    
 */
