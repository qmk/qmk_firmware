/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013 
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:	    arm_mat_scale_q15.c    
*    
* Description:	Multiplies a Q15 matrix by a scalar.    
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
 * @ingroup groupMatrix    
 */

/**    
 * @addtogroup MatrixScale    
 * @{    
 */

/**    
 * @brief Q15 matrix scaling.    
 * @param[in]       *pSrc points to input matrix    
 * @param[in]       scaleFract fractional portion of the scale factor    
 * @param[in]       shift number of bits to shift the result by    
 * @param[out]      *pDst points to output matrix structure    
 * @return     		The function returns either    
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.    
 *    
 * @details    
 * <b>Scaling and Overflow Behavior:</b>    
 * \par    
 * The input data <code>*pSrc</code> and <code>scaleFract</code> are in 1.15 format.    
 * These are multiplied to yield a 2.30 intermediate result and this is shifted with saturation to 1.15 format.    
 */

arm_status arm_mat_scale_q15(
  const arm_matrix_instance_q15 * pSrc,
  q15_t scaleFract,
  int32_t shift,
  arm_matrix_instance_q15 * pDst)
{
  q15_t *pIn = pSrc->pData;                      /* input data matrix pointer */
  q15_t *pOut = pDst->pData;                     /* output data matrix pointer */
  uint32_t numSamples;                           /* total number of elements in the matrix */
  int32_t totShift = 15 - shift;                 /* total shift to apply after scaling */
  uint32_t blkCnt;                               /* loop counters */
  arm_status status;                             /* status of matrix scaling     */

#ifndef ARM_MATH_CM0_FAMILY

  q15_t in1, in2, in3, in4;
  q31_t out1, out2, out3, out4;
  q31_t inA1, inA2;

#endif //     #ifndef ARM_MATH_CM0_FAMILY

#ifdef ARM_MATH_MATRIX_CHECK
  /* Check for matrix mismatch */
  if((pSrc->numRows != pDst->numRows) || (pSrc->numCols != pDst->numCols))
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else
#endif //    #ifdef ARM_MATH_MATRIX_CHECK
  {
    /* Total number of samples in the input matrix */
    numSamples = (uint32_t) pSrc->numRows * pSrc->numCols;

#ifndef ARM_MATH_CM0_FAMILY

    /* Run the below code for Cortex-M4 and Cortex-M3 */
    /* Loop Unrolling */
    blkCnt = numSamples >> 2;

    /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
     ** a second loop below computes the remaining 1 to 3 samples. */
    while(blkCnt > 0u)
    {
      /* C(m,n) = A(m,n) * k */
      /* Scale, saturate and then store the results in the destination buffer. */
      /* Reading 2 inputs from memory */
      inA1 = _SIMD32_OFFSET(pIn);
      inA2 = _SIMD32_OFFSET(pIn + 2);

      /* C = A * scale */
      /* Scale the inputs and then store the 2 results in the destination buffer        
       * in single cycle by packing the outputs */
      out1 = (q31_t) ((q15_t) (inA1 >> 16) * scaleFract);
      out2 = (q31_t) ((q15_t) inA1 * scaleFract);
      out3 = (q31_t) ((q15_t) (inA2 >> 16) * scaleFract);
      out4 = (q31_t) ((q15_t) inA2 * scaleFract);

      out1 = out1 >> totShift;
      inA1 = _SIMD32_OFFSET(pIn + 4);
      out2 = out2 >> totShift;
      inA2 = _SIMD32_OFFSET(pIn + 6);
      out3 = out3 >> totShift;
      out4 = out4 >> totShift;

      in1 = (q15_t) (__SSAT(out1, 16));
      in2 = (q15_t) (__SSAT(out2, 16));
      in3 = (q15_t) (__SSAT(out3, 16));
      in4 = (q15_t) (__SSAT(out4, 16));

      _SIMD32_OFFSET(pOut) = __PKHBT(in2, in1, 16);
      _SIMD32_OFFSET(pOut + 2) = __PKHBT(in4, in3, 16);

      /* update pointers to process next sampels */
      pIn += 4u;
      pOut += 4u;


      /* Decrement the numSamples loop counter */
      blkCnt--;
    }

    /* If the numSamples is not a multiple of 4, compute any remaining output samples here.        
     ** No loop unrolling is used. */
    blkCnt = numSamples % 0x4u;

#else

    /* Run the below code for Cortex-M0 */

    /* Initialize blkCnt with number of samples */
    blkCnt = numSamples;

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

    while(blkCnt > 0u)
    {
      /* C(m,n) = A(m,n) * k */
      /* Scale, saturate and then store the results in the destination buffer. */
      *pOut++ =
        (q15_t) (__SSAT(((q31_t) (*pIn++) * scaleFract) >> totShift, 16));

      /* Decrement the numSamples loop counter */
      blkCnt--;
    }
    /* Set status as ARM_MATH_SUCCESS */
    status = ARM_MATH_SUCCESS;
  }

  /* Return to application */
  return (status);
}

/**        
 * @} end of MatrixScale group        
 */
