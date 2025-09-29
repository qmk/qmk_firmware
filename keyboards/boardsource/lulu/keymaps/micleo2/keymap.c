// Copyright 2022 Cole Smith <cole@boadsource.xyz>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "color.h"
#include "gw_oled.h"
#include "quantum.h"
#include "rgb_matrix.h"
#include "steno_keycodes.h"
#include QMK_KEYBOARD_H

// clang-format off

// template
/* _______,       _______,       _______,      _______,       _______,       _______,       _______,       _______,       _______,       _______,       _______,      _______,       _______,       _______, */
// formatting macro:
// mk2kWjrf`kWkvehyjPwkr j

enum layers {
  _BSE, // Base
  _SYM, // Symbol
  _NAV, // Navigation
  _SYS, // Sysctrl
  _NUM, // Numpad
  _BLN, // Blender
  _PLV, // Plover
  _GME, // Game
};

#define B _BSE
#define M _SYM
#define N _NAV
#define Y _SYS
#define U _NUM
#define L _BLN
#define P _PLV
#define E _GME

// This denotes the key you used to enter into the layer.
// E for entry.
#define ___E___ _______

#define PWR_SFT LT(0, KC_A)
#define BSE_S LT(U, KC_S)
#define BSE_D ALT_T(KC_D)
#define BSE_F LT(N, KC_F)
// base left thumb
#define BSE_LTB GUI_T(KC_SPC)

enum my_keycodes {
  // Following codes use platform-dependent modifier
  KC_ZMIN = SAFE_RANGE,
  KC_ZMOUT,
  KC_CLSTB, // close tab
  // Multi-character
  KC_HMEDIR,
  KC_CURDIR,
  KC_UPDIR,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BSE] = LAYOUT(
  KC_ESC,        KC_1,          KC_2,         KC_3,          KC_4,          KC_5,                                        KC_6,          KC_7,          KC_8,         KC_9,          KC_0,          QK_BOOT,
  TG(_PLV),      KC_Q,          KC_W,         KC_E,          KC_R,          KC_T,                                        KC_Y,          KC_U,          KC_I,         KC_O,          KC_P,          KC_DEL,
  PWR_SFT,       KC_A,          BSE_S,        BSE_D,         BSE_F,         KC_G,                                        KC_H,          KC_J,          KC_K,         KC_L,          KC_SCLN,       OSL(Y),
  TG(_BLN),      KC_Z,          KC_X,         KC_C,          KC_V,          KC_B,          RGB_VAI,       RGB_VAD,       KC_N,          KC_M,          KC_COMM,      KC_DOT,        KC_COLN,       C(G(KC_Q)),
                                KC_TAB,       CTL_T(KC_ESC), BSE_LTB,       SFT_T(KC_ENT),                               HYPR_T(KC_SPC),SFT_T(KC_BSPC),OSL(M),       TG(_GME)
),

[_SYM] = LAYOUT(
  _______,       _______,       _______,      _______,       _______,       _______,                                     _______,       _______,       _______,      _______,       _______,       _______,
  _______,       _______,       KC_LT,        KC_GT,         KC_ASTR,       KC_GRV,                                      _______,       KC_AMPR,       KC_LCBR,      KC_RCBR,       KC_PERC,       _______,
  _______,       KC_QUES,       KC_MINS,      KC_DQUO,       KC_QUOT,       KC_TILD,                                     KC_BSLS,       KC_PLUS,       KC_LPRN,      KC_RPRN,       KC_UNDS,       _______,
  _______,       _______,       KC_HASH,      KC_EQL,        KC_EXLM,       KC_CIRC,       _______,       _______,       KC_DLR,        KC_PIPE,       KC_LBRC,      KC_RBRC,       _______,       _______,
                                _______,      KC_SLSH,       _______,       KC_AT,                                       _______,       _______,       ___E___,      _______
),

[_NAV] = LAYOUT(
  _______,       _______,       _______,      _______,       _______,       _______,                                     _______,       _______,       _______,      _______,       _______,       _______,
  _______,       _______,       _______,      _______,       _______,       _______,                                     _______,       C(KC_TAB),     KC_TAB,       LSFT(KC_TAB),  C(S(KC_TAB)),  _______,
  _______,       _______,       _______,      _______,       ___E___,       _______,                                     KC_LEFT,       KC_DOWN,       KC_UP,        KC_RGHT,       _______,       _______,
  _______,       _______,       _______,      _______,       _______,       _______,       _______,       _______,       _______,       KC_ZMOUT,      KC_HOME,      KC_END,        KC_ZMIN,       _______,
                                _______,      _______,       _______,       _______,                                     KC_CLSTB,      KC_ENT,        _______,      _______
),

