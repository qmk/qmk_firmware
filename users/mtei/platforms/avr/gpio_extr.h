#pragma once

#include "pin_defs_extr.h"

/* Operation of GPIO by port. */

#ifndef readPort

typedef uint8_t port_data_t;
typedef uint16_t port_addr_t;

#define cmpPortAdr(pin1,pin2) ((&PINx_ADDRESS(pin1))==(&PINx_ADDRESS(pin2)))
#define getBitInPort(pin)     ((uint8_t)(((uint16_t)(pin))&0xF))

#define readPort(port) PINx_ADDRESS(port)

#define setPortBitInput(port, bit) (DDRx_ADDRESS(port) &= ~_BV((bit)&0xF), PORTx_ADDRESS(port) &= ~_BV((bit)&0xF))
#define setPortBitInputHigh(port, bit) (DDRx_ADDRESS(port) &= ~_BV((bit)&0xF), PORTx_ADDRESS(port) |= _BV((bit)&0xF))
#define setPortBitInputLow(pin) _Static_assert(0, "AVR processors cannot implement an input as pull low")

#define setPortBitOutputPushPull(port, bit) (DDRx_ADDRESS(port) |= _BV((bit)&0xF))
#define setPortBitOutputOpenDrain(pin) _Static_assert(0, "AVR platform does not implement an open-drain output")
#define setPortBitOutput(port, bit) setPortBitOutputPushPull(port, bit)

#define writePortBitLow(port, bit) (PORTx_ADDRESS(port) &= ~_BV((bit)&0xF))
#define writePortBitHigh(port, bit) (PORTx_ADDRESS(port) |= _BV((bit)&0xF))

#define setPortBunchInput(port, bunch) (DDRx_ADDRESS(port) &= ~(bunch), PORTx_ADDRESS(port) &= ~(bunch))
#define setPortBunchInputHigh(port, bunch) (DDRx_ADDRESS(port) &= ~(bunch), PORTx_ADDRESS(port) |= (bunch))

#define setPortBunchOutputPusuPull(port, bunch) (DDRx_ADDRESS(port) |= (bunch))
#define setPortBunchOutput(port, bunch) setPortBunchOutputPusuPull(port, bunch)

#define writePortBunchLow(port, bunch) (PORTx_ADDRESS(port) &= ~(bunch))
#define writePortBunchHigh(port, bunch) (PORTx_ADDRESS(port) |= (bunch))

#endif // ifndef readPort
