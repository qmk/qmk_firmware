/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:	    arm_cmplx_mult_cmplx_f32.c    
*    
* Description:	Floating-point complex-by-complex multiplication    
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
 * @ingroup groupCmplxMath        
 */

/**        
 * @defgroup CmplxByCmplxMult Complex-by-Complex Multiplication        
 *        
 * Multiplies a complex vector by another complex vector and generates a complex result.        
 * The data in the complex arrays is stored in an interleaved fashion        
 * (real, imag, real, imag, ...).        
 * The parameter <code>numSamples</code> represents the number of complex        
 * samples processed.  The complex arrays have a total of <code>2*numSamples</code>        
 * real values.        
 *        
 * The underlying algorithm is used:        
 *        
 * <pre>        
 * for(n=0; n<numSamples; n++) {        
 *     pDst[(2*n)+0] = pSrcA[(2*n)+0] * pSrcB[(2*n)+0] - pSrcA[(2*n)+1] * pSrcB[(2*n)+1];        
 *     pDst[(2*n)+1] = pSrcA[(2*n)+0] * pSrcB[(2*n)+1] + pSrcA[(2*n)+1] * pSrcB[(2*n)+0];        
 * }        
 * </pre>        
 *        
 * There are separate functions for floating-point, Q15, and Q31 data types.        
 */

/**        
 * @addtogroup CmplxByCmplxMult        
 * @{        
 */


/**        
 * @brief  Floating-point complex-by-complex multiplication        
 * @param[in]  *pSrcA points to the first input vector        
 * @param[in]  *pSrcB points to the second input vector        
 * @param[out]  *pDst  points to the output vector        
 * @param[in]  numSamples number of complex samples in each vector        
 * @return none.        
 */

void arm_cmplx_mult_cmplx_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  float32_t * pDst,
  uint32_t numSamples)
{
  float32_t a1, b1, c1, d1;                      /* Temporary variables to store real and imaginary values */
  uint32_t blkCnt;                               /* loop counters */

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */
  float32_t a2, b2, c2, d2;                      /* Temporary variables to store real and imaginary values */
  float32_t acc1, acc2, acc3, acc4;


  /* loop Unrolling */
  blkCnt = numSamples >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.        
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */
    a1 = *pSrcA;                /* A[2 * i] */
    c1 = *pSrcB;                /* B[2 * i] */

    b1 = *(pSrcA + 1);          /* A[2 * i + 1] */
    acc1 = a1 * c1;             /* acc1 = A[2 * i] * B[2 * i] */

    a2 = *(pSrcA + 2);          /* A[2 * i + 2] */
    acc2 = (b1 * c1);           /* acc2 = A[2 * i + 1] * B[2 * i] */

    d1 = *(pSrcB + 1);          /* B[2 * i + 1] */
    c2 = *(pSrcB + 2);          /* B[2 * i + 2] */
    acc1 -= b1 * d1;            /* acc1 =      A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1] */

    d2 = *(pSrcB + 3);          /* B[2 * i + 3] */
    acc3 = a2 * c2;             /* acc3 =       A[2 * i + 2] * B[2 * i + 2] */

    b2 = *(pSrcA + 3);          /* A[2 * i + 3] */
    acc2 += (a1 * d1);          /* acc2 =      A[2 * i + 1] * B[2 * i] + A[2 * i] * B[2 * i + 1] */

    a1 = *(pSrcA + 4);          /* A[2 * i + 4] */
    acc4 = (a2 * d2);           /* acc4 =   A[2 * i + 2] * B[2 * i + 3] */

    c1 = *(pSrcB + 4);          /* B[2 * i + 4] */
    acc3 -= (b2 * d2);          /* acc3 =       A[2 * i + 2] * B[2 * i + 2] - A[2 * i + 3] * B[2 * i + 3] */
    *pDst = acc1;               /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1] */

    b1 = *(pSrcA + 5);          /* A[2 * i + 5] */
    acc4 += b2 * c2;            /* acc4 =   A[2 * i + 2] * B[2 * i + 3] + A[2 * i + 3] * B[2 * i + 2] */

    *(pDst + 1) = acc2;         /* C[2 * i + 1] = A[2 * i + 1] * B[2 * i] + A[2 * i] * B[2 * i + 1]  */
    acc1 = (a1 * c1);

    d1 = *(pSrcB + 5);
    acc2 = (b1 * c1);

    *(pDst + 2) = acc3;
    *(pDst + 3) = acc4;

    a2 = *(pSrcA + 6);
    acc1 -= (b1 * d1);

    c2 = *(pSrcB + 6);
    acc2 += (a1 * d1);

    b2 = *(pSrcA + 7);
    acc3 = (a2 * c2);

    d2 = *(pSrcB + 7);
    acc4 = (b2 * c2);

    *(pDst + 4) = acc1;
    pSrcA += 8u;

    acc3 -= (b2 * d2);
    acc4 += (a2 * d2);

    *(pDst + 5) = acc2;
    pSrcB += 8u;

    *(pDst + 6) = acc3;
    *(pDst + 7) = acc4;

    pDst += 8u;

    /* Decrement the numSamples loop counter */
    blkCnt--;
  }

  /* If the numSamples is not a multiple of 4, compute any remaining output samples here.        
   ** No loop unrolling is used. */
  blkCnt = numSamples % 0x4u;

#else

  /* Run the below code for Cortex-M0 */
  blkCnt = numSamples;

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

  while(blkCnt > 0u)
  {
    /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */
    a1 = *pSrcA++;
    b1 = *pSrcA++;
    c1 = *pSrcB++;
    d1 = *pSrcB++;

    /* store the result in the destination buffer. */
    *pDst++ = (a1 * c1) - (b1 * d1);
    *pDst++ = (a1 * d1) + (b1 * c1);

    /* Decrement the numSamples loop counter */
    blkCnt--;
  }
}

/**        
 * @} end of CmplxByCmplxMult group        
 */
