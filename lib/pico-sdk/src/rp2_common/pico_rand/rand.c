/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*  xoroshiro128ss(), rotl():

    Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)

    To the extent possible under law, the author has dedicated all copyright
    and related and neighboring rights to this software to the public domain
    worldwide. This software is distributed without any warranty.

    See <http://creativecommons.org/publicdomain/zero/1.0/>

    splitmix64() implementation:

    Written in 2015 by Sebastiano Vigna (vigna@acm.org)
    To the extent possible under law, the author has dedicated all copyright
    and related and neighboring rights to this software to the public domain
    worldwide. This software is distributed without any warranty.

    See <http://creativecommons.org/publicdomain/zero/1.0/>
*/

#include "pico/rand.h"
#include "pico/unique_id.h"
#include "pico/time.h"
#include "hardware/clocks.h"
#include "hardware/structs/rosc.h"
#include "hardware/structs/bus_ctrl.h"
#include "hardware/sync.h"

static bool rng_initialised = false;

// Note: By design, do not initialise any of the variables that hold entropy,
// they may have useful junk in them, either from power-up or a previous boot.
static rng_128_t __uninitialized_ram(rng_state);
#if PICO_RAND_SEED_ENTROPY_SRC_RAM_HASH
static uint64_t __uninitialized_ram(ram_hash);
#endif

#if PICO_RAND_ENTROPY_SRC_ROSC | PICO_RAND_SEED_ENTROPY_SRC_ROSC
static uint64_t __uninitialized_ram(rosc_samples);
#endif

#if PICO_RAND_ENTROPY_SRC_BUS_PERF_COUNTER
static uint8_t bus_counter_idx;
#endif

/* From the original source:

   This is a fixed-increment version of Java 8's SplittableRandom generator
   See http://dx.doi.org/10.1145/2714064.2660195 and
   http://docs.oracle.com/javase/8/docs/api/java/util/SplittableRandom.html

   It is a very fast generator passing BigCrush, and it can be useful if
   for some reason you absolutely want 64 bits of state; otherwise, we
   rather suggest to use a xoroshiro128+ (for moderately parallel
   computations) or xorshift1024* (for massively parallel computations)
   generator.

   Note:  This can be called with any value (i.e. including 0)
*/
static __noinline uint64_t splitmix64(uint64_t x) {
    uint64_t z = x + 0x9E3779B97F4A7C15ull;
    z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ull;
    z = (z ^ (z >> 27)) * 0x94D049BB133111EBull;
    return z ^ (z >> 31);
}

/* From the original source:

   This is xoroshiro128** 1.0, one of our all-purpose, rock-solid,
   small-state generators. It is extremely (sub-ns) fast and it passes all
   tests we are aware of, but its state space is large enough only for
   mild parallelism.

   For generating just floating-point numbers, xoroshiro128+ is even
   faster (but it has a very mild bias, see notes in the comments).

   The state must be seeded so that it is not everywhere zero. If you have
   a 64-bit seed, we suggest to seed a splitmix64 generator and use its
   output to fill s.
*/
static inline uint64_t rotl(const uint64_t x, int k) {
    return (x << k) | (x >> (64 - k));
}

static __noinline uint64_t xoroshiro128ss(rng_128_t *local_rng_state) {
    const uint64_t s0 = local_rng_state->r[0];
    uint64_t s1 = local_rng_state->r[1];

    // Because the state is *modified* outside of this function, there is a
    // 1 in 2^128 chance that it could be all zeroes (which is not allowed).
    while (s0 == 0 && s1 == 0) {
        s1 = time_us_64();   // should not be 0, but loop anyway
    }

    const uint64_t result = rotl(s0 * 5, 7) * 9;

    s1 ^= s0;
    local_rng_state->r[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16); // a, b
    local_rng_state->r[1] = rotl(s1, 37); // c

    return result;
}

