/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/irq.h"
#include "hardware/regs/m0plus.h"
#include "hardware/platform_defs.h"
#include "hardware/structs/scb.h"
#include "hardware/claim.h"

#include "pico/mutex.h"
#include "pico/assert.h"

extern void __unhandled_user_irq(void);

#if PICO_VTABLE_PER_CORE
static uint8_t user_irq_claimed[NUM_CORES];
static inline uint8_t *user_irq_claimed_ptr(void) {
    return &user_irq_claimed[get_core_num()];
}
#else
static uint8_t user_irq_claimed;
static inline uint8_t *user_irq_claimed_ptr(void) {
    return &user_irq_claimed;
}
#endif

static inline irq_handler_t *get_vtable(void) {
    return (irq_handler_t *) scb_hw->vtor;
}

static inline void *add_thumb_bit(void *addr) {
    return (void *) (((uintptr_t) addr) | 0x1);
}

static inline void *remove_thumb_bit(void *addr) {
    return (void *) (((uintptr_t) addr) & (uint)~0x1);
}

static void set_raw_irq_handler_and_unlock(uint num, irq_handler_t handler, uint32_t save) {
    // update vtable (vtable_handler may be same or updated depending on cases, but we do it anyway for compactness)
    get_vtable()[VTABLE_FIRST_IRQ + num] = handler;
    __dmb();
    spin_unlock(spin_lock_instance(PICO_SPINLOCK_ID_IRQ), save);
}

void irq_set_enabled(uint num, bool enabled) {
    check_irq_param(num);
    irq_set_mask_enabled(1u << num, enabled);
}

bool irq_is_enabled(uint num) {
    check_irq_param(num);
    return 0 != ((1u << num) & *((io_rw_32 *) (PPB_BASE + M0PLUS_NVIC_ISER_OFFSET)));
}

void irq_set_mask_enabled(uint32_t mask, bool enabled) {
    if (enabled) {
        // Clear pending before enable
        // (if IRQ is actually asserted, it will immediately re-pend)
        *((io_rw_32 *) (PPB_BASE + M0PLUS_NVIC_ICPR_OFFSET)) = mask;
        *((io_rw_32 *) (PPB_BASE + M0PLUS_NVIC_ISER_OFFSET)) = mask;
    } else {
        *((io_rw_32 *) (PPB_BASE + M0PLUS_NVIC_ICER_OFFSET)) = mask;
    }
}

void irq_set_pending(uint num) {
    check_irq_param(num);
    *((io_rw_32 *) (PPB_BASE + M0PLUS_NVIC_ISPR_OFFSET)) = 1u << num;
}

#if !PICO_DISABLE_SHARED_IRQ_HANDLERS
// limited by 8 bit relative links (and reality)
static_assert(PICO_MAX_SHARED_IRQ_HANDLERS >= 1 && PICO_MAX_SHARED_IRQ_HANDLERS < 0x7f, "");

// note these are not real functions, they are code fragments (i.e. don't call them)
extern void irq_handler_chain_first_slot(void);
extern void irq_handler_chain_remove_tail(void);

extern struct irq_handler_chain_slot {
    // first 3 half words are executable code (raw vtable handler points to one slot, and inst3 will jump to next
    // in chain (or end of chain handler)
    uint16_t inst1;
    uint16_t inst2;
    uint16_t inst3;
    union {
        // when a handler is removed while executing, it needs an extra instruction, which overwrites
        // the link and the priority; this is ok because no one else is modifying the chain, as
        // the chain is effectively core local, and the user code which might still need this link
        // disable the IRQ in question before updating, which means we aren't executing!
        struct {
            int8_t link;
            uint8_t priority;
        };
        uint16_t inst4;
    };
    irq_handler_t handler;
} irq_handler_chain_slots[PICO_MAX_SHARED_IRQ_HANDLERS];

static int8_t irq_hander_chain_free_slot_head;

static inline bool is_shared_irq_raw_handler(irq_handler_t raw_handler) {
    return (uintptr_t)raw_handler - (uintptr_t)irq_handler_chain_slots < sizeof(irq_handler_chain_slots);
}

