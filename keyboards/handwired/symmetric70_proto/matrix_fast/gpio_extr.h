#pragma once
// clang-format off

#if defined(__AVR__)
typedef uint8_t     port_data_t;

#define readPort(port)                 PINx_ADDRESS(port)

#define setPortBitInput(port, bit)     (DDRx_ADDRESS(port) &= ~_BV((bit)&0xF), PORTx_ADDRESS(port) &= ~_BV((bit)&0xF))
#define setPortBitInputHigh(port, bit) (DDRx_ADDRESS(port) &= ~_BV((bit)&0xF), PORTx_ADDRESS(port) |= _BV((bit)&0xF))
#define setPortBitOutput(port, bit)    (DDRx_ADDRESS(port) |= _BV((bit)&0xF))

#define writePortBitLow(port, bit)     (PORTx_ADDRESS(port) &= ~_BV((bit)&0xF))
#define writePortBitHigh(port, bit)    (PORTx_ADDRESS(port) |= _BV((bit)&0xF))

#else
typedef uint16_t     port_data_t;

#define readPort(qmk_pin)                 palReadPort(PAL_PORT(qmk_pin))

#define setPortBitInput(qmk_pin, bit)     palSetPadMode(PAL_PORT(qmk_pin), bit, PAL_MODE_INPUT)
#define setPortBitInputHigh(qmk_pin, bit) palSetPadMode(PAL_PORT(qmk_pin), bit, PAL_MODE_INPUT_PULLUP)
#define setPortBitInputLow(qmk_pin, bit)  palSetPadMode(PAL_PORT(qmk_pin), bit, PAL_MODE_INPUT_PULLDOWN)
#define setPortBitOutput(qmk_pin, bit)    palSetPadMode(PAL_PORT(qmk_pin), bit, PAL_MODE_OUTPUT_PUSHPULL)

#define writePortBitLow(qmk_pin, bit)     palClearLine(PAL_LINE(PAL_PORT(qmk_pin), bit))
#define writePortBitHigh(qmk_pin, bit)    palSetLine(PAL_LINE(PAL_PORT(qmk_pin), bit))
#endif
