#include "nyquist.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _VIM 2
#define _GAME 3

enum custom_macros {
    DLEFT,
    DRIGHT,
    PSCREEN_APP
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |LTVIMF|   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |/ Ctrl| Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  Alt |  F4  | GUI  |Lower | Bksp | Spc  | Ent  |  Alt |   +  | Game | Del  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
    KC_GRV,        KC_1,         KC_2,  KC_3,    KC_4,           KC_5,    KC_6,    KC_7,    KC_8,    KC_9,   KC_0,            KC_MINUS, \
    KC_TAB,        KC_Q,         KC_W,  KC_E,    KC_R,           KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,            KC_BSLASH, \
    KC_ESC,        KC_A,         KC_S,  KC_D,    LT(_VIM, KC_F), KC_G,    KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN,         KC_QUOT, \
    OSM(MOD_LSFT), LCTL_T(KC_Z), KC_X,  KC_C,    KC_V,           KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT, RCTL_T(KC_SLSH), OSM(MOD_RSFT), \
    KC_LCTL,       KC_LALT,      KC_F4, KC_LGUI, OSL(_LOWER),    KC_BSPC, KC_SPC,  KC_ENT,  KC_LOCK, KC_EQL, TG(_GAME),       KC_DEL \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | Caps |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   !  |   @  |   (  |   )  |   |  |   7  |   8  |   9  |   *  |   )  |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   #  |   $  |   {  |   }  |   `  |   4  |   5  |   6  |   +  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | APscr|   %  |   ^  |   [  |   ]  |   ~  |   1  |   2  |   3  |   \  | Vol- | Vol+ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Pscr |      |      |      |      |      |   0  |   .  |   =  | Prev | Next | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = KEYMAP( \
    KC_CAPS,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11, \
    _______,        KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, KC_PIPE, KC_7,  KC_8,   KC_9,   KC_ASTR, KC_RPRN, KC_F12, \
    _______,        KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_GRV,  KC_4,  KC_5,   KC_6,   KC_PLUS, KC_RCBR, KC_PIPE, \
    M(PSCREEN_APP), KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_1,  KC_2,   KC_3,   KC_BSLS, KC_VOLD, KC_VOLU, \
    KC_PSCR,        _______, _______, _______, _______, _______, KC_0,  KC_DOT, KC_EQL, KC_MPRV, KC_MNXT, KC_MPLY \
),

/* Vim Movement (Hold down F)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | DLeft|DRight| LCTRL|      |      | Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | LShft|      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_VIM] =  KEYMAP( \
    _______, _______,  _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______,  _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, M(DLEFT), M(DRIGHT), KC_LCTL, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
    _______, _______,  _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______,  _______,   _______, KC_LSFT, _______, _______, _______, _______, _______, _______, _______ \
),

/* Gaming mode (Raise)
 * All one-shot mods are disabled on this layer
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL |      |      |      |   F  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |      |      |      |      |      |      |      |      |      |  GUI |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Enter|      | Lock | Bksp |  Alt |  Spc | Lower| Left |  Up  | Down | Right|QWERTY|
 * `-----------------------------------------------------------------------------------'
 */
[_GAME] =  KEYMAP( \
    KC_ESC,  _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,    \
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,    \
    KC_LCTL, _______, _______, _______, KC_F,    _______, _______,     _______, _______, _______, _______, _______,    \
    KC_LSFT, KC_Z,    _______, _______, _______, _______, _______,     _______, _______, _______, _______, KC_LGUI,    \
    KC_ENT,  _______, KC_LOCK, KC_BSPC, KC_LALT, KC_SPC,  OSL(_LOWER), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, TO(_QWERTY) \
)

};

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch(id) {
        case DLEFT:
            if (record->event.pressed) { // Windows move desktop left
                return MACRO(D(LCTL), D(LGUI), T(LEFT), U(LGUI), U(LCTL), END);
            }
            break;
        case DRIGHT:
            if (record->event.pressed) { // Windows move desktop right
                return MACRO(D(LCTL), D(LGUI), T(RIGHT), U(LGUI), U(LCTL), END);
            }
            break;
        case PSCREEN_APP:
            if (record->event.pressed) {
                return MACRO(D(LALT), T(PSCR), U(LALT), END);
            }
            break;
    }
    return MACRO_NONE;
}