bool irq_has_shared_handler(uint irq_num) {
    check_irq_param(irq_num);
    irq_handler_t handler = irq_get_vtable_handler(irq_num);
    return handler && is_shared_irq_raw_handler(handler);
}

#else
#define is_shared_irq_raw_handler(h) false
bool irq_has_shared_handler(uint irq_num) {
    return false;
}
#endif


irq_handler_t irq_get_vtable_handler(uint num) {
    check_irq_param(num);
    return get_vtable()[16 + num];
}

void irq_set_exclusive_handler(uint num, irq_handler_t handler) {
    check_irq_param(num);
#if !PICO_NO_RAM_VECTOR_TABLE
    spin_lock_t *lock = spin_lock_instance(PICO_SPINLOCK_ID_IRQ);
    uint32_t save = spin_lock_blocking(lock);
    __unused irq_handler_t current = irq_get_vtable_handler(num);
    hard_assert(current == __unhandled_user_irq || current == handler);
    set_raw_irq_handler_and_unlock(num, handler, save);
#else
    panic_unsupported();
#endif
}

irq_handler_t irq_get_exclusive_handler(uint num) {
    check_irq_param(num);
#if !PICO_NO_RAM_VECTOR_TABLE
    spin_lock_t *lock = spin_lock_instance(PICO_SPINLOCK_ID_IRQ);
    uint32_t save = spin_lock_blocking(lock);
    irq_handler_t current = irq_get_vtable_handler(num);
    spin_unlock(lock, save);
    if (current == __unhandled_user_irq || is_shared_irq_raw_handler(current)) {
        return NULL;
    }
    return current;
#else
    panic_unsupported();
#endif
}


#if !PICO_DISABLE_SHARED_IRQ_HANDLERS
static uint16_t make_branch(uint16_t *from, void *to) {
    uint32_t ui_from = (uint32_t)from;
    uint32_t ui_to = (uint32_t)to;
    int32_t delta = (int32_t)(ui_to - ui_from - 4);
    assert(delta >= -2048 && delta <= 2046 && !(delta & 1));
    return (uint16_t)(0xe000 | ((delta >> 1) & 0x7ff));
}

static void insert_branch_and_link(uint16_t *from, void *to) {
    uint32_t ui_from = (uint32_t)from;
    uint32_t ui_to = (uint32_t)to;
    uint32_t delta = (ui_to - ui_from - 4) / 2;
    assert(!(delta >> 11u));
    from[0] = (uint16_t)(0xf000 | ((delta >> 11u) & 0x7ffu));
    from[1] = (uint16_t)(0xf800 | (delta & 0x7ffu));
}

static inline void *resolve_branch(uint16_t *inst) {
    assert(0x1c == (*inst)>>11u);
    int32_t i_addr = (*inst) << 21u;
    i_addr /= (int32_t)(1u<<21u);
    return inst + 2 + i_addr;
}

// GCC produces horrible code for subtraction of pointers here, and it was bugging me
static inline int8_t slot_diff(struct irq_handler_chain_slot *to, struct irq_handler_chain_slot *from) {
    static_assert(sizeof(struct irq_handler_chain_slot) == 12, "");
    int32_t result = 0xaaaa;
    // return (to - from);
    // note this implementation has limited range, but is fine for plenty more than -128->127 result
    asm (".syntax unified\n"
         "subs %1, %2\n"
         "adcs %1, %1\n" // * 2 (and + 1 if negative for rounding)
         "muls %0, %1\n"
         "lsrs %0, 20\n"
         : "+l" (result), "+l" (to)
         : "l" (from)
         :
         );
    return (int8_t)result;
}

static inline int8_t get_slot_index(struct irq_handler_chain_slot *slot) {
    return slot_diff(slot, irq_handler_chain_slots);
}
#endif

