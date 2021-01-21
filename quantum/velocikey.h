#pragma once

#include <stdint.h>
#include <stdbool.h>

bool    velocikey_enabled(void);
void    velocikey_toggle(void);
void    velocikey_set_typing_speed(uint8_t new_typing_speed);
uint8_t velocikey_get_typing_speed(void);
void    velocikey_accelerate(void);
void    velocikey_decelerate(void);
uint8_t velocikey_match_speed(uint8_t minValue, uint8_t maxValue);
