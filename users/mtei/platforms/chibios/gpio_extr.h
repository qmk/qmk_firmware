#pragma once

/* Operation of GPIO by port. */

#ifdef PAL_MODE_OUTPUT_OPENDRAIN
#    ifdef PAL_STM32_PUPDR_PULLUP
#        define PAL_MODE_OUTPUT_OPENDRAIN_PULLUP (PAL_MODE_OUTPUT_OPENDRAIN | PAL_STM32_PUPDR_PULLUP)
#    endif
#endif

#if PAL_IOPORTS_WIDTH == 16
typedef uint16_t port_data_t;
#endif
#if PAL_IOPORTS_WIDTH == 32
typedef uint32_t port_data_t;
#endif

#ifndef readPort
#    define readPort(pin) palReadPort(PAL_PORT(pin))
#endif // readPort

#ifndef setPortBitInput
#    define setPortBitInput(pin, bit) palSetPadMode(PAL_PORT(pin), (bit), PAL_MODE_INPUT)
#    define setPortBitInputHigh(pin, bit) palSetPadMode(PAL_PORT(pin), (bit), PAL_MODE_INPUT_PULLUP)
#    define setPortBitInputLow(pin, bit) palSetPadMode(PAL_PORT(pin), (bit), PAL_MODE_INPUT_PULLDOWN)

#    define setPortBitOutputPushPull(pin, bit) palSetPadMode(PAL_PORT(pin), (bit), PAL_MODE_OUTPUT_PUSHPULL)
#    define setPortBitOutput(pin, bit) setPortBitOutputPushPull(pin, bit)

#    ifdef PAL_MODE_OUTPUT_OPENDRAIN
#        define setPortBitOutputOpenDrain(pin, bit) palSetPadMode(PAL_PORT(pin), (bit), PAL_MODE_OUTPUT_OPENDRAIN)
#    endif
#    ifdef PAL_MODE_OUTPUT_OPENDRAIN_PULLUP
#        define setPortBitOutputOpenDrainPullup(pin, bit) palSetPadMode(PAL_PORT(pin), (bit), PAL_MODE_OUTPUT_OPENDRAIN_PULLUP)
#    endif

#    define writePortBitLow(pin, bit) palClearLine(PAL_LINE(PAL_PORT(pin), (bit)))
#    define writePortBitHigh(pin, bit) palSetLine(PAL_LINE(PAL_PORT(pin), (bit)))
#endif // setPortBitInput

#ifndef setPortBunchInput
#    define setPortBunchInput(port, bunch) palSetGroupMode_wrap(PAL_PORT(port), (bunch), 0, PAL_MODE_INPUT)
#    define setPortBunchInputHigh(port, bunch) palSetGroupMode_wrap(PAL_PORT(port), (bunch), 0, PAL_MODE_INPUT_PULLUP)

#    define setPortBunchOutputPusuPull(port, bunch) palSetGroupMode_wrap(PAL_PORT(port), (bunch), 0, PAL_MODE_OUTPUT_PUSHPULL)
#    define setPortBunchOutput(port, bunch) setPortBunchOutputPusuPull(port, bunch)

#    ifdef PAL_MODE_OUTPUT_OPENDRAIN
#        define setPortBunchOutputOpenDrain(port, bunch) palSetGroupMode_wrap(PAL_PORT(port), (bunch), 0, PAL_MODE_OUTPUT_OPENDRAIN)
#    endif
#    ifdef PAL_MODE_OUTPUT_OPENDRAIN_PULLUP
#        define setPortBunchOutputOpenDrainPullup(port, bunch) palSetGroupMode_wrap(PAL_PORT(port), (bunch), 0, PAL_MODE_OUTPUT_OPENDRAIN_PULLUP)
#    endif

#    define writePortBunchLow(port, bunch) palWriteGroup(PAL_PORT(port), (bunch), 0, 0)
#    define writePortBunchHigh(port, bunch) palWriteGroup(PAL_PORT(port), (bunch), 0, (bunch))

#    define palSetGroupMode_wrap(port, bunch, offset, mode) palSetGroupMode((port), (bunch), (offset), (mode))

// ChibiOS's GPIO implementation for RP2040 doesn't seem to implement palSetGroupMode(),
// so as a workaround, use the implementation below.
#    ifndef pal_lld_setgroupmode
//#        pragma message "Use alternate palSetGroupMode"
#        undef palSetGroupMode_wrap

#        define palSetGroupMode_wrap(port, mask, offset, mode)           \
                palSetGroupMode_impl((port), (mask), (offset), (mode))
#        define palSetGroupMode_impl(port, mask, offset, mode)           \
                _palSetGroupMode_impl((port), ((mask) << (offset)), (mode))

static inline void _palSetGroupMode_impl(ioportid_t port, ioportmask_t mask, iomode_t mode) {
    iopadid_t pad = 0;

    while (((mask) & 0xff) == 0) {
        pad += 8;
        mask = mask >> 8;
    }
    while (mask != 0) {
        while (((mask) & 0xf) == 0) {
            pad += 4;
            mask = mask >> 4;
        }
        if ((mask & 1) != 0) {
            palSetPadMode(port, pad, mode);
        }
        pad ++;
        mask = mask >> 1;
    }
}
#    endif // ifndef pal_lld_setgroupmode
#endif // setPortBunchInput