void irq_add_shared_handler(uint num, irq_handler_t handler, uint8_t order_priority) {
    check_irq_param(num);
#if PICO_NO_RAM_VECTOR_TABLE
    panic_unsupported()
#elif PICO_DISABLE_SHARED_IRQ_HANDLERS
    irq_set_exclusive_handler(num, handler);
#else
    spin_lock_t *lock = spin_lock_instance(PICO_SPINLOCK_ID_IRQ);
    uint32_t save = spin_lock_blocking(lock);
    hard_assert(irq_hander_chain_free_slot_head >= 0); // we must have a slot
    struct irq_handler_chain_slot *slot = &irq_handler_chain_slots[irq_hander_chain_free_slot_head];
    int8_t slot_index = irq_hander_chain_free_slot_head;
    irq_hander_chain_free_slot_head = slot->link;
    irq_handler_t vtable_handler = get_vtable()[16 + num];
    if (!is_shared_irq_raw_handler(vtable_handler)) {
        // start new chain
        hard_assert(vtable_handler == __unhandled_user_irq);
        struct irq_handler_chain_slot slot_data = {
                .inst1 = 0xa100,                                                    // add r1, pc, #0
                .inst2 = make_branch(&slot->inst2, irq_handler_chain_first_slot),   // b irq_handler_chain_first_slot
                .inst3 = 0xbd01,                                                    // pop {r0, pc}
                .link = -1,
                .priority = order_priority,
                .handler = handler
        };
        *slot = slot_data;
        vtable_handler = (irq_handler_t)add_thumb_bit(slot);
    } else {
        assert(!((((uintptr_t)vtable_handler) - ((uintptr_t)irq_handler_chain_slots) - 1)%sizeof(struct irq_handler_chain_slot)));
        struct irq_handler_chain_slot *prev_slot = NULL;
        struct irq_handler_chain_slot *existing_vtable_slot = remove_thumb_bit(vtable_handler);
        struct irq_handler_chain_slot *cur_slot = existing_vtable_slot;
        while (cur_slot->priority > order_priority) {
            prev_slot = cur_slot;
            if (cur_slot->link < 0) break;
            cur_slot = &irq_handler_chain_slots[cur_slot->link];
        }
        if (prev_slot) {
            // insert into chain
            struct irq_handler_chain_slot slot_data = {
                    .inst1 = 0x4801,                                                        // ldr r0, [pc, #4]
                    .inst2 = 0x4780,                                                        // blx r0
                    .inst3 = prev_slot->link >= 0 ?
                            make_branch(&slot->inst3, resolve_branch(&prev_slot->inst3)) : // b next_slot
                            0xbd01,                                                        // pop {r0, pc}
                    .link = prev_slot->link,
                    .priority = order_priority,
                    .handler = handler
            };
            // update code and data links
            prev_slot->inst3 = make_branch(&prev_slot->inst3, slot),
            prev_slot->link = slot_index;
            *slot = slot_data;
        } else {
            // update with new chain head
            struct irq_handler_chain_slot slot_data = {
                    .inst1 = 0xa100,                                                    // add r1, pc, #0
                    .inst2 = make_branch(&slot->inst2, irq_handler_chain_first_slot),   // b irq_handler_chain_first_slot
                    .inst3 = make_branch(&slot->inst3, existing_vtable_slot),           // b existing_slot
                    .link = get_slot_index(existing_vtable_slot),
                    .priority = order_priority,
                    .handler = handler
            };
            *slot = slot_data;
            // fixup previous head slot
            existing_vtable_slot->inst1 = 0x4801; // ldr r0, [pc, #4]
            existing_vtable_slot->inst2 = 0x4780; // blx r0
            vtable_handler = (irq_handler_t)add_thumb_bit(slot);
        }
    }
    set_raw_irq_handler_and_unlock(num, vtable_handler, save);
#endif
}

