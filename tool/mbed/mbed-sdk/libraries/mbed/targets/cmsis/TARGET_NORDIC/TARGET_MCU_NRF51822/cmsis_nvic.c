/* mbed Microcontroller Library
 * CMSIS-style functionality to support dynamic vectors
 *******************************************************************************
 * Copyright (c) 2011 ARM Limited. All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of ARM Limited nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */
#include "cmsis_nvic.h"

/* In the M0, there is no VTOR. In the LPC range such as the LPC11U,
 * whilst the vector table may only be something like 48 entries (192 bytes, 0xC0), 
 * the SYSMEMREMAP register actually remaps the memory from 0x10000000-0x100001FF 
 * to adress 0x0-0x1FF. In this case, RAM can be addressed at both 0x10000000 and 0x0
 * 
 * If we just copy the vectors to RAM and switch the SYSMEMMAP, any accesses to FLASH
 * above the vector table before 0x200 will actually go to RAM. So we need to provide 
 * a solution where the compiler gets the right results based on the memory map
 *
 * Option 1 - We allocate and copy 0x200 of RAM rather than just the table
 *  - const data and instructions before 0x200 will be copied to and fetched/exec from RAM
 *  - RAM overhead: 0x200 - 0xC0 = 320 bytes, FLASH overhead: 0
 * 
 * Option 2 - We pad the flash to 0x200 to ensure the compiler doesn't allocate anything there  
 *  - No flash accesses will go to ram, as there will be nothing there
 *  - RAM only needs to be allocated for the vectors, as all other ram addresses are normal
 *  - RAM overhead: 0, FLASH overhead: 320 bytes
 *
 * Option 2 is the one to go for, as RAM is the most valuable resource
 */


#define NVIC_RAM_VECTOR_ADDRESS   (0x10000000)  // Location of vectors in RAM
#define NVIC_FLASH_VECTOR_ADDRESS (0x0)       // Initial vector position in flash
/*
void NVIC_SetVector(IRQn_Type IRQn, uint32_t vector) {
    uint32_t *vectors = (uint32_t*)SCB->VTOR;
    uint32_t i;

    // Copy and switch to dynamic vectors if the first time called
    if (SCB->VTOR == NVIC_FLASH_VECTOR_ADDRESS) {
        uint32_t *old_vectors = vectors;
        vectors = (uint32_t*)NVIC_RAM_VECTOR_ADDRESS;
        for (i=0; i<NVIC_NUM_VECTORS; i++) {
            vectors[i] = old_vectors[i];
        }
        SCB->VTOR = (uint32_t)NVIC_RAM_VECTOR_ADDRESS;
    }
    vectors[IRQn + 16] = vector;
}

uint32_t NVIC_GetVector(IRQn_Type IRQn) {
    uint32_t *vectors = (uint32_t*)SCB->VTOR;
    return vectors[IRQn + 16];
}*/

void NVIC_SetVector(IRQn_Type IRQn, uint32_t vector) {
   // int i;
    // Space for dynamic vectors, initialised to allocate in R/W
    static volatile uint32_t* vectors = (uint32_t*)NVIC_RAM_VECTOR_ADDRESS;
    /*
    // Copy and switch to dynamic vectors if first time called
    if((LPC_SYSCON->SYSMEMREMAP & 0x3) != 0x1) {     
      uint32_t *old_vectors = (uint32_t *)0;         // FLASH vectors are at 0x0
      for(i = 0; i < NVIC_NUM_VECTORS; i++) {    
            vectors[i] = old_vectors[i];
        }
        LPC_SYSCON->SYSMEMREMAP = 0x1; // Remaps 0x0-0x1FF FLASH block to RAM block
    }*/

    // Set the vector 
    vectors[IRQn + 16] = vector; 
}

uint32_t NVIC_GetVector(IRQn_Type IRQn) {
    // We can always read vectors at 0x0, as the addresses are remapped
    uint32_t *vectors = (uint32_t*)0; 

    // Return the vector
    return vectors[IRQn + 16];
}