[_SYS] = LAYOUT(
  _______,       _______,       _______,      _______,       _______,       _______,                                     _______,       _______,       _______,      _______,       _______,       _______,
  _______,       _______,       _______,      _______,       KC_PSCR,       _______,                                     _______,       KC_F7,         KC_F8,        KC_F9,         KC_F12,        _______,
  _______,       _______,       KC_MUTE,      KC_VOLD,       KC_VOLU,       _______,                                     _______,       KC_F4,         KC_F5,        KC_F6,         KC_F11,        ___E___,
  _______,       _______,       KC_MPLY,      KC_MPRV,       KC_MNXT,       _______,       _______,       _______,       _______,       KC_F1,         KC_F2,        KC_F3,         KC_F10,        _______,
                                _______,      _______,       _______,       _______,                                     _______,       _______,       _______,      _______
),

[_NUM] = LAYOUT(
  _______,       _______,       _______,      _______,       _______,       _______,                                     _______,       _______,       _______,      _______,       _______,       _______,
  _______,       _______,       _______,      _______,       _______,       _______,                                     _______,       KC_7,          KC_8,         KC_9,          _______,       _______,
  _______,       _______,       _______,      _______,       _______,       _______,                                     _______,       KC_4,          KC_5,         KC_6,          _______,       _______,
  _______,       _______,       _______,      _______,       _______,       _______,       _______,       _______,       _______,       KC_1,          KC_2,         KC_3,          _______,       _______,
                                _______,      _______,       _______,       _______,                                     _______,       KC_0,          KC_BSPC,      _______
),

[_BLN] = LAYOUT(
  _______,       _______,       _______,      _______,       _______,       _______,                                     _______,       _______,       _______,      _______,       _______,       _______,
  KC_GRV,        LT(0, KC_Q),   LT(0, KC_W),  LT(0, KC_E),   LT(0, KC_R),   LT(0, KC_T),                                 _______,       _______,       _______,      _______,       _______,       _______,
  _______,       _______,       _______,      _______,       _______,       LT(0, KC_G),                                 _______,       _______,       _______,      _______,       _______,       _______,
  TG(_BLN),      _______,       LT(0, KC_X),  LT(0, KC_C),   LT(0, KC_V),   _______,       _______,       _______,       _______,       _______,       _______,      _______,       _______,       _______,
                                _______,      _______,       _______,       _______,                                     _______,       _______,       _______,      _______
),

[_PLV] = LAYOUT(
  _______,       _______,       _______,      _______,       _______,       _______,                                     _______,       _______,       _______,      _______,       _______,       _______,
  TG(_PLV),      _______,       _______,      _______,       _______,       _______,                                     _______,       _______,       _______,      _______,       _______,       _______,
  _______,       STN_S1,        STN_TL,       STN_PL,        STN_HL,        STN_ST1,                                     STN_ST3,       STN_FR,        STN_PR,       STN_LR,        STN_TR,        STN_DR,
  _______,       STN_S2,        STN_KL,       STN_WL,        STN_RL,        STN_ST2,       _______,       _______,       STN_ST4,       STN_RR,        STN_BR,       STN_GR,        STN_SR,        STN_ZR,
                                STN_AO,       STN_A,         STN_O,         STN_AO,                                      STN_EU,        STN_E,         STN_U,        STN_EU
),

[_GME] = LAYOUT(
  KC_ESC,        _______,       _______,      _______,       _______,       _______,                                     _______,       _______,       _______,      _______,       _______,       _______,
  KC_TAB,        KC_Q,          KC_W,         KC_E,          KC_R,          KC_T,                                        _______,       _______,       _______,      _______,       _______,       _______,
  KC_LSFT,       KC_A,          KC_S,         KC_D,          KC_F,          KC_G,                                        _______,       _______,       _______,      _______,       _______,       _______,
  KC_NO,         KC_Z,          KC_X,         KC_C,          KC_V,          KC_B,          _______,       _______,       _______,       _______,       _______,      _______,       _______,       _______,
                                KC_LALT,      KC_SPC,        KC_LCTL,       _______,                                     G(A(KC_G)),    _______,       _______,      TG(_GME)
),

};

