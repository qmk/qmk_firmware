#ifndef RGB_BACKLIGHT_H
#define RGB_BACKLIGHT_H

#if BACKLIGHT_ENABLED
#else
#error rgb_backlight.h included when BACKLIGHT_ENABLED == 0
#endif // BACKLIGHT_ENABLED

#include <stdint.h>
#include <stdbool.h>

#include "quantum/color.h"

typedef struct
{
	HSV color;
	uint8_t index;
} backlight_config_indicator;

typedef struct
{
	bool use_split_backspace:1;         // |
	bool use_split_left_shift:1;        // |
	bool use_split_right_shift:1;       // |
	bool use_7u_spacebar:1;             // |
	bool use_iso_enter:1;               // |
	bool disable_when_usb_suspended:1;  // |
	bool disable_hhkb_blocker_leds:1;   // |
	bool __pad7:1;                      // 1 byte
	uint8_t disable_after_timeout;      // 1 byte
	uint8_t brightness;                 // 1 byte
	uint8_t effect;                     // 1 byte
	uint8_t effect_speed;				// 1 byte
	HSV color_1;                        // 3 bytes
	HSV color_2;                        // 3 bytes
	backlight_config_indicator caps_lock_indicator;	// 4 bytes
	backlight_config_indicator layer_1_indicator;	// 4 bytes
	backlight_config_indicator layer_2_indicator;	// 4 bytes
	backlight_config_indicator layer_3_indicator;	// 4 bytes
	uint16_t alphas_mods[5];            // 10 bytes
} backlight_config;                // = 37 bytes

void backlight_config_set_alphas_mods( uint16_t *value );
void backlight_config_load(void);
void backlight_config_save(void);
void backlight_config_set_value( uint8_t *data );
void backlight_config_get_value( uint8_t *data );

void backlight_init_drivers(void);

void backlight_timer_init(void);
void backlight_timer_enable(void);
void backlight_timer_disable(void);

void backlight_set_suspend_state(bool state);
void backlight_set_indicator_state(uint8_t state);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void backlight_update_pwm_buffers(void);

// Handle backlight specific keycodes
bool process_record_backlight(uint16_t keycode, keyrecord_t *record);

void backlight_set_key_hit(uint8_t row, uint8_t col);

void backlight_effect_increase(void);
void backlight_effect_decrease(void);
void backlight_effect_speed_increase(void);
void backlight_effect_speed_decrease(void);

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

void backlight_test_led( uint8_t index, bool red, bool green, bool blue );
uint32_t backlight_get_tick(void);
void backlight_debug_led(bool state);

#endif //RGB_BACKLIGHT_H
