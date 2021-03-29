#pragma once

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

#define EECONFIG_USERSPACE (uint8_t *)20

#define SYMBOL      MO(1)
#define MEDIA       MO(2)
#define ARROW       MO(3)
#define FUNCT       MO(4)
#define KEEB        MO(5)

#define MOD_CTL_MASK (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL))
#define MOD_GUI_MASK (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI))
#define MOD_SFT_MASK (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))

#define LED_FLASH_DELAY       150

#define ACCEL_DELAY           500
#define DEACCEL_DELAY         500

#define INACTIVE_DELAY        250
#define SLEEP_DELAY           180000

#define HUE_MAX               254

enum {
  _QWERTY = 0,
  _SYMBOL,
  _MEDIA,
  _ARROW,
  _FUNCT,
  _KEEB,
};

typedef enum {
  OS_MAC, // Don't assign values
  OS_WIN,
  OS_NIX,
  _OS_COUNT,
} OS;

typedef struct {
  uint16_t  h;
  uint8_t   s;
  uint8_t   v;
} Color;

typedef enum {
  no_flash = 0,
  flash_off,
  flash_on,
} flashState;

typedef enum {
  add_fade = 0,
  sub_fade,
} fadeState;

typedef enum {
  active = 0,
  inactive,
  boot,
} activityState;

enum custom_keycodes {
  M_PMOD = SAFE_RANGE,
  M_SMOD,
  M_OS,
  M_DASH,
};

void velocikey_accelerate(void);
void velocikey_decelerate(void);
uint8_t velocikey_match_speed(uint8_t minValue, uint8_t maxValue);

void set_color (Color new, bool update);
void save_color(Color to_save);
void reset_color(void);

Color mod_color(Color current_color, bool should_add, uint8_t change_amount);

void reverse_fade (void);

void check_state (void);

void fade_rgb (void);

void flash_rgb (void);

void set_os (uint8_t os, bool update);

void tap_key(uint8_t keycode);

void pri_mod(bool press);

void sec_mod(bool press);

void multi_tap(uint8_t num_of_chars, uint16_t keycode, bool use_shift);

void surround_type(uint8_t num_of_chars, uint16_t keycode, bool use_shift);

void long_keystroke(size_t num_of_keys, uint16_t keys[]);
