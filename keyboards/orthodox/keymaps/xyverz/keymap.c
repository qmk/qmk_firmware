#include QMK_KEYBOARD_H

enum layer_names { _QWERTY, _COLEMAK, _DVORAK, _LOWER, _RAISE, _ADJUST };

enum custom_keycodes { QWERTY = SAFE_RANGE, COLEMAK, DVORAK, LOWER, RAISE, ADJUST };

// Aliases to keep the keymap tidy
#define ADJUST MO(_ADJUST)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DVORAK] = LAYOUT (
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                                                                   KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
  KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,             KC_LCTL, KC_LALT,          KC_RGUI, KC_RCTL,          KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    LOWER,   KC_BSPC, KC_LGUI,          KC_ENT,  KC_SPC,  RAISE,   KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT
),

[_QWERTY] = LAYOUT (
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                                   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_LCTL, KC_LALT,          KC_RGUI, KC_RCTL,          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    LOWER,   KC_BSPC, KC_LGUI,          KC_ENT,  KC_SPC,  RAISE,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT
),

[_COLEMAK] = LAYOUT (
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                                                                   KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,             KC_LCTL, KC_LALT,          KC_RGUI, KC_RCTL,          KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    LOWER,   KC_BSPC, KC_LGUI,          KC_ENT,  KC_SPC,  RAISE,   KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT
),

[_LOWER] = LAYOUT (
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                                                KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,          _______, KC_HOME,          KC_PGUP, _______,          _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  _______, _______, KC_LEFT, KC_RGHT, _______, _______, _______, KC_DEL,  KC_END,           KC_PGDN, KC_INS,  _______, _______, _______, KC_UP,   KC_DOWN, _______, _______
),

[_RAISE] = LAYOUT (
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                                   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  KC_CAPS, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,          _______, KC_HOME,          KC_PGUP, _______,          _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, _______, KC_LEFT, KC_RGHT, _______, _______, _______, KC_DEL,  KC_END,           KC_PGDN, KC_INS,  _______, _______, _______, KC_UP,   KC_DOWN, _______, _______
),

[_ADJUST] = LAYOUT (
  KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                                                  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12 ,
  _______, QK_BOOT, _______, _______, _______, _______,          _______, _______,          _______, _______,          _______, QWERTY , COLEMAK, DVORAK,  _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______
)


};
// clang-format on

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void matrix_init_user(void) {
#ifdef BOOTLOADER_CATERINA
    // This will disable the red LEDs on the ProMicros
    setPinInput(D5);
    setPinInput(B0);
#endif
};

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QWERTY:
                set_single_persistent_default_layer(_QWERTY);
                return false;
            case COLEMAK:
                set_single_persistent_default_layer(_COLEMAK);
                return false;
            case DVORAK:
                set_single_persistent_default_layer(_DVORAK);
                return false;
        }
    }
    return true;
}
