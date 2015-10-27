/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:	    arm_cmplx_mult_real_q15.c    
*    
* Description:	Q15 complex by real multiplication    
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
 * @addtogroup CmplxByRealMult    
 * @{    
 */


/**    
 * @brief  Q15 complex-by-real multiplication    
 * @param[in]  *pSrcCmplx points to the complex input vector    
 * @param[in]  *pSrcReal points to the real input vector    
 * @param[out]  *pCmplxDst points to the complex output vector    
 * @param[in]  numSamples number of samples in each vector    
 * @return none.    
 *    
 * <b>Scaling and Overflow Behavior:</b>    
 * \par    
 * The function uses saturating arithmetic.    
 * Results outside of the allowable Q15 range [0x8000 0x7FFF] will be saturated.    
 */

void arm_cmplx_mult_real_q15(
  q15_t * pSrcCmplx,
  q15_t * pSrcReal,
  q15_t * pCmplxDst,
  uint32_t numSamples)
{
  q15_t in;                                      /* Temporary variable to store input value */

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */
  uint32_t blkCnt;                               /* loop counters */
  q31_t inA1, inA2;                              /* Temporary variables to hold input data */
  q31_t inB1;                                    /* Temporary variables to hold input data */
  q15_t out1, out2, out3, out4;                  /* Temporary variables to hold output data */
  q31_t mul1, mul2, mul3, mul4;                  /* Temporary variables to hold intermediate data */

  /* loop Unrolling */
  blkCnt = numSamples >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* C[2 * i] = A[2 * i] * B[i].            */
    /* C[2 * i + 1] = A[2 * i + 1] * B[i].        */
    /* read complex number both real and imaginary from complex input buffer */
    inA1 = *__SIMD32(pSrcCmplx)++;
    /* read two real values at a time from real input buffer */
    inB1 = *__SIMD32(pSrcReal)++;
    /* read complex number both real and imaginary from complex input buffer */
    inA2 = *__SIMD32(pSrcCmplx)++;

    /* multiply complex number with real numbers */
#ifndef ARM_MATH_BIG_ENDIAN

    mul1 = (q31_t) ((q15_t) (inA1) * (q15_t) (inB1));
    mul2 = (q31_t) ((q15_t) (inA1 >> 16) * (q15_t) (inB1));
    mul3 = (q31_t) ((q15_t) (inA2) * (q15_t) (inB1 >> 16));
    mul4 = (q31_t) ((q15_t) (inA2 >> 16) * (q15_t) (inB1 >> 16));

#else

    mul2 = (q31_t) ((q15_t) (inA1 >> 16) * (q15_t) (inB1 >> 16));
    mul1 = (q31_t) ((q15_t) inA1 * (q15_t) (inB1 >> 16));
    mul4 = (q31_t) ((q15_t) (inA2 >> 16) * (q15_t) inB1);
    mul3 = (q31_t) ((q15_t) inA2 * (q15_t) inB1);

#endif //      #ifndef ARM_MATH_BIG_ENDIAN

    /* saturate the result */
    out1 = (q15_t) __SSAT(mul1 >> 15u, 16);
    out2 = (q15_t) __SSAT(mul2 >> 15u, 16);
    out3 = (q15_t) __SSAT(mul3 >> 15u, 16);
    out4 = (q15_t) __SSAT(mul4 >> 15u, 16);

    /* pack real and imaginary outputs and store them to destination */
    *__SIMD32(pCmplxDst)++ = __PKHBT(out1, out2, 16);
    *__SIMD32(pCmplxDst)++ = __PKHBT(out3, out4, 16);

    inA1 = *__SIMD32(pSrcCmplx)++;
    inB1 = *__SIMD32(pSrcReal)++;
    inA2 = *__SIMD32(pSrcCmplx)++;

#ifndef ARM_MATH_BIG_ENDIAN

    mul1 = (q31_t) ((q15_t) (inA1) * (q15_t) (inB1));
    mul2 = (q31_t) ((q15_t) (inA1 >> 16) * (q15_t) (inB1));
    mul3 = (q31_t) ((q15_t) (inA2) * (q15_t) (inB1 >> 16));
    mul4 = (q31_t) ((q15_t) (inA2 >> 16) * (q15_t) (inB1 >> 16));

#else

    mul2 = (q31_t) ((q15_t) (inA1 >> 16) * (q15_t) (inB1 >> 16));
    mul1 = (q31_t) ((q15_t) inA1 * (q15_t) (inB1 >> 16));
    mul4 = (q31_t) ((q15_t) (inA2 >> 16) * (q15_t) inB1);
    mul3 = (q31_t) ((q15_t) inA2 * (q15_t) inB1);

#endif //      #ifndef ARM_MATH_BIG_ENDIAN

    out1 = (q15_t) __SSAT(mul1 >> 15u, 16);
    out2 = (q15_t) __SSAT(mul2 >> 15u, 16);
    out3 = (q15_t) __SSAT(mul3 >> 15u, 16);
    out4 = (q15_t) __SSAT(mul4 >> 15u, 16);

    *__SIMD32(pCmplxDst)++ = __PKHBT(out1, out2, 16);
    *__SIMD32(pCmplxDst)++ = __PKHBT(out3, out4, 16);

    /* Decrement the numSamples loop counter */
    blkCnt--;
  }

  /* If the numSamples is not a multiple of 4, compute any remaining output samples here.    
   ** No loop unrolling is used. */
  blkCnt = numSamples % 0x4u;

  while(blkCnt > 0u)
  {
    /* C[2 * i] = A[2 * i] * B[i].            */
    /* C[2 * i + 1] = A[2 * i + 1] * B[i].        */
    in = *pSrcReal++;
    /* store the result in the destination buffer. */
    *pCmplxDst++ =
      (q15_t) __SSAT((((q31_t) (*pSrcCmplx++) * (in)) >> 15), 16);
    *pCmplxDst++ =
      (q15_t) __SSAT((((q31_t) (*pSrcCmplx++) * (in)) >> 15), 16);

    /* Decrement the numSamples loop counter */
    blkCnt--;
  }

#else

  /* Run the below code for Cortex-M0 */

  while(numSamples > 0u)
  {
    /* realOut = realA * realB.            */
    /* imagOut = imagA * realB.                */
    in = *pSrcReal++;
    /* store the result in the destination buffer. */
    *pCmplxDst++ =
      (q15_t) __SSAT((((q31_t) (*pSrcCmplx++) * (in)) >> 15), 16);
    *pCmplxDst++ =
      (q15_t) __SSAT((((q31_t) (*pSrcCmplx++) * (in)) >> 15), 16);

    /* Decrement the numSamples loop counter */
    numSamples--;
  }

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

}

/**    
 * @} end of CmplxByRealMult group    
 */
