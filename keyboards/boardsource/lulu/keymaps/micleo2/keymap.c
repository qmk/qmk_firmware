// Copyright 2022 Cole Smith <cole@boadsource.xyz>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "color.h"
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
  _GME, // GAME
};

#define B _BSE
#define M _SYM
#define N _NAV
#define Y _SYS
#define U _NUM
#define L _BLN
#define P _PLV
#define E _GAME

// This denotes the key you used to enter into the layer.
// E for entry.
#define ___E___ _______

#define PWR_SFT LT(0, KC_A)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BSE] = LAYOUT(
  QK_BOOT,       KC_1,          KC_2,         KC_3,          KC_4,          KC_5,                                        KC_6,          KC_7,          KC_8,         KC_9,          KC_0,          QK_BOOT,
  TG(_PLV),      KC_Q,          KC_W,         KC_E,          KC_R,          KC_T,                                        KC_Y,          KC_U,          KC_I,         KC_O,          KC_P,          KC_DEL,
  PWR_SFT,       KC_A,          LT(U, KC_S),  ALT_T(KC_D),   LT(N, KC_F),   KC_G,                                        KC_H,          KC_J,          KC_K,         KC_L,          KC_SCLN,       OSL(Y),
  TG(_BLN),      KC_Z,          KC_X,         KC_C,          KC_V,          KC_B,          RGB_VAI,       RGB_VAD,       KC_N,          KC_M,          KC_COMM,      KC_DOT,        KC_COLN,       C(G(KC_Q)),
                                KC_TAB,       CTL_T(KC_ESC), GUI_T(KC_SPC), SFT_T(KC_ENT),                               HYPR_T(KC_SPC),SFT_T(KC_BSPC),OSL(M),       TG(_GME)
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
  _______,       _______,       _______,      _______,       _______,       _______,       _______,       _______,       _______,       _______,       KC_HOME,      KC_END,        _______,       _______,
                                _______,      _______,       _______,       _______,                                     _______,       KC_ENT,        _______,      _______
),

[_SYS] = LAYOUT(
  _______,       _______,       _______,      _______,       _______,       _______,                                     _______,       _______,       _______,      _______,       _______,       _______,
  CW_TOGG,       RGB_TOG,       RGB_VAD,      RGB_VAI,       KC_PSCR,       _______,                                     _______,       KC_F7,         KC_F8,        KC_F9,         KC_F12,        _______,
  _______,       _______,       KC_MPLY,      KC_VOLD,       KC_VOLU,       _______,                                     _______,       KC_F4,         KC_F5,        KC_F6,         KC_F11,        ___E___,
  _______,       _______,       KC_MPRV,      KC_MNXT,       KC_MUTE,       _______,       _______,       _______,       _______,       KC_F1,         KC_F2,        KC_F3,         KC_F10,        _______,
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
                                _______,      STN_A,         STN_O,         STN_AO,                                      STN_EU,        STN_E,         STN_U,        _______
),

[_GME] = LAYOUT(
  KC_ESC,        _______,       _______,      _______,       _______,       _______,                                     _______,       _______,       _______,      _______,       _______,       _______,
  KC_TAB,        _______,       _______,      _______,       _______,       _______,                                     _______,       _______,       _______,      _______,       _______,       _______,
  KC_LSFT,       _______,       KC_S,         KC_D,          KC_F,          _______,                                     _______,       _______,       _______,      _______,       _______,       _______,
  _______,       _______,       _______,      _______,       _______,       _______,       _______,       _______,       _______,       _______,       _______,      _______,       _______,       _______,
                                KC_LALT,      KC_SPC,        KC_LCTL,       _______,                                     _______,       _______,       _______,      TG(_GME)
),

};

