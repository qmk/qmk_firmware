#pragma once

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

#define EECONFIG_USERSPACE (uint8_t *)20

#define LRALT       TD(TD_LALT_RALT)
#define QUOTE       TD(TD_SING_DOUB)
#define GRAVE       TD(TD_GRV_3GRV)
#define OBRACK      TD(TD_BRCK_PARN_O)
#define CBRACK      TD(TD_BRCK_PARN_C)
#define THREE       TD(TD_3_GRV_ACT)
#define STRIKE      TD(TD_STRK_SHOT)
#define HYPHEN      TD(TD_HYPH_UNDR)
#define CEDILLA     TD(TD_C_CED)

#define RAISE       MO(1)
#define LOWER       MO(2)
#define KEEB        MO(3)
#define MEDIA       MO(4)
#define LAZY        MO(5)

#define MOD_CTL_MASK (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL))
#define MOD_GUI_MASK (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI))
#define MOD_SFT_MASK (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))

#define LED_FLASH_DELAY       150

#define ACCEL_DELAY           500
#define DEACCEL_DELAY         500

#define INACTIVE_DELAY        250
#define SLEEP_DELAY           180000

enum {
  _QWERTY = 0,
  _RAISE,
  _LOWER,
  _KEEB,
  _MEDIA,
  _LAZY,
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
  sleeping,
  boot,
} activityState;

enum custom_keycodes {
  M_PMOD = SAFE_RANGE,
  M_SMOD,
  M_P_B,
  M_C_A_D,
  M_CALC,
  M_OS,
  M_TF,
  M_TM,
  M_GGT,
  M_LOD,
  M_LENNY,
  M_BOLD,
  M_ITAL,
  M_ULIN,
  M_SNIPT,
  M_REPO,
  M_SHRUG,
  M_UF,
};

enum tapdances {
  TD_3_GRV_ACT = 0,
  TD_C_CED,
  TD_GRV_3GRV,
  TD_SLSH_HTTP,
  TD_SING_DOUB,
  TD_HYPH_UNDR,
  TD_STRK_SHOT,
  TD_SPECIAL,
  TD_BRCK_PARN_O,
  TD_BRCK_PARN_C,
  TD_LALT_RALT,
  SPC_SFT_NSFT,
};

void send_unicode_hex_string(const char *str);

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

void surround_type(uint8_t num_of_chars, uint16_t keycode, bool use_shift);

void long_keystroke(size_t num_of_keys, uint16_t keys[]);

void dance_grv (qk_tap_dance_state_t *state, void *user_data);
void dance_quot (qk_tap_dance_state_t *state, void *user_data);
void dance_strk (qk_tap_dance_state_t *state, void *user_data);
void dance_3 (qk_tap_dance_state_t *state, void *user_data);
void dance_c (qk_tap_dance_state_t *state, void *user_data);

int cur_dance (qk_tap_dance_state_t *state);
void spc_finished (qk_tap_dance_state_t *state, void *user_data);
void spc_reset (qk_tap_dance_state_t *state, void *user_data);
