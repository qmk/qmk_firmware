#include QMK_KEYBOARD_H

#define _BASE     0
#define _VIA1     1
#define _VIA2     2
#define _VIA3     3

#define KC_DISC_MUTE KC_F23
#define KC_DISC_DEAF KC_F24
#define NUM_CUST_KEYCODES (_NUM_CUST_KCS - SAFE_RANGE)
#define VIA_KEYCODE_RANGE 0x5F80

enum custom_keycodes {
  PROG = SAFE_RANGE,
  DISC_MUTE,
  DISC_DEAF,
  SUPER_ALT_TAB,
  _NUM_CUST_KCS,
};

// Macro variables
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
bool muted = false;
bool deafened = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_all(
    KC_NUBS,   KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
    KC_F13,    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
    KC_F14,    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
    KC_F15,    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
    KC_F16,    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                  MO(_VIA1), KC_RALT, KC_RCTL, KC_LEFT,          KC_DOWN, KC_RGHT
  ),

  [_VIA1] = LAYOUT_all(
    _______,  RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_HOME,  KC_INS,
    RGB_TOG,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______,  _______, _______, _______,                   _______,                   _______, _______, _______, KC_MPRV,          KC_MPLY, KC_MNXT
  ),

  [_VIA2] = LAYOUT_all(
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______,  _______, _______, _______,                   _______,                   _______, _______, _______, _______,          _______, _______
  ),

  [_VIA3] = LAYOUT_all(
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______,  _______, _______, _______,                   _______,                   _______, _______, _______, _______,          _______, _______
  ),

};

void map_via_keycode(uint16_t * keycode) {
  if (abs(*keycode - VIA_KEYCODE_RANGE) < NUM_CUST_KEYCODES) { //make into macro?
    dprintf("VIA custom keycode found, mapping to QMK keycode.\n");
    uint16_t new_keycode = (*keycode - VIA_KEYCODE_RANGE) + SAFE_RANGE;
    dprintf("VIA KC: %u QMK KC: %u\n", *keycode, new_keycode);
    *keycode = new_keycode;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef VIA_ENABLE
    map_via_keycode(&keycode);
  #endif
  process_record_remote_kb(keycode, record);
  switch(keycode) {
    case PROG:
      if (record->event.pressed) {
        rgblight_disable_noeeprom();
        bootloader_jump();
      }
    break;

    case DISC_MUTE:
      if (record->event.pressed) {
        tap_code(KC_DISC_MUTE);
        if (!rgblight_is_enabled()) break;
        
        if (muted) {
          rgblight_enable_noeeprom();
        } else {
          rgblight_timer_disable();
          uint8_t val = rgblight_get_val();
          rgblight_sethsv_range(255, 255, val, 0, 1);
        }
        muted = !muted;
      }
    break;

    case DISC_DEAF:
      if (record->event.pressed) {
        tap_code(KC_DISC_DEAF);
        if (!rgblight_is_enabled()) break;

        if (deafened) {
          rgblight_enable_noeeprom();
        } else {
          rgblight_timer_disable();
          uint8_t val = rgblight_get_val();
          rgblight_sethsv_range(255, 255, val, 0, RGBLED_NUM-1);
        }
        deafened = !deafened;
      }
    break;

    case SUPER_ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        } 
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;

    default:
    break;    
  }
return true;
}

void matrix_init_user(void) {
  matrix_init_remote_kb();
}

void matrix_scan_user(void) {
  matrix_scan_remote_kb();

  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}