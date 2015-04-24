/* ----------------------------------------------------------------------   
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.   
*   
* $Date:        17. January 2013  
* $Revision: 	V1.4.1  
*   
* Project: 	    CMSIS DSP Library   
* Title:	    arm_cfft_radix2_f32.c   
*   
* Description:	Radix-2 Decimation in Frequency CFFT & CIFFT Floating point processing function   
*   
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

void arm_radix2_butterfly_f32(
  float32_t * pSrc,
  uint32_t fftLen,
  float32_t * pCoef,
  uint16_t twidCoefModifier);

void arm_radix2_butterfly_inverse_f32(
  float32_t * pSrc,
  uint32_t fftLen,
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

/**   
* @addtogroup ComplexFFT   
* @{   
*/

/**   
* @details
* @brief Radix-2 CFFT/CIFFT.
* @deprecated Do not use this function.  It has been superceded by \ref arm_cfft_f32 and will be removed
* in the future.
* @param[in]      *S    points to an instance of the floating-point Radix-2 CFFT/CIFFT structure.  
* @param[in, out] *pSrc points to the complex data buffer of size <code>2*fftLen</code>. Processing occurs in-place.  
* @return none.
*/

void arm_cfft_radix2_f32(
const arm_cfft_radix2_instance_f32 * S,
float32_t * pSrc)
{

   if(S->ifftFlag == 1u)
   {
      /*  Complex IFFT radix-2  */
      arm_radix2_butterfly_inverse_f32(pSrc, S->fftLen, S->pTwiddle,
      S->twidCoefModifier, S->onebyfftLen);
   }
   else
   {
      /*  Complex FFT radix-2  */
      arm_radix2_butterfly_f32(pSrc, S->fftLen, S->pTwiddle,
      S->twidCoefModifier);
   }

   if(S->bitReverseFlag == 1u)
   {
      /*  Bit Reversal */
      arm_bitreversal_f32(pSrc, S->fftLen, S->bitRevFactor, S->pBitRevTable);
   }

}


/**    
* @} end of ComplexFFT group    
*/



/* ----------------------------------------------------------------------    
** Internal helper function used by the FFTs    
** ------------------------------------------------------------------- */

/*    
* @brief  Core function for the floating-point CFFT butterfly process.   
* @param[in, out] *pSrc            points to the in-place buffer of floating-point data type.   
* @param[in]      fftLen           length of the FFT.   
* @param[in]      *pCoef           points to the twiddle coefficient buffer.   
* @param[in]      twidCoefModifier twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table.   
* @return none.   
*/

