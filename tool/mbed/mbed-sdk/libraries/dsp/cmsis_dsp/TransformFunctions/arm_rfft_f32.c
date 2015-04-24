/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013  
* $Revision: 	V1.4.1  
*    
* Project: 	    CMSIS DSP Library    
* Title:	    arm_rfft_f32.c    
*    
* Description:	RFFT & RIFFT Floating point process function    
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

extern void arm_radix4_butterfly_f32(
    float32_t * pSrc,
    uint16_t fftLen,
    float32_t * pCoef,
    uint16_t twidCoefModifier);

extern void arm_radix4_butterfly_inverse_f32(
    float32_t * pSrc,
    uint16_t fftLen,
    float32_t * pCoef,
    uint16_t twidCoefModifier,
    float32_t onebyfftLen);

extern void arm_bitreversal_f32(
    float32_t * pSrc,
    uint16_t fftSize,
    uint16_t bitRevFactor,
    uint16_t * pBitRevTab);

/**    
 * @ingroup groupTransforms    
 */

/*--------------------------------------------------------------------    
 *		Internal functions prototypes    
 *--------------------------------------------------------------------*/

void arm_split_rfft_f32(
  float32_t * pSrc,
  uint32_t fftLen,
  float32_t * pATable,
  float32_t * pBTable,
  float32_t * pDst,
  uint32_t modifier);
void arm_split_rifft_f32(
  float32_t * pSrc,
  uint32_t fftLen,
  float32_t * pATable,
  float32_t * pBTable,
  float32_t * pDst,
  uint32_t modifier);

/**    
 * @addtogroup RealFFT    
 * @{    
 */

/**    
 * @brief Processing function for the floating-point RFFT/RIFFT.   
 * @deprecated Do not use this function.  It has been superceded by \ref arm_rfft_fast_f32 and will be removed
 * in the future.
 * @param[in]  *S    points to an instance of the floating-point RFFT/RIFFT structure.   
 * @param[in]  *pSrc points to the input buffer.   
 * @param[out] *pDst points to the output buffer.   
 * @return none.   
 */

void arm_rfft_f32(
  const arm_rfft_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst)
{
  const arm_cfft_radix4_instance_f32 *S_CFFT = S->pCfft;


  /* Calculation of Real IFFT of input */
  if(S->ifftFlagR == 1u)
  {
    /*  Real IFFT core process */
    arm_split_rifft_f32(pSrc, S->fftLenBy2, S->pTwiddleAReal,
                        S->pTwiddleBReal, pDst, S->twidCoefRModifier);


    /* Complex radix-4 IFFT process */
    arm_radix4_butterfly_inverse_f32(pDst, S_CFFT->fftLen,
                                     S_CFFT->pTwiddle,
                                     S_CFFT->twidCoefModifier,
                                     S_CFFT->onebyfftLen);

    /* Bit reversal process */
    if(S->bitReverseFlagR == 1u)
    {
      arm_bitreversal_f32(pDst, S_CFFT->fftLen,
                          S_CFFT->bitRevFactor, S_CFFT->pBitRevTable);
    }
  }
  else
  {

    /* Calculation of RFFT of input */

    /* Complex radix-4 FFT process */
    arm_radix4_butterfly_f32(pSrc, S_CFFT->fftLen,
                             S_CFFT->pTwiddle, S_CFFT->twidCoefModifier);

    /* Bit reversal process */
    if(S->bitReverseFlagR == 1u)
    {
      arm_bitreversal_f32(pSrc, S_CFFT->fftLen,
                          S_CFFT->bitRevFactor, S_CFFT->pBitRevTable);
    }


    /*  Real FFT core process */
    arm_split_rfft_f32(pSrc, S->fftLenBy2, S->pTwiddleAReal,
                       S->pTwiddleBReal, pDst, S->twidCoefRModifier);
  }

}

/**    
   * @} end of RealFFT group    
   */

/**    
 * @brief  Core Real FFT process    
 * @param[in]   *pSrc 				points to the input buffer.    
 * @param[in]   fftLen  			length of FFT.    
 * @param[in]   *pATable 			points to the twiddle Coef A buffer.    
 * @param[in]   *pBTable 			points to the twiddle Coef B buffer.    
 * @param[out]  *pDst 				points to the output buffer.    
 * @param[in]   modifier 	        twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table.   
 * @return none.    
 */

