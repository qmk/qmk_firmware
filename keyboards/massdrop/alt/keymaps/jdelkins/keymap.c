/*
  Copyright 2020 Joel Elkins <joel@elkins.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "jdelkins.h"
#include "print.h"

// Idle handling

#define IDLE_TIMEOUT 360
#define _LAYERS _RPT

uint16_t rgb_idle_seconds = 0;
uint16_t rgb_timer;
uint8_t save_layer;

// Macro keycodes

enum alt_keycodes {
    U_T_AUTO = USER_SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,                   //USB Toggle Automatic GCR control
    DBG_TOG,                    //DEBUG Toggle On / Off
    DBG_MTRX,                   //DEBUG Toggle Matrix Prints
    DBG_KBD,                    //DEBUG Toggle Keyboard Prints
    DBG_MOU,                    //DEBUG Toggle Mouse Prints
};

// Tap Dance

int ctl_state = 0;

void ctl_finished(qk_tap_dance_state_t *state, void *user_data) {
    ctl_state = cur_dance(state);
    switch(ctl_state) {
        case SINGLE_TAP:    qk_leader_start(); break;
        case SINGLE_HOLD:   register_code(KC_LCTL); break;
        case DOUBLE_TAP:    tap_code(KC_RCTL); break;
        case DOUBLE_HOLD:   register_code(KC_RCTL); break;
        case TRIPLE_TAP:    tap_code(KC_RCTL); tap_code(KC_RCTL); break;
        case TRIPLE_HOLD:   tap_code(KC_RCTL); register_code(KC_RCTL); break;
    }
}

void ctl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch(ctl_state) {
        case SINGLE_HOLD:   unregister_code(KC_LCTL); break;
        case DOUBLE_HOLD:
        case TRIPLE_HOLD:   unregister_code(KC_RCTL); break;
    }
    ctl_state = 0;
}

void g_finished(qk_tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state)) {
        case SINGLE_TAP:
            tap_code16(C(KC_END));
            break;
        case DOUBLE_TAP:
            tap_code16(C(KC_HOME));
            break;
    }
}

enum {
    TD_LDCTL,
    TD_GUI,
    TD_G,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LDCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctl_finished, ctl_reset),
    [TD_GUI]   = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_RGUI),
    [TD_G]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, g_finished, NULL),
};

// Layers

const uint16_t PROGMEM keymaps[_LAYER_MAX][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,    KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,    KC_RBRC, KC_BSLS, KC_HOME,
        MY_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,    KC_ENT,           KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,             KC_UP,   KC_PGDN,
        TD(TD_LDCTL), TD(TD_GUI), KC_LALT,                       MY_SPC,                          KC_RALT, MO(_ADJUST),KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_GAME] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_LCTL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, KC_NO,   _______,                               KC_SPC,                          _______, _______, _______, _______, _______
    ),
    [_FUNC] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_DEL,  KC_INS,
        _______, _______, FW_WRD,  KC_END,  _______, _______,  C(KC_INS),KC_PGUP, _______, _______, S(KC_INS),KC_SCRL, KC_PAUS, KC_CALC, KC_END,
        _______, KC_HOME, _______, KC_PGDN, _______, TD(TD_G), KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT, _______,  _______, _______,          _______,
        _______, _______, KC_DEL,  _______, _______, BK_WRD,   _______,  _______, _______, _______, _______,  _______,          KC_PGUP, _______,
        _______, _______, _______,                             _______,                             _______,  _______, KC_HOME, KC_PGDN, KC_END
    ),
    [_LAYERS] = LAYOUT(
        KC_NO, TO(_QWERTY),TO(_GAME), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO,      KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO,      KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,        KC_NO,
        KC_NO, KC_NO,      KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,          KC_NO, KC_NO,
        KC_NO, KC_NO,      KC_NO,                            KC_NO,                    KC_NO, _______, KC_NO, KC_NO, KC_NO
    ),
    [_KP] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_ASTERISK, _______, _______,       _______, _______, _______, _______,
        KC_NUM,  KC_KP_7, KC_KP_8, KC_KP_9, _______, _______, _______, KC_KP_7, KC_KP_8,        KC_KP_9, KC_KP_MINUS,   _______, _______, _______, _______,
        _______, KC_KP_4, KC_KP_5, KC_KP_6, _______, _______, _______, KC_KP_4, KC_KP_5,        KC_KP_6, KC_KP_PLUS,    _______, _______,          _______,
        _______, KC_KP_1, KC_KP_2, KC_KP_3, _______, _______, _______, KC_KP_1, KC_KP_2,        KC_KP_3, KC_KP_SLASH,   _______,          _______, _______,
        _______, _______, _______,                            KC_KP_0,                                       KC_KP_DOT, TG(_KP), _______, _______, _______
    ),
    [_SECRETS] = LAYOUT(
        KC_NO, KC_SEC1, KC_SEC2, KC_SEC3, KC_SEC4, KC_SEC5, KC_SEC6, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,        KC_NO,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,          KC_NO, KC_NO,
        KC_NO, KC_NO,   KC_NO,                                KC_NO,                      KC_NO, _______, KC_NO, KC_NO, KC_NO
    ),
    [_ADJUST] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,        KC_F10,        KC_F11,  KC_F12,  KC_F13,  KC_INS,
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______,      KC_PSCR,       KC_SCRL, KC_PAUS, KC_CALC, KC_END,
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, TG(_KP), OSL(_LAYERS), OSL(_SECRETS), _______, _______,          KC_MPLY,
        _______, RGB_TOG, KB_MAKE, KB_FLSH, KB_VRSN, KB_BOOT, NK_TOGG, DBG_TOG, _______, _______,      _______,       _______,          KC_VOLU, KC_MUTE,
        _______, _______, _______,                            _______,                                 _______,       _______, KC_MPRV, KC_VOLD, KC_MNXT
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______
    ),
    */
};

