#include QMK_KEYBOARD_H
#include "keymap_german.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
  _QWERTZ,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwertz
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Z  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   +  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Y  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   -  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | AltGr| Alt  |Lower |Space | Space| Raise| Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTZ] = LAYOUT( 
   KC_TAB,    DE_Q,    DE_W,    DE_E,   DE_R,     DE_T,    DE_Z,    DE_U,    DE_I,    DE_O,    DE_P, KC_BSPC,
   KC_ESC,    DE_A,    DE_S,    DE_D,    DE_F,    DE_G,    DE_H,    DE_J,    DE_K,    DE_L, DE_PLUS,  KC_ENT,
  KC_LSFT,    DE_Y,    DE_X,    DE_C,    DE_V,    DE_B,    DE_N,    DE_M, DE_COMM,  DE_DOT, DE_MINS, KC_RSFT,
  KC_LCTL, KC_LGUI, KC_ALGR, KC_LALT,   LOWER,  KC_SPC,  KC_SPC,   RAISE, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   °  |   !  |   ?  |   §  |   €  |   ~  |   $  |   (  |   )  |   <  |   >  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  | Vol+ | Prev | Next | Play |   &  |   @  |   {  |   }  |   [  |   ]  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift| Vol- |      |      |      |   |  |   %  |   /  |   \  |   '  |   "  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |      |      |      |Lower |             | Raise|   =  |   *  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT( 
  DE_CIRC, DE_EXLM, DE_QUES, DE_SECT, DE_EURO,  DE_TILD,  DE_DLR, DE_LPRN, DE_RPRN, DE_LABK, DE_RABK, KC_BSPC,
   KC_DEL, KC_VOLU, KC_MPRV, KC_MNXT, KC_MPLY,  DE_AMPR,   DE_AT, DE_LCBR, DE_RCBR, DE_LBRC, DE_RBRC,  KC_ENT,
  KC_LSFT, KC_VOLD, _______, _______, _______,  DE_PIPE, DE_PERC, DE_SLSH, DE_BSLS, DE_QUOT, DE_DQUO, KC_RSFT,
  KC_LCTL, _______, _______, _______, _______,  _______, _______, _______,  DE_EQL, DE_ASTR, _______, _______ 
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   /  |   7  |   8  |   9  |   *  |      |      |      |   #  |  Alt |   `  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |   4  |   5  |   6  |   -  | Pos1 |  End |   ä  |   ö  |   ü  |   ß  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   1  |   2  |   3  |   +  |PageUp|PageDn|      |      |      |      |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   .  |  0   |   =  |Lower |             | Raise|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT( 
  DE_SLSH,    KC_7,    KC_8,    KC_9, DE_ASTR, _______, _______, _______, DE_HASH, KC_LALT, DE_ACUT, KC_BSPC,
   KC_DEL,    KC_4,    KC_5,    KC_6, DE_MINS, KC_HOME,  KC_END,   DE_ADIA, DE_ODIA, DE_UDIA, DE_SS,  KC_ENT,
  KC_LSFT,    KC_1,    KC_2,    KC_3, DE_PLUS, KC_PGUP, KC_PGDN, _______, _______, _______, _______, KC_LSFT,
  _______,  DE_DOT,    KC_0,  DE_EQL, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  F13 |  F14 |  F15 |  F16 |  F17 |  F18 |  F19 |  F20 |  F21 |  F22 |  F23 |  F24 |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT( 
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
   KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,
  _______, _______, _______,   AU_ON,  AU_OFF, AG_NORM, AG_SWAP, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)


};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
