#include QMK_KEYBOARD_H

enum pteron_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// alt gr
#undef G
#define G(kc) RALT(kc)

// custom keycodes
// use F_ prefix to avoid problems

// NB! I use Norwegian keyboard layout on my machines, so the keymap probably
// doesn't make much sense for US/ANSI users

#define F_FSLH S(KC_7) // forward slash
#define F_BSLH KC_EQL // backward slash
#define F_EQL S(KC_0) // equals sign
#define F_APOS KC_BSLS // '
#define F_TIMES S(KC_BSLS) // *
#define F_PLUS KC_MINS // +
#define F_QUEST S(KC_MINS) // ?
#define F_HAT S(KC_RBRC) // ^
#define F_TILD G(KC_RBRC) // ~
#define F_UML KC_RBRC // ¨ (umlaut)
#define F_SECT S(KC_GRV) // section sign ("law sign") (shifted key below esc)
#define F_GRAVE S(KC_EQL)
#define F_ACUTE G(KC_EQL)

#define KC_AA KC_LBRC
#define KC_OE KC_SCLN
#define KC_AE KC_QUOT

// brackets
#define F_SBRL G(KC_8) // square bracket left
#define F_SBRR G(KC_9) // square bracket right
#define F_CBRL G(KC_7) // curly bracket left
#define F_CBRR G(KC_0) // curly bracket right
#define F_RBRL S(KC_8) // round bracket left
#define F_RBRR S(KC_9) // round bracket right
#define F_ABRL KC_NUBS // angle bracket left
#define F_ABRR S(KC_NUBS) // angle bracket right

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * +-----------------------------------------+                                +-----------------------------------------+
 * | Esc  |   1  |   2  |   3  |   4  |   5  |                                |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------|                                |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                                |   Y  |   U  |   I  |   O  |   P  |   Å  |
 * |------+------+------+------+------+------|                                |------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |                                |   H  |   J  |   K  |   L  |   Ø  |   Æ  |
 * |------+------+------+------+------+------|                                |------+------+------+------+------+------|
 * | Shft |   Z  |   X  |   C  |   V  |   B  |                                |   N  |   M  |   ,  |   .  |   -  | Shft |
 * +---------------------------+------+------+-------------+    +-------------+------+------+---------------------------+
 *                             | LOWR | Spc  | Alt  | Win  |    | Win  | Alt  | Spc  | RISE |
 *                             +---------------------------+    +---------------------------+
 */

[_QWERTY] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_AA,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_OE,   KC_AE,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSHIFT,
                          LOWER,   KC_SPC,  KC_LALT, KC_LGUI,          KC_RGUI, KC_RALT, KC_ENT,  RAISE
    ),

/* LOWER
 * +-----------------------------------------+                                +-----------------------------------------+
 * |      |      |      |      |      |      |                                |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                                |   \  |   /  |   [  |   ]  |   =  | Del  |
 * |------+------+------+------+------+------|                                |------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                                |   <  |   >  |   (  |   )  |   *  |   ~  |
 * |------+------+------+------+------+------|                                |------+------+------+------+------+------|
 * |      |  F6  |  F7  |  F8  |  F9  |  F10 |                                |  F11 |  F12 |   {  |   }  |   +  |      |
 * +---------------------------+------+------+-------------+    +-------------+------+------+---------------------------+
 *                             |      |      |      |      |    |      |      |      |      |
 *                             +---------------------------+    +---------------------------+
 */

[_LOWER] = LAYOUT(
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,          F_BSLH,  F_FSLH,  F_SBRL,  F_SBRR,  F_EQL,   KC_DEL,
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,            F_ABRL,  F_ABRR,  F_RBRL,  F_RBRR,  F_TIMES, F_TILD,
        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,           KC_F11,  KC_F12,  F_CBRL,  F_CBRR,  F_PLUS,  _______,
                          _______, _______, _______, _______,          _______, _______, _______, _______
    ),

[_RAISE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_AA,
        F_SECT,  S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),          F_QUEST, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, F_APOS,
        _______, S(KC_6), G(KC_2), G(KC_3), G(KC_4), G(KC_5),          F_HAT,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
                          _______, _______, _______, _______,          _______, _______, _______, _______
    ),

[_ADJUST] = LAYOUT(
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
        _______, F_UML,   F_GRAVE, F_ACUTE, _______, QK_BOOT,          _______, _______, _______, _______, KC_PSCR, _______,
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,          _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______,
                          _______, _______, _______, _______,          _______, _______, _______, _______
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
