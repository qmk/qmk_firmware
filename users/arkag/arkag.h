#pragma once

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

#define _QWERTY  0
#define _RAISE   1
#define _LOWER   2
#define _KEEB    3
#define _MEDIA   4
#define _LAZY    5

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
#define LED_FADE_DELAY        10

#define INACTIVE_DELAY        200
#define SLEEP_DELAY           60000

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

uint8_t       current_os, mod_primary_mask, fade_delay;
uint16_t      flash_timer_one, flash_timer_two,
              fade_timer_one, fade_timer_two,
              active_timer_one, active_timer_two,
              elapsed               = 0,
              num_extra_flashes_off = 0;
Color         underglow,
              flash_color,
              saved_color,
              hsv_none      = {0,0,0},
              hsv_white     = {0,0,127};
flashState    flash_state   = no_flash;
fadeState     fade_state    = add_fade;
activityState state         = boot;

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
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
        [TD_3_GRV_ACT]      = ACTION_TAP_DANCE_FN (dance_3),
        [TD_C_CED]          = ACTION_TAP_DANCE_FN (dance_c),
        [TD_GRV_3GRV]       = ACTION_TAP_DANCE_FN (dance_grv),
        [TD_SING_DOUB]      = ACTION_TAP_DANCE_FN (dance_quot),
        [TD_STRK_SHOT]      = ACTION_TAP_DANCE_FN (dance_strk),
        [TD_HYPH_UNDR]      = ACTION_TAP_DANCE_DOUBLE (KC_MINS, LSFT(KC_MINS)),
        [TD_BRCK_PARN_O]    = ACTION_TAP_DANCE_DOUBLE (KC_LBRC, LSFT(KC_9)),
        [TD_BRCK_PARN_C]    = ACTION_TAP_DANCE_DOUBLE (KC_RBRC, LSFT(KC_0)),
        [TD_LALT_RALT]      = ACTION_TAP_DANCE_DOUBLE (KC_LALT, KC_RALT),
};

void send_unicode_hex_string(const char *str);

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

void dance_grv (qk_tap_dance_state_t *state, void *user_data)
void dance_quot (qk_tap_dance_state_t *state, void *user_data)
void dance_strk (qk_tap_dance_state_t *state, void *user_data)
void dance_3 (qk_tap_dance_state_t *state, void *user_data)
void dance_c (qk_tap_dance_state_t *state, void *user_data)
