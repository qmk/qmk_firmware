/* Copyright (c) 2009 - 2012 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *      Functions
 *---------------------------------------------------------------------------*/
    .text
    .global __v7_all_cache
/*
 * __STATIC_ASM void __v7_all_cache(uint32_t op) {
 */
__v7_all_cache:
        .arm

        PUSH    {R4-R11}

        MRC     p15, 1, R6, c0, c0, 1      /* Read CLIDR */
        ANDS    R3, R6, #0x07000000        /* Extract coherency level */
        MOV     R3, R3, LSR #23            /* Total cache levels << 1 */
        BEQ     Finished                   /* If 0, no need to clean */

        MOV     R10, #0                    /* R10 holds current cache level << 1 */
Loop1:  ADD     R2, R10, R10, LSR #1       /* R2 holds cache "Set" position */
        MOV     R1, R6, LSR R2             /* Bottom 3 bits are the Cache-type for this level */
        AND     R1, R1, #7                 /* Isolate those lower 3 bits */
        CMP     R1, #2
        BLT     Skip                       /* No cache or only instruction cache at this level */

        MCR     p15, 2, R10, c0, c0, 0     /* Write the Cache Size selection register */
        ISB                                /* ISB to sync the change to the CacheSizeID reg */
        MRC     p15, 1, R1, c0, c0, 0      /* Reads current Cache Size ID register */
        AND     R2, R1, #7                 /* Extract the line length field */
        ADD     R2, R2, #4                 /* Add 4 for the line length offset (log2 16 bytes) */
        LDR     R4, =0x3FF
        ANDS    R4, R4, R1, LSR #3         /* R4 is the max number on the way size (right aligned) */
        CLZ     R5, R4                     /* R5 is the bit position of the way size increment */
        LDR     R7, =0x7FFF
        ANDS    R7, R7, R1, LSR #13        /* R7 is the max number of the index size (right aligned) */

Loop2:  MOV     R9, R4                     /* R9 working copy of the max way size (right aligned) */

Loop3:  ORR     R11, R10, R9, LSL R5       /* Factor in the Way number and cache number into R11 */
        ORR     R11, R11, R7, LSL R2       /* Factor in the Set number */
        CMP     R0, #0
        BNE     Dccsw
        MCR     p15, 0, R11, c7, c6, 2     /* DCISW. Invalidate by Set/Way */
        B       cont
Dccsw:  CMP     R0, #1
        BNE     Dccisw
        MCR     p15, 0, R11, c7, c10, 2    /* DCCSW. Clean by Set/Way */
        B       cont
Dccisw: MCR     p15, 0, R11, c7, c14, 2    /* DCCISW, Clean and Invalidate by Set/Way */
cont:   SUBS    R9, R9, #1                 /* Decrement the Way number */
        BGE     Loop3
        SUBS    R7, R7, #1                 /* Decrement the Set number */
        BGE     Loop2
Skip:   ADD     R10, R10, #2               /* increment the cache number */
        CMP     R3, R10
        BGT     Loop1

Finished:
        DSB
        POP    {R4-R11}
        BX     lr


    .END
/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
