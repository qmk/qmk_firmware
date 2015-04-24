/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:	    arm_fir_interpolate_f32.c    
*    
* Description:	FIR interpolation for floating-point sequences.    
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
 * @defgroup FIR_Interpolate Finite Impulse Response (FIR) Interpolator    
 *    
 * These functions combine an upsampler (zero stuffer) and an FIR filter.    
 * They are used in multirate systems for increasing the sample rate of a signal without introducing high frequency images.    
 * Conceptually, the functions are equivalent to the block diagram below:    
 * \image html FIRInterpolator.gif "Components included in the FIR Interpolator functions"    
 * After upsampling by a factor of <code>L</code>, the signal should be filtered by a lowpass filter with a normalized    
 * cutoff frequency of <code>1/L</code> in order to eliminate high frequency copies of the spectrum.    
 * The user of the function is responsible for providing the filter coefficients.    
 *    
 * The FIR interpolator functions provided in the CMSIS DSP Library combine the upsampler and FIR filter in an efficient manner.    
 * The upsampler inserts <code>L-1</code> zeros between each sample.    
 * Instead of multiplying by these zero values, the FIR filter is designed to skip them.    
 * This leads to an efficient implementation without any wasted effort.    
 * The functions operate on blocks of input and output data.    
 * <code>pSrc</code> points to an array of <code>blockSize</code> input values and    
 * <code>pDst</code> points to an array of <code>blockSize*L</code> output values.    
 *    
 * The library provides separate functions for Q15, Q31, and floating-point data types.    
 *    
 * \par Algorithm:    
 * The functions use a polyphase filter structure:    
 * <pre>    
 *    y[n] = b[0] * x[n] + b[L]   * x[n-1] + ... + b[L*(phaseLength-1)] * x[n-phaseLength+1]    
 *    y[n+1] = b[1] * x[n] + b[L+1] * x[n-1] + ... + b[L*(phaseLength-1)+1] * x[n-phaseLength+1]    
 *    ...    
 *    y[n+(L-1)] = b[L-1] * x[n] + b[2*L-1] * x[n-1] + ....+ b[L*(phaseLength-1)+(L-1)] * x[n-phaseLength+1]    
 * </pre>    
 * This approach is more efficient than straightforward upsample-then-filter algorithms.    
 * With this method the computation is reduced by a factor of <code>1/L</code> when compared to using a standard FIR filter.    
 * \par    
 * <code>pCoeffs</code> points to a coefficient array of size <code>numTaps</code>.    
 * <code>numTaps</code> must be a multiple of the interpolation factor <code>L</code> and this is checked by the    
 * initialization functions.    
 * Internally, the function divides the FIR filter's impulse response into shorter filters of length    
 * <code>phaseLength=numTaps/L</code>.    
 * Coefficients are stored in time reversed order.    
 * \par    
 * <pre>    
 *    {b[numTaps-1], b[numTaps-2], b[N-2], ..., b[1], b[0]}    
 * </pre>    
 * \par    
 * <code>pState</code> points to a state array of size <code>blockSize + phaseLength - 1</code>.    
 * Samples in the state buffer are stored in the order:    
 * \par    
 * <pre>    
 *    {x[n-phaseLength+1], x[n-phaseLength], x[n-phaseLength-1], x[n-phaseLength-2]....x[0], x[1], ..., x[blockSize-1]}    
 * </pre>    
 * The state variables are updated after each block of data is processed, the coefficients are untouched.    
 *    
 * \par Instance Structure    
 * The coefficients and state variables for a filter are stored together in an instance data structure.    
 * A separate instance structure must be defined for each filter.    
 * Coefficient arrays may be shared among several instances while state variable array should be allocated separately.    
 * There are separate instance structure declarations for each of the 3 supported data types.    
 *    
 * \par Initialization Functions    
 * There is also an associated initialization function for each data type.    
 * The initialization function performs the following operations:    
 * - Sets the values of the internal structure fields.    
 * - Zeros out the values in the state buffer.    
 * - Checks to make sure that the length of the filter is a multiple of the interpolation factor.    
 * To do this manually without calling the init function, assign the follow subfields of the instance structure:
 * L (interpolation factor), pCoeffs, phaseLength (numTaps / L), pState. Also set all of the values in pState to zero. 
 *    
 * \par    
 * Use of the initialization function is optional.    
 * However, if the initialization function is used, then the instance structure cannot be placed into a const data section.    
 * To place an instance structure into a const data section, the instance structure must be manually initialized.    
 * The code below statically initializes each of the 3 different data type filter instance structures    
 * <pre>    
 * arm_fir_interpolate_instance_f32 S = {L, phaseLength, pCoeffs, pState};    
 * arm_fir_interpolate_instance_q31 S = {L, phaseLength, pCoeffs, pState};    
 * arm_fir_interpolate_instance_q15 S = {L, phaseLength, pCoeffs, pState};    
 * </pre>    
 * where <code>L</code> is the interpolation factor; <code>phaseLength=numTaps/L</code> is the    
 * length of each of the shorter FIR filters used internally,    
 * <code>pCoeffs</code> is the address of the coefficient buffer;    
 * <code>pState</code> is the address of the state buffer.    
 * Be sure to set the values in the state buffer to zeros when doing static initialization.    
 *    
 * \par Fixed-Point Behavior    
 * Care must be taken when using the fixed-point versions of the FIR interpolate filter functions.    
 * In particular, the overflow and saturation behavior of the accumulator used in each function must be considered.    
 * Refer to the function specific documentation below for usage guidelines.    
 */

