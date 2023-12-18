#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _PLOVER 0
#define _QWERTY 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4

enum custom_keycodes 
{
  PLOVER = SAFE_RANGE,
  QWERTY, 
  LOWER,
  RAISE,
  ADJUST,
  EXT_QWE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = 
{

  [_PLOVER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      STN_PWR,  STN_S1, STN_TL,  STN_PL,  STN_HL, STN_ST1,                            STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      STN_FN,  STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,                           STN_ST4,  STN_RR,  STN_BR, STN_GR,  STN_SR,  STN_ZR,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     STN_N1,    STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,                             STN_N7, STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC,
  //├────────┼────────┼────────┼────────┼────────┼────────┼                          ┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX,  STN_RE1,  STN_RE2, XXXXXXX, STN_A,   STN_O,                              STN_E,  STN_U, XXXXXXX, XXXXXXX, QWERTY, XXXXXXX
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴                          ┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
 
  ),

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_RSFT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LGUI, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼                          ┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LALT, KC_MINUS, KC_TAB, KC_LCTL, LOWER,    KC_SPC,                            KC_ENT,  RAISE,   KC_RCTL, KC_RGUI,  EXT_QWE, KC_RALT
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴                          ┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                                  
  ),

  [_LOWER] = LAYOUT( 
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              _______,  KC_7,   KC_8,    KC_9,   KC_PLUS, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_F7,    KC_F8,   KC_LEFT, KC_UP,  KC_RGHT,  KC_F9,                            KC_PSLS,   KC_4,   KC_5,    KC_6,   KC_MINUS, KC_MUTE,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  KC_F10,   KC_F11,  KC_DOWN, KC_F11, KC_F12,                            KC_PAST,  KC_1,   KC_2,    KC_3,   KC_EQL,   KC_VOLU,
  //├────────┼────────┼────────┼────────┼────────┼────────┼                          ┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  _______,  _______, _______, _______, _______,                           KC_0,   _______, KC_COMM, KC_DOT,  KC_ENT, KC_VOLD
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴                          ┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
  
  ),

  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRAVE,  KC_TILD, KC_UNDS, KC_EQL, KC_PIPE,  _______,                         KC_HOME, KC_DEL, _______, KC_INS, KC_PGUP, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSLS,KC_LCBR, KC_RCBR, KC_MINUS, KC_LBRC, KC_RBRC,                          KC_END, KC_LEFT, KC_UP, KC_RGHT, KC_PGDN, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_COLN,  KC_LT,   KC_GT,  KC_PLUS,  KC_LPRN, KC_RPRN,                            _______, _______, KC_DOWN, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼                          ┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴                          ┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
  
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______,  _______, KC_CAPS, KC_MENU, KC_APP, KC_PSCR,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  _______,_______, _______, _______, KC_PAUS,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______,  KC_SCRL,                           _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼                          ┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴                          ┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
   
  ),

  
};


void matrix_init_user(void) {
  steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case PLOVER:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_PLOVER);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case QWERTY:
      if (!record->event.pressed) {
        layer_on(_QWERTY);
      }
      return false;
      break;
    case EXT_QWE:
      if (record->event.pressed) {
        layer_off(_QWERTY);
      }
      return false;
      break;
  }
  return true;
}
