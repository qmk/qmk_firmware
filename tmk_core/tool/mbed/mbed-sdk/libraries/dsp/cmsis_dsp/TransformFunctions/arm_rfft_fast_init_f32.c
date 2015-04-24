/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013  
* $Revision: 	V1.4.1  
*    
* Project: 	    CMSIS DSP Library    
* Title:	    arm_cfft_init_f32.c   
*    
* Description:	Split Radix Decimation in Frequency CFFT Floating point processing function   
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
#include "arm_common_tables.h"

/**   
 * @ingroup groupTransforms   
 */

/**   
 * @addtogroup RealFFT   
 * @{   
 */

/**   
* @brief  Initialization function for the floating-point real FFT.  
* @param[in,out] *S             points to an arm_rfft_fast_instance_f32 structure.
* @param[in]     fftLen         length of the Real Sequence.  
* @return        The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_ARGUMENT_ERROR if <code>fftLen</code> is not a supported value.  
*   
* \par Description:  
* \par   
* The parameter <code>ifftFlag</code> controls whether a forward or inverse transform is computed.   
* Set(=1) ifftFlag for calculation of CIFFT otherwise  RFFT is calculated  
* \par   
* The parameter <code>bitReverseFlag</code> controls whether output is in normal order or bit reversed order.   
* Set(=1) bitReverseFlag for output to be in normal order otherwise output is in bit reversed order.   
* \par   
* The parameter <code>fftLen</code>	Specifies length of RFFT/CIFFT process. Supported FFT Lengths are 16, 32, 64, 128, 256, 512, 1024, 2048, 4096.   
* \par   
* This Function also initializes Twiddle factor table pointer and Bit reversal table pointer.   
*/
arm_status arm_rfft_fast_init_f32(
  arm_rfft_fast_instance_f32 * S,
  uint16_t fftLen)
{
  arm_cfft_instance_f32 * Sint;
  /*  Initialise the default arm status */
  arm_status status = ARM_MATH_SUCCESS;
  /*  Initialise the FFT length */
  Sint = &(S->Sint);
  Sint->fftLen = fftLen/2;
  S->fftLenRFFT = fftLen;
  /*  Initialise the Twiddle coefficient pointer */
  //  S->pTwiddle = (float32_t *) twiddleCoef;

  /*  Initializations of structure parameters depending on the FFT length */
  switch (Sint->fftLen)
  {
  case 4096u:
    /*  Initializations of structure parameters for 4096 point FFT */
    /*  Initialise the bit reversal table length */
    Sint->bitRevLength = ARMBITREVINDEXTABLE4096_TABLE_LENGTH;
    /*  Initialise the bit reversal table pointer */
    Sint->pBitRevTable = (uint16_t *)armBitRevIndexTable4096;
    /*  Initialise the 1/fftLen Value */
    break;
  case 2048u:
    Sint->bitRevLength = ARMBITREVINDEXTABLE2048_TABLE_LENGTH;
    Sint->pBitRevTable = (uint16_t *)armBitRevIndexTable2048;
    break;
  case 1024u:
    Sint->bitRevLength = ARMBITREVINDEXTABLE1024_TABLE_LENGTH;
    Sint->pBitRevTable = (uint16_t *)armBitRevIndexTable1024;
    break;
  case 512u:
    Sint->bitRevLength = ARMBITREVINDEXTABLE_512_TABLE_LENGTH;
    Sint->pBitRevTable = (uint16_t *)armBitRevIndexTable512;
    break;
  case 256u:
    Sint->bitRevLength = ARMBITREVINDEXTABLE_256_TABLE_LENGTH;
    Sint->pBitRevTable = (uint16_t *)armBitRevIndexTable256;
    break;
  case 128u:
    Sint->bitRevLength = ARMBITREVINDEXTABLE_128_TABLE_LENGTH;
    Sint->pBitRevTable = (uint16_t *)armBitRevIndexTable128;
    break;
  case 64u:
    Sint->bitRevLength = ARMBITREVINDEXTABLE__64_TABLE_LENGTH;
    Sint->pBitRevTable = (uint16_t *)armBitRevIndexTable64;
    break;
  case 32u:
    Sint->bitRevLength = ARMBITREVINDEXTABLE__32_TABLE_LENGTH;
    Sint->pBitRevTable = (uint16_t *)armBitRevIndexTable32;
    break;
  case 16u:
    Sint->bitRevLength = ARMBITREVINDEXTABLE__16_TABLE_LENGTH;
    Sint->pBitRevTable = (uint16_t *)armBitRevIndexTable16;
    break;
  default:
    /*  Reporting argument error if fftSize is not valid value */
    status = ARM_MATH_ARGUMENT_ERROR;
    break;
  }

  return (status);
}

/**   
 * @} end of RealFFT group   
 */
