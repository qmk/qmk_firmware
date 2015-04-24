/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1  
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_max_q15.c    
*    
* Description:	Maximum value of a Q15 vector.    
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
 * @ingroup groupStats    
 */

/**    
 * @addtogroup Max    
 * @{    
 */


/**    
 * @brief Maximum value of a Q15 vector.    
 * @param[in]       *pSrc points to the input vector    
 * @param[in]       blockSize length of the input vector    
 * @param[out]      *pResult maximum value returned here    
 * @param[out]      *pIndex index of maximum value returned here    
 * @return none.    
 */

void arm_max_q15(
  q15_t * pSrc,
  uint32_t blockSize,
  q15_t * pResult,
  uint32_t * pIndex)
{
#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */
  q15_t maxVal1, maxVal2, out;                   /* Temporary variables to store the output value. */
  uint32_t blkCnt, outIndex, count;              /* loop counter */

  /* Initialise the count value. */
  count = 0u;
  /* Initialise the index value to zero. */
  outIndex = 0u;
  /* Load first input value that act as reference value for comparision */
  out = *pSrc++;

  /* Loop unrolling */
  blkCnt = (blockSize - 1u) >> 2u;

  /* Run the below code for Cortex-M4 and Cortex-M3 */
  while(blkCnt > 0u)
  {
    /* Initialize maxVal to the next consecutive values one by one */
    maxVal1 = *pSrc++;

    maxVal2 = *pSrc++;

    /* compare for the maximum value */
    if(out < maxVal1)
    {
      /* Update the maximum value and its index */
      out = maxVal1;
      outIndex = count + 1u;
    }

    maxVal1 = *pSrc++;

    /* compare for the maximum value */
    if(out < maxVal2)
    {
      /* Update the maximum value and its index */
      out = maxVal2;
      outIndex = count + 2u;
    }

    maxVal2 = *pSrc++;

    /* compare for the maximum value */
    if(out < maxVal1)
    {
      /* Update the maximum value and its index */
      out = maxVal1;
      outIndex = count + 3u;
    }

    /* compare for the maximum value */
    if(out < maxVal2)
    {
      /* Update the maximum value and its index */
      out = maxVal2;
      outIndex = count + 4u;
    }

    count += 4u;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* if (blockSize - 1u) is not multiple of 4 */
  blkCnt = (blockSize - 1u) % 4u;

#else

  /* Run the below code for Cortex-M0 */
  q15_t maxVal1, out;                            /* Temporary variables to store the output value. */
  uint32_t blkCnt, outIndex;                     /* loop counter */

  blkCnt = (blockSize - 1u);

  /* Initialise the index value to zero. */
  outIndex = 0u;
  /* Load first input value that act as reference value for comparision */
  out = *pSrc++;

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

  while(blkCnt > 0u)
  {
    /* Initialize maxVal to the next consecutive values one by one */
    maxVal1 = *pSrc++;

    /* compare for the maximum value */
    if(out < maxVal1)
    {
      /* Update the maximum value and it's index */
      out = maxVal1;
      outIndex = blockSize - blkCnt;
    }
    /* Decrement the loop counter */
    blkCnt--;

  }

  /* Store the maximum value and its index into destination pointers */
  *pResult = out;
  *pIndex = outIndex;
}

/**    
 * @} end of Max group    
 */
