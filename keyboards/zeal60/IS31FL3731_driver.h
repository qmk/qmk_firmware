#ifndef IS31FL3731_DRIVER_H
#define IS31FL3731_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

void IS31FL3731_init( uint8_t addr );
void IS31FL3731_write_register( uint8_t addr, uint8_t reg, uint8_t data );
void IS31FL3731_write_pwm_buffer( uint8_t addr, uint8_t *pwm_buffer );

void IS31FL3731_set_color( int index, uint8_t red, uint8_t green, uint8_t blue );
void IS31FL3731_set_color_all( uint8_t red, uint8_t green, uint8_t blue );

void IS31FL3731_set_led_control_register( uint8_t index, bool red, bool green, bool blue );

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void IS31FL3731_update_pwm_buffers( uint8_t addr1, uint8_t addr2 );
void IS31FL3731_update_led_control_registers( uint8_t addr1, uint8_t addr2 );

#endif // IS31FL3731_DRIVER_H
