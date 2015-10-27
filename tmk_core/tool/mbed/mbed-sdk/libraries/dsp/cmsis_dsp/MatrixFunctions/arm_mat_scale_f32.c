/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013 
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:        arm_mat_scale_f32.c    
*    
* Description:	Multiplies a floating-point matrix by a scalar.    
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
 * @defgroup MatrixScale Matrix Scale        
 *        
 * Multiplies a matrix by a scalar.  This is accomplished by multiplying each element in the        
 * matrix by the scalar.  For example:        
 * \image html MatrixScale.gif "Matrix Scaling of a 3 x 3 matrix"        
 *        
 * The function checks to make sure that the input and output matrices are of the same size.        
 *        
 * In the fixed-point Q15 and Q31 functions, <code>scale</code> is represented by        
 * a fractional multiplication <code>scaleFract</code> and an arithmetic shift <code>shift</code>.        
 * The shift allows the gain of the scaling operation to exceed 1.0.        
 * The overall scale factor applied to the fixed-point data is        
 * <pre>        
 *     scale = scaleFract * 2^shift.        
 * </pre>        
 */

/**        
 * @addtogroup MatrixScale        
 * @{        
 */

/**        
 * @brief Floating-point matrix scaling.        
 * @param[in]       *pSrc points to input matrix structure        
 * @param[in]       scale scale factor to be applied         
 * @param[out]      *pDst points to output matrix structure        
 * @return     		The function returns either <code>ARM_MATH_SIZE_MISMATCH</code>         
 * or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.        
 *        
 */

arm_status arm_mat_scale_f32(
  const arm_matrix_instance_f32 * pSrc,
  float32_t scale,
  arm_matrix_instance_f32 * pDst)
{
  float32_t *pIn = pSrc->pData;                  /* input data matrix pointer */
  float32_t *pOut = pDst->pData;                 /* output data matrix pointer */
  uint32_t numSamples;                           /* total number of elements in the matrix */
  uint32_t blkCnt;                               /* loop counters */
  arm_status status;                             /* status of matrix scaling     */

#ifndef ARM_MATH_CM0_FAMILY

  float32_t in1, in2, in3, in4;                  /* temporary variables */
  float32_t out1, out2, out3, out4;              /* temporary variables */

#endif //      #ifndef ARM_MATH_CM0_FAMILY

#ifdef ARM_MATH_MATRIX_CHECK
  /* Check for matrix mismatch condition */
  if((pSrc->numRows != pDst->numRows) || (pSrc->numCols != pDst->numCols))
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else
#endif /*    #ifdef ARM_MATH_MATRIX_CHECK    */
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
      /* C(m,n) = A(m,n) * scale */
      /* Scaling and results are stored in the destination buffer. */
      in1 = pIn[0];
      in2 = pIn[1];
      in3 = pIn[2];
      in4 = pIn[3];

      out1 = in1 * scale;
      out2 = in2 * scale;
      out3 = in3 * scale;
      out4 = in4 * scale;


      pOut[0] = out1;
      pOut[1] = out2;
      pOut[2] = out3;
      pOut[3] = out4;

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
      /* C(m,n) = A(m,n) * scale */
      /* The results are stored in the destination buffer. */
      *pOut++ = (*pIn++) * scale;

      /* Decrement the loop counter */
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