#define SEQ_END 0

const uint16_t PROGMEM chrd_goto_ws1[] = {BSE_S, BSE_LTB, KC_M, SEQ_END};
const uint16_t PROGMEM chrd_goto_ws2[] = {BSE_S, BSE_LTB, KC_COMM, SEQ_END};
const uint16_t PROGMEM chrd_goto_ws3[] = {BSE_S, BSE_LTB, KC_DOT, SEQ_END};
const uint16_t PROGMEM chrd_goto_ws4[] = {BSE_S, BSE_LTB, KC_J, SEQ_END};
const uint16_t PROGMEM chrd_goto_ws5[] = {BSE_S, BSE_LTB, KC_K, SEQ_END};
const uint16_t PROGMEM chrd_goto_ws6[] = {BSE_S, BSE_LTB, KC_L, SEQ_END};
const uint16_t PROGMEM chrd_goto_ws7[] = {BSE_S, BSE_LTB, KC_U, SEQ_END};
const uint16_t PROGMEM chrd_goto_ws8[] = {BSE_S, BSE_LTB, KC_I, SEQ_END};
const uint16_t PROGMEM chrd_goto_ws9[] = {BSE_S, BSE_LTB, KC_O, SEQ_END};

const uint16_t PROGMEM chrd_curdir[]  = {BSE_S, BSE_D, BSE_F, SEQ_END};
const uint16_t PROGMEM chrd_homedir[] = {BSE_S, BSE_D, BSE_F, KC_J, SEQ_END};
const uint16_t PROGMEM chrd_updir[]   = {BSE_S, BSE_D, BSE_F, KC_K, SEQ_END};

combo_t key_combos[] = {
  COMBO(chrd_goto_ws1, G(KC_1)),
  COMBO(chrd_goto_ws2, G(KC_2)),
  COMBO(chrd_goto_ws3, G(KC_3)),
  COMBO(chrd_goto_ws4, G(KC_4)),
  COMBO(chrd_goto_ws5, G(KC_5)),
  COMBO(chrd_goto_ws6, G(KC_6)),
  COMBO(chrd_goto_ws7, G(KC_7)),
  COMBO(chrd_goto_ws8, G(KC_8)),
  COMBO(chrd_goto_ws9, G(KC_9)),
  COMBO(chrd_curdir, KC_CURDIR),
  COMBO(chrd_homedir, KC_HMEDIR),
  COMBO(chrd_updir, KC_UPDIR),
};

// clang-format on

static uint8_t host_is_apple = 0;
static uint8_t cpy_mod       = MOD_MASK_CTRL;

bool process_detected_host_os_user(os_variant_t detected_os) {
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            host_is_apple = 1;
            cpy_mod       = MOD_MASK_GUI;
            break;
        default:
            break;
    }
    return true;
}

void b_key_pressed_cb(void);

void enter_key_pressed_cb(void);

void delete_key_pressed_cb(void);

void copy_key_pressed_cb(void);

void paste_key_pressed_cb(void);

void leftarrow_key_pressed_cb(bool mods_active);

void rightarrow_key_pressed_cb(bool mods_active);

void downarrow_key_pressed_cb(void);

void refresh_key_pressed_cb(void);

