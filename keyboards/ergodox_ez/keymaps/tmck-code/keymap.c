#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    BASE,  // default layer
    SYMB,  // symbols
    MDIA,  // media keys
};

enum custom_keycodes {
    VRSN = SAFE_RANGE,
    SOCD_W,
    SOCD_A,
    SOCD_S,
    SOCD_D,
    NULLBIND_TOGGLE,
};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 *                                                 ,--------------------------------------------------.                         ,--------------------------------------------------.
 *                                                 |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |                         | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 *                                                 |--------+------+------+------+------+-------------|                         |------+------+------+------+------+------+--------|
 *                                                 | Del    |   Q  |   W  |   E  |   R  |   T  |  L1  |                         | End  |   Y  |   U  |   I  |   O  |   P  |   \    |
 *                                                 |--------+------+------+------+------+------|      |                         |      |------+------+------+------+------+--------|
 *                                                 | BkSp   |   A  |   S  |   D  |   F  |   G  |------|                         |------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
 *                                                 |--------+------+------+------+------+------| Hyper|                         | Home |------+------+------+------+------+--------|
 *                                                 | LShift | Z/L1 |   X  |   C  |   V  |   B  |      |                         |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 *                                                 `--------+------+------+------+------+-------------'                         `-------------+------+------+------+------+--------'
 *                                                   | Grv/ |'"/L2 |AltShf| Left | Right|                                                     |  Up  | Down |   [  |   ]  | AltR |
 *                                                   `-Ctrl-----------------------------'                                                     `----------------------------------'
 *                                                                                        ,-------------.                     ,-------------.
 *                                                                                        | App  | LGui |                     | Alt  |Ctrl/Esc|
 *                                                                                 ,------|------|------|                     |------+--------+------.
 *                                                                                 |      |      | Home |                     | PgUp |        |      |
 *                                                                                 | Space|Backsp|------|                     |------|  Enter | Tab  |
 *                                                                                 |      |ace   | End  |                     | PgDn |        |      |
 *                                                                                 `--------------------'                     `----------------------'
 */
[BASE] = LAYOUT_ergodox_pretty(
  // left hand
    KC_EQUAL,               KC_1,           KC_2,             KC_3,    KC_4,     KC_5,     NULLBIND_TOGGLE,             KC_DELETE,   KC_6,      KC_7,  KC_8,     KC_9,    KC_0,                   KC_MINUS,
    KC_ESCAPE,              KC_Q,           SOCD_W,           KC_E,    KC_R,     KC_T,     LCTL(LSFT(KC_ESCAPE)),       KC_END,      KC_Y,      KC_U,  KC_I,     KC_O,    KC_P,                   KC_BSLS,
    KC_CAPS,                SOCD_A,         SOCD_S,           SOCD_D,  KC_F,     KC_G,                                               KC_H,      KC_J,  KC_K,     KC_L,    KC_SCLN,                MT(MOD_LGUI, KC_QUOTE),
    KC_LEFT_SHIFT,          LT(1,KC_Z),     KC_X,             KC_C,    KC_V,     KC_B,     KC_TRANSPARENT,              KC_HOME,     KC_N,      KC_M,  KC_COMMA, KC_DOT,  MT(MOD_RCTL, KC_SLASH), KC_RIGHT_SHIFT,
    MT(MOD_LCTL, KC_GRAVE), LT(2,KC_QUOTE), LALT(LSFT(KC_D)), KC_LEFT, KC_RIGHT,                                                                KC_UP, KC_DOWN,  KC_LBRC, KC_RBRC,                RCTL(KC_RIGHT_ALT),
                                                                                 KC_LEFT_ALT,       KC_ESCAPE,          KC_LEFT_ALT, MT(MOD_LCTL, KC_ESCAPE),
                                                                                                    KC_HOME,            KC_PAGE_UP,
                                                                                 KC_SPACE, KC_BSPC, KC_END,             KC_PGDN,     KC_ENTER,  KC_TAB
  ),
