/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:	    arm_fir_lattice_q31.c    
*    
* Description:	Q31 FIR lattice filter processing function.    
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
 * @addtogroup FIR_Lattice    
 * @{    
 */


/**    
 * @brief Processing function for the Q31 FIR lattice filter.    
 * @param[in]  *S        points to an instance of the Q31 FIR lattice structure.    
 * @param[in]  *pSrc     points to the block of input data.    
 * @param[out] *pDst     points to the block of output data    
 * @param[in]  blockSize number of samples to process.    
 * @return none.    
 *    
 * @details    
 * <b>Scaling and Overflow Behavior:</b>    
 * In order to avoid overflows the input signal must be scaled down by 2*log2(numStages) bits.    
 */

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */

void arm_fir_lattice_q31(
  const arm_fir_lattice_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize)
{
  q31_t *pState;                                 /* State pointer */
  q31_t *pCoeffs = S->pCoeffs;                   /* Coefficient pointer */
  q31_t *px;                                     /* temporary state pointer */
  q31_t *pk;                                     /* temporary coefficient pointer */
  q31_t fcurr1, fnext1, gcurr1 = 0, gnext1;      /* temporary variables for first sample in loop unrolling */
  q31_t fcurr2, fnext2, gnext2;                  /* temporary variables for second sample in loop unrolling */
  uint32_t numStages = S->numStages;             /* Length of the filter */
  uint32_t blkCnt, stageCnt;                     /* temporary variables for counts */
  q31_t k;

  pState = &S->pState[0];

  blkCnt = blockSize >> 1u;

  /* First part of the processing with loop unrolling.  Compute 2 outputs at a time.        
     a second loop below computes the remaining 1 sample. */
  while(blkCnt > 0u)
  {
    /* f0(n) = x(n) */
    fcurr1 = *pSrc++;

    /* f0(n) = x(n) */
    fcurr2 = *pSrc++;

    /* Initialize coeff pointer */
    pk = (pCoeffs);

    /* Initialize state pointer */
    px = pState;

    /* read g0(n - 1) from state buffer */
    gcurr1 = *px;

    /* Read the reflection coefficient */
    k = *pk++;

    /* for sample 1 processing */
    /* f1(n) = f0(n) +  K1 * g0(n-1) */
    fnext1 = (q31_t) (((q63_t) gcurr1 * k) >> 32);

    /* g1(n) = f0(n) * K1  +  g0(n-1) */
    gnext1 = (q31_t) (((q63_t) fcurr1 * (k)) >> 32);
    fnext1 = fcurr1 + (fnext1 << 1u);
    gnext1 = gcurr1 + (gnext1 << 1u);

    /* for sample 1 processing */
    /* f1(n) = f0(n) +  K1 * g0(n-1) */
    fnext2 = (q31_t) (((q63_t) fcurr1 * k) >> 32);

    /* g1(n) = f0(n) * K1  +  g0(n-1) */
    gnext2 = (q31_t) (((q63_t) fcurr2 * (k)) >> 32);
    fnext2 = fcurr2 + (fnext2 << 1u);
    gnext2 = fcurr1 + (gnext2 << 1u);

    /* save g1(n) in state buffer */
    *px++ = fcurr2;

    /* f1(n) is saved in fcurr1        
       for next stage processing */
    fcurr1 = fnext1;
    fcurr2 = fnext2;

    stageCnt = (numStages - 1u);

    /* stage loop */
    while(stageCnt > 0u)
    {

      /* Read the reflection coefficient */
      k = *pk++;

      /* read g2(n) from state buffer */
      gcurr1 = *px;

      /* save g1(n) in state buffer */
      *px++ = gnext2;

      /* Sample processing for K2, K3.... */
      /* f2(n) = f1(n) +  K2 * g1(n-1) */
      fnext1 = (q31_t) (((q63_t) gcurr1 * k) >> 32);
      fnext2 = (q31_t) (((q63_t) gnext1 * k) >> 32);

      fnext1 = fcurr1 + (fnext1 << 1u);
      fnext2 = fcurr2 + (fnext2 << 1u);

      /* g2(n) = f1(n) * K2  +  g1(n-1) */
      gnext2 = (q31_t) (((q63_t) fcurr2 * (k)) >> 32);
      gnext2 = gnext1 + (gnext2 << 1u);

      /* g2(n) = f1(n) * K2  +  g1(n-1) */
      gnext1 = (q31_t) (((q63_t) fcurr1 * (k)) >> 32);
      gnext1 = gcurr1 + (gnext1 << 1u);

      /* f1(n) is saved in fcurr1        
         for next stage processing */
      fcurr1 = fnext1;
      fcurr2 = fnext2;

      stageCnt--;

    }

    /* y(n) = fN(n) */
    *pDst++ = fcurr1;
    *pDst++ = fcurr2;

    blkCnt--;

  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.        
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x2u;

  while(blkCnt > 0u)
  {
    /* f0(n) = x(n) */
    fcurr1 = *pSrc++;

    /* Initialize coeff pointer */
    pk = (pCoeffs);

    /* Initialize state pointer */
    px = pState;

    /* read g0(n - 1) from state buffer */
    gcurr1 = *px;

    /* Read the reflection coefficient */
    k = *pk++;

    /* for sample 1 processing */
    /* f1(n) = f0(n) +  K1 * g0(n-1) */
    fnext1 = (q31_t) (((q63_t) gcurr1 * k) >> 32);
    fnext1 = fcurr1 + (fnext1 << 1u);

    /* g1(n) = f0(n) * K1  +  g0(n-1) */
    gnext1 = (q31_t) (((q63_t) fcurr1 * (k)) >> 32);
    gnext1 = gcurr1 + (gnext1 << 1u);

    /* save g1(n) in state buffer */
    *px++ = fcurr1;

    /* f1(n) is saved in fcurr1        
       for next stage processing */
    fcurr1 = fnext1;

    stageCnt = (numStages - 1u);

    /* stage loop */
    while(stageCnt > 0u)
    {
      /* Read the reflection coefficient */
      k = *pk++;

      /* read g2(n) from state buffer */
      gcurr1 = *px;

      /* save g1(n) in state buffer */
      *px++ = gnext1;

      /* Sample processing for K2, K3.... */
      /* f2(n) = f1(n) +  K2 * g1(n-1) */
      fnext1 = (q31_t) (((q63_t) gcurr1 * k) >> 32);
      fnext1 = fcurr1 + (fnext1 << 1u);

      /* g2(n) = f1(n) * K2  +  g1(n-1) */
      gnext1 = (q31_t) (((q63_t) fcurr1 * (k)) >> 32);
      gnext1 = gcurr1 + (gnext1 << 1u);

      /* f1(n) is saved in fcurr1        
         for next stage processing */
      fcurr1 = fnext1;

      stageCnt--;

    }


    /* y(n) = fN(n) */
    *pDst++ = fcurr1;

    blkCnt--;

  }


}


#else

/* Run the below code for Cortex-M0 */

void arm_fir_lattice_q31(
  const arm_fir_lattice_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize)
{
  q31_t *pState;                                 /* State pointer */
  q31_t *pCoeffs = S->pCoeffs;                   /* Coefficient pointer */
  q31_t *px;                                     /* temporary state pointer */
  q31_t *pk;                                     /* temporary coefficient pointer */
  q31_t fcurr, fnext, gcurr, gnext;              /* temporary variables */
  uint32_t numStages = S->numStages;             /* Length of the filter */
  uint32_t blkCnt, stageCnt;                     /* temporary variables for counts */

  pState = &S->pState[0];

  blkCnt = blockSize;

  while(blkCnt > 0u)
  {
    /* f0(n) = x(n) */
    fcurr = *pSrc++;

    /* Initialize coeff pointer */
    pk = (pCoeffs);

    /* Initialize state pointer */
    px = pState;

    /* read g0(n-1) from state buffer */
    gcurr = *px;

    /* for sample 1 processing */
    /* f1(n) = f0(n) +  K1 * g0(n-1) */
    fnext = (q31_t) (((q63_t) gcurr * (*pk)) >> 31) + fcurr;
    /* g1(n) = f0(n) * K1  +  g0(n-1) */
    gnext = (q31_t) (((q63_t) fcurr * (*pk++)) >> 31) + gcurr;
    /* save g1(n) in state buffer */
    *px++ = fcurr;

    /* f1(n) is saved in fcurr1            
       for next stage processing */
    fcurr = fnext;

    stageCnt = (numStages - 1u);

    /* stage loop */
    while(stageCnt > 0u)
    {
      /* read g2(n) from state buffer */
      gcurr = *px;

      /* save g1(n) in state buffer */
      *px++ = gnext;

      /* Sample processing for K2, K3.... */
      /* f2(n) = f1(n) +  K2 * g1(n-1) */
      fnext = (q31_t) (((q63_t) gcurr * (*pk)) >> 31) + fcurr;
      /* g2(n) = f1(n) * K2  +  g1(n-1) */
      gnext = (q31_t) (((q63_t) fcurr * (*pk++)) >> 31) + gcurr;

      /* f1(n) is saved in fcurr1            
         for next stage processing */
      fcurr = fnext;

      stageCnt--;

    }

    /* y(n) = fN(n) */
    *pDst++ = fcurr;

    blkCnt--;

  }

}

#endif /*   #ifndef ARM_MATH_CM0_FAMILY */


/**    
 * @} end of FIR_Lattice group    
 */