void arm_radix2_butterfly_f32(
float32_t * pSrc,
uint32_t fftLen,
float32_t * pCoef,
uint16_t twidCoefModifier)
{

   uint32_t i, j, k, l;
   uint32_t n1, n2, ia;
   float32_t xt, yt, cosVal, sinVal;
   float32_t p0, p1, p2, p3;
   float32_t a0, a1;

#ifndef ARM_MATH_CM0_FAMILY

   /*  Initializations for the first stage */
   n2 = fftLen >> 1;
   ia = 0;
   i = 0;

   // loop for groups 
   for (k = n2; k > 0; k--)
   {
      cosVal = pCoef[ia * 2];
      sinVal = pCoef[(ia * 2) + 1];

      /*  Twiddle coefficients index modifier */
      ia += twidCoefModifier;

      /*  index calculation for the input as, */
      /*  pSrc[i + 0], pSrc[i + fftLen/1] */
      l = i + n2;

      /*  Butterfly implementation */
      a0 = pSrc[2 * i] + pSrc[2 * l];
      xt = pSrc[2 * i] - pSrc[2 * l];

      yt = pSrc[2 * i + 1] - pSrc[2 * l + 1];
      a1 = pSrc[2 * l + 1] + pSrc[2 * i + 1];
      
      p0 = xt * cosVal;
      p1 = yt * sinVal;
      p2 = yt * cosVal;
      p3 = xt * sinVal;  
      
      pSrc[2 * i]     = a0;   
      pSrc[2 * i + 1] = a1;       
      
      pSrc[2 * l]     = p0 + p1;
      pSrc[2 * l + 1] = p2 - p3;
      
      i++;
   }                             // groups loop end 

   twidCoefModifier <<= 1u;

   // loop for stage 
   for (k = n2; k > 2; k = k >> 1)
   {
      n1 = n2;
      n2 = n2 >> 1;
      ia = 0;

      // loop for groups 
      j = 0;
      do
      {
         cosVal = pCoef[ia * 2];
         sinVal = pCoef[(ia * 2) + 1];
         ia += twidCoefModifier;

         // loop for butterfly 
         i = j;
         do
         {
            l = i + n2;
            a0 = pSrc[2 * i] + pSrc[2 * l];
            xt = pSrc[2 * i] - pSrc[2 * l];

            yt = pSrc[2 * i + 1] - pSrc[2 * l + 1];
            a1 = pSrc[2 * l + 1] + pSrc[2 * i + 1];
            
            p0 = xt * cosVal;
            p1 = yt * sinVal;
            p2 = yt * cosVal;
            p3 = xt * sinVal;  
            
            pSrc[2 * i] = a0;   
            pSrc[2 * i + 1] = a1;       
            
            pSrc[2 * l]     = p0 + p1;
            pSrc[2 * l + 1] = p2 - p3;
            
            i += n1;
         } while( i < fftLen );                        // butterfly loop end 
         j++;
      } while( j < n2);                          // groups loop end 
      twidCoefModifier <<= 1u;
   }                             // stages loop end 

   // loop for butterfly 
   for (i = 0; i < fftLen; i += 2)
   {
      a0 = pSrc[2 * i] + pSrc[2 * i + 2];
      xt = pSrc[2 * i] - pSrc[2 * i + 2];

      yt = pSrc[2 * i + 1] - pSrc[2 * i + 3];
      a1 = pSrc[2 * i + 3] + pSrc[2 * i + 1];
      
      pSrc[2 * i] = a0;   
      pSrc[2 * i + 1] = a1;
      pSrc[2 * i + 2] = xt;
      pSrc[2 * i + 3] = yt;
   }                             // groups loop end 

#else
 
   n2 = fftLen;

   // loop for stage 
   for (k = fftLen; k > 1; k = k >> 1)
   {
      n1 = n2;
      n2 = n2 >> 1;
      ia = 0;

      // loop for groups 
      j = 0;
      do
      {
         cosVal = pCoef[ia * 2];
         sinVal = pCoef[(ia * 2) + 1];
         ia += twidCoefModifier;

         // loop for butterfly 
         i = j;
         do
         {
            l = i + n2;
            a0 = pSrc[2 * i] + pSrc[2 * l];
            xt = pSrc[2 * i] - pSrc[2 * l];

            yt = pSrc[2 * i + 1] - pSrc[2 * l + 1];
            a1 = pSrc[2 * l + 1] + pSrc[2 * i + 1];
            
            p0 = xt * cosVal;
            p1 = yt * sinVal;
            p2 = yt * cosVal;
            p3 = xt * sinVal;  
            
            pSrc[2 * i] = a0;   
            pSrc[2 * i + 1] = a1;       
            
            pSrc[2 * l]     = p0 + p1;
            pSrc[2 * l + 1] = p2 - p3;
            
            i += n1;
         } while(i < fftLen);
         j++;
      } while(j < n2);
      twidCoefModifier <<= 1u;
   }

#endif //    #ifndef ARM_MATH_CM0_FAMILY

}


