/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1  
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_min_f32.c    
*    
* Description:	Minimum value of a floating-point vector.    
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
 * @defgroup Min Minimum    
 *    
 * Computes the minimum value of an array of data.     
 * The function returns both the minimum value and its position within the array.     
 * There are separate functions for floating-point, Q31, Q15, and Q7 data types.    
 */

/**    
 * @addtogroup Min    
 * @{    
 */


/**    
 * @brief Minimum value of a floating-point vector.    
 * @param[in]       *pSrc points to the input vector    
 * @param[in]       blockSize length of the input vector    
 * @param[out]      *pResult minimum value returned here    
 * @param[out]      *pIndex index of minimum value returned here    
  * @return none.    
 *    
 */

void arm_min_f32(
  float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult,
  uint32_t * pIndex)
{
#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */

  float32_t minVal1, minVal2, out;               /* Temporary variables to store the output value. */
  uint32_t blkCnt, outIndex, count;              /* loop counter */

  /* Initialise the count value. */
  count = 0u;
  /* Initialise the index value to zero. */
  outIndex = 0u;
  /* Load first input value that act as reference value for comparision */
  out = *pSrc++;

  /* Loop unrolling */
  blkCnt = (blockSize - 1u) >> 2u;

  while(blkCnt > 0)
  {
    /* Initialize minVal to the next consecutive values one by one */
    minVal1 = *pSrc++;
    minVal2 = *pSrc++;

    /* compare for the minimum value */
    if(out > minVal1)
    {
      /* Update the minimum value and its index */
      out = minVal1;
      outIndex = count + 1u;
    }

    minVal1 = *pSrc++;

    /* compare for the minimum value */
    if(out > minVal2)
    {
      /* Update the minimum value and its index */
      out = minVal2;
      outIndex = count + 2u;
    }

    minVal2 = *pSrc++;

    /* compare for the minimum value */
    if(out > minVal1)
    {
      /* Update the minimum value and its index */
      out = minVal1;
      outIndex = count + 3u;
    }

    /* compare for the minimum value */
    if(out > minVal2)
    {
      /* Update the minimum value and its index */
      out = minVal2;
      outIndex = count + 4u;
    }

    count += 4u;

    blkCnt--;
  }

  /* if (blockSize - 1u ) is not multiple of 4 */
  blkCnt = (blockSize - 1u) % 4u;

#else

  /* Run the below code for Cortex-M0 */
  float32_t minVal1, out;                        /* Temporary variables to store the output value. */
  uint32_t blkCnt, outIndex;                     /* loop counter */

  /* Initialise the index value to zero. */
  outIndex = 0u;
  /* Load first input value that act as reference value for comparision */
  out = *pSrc++;

  blkCnt = (blockSize - 1u);

#endif //      #ifndef ARM_MATH_CM0_FAMILY

  while(blkCnt > 0)
  {
    /* Initialize minVal to the next consecutive values one by one */
    minVal1 = *pSrc++;

    /* compare for the minimum value */
    if(out > minVal1)
    {
      /* Update the minimum value and it's index */
      out = minVal1;
      outIndex = blockSize - blkCnt;
    }

    blkCnt--;

  }

  /* Store the minimum value and it's index into destination pointers */
  *pResult = out;
  *pIndex = outIndex;
}

/**    
 * @} end of Min group    
 */
