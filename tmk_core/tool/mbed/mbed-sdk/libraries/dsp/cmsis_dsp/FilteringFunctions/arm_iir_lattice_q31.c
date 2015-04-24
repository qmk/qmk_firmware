/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:	    arm_iir_lattice_q31.c    
*    
* Description:	Q31 IIR lattice filter processing function.    
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
 * @addtogroup IIR_Lattice    
 * @{    
 */

/**    
 * @brief Processing function for the Q31 IIR lattice filter.    
 * @param[in] *S points to an instance of the Q31 IIR lattice structure.    
 * @param[in] *pSrc points to the block of input data.    
 * @param[out] *pDst points to the block of output data.    
 * @param[in] blockSize number of samples to process.    
 * @return none.    
 *    
 * @details    
 * <b>Scaling and Overflow Behavior:</b>    
 * \par    
 * The function is implemented using an internal 64-bit accumulator.    
 * The accumulator has a 2.62 format and maintains full precision of the intermediate multiplication results but provides only a single guard bit.    
 * Thus, if the accumulator result overflows it wraps around rather than clip.    
 * In order to avoid overflows completely the input signal must be scaled down by 2*log2(numStages) bits.    
 * After all multiply-accumulates are performed, the 2.62 accumulator is saturated to 1.32 format and then truncated to 1.31 format.    
 */

void arm_iir_lattice_q31(
  const arm_iir_lattice_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize)
{
  q31_t fcurr, fnext = 0, gcurr = 0, gnext;      /* Temporary variables for lattice stages */
  q63_t acc;                                     /* Accumlator */
  uint32_t blkCnt, tapCnt;                       /* Temporary variables for counts */
  q31_t *px1, *px2, *pk, *pv;                    /* Temporary pointers for state and coef */
  uint32_t numStages = S->numStages;             /* number of stages */
  q31_t *pState;                                 /* State pointer */
  q31_t *pStateCurnt;                            /* State current pointer */

  blkCnt = blockSize;

  pState = &S->pState[0];


#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */

  /* Sample processing */
  while(blkCnt > 0u)
  {
    /* Read Sample from input buffer */
    /* fN(n) = x(n) */
    fcurr = *pSrc++;

    /* Initialize state read pointer */
    px1 = pState;
    /* Initialize state write pointer */
    px2 = pState;
    /* Set accumulator to zero */
    acc = 0;
    /* Initialize Ladder coeff pointer */
    pv = &S->pvCoeffs[0];
    /* Initialize Reflection coeff pointer */
    pk = &S->pkCoeffs[0];


    /* Process sample for first tap */
    gcurr = *px1++;
    /* fN-1(n) = fN(n) - kN * gN-1(n-1) */
    fnext = __QSUB(fcurr, (q31_t) (((q63_t) gcurr * (*pk)) >> 31));
    /* gN(n) = kN * fN-1(n) + gN-1(n-1) */
    gnext = __QADD(gcurr, (q31_t) (((q63_t) fnext * (*pk++)) >> 31));
    /* write gN-1(n-1) into state for next sample processing */
    *px2++ = gnext;
    /* y(n) += gN(n) * vN  */
    acc += ((q63_t) gnext * *pv++);

    /* Update f values for next coefficient processing */
    fcurr = fnext;

    /* Loop unrolling.  Process 4 taps at a time. */
    tapCnt = (numStages - 1u) >> 2;

    while(tapCnt > 0u)
    {

      /* Process sample for 2nd, 6th .. taps */
      /* Read gN-2(n-1) from state buffer */
      gcurr = *px1++;
      /* fN-2(n) = fN-1(n) - kN-1 * gN-2(n-1) */
      fnext = __QSUB(fcurr, (q31_t) (((q63_t) gcurr * (*pk)) >> 31));
      /* gN-1(n) = kN-1 * fN-2(n) + gN-2(n-1) */
      gnext = __QADD(gcurr, (q31_t) (((q63_t) fnext * (*pk++)) >> 31));
      /* y(n) += gN-1(n) * vN-1  */
      /* process for gN-5(n) * vN-5, gN-9(n) * vN-9 ... */
      acc += ((q63_t) gnext * *pv++);
      /* write gN-1(n) into state for next sample processing */
      *px2++ = gnext;

      /* Process sample for 3nd, 7th ...taps */
      /* Read gN-3(n-1) from state buffer */
      gcurr = *px1++;
      /* Process sample for 3rd, 7th .. taps */
      /* fN-3(n) = fN-2(n) - kN-2 * gN-3(n-1) */
      fcurr = __QSUB(fnext, (q31_t) (((q63_t) gcurr * (*pk)) >> 31));
      /* gN-2(n) = kN-2 * fN-3(n) + gN-3(n-1) */
      gnext = __QADD(gcurr, (q31_t) (((q63_t) fcurr * (*pk++)) >> 31));
      /* y(n) += gN-2(n) * vN-2  */
      /* process for gN-6(n) * vN-6, gN-10(n) * vN-10 ... */
      acc += ((q63_t) gnext * *pv++);
      /* write gN-2(n) into state for next sample processing */
      *px2++ = gnext;


      /* Process sample for 4th, 8th ...taps */
      /* Read gN-4(n-1) from state buffer */
      gcurr = *px1++;
      /* Process sample for 4th, 8th .. taps */
      /* fN-4(n) = fN-3(n) - kN-3 * gN-4(n-1) */
      fnext = __QSUB(fcurr, (q31_t) (((q63_t) gcurr * (*pk)) >> 31));
      /* gN-3(n) = kN-3 * fN-4(n) + gN-4(n-1) */
      gnext = __QADD(gcurr, (q31_t) (((q63_t) fnext * (*pk++)) >> 31));
      /* y(n) += gN-3(n) * vN-3  */
      /* process for gN-7(n) * vN-7, gN-11(n) * vN-11 ... */
      acc += ((q63_t) gnext * *pv++);
      /* write gN-3(n) into state for next sample processing */
      *px2++ = gnext;


      /* Process sample for 5th, 9th ...taps */
      /* Read gN-5(n-1) from state buffer */
      gcurr = *px1++;
      /* Process sample for 5th, 9th .. taps */
      /* fN-5(n) = fN-4(n) - kN-4 * gN-1(n-1) */
      fcurr = __QSUB(fnext, (q31_t) (((q63_t) gcurr * (*pk)) >> 31));
      /* gN-4(n) = kN-4 * fN-5(n) + gN-5(n-1) */
      gnext = __QADD(gcurr, (q31_t) (((q63_t) fcurr * (*pk++)) >> 31));
      /* y(n) += gN-4(n) * vN-4  */
      /* process for gN-8(n) * vN-8, gN-12(n) * vN-12 ... */
      acc += ((q63_t) gnext * *pv++);
      /* write gN-4(n) into state for next sample processing */
      *px2++ = gnext;

      tapCnt--;

    }

    fnext = fcurr;

    /* If the filter length is not a multiple of 4, compute the remaining filter taps */
    tapCnt = (numStages - 1u) % 0x4u;

    while(tapCnt > 0u)
    {
      gcurr = *px1++;
      /* Process sample for last taps */
      fnext = __QSUB(fcurr, (q31_t) (((q63_t) gcurr * (*pk)) >> 31));
      gnext = __QADD(gcurr, (q31_t) (((q63_t) fnext * (*pk++)) >> 31));
      /* Output samples for last taps */
      acc += ((q63_t) gnext * *pv++);
      *px2++ = gnext;
      fcurr = fnext;

      tapCnt--;

    }

    /* y(n) += g0(n) * v0 */
    acc += (q63_t) fnext *(
  *pv++);

    *px2++ = fnext;

    /* write out into pDst */
    *pDst++ = (q31_t) (acc >> 31u);

    /* Advance the state pointer by 4 to process the next group of 4 samples */
    pState = pState + 1u;
    blkCnt--;

  }

  /* Processing is complete. Now copy last S->numStages samples to start of the buffer    
     for the preperation of next frame process */

  /* Points to the start of the state buffer */
  pStateCurnt = &S->pState[0];
  pState = &S->pState[blockSize];

  tapCnt = numStages >> 2u;

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
  tapCnt = (numStages) % 0x4u;

  /* Copy the remaining q31_t data */
  while(tapCnt > 0u)
  {
    *pStateCurnt++ = *pState++;

    /* Decrement the loop counter */
    tapCnt--;
  };

#else

  /* Run the below code for Cortex-M0 */
  /* Sample processing */
  while(blkCnt > 0u)
  {
    /* Read Sample from input buffer */
    /* fN(n) = x(n) */
    fcurr = *pSrc++;

    /* Initialize state read pointer */
    px1 = pState;
    /* Initialize state write pointer */
    px2 = pState;
    /* Set accumulator to zero */
    acc = 0;
    /* Initialize Ladder coeff pointer */
    pv = &S->pvCoeffs[0];
    /* Initialize Reflection coeff pointer */
    pk = &S->pkCoeffs[0];

    tapCnt = numStages;

    while(tapCnt > 0u)
    {
      gcurr = *px1++;
      /* Process sample */
      /* fN-1(n) = fN(n) - kN * gN-1(n-1) */
      fnext =
        clip_q63_to_q31(((q63_t) fcurr -
                         ((q31_t) (((q63_t) gcurr * (*pk)) >> 31))));
      /* gN(n) = kN * fN-1(n) + gN-1(n-1) */
      gnext =
        clip_q63_to_q31(((q63_t) gcurr +
                         ((q31_t) (((q63_t) fnext * (*pk++)) >> 31))));
      /* Output samples */
      /* y(n) += gN(n) * vN  */
      acc += ((q63_t) gnext * *pv++);
      /* write gN-1(n-1) into state for next sample processing */
      *px2++ = gnext;
      /* Update f values for next coefficient processing */
      fcurr = fnext;

      tapCnt--;
    }

    /* y(n) += g0(n) * v0 */
    acc += (q63_t) fnext *(
  *pv++);

    *px2++ = fnext;

    /* write out into pDst */
    *pDst++ = (q31_t) (acc >> 31u);

    /* Advance the state pointer by 1 to process the next group of samples */
    pState = pState + 1u;
    blkCnt--;

  }

  /* Processing is complete. Now copy last S->numStages samples to start of the buffer           
     for the preperation of next frame process */

  /* Points to the start of the state buffer */
  pStateCurnt = &S->pState[0];
  pState = &S->pState[blockSize];

  tapCnt = numStages;

  /* Copy the remaining q31_t data */
  while(tapCnt > 0u)
  {
    *pStateCurnt++ = *pState++;

    /* Decrement the loop counter */
    tapCnt--;
  }

#endif /*   #ifndef ARM_MATH_CM0_FAMILY */

}




/**    
 * @} end of IIR_Lattice group    
 */