void irq_remove_handler(uint num, irq_handler_t handler) {
#if !PICO_NO_RAM_VECTOR_TABLE
    spin_lock_t *lock = spin_lock_instance(PICO_SPINLOCK_ID_IRQ);
    uint32_t save = spin_lock_blocking(lock);
    irq_handler_t vtable_handler = get_vtable()[16 + num];
    if (vtable_handler != __unhandled_user_irq && vtable_handler != handler) {
#if !PICO_DISABLE_SHARED_IRQ_HANDLERS
        if (is_shared_irq_raw_handler(vtable_handler)) {
            // This is a bit tricky, as an executing IRQ handler doesn't take a lock.

            // First thing to do is to disable the IRQ in question; that takes care of calls from user code.
            // Note that a irq handler chain is local to our own core, so we don't need to worry about the other core
            bool was_enabled = irq_is_enabled(num);
            irq_set_enabled(num, false);
            __dmb();

            // It is possible we are being called while an IRQ for this chain is already in progress.
            // The issue we have here is that we must not free a slot that is currently being executed, because
            // inst3 is still to be executed, and inst3 might get overwritten if the slot is re-used.

            // By disallowing other exceptions from removing an IRQ handler (which seems fair)
            // we now only have to worry about removing a slot from a chain that is currently executing.

            // Note we expect that the slot we are deleting is the one that is executing.
            // In particular, bad things happen if the caller were to delete the handler in the chain
            // before it. This is not an allowed use case though, and I can't imagine anyone wanting to in practice.
            // Sadly this is not something we can detect.

            uint exception = __get_current_exception();
            hard_assert(!exception || exception == num + VTABLE_FIRST_IRQ);

            struct irq_handler_chain_slot *prev_slot = NULL;
            struct irq_handler_chain_slot *existing_vtable_slot = remove_thumb_bit(vtable_handler);
            struct irq_handler_chain_slot *to_free_slot = existing_vtable_slot;
            while (to_free_slot->handler != handler) {
                prev_slot = to_free_slot;
                if (to_free_slot->link < 0) break;
                to_free_slot = &irq_handler_chain_slots[to_free_slot->link];
            }
            if (to_free_slot->handler == handler) {
                int8_t next_slot_index = to_free_slot->link;
                if (next_slot_index >= 0) {
                    // There is another slot in the chain, so copy that over us, so that our inst3 points at something valid
                    // Note this only matters in the exception case anyway, and it that case, we will skip the next handler,
                    // however in that case it's IRQ cause should immediately cause re-entry of the IRQ and the only side
                    // effect will be that there was potentially brief out of priority order execution of the handlers
                    struct irq_handler_chain_slot *next_slot = &irq_handler_chain_slots[next_slot_index];
                    to_free_slot->handler = next_slot->handler;
                    to_free_slot->priority = next_slot->priority;
                    to_free_slot->link = next_slot->link;
                    to_free_slot->inst3 = next_slot->link >= 0 ?
                            make_branch(&to_free_slot->inst3, resolve_branch(&next_slot->inst3)) : // b mext_>slot->next_slot
                            0xbd01;                                                                // pop {r0, pc}

                    // add old next slot back to free list
                    next_slot->link = irq_hander_chain_free_slot_head;
                    irq_hander_chain_free_slot_head = next_slot_index;
                } else {
                    // Slot being removed is at the end of the chain
                    if (!exception) {
                        // case when we're not in exception, we physically unlink now
                        if (prev_slot) {
                            // chain is not empty
                            prev_slot->link = -1;
                            prev_slot->inst3 = 0xbd01; // pop {r0, pc}
                        } else {
                            // chain is not empty
                            vtable_handler = __unhandled_user_irq;
                        }
                        // add slot back to free list
                        to_free_slot->link = irq_hander_chain_free_slot_head;
                        irq_hander_chain_free_slot_head = get_slot_index(to_free_slot);
                    } else {
                        // since we are the last slot we know that our inst3 hasn't executed yet, so we change
                        // it to bl to irq_handler_chain_remove_tail which will remove the slot.
                        // NOTE THAT THIS TRASHES PRIORITY AND LINK SINCE THIS IS A 4 BYTE INSTRUCTION
                        //      BUT THEY ARE NOT NEEDED NOW
                        insert_branch_and_link(&to_free_slot->inst3, irq_handler_chain_remove_tail);
                    }
                }
            } else {
                assert(false); // not found
            }
            irq_set_enabled(num, was_enabled);
        }
#else
        assert(false); // not found
#endif
    } else {
        vtable_handler = __unhandled_user_irq;
    }
    set_raw_irq_handler_and_unlock(num, vtable_handler, save);
#else
    panic_unsupported();
#endif
}

