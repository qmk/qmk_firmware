/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_abs_q15.c    
*    
* Description:	Q15 vector absolute value.    
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
 * @addtogroup BasicAbs    
 * @{    
 */

/**    
 * @brief Q15 vector absolute value.    
 * @param[in]       *pSrc points to the input buffer    
 * @param[out]      *pDst points to the output buffer    
 * @param[in]       blockSize number of samples in each vector    
 * @return none.    
 *    
 * <b>Scaling and Overflow Behavior:</b>    
 * \par    
 * The function uses saturating arithmetic.    
 * The Q15 value -1 (0x8000) will be saturated to the maximum allowable positive value 0x7FFF.    
 */

void arm_abs_q15(
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;                               /* loop counter */

#ifndef ARM_MATH_CM0_FAMILY
  __SIMD32_TYPE *simd;

/* Run the below code for Cortex-M4 and Cortex-M3 */

  q15_t in1;                                     /* Input value1 */
  q15_t in2;                                     /* Input value2 */


  /*loop Unrolling */
  blkCnt = blockSize >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
   ** a second loop below computes the remaining 1 to 3 samples. */
  simd = __SIMD32_CONST(pDst);
  while(blkCnt > 0u)
  {
    /* C = |A| */
    /* Read two inputs */
    in1 = *pSrc++;
    in2 = *pSrc++;


    /* Store the Absolute result in the destination buffer by packing the two values, in a single cycle */
#ifndef  ARM_MATH_BIG_ENDIAN
    *simd++ =
      __PKHBT(((in1 > 0) ? in1 : (q15_t)__QSUB16(0, in1)),
              ((in2 > 0) ? in2 : (q15_t)__QSUB16(0, in2)), 16);

#else


    *simd++ =
      __PKHBT(((in2 > 0) ? in2 : (q15_t)__QSUB16(0, in2)),
              ((in1 > 0) ? in1 : (q15_t)__QSUB16(0, in1)), 16);

#endif /* #ifndef  ARM_MATH_BIG_ENDIAN    */

    in1 = *pSrc++;
    in2 = *pSrc++;


#ifndef  ARM_MATH_BIG_ENDIAN

    *simd++ =
      __PKHBT(((in1 > 0) ? in1 : (q15_t)__QSUB16(0, in1)),
              ((in2 > 0) ? in2 : (q15_t)__QSUB16(0, in2)), 16);

#else


    *simd++ =
      __PKHBT(((in2 > 0) ? in2 : (q15_t)__QSUB16(0, in2)),
              ((in1 > 0) ? in1 : (q15_t)__QSUB16(0, in1)), 16);

#endif /* #ifndef  ARM_MATH_BIG_ENDIAN    */

    /* Decrement the loop counter */
    blkCnt--;
  }
  pDst = (q15_t *)simd;
	
  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.    
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4u;

  while(blkCnt > 0u)
  {
    /* C = |A| */
    /* Read the input */
    in1 = *pSrc++;

    /* Calculate absolute value of input and then store the result in the destination buffer. */
    *pDst++ = (in1 > 0) ? in1 : (q15_t)__QSUB16(0, in1);

    /* Decrement the loop counter */
    blkCnt--;
  }

#else

  /* Run the below code for Cortex-M0 */

  q15_t in;                                      /* Temporary input variable */

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

  while(blkCnt > 0u)
  {
    /* C = |A| */
    /* Read the input */
    in = *pSrc++;

    /* Calculate absolute value of input and then store the result in the destination buffer. */
    *pDst++ = (in > 0) ? in : ((in == (q15_t) 0x8000) ? 0x7fff : -in);

    /* Decrement the loop counter */
    blkCnt--;
  }

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

}

/**    
 * @} end of BasicAbs group    
 */
