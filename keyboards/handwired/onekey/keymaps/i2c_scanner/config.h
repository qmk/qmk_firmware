#pragma once

// AVR: can change to other supported values
#ifdef __AVR__
#   define F_SCL 100000UL
#endif

#ifdef PROTOCOL_CHIBIOS
#   define I2C1_CLOCK_SPEED 100000
#   define I2C1_DUTY_CYCLE STD_DUTY_CYCLE
#endif
