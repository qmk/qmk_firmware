 /* Copyright 2021 OpenAnnePro community
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#pragma once

#include "protocol.h"

// Struct defining an LED and its RGB color components
// Compatible with Shine firmware.
typedef union {
    struct {
        /* Little endian ordering to match uint32_t */
        uint8_t blue, green, red;
        /* Used in mask; nonzero means - use color from mask. */
        uint8_t alpha;
    } p; /* parts */
    /* Parts vector access: 0 - blue, 1 - green, 2 - red */
    uint8_t pv[4];
    /* 0xrgb in mem is b g r a */
    uint32_t rgb;
} ap2_led_t;

#define ROWCOL2IDX(row, col) (NUM_COLUMN * (row) + (col))
#define NUM_COLUMN 14
#define NUM_ROW 5
#define KEY_COUNT 70

/* Local copy of led_mask, used to override colors on the board */
extern ap2_led_t led_mask[KEY_COUNT];
extern ap2_led_t led_colors[KEY_COUNT];
extern uint8_t rgb_row_changed[NUM_ROW];

/* Handle incoming messages */
extern void led_command_callback(const message_t *msg);

void ap2_set_IAP(void);
void ap2_led_disable(void);
void ap2_led_enable(void);
void ap2_led_set_profile(uint8_t prof);
void ap2_led_get_status(void);
void ap2_led_next_profile(void);
void ap2_led_prev_profile(void);
void ap2_led_next_intensity(void);
void ap2_led_next_animation_speed(void);
void ap2_led_forward_keypress(uint8_t row, uint8_t col);

/* Set single key to a given color; alpha controls which is displayed */
void ap2_led_mask_set_key(uint8_t row, uint8_t col, ap2_led_t color);
/* Push a whole local row to the shine */
void ap2_led_mask_set_row(uint8_t row);
/* Synchronize all rows */
void ap2_led_mask_set_all(void);

/* Set all keys to a given color */
void ap2_led_mask_set_mono(ap2_led_t color);

/* Set single key to a given color; alpha controls which is displayed */
void ap2_led_colors_set_key(uint8_t row, uint8_t col, ap2_led_t color);
/* Push a whole local row to the shine */
void ap2_led_colors_set_row(uint8_t row);
/* Synchronize all rows */
void ap2_led_colors_set_all(void);

/* Set all keys to a given color */
void ap2_led_colors_set_mono(ap2_led_t color);

void ap2_led_set_manual_control(uint8_t manual);

/* Blink given key `count` times by masking it with a `color`. Blink takes `hundredths` of a second */
void ap2_led_blink(uint8_t row, uint8_t col, ap2_led_t color, uint8_t count, uint8_t hundredths);

/* Kept for compatibility, but implemented using masks */
void ap2_led_set_foreground_color(uint8_t red, uint8_t green, uint8_t blue);
void ap2_led_reset_foreground_color(void);

typedef struct {
    uint8_t amount_of_profiles;
    uint8_t current_profile;
    uint8_t matrix_enabled;
    uint8_t is_reactive;
    uint8_t led_intensity;
    uint8_t errors;
} ap2_led_status_t;

extern ap2_led_status_t ap2_led_status;

#ifdef RGB_MATRIX_ENABLE
/* RGB driver functions */
void init(void);
void flush(void);
void set_color(int index, uint8_t r, uint8_t g, uint8_t b);
void set_color_all(uint8_t r, uint8_t g, uint8_t b);
#endif