#if PICO_RAND_SEED_ENTROPY_SRC_RAM_HASH
static uint64_t sdbm_hash64_sram(uint64_t hash) {
    // save some time by hashing a word at a time
    for (uint i = (PICO_RAND_RAM_HASH_START + 3) & ~3; i < PICO_RAND_RAM_HASH_END; i+=4) {
        uint32_t c = *(uint32_t *) i;
        hash = (uint64_t) c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}
#endif

#if PICO_RAND_SEED_ENTROPY_SRC_ROSC | PICO_RAND_ENTROPY_SRC_ROSC
/* gather an additional n bits of entropy, and shift them into the 64 bit entropy counter */
static uint64_t capture_additional_rosc_samples(uint n) {
    static absolute_time_t next_sample_time;

    // provide an override if someone really wants it, but disabling ROSC as an entropy source makes more sense
#if !PICO_RAND_DISABLE_ROSC_CHECK
    // check that the ROSC is running but that the processors are NOT running from it
    hard_assert((rosc_hw->status & ROSC_STATUS_ENABLED_BITS) &&
                ((clocks_hw->clk[clk_sys].ctrl & CLOCKS_CLK_SYS_CTRL_AUXSRC_BITS) != (CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_ROSC_CLKSRC << CLOCKS_CLK_SYS_CTRL_AUXSRC_LSB)));
#endif

    bool in_exception = __get_current_exception();
    assert(n); // save us having to special case samples for this
    uint64_t samples = 0;
    for(uint i=0; i<n; i++) {
        bool bit_done = false;
        do {
            // Ensure that the ROSC random bit is not sampled too quickly,
            // ROSC may be ticking only a few times a microsecond.
            // Note: In general (i.e. sporadic) use, very often there will be no delay here.

            // note this is not read under lock, so the two 32 bit halves could be skewed, but in that
            // case we'll fail the check later, which is fine in this rare case
            absolute_time_t cached_next_sample_time = next_sample_time;
            // we support being called from IRQ, so be careful about sleeping... still not
            // ideal, but not much that can be done
            if (in_exception) {
                busy_wait_until(next_sample_time);
            } else {
                sleep_until(next_sample_time);
            }
            spin_lock_t *lock = spin_lock_instance(PICO_SPINLOCK_ID_RAND);
            uint32_t save = spin_lock_blocking(lock);
            if (!absolute_time_diff_us(cached_next_sample_time, next_sample_time)) {
                // we won the race (if any) for the bit, so we collect it locally
                samples <<= 1;
                samples |= rosc_hw->randombit & 1u;
                // use of relative time to now, rather than offset from before makes things
                // a bit less predictable at the cost of some speed.
                next_sample_time = make_timeout_time_us(PICO_RAND_MIN_ROSC_BIT_SAMPLE_TIME_US);
                bit_done = true;
                if (i == n - 1) {
                    // samples has our random bits, so let's mix them in now
                    samples = rosc_samples = (rosc_samples << n) | samples;
                }
            }
            spin_unlock(lock, save);
        } while (!bit_done);
    }
    return samples;
}
#endif

static void initialise_rand(void) {
    rng_128_t local_rng_state = local_rng_state;
    uint which = 0;
#if PICO_RAND_SEED_ENTROPY_SRC_RAM_HASH
    ram_hash = sdbm_hash64_sram(ram_hash);
    local_rng_state.r[which] ^= splitmix64(ram_hash);
    which ^= 1;
#endif

#if PICO_RAND_SEED_ENTROPY_SRC_BOARD_ID
    static_assert(PICO_UNIQUE_BOARD_ID_SIZE_BYTES == sizeof(uint64_t),
                  "Code below requires that 'board_id' is 64-bits in size");

    // Note! The safety of the length assumption here is protected by a 'static_assert' above
    union unique_id_u {
        pico_unique_board_id_t board_id_native;
        uint64_t board_id_u64;
    } unique_id;
    // Note! The safety of the length assumption here is protected by a 'static_assert' above
    pico_get_unique_board_id(&unique_id.board_id_native);
    local_rng_state.r[which] ^= splitmix64(unique_id.board_id_u64);
    which ^= 1;
#endif

#if PICO_RAND_SEED_ENTROPY_SRC_ROSC
    // this is really quite slow (10ms per iteration), and I'm not sure that it adds value over the 64 random bits
//    uint ref_khz = clock_get_hz(clk_ref) / 100;
//    for (int i = 0; i < 5; i++) {
//        // Apply hash of the rosc frequency, limited but still 'extra' entropy
//        uint measurement = frequency_count_raw(CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC, ref_khz);
//        local_rng_state.r[which] ^= splitmix64(measurement);
//        (void) xoroshiro128ss(&local_rng_state);  //churn to mix seed sources
//    }

    // Gather a full ROSC sample array with sample bits
    local_rng_state.r[which] ^= splitmix64(capture_additional_rosc_samples(8 * sizeof(rosc_samples)));
    which ^= 1;
#endif

#if PICO_RAND_SEED_ENTROPY_SRC_TIME
    // Mix in hashed time.  This is [possibly] predictable boot-to-boot
    // but will vary application-to-application.
    local_rng_state.r[which] ^= splitmix64(time_us_64());
    which ^= 1;
#endif

    spin_lock_t *lock = spin_lock_instance(PICO_SPINLOCK_ID_RAND);
    uint32_t save = spin_lock_blocking(lock);
    if (!rng_initialised) {
#if PICO_RAND_ENTROPY_SRC_BUS_PERF_COUNTER
#if !PICO_RAND_BUSCTRL_COUNTER_INDEX
        int idx = -1;
        for(uint i = 0; i < count_of(bus_ctrl_hw->counter); i++) {
            if (bus_ctrl_hw->counter[i].sel == BUSCTRL_PERFSEL0_RESET) {
                idx = (int)i;
                break;
            }
        }
        hard_assert(idx != -1);
        bus_counter_idx = (uint8_t)idx;
#else
        bus_counter_idx = (uint8_t)PICO_RAND_BUSCTRL_COUNTER_INDEX;
#endif
        bus_ctrl_hw->counter[bus_counter_idx].sel = PICO_RAND_BUS_PERF_COUNTER_EVENT;
#endif
        (void) xoroshiro128ss(&local_rng_state);
        rng_state = local_rng_state;
        rng_initialised = true;
    }
    spin_unlock(lock, save);
}

uint64_t get_rand_64(void) {
    if (!rng_initialised) {
        // Do not provide 'RNs' until the system has been initialised.  Note:
        // The first initialisation can be quite time-consuming depending on
        // the amount of RAM hashed, see RAM_HASH_START and RAM_HASH_END
        initialise_rand();
    }

    static volatile uint8_t check_byte;
    rng_128_t local_rng_state = rng_state;
    uint8_t local_check_byte = check_byte;
    // Modify PRNG state with the run-time entropy sources,
    // hashed to reduce correlation with previous modifications.
    uint which = 0;
#if PICO_RAND_ENTROPY_SRC_TIME
    local_rng_state.r[which] ^= splitmix64(time_us_64());
    which ^= 1;
#endif
#if PICO_RAND_ENTROPY_SRC_ROSC
    local_rng_state.r[which] ^= splitmix64(capture_additional_rosc_samples(PICO_RAND_ROSC_BIT_SAMPLE_COUNT));
    which ^= 1;
#endif
#if PICO_RAND_ENTROPY_SRC_BUS_PERF_COUNTER
    uint32_t bus_counter_value = bus_ctrl_hw->counter[bus_counter_idx].value;
    // counter is saturating, so clear it if it has reached saturation
    if (bus_counter_value == BUSCTRL_PERFCTR0_BITS) {
        bus_ctrl_hw->counter[bus_counter_idx].value = 0;
    }
    local_rng_state.r[which] &= splitmix64(bus_counter_value);
    which ^= 1;
#endif

    spin_lock_t *lock = spin_lock_instance(PICO_SPINLOCK_ID_RAND);
    uint32_t save = spin_lock_blocking(lock);
    if (local_check_byte != check_byte) {
        // someone got a random number in the interim, so mix it in
        local_rng_state.r[0] ^= rng_state.r[0];
        local_rng_state.r[1] ^= rng_state.r[1];
    }
    // Generate a 64-bit RN from the modified PRNG state.
    // Note: This also "churns" the 128-bit state for next time.
    uint64_t rand64 = xoroshiro128ss(&local_rng_state);
    rng_state = local_rng_state;
    check_byte++;
    spin_unlock(lock, save);

    return rand64;
}

void get_rand_128(rng_128_t *ptr128) {
    ptr128->r[0] = get_rand_64();
    ptr128->r[1] = get_rand_64();
}

uint32_t get_rand_32(void) {
    return (uint32_t) get_rand_64();
}
