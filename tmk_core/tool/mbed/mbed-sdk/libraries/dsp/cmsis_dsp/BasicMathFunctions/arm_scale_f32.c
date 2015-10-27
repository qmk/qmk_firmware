/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_scale_f32.c    
*    
* Description:	Multiplies a floating-point vector by a scalar.    
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
 * @ingroup groupMath        
 */

/**        
 * @defgroup scale Vector Scale        
 *        
 * Multiply a vector by a scalar value.  For floating-point data, the algorithm used is:        
 *        
 * <pre>        
 *     pDst[n] = pSrc[n] * scale,   0 <= n < blockSize.        
 * </pre>        
 *        
 * In the fixed-point Q7, Q15, and Q31 functions, <code>scale</code> is represented by        
 * a fractional multiplication <code>scaleFract</code> and an arithmetic shift <code>shift</code>.        
 * The shift allows the gain of the scaling operation to exceed 1.0.        
 * The algorithm used with fixed-point data is:        
 *        
 * <pre>        
 *     pDst[n] = (pSrc[n] * scaleFract) << shift,   0 <= n < blockSize.        
 * </pre>        
 *        
 * The overall scale factor applied to the fixed-point data is        
 * <pre>        
 *     scale = scaleFract * 2^shift.        
 * </pre>        
 *
 * The functions support in-place computation allowing the source and destination
 * pointers to reference the same memory buffer.
 */

/**        
 * @addtogroup scale        
 * @{        
 */

/**        
 * @brief Multiplies a floating-point vector by a scalar.        
 * @param[in]       *pSrc points to the input vector        
 * @param[in]       scale scale factor to be applied        
 * @param[out]      *pDst points to the output vector        
 * @param[in]       blockSize number of samples in the vector        
 * @return none.        
 */


void arm_scale_f32(
  float32_t * pSrc,
  float32_t scale,
  float32_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;                               /* loop counter */
#ifndef ARM_MATH_CM0_FAMILY

/* Run the below code for Cortex-M4 and Cortex-M3 */
  float32_t in1, in2, in3, in4;                  /* temporary variabels */

  /*loop Unrolling */
  blkCnt = blockSize >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.        
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* C = A * scale */
    /* Scale the input and then store the results in the destination buffer. */
    /* read input samples from source */
    in1 = *pSrc;
    in2 = *(pSrc + 1);

    /* multiply with scaling factor */
    in1 = in1 * scale;

    /* read input sample from source */
    in3 = *(pSrc + 2);

    /* multiply with scaling factor */
    in2 = in2 * scale;

    /* read input sample from source */
    in4 = *(pSrc + 3);

    /* multiply with scaling factor */
    in3 = in3 * scale;
    in4 = in4 * scale;
    /* store the result to destination */
    *pDst = in1;
    *(pDst + 1) = in2;
    *(pDst + 2) = in3;
    *(pDst + 3) = in4;

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

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

  while(blkCnt > 0u)
  {
    /* C = A * scale */
    /* Scale the input and then store the result in the destination buffer. */
    *pDst++ = (*pSrc++) * scale;

    /* Decrement the loop counter */
    blkCnt--;
  }
}

/**        
 * @} end of scale group        
 */