#ifdef _______
#undef _______
#endif

#define RGB_NULL 254, 254, 254
#define RGB_IS_NULL(rgb) ((rgb).r == 254 && (rgb).g == 254 && (rgb).b == 254)

#define DEFAULT_HSV 255, 255, 128
#define R(COL) { RGB_ ## COL }
#define _______ R(NULL)
#define xxxxxxx R(BLACK)

struct layer_rgb PROGMEM rgbs[_LAYER_MAX] = {
    [_QWERTY] = LAYOUT_hsv(LED_FLAG_ALL, RGB_MATRIX_CYCLE_ALL, DEFAULT_HSV),
    [_GAME] = LAYOUT_hsv(LED_FLAG_KEYLIGHT, RGB_MATRIX_SOLID_COLOR, DEFAULT_HSV),
    [_FUNC] = LAYOUT_rgb(LED_FLAG_KEYLIGHT, RGB_LINK_TO_LAYER(_QWERTY),
        R(BLUE),   R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(BLUE),
        R(BLUE),   _______,   _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,   _______,  _______,   R(BLUE),
        R(BLUE),   _______,   _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,   _______,  _______,   R(BLUE),
                   _______,   _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,         _______,       _______,
        R(BLUE),   _______,   _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,         _______,       _______,  _______,   R(BLUE),
        R(BLUE),   _______,   _______,   _______,                                        _______,                         _______,  _______,   _______,   _______,  _______,   R(BLUE),
        R(BLUE),   R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(RED),     R(BLUE)
    ),
    [_LAYERS] = LAYOUT_rgb(LED_FLAG_NONE, RGB_MATRIX_SOLID_COLOR,
        R(CYAN),   R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),
        R(CYAN),   xxxxxxx,   R(RED),    R(GREEN),  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,   R(CYAN),
        R(CYAN),   xxxxxxx,   xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,   R(CYAN),
                   xxxxxxx,   xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,         xxxxxxx,       xxxxxxx,
        R(CYAN),   xxxxxxx,   xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,         xxxxxxx,       xxxxxxx,  xxxxxxx,   R(CYAN),
        R(CYAN),   xxxxxxx,   xxxxxxx,   xxxxxxx,                                        xxxxxxx,                         xxxxxxx,  xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,   R(CYAN),
        R(CYAN),   R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN),    R(CYAN)
    ),
    [_KP] = LAYOUT_rgb(LED_FLAG_NONE, RGB_MATRIX_SOLID_COLOR,
        xxxxxxx,   xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,
        xxxxxxx,   R(GREEN),  xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  R(YELLOW),xxxxxxx,  xxxxxxx,   xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,  xxxxxxx,
        xxxxxxx,   xxxxxxx,   R(WHITE),  R(WHITE),  R(WHITE), xxxxxxx,  xxxxxxx,  xxxxxxx,  R(WHITE), R(WHITE), R(WHITE), R(YELLOW), xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,  xxxxxxx,
                   xxxxxxx,   R(WHITE),  R(WHITE),  R(WHITE), xxxxxxx,  xxxxxxx,  xxxxxxx,  R(WHITE), R(WHITE), R(WHITE), R(YELLOW), xxxxxxx,         xxxxxxx,       xxxxxxx,
        xxxxxxx,   xxxxxxx,   R(WHITE),  R(WHITE),  R(WHITE), xxxxxxx,  xxxxxxx,  xxxxxxx,  R(WHITE), R(WHITE), R(WHITE), R(YELLOW),        xxxxxxx,       xxxxxxx,  xxxxxxx,  xxxxxxx,
        xxxxxxx,   xxxxxxx,   xxxxxxx,   xxxxxxx,                                        R(WHITE),                        R(YELLOW), R(GREEN),  xxxxxxx,   xxxxxxx,  xxxxxxx,  xxxxxxx,
        xxxxxxx,   xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx
    ),
    [_SECRETS] = LAYOUT_rgb(LED_FLAG_NONE, RGB_MATRIX_SOLID_COLOR,
        xxxxxxx,   xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,
        xxxxxxx,   xxxxxxx,   R(GREEN),  R(GREEN),  R(GREEN), R(GREEN), R(GREEN), R(GREEN), xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,   xxxxxxx,
        xxxxxxx,   xxxxxxx,   xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,   xxxxxxx,
                   xxxxxxx,   xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,         xxxxxxx,       xxxxxxx,
        xxxxxxx,   xxxxxxx,   xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,         xxxxxxx,       xxxxxxx,  xxxxxxx,   xxxxxxx,
        xxxxxxx,   xxxxxxx,   xxxxxxx,   xxxxxxx,                                        xxxxxxx,                         xxxxxxx,  xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,   xxxxxxx,
        xxxxxxx,   xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx,    xxxxxxx
    ),
    [_ADJUST] = LAYOUT_rgb(LED_FLAG_NONE, RGB_MATRIX_SOLID_COLOR,
        R(GREEN),  R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),
        R(GREEN),  xxxxxxx,   xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,   R(GREEN),
        R(GREEN),  xxxxxxx,   R(BLUE),   R(YELLOW), R(BLUE),  R(GREEN), R(ORANGE),xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,   R(GREEN),
                   xxxxxxx,   R(MAGENTA),R(YELLOW), R(MAGENTA),R(GREEN),R(ORANGE),xxxxxxx,  xxxxxxx,  R(CORAL), R(CORAL), R(CORAL), xxxxxxx,         xxxxxxx,       xxxxxxx,
        R(GREEN),  xxxxxxx,   R(WHITE),  R(CYAN),   R(CYAN),  R(CYAN),  R(CYAN),  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,         xxxxxxx,       xxxxxxx,  xxxxxxx,   R(GREEN),
        R(GREEN),  xxxxxxx,   xxxxxxx,   xxxxxxx,                                        xxxxxxx,                         xxxxxxx,  xxxxxxx,   xxxxxxx,   xxxxxxx,  xxxxxxx,   R(GREEN),
        R(GREEN),  R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN),   R(GREEN)
    ),
    /*
    [X] = LAYOUT_rgb(
        _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,   _______,  _______,   _______,
        _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,   _______,  _______,   _______,
                   _______,   _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,         _______,       _______,
        _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,         _______,       _______,  _______,   _______,
        _______,   _______,   _______,   _______,                                        _______,                         _______,  _______,   _______,   _______,  _______,   _______,
        _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
    ),
    */
};