void arm_split_rfft_f32(
  float32_t * pSrc,
  uint32_t fftLen,
  float32_t * pATable,
  float32_t * pBTable,
  float32_t * pDst,
  uint32_t modifier)
{
  uint32_t i;                                    /* Loop Counter */
  float32_t outR, outI;                          /* Temporary variables for output */
  float32_t *pCoefA, *pCoefB;                    /* Temporary pointers for twiddle factors */
  float32_t CoefA1, CoefA2, CoefB1;              /* Temporary variables for twiddle coefficients */
  float32_t *pDst1 = &pDst[2], *pDst2 = &pDst[(4u * fftLen) - 1u];      /* temp pointers for output buffer */
  float32_t *pSrc1 = &pSrc[2], *pSrc2 = &pSrc[(2u * fftLen) - 1u];      /* temp pointers for input buffer */

  /* Init coefficient pointers */
  pCoefA = &pATable[modifier * 2u];
  pCoefB = &pBTable[modifier * 2u];

  i = fftLen - 1u;

  while(i > 0u)
  {
    /*    
       outR = (pSrc[2 * i] * pATable[2 * i] - pSrc[2 * i + 1] * pATable[2 * i + 1]    
       + pSrc[2 * n - 2 * i] * pBTable[2 * i] +    
       pSrc[2 * n - 2 * i + 1] * pBTable[2 * i + 1]);    
     */

    /* outI = (pIn[2 * i + 1] * pATable[2 * i] + pIn[2 * i] * pATable[2 * i + 1] +    
       pIn[2 * n - 2 * i] * pBTable[2 * i + 1] -    
       pIn[2 * n - 2 * i + 1] * pBTable[2 * i]); */

    /* read pATable[2 * i] */
    CoefA1 = *pCoefA++;
    /* pATable[2 * i + 1] */
    CoefA2 = *pCoefA;

    /* pSrc[2 * i] * pATable[2 * i] */
    outR = *pSrc1 * CoefA1;
    /* pSrc[2 * i] * CoefA2 */
    outI = *pSrc1++ * CoefA2;

    /* (pSrc[2 * i + 1] + pSrc[2 * fftLen - 2 * i + 1]) * CoefA2 */
    outR -= (*pSrc1 + *pSrc2) * CoefA2;
    /* pSrc[2 * i + 1] * CoefA1 */
    outI += *pSrc1++ * CoefA1;

    CoefB1 = *pCoefB;

    /* pSrc[2 * fftLen - 2 * i + 1] * CoefB1 */
    outI -= *pSrc2-- * CoefB1;
    /* pSrc[2 * fftLen - 2 * i] * CoefA2 */
    outI -= *pSrc2 * CoefA2;

    /* pSrc[2 * fftLen - 2 * i] * CoefB1 */
    outR += *pSrc2-- * CoefB1;

    /* write output */
    *pDst1++ = outR;
    *pDst1++ = outI;

    /* write complex conjugate output */
    *pDst2-- = -outI;
    *pDst2-- = outR;

    /* update coefficient pointer */
    pCoefB = pCoefB + (modifier * 2u);
    pCoefA = pCoefA + ((modifier * 2u) - 1u);

    i--;

  }

  pDst[2u * fftLen] = pSrc[0] - pSrc[1];
  pDst[(2u * fftLen) + 1u] = 0.0f;

  pDst[0] = pSrc[0] + pSrc[1];
  pDst[1] = 0.0f;

}


/**    
 * @brief  Core Real IFFT process    
 * @param[in]   *pSrc 				points to the input buffer.    
 * @param[in]   fftLen  			length of FFT.   
 * @param[in]   *pATable 			points to the twiddle Coef A buffer.   
 * @param[in]   *pBTable 			points to the twiddle Coef B buffer.   
 * @param[out]  *pDst 				points to the output buffer.   
 * @param[in]   modifier 	        twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table.    
 * @return none.    
 */

void arm_split_rifft_f32(
  float32_t * pSrc,
  uint32_t fftLen,
  float32_t * pATable,
  float32_t * pBTable,
  float32_t * pDst,
  uint32_t modifier)
{
  float32_t outR, outI;                          /* Temporary variables for output */
  float32_t *pCoefA, *pCoefB;                    /* Temporary pointers for twiddle factors */
  float32_t CoefA1, CoefA2, CoefB1;              /* Temporary variables for twiddle coefficients */
  float32_t *pSrc1 = &pSrc[0], *pSrc2 = &pSrc[(2u * fftLen) + 1u];

  pCoefA = &pATable[0];
  pCoefB = &pBTable[0];

  while(fftLen > 0u)
  {
    /*    
       outR = (pIn[2 * i] * pATable[2 * i] + pIn[2 * i + 1] * pATable[2 * i + 1] +    
       pIn[2 * n - 2 * i] * pBTable[2 * i] -    
       pIn[2 * n - 2 * i + 1] * pBTable[2 * i + 1]);    

       outI = (pIn[2 * i + 1] * pATable[2 * i] - pIn[2 * i] * pATable[2 * i + 1] -    
       pIn[2 * n - 2 * i] * pBTable[2 * i + 1] -    
       pIn[2 * n - 2 * i + 1] * pBTable[2 * i]);    

     */

    CoefA1 = *pCoefA++;
    CoefA2 = *pCoefA;

    /* outR = (pSrc[2 * i] * CoefA1 */
    outR = *pSrc1 * CoefA1;

    /* - pSrc[2 * i] * CoefA2 */
    outI = -(*pSrc1++) * CoefA2;

    /* (pSrc[2 * i + 1] + pSrc[2 * fftLen - 2 * i + 1]) * CoefA2 */
    outR += (*pSrc1 + *pSrc2) * CoefA2;

    /* pSrc[2 * i + 1] * CoefA1 */
    outI += (*pSrc1++) * CoefA1;

    CoefB1 = *pCoefB;

    /* - pSrc[2 * fftLen - 2 * i + 1] * CoefB1 */
    outI -= *pSrc2-- * CoefB1;

    /* pSrc[2 * fftLen - 2 * i] * CoefB1 */
    outR += *pSrc2 * CoefB1;

    /* pSrc[2 * fftLen - 2 * i] * CoefA2 */
    outI += *pSrc2-- * CoefA2;

    /* write output */
    *pDst++ = outR;
    *pDst++ = outI;

    /* update coefficient pointer */
    pCoefB = pCoefB + (modifier * 2u);
    pCoefA = pCoefA + ((modifier * 2u) - 1u);

    /* Decrement loop count */
    fftLen--;
  }

}