#define SEQ_END 0
const uint16_t PROGMEM goto_ws1[] = {LT(U, KC_S), GUI_T(KC_SPC), KC_M, SEQ_END};
const uint16_t PROGMEM goto_ws2[] = {LT(U, KC_S), GUI_T(KC_SPC), KC_COMM, SEQ_END};
const uint16_t PROGMEM goto_ws3[] = {LT(U, KC_S), GUI_T(KC_SPC), KC_DOT, SEQ_END};
const uint16_t PROGMEM goto_ws4[] = {LT(U, KC_S), GUI_T(KC_SPC), KC_J, SEQ_END};
const uint16_t PROGMEM goto_ws5[] = {LT(U, KC_S), GUI_T(KC_SPC), KC_K, SEQ_END};
const uint16_t PROGMEM goto_ws6[] = {LT(U, KC_S), GUI_T(KC_SPC), KC_L, SEQ_END};
const uint16_t PROGMEM goto_ws7[] = {LT(U, KC_S), GUI_T(KC_SPC), KC_U, SEQ_END};
const uint16_t PROGMEM goto_ws8[] = {LT(U, KC_S), GUI_T(KC_SPC), KC_I, SEQ_END};
const uint16_t PROGMEM goto_ws9[] = {LT(U, KC_S), GUI_T(KC_SPC), KC_O, SEQ_END};

// clang-format off
combo_t key_combos[] = {
    COMBO(goto_ws1, G(KC_1)),
    COMBO(goto_ws2, G(KC_2)),
    COMBO(goto_ws3, G(KC_3)),
    COMBO(goto_ws4, G(KC_4)),
    COMBO(goto_ws5, G(KC_5)),
    COMBO(goto_ws6, G(KC_6)),
    COMBO(goto_ws7, G(KC_7)),
    COMBO(goto_ws8, G(KC_8)),
    COMBO(goto_ws9, G(KC_9)),
};

// clang-format on

/* ********************* */
/* VLEADER SECTION BEGIN */
/* ********************* */

typedef struct vlead_seq_t {
    const uint16_t *keys;
    uint16_t        event_id;
    unsigned int    is_eligible : 1;
    unsigned int    keys_count : 7;
} vlead_seq_t;
#define VLEAD_SEQ(ck, ca) \
    { .keys = &(ck)[0], .event_id = (ca) }

enum vleader_events {
    K_U,
    K_D,
    K_E,
    K_M,
    K_H,
    K_NM,
    K_NT,
    K_NA,
    K_LTHUMB,
};

const uint16_t PROGMEM k_u[]      = {KC_U, SEQ_END};
const uint16_t PROGMEM k_d[]      = {ALT_T(KC_D), SEQ_END};
const uint16_t PROGMEM k_e[]      = {KC_E, SEQ_END};
const uint16_t PROGMEM k_m[]      = {KC_M, SEQ_END};
const uint16_t PROGMEM k_h[]      = {KC_H, SEQ_END};
const uint16_t PROGMEM k_nm[]     = {KC_N, KC_M, SEQ_END};
const uint16_t PROGMEM k_nt[]     = {KC_N, KC_T, SEQ_END};
const uint16_t PROGMEM k_na[]     = {KC_N, KC_A, SEQ_END};
const uint16_t PROGMEM k_lthumb[] = {GUI_T(KC_SPC), SEQ_END};

// clang-format off
vlead_seq_t vleader_map[] = {
    VLEAD_SEQ(k_u, K_U),
    VLEAD_SEQ(k_d, K_D),
    VLEAD_SEQ(k_e, K_E),
    VLEAD_SEQ(k_m, K_M),
    VLEAD_SEQ(k_h, K_H),
    VLEAD_SEQ(k_nm, K_NM),
    VLEAD_SEQ(k_nt, K_NT),
    VLEAD_SEQ(k_na, K_NA),
    VLEAD_SEQ(k_lthumb, K_LTHUMB),
};
// clang-format on

void process_vlead_event_user(uint16_t vlead_idx) {
    switch (vlead_idx) {
        case K_LTHUMB:
            SEND_STRING(". ");
            add_oneshot_mods(MOD_MASK_SHIFT);
            break;
        case K_U:
            SEND_STRING("../");
            break;
        case K_D:
            SEND_STRING("./");
            break;
        default:
            break;
    }
}

bool     vleading              = false;
uint16_t vleader_time          = 0;
uint8_t  vleader_sequence_size = 0;