#undef _______
#define _______ KC_TRANS

static void set_rgb_layer(int layer) {
    const struct layer_rgb *cur = &rgbs[layer];

    switch (cur->type) {
        case type_hsv:
            for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT ; i++) {
                if (!(g_led_config.flags[i] & cur->flags))
                    rgb_matrix_set_color(i, 0, 0, 0);
            }
            rgb_matrix_set_flags(cur->flags);
            if (cur->mode >= RGB_MATRIX_EFFECT_MAX)
                rgb_matrix_mode_noeeprom(rgbs[cur->mode - RGB_MATRIX_EFFECT_MAX].mode);
            else
                rgb_matrix_mode_noeeprom(cur->mode);
            rgb_matrix_sethsv_noeeprom(cur->hsv.h, cur->hsv.s, cur->hsv.v);
            break;
        case type_rgb:
            rgb_matrix_set_flags(cur->flags);
            if (cur->mode >= RGB_MATRIX_EFFECT_MAX)
                rgb_matrix_mode_noeeprom(rgbs[cur->mode - RGB_MATRIX_EFFECT_MAX].mode);
            else
                rgb_matrix_mode_noeeprom(cur->mode);
            for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                const RGB *m = &cur->rgb[i];
                if (!RGB_IS_NULL(*m))
                    rgb_matrix_set_color(i, m->r, m->g, m->b);
            }
            break;
    }
}

