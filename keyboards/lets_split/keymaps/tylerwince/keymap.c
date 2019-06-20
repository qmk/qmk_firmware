#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum layer_names {
  _QWERTY = 0,
  _COLEMAK,
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST,
  SH_GOUP,
};

//Tap Dance Declarations
enum {
  TD_SEMI_COLON,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SEMI_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,------------------------------------------   ------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   |   Y  |   U  |   I  |   O  |   P  | BSPC |
 * |------+------+------+------+------+-------   -------+------+------+------+------+------|
 * |CTL/Es|   A  |   S  |   D  |   F  |   G  |   |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * |Shift |   Z  |   X  |   C  |   V  |   B  |   |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * |Things|1PASS | alt  | CMD  |Lower |Space |   |Space |Raise | Next | Vol- | Vol+ | Play |
 * `------------------------------------------   ------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12(
   KC_TAB,        KC_Q,          KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,              KC_BSPC,
   CTL_T(KC_ESC), KC_A,          KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    TD(TD_SEMI_COLON), KC_QUOT,
   KC_LSFT,       KC_Z,          KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH,           KC_ENT ,
   RALT(KC_SPC),  RGUI(KC_BSLS), KC_LALT, KC_LCMD, LOWER, KC_SPC, KC_SPC, RAISE, KC_MNXT, KC_VOLD, KC_VOLU,           KC_MPLY
),

/* Colemak
 * ,------------------------------------------   ------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------   -------+------+------+------+------+------|
 * |CTL/Es|   A  |   R  |   S  |   T  |   D  |   |   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * |Shift |   Z  |   X  |   C  |   V  |   B  |   |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * |Things|1PASS | alt  | CMD  |Lower |Space |   |Space |Raise | Next | Vol- | Vol+ | Play |
 * `------------------------------------------   ------------------------------------------'
 */
[_COLEMAK] = LAYOUT_ortho_4x12(
  KC_TAB,        KC_Q,          KC_W,    KC_F,    KC_P,  KC_G,   KC_J,   KC_L,  KC_U,    KC_Y,    TD(TD_SEMI_COLON), KC_BSPC,
  CTL_T(KC_ESC), KC_A,          KC_R,    KC_S,    KC_T,  KC_D,   KC_H,   KC_N,  KC_E,    KC_I,    KC_O,              KC_QUOT,
  KC_LSFT,       KC_Z,          KC_X,    KC_C,    KC_V,  KC_B,   KC_K,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH,           KC_ENT ,
  RALT(KC_SPC),  RGUI(KC_BSLS), KC_LALT, KC_LCMD, LOWER, KC_SPC, KC_SPC, RAISE, KC_MNXT, KC_VOLD, KC_VOLU,           KC_MPLY
),

/* Dvorak
 * ,------------------------------------------   ------------------------------------------.
 * | Tab  |   '  |   ,  |   .  |   P  |   Y  |   |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------   -------+------+------+------+------+------|
 * |CTL/Es|   A  |   O  |   E  |   U  |   I  |   |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * |Shift |   ;  |   Q  |   J  |   K  |   X  |   |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * |Things|1PASS | alt  | CMD  |Lower |Space |   |Space |Raise | Next | Vol- | Vol+ | Play |
 * `------------------------------------------   ------------------------------------------'
 */
[_DVORAK] = LAYOUT_ortho_4x12(
  KC_TAB,        KC_QUOT,           KC_COMM, KC_DOT,  KC_P,  KC_Y,   KC_F,   KC_G,  KC_C,    KC_R,    KC_L,    KC_BSPC,
  CTL_T(KC_ESC), KC_A,              KC_O,    KC_E,    KC_U,  KC_I,   KC_D,   KC_H,  KC_T,    KC_N,    KC_S,    KC_SLSH,
  KC_LSFT,       TD(TD_SEMI_COLON), KC_Q,    KC_J,    KC_K,  KC_X,   KC_B,   KC_M,  KC_W,    KC_V,    KC_Z,    KC_ENT ,
  RALT(KC_SPC),  RGUI(KC_BSLS),     KC_LALT, KC_LCMD, LOWER, KC_SPC, KC_SPC, RAISE, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Lower
 * ,------------------------------------------   ------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------   -------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   |      |   _  |   +  |   {  |   }  |  |   |
 * +------+------+------+------+------|------+   |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   |      |   -  |   =  |   [  |   ]  |      |
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * |Things|1PASS | alt  | CMD  |Lower |Space |   |Space |Raise | Next | Vol- | Vol+ | Play |
 * `------------------------------------------   ------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
  KC_TILD,      KC_EXLM,       KC_AT,   KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
  KC_F1,        KC_F2,         KC_F3,   KC_F4,   KC_F5,  KC_F6,   _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  KC_F7,        KC_F8,         KC_F9,   KC_F10,  KC_F11, KC_F12,  _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,
  RALT(KC_SPC), RGUI(KC_BSLS), KC_LALT, KC_LCMD, LOWER,  KC_SPC,  KC_SPC,  RAISE,   KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,------------------------------------------   ------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------   -------+------+------+------+------+------|
 * | Del  |      |      |      |      |      |   | LEFT | DOWN |  UP  |RIGHT |      |  \   |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |   |      |      |      |      |      |      |
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * |Things|1PASS | alt  | CMD  |Lower |Space |   |Space |Raise | Next | Vol- | Vol+ | Play |
 * `------------------------------------------   ------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
  KC_GRV,       KC_1,          KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_DEL,
  KC_DEL,       _______,       _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, KC_BSLS,
  _______,      _______,       _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
  RALT(KC_SPC), RGUI(KC_BSLS), KC_LALT, KC_LCMD, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_MNXT, KC_VOLD, KC_VOLU,  KC_MPLY
),

/* Adjust (Lower + Raise)
 * ,------------------------------------------   ------------------------------------------.
 * |      | Reset|      |      |      |      |   |      |Qwerty|Colemk|Dvorak|WTLEFT|WTRGHT|
 * |------+------+------+------+------+-------   -------+------+------+------+------+------|
 * |      |      |Aud on|Audoff|AGnorm|AGswap|   |WLEFT |WDOWN | WUP  |WRGHT |WBLEFT|WBRGHT|
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |   |      |RGBsUP|RGBsDN|RGBvUP|RGBvDN|WFULL |
 * |------+------+------+------+------+------+   +------+------+------+------+------+------|
 * |      |      |      |      |      |      |   |      |      |RGBwav|RGBfla|RGBtog|      |
 * `------------------------------------------   ------------------------------------------'
 */
[_ADJUST] =  LAYOUT_ortho_4x12(
  _______, RESET,   _______, _______, _______, _______, _______,   QWERTY,    COLEMAK,   DVORAK,    LCA(KC_7), LCA(KC_8),
  _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, LCA(KC_H), LCA(KC_J), LCA(KC_K), LCA(KC_L), LCA(KC_U), LCA(KC_I),
  _______, _______, _______, _______, _______, _______, _______,   RGB_SAI,   RGB_SAD,   RGB_VAI,   RGB_VAD,   LCA(KC_ENT),
  _______, _______, _______, _______, _______, _______, _______,   _______,   RGB_M_K,   RGB_M_B,   RGB_TOG,   _______
)


};

void keyboard_post_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
  rgblight_enable_noeeprom();
  layer_state_set_user(layer_state);
  #endif
}
void set_qwerty(void){
  rgblight_sethsv_noeeprom(255, 0, 160);
}
void set_lower(void){
  rgblight_sethsv_master(255, 255, 255);
  rgblight_sethsv_slave(255, 0, 160);
}
void set_raise(void){
  rgblight_sethsv_slave(35, 255, 255);
  rgblight_sethsv_master(255, 0, 160);
}
void set_adjust(void){
  rgblight_sethsv_slave(35, 255, 255);
  rgblight_sethsv_master(255, 255, 255);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          set_qwerty();
        #endif
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          set_lower();
        #endif
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          set_qwerty();
        #endif
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          set_raise();
        #endif
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          set_qwerty();
        #endif
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          set_adjust();
        #endif
        layer_on(_ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          set_qwerty();
        #endif
        layer_off(_ADJUST);
      }
      return false;
  }
  return true;
}