void arm_radix2_butterfly_inverse_f32(
float32_t * pSrc,
uint32_t fftLen,
float32_t * pCoef,
uint16_t twidCoefModifier,
float32_t onebyfftLen)
{

   uint32_t i, j, k, l;
   uint32_t n1, n2, ia;
   float32_t xt, yt, cosVal, sinVal;
   float32_t p0, p1, p2, p3;
   float32_t a0, a1;

#ifndef ARM_MATH_CM0_FAMILY

   n2 = fftLen >> 1;
   ia = 0;

   // loop for groups 
   for (i = 0; i < n2; i++)
   {
      cosVal = pCoef[ia * 2];
      sinVal = pCoef[(ia * 2) + 1];
      ia += twidCoefModifier;

      l = i + n2;
      a0 = pSrc[2 * i] + pSrc[2 * l];
      xt = pSrc[2 * i] - pSrc[2 * l];

      yt = pSrc[2 * i + 1] - pSrc[2 * l + 1];
      a1 = pSrc[2 * l + 1] + pSrc[2 * i + 1];
      
      p0 = xt * cosVal;
      p1 = yt * sinVal;
      p2 = yt * cosVal;
      p3 = xt * sinVal;  
      
      pSrc[2 * i] = a0;   
      pSrc[2 * i + 1] = a1;       
      
      pSrc[2 * l]     = p0 - p1;
      pSrc[2 * l + 1] = p2 + p3;  
   }                             // groups loop end 

   twidCoefModifier <<= 1u;

   // loop for stage 
   for (k = fftLen / 2; k > 2; k = k >> 1)
   {
      n1 = n2;
      n2 = n2 >> 1;
      ia = 0;

      // loop for groups 
      j = 0;
      do
      {
         cosVal = pCoef[ia * 2];
         sinVal = pCoef[(ia * 2) + 1];
         ia += twidCoefModifier;

         // loop for butterfly 
         i = j;
         do
         {
            l = i + n2;
            a0 = pSrc[2 * i] + pSrc[2 * l];
            xt = pSrc[2 * i] - pSrc[2 * l];

            yt = pSrc[2 * i + 1] - pSrc[2 * l + 1];
            a1 = pSrc[2 * l + 1] + pSrc[2 * i + 1];
            
            p0 = xt * cosVal;
            p1 = yt * sinVal;
            p2 = yt * cosVal;
            p3 = xt * sinVal;  
            
            pSrc[2 * i] = a0;   
            pSrc[2 * i + 1] = a1;       
            
            pSrc[2 * l]     = p0 - p1;
            pSrc[2 * l + 1] = p2 + p3; 

            i += n1;
         } while( i < fftLen );                 // butterfly loop end 
         j++;
      } while(j < n2);                      // groups loop end 

      twidCoefModifier <<= 1u;
   }                             // stages loop end 

   // loop for butterfly 
   for (i = 0; i < fftLen; i += 2)
   {   
      a0 = pSrc[2 * i] + pSrc[2 * i + 2];
      xt = pSrc[2 * i] - pSrc[2 * i + 2];
      
      a1 = pSrc[2 * i + 3] + pSrc[2 * i + 1];
      yt = pSrc[2 * i + 1] - pSrc[2 * i + 3];
      
      p0 = a0 * onebyfftLen;
      p2 = xt * onebyfftLen;
      p1 = a1 * onebyfftLen;
      p3 = yt * onebyfftLen; 
      
      pSrc[2 * i] = p0;
      pSrc[2 * i + 1] = p1;  
      pSrc[2 * i + 2] = p2;       
      pSrc[2 * i + 3] = p3;
   }                             // butterfly loop end 

#else

   n2 = fftLen;

   // loop for stage 
   for (k = fftLen; k > 2; k = k >> 1)
   {
      n1 = n2;
      n2 = n2 >> 1;
      ia = 0;

      // loop for groups 
      j = 0;
      do
      {
         cosVal = pCoef[ia * 2];
         sinVal = pCoef[(ia * 2) + 1];
         ia = ia + twidCoefModifier;

         // loop for butterfly 
         i = j;
         do
         {
            l = i + n2;
            a0 = pSrc[2 * i] + pSrc[2 * l];
            xt = pSrc[2 * i] - pSrc[2 * l];

            yt = pSrc[2 * i + 1] - pSrc[2 * l + 1];
            a1 = pSrc[2 * l + 1] + pSrc[2 * i + 1];
            
            p0 = xt * cosVal;
            p1 = yt * sinVal;
            p2 = yt * cosVal;
            p3 = xt * sinVal;  
            
            pSrc[2 * i] = a0;   
            pSrc[2 * i + 1] = a1;       
            
            pSrc[2 * l]     = p0 - p1;
            pSrc[2 * l + 1] = p2 + p3;  
            
            i += n1;
         } while( i < fftLen );                    // butterfly loop end 
         j++;
      } while( j < n2 );                      // groups loop end 

      twidCoefModifier = twidCoefModifier << 1u;
   }                             // stages loop end 

   n1 = n2;
   n2 = n2 >> 1;

   // loop for butterfly 
   for (i = 0; i < fftLen; i += n1)
   {
      l = i + n2;
      
      a0 = pSrc[2 * i] + pSrc[2 * l];
      xt = pSrc[2 * i] - pSrc[2 * l];
      
      a1 = pSrc[2 * l + 1] + pSrc[2 * i + 1];
      yt = pSrc[2 * i + 1] - pSrc[2 * l + 1];
      
      p0 = a0 * onebyfftLen;
      p2 = xt * onebyfftLen;
      p1 = a1 * onebyfftLen;
      p3 = yt * onebyfftLen; 
      
      pSrc[2 * i] = p0;
      pSrc[2u * l] = p2;
     
      pSrc[2 * i + 1] = p1;    
      pSrc[2u * l + 1u] = p3;
   }                             // butterfly loop end 

#endif //      #ifndef ARM_MATH_CM0_FAMILY

}