/* Keymap 1: Symbol Layer
 *
 *                                                              ,---------------------------------------------------.                         ,--------------------------------------------------.
 *                                                              |CmdShiftU|  F1  |  F2  |  F3  |  F4  |  F5  |      |                         |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 *                                                              |---------+------+------+------+------+------+------|                         |------+------+------+------+------+------+--------|
 *                                                              |CmdShiftA|   !  |   @  |   {  |   }  |   |  |      |                         |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 *                                                              |---------+------+------+------+------+------|      |                         |      |------+------+------+------+------+--------|
 *                                                              |CmdShiftS|   #  |   $  |   (  |   )  |   `  |------|                         |------| Down |   4  |   5  |   6  |   +  |        |
 *                                                              |---------+------+------+------+------+------|      |                         | Cmd+ |------+------+------+------+------+--------|
 *                                                              |         |   %  |   ^  |   [  |   ]  |   ~  |      |                         |Shift+|   &  |   1  |   2  |   3  |   \  |        |
 *                                                              `---------+------+------+------+------+-------------'                         `-A-----------+------+------+------+------+--------'
 *                                                                | EPRM  |      |      |      |      |                                                     |      |    . |   0  |   =  |      |
 *                                                                `-----------------------------------'                                                     `----------------------------------'
 *                                                                                                     ,-------------.                     ,-------------.
 *                                                                                                     |Animat|      |                     |Toggle|Solid |
 *                                                                                              ,------|------|------|                     |------+------+------.
 *                                                                                              |Bright|Bright|      |                     |      |Hue-  |Hue+  |
 *                                                                                              |ness- |ness+ |------|                     |------|      |      |
 *                                                                                              |      |      |      |                     |      |      |      |
 *                                                                                              `--------------------'                     `--------------------'
 */
[SYMB] = LAYOUT_ergodox_pretty(
  // left hand
LGUI(LSFT(KC_U)), KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,
LGUI(LSFT(KC_A)), KC_EXLM,        KC_AT,          KC_LCBR,        KC_RCBR,        KC_PIPE,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_UP,          KC_7,           KC_8,           KC_9,           KC_ASTR,        KC_F12,
LGUI(LSFT(KC_S)), KC_HASH,        KC_DLR,         KC_LPRN,        KC_RPRN,        KC_GRAVE,                                                                       KC_DOWN,        KC_4,           KC_5,           KC_6,           KC_TRANSPARENT, KC_TRANSPARENT,
  KC_TRANSPARENT, KC_TRANSPARENT, KC_CIRC,        KC_LBRC,        KC_RBRC,        KC_TILD,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_AMPR,        KC_1,           KC_2,           KC_3,           KC_BSLS,        KC_TRANSPARENT,
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_DOT,         KC_0,           KC_EQUAL,       KC_TRANSPARENT,
                                                                                                  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                  KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
),

/* Keymap 2: Media and mouse keys
 *
 *                                               ,--------------------------------------------------.                                                ,--------------------------------------------------.
 *                                               |        |      |      |      |      |      |      |                                                |      |      |      |      |      |      |        |
 *                                               |--------+------+------+------+------+-------------|                                                |------+------+------+------+------+------+--------|
 *                                               |        |      |      | MsUp |      |      |      |                                                |      |      |      |      |      |      |        |
 *                                               |--------+------+------+------+------+------|      |                                                |      |------+------+------+------+------+--------|
 *                                               |        |      |MsLeft|MsDown|MsRght|      |------|                                                |------|      |      |      |      |      |  Play  |
 *                                               |--------+------+------+------+------+------|      |                                                |      |------+------+------+------+------+--------|
 *                                               |        |      |      |      |      |      |      |                                                |      |      |      | Prev | Next |      |        |
 *                                               `--------+------+------+------+------+-------------'                                                `-------------+------+------+------+------+--------'
 *                                                 |      |      |      | Lclk | Rclk |                                                                            |VolUp |VolDn | Mute |      |      |
 *                                                 `----------------------------------'                                                                            `----------------------------------'
 *                                                                                      ,-------------.                                            ,-------------.
 *                                                                                      |      |      |                                            |      |      |
 *                                                                               ,------|------|------|                                            |------+------+------.
 *                                                                               |      |      |      |                                            |      |      |Brwser|
 *                                                                               |      |      |------|                                            |------|      |Back  |
 *                                                                               |      |      |      |                                            |      |      |      |
 *                                                                               `--------------------'                                            `--------------------'
 */
