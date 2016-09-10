#ifndef WAIT_H
#define WAIT_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__AVR__)
#   include <util/delay.h>
#   define wait_ms(ms)  _delay_ms(ms)
#   define wait_us(us)  _delay_us(us)
#elif defined(PROTOCOL_CHIBIOS) /* __AVR__ */
#   include "ch.h"
#   define wait_ms(ms) chThdSleepMilliseconds(ms)
#   define wait_us(us) chThdSleepMicroseconds(us)
#elif defined(__arm__) /* __AVR__ */
#   include "wait_api.h"
#endif /* __AVR__ */

#ifdef __cplusplus
}
#endif

#endif
