/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:	    arm_lms_q31.c    
*    
* Description:	Processing function for the Q31 LMS filter.    
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
 * @brief Processing function for Q31 LMS filter.    
 * @param[in]  *S points to an instance of the Q15 LMS filter structure.    
 * @param[in]  *pSrc points to the block of input data.    
 * @param[in]  *pRef points to the block of reference data.    
 * @param[out] *pOut points to the block of output data.    
 * @param[out] *pErr points to the block of error data.    
 * @param[in]  blockSize number of samples to process.    
 * @return     none.    
 *    
 * \par Scaling and Overflow Behavior:     
 * The function is implemented using an internal 64-bit accumulator.     
 * The accumulator has a 2.62 format and maintains full precision of the intermediate    
 * multiplication results but provides only a single guard bit.     
 * Thus, if the accumulator result overflows it wraps around rather than clips.     
 * In order to avoid overflows completely the input signal must be scaled down by    
 * log2(numTaps) bits.     
 * The reference signal should not be scaled down.     
 * After all multiply-accumulates are performed, the 2.62 accumulator is shifted    
 * and saturated to 1.31 format to yield the final result.     
 * The output signal and error signal are in 1.31 format.     
 *    
 * \par    
 * 	In this filter, filter coefficients are updated for each sample and the updation of filter cofficients are saturted.    
 */

