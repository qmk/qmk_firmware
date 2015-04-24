/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:        arm_fir_q7.c    
*    
* Description:  Q7 FIR filter processing function.    
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
 * @addtogroup FIR    
 * @{    
 */

/**    
 * @param[in]   *S points to an instance of the Q7 FIR filter structure.    
 * @param[in]   *pSrc points to the block of input data.    
 * @param[out]  *pDst points to the block of output data.    
 * @param[in]   blockSize number of samples to process per call.    
 * @return 	none.    
 *    
 * <b>Scaling and Overflow Behavior:</b>    
 * \par    
 * The function is implemented using a 32-bit internal accumulator.    
 * Both coefficients and state variables are represented in 1.7 format and multiplications yield a 2.14 result.    
 * The 2.14 intermediate results are accumulated in a 32-bit accumulator in 18.14 format.    
 * There is no risk of internal overflow with this approach and the full precision of intermediate multiplications is preserved.    
 * The accumulator is converted to 18.7 format by discarding the low 7 bits.    
 * Finally, the result is truncated to 1.7 format.    
 */

void arm_fir_q7(
  const arm_fir_instance_q7 * S,
  q7_t * pSrc,
  q7_t * pDst,
  uint32_t blockSize)
{

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */

  q7_t *pState = S->pState;                      /* State pointer */
  q7_t *pCoeffs = S->pCoeffs;                    /* Coefficient pointer */
  q7_t *pStateCurnt;                             /* Points to the current sample of the state */
  q7_t x0, x1, x2, x3;                           /* Temporary variables to hold state */
  q7_t c0;                                       /* Temporary variable to hold coefficient value */
  q7_t *px;                                      /* Temporary pointer for state */
  q7_t *pb;                                      /* Temporary pointer for coefficient buffer */
  q31_t acc0, acc1, acc2, acc3;                  /* Accumulators */
  uint32_t numTaps = S->numTaps;                 /* Number of filter coefficients in the filter */
  uint32_t i, tapCnt, blkCnt;                    /* Loop counters */

  /* S->pState points to state array which contains previous frame (numTaps - 1) samples */
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
      acc0 += ((q15_t) x0 * c0);

      /* acc1 +=  b[numTaps] * x[n-numTaps-1] */
      acc1 += ((q15_t) x1 * c0);

      /* acc2 +=  b[numTaps] * x[n-numTaps-2] */
      acc2 += ((q15_t) x2 * c0);

      /* acc3 +=  b[numTaps] * x[n-numTaps-3] */
      acc3 += ((q15_t) x3 * c0);

      /* Read the b[numTaps-1] coefficient */
      c0 = *(pb++);

      /* Read x[n-numTaps-4] sample */
      x0 = *(px++);

      /* Perform the multiply-accumulates */
      acc0 += ((q15_t) x1 * c0);
      acc1 += ((q15_t) x2 * c0);
      acc2 += ((q15_t) x3 * c0);
      acc3 += ((q15_t) x0 * c0);

      /* Read the b[numTaps-2] coefficient */
      c0 = *(pb++);

      /* Read x[n-numTaps-5] sample */
      x1 = *(px++);

      /* Perform the multiply-accumulates */
      acc0 += ((q15_t) x2 * c0);
      acc1 += ((q15_t) x3 * c0);
      acc2 += ((q15_t) x0 * c0);
      acc3 += ((q15_t) x1 * c0);
      /* Read the b[numTaps-3] coefficients */
      c0 = *(pb++);

      /* Read x[n-numTaps-6] sample */
      x2 = *(px++);

      /* Perform the multiply-accumulates */
      acc0 += ((q15_t) x3 * c0);
      acc1 += ((q15_t) x0 * c0);
      acc2 += ((q15_t) x1 * c0);
      acc3 += ((q15_t) x2 * c0);
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
      acc0 += ((q15_t) x0 * c0);
      acc1 += ((q15_t) x1 * c0);
      acc2 += ((q15_t) x2 * c0);
      acc3 += ((q15_t) x3 * c0);

      /* Reuse the present sample states for next sample */
      x0 = x1;
      x1 = x2;
      x2 = x3;

      /* Decrement the loop counter */
      i--;
    }

    /* Advance the state pointer by 4 to process the next group of 4 samples */
    pState = pState + 4;

    /* The results in the 4 accumulators are in 2.62 format.  Convert to 1.31    
     ** Then store the 4 outputs in the destination buffer. */
    acc0 = __SSAT((acc0 >> 7u), 8);
    *pDst++ = acc0;
    acc1 = __SSAT((acc1 >> 7u), 8);
    *pDst++ = acc1;
    acc2 = __SSAT((acc2 >> 7u), 8);
    *pDst++ = acc2;
    acc3 = __SSAT((acc3 >> 7u), 8);
    *pDst++ = acc3;

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
      acc0 += (q15_t) * (px++) * (*(pb++));
      i--;
    } while(i > 0u);

    /* The result is in 2.14 format.  Convert to 1.7    
     ** Then store the output in the destination buffer. */
    *pDst++ = __SSAT((acc0 >> 7u), 8);

    /* Advance state pointer by 1 for the next sample */
    pState = pState + 1;

    /* Decrement the samples loop counter */
    blkCnt--;
  }

  /* Processing is complete.    
   ** Now copy the last numTaps - 1 samples to the satrt of the state buffer.    
   ** This prepares the state buffer for the next function call. */

  /* Points to the start of the state buffer */
  pStateCurnt = S->pState;

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

  uint32_t numTaps = S->numTaps;                 /* Number of taps in the filter */
  uint32_t i, blkCnt;                            /* Loop counters */
  q7_t *pState = S->pState;                      /* State pointer */
  q7_t *pCoeffs = S->pCoeffs;                    /* Coefficient pointer */
  q7_t *px, *pb;                                 /* Temporary pointers to state and coeff */
  q31_t acc = 0;                                 /* Accumlator */
  q7_t *pStateCurnt;                             /* Points to the current sample of the state */


  /* S->pState points to state array which contains previous frame (numTaps - 1) samples */
  /* pStateCurnt points to the location where the new input data should be written */
  pStateCurnt = S->pState + (numTaps - 1u);

  /* Initialize blkCnt with blockSize */
  blkCnt = blockSize;

  /* Perform filtering upto BlockSize - BlockSize%4  */
  while(blkCnt > 0u)
  {
    /* Copy one sample at a time into state buffer */
    *pStateCurnt++ = *pSrc++;

    /* Set accumulator to zero */
    acc = 0;

    /* Initialize state pointer of type q7 */
    px = pState;

    /* Initialize coeff pointer of type q7 */
    pb = pCoeffs;


    i = numTaps;

    while(i > 0u)
    {
      /* acc =  b[numTaps-1] * x[n-numTaps-1] + b[numTaps-2] * x[n-numTaps-2] + b[numTaps-3] * x[n-numTaps-3] +...+ b[0] * x[0] */
      acc += (q15_t) * px++ * *pb++;
      i--;
    }

    /* Store the 1.7 format filter output in destination buffer */
    *pDst++ = (q7_t) __SSAT((acc >> 7), 8);

    /* Advance the state pointer by 1 to process the next sample */
    pState = pState + 1;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* Processing is complete.         
   ** Now copy the last numTaps - 1 samples to the satrt of the state buffer.       
   ** This prepares the state buffer for the next function call. */


  /* Points to the start of the state buffer */
  pStateCurnt = S->pState;


  /* Copy numTaps number of values */
  i = (numTaps - 1u);

  /* Copy q7_t data */
  while(i > 0u)
  {
    *pStateCurnt++ = *pState++;
    i--;
  }

#endif /*   #ifndef ARM_MATH_CM0_FAMILY */

}

/**    
 * @} end of FIR group    
 */
