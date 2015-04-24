/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_cmplx_dot_prod_f32.c    
*    
* Description:	Floating-point complex dot product    
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
 * @ingroup groupCmplxMath    
 */

/**    
 * @defgroup cmplx_dot_prod Complex Dot Product    
 *    
 * Computes the dot product of two complex vectors.    
 * The vectors are multiplied element-by-element and then summed.    
 *   
 * The <code>pSrcA</code> points to the first complex input vector and    
 * <code>pSrcB</code> points to the second complex input vector.    
 * <code>numSamples</code> specifies the number of complex samples    
 * and the data in each array is stored in an interleaved fashion    
 * (real, imag, real, imag, ...).    
 * Each array has a total of <code>2*numSamples</code> values.    
 *    
 * The underlying algorithm is used:    
 * <pre>    
 * realResult=0;    
 * imagResult=0;    
 * for(n=0; n<numSamples; n++) {    
 *     realResult += pSrcA[(2*n)+0]*pSrcB[(2*n)+0] - pSrcA[(2*n)+1]*pSrcB[(2*n)+1];    
 *     imagResult += pSrcA[(2*n)+0]*pSrcB[(2*n)+1] + pSrcA[(2*n)+1]*pSrcB[(2*n)+0];    
 * }    
 * </pre>    
 *    
 * There are separate functions for floating-point, Q15, and Q31 data types.    
 */

/**    
 * @addtogroup cmplx_dot_prod    
 * @{    
 */

/**    
 * @brief  Floating-point complex dot product    
 * @param  *pSrcA points to the first input vector    
 * @param  *pSrcB points to the second input vector    
 * @param  numSamples number of complex samples in each vector    
 * @param  *realResult real part of the result returned here    
 * @param  *imagResult imaginary part of the result returned here    
 * @return none.    
 */

void arm_cmplx_dot_prod_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  uint32_t numSamples,
  float32_t * realResult,
  float32_t * imagResult)
{
  float32_t real_sum = 0.0f, imag_sum = 0.0f;    /* Temporary result storage */

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */
  uint32_t blkCnt;                               /* loop counter */

  /*loop Unrolling */
  blkCnt = numSamples >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* CReal = A[0]* B[0] + A[2]* B[2] + A[4]* B[4] + .....+ A[numSamples-2]* B[numSamples-2] */
    real_sum += (*pSrcA++) * (*pSrcB++);
    /* CImag = A[1]* B[1] + A[3]* B[3] + A[5]* B[5] + .....+ A[numSamples-1]* B[numSamples-1] */
    imag_sum += (*pSrcA++) * (*pSrcB++);

    real_sum += (*pSrcA++) * (*pSrcB++);
    imag_sum += (*pSrcA++) * (*pSrcB++);

    real_sum += (*pSrcA++) * (*pSrcB++);
    imag_sum += (*pSrcA++) * (*pSrcB++);

    real_sum += (*pSrcA++) * (*pSrcB++);
    imag_sum += (*pSrcA++) * (*pSrcB++);

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the numSamples is not a multiple of 4, compute any remaining output samples here.    
   ** No loop unrolling is used. */
  blkCnt = numSamples % 0x4u;

  while(blkCnt > 0u)
  {
    /* CReal = A[0]* B[0] + A[2]* B[2] + A[4]* B[4] + .....+ A[numSamples-2]* B[numSamples-2] */
    real_sum += (*pSrcA++) * (*pSrcB++);
    /* CImag = A[1]* B[1] + A[3]* B[3] + A[5]* B[5] + .....+ A[numSamples-1]* B[numSamples-1] */
    imag_sum += (*pSrcA++) * (*pSrcB++);


    /* Decrement the loop counter */
    blkCnt--;
  }

#else

  /* Run the below code for Cortex-M0 */

  while(numSamples > 0u)
  {
    /* CReal = A[0]* B[0] + A[2]* B[2] + A[4]* B[4] + .....+ A[numSamples-2]* B[numSamples-2] */
    real_sum += (*pSrcA++) * (*pSrcB++);
    /* CImag = A[1]* B[1] + A[3]* B[3] + A[5]* B[5] + .....+ A[numSamples-1]* B[numSamples-1] */
    imag_sum += (*pSrcA++) * (*pSrcB++);


    /* Decrement the loop counter */
    numSamples--;
  }

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

  /* Store the real and imaginary results in the destination buffers */
  *realResult = real_sum;
  *imagResult = imag_sum;
}

/**    
 * @} end of cmplx_dot_prod group    
 */