void arm_lms_q31(
  const arm_lms_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pRef,
  q31_t * pOut,
  q31_t * pErr,
  uint32_t blockSize)
{
  q31_t *pState = S->pState;                     /* State pointer */
  uint32_t numTaps = S->numTaps;                 /* Number of filter coefficients in the filter */
  q31_t *pCoeffs = S->pCoeffs;                   /* Coefficient pointer */
  q31_t *pStateCurnt;                            /* Points to the current sample of the state */
  q31_t mu = S->mu;                              /* Adaptive factor */
  q31_t *px;                                     /* Temporary pointer for state */
  q31_t *pb;                                     /* Temporary pointer for coefficient buffer */
  uint32_t tapCnt, blkCnt;                       /* Loop counters */
  q63_t acc;                                     /* Accumulator */
  q31_t e = 0;                                   /* error of data sample */
  q31_t alpha;                                   /* Intermediate constant for taps update */
  q31_t coef;                                    /* Temporary variable for coef */
  q31_t acc_l, acc_h;                            /*  temporary input */
  uint32_t uShift = ((uint32_t) S->postShift + 1u);
  uint32_t lShift = 32u - uShift;                /*  Shift to be applied to the output */

  /* S->pState points to buffer which contains previous frame (numTaps - 1) samples */
  /* pStateCurnt points to the location where the new input data should be written */
  pStateCurnt = &(S->pState[(numTaps - 1u)]);

  /* Initializing blkCnt with blockSize */
  blkCnt = blockSize;


#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */

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
    tapCnt = numTaps >> 2;

    while(tapCnt > 0u)
    {
      /* Perform the multiply-accumulate */
      /* acc +=  b[N] * x[n-N] */
      acc += ((q63_t) (*px++)) * (*pb++);

      /* acc +=  b[N-1] * x[n-N-1] */
      acc += ((q63_t) (*px++)) * (*pb++);

      /* acc +=  b[N-2] * x[n-N-2] */
      acc += ((q63_t) (*px++)) * (*pb++);

      /* acc +=  b[N-3] * x[n-N-3] */
      acc += ((q63_t) (*px++)) * (*pb++);

      /* Decrement the loop counter */
      tapCnt--;
    }

    /* If the filter length is not a multiple of 4, compute the remaining filter taps */
    tapCnt = numTaps % 0x4u;

    while(tapCnt > 0u)
    {
      /* Perform the multiply-accumulate */
      acc += ((q63_t) (*px++)) * (*pb++);

      /* Decrement the loop counter */
      tapCnt--;
    }

    /* Converting the result to 1.31 format */
    /* Calc lower part of acc */
    acc_l = acc & 0xffffffff;

    /* Calc upper part of acc */
    acc_h = (acc >> 32) & 0xffffffff;

    acc = (uint32_t) acc_l >> lShift | acc_h << uShift;

    /* Store the result from accumulator into the destination buffer. */
    *pOut++ = (q31_t) acc;

    /* Compute and store error */
    e = *pRef++ - (q31_t) acc;

    *pErr++ = (q31_t) e;

    /* Compute alpha i.e. intermediate constant for taps update */
    alpha = (q31_t) (((q63_t) e * mu) >> 31);

    /* Initialize state pointer */
    /* Advance state pointer by 1 for the next sample */
    px = pState++;

    /* Initialize coefficient pointer */
    pb = pCoeffs;

    /* Loop unrolling.  Process 4 taps at a time. */
    tapCnt = numTaps >> 2;

    /* Update filter coefficients */
    while(tapCnt > 0u)
    {
      /* coef is in 2.30 format */
      coef = (q31_t) (((q63_t) alpha * (*px++)) >> (32));
      /* get coef in 1.31 format by left shifting */
      *pb = clip_q63_to_q31((q63_t) * pb + (coef << 1u));
      /* update coefficient buffer to next coefficient */
      pb++;

      coef = (q31_t) (((q63_t) alpha * (*px++)) >> (32));
      *pb = clip_q63_to_q31((q63_t) * pb + (coef << 1u));
      pb++;

      coef = (q31_t) (((q63_t) alpha * (*px++)) >> (32));
      *pb = clip_q63_to_q31((q63_t) * pb + (coef << 1u));
      pb++;

      coef = (q31_t) (((q63_t) alpha * (*px++)) >> (32));
      *pb = clip_q63_to_q31((q63_t) * pb + (coef << 1u));
      pb++;

      /* Decrement the loop counter */
      tapCnt--;
    }

    /* If the filter length is not a multiple of 4, compute the remaining filter taps */
    tapCnt = numTaps % 0x4u;

    while(tapCnt > 0u)
    {
      /* Perform the multiply-accumulate */
      coef = (q31_t) (((q63_t) alpha * (*px++)) >> (32));
      *pb = clip_q63_to_q31((q63_t) * pb + (coef << 1u));
      pb++;

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

  /* Loop unrolling for (numTaps - 1u) samples copy */
  tapCnt = (numTaps - 1u) >> 2u;

  /* copy data */
  while(tapCnt > 0u)
  {
    *pStateCurnt++ = *pState++;
    *pStateCurnt++ = *pState++;
    *pStateCurnt++ = *pState++;
    *pStateCurnt++ = *pState++;

    /* Decrement the loop counter */
    tapCnt--;
  }

  /* Calculate remaining number of copies */
  tapCnt = (numTaps - 1u) % 0x4u;

  /* Copy the remaining q31_t data */
  while(tapCnt > 0u)
  {
    *pStateCurnt++ = *pState++;

    /* Decrement the loop counter */
    tapCnt--;
  }

#else

  /* Run the below code for Cortex-M0 */

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
      acc += ((q63_t) (*px++)) * (*pb++);

      /* Decrement the loop counter */
      tapCnt--;
    }

    /* Converting the result to 1.31 format */
    /* Store the result from accumulator into the destination buffer. */
    /* Calc lower part of acc */
    acc_l = acc & 0xffffffff;

    /* Calc upper part of acc */
    acc_h = (acc >> 32) & 0xffffffff;

    acc = (uint32_t) acc_l >> lShift | acc_h << uShift;

    *pOut++ = (q31_t) acc;

    /* Compute and store error */
    e = *pRef++ - (q31_t) acc;

    *pErr++ = (q31_t) e;

    /* Weighting factor for the LMS version */
    alpha = (q31_t) (((q63_t) e * mu) >> 31);

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
      coef = (q31_t) (((q63_t) alpha * (*px++)) >> (32));
      *pb += (coef << 1u);
      pb++;

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
