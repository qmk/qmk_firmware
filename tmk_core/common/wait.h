#ifndef WAIT_H
#define WAIT_H

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__AVR__)
    #include <util/delay.h>
    #define wait_ms(ms)  _delay_ms(ms)
    #define wait_us(us)  _delay_us(us)
#elif defined(PROTOCOL_CHIBIOS)
    #include "ch.h"
    // millisecond-order sleep will sleep the thread
    #define wait_ms(ms) chThdSleepMilliseconds(ms)
    #if defined(CH_HT32_WAIT_US_POLL) && (CH_HT32_WAIT_US_POLL == TRUE)
        // microsecond-order sleep will poll a one-shot counter
        #define wait_us(us) gptPolledDelay(&GPTD_BFTM0, us)
    #else
        #define wait_us(us) chThdSleepMicroseconds(us)
    #endif
#elif defined(__arm__)
    #include "wait_api.h"
#else  // Unit tests
void wait_ms(uint32_t ms);
#define wait_us(us) wait_ms(us / 1000)
#endif

#ifdef __cplusplus
}
#endif

#endif
