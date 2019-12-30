/* Copyright 2019 Rys Sommefeldt
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

/*
 * LED ranges
 * ┌─────────────┬─────────────┬───────────────────────────────────────────┐
 * │ 00 01 02 03 │ 04 05 06 07 │ 08 09 10 11 12 13 14 15 16 17 18 19 20 21 │
 * │   escape    │    badge    │              underglow                    │
 * └─────────────┴─────────────┴───────────────────────────────────────────┘
 */

// Define the LED ranges                  start, end
#define THINK65_LED_RANGE_OFF                 0, 0
#define THINK65_LED_RANGE_ESC                 0, 4
#define THINK65_LED_RANGE_BADGE               4, 8
#define THINK65_LED_RANGE_UNDERGLOW           8, 22
#define THINK65_LED_RANGE_ALL                 0, 22

// Turn the LEDs off by setting HSV to 0, 0, 0
#define THINK65_LEDS_OFF                      0, 0, 0

// There are 3 ranges, so we can store all combinations in 2^3 values
// Define all of them to make it easier to write the cycling code
#define THINK65_LED_STATE_OFF                 0x0 // 0b00000000
#define THINK65_LED_STATE_ESC                 0x1 // 0b00000001
#define THINK65_LED_STATE_BADGE               0x2 // 0b00000010
#define THINK65_LED_STATE_UNDERGLOW           0x4 // 0b00000100
#define THINK65_LED_STATE_ESC_AND_BADGE       0x3 // 0b00000011
#define THINK65_LED_STATE_ESC_AND_UNDERGLOW   0x5 // 0b00000101
#define THINK65_LED_STATE_BADGE_AND_UNDERGLOW 0x6 // 0b00000110
#define THINK65_LED_STATE_ON                  0x7 // 0b00000111

// Define each LED range as a bit flag
#define THINK65_LED_ESC_RANGE_BIT             0
#define THINK65_LED_BADGE_RANGE_BIT           1
#define THINK65_LED_UNDERGLOW_RANGE_BIT       2

// Define a magic byte value to help protect us from other users overwriting our EEPROM space
#define THINK65_LED_EEPROM_MAGIC_BYTE         0x52

// Define where in user EEPROM we want to start saving the per-range colour values
// eeconfig values currently stop at byte 33, so in theory we could use byte 34 onwards
// but let's pick something nice and high since we've got 1024 bytes on an atmega32u4
#define THINK65_LED_EEPROM_BASE_ADDR          (uint8_t *)128
#define THINK65_LED_EEPROM_MAGIC_ADDR         0
#define THINK65_LED_EEPROM_ESC_ADDR           1
#define THINK65_LED_EEPROM_BADGE_ADDR         4
#define THINK65_LED_EEPROM_UNDERGLOW_ADDR     7
#define THINK65_LED_EEPROM_H_BYTE             0
#define THINK65_LED_EEPROM_S_BYTE             1
#define THINK65_LED_EEPROM_V_BYTE             2

// setup the user EEPROM space we need
typedef union {
    uint8_t raw;
    struct {
        uint8_t current_led_state:8;
    };
} user_config_t;

user_config_t user_config;

// setup a struct to hold the data we save into EEPROM for the per-range colours
typedef struct Think65_LED_Config {
    uint8_t esc_h;
    uint8_t esc_s;
    uint8_t esc_v;
    uint8_t badge_h;
    uint8_t badge_s;
    uint8_t badge_v;
    uint8_t underglow_h;
    uint8_t underglow_s;
    uint8_t underglow_v;
} Think65_LED_Config;

Think65_LED_Config think65_led_config;

// Range control setup
void setup_led_range_control(void);

// magic value read/write
bool is_magic_valid(void);
void set_magic_value(void);
uint8_t read_magic_value(void);

// clear/read/set LED config in user EEPROM
void clear_led_config(void);
void read_led_config(void);
void save_led_config(void);
void print_led_config(void);

// LED state API
void toggle_led_state(unsigned int led_range);
void set_led_state(unsigned int led_range);
void clear_led_state(unsigned int led_range);
void cycle_led_state(void);
void apply_led_state(void);

// Setup some keycodes to control cycling and range toggling
enum think65_led_keycodes {
    CYC_LED = SAFE_RANGE,
    // Range toggle
    TOG_ESC,
    TOG_BDG,
    TOG_UGL,
    // Escape range HSV
    ESC_HUI,
    ESC_HUD,
    ESC_SAI,
    ESC_SAD,
    ESC_VAI,
    ESC_VAD,
    // Badge range HSV
    BDG_HUI,
    BDG_HUD,
    BDG_SAI,
    BDG_SAD,
    BDG_VAI,
    BDG_VAD,
    // Underglow range HSV
    UGL_HUI,
    UGL_HUD,
    UGL_SAI,
    UGL_SAD,
    UGL_VAI,
    UGL_VAD,
    // New SAFE_RANGE
    THINK65_SAFE_RANGE
};

// Handle the custom LED range control keycodes
bool process_led_range_control_codes(uint16_t keycode, keyrecord_t *record);
