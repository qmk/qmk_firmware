/*-----------------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:        arm_fir_lattice_init_q31.c    
*    
* Description:  Q31 FIR lattice filter initialization function.    
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
* ---------------------------------------------------------------------------*/

#include "arm_math.h"

/**    
 * @ingroup groupFilters    
 */

/**    
 * @addtogroup FIR_Lattice    
 * @{    
 */

  /**    
   * @brief Initialization function for the Q31 FIR lattice filter.    
   * @param[in] *S points to an instance of the Q31 FIR lattice structure.    
   * @param[in] numStages  number of filter stages.    
   * @param[in] *pCoeffs points to the coefficient buffer.  The array is of length numStages.    
   * @param[in] *pState points to the state buffer.   The array is of length numStages.    
   * @return none.    
   */

void arm_fir_lattice_init_q31(
  arm_fir_lattice_instance_q31 * S,
  uint16_t numStages,
  q31_t * pCoeffs,
  q31_t * pState)
{
  /* Assign filter taps */
  S->numStages = numStages;

  /* Assign coefficient pointer */
  S->pCoeffs = pCoeffs;

  /* Clear state buffer and size is always numStages */
  memset(pState, 0, (numStages) * sizeof(q31_t));

  /* Assign state pointer */
  S->pState = pState;

}

/**    
 * @} end of FIR_Lattice group    
 */
