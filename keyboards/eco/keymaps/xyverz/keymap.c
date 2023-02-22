#include QMK_KEYBOARD_H

enum layer_names { _QWERTY, _COLEMAK, _DVORAK, _LOWER, _RAISE, _ADJUST };

enum custom_keycodes { QWERTY = SAFE_RANGE, COLEMAK, DVORAK, LOWER, RAISE, ADJUST };

// Aliases to keep the keymap tidy
#define GUIBSPC GUI_T(KC_BSPC)  // GUI when held, BSPC when tapped.

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-------------------------------------------------------------------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |      |      |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * | Esc  |   A  |   S  |   D  |   F  |   G  |      |      |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |      |      |   N  |   M  |   ,  |   .  |   /  |Shift |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * | Ctrl | Alt  | Left |Right |Lower | Bksp |  GUI |Enter |Space |Raise |  Up  | Down |  GUI |Enter |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,   KC_NO,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_NO,   KC_NO,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_NO,   KC_NO,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC, KC_LGUI, KC_ENT,  KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_ENT
  ),

  /* Colemak
   * ,-------------------------------------------------------------------------------------------------.
   * | Tab  |   Q  |   W  |   F  |   P  |   G  |      |      |   J  |   L  |   U  |   Y  |   ;  | Bksp |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * | Esc  |   A  |   R  |   S  |   T  |   D  |      |      |   H  |   N  |   E  |   I  |   O  |  "   |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |      |      |   N  |   M  |   ,  |   .  |   /  |Shift |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * | Ctrl | Alt  | Left |Right |Lower | Bksp |  GUI |Enter |Space |Raise |  Up  | Down |  GUI |Enter |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_COLEMAK] = LAYOUT(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_NO,   KC_NO,   KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_NO,   KC_NO,   KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_NO,   KC_NO,   KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC, KC_LGUI, KC_ENT,  KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_ENT
  ),

  /* Dvorak
   * ,-------------------------------------------------------------------------------------------------.
   * | Tab  |   "  |   ,  |   .  |   P  |   Y  |      |      |   F  |   G  |   C  |   R  |   L  |  /   |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * | Esc  |   A  |   O  |   E  |   U  |   I  |      |      |   D  |   H  |   T  |   N  |   S  |  -   |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * | Shift|   ;  |   Q  |   J  |   K  |   X  |      |      |   B  |   M  |   W  |   V  |   Z  | Shift|
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * | Ctrl | Alt  | Left |Right |Lower | Bksp |  GUI |Enter |Space |Raise |  Up  | Down |  GUI |Enter |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_DVORAK] = LAYOUT(
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_NO,   KC_NO,   KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
    KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_NO,   KC_NO,   KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_NO,   KC_NO,   KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
    KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, LOWER,   KC_BSPC, KC_LGUI, KC_ENT,  KC_SPC,  RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_ENT
  ),

  /* Lower
   * ,-------------------------------------------------------------------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |      |      |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * | Caps |      | Mute | Vol- | Vol+ |      |      |      |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * |      |      | Prev | Play | Next |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * | Brite|      | Home |  End |      |  Del |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_NO,   KC_NO,   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_NO,   KC_NO,   _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_NO,   KC_NO,   _______, _______, _______, _______, _______, _______,
    _______, _______, KC_HOME, KC_END,  _______, KC_DEL,  _______, _______, KC_INS,  _______, KC_PGUP, KC_PGDN, _______, _______
  ),

  /* Raise
   * ,-------------------------------------------------------------------------------------------------.
   * |      |   1  |   2  |   3  |   4  |   5  |      |      |   6  |   7  |   8  |   9  |   0  |   -  |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_NO,   KC_NO,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_NO,   KC_NO,   _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_NO,   KC_NO,   _______, _______, _______, _______, _______, _______,
    _______, _______, KC_HOME, KC_END,  _______, KC_DEL,  _______, _______, KC_INS,  _______, KC_PGUP, KC_PGDN, _______, _______
  ),


  /* Adjust
   * ,-------------------------------------------------------------------------------------------------.
   * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * |      | Reset|      |      |      |      |      |      |      |Qwerty|Colemk|Dvorak|      |      |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] = LAYOUT(
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,   KC_NO,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12 ,
    _______, QK_BOOT, _______, _______, _______, _______, KC_NO,   KC_NO,   _______, QWERTY,  COLEMAK, DVORAK,  _______, _______,
    _______, _______, _______, _______, _______, _______, KC_NO,   KC_NO,   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

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
