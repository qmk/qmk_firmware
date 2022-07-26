#pragma once

/* Operation of GPIO by port. */

#ifndef readPort

#ifdef PAL_MODE_OUTPUT_OPENDRAIN
#    ifdef PAL_STM32_PUPDR_PULLUP
#        define PAL_MODE_OUTPUT_OPENDRAIN_PULLUP (PAL_MODE_OUTPUT_OPENDRAIN | PAL_STM32_PUPDR_PULLUP)
#    endif
#endif

typedef uint16_t port_data_t;

#define readPort(pin) palReadPort(PAL_PORT(pin))

#define setPortBitInput(pin, bit) palSetPadMode(PAL_PORT(pin), (bit), PAL_MODE_INPUT)
#define setPortBitInputHigh(pin, bit) palSetPadMode(PAL_PORT(pin), (bit), PAL_MODE_INPUT_PULLUP)
#define setPortBitInputLow(pin, bit) palSetPadMode(PAL_PORT(pin), (bit), PAL_MODE_INPUT_PULLDOWN)

#define setPortBitOutputPushPull(pin, bit) palSetPadMode(PAL_PORT(pin), (bit), PAL_MODE_OUTPUT_PUSHPULL)
#define setPortBitOutput(pin, bit) setPortBitOutputPushPull(pin, bit)

#ifdef PAL_MODE_OUTPUT_OPENDRAIN
#    define setPortBitOutputOpenDrain(pin, bit) palSetPadMode(PAL_PORT(pin), (bit), PAL_MODE_OUTPUT_OPENDRAIN)
#endif
#ifdef PAL_MODE_OUTPUT_OPENDRAIN_PULLUP
#    define setPortBitOutputOpenDrainPullup(pin, bit) palSetPadMode(PAL_PORT(pin), (bit), PAL_MODE_OUTPUT_OPENDRAIN_PULLUP)
#endif

#define writePortBitLow(pin, bit) palClearLine(PAL_LINE(PAL_PORT(pin), (bit)))
#define writePortBitHigh(pin, bit) palSetLine(PAL_LINE(PAL_PORT(pin), (bit)))

#define setPortBunchInput(port, bunch) palSetGroupMode(PAL_PORT(port), (bunch), 0, PAL_MODE_INPUT)
#define setPortBunchInputHigh(port, bunch) palSetGroupMode(PAL_PORT(port), (bunch), 0, PAL_MODE_INPUT_PULLUP)

#define setPortBunchOutputPusuPull(port, bunch) palSetGroupMode(PAL_PORT(port), (bunch), 0, PAL_MODE_OUTPUT_PUSHPULL)
#define setPortBunchOutput(port, bunch) setPortBunchOutputPusuPull(port, bunch)

#ifdef PAL_MODE_OUTPUT_OPENDRAIN
#    define setPortBunchOutputOpenDrain(port, bunch) palSetGroupMode(PAL_PORT(port), (bunch), 0, PAL_MODE_OUTPUT_OPENDRAIN)
#endif
#ifdef PAL_MODE_OUTPUT_OPENDRAIN_PULLUP
#    define setPortBunchOutputOpenDrainPullup(port, bunch) palSetGroupMode(PAL_PORT(port), (bunch), 0, PAL_MODE_OUTPUT_OPENDRAIN_PULLUP)
#endif

#define writePortBunchLow(port, bunch) palWriteGroup(PAL_PORT(port), (bunch), 0, 0)
#define writePortBunchHigh(port, bunch) palWriteGroup(PAL_PORT(port), (bunch), 0, (bunch))

#endif // ifndef readPort
