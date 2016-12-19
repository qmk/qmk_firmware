#ifndef ZEAL_BACKLIGHT_H
#define ZEAL_BACKLIGHT_H

#include <stdint.h>
#include <stdbool.h>

#include "zeal_color.h"

typedef struct zeal_backlight_config
{
	bool use_split_backspace:1;
	bool use_split_left_shift:1;
	bool use_split_right_shift:1;
	bool use_7u_spacebar:1;
	bool use_iso_enter:1;
	uint16_t alphas_mods[5];
	uint8_t brightness;
	uint8_t effect;

	HSV color_1;
	HSV color_2;
} zeal_backlight_config;

void backlight_config_set_flags(uint8_t value);
void backlight_config_set_alphas_mods( uint16_t *value );
void backlight_config_load(void);
void backlight_config_save(void);

void backlight_init_drivers(void);

void backlight_timer_init(void);
void backlight_timer_enable(void);
void backlight_timer_disable(void);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void backlight_update_pwm_buffers(void);

void backlight_set_key_hit(uint8_t row, uint8_t col);

void backlight_effect_increase(void);
void backlight_effect_decrease(void);

void backlight_brightness_increase(void);
void backlight_brightness_decrease(void);

void backlight_color_1_hue_increase(void);
void backlight_color_1_hue_decrease(void);
void backlight_color_1_sat_increase(void);
void backlight_color_1_sat_decrease(void);
void backlight_color_2_hue_increase(void);
void backlight_color_2_hue_decrease(void);
void backlight_color_2_sat_increase(void);
void backlight_color_2_sat_decrease(void);

void *backlight_get_key_color_eeprom_address(uint8_t led);
void backlight_get_key_color( uint8_t led, HSV *hsv );
void backlight_set_key_color( uint8_t row, uint8_t col, HSV hsv );

#endif //ZEAL_BACKLIGHT_H