// return true if qmk should continue processing the keycode as normal.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // The following handlers simply notify callbacks.
    switch (QK_MODS_GET_BASIC_KEYCODE(keycode)) {
        case KC_B:
            if (record->event.pressed) {
                b_key_pressed_cb();
            }
            break;
        case KC_ENT:
            if (record->event.pressed) {
                enter_key_pressed_cb();
            }
            break;
        case KC_DEL:
            if (record->event.pressed) {
                delete_key_pressed_cb();
            }
            break;
        case KC_C: {
            bool copypaste_mod_held = get_mods() & cpy_mod;
            if (record->event.pressed && copypaste_mod_held) {
                copy_key_pressed_cb();
            }
            break;
        }
        case KC_R: {
            bool copypaste_mod_held = get_mods() & cpy_mod;
            if (record->event.pressed && copypaste_mod_held) {
                refresh_key_pressed_cb();
            }
            break;
        }
        case KC_V: {
            bool copypaste_mod_held = get_mods() & cpy_mod;
            if (record->event.pressed && copypaste_mod_held) {
                paste_key_pressed_cb();
            }
            break;
        }
        case KC_LEFT:
            if (record->event.pressed) {
                leftarrow_key_pressed_cb(get_mods());
            }
            break;
        case KC_RIGHT:
            if (record->event.pressed) {
                rightarrow_key_pressed_cb(get_mods());
            }
            break;
        case KC_DOWN:
            if (record->event.pressed) {
                downarrow_key_pressed_cb();
            }
            break;
        default:
            break;
    }

    const uint8_t all_mods = get_mods() | get_oneshot_mods();
    // This switch can actually modify keypress behavior.
    switch (keycode) {
        case KC_CURDIR:
            if (record->event.pressed) {
                SEND_STRING("./");
                break;
            }
            return false;
        case KC_HMEDIR:
            if (record->event.pressed) {
                SEND_STRING("~/.");
                break;
            }
            return false;
        case KC_UPDIR:
            if (record->event.pressed) {
                SEND_STRING("../");
                break;
            }
            return false;
        case KC_ZMOUT:
            if (record->event.pressed) {
                register_mods(cpy_mod);
                tap_code16(KC_MINS);
                unregister_mods(cpy_mod);
            }
            return false;
        case KC_ZMIN:
            if (record->event.pressed) {
                register_mods(cpy_mod);
                tap_code16(KC_PLUS);
                unregister_mods(cpy_mod);
            }
            return false;
        case KC_CLSTB:
            if (record->event.pressed) {
                register_mods(cpy_mod);
                tap_code16(KC_W);
                unregister_mods(cpy_mod);
            }
            return false;
        // When tapped: oneshot shift.
        // When tapped while holding shift: toggle caps word.
        // When held: hold shift.
        case PWR_SFT:
            if (record->event.pressed) {
                if (record->tap.count) {
                    if (all_mods & MOD_MASK_SHIFT) {
                        caps_word_toggle();
                    } else {
                        add_oneshot_mods(MOD_MASK_SHIFT);
                    }
                } else {
                    register_mods(MOD_MASK_SHIFT);
                }
            } else {
                if (!record->tap.count) {
                    unregister_mods(MOD_MASK_SHIFT);
                }
            }
            return false;
            break;
        case LT(0, KC_Q):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_1);
                return false;
            }
            break;
        case LT(0, KC_W):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_2);
                return false;
            }
            break;
        case LT(0, KC_E):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_3);
                return false;
            }
            break;
        case LT(0, KC_R):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_4);
                return false;
            }
            break;
        case LT(0, KC_T):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_Y);
                return false;
            }
            break;
        case LT(0, KC_G):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_H);
                return false;
            }
            break;
        case LT(0, KC_X):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_KP_7);
                return false;
            }
            break;
        case LT(0, KC_C):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_KP_1);
                return false;
            }
            break;
        case LT(0, KC_V):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_KP_3);
                return false;
            }
            break;
        default:
            break;
    }
    return true;
}

// return true to immediately select the hold action when another key is pressed.
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_T(KC_ESC):
        case SFT_T(KC_BSPC):
            return true;
        default:
            return false;
    }
}

/* ******************* */
/* RGB SECTION BEGIN   */
/* ******************* */

#ifdef RGB_MATRIX_ENABLE

void set_underglow(uint8_t red, uint8_t green, uint8_t blue) {
#    define NUM_PER_HALF 35
#    define NUM_UNDERGLOW 6
    for (uint8_t i = 0; i < NUM_UNDERGLOW; i++) {
        rgb_matrix_set_color(i, red, green, blue);
    }
    for (uint8_t i = NUM_PER_HALF; i < NUM_PER_HALF + NUM_UNDERGLOW; i++) {
        rgb_matrix_set_color(i, red, green, blue);
    }
}

#    define HSV_LIGHT_BLUE 140, 120, 255
#    define BASE_COL HSV_LIGHT_BLUE

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    uint8_t hue;
    uint8_t sat;
    uint8_t val;
#    define SET_COLOR_INNER(h, s, v) \
        hue = h;                     \
        sat = s;                     \
        val = v;

