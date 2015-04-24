/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_abs_q7.c    
*    
* Description:	Q7 vector absolute value.    
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
 * @brief Q7 vector absolute value.        
 * @param[in]       *pSrc points to the input buffer        
 * @param[out]      *pDst points to the output buffer        
 * @param[in]       blockSize number of samples in each vector        
 * @return none.        
 *    
 * \par Conditions for optimum performance    
 *  Input and output buffers should be aligned by 32-bit    
 *    
 *        
 * <b>Scaling and Overflow Behavior:</b>        
 * \par        
 * The function uses saturating arithmetic.        
 * The Q7 value -1 (0x80) will be saturated to the maximum allowable positive value 0x7F.        
 */

void arm_abs_q7(
  q7_t * pSrc,
  q7_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;                               /* loop counter */
  q7_t in;                                       /* Input value1 */

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */
  q31_t in1, in2, in3, in4;                      /* temporary input variables */
  q31_t out1, out2, out3, out4;                  /* temporary output variables */

  /*loop Unrolling */
  blkCnt = blockSize >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* C = |A| */
    /* Read inputs */
    in1 = (q31_t) * pSrc;
    in2 = (q31_t) * (pSrc + 1);
    in3 = (q31_t) * (pSrc + 2);

    /* find absolute value */
    out1 = (in1 > 0) ? in1 : (q31_t)__QSUB8(0, in1);

    /* read input */
    in4 = (q31_t) * (pSrc + 3);

    /* find absolute value */
    out2 = (in2 > 0) ? in2 : (q31_t)__QSUB8(0, in2);

    /* store result to destination */
    *pDst = (q7_t) out1;

    /* find absolute value */
    out3 = (in3 > 0) ? in3 : (q31_t)__QSUB8(0, in3);

    /* find absolute value */
    out4 = (in4 > 0) ? in4 : (q31_t)__QSUB8(0, in4);

    /* store result to destination */
    *(pDst + 1) = (q7_t) out2;

    /* store result to destination */
    *(pDst + 2) = (q7_t) out3;

    /* store result to destination */
    *(pDst + 3) = (q7_t) out4;

    /* update pointers to process next samples */
    pSrc += 4u;
    pDst += 4u;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.    
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4u;
#else

  /* Run the below code for Cortex-M0 */
  blkCnt = blockSize;

#endif //      #define ARM_MATH_CM0_FAMILY

  while(blkCnt > 0u)
  {
    /* C = |A| */
    /* Read the input */
    in = *pSrc++;

    /* Store the Absolute result in the destination buffer */
    *pDst++ = (in > 0) ? in : ((in == (q7_t) 0x80) ? 0x7f : -in);

    /* Decrement the loop counter */
    blkCnt--;
  }
}

/**        
 * @} end of BasicAbs group        
 */