// Runs just one time when the keyboard initializes.
void matrix_init_keymap(void) {
    // force numlock on upon startup
    if (!NUMLOCK_ON) {
        tap_code(KC_NUM_LOCK);
    }
};

LEADER_EXTERNS();

// Runs constantly in the background, in a loop.
void matrix_scan_keymap(void) {
    if (rgb_matrix_get_flags() != LED_FLAG_NONE && timer_elapsed(rgb_timer) > 1000) {
        rgb_idle_seconds++;
        rgb_timer = timer_read();
    }
    if (rgb_idle_seconds > IDLE_TIMEOUT) {
        rgb_matrix_disable_noeeprom();
        rgb_idle_seconds = 0;
    }
    if (IS_LAYER_ON(_KP)) {
        if (NUMLOCK_ON)
            rgb_matrix_set_color(15, RGB_GOLD);
        else
            rgb_matrix_set_color(15, 0, 0, 0);
    }
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_K) {
            layer_invert(_KP);
        }
        SEQ_ONE_KEY(KC_G) {
            layer_invert(_GAME);
        }
        SEQ_ONE_KEY(KC_KP_5) {
            layer_invert(_KP);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_1) {
            send_secret_string(0);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_2) {
            send_secret_string(1);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_3) {
            send_secret_string(2);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_4) {
            send_secret_string(3);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_5) {
            send_secret_string(4);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_6) {
            send_secret_string(5);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_M) {
            send_secret_string(0);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_COMM) {
            send_secret_string(1);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_DOT) {
            send_secret_string(2);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_J) {
            send_secret_string(3);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_K) {
            send_secret_string(4);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_L) {
            send_secret_string(5);
        }
    }
};

