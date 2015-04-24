/* ----------------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013 
* $Revision: 	V1.4.1  
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_q15_to_q31.c    
*    
* Description:	Converts the elements of the Q15 vector to Q31 vector.  
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
 * @ingroup groupSupport    
 */

/**    
 * @addtogroup q15_to_x    
 * @{    
 */

/**    
 * @brief Converts the elements of the Q15 vector to Q31 vector.     
 * @param[in]       *pSrc points to the Q15 input vector    
 * @param[out]      *pDst points to the Q31 output vector   
 * @param[in]       blockSize length of the input vector    
 * @return none.    
 *    
 * \par Description:    
 *    
 * The equation used for the conversion process is:   
 *   
 * <pre>    
 * 	pDst[n] = (q31_t) pSrc[n] << 16;   0 <= n < blockSize.    
 * </pre>    
 *   
 */


void arm_q15_to_q31(
  q15_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize)
{
  q15_t *pIn = pSrc;                             /* Src pointer */
  uint32_t blkCnt;                               /* loop counter */

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */
  q31_t in1, in2;
  q31_t out1, out2, out3, out4;

  /*loop Unrolling */
  blkCnt = blockSize >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* C = (q31_t)A << 16 */
    /* convert from q15 to q31 and then store the results in the destination buffer */
    in1 = *__SIMD32(pIn)++;
    in2 = *__SIMD32(pIn)++;

#ifndef ARM_MATH_BIG_ENDIAN

    /* extract lower 16 bits to 32 bit result */
    out1 = in1 << 16u;
    /* extract upper 16 bits to 32 bit result */
    out2 = in1 & 0xFFFF0000;
    /* extract lower 16 bits to 32 bit result */
    out3 = in2 << 16u;
    /* extract upper 16 bits to 32 bit result */
    out4 = in2 & 0xFFFF0000;

#else

    /* extract upper 16 bits to 32 bit result */
    out1 = in1 & 0xFFFF0000;
    /* extract lower 16 bits to 32 bit result */
    out2 = in1 << 16u;
    /* extract upper 16 bits to 32 bit result */
    out3 = in2 & 0xFFFF0000;
    /* extract lower 16 bits to 32 bit result */
    out4 = in2 << 16u;

#endif //      #ifndef ARM_MATH_BIG_ENDIAN

    *pDst++ = out1;
    *pDst++ = out2;
    *pDst++ = out3;
    *pDst++ = out4;

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
    /* C = (q31_t)A << 16 */
    /* convert from q15 to q31 and then store the results in the destination buffer */
    *pDst++ = (q31_t) * pIn++ << 16;

    /* Decrement the loop counter */
    blkCnt--;
  }

}

/**    
 * @} end of q15_to_x group    
 */
