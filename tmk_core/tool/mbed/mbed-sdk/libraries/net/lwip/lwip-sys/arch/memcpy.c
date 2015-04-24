/* Copyright (C) 2013 - Adam Green (https://github.com/adamgreen)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#if defined(TOOLCHAIN_GCC) && defined(__thumb2__)

#include <stdio.h>


/* This is a hand written Thumb-2 assembly language version of the
   standard C memcpy() function that can be used by the lwIP networking
   stack to improve its performance.  It copies 4 bytes at a time and
   unrolls the loop to perform 4 of these copies per loop iteration.
*/
__attribute__((naked)) void thumb2_memcpy(void* pDest, const void* pSource, size_t length)
{
    __asm (
        ".syntax unified\n"
        ".thumb\n"

        // Copy 16 bytes at a time first.
        "    lsrs    r3, r2, #4\n"
        "    beq.n   2$\n"
        "1$: ldr     r12, [r1], #4\n"
        "    str     r12, [r0], #4\n"
        "    ldr     r12, [r1], #4\n"
        "    str     r12, [r0], #4\n"
        "    ldr     r12, [r1], #4\n"
        "    str     r12, [r0], #4\n"
        "    ldr     r12, [r1], #4\n"
        "    str     r12, [r0], #4\n"
        "    subs    r3, #1\n"
        "    bne     1$\n"

        // Copy byte by byte for what is left.
        "2$:\n"
        "    ands    r3, r2, #0xf\n"
        "    beq.n   4$\n"
        "3$: ldrb    r12, [r1], #1\n"
        "    strb    r12, [r0], #1\n"
        "    subs    r3, #1\n"
        "    bne     3$\n"

        // Return to caller.
        "4$: bx      lr\n"
    );
}

#endif
