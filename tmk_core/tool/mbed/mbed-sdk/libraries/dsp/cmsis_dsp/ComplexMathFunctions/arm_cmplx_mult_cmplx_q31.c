/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:	    arm_cmplx_mult_cmplx_q31.c    
*    
* Description:	Q31 complex-by-complex multiplication    
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
 * @addtogroup CmplxByCmplxMult    
 * @{    
 */


/**    
 * @brief  Q31 complex-by-complex multiplication    
 * @param[in]  *pSrcA points to the first input vector    
 * @param[in]  *pSrcB points to the second input vector    
 * @param[out]  *pDst  points to the output vector    
 * @param[in]  numSamples number of complex samples in each vector    
 * @return none.    
 *    
 * <b>Scaling and Overflow Behavior:</b>    
 * \par    
 * The function implements 1.31 by 1.31 multiplications and finally output is converted into 3.29 format.    
 * Input down scaling is not required.    
 */

void arm_cmplx_mult_cmplx_q31(
  q31_t * pSrcA,
  q31_t * pSrcB,
  q31_t * pDst,
  uint32_t numSamples)
{
  q31_t a, b, c, d;                              /* Temporary variables to store real and imaginary values */
  uint32_t blkCnt;                               /* loop counters */
  q31_t mul1, mul2, mul3, mul4;
  q31_t out1, out2;

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */

  /* loop Unrolling */
  blkCnt = numSamples >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */
    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    mul1 = (q31_t) (((q63_t) a * c) >> 32);
    mul2 = (q31_t) (((q63_t) b * d) >> 32);
    mul3 = (q31_t) (((q63_t) a * d) >> 32);
    mul4 = (q31_t) (((q63_t) b * c) >> 32);

    mul1 = (mul1 >> 1);
    mul2 = (mul2 >> 1);
    mul3 = (mul3 >> 1);
    mul4 = (mul4 >> 1);

    out1 = mul1 - mul2;
    out2 = mul3 + mul4;

    /* store the real result in 3.29 format in the destination buffer. */
    *pDst++ = out1;
    /* store the imag result in 3.29 format in the destination buffer. */
    *pDst++ = out2;

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    mul1 = (q31_t) (((q63_t) a * c) >> 32);
    mul2 = (q31_t) (((q63_t) b * d) >> 32);
    mul3 = (q31_t) (((q63_t) a * d) >> 32);
    mul4 = (q31_t) (((q63_t) b * c) >> 32);

    mul1 = (mul1 >> 1);
    mul2 = (mul2 >> 1);
    mul3 = (mul3 >> 1);
    mul4 = (mul4 >> 1);

    out1 = mul1 - mul2;
    out2 = mul3 + mul4;

    /* store the real result in 3.29 format in the destination buffer. */
    *pDst++ = out1;
    /* store the imag result in 3.29 format in the destination buffer. */
    *pDst++ = out2;

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    mul1 = (q31_t) (((q63_t) a * c) >> 32);
    mul2 = (q31_t) (((q63_t) b * d) >> 32);
    mul3 = (q31_t) (((q63_t) a * d) >> 32);
    mul4 = (q31_t) (((q63_t) b * c) >> 32);

    mul1 = (mul1 >> 1);
    mul2 = (mul2 >> 1);
    mul3 = (mul3 >> 1);
    mul4 = (mul4 >> 1);

    out1 = mul1 - mul2;
    out2 = mul3 + mul4;

    /* store the real result in 3.29 format in the destination buffer. */
    *pDst++ = out1;
    /* store the imag result in 3.29 format in the destination buffer. */
    *pDst++ = out2;

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    mul1 = (q31_t) (((q63_t) a * c) >> 32);
    mul2 = (q31_t) (((q63_t) b * d) >> 32);
    mul3 = (q31_t) (((q63_t) a * d) >> 32);
    mul4 = (q31_t) (((q63_t) b * c) >> 32);

    mul1 = (mul1 >> 1);
    mul2 = (mul2 >> 1);
    mul3 = (mul3 >> 1);
    mul4 = (mul4 >> 1);

    out1 = mul1 - mul2;
    out2 = mul3 + mul4;

    /* store the real result in 3.29 format in the destination buffer. */
    *pDst++ = out1;
    /* store the imag result in 3.29 format in the destination buffer. */
    *pDst++ = out2;

    /* Decrement the blockSize loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.    
   ** No loop unrolling is used. */
  blkCnt = numSamples % 0x4u;

  while(blkCnt > 0u)
  {
    /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */
    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    mul1 = (q31_t) (((q63_t) a * c) >> 32);
    mul2 = (q31_t) (((q63_t) b * d) >> 32);
    mul3 = (q31_t) (((q63_t) a * d) >> 32);
    mul4 = (q31_t) (((q63_t) b * c) >> 32);

    mul1 = (mul1 >> 1);
    mul2 = (mul2 >> 1);
    mul3 = (mul3 >> 1);
    mul4 = (mul4 >> 1);

    out1 = mul1 - mul2;
    out2 = mul3 + mul4;

    /* store the real result in 3.29 format in the destination buffer. */
    *pDst++ = out1;
    /* store the imag result in 3.29 format in the destination buffer. */
    *pDst++ = out2;

    /* Decrement the blockSize loop counter */
    blkCnt--;
  }

#else

  /* Run the below code for Cortex-M0 */

  /* loop Unrolling */
  blkCnt = numSamples >> 1u;

  /* First part of the processing with loop unrolling.  Compute 2 outputs at a time.     
   ** a second loop below computes the remaining 1 sample. */
  while(blkCnt > 0u)
  {
    /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */
    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    mul1 = (q31_t) (((q63_t) a * c) >> 32);
    mul2 = (q31_t) (((q63_t) b * d) >> 32);
    mul3 = (q31_t) (((q63_t) a * d) >> 32);
    mul4 = (q31_t) (((q63_t) b * c) >> 32);

    mul1 = (mul1 >> 1);
    mul2 = (mul2 >> 1);
    mul3 = (mul3 >> 1);
    mul4 = (mul4 >> 1);

    out1 = mul1 - mul2;
    out2 = mul3 + mul4;

    /* store the real result in 3.29 format in the destination buffer. */
    *pDst++ = out1;
    /* store the imag result in 3.29 format in the destination buffer. */
    *pDst++ = out2;

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    mul1 = (q31_t) (((q63_t) a * c) >> 32);
    mul2 = (q31_t) (((q63_t) b * d) >> 32);
    mul3 = (q31_t) (((q63_t) a * d) >> 32);
    mul4 = (q31_t) (((q63_t) b * c) >> 32);

    mul1 = (mul1 >> 1);
    mul2 = (mul2 >> 1);
    mul3 = (mul3 >> 1);
    mul4 = (mul4 >> 1);

    out1 = mul1 - mul2;
    out2 = mul3 + mul4;

    /* store the real result in 3.29 format in the destination buffer. */
    *pDst++ = out1;
    /* store the imag result in 3.29 format in the destination buffer. */
    *pDst++ = out2;

    /* Decrement the blockSize loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 2, compute any remaining output samples here.     
   ** No loop unrolling is used. */
  blkCnt = numSamples % 0x2u;

  while(blkCnt > 0u)
  {
    /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */
    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    mul1 = (q31_t) (((q63_t) a * c) >> 32);
    mul2 = (q31_t) (((q63_t) b * d) >> 32);
    mul3 = (q31_t) (((q63_t) a * d) >> 32);
    mul4 = (q31_t) (((q63_t) b * c) >> 32);

    mul1 = (mul1 >> 1);
    mul2 = (mul2 >> 1);
    mul3 = (mul3 >> 1);
    mul4 = (mul4 >> 1);

    out1 = mul1 - mul2;
    out2 = mul3 + mul4;

    /* store the real result in 3.29 format in the destination buffer. */
    *pDst++ = out1;
    /* store the imag result in 3.29 format in the destination buffer. */
    *pDst++ = out2;

    /* Decrement the blockSize loop counter */
    blkCnt--;
  }

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

}

/**    
 * @} end of CmplxByCmplxMult group    
 */
