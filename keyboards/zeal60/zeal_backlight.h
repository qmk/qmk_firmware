#ifndef ZEAL_BACKLIGHT_H
#define ZEAL_BACKLIGHT_H

#include <stdint.h>
#include <stdbool.h>

#include "zeal_color.h"
#include "zeal_rpc.h"

typedef struct
{
	HSV color;
	uint8_t index;
} zeal_indicator;

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
	zeal_indicator caps_lock_indicator;	// 4 bytes
	zeal_indicator layer_1_indicator;	// 4 bytes
	zeal_indicator layer_2_indicator;	// 4 bytes
	zeal_indicator layer_3_indicator;	// 4 bytes
	uint16_t alphas_mods[5];            // 10 bytes
} zeal_backlight_config;                // = 37 bytes

void backlight_config_set_values(msg_backlight_config_set_values *values);
void backlight_config_set_alphas_mods( uint16_t *value );
void backlight_config_load(void);
void backlight_config_save(void);

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



void *backlight_get_key_color_eeprom_address(uint8_t led);
void backlight_get_key_color( uint8_t led, HSV *hsv );
void backlight_set_key_color( uint8_t row, uint8_t column, HSV hsv );

void backlight_test_led( uint8_t index, bool red, bool green, bool blue );
uint32_t backlight_get_tick(void);
void backlight_debug_led(bool state);

#endif //ZEAL_BACKLIGHT_H
