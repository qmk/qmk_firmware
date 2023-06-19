#pragma once

#include "quantum.h"

#include "via.h" // only for EEPROM address
#define EEPROM_ENABLED_ENCODER_MODES (VIA_EEPROM_CUSTOM_CONFIG_ADDR)
#define EEPROM_CUSTOM_BACKLIGHT (VIA_EEPROM_CUSTOM_CONFIG_ADDR+1)
#define EEPROM_DEFAULT_OLED (VIA_EEPROM_CUSTOM_CONFIG_ADDR+2)
#define EEPROM_CUSTOM_ENCODER (VIA_EEPROM_CUSTOM_CONFIG_ADDR+3)

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

enum s75_keyboard_value_id {
  id_encoder_modes = 0x80,
  id_oled_default_mode,
  id_encoder_custom,
  id_oled_mode
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

enum custom_encoder_behavior {
    ENC_CUSTOM_CW = 0,
    ENC_CUSTOM_CCW,
    ENC_CUSTOM_PRESS
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
extern uint8_t oled_mode;
extern bool oled_repaint_requested;
extern bool oled_wakeup_requested;
extern uint32_t oled_sleep_timer;

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
uint16_t retrieve_custom_encoder_config(uint8_t encoder_idx, uint8_t behavior);
void set_custom_encoder_config(uint8_t encoder_idx, uint8_t behavior, uint16_t new_code);

void update_time_config(int8_t increment);

void oled_request_wakeup(void);
void oled_request_repaint(void);
bool oled_task_needs_to_repaint(void);

void backlight_init_ports(void);
void backlight_set(uint8_t level);
bool is_breathing(void);
void breathing_enable(void);
void breathing_disable(void);
void custom_config_load(void);
void backlight_config_save(void);

#define ____ KC_NO
#define LAYOUT_all( \
	K000,       K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, \
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, K314, \
	K400,       K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, K413, K414, \
	K500, K501, K502,                   K506,                   K510, K511, K512, K513, K514  \
) { \
	{ K000,  ____,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  ____ }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  K214 }, \
	{ K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  ____,  K313,  K314 }, \
	{ K400,  ____,  K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412,  K413,  K414 }, \
	{ K500,  K501,  K502,  ____,  ____,  ____,  K506,  ____,  ____,  ____,  K510,  K511,  K512,  K513,  K514 } \
}