#    define SET_COLOR(...) SET_COLOR_INNER(__VA_ARGS__)

    switch (layer) {
        case _BSE:
            SET_COLOR(BASE_COL)
            break;
        case _SYM:
            SET_COLOR(HSV_PURPLE);
            break;
        case _NAV:
            SET_COLOR(HSV_BLUE);
            break;
        case _SYS:
            SET_COLOR(HSV_RED);
            break;
        case _NUM:
        case _PLV:
            SET_COLOR(HSV_GREEN);
            break;
        case _BLN:
            SET_COLOR(HSV_ORANGE);
            break;
        case _GME:
            SET_COLOR(HSV_PINK);
            break;
        default:
            SET_COLOR(BASE_COL);
    }
    HSV base_hsv = (HSV){BASE_COL};
    if (val > rgb_matrix_get_val()) {
        val = rgb_matrix_get_val();
    }
    if (base_hsv.v > rgb_matrix_get_val()) {
        base_hsv.v = rgb_matrix_get_val();
    }
    RGB base_col = hsv_to_rgb(base_hsv);
    RGB c        = hsv_to_rgb((HSV){hue, sat, val});

    set_underglow(c.r, c.g, c.b);
    if (host_is_apple) return false;
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (!(index >= led_min && index < led_max && index != NO_LED)) {
                continue;
            }
            uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){col, row});
            if (kc == KC_NO) {
                rgb_matrix_set_color(index, RGB_OFF);
                continue;
            }
            if (kc == KC_TRNS) {
                rgb_matrix_set_color(index, base_col.r, base_col.g, base_col.b);
                continue;
            }
            rgb_matrix_set_color(index, c.r, c.g, c.b);
        }
    }

    return false;
}
#endif
/* ***************** */
/* RGB SECTION END   */
/* ***************** */

/* ****************** */
/* OLED SECTION BEGIN */
/* ****************** */

#ifdef OLED_ENABLE

// This is updated to the current time in ms every time we enter the render loop.
static uint32_t cur_render_time = 0;

// Render functions which return bool will optionally render. Returning true means the caller may
// continue rendering their own content.
bool render_downtaunt(void);
bool render_flash_seq(void);
void render_idle(void);
void render_parachute(void);

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
#    ifdef MASTER_RIGHT
    if (is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
#    else
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
#    endif
    return rotation;
}

void oled_render_boot(bool bootloader) {
    oled_clear();
    for (int i = 0; i < 16; i++) {
        oled_set_cursor(0, i);
        if (bootloader) {
            oled_write_P(PSTR("Awaiting New Firmware "), false);
        } else {
            oled_write_P(PSTR("Rebooting "), false);
        }
    }

    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    return true;
}

bool oled_task_user() {
    cur_render_time = timer_read32();
    if (render_flash_seq() == false) {
        return false;
    }

    const uint8_t cur_layer = get_highest_layer(layer_state);
    switch (cur_layer) {
        case _BSE:
            if (render_downtaunt()) {
                render_idle();
            }
            break;
        case _SYM:
            oled_write_raw(gw_diver, sizeof(gw_diver));
            break;
        case _NAV:
            render_parachute();
            break;
        case _SYS:
            oled_write_raw(gw_bomb, sizeof(gw_bomb));
            break;
        case _NUM:
        case _PLV:
            oled_write_raw(gw_key, sizeof(gw_key));
            break;
        case _BLN:
            oled_write_raw(gw_flagman_right, sizeof(gw_flagman_right));
            break;
        default:
            render_idle();
            break;
    }

    return false;
}

enum IDLE_DIR { RIGHT, LEFT };
static uint8_t cur_arrow_dir = RIGHT;

// How long an individual idle frame lasts.
#    define IDLE_TOGGLE_FRAME_LEN_MS 1000
static uint8_t  cur_idle_pose          = 0;
static bool     must_do_crouch         = false;
static uint32_t change_idle_pose_timer = 0;

