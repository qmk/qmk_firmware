/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:	    arm_lms_q15.c    
*    
* Description:	Processing function for the Q15 LMS filter.    
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
 * @ingroup groupFilters    
 */

/**    
 * @addtogroup LMS    
 * @{    
 */

 /**    
 * @brief Processing function for Q15 LMS filter.    
 * @param[in] *S points to an instance of the Q15 LMS filter structure.    
 * @param[in] *pSrc points to the block of input data.    
 * @param[in] *pRef points to the block of reference data.    
 * @param[out] *pOut points to the block of output data.    
 * @param[out] *pErr points to the block of error data.    
 * @param[in] blockSize number of samples to process.    
 * @return none.    
 *    
 * \par Scaling and Overflow Behavior:    
 * The function is implemented using a 64-bit internal accumulator.    
 * Both coefficients and state variables are represented in 1.15 format and multiplications yield a 2.30 result.    
 * The 2.30 intermediate results are accumulated in a 64-bit accumulator in 34.30 format.    
 * There is no risk of internal overflow with this approach and the full precision of intermediate multiplications is preserved.    
 * After all additions have been performed, the accumulator is truncated to 34.15 format by discarding low 15 bits.    
 * Lastly, the accumulator is saturated to yield a result in 1.15 format.    
 *   
 * \par   
 * 	In this filter, filter coefficients are updated for each sample and the updation of filter cofficients are saturted.   
 *    
 */

