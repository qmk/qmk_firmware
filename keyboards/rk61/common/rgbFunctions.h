#pragma once

#ifndef RGB_FUNCTIONS_H
#define RGB_FUNCTIONS_H

#include "quantum.h"        // Include QMK core functionalities

#define RGB_UNSET (RGB){0xFF, 0xFF, 0xFF} // Special value indicating "unset"

#define FN_KEYS_COUNT 12
#define RGB_KEYS_COUNT 7
#define NAV_COUNT 6        
#define MEDIA_LED_COUNT 12

typedef struct {
    uint8_t index;
    RGB color; // Use RGB_UNSET to indicate "use default"
} led_color_t;

// Define nav_keys as an extern array
extern const led_color_t fn_keys[];
extern const led_color_t rgb_keys[];
extern const led_color_t nav_keys[];
extern const led_color_t media_keys[];

void setRgbForKeys(layer_state_t layer, const led_color_t *keys, uint8_t key_count, RGB default_color);
void setRgbForWinKeyIndicator(void);
void setRgbForCapsLockIndicator(void);
void setRgbForFnLayer(void);

#endif