uint16_t vleader_map_count(void) {
    return sizeof(vleader_map) / sizeof(vlead_seq_t);
}

vlead_seq_t *vleader_map_get(uint16_t seq_idx) {
    return &vleader_map[seq_idx];
}

bool vleader_sequence_active(void) {
    return vleading;
}

bool vleader_sequence_timed_out(void) {
#if defined(LEADER_NO_TIMEOUT)
    return vleader_sequence_size > 0 && timer_elapsed(vleader_time) > LEADER_TIMEOUT;
#else
    return timer_elapsed(vleader_time) > LEADER_TIMEOUT;
#endif
}

void vleader_reset_timer(void) {
    vleader_time = timer_read();
}

void vleader_start(void) {
    vleading              = true;
    vleader_time          = timer_read();
    vleader_sequence_size = 0;
    for (uint16_t i = 0; i < vleader_map_count(); i++) {
        vlead_seq_t *seq = vleader_map_get(i);
        seq->is_eligible = 1;
    }
}

void vleader_end(void) {
    vleading = false;
}

void vleader_sequence_add(uint16_t keycode) {
    vleader_sequence_size++;
    bool         duplicate_matches  = false;
    vlead_seq_t *first_matching_seq = NULL;
    for (uint16_t i = 0; i < vleader_map_count(); i++) {
        vlead_seq_t *seq = vleader_map_get(i);
        if (!seq->is_eligible) continue;
        if (seq->keys_count < vleader_sequence_size) {
            seq->is_eligible = false;
            continue;
        }
        uint16_t seq_cur_kc = pgm_read_word(&seq->keys[vleader_sequence_size - 1]);
        if (seq_cur_kc != keycode) {
            seq->is_eligible = false;
            continue;
        }
        if (first_matching_seq) {
            duplicate_matches = true;
        } else {
            first_matching_seq = seq;
        }
    }
    if (!first_matching_seq) {
        vleader_end();
        return;
    }
    // If we found a single match, execute this event and end the sequence.
    if (!duplicate_matches) {
        process_vlead_event_user(first_matching_seq->event_id);
        vleader_end();
        return;
    }
    // We found a partial match, reset the timer.
    vleader_reset_timer();
}

bool process_vleader(uint16_t keycode, keyrecord_t *record) {
    if (vleader_sequence_active() && vleader_sequence_timed_out()) {
        vleader_end();
    }
    if (record->event.pressed) {
        if (vleader_sequence_active()) {
            // If a user enters in an incorrect sequence, we still want to consume the entire
            // sequence. So if there is a sequence for "as", and they type "ad", then both a
            // and d should not register as taps. But the leader will get disabled after.
            vleader_sequence_add(keycode);
            return false;
        }
    }
    return true;
}

void keyboard_post_init_user(void) {
    for (uint16_t i = 0; i < vleader_map_count(); i++) {
        vlead_seq_t *seq        = vleader_map_get(i);
        uint16_t     keys_count = 0;
        while (true) {
            uint16_t key = pgm_read_word(&seq->keys[keys_count]);
            if (key == SEQ_END) break;
            keys_count++;
        }
        seq->keys_count = keys_count;
    }
}

void housekeeping_task_user(void) {
    if (vleader_sequence_active() && vleader_sequence_timed_out()) {
        vleader_end();
    }
}

/* ********************* */
/* VLEADER SECTION END   */
/* ********************* */

// return true if qmk should continue processing the keycode as normal.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_vleader(keycode, record)) {
        return false;
    }

    const uint8_t all_mods = get_mods() | get_oneshot_mods();
    // This switch can actually modify keypress behavior.
    switch (keycode) {
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
        case HYPR_T(KC_SPC):
            if (record->tap.count && record->event.pressed) {
                vleader_start();
                return false;
            }
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

static uint8_t use_simple_rgb = 0;

bool process_detected_host_os_user(os_variant_t detected_os) {
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            use_simple_rgb = 1;
            break;
        default:
            break;
    }
    return true;
}

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
    if (use_simple_rgb) return false;
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
