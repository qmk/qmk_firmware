#include QMK_KEYBOARD_H
#include "brandonschlack.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* LAYOUT
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┼───┤
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │  2.0U │   │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │1.5U │   │   │   │   │   │   │   │   │   │   │   │   │1.5U │   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │1.75U │   │   │   │   │   │   │   │   │   │   │   │2.25U   │   │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │2.25U   │   │   │   │   │   │   │   │   │   │   │1.75U │   │   │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
     * │1.25│1.25│1.25│6.25U                   │1U │1U │1U │1U │1U │1U │
     * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
     */

    /* Base Layer: Mac
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ F1│ F2│ F3│ F4│ F5│ F6│ F7│ F8│ F9│F10│F11│F12│F13│F14│F15│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┼───┤
     * │~ `│! 1│@ 2│# 3│$ 4│% 5│^ 6│& 7│* 8│( 9│) 0│_ -│+ =│ Bckspc│Hom│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │Tab  │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │{ [│} ]│|   \│PgU│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │Caps  │ A │ S │ D │ F │ G │ H │ J │ K │ L │: ;│" '│   Enter│PgD│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │Shift   │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│? /│ Shift│ Up│End│
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
     * │Ctrl│ Opt│ Cmd│          Space         │Cmd│Opt│Fn │Lef│Dow│Rig│
     * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
     */
    [_MAC] = LAYOUT(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_MUTE,  KC_VOLD,  KC_VOLU,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   XXXXXXX,  KC_BSPC,  KC_HOME,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGUP,
        HY_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,                      KC_ENT,   KC_PGDN,
        KC_LSFT,  XXXXXXX,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,    KC_END,
        KC_LCTL,  KC_LALT,  KC_LGUI,                      XXXXXXX,  KC_SPC,   XXXXXXX,                      MM_RGUI,  MM_RALT,  MM_FN_M,  KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    [_MACFN] = LAYOUT(
        KC_MAKE,  KC_BRMD,  KC_BRMU,  MC_MSSN,  MC_LHPD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_MPLY,  KC_MRWD,  KC_MFFD,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_DEL,   MC_SLPD,
        RGB_MOD,  RGB_HUI,  RGB_SAI,  RGB_VAI,  RESET,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  MC_LHPD,            _______,
        _______,  RGB_HUD,  RGB_SAD,  RGB_VAD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      TG_MAGC,  _______,
        _______,  _______,  RGB_TOG,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  MM_RSFT,            KC_PGUP,  _______,
        _______,  _______,  _______,                      _______,  _______,  _______,                      _______,  _______,  _______,  KC_HOME,  KC_PGDN,  KC_END
    ),

    [_MAGIC] = LAYOUT(
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        RGB_MOD,  RGB_HUI,  RGB_SAI,  RGB_VAI,  RESET,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  RGB_HUD,  RGB_SAD,  RGB_VAD,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      TG_MAGC,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  RGB_TOG,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
    ),
};
