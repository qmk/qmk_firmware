#pragma once

#include "quantum.h"

// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
 #define LAYOUT_default( \
	K000,       K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013,             \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113,       K115, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213,       K215, \
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312,             K315, \
	K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411,       K413,       K415, \
	K500, K501, K502,             K505,                   K509, K510, K511, K512, K513,       K515  \
) { \
	{ K000,  KC_NO, K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  KC_NO,  KC_NO }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  KC_NO,  K115 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  KC_NO,  K215 }, \
	{ K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  KC_NO, KC_NO,  K315 }, \
	{ K400,  K401,  K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  KC_NO, K413,  KC_NO,  K415 }, \
	{ K500,  K501,  K502,  KC_NO, KC_NO, K505,  KC_NO, KC_NO, KC_NO, K509,  K510,  K511,  K512,  K513,  KC_NO,  K515 } \
}

/* screen off after this many milliseconds */
#define ScreenOffInterval 60000 /* milliseconds */

typedef union {
    uint8_t raw;
    struct {
        bool    enable :1;
        bool    breathing : 1;
        uint8_t level  :6;
    };
} backlight_config_t;

// Start these at the USER code range in VIA
enum my_keycodes {
  ENC_PRESS = 0x5F80,
  CLOCK_SET,
  OLED_TOGG
};

enum encoder_modes {
  ENC_MODE_VOLUME,
  ENC_MODE_MEDIA,
  ENC_MODE_SCROLL,
  ENC_MODE_BRIGHTNESS,
  ENC_MODE_BACKLIGHT,
  ENC_MODE_CUSTOM0,
  ENC_MODE_CUSTOM1,
  ENC_MODE_CUSTOM2,
  _NUM_ENCODER_MODES,
  ENC_MODE_CLOCK_SET // This shouldn't be included in the default modes, so we put it after NUM_ENCODER_MODES
};

enum oled_modes {
  OLED_DEFAULT,
  OLED_TIME,
  OLED_OFF,
  _NUM_OLED_MODES
};


// Keyboard Information
extern volatile uint8_t led_numlock;
extern volatile uint8_t led_capslock;
extern volatile uint8_t led_scrolllock;
extern uint8_t layer;

// OLED Behavior
extern uint16_t last_flush;
extern bool queue_for_send;
extern uint8_t oled_mode;
extern bool oled_sleeping;

// Encoder Behavior
extern uint8_t encoder_value;
extern uint8_t encoder_mode;
extern uint8_t enabled_encoder_modes;

// RTC
extern RTCDateTime last_timespec;
extern uint16_t last_minute;

// RTC Configuration
extern bool clock_set_mode;
extern uint8_t time_config_idx;
extern int8_t hour_config;
extern int16_t minute_config;
extern int8_t year_config;
extern int8_t month_config;
extern int8_t day_config;
extern uint8_t previous_encoder_mode;

// Backlighting
extern backlight_config_t kb_backlight_config;
extern bool kb_backlight_breathing;

void pre_encoder_mode_change(void);
void post_encoder_mode_change(void);
void change_encoder_mode(bool negative);
uint16_t handle_encoder_clockwise(void);
uint16_t handle_encoder_ccw(void);
uint16_t handle_encoder_press(void);

void update_time_config(int8_t increment);

__attribute__ ((weak))
void draw_ui(void);
void draw_default(void);
void draw_clock(void);

void backlight_init_ports(void);
void backlight_set(uint8_t level);
bool is_breathing(void);
void breathing_enable(void);
void breathing_disable(void);
// void backlight_save_to_eeprom(uint8_t level);
// uint8_t backlight_config_load();
