#include QMK_KEYBOARD_H

enum layer_names {
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE
};

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

enum combos {
  AB_ESC,
  JK_TAB
};

enum combo_events {
  ZC_COPY,
  XV_PASTE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Ctl/Es|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | FN   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  `   | Alt  | GUI  |Lower |Space |Enter |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    LCTL_T(KC_ESC),  KC_A,   KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    KC_LCTL, KC_GRAVE, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Colemak-DH
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Ctl/Es|   A  |   R  |   S  |   T  |   G  |   K  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   D  |   V  |   M  |   H  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |Space |Enter |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_ortho_4x12(
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  LCTL_T(KC_ESC),  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_K,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_M,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  KC_LCTL, KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      | Mute |      |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |Lower | Bksp | Bksp |Raise | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
    KC_GRV, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    _______, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(LSFT(KC_V)), KC_F11,  KC_F12, _______, _______, _______, _______, _______,
    _______, LCTL(KC_Y), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   [  |   ]  |  |   |  \   |      |      |   _  |   =  |   -  |   +  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |Pg Up |Pg Dn | Home | End  |PrtSn |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
    KC_TILD, KC_LBRC, KC_RBRC, KC_PIPE, KC_BSLS, _______, _______, KC_UNDS, KC_EQL,  KC_MINS, KC_PLUS, KC_BSPC,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN, KC_HOME, KC_END, KC_PSCR,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Taskmg|      |      |      |      |      |      |      |      |      |      |caltde|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | RESET|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12(
  TSKMGR,  QWERTY, COLEMAK, _______, _______, _______, _______, _______, _______, _______, CMB_TOG, CALTDEL,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
  }
  return true;
}

const uint16_t PROGMEM copy_combo[] = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_V, COMBO_END};

const uint16_t PROGMEM ab_combo[] = {KC_A, KC_B, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
  [AB_ESC] = COMBO(ab_combo, KC_ESC),
  [JK_TAB] = COMBO(jk_combo, KC_TAB),
  [ZC_COPY] = COMBO_ACTION(copy_combo),
  [XV_PASTE] = COMBO_ACTION(paste_combo),
};

void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case ZC_COPY:
      if (pressed) {
        tap_code16(LCTL(KC_C));
      }
      break;
    case XV_PASTE:
      if (pressed) {
        tap_code16(LCTL(KC_V));
      }
      break;
  }
}
