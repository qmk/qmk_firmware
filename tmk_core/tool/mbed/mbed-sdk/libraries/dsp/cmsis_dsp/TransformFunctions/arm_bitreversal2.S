;/* ----------------------------------------------------------------------    
;* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
;*    
;* $Date:        17. January 2013  
;* $Revision: 	V1.4.1  
;*    
;* Project: 	    CMSIS DSP Library    
;* Title:	    arm_bitreversal2.S   
;*    
;* Description:	This is the arm_bitreversal_32 function done in
;*                assembly for maximum speed.  This function is called
;*                after doing an fft to reorder the output.  The function
;*                is loop unrolled by 2.
;*    
;* Target Processor: Cortex-M4/Cortex-M3/Cortex-M0
;*  
;* Redistribution and use in source and binary forms, with or without 
;* modification, are permitted provided that the following conditions
;* are met:
;*   - Redistributions of source code must retain the above copyright
;*     notice, this list of conditions and the following disclaimer.
;*   - Redistributions in binary form must reproduce the above copyright
;*     notice, this list of conditions and the following disclaimer in
;*     the documentation and/or other materials provided with the 
;*     distribution.
;*   - Neither the name of ARM LIMITED nor the names of its contributors
;*     may be used to endorse or promote products derived from this
;*     software without specific prior written permission.
;*
;* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
;* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
;* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
;* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
;* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
;* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
;* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
;* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
;* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
;* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
;* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;* POSSIBILITY OF SUCH DAMAGE.   
;* -------------------------------------------------------------------- */
#if defined(__CC_ARM) //Keil
	#define CODESECT AREA     ||.text||, CODE, READONLY, ALIGN=2
	#define LABEL
#elif defined(__IASMARM__) //IAR
	#define CODESECT SECTION `.text`:CODE
	#define PROC 
	#define LABEL 
	#define ENDP
	#define EXPORT PUBLIC
#elif defined (__GNUC__) //GCC
	.syntax unified
	.cpu cortex-m4
	.fpu softvfp
	#define THUMB .thumb
	#define CODESECT .section text
	#define EXPORT .global
	#define PROC :
	#define LABEL :
	#define ENDP
	#define END
#endif

	CODESECT
	THUMB

;/*    
;* @brief  In-place bit reversal function.   
;* @param[in, out] *pSrc        points to the in-place buffer of unknown 32-bit data type. 
;* @param[in]      bitRevLen    bit reversal table length
;* @param[in]      *pBitRevTab  points to bit reversal table.   
;* @return none.   
;*/
	EXPORT arm_bitreversal_32
   
#if defined(ARM_MATH_CM0) || defined(ARM_MATH_CM0PLUS)

arm_bitreversal_32 PROC
	ADDS     r3,r1,#1
	PUSH     {r4-r6}           
	ADDS     r1,r2,#0          
	LSRS     r3,r3,#1          
arm_bitreversal_32_0 LABEL
	LDRH     r2,[r1,#2]        
	LDRH     r6,[r1,#0]    
	ADD      r2,r0,r2   
	ADD      r6,r0,r6   
	LDR      r5,[r2,#0] 
	LDR      r4,[r6,#0]
	STR      r5,[r6,#0]
	STR      r4,[r2,#0]    
	LDR      r5,[r2,#4]        
	LDR      r4,[r6,#4]       
	STR      r5,[r6,#4]       
	STR      r4,[r2,#4]        
	ADDS     r1,r1,#4          
	SUBS     r3,r3,#1          
	BNE      arm_bitreversal_32_0
	POP      {r4-r6}
	BX       lr
	ENDP

#else

arm_bitreversal_32 PROC
	ADDS     r3,r1,#1
	CMP      r3,#1
	IT       LS
	BXLS     lr
	PUSH     {r4-r9}           
	ADDS     r1,r2,#2          
	LSRS     r3,r3,#2          
arm_bitreversal_32_0 LABEL       ;/* loop unrolled by 2 */
	LDRH     r8,[r1,#4]        
	LDRH     r9,[r1,#2]  
	LDRH     r2,[r1,#0]        
	LDRH     r12,[r1,#-2]    
	ADD      r8,r0,r8   
	ADD      r9,r0,r9    
	ADD      r2,r0,r2   
	ADD      r12,r0,r12   
	LDR      r7,[r9,#0] 
	LDR      r6,[r8,#0]
	LDR      r5,[r2,#0] 
	LDR      r4,[r12,#0]
	STR      r6,[r9,#0]
	STR      r7,[r8,#0] 
	STR      r5,[r12,#0]
	STR      r4,[r2,#0]      
	LDR      r7,[r9,#4]        
	LDR      r6,[r8,#4] 
	LDR      r5,[r2,#4]        
	LDR      r4,[r12,#4]           
	STR      r6,[r9,#4]       
	STR      r7,[r8,#4]   
	STR      r5,[r12,#4]       
	STR      r4,[r2,#4]        
	ADDS     r1,r1,#8          
	SUBS     r3,r3,#1          
	BNE      arm_bitreversal_32_0
	POP      {r4-r9}
	BX       lr
	ENDP
   
#endif
   
	END