void render_idle() {
    if (timer_expired32(cur_render_time, change_idle_pose_timer)) {
        change_idle_pose_timer = cur_render_time + IDLE_TOGGLE_FRAME_LEN_MS;
        // We emulate the idle animation behavior from smash. Most of the time is spent toggling between stand and crouch.
        // When you are in any pose other than stand, the only valid next pose is back to stand. Stand can then branch
        // into crouch, or backhand/outstreched (BO), but crouch is the most likely. If you have entered into stand from BO,
        // then you must perform a crouch before you are eligible to do another BO.
        if (cur_idle_pose == idle_stand_pose) {
            if (must_do_crouch) {
                cur_idle_pose  = idle_crouch_pose;
                must_do_crouch = false;
            } else {
                // 50% chance go into crouch, 25% backhand or outstreched individually.
                switch (rand() % 4) {
                    case 0:
                    case 1:
                        cur_idle_pose = idle_crouch_pose;
                        break;
                    case 2:
                        cur_idle_pose  = idle_backhand_pose;
                        must_do_crouch = true;
                        break;
                    case 3:
                        cur_idle_pose  = idle_outstretched_pose;
                        must_do_crouch = true;
                        break;
                }
            }
        } else {
            cur_idle_pose = idle_stand_pose;
        }
    };
    uint8_t idleIdx = cur_idle_pose * 2 + cur_arrow_dir;
    // All the poses should have the same size, so it doesn't matter which one we use sizeof on.
    oled_write_raw(gw_idle_poses[idleIdx], sizeof(gw_idle_A_right));
}

uint32_t next_parachute_frame_timer = 0;
uint16_t parachute_idx              = 0;

void render_parachute() {
#    define PARACHUTE_FRAME_LEN 550
    if (timer_expired32(cur_render_time, next_parachute_frame_timer)) {
        // If the frame timer is expired by a lot, that probably means that the parachute animation
        // hasn't been running for a while. So reset the animation.
        if (cur_render_time - next_parachute_frame_timer > PARACHUTE_FRAME_LEN * 2) {
            parachute_idx = 0;
        } else {
            parachute_idx++;
            parachute_idx %= PARACHUTE_SEQ_LEN;
        }
        next_parachute_frame_timer = cur_render_time + PARACHUTE_FRAME_LEN;
    }
    oled_write_raw(gw_parachute[parachute_idx], sizeof(gw_parachute1));
}

// Delay to wait after kb inactivity to begin taunt animation.
#    define TAUNT_WAIT_MS 60 * 1000
// Length of a single frame of the taunt animation.
#    define TAUNT_TOGGLE_FRAME_LEN_MS 1500

bool render_downtaunt() {
    const uint32_t idle_time_ms = last_matrix_activity_elapsed();
    if (idle_time_ms <= TAUNT_WAIT_MS) {
        return true;
    }
    if ((cur_render_time / TAUNT_TOGGLE_FRAME_LEN_MS) % 2 == 0) {
        oled_write_raw(gw_downtaunt_f1, sizeof(gw_downtaunt_f1));
    } else {
        oled_write_raw(gw_downtaunt_f2, sizeof(gw_downtaunt_f2));
    }
    return false;
}

// Contains all the frame data of the sequence.
static const char **flash_seq_data;
// When set, contains the end deadline for the flash sequence.
static uint32_t flash_img_end_timer = 0;
static uint32_t flash_seq_begin_time;
static uint16_t flash_num_frames;
static uint32_t flash_frame_len_ms;
static uint16_t flash_img_size;

// Support briefly flashing an image sequence on the display for a set amount of time. This ignores any layer information.
// Each frame of the sequence will have an equal amount of render time, based off the ratio of the sequence length and
// number of frames. Any leftover time not evenly divisible will be given to the last frame.
bool render_flash_seq() {
    if (flash_img_end_timer == 0) {
        return true;
    }
    if (timer_expired32(cur_render_time, flash_img_end_timer)) {
        flash_img_end_timer = 0;
        return true;
    }
    uint16_t seq_idx = (cur_render_time - flash_seq_begin_time) / flash_frame_len_ms;
    if (seq_idx >= flash_num_frames) {
        seq_idx = flash_num_frames - 1;
    }
    oled_write_raw(flash_seq_data[seq_idx], flash_img_size);
    return false;
}

void start_flash_seq(const char **data, uint32_t seq_len_ms, uint16_t num_frames, uint16_t img_size) {
    flash_seq_data       = data;
    flash_seq_begin_time = cur_render_time;
    flash_img_end_timer  = cur_render_time + seq_len_ms;
    flash_num_frames     = num_frames;
    flash_frame_len_ms   = seq_len_ms / num_frames;
    flash_img_size       = img_size;
}

// Helper function to launch a "sequence" which is really just one frame of data.
static const char *helper_img_wrapper[1] = {NULL};
void               start_flash_img(const char *data, uint32_t img_len_ms, uint16_t img_size) {
    helper_img_wrapper[0] = data;
    start_flash_seq(helper_img_wrapper, img_len_ms, 1, img_size);
}