void irq_set_priority(uint num, uint8_t hardware_priority) {
    check_irq_param(num);

    // note that only 32 bit writes are supported
    io_rw_32 *p = (io_rw_32 *)((PPB_BASE + M0PLUS_NVIC_IPR0_OFFSET) + (num & ~3u));
    *p = (*p & ~(0xffu << (8 * (num & 3u)))) | (((uint32_t) hardware_priority) << (8 * (num & 3u)));
}

uint irq_get_priority(uint num) {
    check_irq_param(num);

    // note that only 32 bit reads are supported
    io_rw_32 *p = (io_rw_32 *)((PPB_BASE + M0PLUS_NVIC_IPR0_OFFSET) + (num & ~3u));
    return (uint8_t)(*p >> (8 * (num & 3u)));
}

#if !PICO_DISABLE_SHARED_IRQ_HANDLERS
// used by irq_handler_chain.S to remove the last link in a handler chain after it executes
// note this must be called only with the last slot in a chain (and during the exception)
void irq_add_tail_to_free_list(struct irq_handler_chain_slot *slot) {
    irq_handler_t slot_handler = (irq_handler_t) add_thumb_bit(slot);
    assert(is_shared_irq_raw_handler(slot_handler));

    uint exception = __get_current_exception();
    assert(exception);
    spin_lock_t *lock = spin_lock_instance(PICO_SPINLOCK_ID_IRQ);
    uint32_t save = spin_lock_blocking(lock);
    int8_t slot_index = get_slot_index(slot);
    if (slot_handler == get_vtable()[exception]) {
        get_vtable()[exception] = __unhandled_user_irq;
    } else {
        bool __unused found = false;
        // need to find who points at the slot and update it
        for(uint i=0;i<count_of(irq_handler_chain_slots);i++) {
            if (irq_handler_chain_slots[i].link == slot_index) {
                irq_handler_chain_slots[i].link = -1;
                irq_handler_chain_slots[i].inst3 = 0xbd01; // pop {r0, pc}
                found = true;
                break;
            }
        }
        assert(found);
    }
    // add slot to free list
    slot->link = irq_hander_chain_free_slot_head;
    irq_hander_chain_free_slot_head = slot_index;
    spin_unlock(lock, save);
}
#endif

void irq_init_priorities() {
#if PICO_DEFAULT_IRQ_PRIORITY != 0
    static_assert(!(NUM_IRQS & 3), "");
    uint32_t prio4 = (PICO_DEFAULT_IRQ_PRIORITY & 0xff) * 0x1010101u;
    io_rw_32 * p = (io_rw_32 *)(PPB_BASE + M0PLUS_NVIC_IPR0_OFFSET);
    for (uint i = 0; i < NUM_IRQS / 4; i++) {
        *p++ = prio4;
    }
#endif
}

static uint get_user_irq_claim_index(uint irq_num) {
    invalid_params_if(IRQ, irq_num < FIRST_USER_IRQ || irq_num >= NUM_IRQS);
    // we count backwards from the last, to match the existing hard coded uses of user IRQs in the SDK which were previously using 31
    static_assert(NUM_IRQS - FIRST_USER_IRQ <= 8, ""); // we only use a single byte's worth of claim bits today.
    return NUM_IRQS - irq_num  - 1u;
}

void user_irq_claim(uint irq_num) {
    hw_claim_or_assert(user_irq_claimed_ptr(), get_user_irq_claim_index(irq_num), "User IRQ is already claimed");
}

void user_irq_unclaim(uint irq_num) {
    hw_claim_clear(user_irq_claimed_ptr(), get_user_irq_claim_index(irq_num));
}

int user_irq_claim_unused(bool required) {
    int bit = hw_claim_unused_from_range(user_irq_claimed_ptr(), required, 0, NUM_USER_IRQS - 1, "No user IRQs are available");
    if (bit >= 0) bit =  (int)NUM_IRQS - bit - 1;
    return bit;
}

bool user_irq_is_claimed(uint irq_num) {
    return hw_is_claimed(user_irq_claimed_ptr(), get_user_irq_claim_index(irq_num));
}

