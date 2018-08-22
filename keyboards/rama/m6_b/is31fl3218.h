#ifndef IS31FL3218_H
#define IS31FL3218_H

#include <stdint.h>
#include <stdbool.h>

void IS31FL3218_init(void);
void IS31FL3218_set_color( int index, uint8_t red, uint8_t green, uint8_t blue );
void IS31FL3218_set_color_all( uint8_t red, uint8_t green, uint8_t blue );
void IS31FL3218_update_pwm_buffers(void);

#endif // IS31FL3218_H