/**    
 * @addtogroup FIR_Interpolate    
 * @{    
 */

/**    
 * @brief Processing function for the floating-point FIR interpolator.    
 * @param[in] *S        points to an instance of the floating-point FIR interpolator structure.    
 * @param[in] *pSrc     points to the block of input data.    
 * @param[out] *pDst    points to the block of output data.    
 * @param[in] blockSize number of input samples to process per call.    
 * @return none.    
 */
#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */

void arm_fir_interpolate_f32(
  const arm_fir_interpolate_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize)
{
  float32_t *pState = S->pState;                 /* State pointer */
  float32_t *pCoeffs = S->pCoeffs;               /* Coefficient pointer */
  float32_t *pStateCurnt;                        /* Points to the current sample of the state */
  float32_t *ptr1, *ptr2;                        /* Temporary pointers for state and coefficient buffers */
  float32_t sum0;                                /* Accumulators */
  float32_t x0, c0;                              /* Temporary variables to hold state and coefficient values */
  uint32_t i, blkCnt, j;                         /* Loop counters */
  uint16_t phaseLen = S->phaseLength, tapCnt;    /* Length of each polyphase filter component */
  float32_t acc0, acc1, acc2, acc3;
  float32_t x1, x2, x3;
  uint32_t blkCntN4;
  float32_t c1, c2, c3;

  /* S->pState buffer contains previous frame (phaseLen - 1) samples */
  /* pStateCurnt points to the location where the new input data should be written */
  pStateCurnt = S->pState + (phaseLen - 1u);

  /* Initialise  blkCnt */
  blkCnt = blockSize / 4;
  blkCntN4 = blockSize - (4 * blkCnt);

  /* Samples loop unrolled by 4 */
  while(blkCnt > 0u)
  {
    /* Copy new input sample into the state buffer */
    *pStateCurnt++ = *pSrc++;
    *pStateCurnt++ = *pSrc++;
    *pStateCurnt++ = *pSrc++;
    *pStateCurnt++ = *pSrc++;

    /* Address modifier index of coefficient buffer */
    j = 1u;

    /* Loop over the Interpolation factor. */
    i = (S->L);

    while(i > 0u)
    {
      /* Set accumulator to zero */
      acc0 = 0.0f;
      acc1 = 0.0f;
      acc2 = 0.0f;
      acc3 = 0.0f;

      /* Initialize state pointer */
      ptr1 = pState;

      /* Initialize coefficient pointer */
      ptr2 = pCoeffs + (S->L - j);

      /* Loop over the polyPhase length. Unroll by a factor of 4.        
       ** Repeat until we've computed numTaps-(4*S->L) coefficients. */
      tapCnt = phaseLen >> 2u;

      x0 = *(ptr1++);
      x1 = *(ptr1++);
      x2 = *(ptr1++);

      while(tapCnt > 0u)
      {

        /* Read the input sample */
        x3 = *(ptr1++);

        /* Read the coefficient */
        c0 = *(ptr2);

        /* Perform the multiply-accumulate */
        acc0 += x0 * c0;
        acc1 += x1 * c0;
        acc2 += x2 * c0;
        acc3 += x3 * c0;

        /* Read the coefficient */
        c1 = *(ptr2 + S->L);

        /* Read the input sample */
        x0 = *(ptr1++);

        /* Perform the multiply-accumulate */
        acc0 += x1 * c1;
        acc1 += x2 * c1;
        acc2 += x3 * c1;
        acc3 += x0 * c1;

        /* Read the coefficient */
        c2 = *(ptr2 + S->L * 2);

        /* Read the input sample */
        x1 = *(ptr1++);

        /* Perform the multiply-accumulate */
        acc0 += x2 * c2;
        acc1 += x3 * c2;
        acc2 += x0 * c2;
        acc3 += x1 * c2;

        /* Read the coefficient */
        c3 = *(ptr2 + S->L * 3);

        /* Read the input sample */
        x2 = *(ptr1++);

        /* Perform the multiply-accumulate */
        acc0 += x3 * c3;
        acc1 += x0 * c3;
        acc2 += x1 * c3;
        acc3 += x2 * c3;


        /* Upsampling is done by stuffing L-1 zeros between each sample.        
         * So instead of multiplying zeros with coefficients,        
         * Increment the coefficient pointer by interpolation factor times. */
        ptr2 += 4 * S->L;

        /* Decrement the loop counter */
        tapCnt--;
      }

      /* If the polyPhase length is not a multiple of 4, compute the remaining filter taps */
      tapCnt = phaseLen % 0x4u;

      while(tapCnt > 0u)
      {

        /* Read the input sample */
        x3 = *(ptr1++);

        /* Read the coefficient */
        c0 = *(ptr2);

        /* Perform the multiply-accumulate */
        acc0 += x0 * c0;
        acc1 += x1 * c0;
        acc2 += x2 * c0;
        acc3 += x3 * c0;

        /* Increment the coefficient pointer by interpolation factor times. */
        ptr2 += S->L;

        /* update states for next sample processing */
        x0 = x1;
        x1 = x2;
        x2 = x3;

        /* Decrement the loop counter */
        tapCnt--;
      }

      /* The result is in the accumulator, store in the destination buffer. */
      *pDst = acc0;
      *(pDst + S->L) = acc1;
      *(pDst + 2 * S->L) = acc2;
      *(pDst + 3 * S->L) = acc3;

      pDst++;

      /* Increment the address modifier index of coefficient buffer */
      j++;

      /* Decrement the loop counter */
      i--;
    }

    /* Advance the state pointer by 1        
     * to process the next group of interpolation factor number samples */
    pState = pState + 4;

    pDst += S->L * 3;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.        
   ** No loop unrolling is used. */

  while(blkCntN4 > 0u)
  {
    /* Copy new input sample into the state buffer */
    *pStateCurnt++ = *pSrc++;

    /* Address modifier index of coefficient buffer */
    j = 1u;

    /* Loop over the Interpolation factor. */
    i = S->L;
    while(i > 0u)
    {
      /* Set accumulator to zero */
      sum0 = 0.0f;

      /* Initialize state pointer */
      ptr1 = pState;

      /* Initialize coefficient pointer */
      ptr2 = pCoeffs + (S->L - j);

      /* Loop over the polyPhase length. Unroll by a factor of 4.        
       ** Repeat until we've computed numTaps-(4*S->L) coefficients. */
      tapCnt = phaseLen >> 2u;
      while(tapCnt > 0u)
      {

        /* Read the coefficient */
        c0 = *(ptr2);

        /* Upsampling is done by stuffing L-1 zeros between each sample.        
         * So instead of multiplying zeros with coefficients,        
         * Increment the coefficient pointer by interpolation factor times. */
        ptr2 += S->L;

        /* Read the input sample */
        x0 = *(ptr1++);

        /* Perform the multiply-accumulate */
        sum0 += x0 * c0;

        /* Read the coefficient */
        c0 = *(ptr2);

        /* Increment the coefficient pointer by interpolation factor times. */
        ptr2 += S->L;

        /* Read the input sample */
        x0 = *(ptr1++);

        /* Perform the multiply-accumulate */
        sum0 += x0 * c0;

        /* Read the coefficient */
        c0 = *(ptr2);

        /* Increment the coefficient pointer by interpolation factor times. */
        ptr2 += S->L;

        /* Read the input sample */
        x0 = *(ptr1++);

        /* Perform the multiply-accumulate */
        sum0 += x0 * c0;

        /* Read the coefficient */
        c0 = *(ptr2);

        /* Increment the coefficient pointer by interpolation factor times. */
        ptr2 += S->L;

        /* Read the input sample */
        x0 = *(ptr1++);

        /* Perform the multiply-accumulate */
        sum0 += x0 * c0;

        /* Decrement the loop counter */
        tapCnt--;
      }

      /* If the polyPhase length is not a multiple of 4, compute the remaining filter taps */
      tapCnt = phaseLen % 0x4u;

      while(tapCnt > 0u)
      {
        /* Perform the multiply-accumulate */
        sum0 += *(ptr1++) * (*ptr2);

        /* Increment the coefficient pointer by interpolation factor times. */
        ptr2 += S->L;

        /* Decrement the loop counter */
        tapCnt--;
      }

      /* The result is in the accumulator, store in the destination buffer. */
      *pDst++ = sum0;

      /* Increment the address modifier index of coefficient buffer */
      j++;

      /* Decrement the loop counter */
      i--;
    }

    /* Advance the state pointer by 1        
     * to process the next group of interpolation factor number samples */
    pState = pState + 1;

    /* Decrement the loop counter */
    blkCntN4--;
  }

  /* Processing is complete.        
   ** Now copy the last phaseLen - 1 samples to the satrt of the state buffer.        
   ** This prepares the state buffer for the next function call. */

  /* Points to the start of the state buffer */
  pStateCurnt = S->pState;

  tapCnt = (phaseLen - 1u) >> 2u;

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

  tapCnt = (phaseLen - 1u) % 0x04u;

  /* copy data */
  while(tapCnt > 0u)
  {
    *pStateCurnt++ = *pState++;

    /* Decrement the loop counter */
    tapCnt--;
  }
}

#else

  /* Run the below code for Cortex-M0 */

void arm_fir_interpolate_f32(
  const arm_fir_interpolate_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize)
{
  float32_t *pState = S->pState;                 /* State pointer */
  float32_t *pCoeffs = S->pCoeffs;               /* Coefficient pointer */
  float32_t *pStateCurnt;                        /* Points to the current sample of the state */
  float32_t *ptr1, *ptr2;                        /* Temporary pointers for state and coefficient buffers */


  float32_t sum;                                 /* Accumulator */
  uint32_t i, blkCnt;                            /* Loop counters */
  uint16_t phaseLen = S->phaseLength, tapCnt;    /* Length of each polyphase filter component */


  /* S->pState buffer contains previous frame (phaseLen - 1) samples */
  /* pStateCurnt points to the location where the new input data should be written */
  pStateCurnt = S->pState + (phaseLen - 1u);

  /* Total number of intput samples */
  blkCnt = blockSize;

  /* Loop over the blockSize. */
  while(blkCnt > 0u)
  {
    /* Copy new input sample into the state buffer */
    *pStateCurnt++ = *pSrc++;

    /* Loop over the Interpolation factor. */
    i = S->L;

    while(i > 0u)
    {
      /* Set accumulator to zero */
      sum = 0.0f;

      /* Initialize state pointer */
      ptr1 = pState;

      /* Initialize coefficient pointer */
      ptr2 = pCoeffs + (i - 1u);

      /* Loop over the polyPhase length */
      tapCnt = phaseLen;

      while(tapCnt > 0u)
      {
        /* Perform the multiply-accumulate */
        sum += *ptr1++ * *ptr2;

        /* Increment the coefficient pointer by interpolation factor times. */
        ptr2 += S->L;

        /* Decrement the loop counter */
        tapCnt--;
      }

      /* The result is in the accumulator, store in the destination buffer. */
      *pDst++ = sum;

      /* Decrement the loop counter */
      i--;
    }

    /* Advance the state pointer by 1           
     * to process the next group of interpolation factor number samples */
    pState = pState + 1;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* Processing is complete.         
   ** Now copy the last phaseLen - 1 samples to the start of the state buffer.       
   ** This prepares the state buffer for the next function call. */

  /* Points to the start of the state buffer */
  pStateCurnt = S->pState;

  tapCnt = phaseLen - 1u;

  while(tapCnt > 0u)
  {
    *pStateCurnt++ = *pState++;

    /* Decrement the loop counter */
    tapCnt--;
  }

}

#endif /*   #ifndef ARM_MATH_CM0_FAMILY */



 /**    
  * @} end of FIR_Interpolate group    
  */
