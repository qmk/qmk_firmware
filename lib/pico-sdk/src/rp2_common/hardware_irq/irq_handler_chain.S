/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico.h"
#include "hardware/irq.h"

#if !PICO_DISABLE_SHARED_IRQ_HANDLERS
.syntax unified
.cpu cortex-m0plus
.thumb

.data
.align 2

.global irq_handler_chain_slots

.global irq_handler_chain_first_slot
.global irq_handler_chain_remove_tail

//
// These Slots make up the code and structure of the handler chains; the only external information are the VTABLE entries
// (obviously one set per core) and a free list head. Each individual handler chain starts with the VTABLE entry I
// pointing at the address of slot S (with thumb bit set). Thus each slot which is part of a chain is executble.
//
// The execution jumps (via branch instruction) from one slot to the other, then jumps to the end of chain handler.
// The entirety of the state needed to traverse the chain is contained within the slots of the chain, which is why
// a VTABLE entry is all that is needed per chain (rather than requiring a separarte set of head pointers)
//

irq_handler_chain_slots:
.set next_slot_number, 1
.rept PICO_MAX_SHARED_IRQ_HANDLERS
    // a slot is executable and is always 3 instructions long.
    .hword 0    // inst1 (either: ldr r0, [pc, #4]    or for the FIRST slot : add r1, pc, #0                 )
    .hword 0    // inst2 (        blx r0                                      b irq_handler_chain_first_slot )

    .hword 0    // inst3 (either: b next_slot         or for the LAST         pop {pc}                       )

    // next is a single byte index of next slot in chain (or -1 to end)
.if next_slot_number == PICO_MAX_SHARED_IRQ_HANDLERS
    .byte 0xff
.else
    .byte next_slot_number
.endif
    // next is the 8 bit unsigned priority
    .byte 0x00
1:
    // and finally the handler function pointer
    .word 0x00000000
    .set next_slot_number, next_slot_number + 1
.endr

irq_handler_chain_first_slot:
    push {r0, lr}     // Save EXC_RETURN token, so `pop {r0, pc}` will return from interrupt
                      // Note that r0 does not NEED to be saved, however we must maintain
                      // an 8 byte stack alignment, and this is the cheapest way to do so
    ldr  r0, [r1, #4] // Get `handler` field of irq_handler_chain_slot
    adds r1, #1       // r1 points to `inst3` field of slot struct. Set Thumb bit on r1,
    mov  lr, r1       // and copy to lr, so `inst3` is executed on return from handler
    bx   r0           // Enter handler

irq_handler_chain_remove_tail:
    mov  r0, lr       // Get start of struct. This function was called by a bl at offset +4,
    subs r0, #9       // so lr points to offset +8. Note also lr has its Thumb bit set!
    ldr  r1, =irq_add_tail_to_free_list
    blx  r1
    pop  {r0, pc}     // Top of stack is EXC_RETURN


#endif