void arm_lms_q15(
  const arm_lms_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pRef,
  q15_t * pOut,
  q15_t * pErr,
  uint32_t blockSize)
{
  q15_t *pState = S->pState;                     /* State pointer */
  uint32_t numTaps = S->numTaps;                 /* Number of filter coefficients in the filter */
  q15_t *pCoeffs = S->pCoeffs;                   /* Coefficient pointer */
  q15_t *pStateCurnt;                            /* Points to the current sample of the state */
  q15_t mu = S->mu;                              /* Adaptive factor */
  q15_t *px;                                     /* Temporary pointer for state */
  q15_t *pb;                                     /* Temporary pointer for coefficient buffer */
  uint32_t tapCnt, blkCnt;                       /* Loop counters */
  q63_t acc;                                     /* Accumulator */
  q15_t e = 0;                                   /* error of data sample */
  q15_t alpha;                                   /* Intermediate constant for taps update */
  q31_t acc_l, acc_h;
  int32_t lShift = (15 - (int32_t) S->postShift);       /*  Post shift  */
  int32_t uShift = (32 - lShift);


#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */

  q31_t coef;                                    /* Teporary variable for coefficient */

  /* S->pState points to buffer which contains previous frame (numTaps - 1) samples */
  /* pStateCurnt points to the location where the new input data should be written */
  pStateCurnt = &(S->pState[(numTaps - 1u)]);

  /* Initializing blkCnt with blockSize */
  blkCnt = blockSize;

  while(blkCnt > 0u)
  {
    /* Copy the new input sample into the state buffer */
    *pStateCurnt++ = *pSrc++;

    /* Initialize state pointer */
    px = pState;

    /* Initialize coefficient pointer */
    pb = pCoeffs;

    /* Set the accumulator to zero */
    acc = 0;

    /* Loop unrolling.  Process 4 taps at a time. */
    tapCnt = numTaps >> 2u;

    while(tapCnt > 0u)
    {
      /* acc +=  b[N] * x[n-N] + b[N-1] * x[n-N-1] */
      /* Perform the multiply-accumulate */
#ifndef UNALIGNED_SUPPORT_DISABLE

      acc = __SMLALD(*__SIMD32(px)++, (*__SIMD32(pb)++), acc);
      acc = __SMLALD(*__SIMD32(px)++, (*__SIMD32(pb)++), acc);

#else

      acc += (q63_t) (((q31_t) (*px++) * (*pb++)));
      acc += (q63_t) (((q31_t) (*px++) * (*pb++)));
      acc += (q63_t) (((q31_t) (*px++) * (*pb++)));
      acc += (q63_t) (((q31_t) (*px++) * (*pb++)));


#endif	/*	#ifndef UNALIGNED_SUPPORT_DISABLE	*/

      /* Decrement the loop counter */
      tapCnt--;
    }

    /* If the filter length is not a multiple of 4, compute the remaining filter taps */
    tapCnt = numTaps % 0x4u;

    while(tapCnt > 0u)
    {
      /* Perform the multiply-accumulate */
      acc += (q63_t) (((q31_t) (*px++) * (*pb++)));

      /* Decrement the loop counter */
      tapCnt--;
    }

    /* Calc lower part of acc */
    acc_l = acc & 0xffffffff;

    /* Calc upper part of acc */
    acc_h = (acc >> 32) & 0xffffffff;

    /* Apply shift for lower part of acc and upper part of acc */
    acc = (uint32_t) acc_l >> lShift | acc_h << uShift;

    /* Converting the result to 1.15 format and saturate the output */
    acc = __SSAT(acc, 16);

    /* Store the result from accumulator into the destination buffer. */
    *pOut++ = (q15_t) acc;

    /* Compute and store error */
    e = *pRef++ - (q15_t) acc;

    *pErr++ = (q15_t) e;

    /* Compute alpha i.e. intermediate constant for taps update */
    alpha = (q15_t) (((q31_t) e * (mu)) >> 15);

    /* Initialize state pointer */
    /* Advance state pointer by 1 for the next sample */
    px = pState++;

    /* Initialize coefficient pointer */
    pb = pCoeffs;

    /* Loop unrolling.  Process 4 taps at a time. */
    tapCnt = numTaps >> 2u;

    /* Update filter coefficients */
    while(tapCnt > 0u)
    {
      coef = (q31_t) * pb + (((q31_t) alpha * (*px++)) >> 15);
      *pb++ = (q15_t) __SSAT((coef), 16);
      coef = (q31_t) * pb + (((q31_t) alpha * (*px++)) >> 15);
      *pb++ = (q15_t) __SSAT((coef), 16);
      coef = (q31_t) * pb + (((q31_t) alpha * (*px++)) >> 15);
      *pb++ = (q15_t) __SSAT((coef), 16);
      coef = (q31_t) * pb + (((q31_t) alpha * (*px++)) >> 15);
      *pb++ = (q15_t) __SSAT((coef), 16);

      /* Decrement the loop counter */
      tapCnt--;
    }

    /* If the filter length is not a multiple of 4, compute the remaining filter taps */
    tapCnt = numTaps % 0x4u;

    while(tapCnt > 0u)
    {
      /* Perform the multiply-accumulate */
      coef = (q31_t) * pb + (((q31_t) alpha * (*px++)) >> 15);
      *pb++ = (q15_t) __SSAT((coef), 16);

      /* Decrement the loop counter */
      tapCnt--;
    }

    /* Decrement the loop counter */
    blkCnt--;

  }

  /* Processing is complete. Now copy the last numTaps - 1 samples to the    
     satrt of the state buffer. This prepares the state buffer for the    
     next function call. */

  /* Points to the start of the pState buffer */
  pStateCurnt = S->pState;

  /* Calculation of count for copying integer writes */
  tapCnt = (numTaps - 1u) >> 2;

  while(tapCnt > 0u)
  {

#ifndef UNALIGNED_SUPPORT_DISABLE

    *__SIMD32(pStateCurnt)++ = *__SIMD32(pState)++;
    *__SIMD32(pStateCurnt)++ = *__SIMD32(pState)++;
#else
    *pStateCurnt++ = *pState++;
    *pStateCurnt++ = *pState++;
    *pStateCurnt++ = *pState++;
    *pStateCurnt++ = *pState++;
#endif

    tapCnt--;

  }

  /* Calculation of count for remaining q15_t data */
  tapCnt = (numTaps - 1u) % 0x4u;

  /* copy data */
  while(tapCnt > 0u)
  {
    *pStateCurnt++ = *pState++;

    /* Decrement the loop counter */
    tapCnt--;
  }

#else

  /* Run the below code for Cortex-M0 */

  /* S->pState points to buffer which contains previous frame (numTaps - 1) samples */
  /* pStateCurnt points to the location where the new input data should be written */
  pStateCurnt = &(S->pState[(numTaps - 1u)]);

  /* Loop over blockSize number of values */
  blkCnt = blockSize;

  while(blkCnt > 0u)
  {
    /* Copy the new input sample into the state buffer */
    *pStateCurnt++ = *pSrc++;

    /* Initialize pState pointer */
    px = pState;

    /* Initialize pCoeffs pointer */
    pb = pCoeffs;

    /* Set the accumulator to zero */
    acc = 0;

    /* Loop over numTaps number of values */
    tapCnt = numTaps;

    while(tapCnt > 0u)
    {
      /* Perform the multiply-accumulate */
      acc += (q63_t) ((q31_t) (*px++) * (*pb++));

      /* Decrement the loop counter */
      tapCnt--;
    }

    /* Calc lower part of acc */
    acc_l = acc & 0xffffffff;

    /* Calc upper part of acc */
    acc_h = (acc >> 32) & 0xffffffff;

    /* Apply shift for lower part of acc and upper part of acc */
    acc = (uint32_t) acc_l >> lShift | acc_h << uShift;

    /* Converting the result to 1.15 format and saturate the output */
    acc = __SSAT(acc, 16);

    /* Store the result from accumulator into the destination buffer. */
    *pOut++ = (q15_t) acc;

    /* Compute and store error */
    e = *pRef++ - (q15_t) acc;

    *pErr++ = (q15_t) e;

    /* Compute alpha i.e. intermediate constant for taps update */
    alpha = (q15_t) (((q31_t) e * (mu)) >> 15);

    /* Initialize pState pointer */
    /* Advance state pointer by 1 for the next sample */
    px = pState++;

    /* Initialize pCoeffs pointer */
    pb = pCoeffs;

    /* Loop over numTaps number of values */
    tapCnt = numTaps;

    while(tapCnt > 0u)
    {
      /* Perform the multiply-accumulate */
      *pb++ += (q15_t) (((q31_t) alpha * (*px++)) >> 15);

      /* Decrement the loop counter */
      tapCnt--;
    }

    /* Decrement the loop counter */
    blkCnt--;

  }

  /* Processing is complete. Now copy the last numTaps - 1 samples to the        
     start of the state buffer. This prepares the state buffer for the   
     next function call. */

  /* Points to the start of the pState buffer */
  pStateCurnt = S->pState;

  /*  Copy (numTaps - 1u) samples  */
  tapCnt = (numTaps - 1u);

  /* Copy the data */
  while(tapCnt > 0u)
  {
    *pStateCurnt++ = *pState++;

    /* Decrement the loop counter */
    tapCnt--;
  }

#endif /*   #ifndef ARM_MATH_CM0_FAMILY */

}

/**    
   * @} end of LMS group    
   */