[MDIA] = LAYOUT_ergodox_pretty(
  // left hand
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
  KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_UP,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
  KC_TRANSPARENT, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PLAY_PAUSE,
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_TRANSPARENT, KC_TRANSPARENT,
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN1,     KC_MS_BTN2,                                                                                                     KC_AUDIO_VOL_UP,KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE,  KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                  KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_ACCEL0,   KC_TRANSPARENT,
                                                                                                                  KC_TRANSPARENT, KC_MS_ACCEL1,
                                                                                  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_ACCEL2,   KC_TRANSPARENT, KC_WWW_BACK
),
};
// clang-format on

bool w_down = false;
bool a_down = false;
bool s_down = false;
bool d_down = false;

bool nullbind_enabled = false;

bool nullbind_turn(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SOCD_W:
            if (record->event.pressed) {
                if (s_down && nullbind_enabled) {
                    unregister_code(KC_S);
                }
                register_code(KC_W);
                w_down = true;
            } else {
                unregister_code(KC_W);
                w_down = false;
                if (s_down && nullbind_enabled) {
                    register_code(KC_S);
                }
            }
            return false;
            break;
        case SOCD_A:
            if (record->event.pressed) {
                if (d_down && nullbind_enabled) {
                    unregister_code(KC_D);
                }
                register_code(KC_A);
                a_down = true;
            } else {
                unregister_code(KC_A);
                a_down = false;
                if (d_down && nullbind_enabled) {
                    register_code(KC_D);
                }
            }
            return false;
            break;
        case SOCD_S:
            if (record->event.pressed) {
                if (w_down && nullbind_enabled) {
                    unregister_code(KC_W);
                }
                register_code(KC_S);
                s_down = true;
            } else {
                unregister_code(KC_S);
                s_down = false;
                if (w_down && nullbind_enabled) {
                    register_code(KC_W);
                }
            }
            return false;
            break;
        case SOCD_D:
            if (record->event.pressed) {
                if (a_down && nullbind_enabled) {
                    unregister_code(KC_A);
                }
                register_code(KC_D);
                d_down = true;
            } else {
                unregister_code(KC_D);
                d_down = false;
                if (a_down && nullbind_enabled) {
                    register_code(KC_A);
                }
            }
            return false;
            break;
    }
    return true;
}

bool nullbind_toggle(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (nullbind_enabled) {
            ergodox_right_led_1_off();
            nullbind_enabled = false;
        } else {
            ergodox_right_led_1_on();
            nullbind_enabled = true;
        }
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VRSN:
            SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;
        case NULLBIND_TOGGLE:
            return nullbind_toggle(keycode, record);
            break;
    }
    return nullbind_turn(keycode, record);
    return true;
}

// Runs just one time when the keyboard initializes.
void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case 0:
#ifdef RGBLIGHT_COLOR_LAYER_0
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
            break;
        case 1:
            ergodox_right_led_1_on();
#ifdef RGBLIGHT_COLOR_LAYER_1
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
#endif
            break;
        case 2:
            ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_2
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
#endif
            break;
        case 3:
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_3
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
#endif
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_4
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
#endif
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_5
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
#endif
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_6
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
#endif
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_7
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
#endif
            break;
        default:
            break;
    }

    return state;
};
