/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_shift_q7.c    
*    
* Description:	Processing function for the Q7 Shifting    
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
 * @addtogroup shift        
 * @{        
 */


/**        
 * @brief  Shifts the elements of a Q7 vector a specified number of bits.        
 * @param[in]  *pSrc points to the input vector        
 * @param[in]  shiftBits number of bits to shift.  A positive value shifts left; a negative value shifts right.        
 * @param[out]  *pDst points to the output vector        
 * @param[in]  blockSize number of samples in the vector        
 * @return none.        
 *    
 * \par Conditions for optimum performance    
 *  Input and output buffers should be aligned by 32-bit    
 *    
 *        
 * <b>Scaling and Overflow Behavior:</b>        
 * \par        
 * The function uses saturating arithmetic.        
 * Results outside of the allowable Q7 range [0x8 0x7F] will be saturated.        
 */

void arm_shift_q7(
  q7_t * pSrc,
  int8_t shiftBits,
  q7_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;                               /* loop counter */
  uint8_t sign;                                  /* Sign of shiftBits */

#ifndef ARM_MATH_CM0_FAMILY

/* Run the below code for Cortex-M4 and Cortex-M3 */
  q7_t in1;                                      /* Input value1 */
  q7_t in2;                                      /* Input value2 */
  q7_t in3;                                      /* Input value3 */
  q7_t in4;                                      /* Input value4 */


  /*loop Unrolling */
  blkCnt = blockSize >> 2u;

  /* Getting the sign of shiftBits */
  sign = (shiftBits & 0x80);

  /* If the shift value is positive then do right shift else left shift */
  if(sign == 0u)
  {
    /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
     ** a second loop below computes the remaining 1 to 3 samples. */
    while(blkCnt > 0u)
    {
      /* C = A << shiftBits */
      /* Read 4 inputs */
      in1 = *pSrc;
      in2 = *(pSrc + 1);
      in3 = *(pSrc + 2);
      in4 = *(pSrc + 3);

      /* Store the Shifted result in the destination buffer in single cycle by packing the outputs */
      *__SIMD32(pDst)++ = __PACKq7(__SSAT((in1 << shiftBits), 8),
                                   __SSAT((in2 << shiftBits), 8),
                                   __SSAT((in3 << shiftBits), 8),
                                   __SSAT((in4 << shiftBits), 8));
      /* Update source pointer to process next sampels */
      pSrc += 4u;

      /* Decrement the loop counter */
      blkCnt--;
    }

    /* If the blockSize is not a multiple of 4, compute any remaining output samples here.        
     ** No loop unrolling is used. */
    blkCnt = blockSize % 0x4u;

    while(blkCnt > 0u)
    {
      /* C = A << shiftBits */
      /* Shift the input and then store the result in the destination buffer. */
      *pDst++ = (q7_t) __SSAT((*pSrc++ << shiftBits), 8);

      /* Decrement the loop counter */
      blkCnt--;
    }
  }
  else
  {
    shiftBits = -shiftBits;
    /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
     ** a second loop below computes the remaining 1 to 3 samples. */
    while(blkCnt > 0u)
    {
      /* C = A >> shiftBits */
      /* Read 4 inputs */
      in1 = *pSrc;
      in2 = *(pSrc + 1);
      in3 = *(pSrc + 2);
      in4 = *(pSrc + 3);

      /* Store the Shifted result in the destination buffer in single cycle by packing the outputs */
      *__SIMD32(pDst)++ = __PACKq7((in1 >> shiftBits), (in2 >> shiftBits),
                                   (in3 >> shiftBits), (in4 >> shiftBits));


      pSrc += 4u;

      /* Decrement the loop counter */
      blkCnt--;
    }

    /* If the blockSize is not a multiple of 4, compute any remaining output samples here.    
     ** No loop unrolling is used. */
    blkCnt = blockSize % 0x4u;

    while(blkCnt > 0u)
    {
      /* C = A >> shiftBits */
      /* Shift the input and then store the result in the destination buffer. */
      in1 = *pSrc++;
      *pDst++ = (in1 >> shiftBits);

      /* Decrement the loop counter */
      blkCnt--;
    }
  }

#else

  /* Run the below code for Cortex-M0 */

  /* Getting the sign of shiftBits */
  sign = (shiftBits & 0x80);

  /* If the shift value is positive then do right shift else left shift */
  if(sign == 0u)
  {
    /* Initialize blkCnt with number of samples */
    blkCnt = blockSize;

    while(blkCnt > 0u)
    {
      /* C = A << shiftBits */
      /* Shift the input and then store the result in the destination buffer. */
      *pDst++ = (q7_t) __SSAT(((q15_t) * pSrc++ << shiftBits), 8);

      /* Decrement the loop counter */
      blkCnt--;
    }
  }
  else
  {
    /* Initialize blkCnt with number of samples */
    blkCnt = blockSize;

    while(blkCnt > 0u)
    {
      /* C = A >> shiftBits */
      /* Shift the input and then store the result in the destination buffer. */
      *pDst++ = (*pSrc++ >> -shiftBits);

      /* Decrement the loop counter */
      blkCnt--;
    }
  }

#endif /* #ifndef ARM_MATH_CM0_FAMILY */
}

/**        
 * @} end of shift group        
 */
