/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013  
* $Revision: 	V1.4.1  
*    
* Project: 	    CMSIS DSP Library    
* Title:	    arm_fir_fast_q31.c    
*    
* Description:	Processing function for the Q31 Fast FIR filter.    
*    
* Target Processor: Cortex-M4/Cortex-M3
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
 * @ingroup groupFilters    
 */

/**    
 * @addtogroup FIR    
 * @{    
 */

/**    
 * @param[in] *S points to an instance of the Q31 structure.    
 * @param[in] *pSrc points to the block of input data.    
 * @param[out] *pDst points to the block output data.    
 * @param[in] blockSize number of samples to process per call.    
 * @return none.    
 *    
 * <b>Scaling and Overflow Behavior:</b>    
 *    
 * \par    
 * This function is optimized for speed at the expense of fixed-point precision and overflow protection.    
 * The result of each 1.31 x 1.31 multiplication is truncated to 2.30 format.    
 * These intermediate results are added to a 2.30 accumulator.    
 * Finally, the accumulator is saturated and converted to a 1.31 result.    
 * The fast version has the same overflow behavior as the standard version and provides less precision since it discards the low 32 bits of each multiplication result.    
 * In order to avoid overflows completely the input signal must be scaled down by log2(numTaps) bits.    
 *    
 * \par    
 * Refer to the function <code>arm_fir_q31()</code> for a slower implementation of this function which uses a 64-bit accumulator to provide higher precision.  Both the slow and the fast versions use the same instance structure.    
 * Use the function <code>arm_fir_init_q31()</code> to initialize the filter structure.    
 */