layer_state_t layer_state_set_keymap(layer_state_t state) {
    dprintf("layer: %d\n", get_highest_layer(state));
    set_rgb_layer(get_highest_layer(state));
#ifdef AUTO_SHIFT_ENABLE
    autoshift_enable();
#endif
    if (layer_state_cmp(state, _GAME)) {
        save_layer = _GAME;
#ifdef AUTO_SHIFT_ENABLE
        autoshift_disable();
#endif
    }
    else if (layer_state_cmp(state, _QWERTY))
        save_layer = _QWERTY;
    return state;
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    struct layer_rgb *rgb_base_layer = &rgbs[save_layer];

    rgb_idle_seconds = 0;
    rgb_matrix_enable_noeeprom();

    switch (keycode) {
        // custom handle QK_GESC to emulate auto shift on it
        case QK_GRAVE_ESCAPE:
#ifdef AUTO_SHIFT_ENABLE
            if (get_autoshift_state()) {
                static uint16_t gesc_timer;
                if (record->event.pressed)
                    gesc_timer = timer_read();
                else {
                    if (timer_elapsed(gesc_timer) > AUTO_SHIFT_TIMEOUT || MODS_SHIFT) {
                        tap_code16(S(KC_GRV));
                    } else if (MODS_GUI)
                        tap_code(KC_GRV);
                    else
                        tap_code(KC_ESC);
                }
                return false;
            }
#else // AUTO_SHIFT_ENABLE
            return true;
#endif // AUTO_SHIFT_ENABLE
            break;

        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case RGB_MOD:
            if (record->event.pressed) {
                if (++rgb_base_layer->mode >= RGB_MATRIX_EFFECT_MAX)
                    rgb_base_layer->mode = RGB_MATRIX_NONE;
                set_rgb_layer(save_layer);
            }
            return false;
        case RGB_RMOD:
            if (record->event.pressed) {
                if (--rgb_base_layer->mode <= RGB_MATRIX_NONE)
                    rgb_base_layer->mode = RGB_MATRIX_EFFECT_MAX - 1;
                set_rgb_layer(save_layer);
            }
            return false;
        case RGB_HUI:
            if (rgb_base_layer->type == type_hsv && record->event.pressed) {
                if (rgb_base_layer->hsv.h > 235)
                    rgb_base_layer->hsv.h = 255;
                else
                    rgb_base_layer->hsv.h += 20;
            }
            set_rgb_layer(save_layer);
            return false;
        case RGB_HUD:
            if (rgb_base_layer->type == type_hsv && record->event.pressed) {
                if (rgb_base_layer->hsv.h < 20)
                    rgb_base_layer->hsv.h = 0;
                else
                    rgb_base_layer->hsv.h -= 20;
            }
            set_rgb_layer(save_layer);
            return false;
        case RGB_SAI:
            if (rgb_base_layer->type == type_hsv && record->event.pressed) {
                if (rgb_base_layer->hsv.s > 235)
                    rgb_base_layer->hsv.s = 255;
                else
                    rgb_base_layer->hsv.s += 20;
            }
            set_rgb_layer(save_layer);
            return false;
        case RGB_SAD:
            if (rgb_base_layer->type == type_hsv && record->event.pressed) {
                if (rgb_base_layer->hsv.s < 20)
                    rgb_base_layer->hsv.s = 0;
                else
                    rgb_base_layer->hsv.s -= 20;
            }
            set_rgb_layer(save_layer);
            return false;
        case RGB_VAI:
            if (rgb_base_layer->type == type_hsv && record->event.pressed) {
                if (rgb_base_layer->hsv.v > 235)
                    rgb_base_layer->hsv.v = 255;
                else
                    rgb_base_layer->hsv.v += 20;
            }
            set_rgb_layer(save_layer);
            return false;
        case RGB_VAD:
            if (rgb_base_layer->type == type_hsv && record->event.pressed) {
                if (rgb_base_layer->hsv.v < 20)
                    rgb_base_layer->hsv.v = 0;
                else
                    rgb_base_layer->hsv.v -= 20;
            }
            set_rgb_layer(save_layer);
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_base_layer->flags) {
                    case LED_FLAG_ALL:
                        rgb_base_layer->flags = LED_FLAG_KEYLIGHT;
                        break;
                    case LED_FLAG_KEYLIGHT:
                        rgb_base_layer->flags = LED_FLAG_UNDERGLOW;
                        break;
                    case LED_FLAG_UNDERGLOW:
                        rgb_base_layer->flags = LED_FLAG_NONE;
                        break;
                    default:
                        rgb_base_layer->flags = LED_FLAG_ALL;
                        break;
                }
            }
            set_rgb_layer(save_layer);
            return false;
        default:
            return true; //Process all other keycodes normally
    }
    return true;
}
