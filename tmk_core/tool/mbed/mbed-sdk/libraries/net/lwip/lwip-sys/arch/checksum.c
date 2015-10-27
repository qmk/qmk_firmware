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


/* This is a hand written Thumb-2 assembly language version of the
   algorithm 3 version of lwip_standard_chksum in lwIP's inet_chksum.c.  It
   performs the checksumming 32-bits at a time and even unrolls the loop to
   perform two of these 32-bit adds per loop iteration.
   
   Returns:
        16-bit 1's complement summation (not inversed).
        
   NOTE: This function does return a uint16_t from the assembly language code
         but is marked as void so that GCC doesn't issue warning because it
         doesn't know about this low level return.
*/
__attribute__((naked)) void /*uint16_t*/ thumb2_checksum(const void* pData, int length)
{
    __asm (
        ".syntax unified\n"
        ".thumb\n"

        // Push non-volatile registers we use on stack.  Push link register too to
        // keep stack 8-byte aligned and allow single pop to restore and return.
        "    push        {r4, lr}\n"
        // Initialize sum, r2, to 0.
        "    movs    r2, #0\n"
        // Remember whether pData was at odd address in r3.  This is used later to
        // know if it needs to swap the result since the summation will be done at
        // an offset of 1, rather than 0.
        "    ands    r3, r0, #1\n"
        // Need to 2-byte align?  If not skip ahead.
        "    beq     1$\n"
        // We can return if there are no bytes to sum.
        "    cbz     r1, 9$\n"

        // 2-byte align.
        // Place the first data byte in odd summation location since it needs to be
        // swapped later.  It's ok to overwrite r2 here as it only had a value of 0
        // up until now.  Advance r0 pointer and decrement r1 length as we go.
        "    ldrb    r2, [r0], #1\n"
        "    lsls    r2, r2, #8\n"
        "    subs    r1, r1, #1\n"

        // Need to 4-byte align?  If not skip ahead.
        "1$:\n"
        "    ands    r4, r0, #3\n"
        "    beq     2$\n"
        // Have more than 1 byte left to align?  If not skip ahead to take care of
        // trailing byte.
        "    cmp     r1, #2\n"
        "    blt     7$\n"

        // 4-byte align.
        "    ldrh    r4, [r0], #2\n"
        "    adds    r2, r2, r4\n"
        "    subs    r1, r1, #2\n"

        // Main summing loop which sums up data 2 words at a time.
        // Make sure that we have more than 7 bytes left to sum.
        "2$:\n"
        "    cmp     r1, #8\n"
        "    blt     3$\n"
        // Sum next two words.  Applying previous upper 16-bit carry to
        // lower 16-bits.
        "    ldr     r4, [r0], #4\n"
        "    adds    r2, r4\n"
        "    adc     r2, r2, #0\n"
        "    ldr     r4, [r0], #4\n"
        "    adds    r2, r4\n"
        "    adc     r2, r2, #0\n"
        "    subs    r1, r1, #8\n"
        "    b       2$\n"

        // Sum up any remaining half-words.
        "3$:\n"
        // Make sure that we have more than 1 byte left to sum.
        "    cmp     r1, #2\n"
        "    blt     7$\n"
        // Sum up next half word, continue to apply carry.
        "    ldrh    r4, [r0], #2\n"
        "    adds    r2, r4\n"
        "    adc     r2, r2, #0\n"
        "    subs    r1, r1, #2\n"
        "    b       3$\n"

        // Handle trailing byte, if it exists
        "7$:\n"
        "    cbz     r1, 8$\n"
        "    ldrb    r4, [r0]\n"
        "    adds    r2, r4\n"
        "    adc     r2, r2, #0\n"

        // Fold 32-bit checksum into 16-bit checksum.
        "8$:\n"
        "    ubfx    r4, r2, #16, #16\n"
        "    ubfx    r2, r2, #0, #16\n"
        "    adds    r2, r4\n"
        "    ubfx    r4, r2, #16, #16\n"
        "    ubfx    r2, r2, #0, #16\n"
        "    adds    r2, r4\n"

        // Swap bytes if started at odd address
        "    cbz     r3, 9$\n"
        "    rev16   r2, r2\n"

        // Return final sum.
        "9$: mov     r0, r2\n"
        "    pop     {r4, pc}\n"
    );
}

#endif