IAR_ONLY_LOW_OPTIMIZATION_ENTER
void arm_fir_fast_q31(
  const arm_fir_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize)
{
  q31_t *pState = S->pState;                     /* State pointer */
  q31_t *pCoeffs = S->pCoeffs;                   /* Coefficient pointer */
  q31_t *pStateCurnt;                            /* Points to the current sample of the state */
  q31_t x0, x1, x2, x3;                          /* Temporary variables to hold state */
  q31_t c0;                                      /* Temporary variable to hold coefficient value */
  q31_t *px;                                     /* Temporary pointer for state */
  q31_t *pb;                                     /* Temporary pointer for coefficient buffer */
  q31_t acc0, acc1, acc2, acc3;                  /* Accumulators */
  uint32_t numTaps = S->numTaps;                 /* Number of filter coefficients in the filter */
  uint32_t i, tapCnt, blkCnt;                    /* Loop counters */

  /* S->pState points to buffer which contains previous frame (numTaps - 1) samples */
  /* pStateCurnt points to the location where the new input data should be written */
  pStateCurnt = &(S->pState[(numTaps - 1u)]);

  /* Apply loop unrolling and compute 4 output values simultaneously.    
   * The variables acc0 ... acc3 hold output values that are being computed:    
   *    
   *    acc0 =  b[numTaps-1] * x[n-numTaps-1] + b[numTaps-2] * x[n-numTaps-2] + b[numTaps-3] * x[n-numTaps-3] +...+ b[0] * x[0]    
   *    acc1 =  b[numTaps-1] * x[n-numTaps] +   b[numTaps-2] * x[n-numTaps-1] + b[numTaps-3] * x[n-numTaps-2] +...+ b[0] * x[1]    
   *    acc2 =  b[numTaps-1] * x[n-numTaps+1] + b[numTaps-2] * x[n-numTaps] +   b[numTaps-3] * x[n-numTaps-1] +...+ b[0] * x[2]    
   *    acc3 =  b[numTaps-1] * x[n-numTaps+2] + b[numTaps-2] * x[n-numTaps+1] + b[numTaps-3] * x[n-numTaps]   +...+ b[0] * x[3]    
   */
  blkCnt = blockSize >> 2;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.    
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* Copy four new input samples into the state buffer */
    *pStateCurnt++ = *pSrc++;
    *pStateCurnt++ = *pSrc++;
    *pStateCurnt++ = *pSrc++;
    *pStateCurnt++ = *pSrc++;

    /* Set all accumulators to zero */
    acc0 = 0;
    acc1 = 0;
    acc2 = 0;
    acc3 = 0;

    /* Initialize state pointer */
    px = pState;

    /* Initialize coefficient pointer */
    pb = pCoeffs;

    /* Read the first three samples from the state buffer:    
     *  x[n-numTaps], x[n-numTaps-1], x[n-numTaps-2] */
    x0 = *(px++);
    x1 = *(px++);
    x2 = *(px++);

    /* Loop unrolling.  Process 4 taps at a time. */
    tapCnt = numTaps >> 2;
    i = tapCnt;

    while(i > 0u)
    {
      /* Read the b[numTaps] coefficient */
      c0 = *(pb++);

      /* Read x[n-numTaps-3] sample */
      x3 = *(px++);

      /* acc0 +=  b[numTaps] * x[n-numTaps] */
      multAcc_32x32_keep32_R(acc0, x0, c0);

      /* acc1 +=  b[numTaps] * x[n-numTaps-1] */
      multAcc_32x32_keep32_R(acc1, x1, c0);

      /* acc2 +=  b[numTaps] * x[n-numTaps-2] */
      multAcc_32x32_keep32_R(acc2, x2, c0);

      /* acc3 +=  b[numTaps] * x[n-numTaps-3] */
      multAcc_32x32_keep32_R(acc3, x3, c0);

      /* Read the b[numTaps-1] coefficient */
      c0 = *(pb++);

      /* Read x[n-numTaps-4] sample */
      x0 = *(px++);

      /* Perform the multiply-accumulates */      
      multAcc_32x32_keep32_R(acc0, x1, c0);
      multAcc_32x32_keep32_R(acc1, x2, c0);
      multAcc_32x32_keep32_R(acc2, x3, c0);
      multAcc_32x32_keep32_R(acc3, x0, c0);

      /* Read the b[numTaps-2] coefficient */
      c0 = *(pb++);

      /* Read x[n-numTaps-5] sample */
      x1 = *(px++);

      /* Perform the multiply-accumulates */      
      multAcc_32x32_keep32_R(acc0, x2, c0);
      multAcc_32x32_keep32_R(acc1, x3, c0);
      multAcc_32x32_keep32_R(acc2, x0, c0);
      multAcc_32x32_keep32_R(acc3, x1, c0);

      /* Read the b[numTaps-3] coefficients */
      c0 = *(pb++);

      /* Read x[n-numTaps-6] sample */
      x2 = *(px++);

      /* Perform the multiply-accumulates */      
      multAcc_32x32_keep32_R(acc0, x3, c0);
      multAcc_32x32_keep32_R(acc1, x0, c0);
      multAcc_32x32_keep32_R(acc2, x1, c0);
      multAcc_32x32_keep32_R(acc3, x2, c0);
      i--;
    }

    /* If the filter length is not a multiple of 4, compute the remaining filter taps */

    i = numTaps - (tapCnt * 4u);
    while(i > 0u)
    {
      /* Read coefficients */
      c0 = *(pb++);

      /* Fetch 1 state variable */
      x3 = *(px++);

      /* Perform the multiply-accumulates */      
      multAcc_32x32_keep32_R(acc0, x0, c0);
      multAcc_32x32_keep32_R(acc1, x1, c0);
      multAcc_32x32_keep32_R(acc2, x2, c0);
      multAcc_32x32_keep32_R(acc3, x3, c0);

      /* Reuse the present sample states for next sample */
      x0 = x1;
      x1 = x2;
      x2 = x3;

      /* Decrement the loop counter */
      i--;
    }

    /* Advance the state pointer by 4 to process the next group of 4 samples */
    pState = pState + 4;

    /* The results in the 4 accumulators are in 2.30 format.  Convert to 1.31    
     ** Then store the 4 outputs in the destination buffer. */
    *pDst++ = (q31_t) (acc0 << 1);
    *pDst++ = (q31_t) (acc1 << 1);
    *pDst++ = (q31_t) (acc2 << 1);
    *pDst++ = (q31_t) (acc3 << 1);

    /* Decrement the samples loop counter */
    blkCnt--;
  }


  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.    
   ** No loop unrolling is used. */
  blkCnt = blockSize % 4u;

  while(blkCnt > 0u)
  {
    /* Copy one sample at a time into state buffer */
    *pStateCurnt++ = *pSrc++;

    /* Set the accumulator to zero */
    acc0 = 0;

    /* Initialize state pointer */
    px = pState;

    /* Initialize Coefficient pointer */
    pb = (pCoeffs);

    i = numTaps;

    /* Perform the multiply-accumulates */
    do
    {
      multAcc_32x32_keep32_R(acc0, (*px++), (*(pb++)));
      i--;
    } while(i > 0u);

    /* The result is in 2.30 format.  Convert to 1.31    
     ** Then store the output in the destination buffer. */
    *pDst++ = (q31_t) (acc0 << 1);

    /* Advance state pointer by 1 for the next sample */
    pState = pState + 1;

    /* Decrement the samples loop counter */
    blkCnt--;
  }

  /* Processing is complete.    
   ** Now copy the last numTaps - 1 samples to the start of the state buffer.    
   ** This prepares the state buffer for the next function call. */

  /* Points to the start of the state buffer */
  pStateCurnt = S->pState;

  /* Calculate remaining number of copies */
  tapCnt = (numTaps - 1u);

  /* Copy the remaining q31_t data */
  while(tapCnt > 0u)
  {
    *pStateCurnt++ = *pState++;

    /* Decrement the loop counter */
    tapCnt--;
  }


}
IAR_ONLY_LOW_OPTIMIZATION_EXIT
/**    
 * @} end of FIR group    
 */