void refresh_key_pressed_cb(void) {
#    define PUFF_LEN_MS 200 * 3
    start_flash_seq(gw_puffs, PUFF_LEN_MS, PUFF_SEQ_LEN, sizeof(gw_puff_f1));
}

// Start vermin anim on enter key.
void enter_key_pressed_cb(void) {
#    define VERMIN_LEN_MS 300 * VERMIN_SEQ_LEN
    start_flash_seq(gw_vermin, VERMIN_LEN_MS, VERMIN_SEQ_LEN, sizeof(gw_vermin_hi));
}

void delete_key_pressed_cb(void) {
#    define JUDGE9_LEN_MS 1100
    // Treat the time at which the delete key is pressed as RNG.
    // We have a 1/9 chance of flashing the judge9.
    if (cur_render_time % 9 == 0) {
        start_flash_img(gw_judge9, JUDGE9_LEN_MS, sizeof(gw_judge9));
    }
}

void b_key_pressed_cb(void) {
#    define BACON_LEN_MS 300 * BACON_SEQ_LEN
    // 1/2 chance of cooking bacon on b.
    if (cur_render_time % 2 == 0) {
        start_flash_seq(gw_bacon, BACON_LEN_MS, BACON_SEQ_LEN, sizeof(gw_bacon0));
    }
}

// The current charged state of the bucket.
static uint8_t charge_state = 0;
// The bucket's fully charged state.
#    define MAX_CHARGE_STATE 3

void flash_current_charge_state(void) {
#    define BUCKET_CHARGE_LEN_MS 500
    switch (charge_state) {
        case 0:
            start_flash_img(gw_bucket_charged0, BUCKET_CHARGE_LEN_MS, sizeof(gw_bucket_charged0));
            break;
        case 1:
            start_flash_img(gw_bucket_charged1, BUCKET_CHARGE_LEN_MS, sizeof(gw_bucket_charged1));
            break;
        case 2:
            start_flash_img(gw_bucket_charged2, BUCKET_CHARGE_LEN_MS, sizeof(gw_bucket_charged2));
            break;
        case 3:
            start_flash_img(gw_bucket_charged3, BUCKET_CHARGE_LEN_MS, sizeof(gw_bucket_charged3));
            break;
    }
}

void copy_key_pressed_cb(void) {
    if (charge_state < MAX_CHARGE_STATE) {
        charge_state++;
    }
    flash_current_charge_state();
}

void paste_key_pressed_cb(void) {
#    define BUCKET_THROW_LEN_MS 200 * THROW_SEQ_LEN
    if (charge_state == MAX_CHARGE_STATE) {
        start_flash_seq(gw_bucket_throws, BUCKET_THROW_LEN_MS, THROW_SEQ_LEN, sizeof(gw_bucket_throw1));
        charge_state = 0;
    } else {
        flash_current_charge_state();
    }
}

#    define CHAIR_LEN_MS 600
void leftarrow_key_pressed_cb(bool mods_active) {
    cur_arrow_dir = LEFT;
    if (mods_active) {
        start_flash_img(gw_chair_left, CHAIR_LEN_MS, sizeof(gw_chair_left));
    }
}

void rightarrow_key_pressed_cb(bool mods_active) {
    cur_arrow_dir = RIGHT;
    if (mods_active) {
        start_flash_img(gw_chair_right, CHAIR_LEN_MS, sizeof(gw_chair_right));
    }
}

void downarrow_key_pressed_cb() {
    if (cur_arrow_dir == RIGHT) {
        start_flash_img(gw_down_squat_right, CHAIR_LEN_MS, sizeof(gw_down_squat_right));
    } else {
        start_flash_img(gw_down_squat_left, CHAIR_LEN_MS, sizeof(gw_down_squat_left));
    }
}

#else
// Stub impls.
void b_key_pressed_cb(void) {}
void enter_key_pressed_cb(void) {}
void delete_key_pressed_cb(void) {}
void copy_key_pressed_cb(void) {}
void paste_key_pressed_cb(void) {}
void leftarrow_key_pressed_cb(bool) {}
void rightarrow_key_pressed_cb(bool) {}
void downarrow_key_pressed_cb(void) {}
void refresh_key_pressed_cb(void) {}
#endif
/* ****************** */
/* OLED SECTION END */
/* ****************** */
