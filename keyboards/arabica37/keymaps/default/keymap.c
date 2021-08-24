#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
  RGBRST
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
 //,-----------------------------------------------.          ,-----------------------------------------------.
     KC_ESC,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,              KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,KC_BSPC,\
 //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
    KC_LCTL,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,              KC_H,   KC_J,   KC_K,   KC_L,KC_SCLN,KC_QUOT,\
 //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     ADJUST,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,              KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,KC_BSLS,\
 //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
    KC_LSFT,                          LOWER,KC_LGUI,           KC_LALT,  RAISE,                        KC_RSFT,\
 //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
                                     KC_SPC,                            KC_ENT
 //`-----------------------------------------------'          `-----------------------------------------------'
 ),
 [_LOWER] = LAYOUT( \
 //,-----------------------------------------------.          ,-----------------------------------------------.
    KC_TRNS,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,              KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_TRNS,\
 //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
    KC_TRNS,KC_HOME,KC_LEFT,  KC_UP,KC_RGHT,KC_PGUP,             KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,\
 //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
    KC_TRNS, KC_END,KC_PSCR,KC_DOWN, KC_INS,KC_PGDN,             KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,\
 //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
    KC_TRNS,                        KC_TRNS,KC_TRNS,           KC_TRNS,KC_TRNS,                        KC_TRNS,\
 //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
                                    KC_TRNS,                           KC_TRNS
 //`-----------------------------------------------'          `-----------------------------------------------'
 ),
 [_RAISE] = LAYOUT( \
 //,-----------------------------------------------.          ,-----------------------------------------------.
    KC_TRNS,KC_EXLM,  KC_AT,KC_HASH, KC_DLR,KC_PERC,           KC_CIRC,KC_PSLS,KC_PAST,KC_PMNS,KC_PPLS,KC_TRNS,\
 //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
    KC_TRNS,KC_RBRC,KC_LABK,KC_ASTR,KC_SCLN,KC_LBRC,              KC_1,   KC_2,   KC_3,   KC_4,   KC_5, KC_EQL,\
 //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
    KC_TRNS,KC_BSLS,KC_RABK,KC_LPRN,KC_JYEN,KC_UNDS,              KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_PENT,\
 //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+--- ---+-------+-------|
    KC_TRNS,                        KC_TRNS,KC_TRNS,           KC_TRNS,KC_TRNS,                        KC_TRNS,\
 //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+--- ---+-------+-------|
                                    KC_TRNS,                           KC_TRNS
 //`-----------------------------------------------'          `-----------------------------------------------'
 ),
 [_ADJUST] = LAYOUT( \
 //,-----------------------------------------------.          ,-----------------------------------------------.
    KC_TRNS, RGBRST,RGB_TOG,  KC_NO,  KC_NO,  KC_NO,             KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,\
 //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
    KC_TRNS,RGB_HUI,RGB_SAI,RGB_VAI,AG_SWAP,  KC_NO,             KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,\
 //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
    KC_TRNS,RGB_HUD,RGB_SAD,RGB_VAD,AG_NORM,  KC_NO,             KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,\
 //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
    KC_TRNS,                        KC_TRNS,KC_TRNS,           KC_TRNS,KC_TRNS,                        KC_TRNS,\
 //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
                                    KC_TRNS,                           KC_TRNS
 //`-----------------------------------------------'          `-----------------------------------------------'
 )
};

int RGB_current_mode;

void keyboard_post_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_get_mode();
    #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    // set_timelog();
  }

  switch (keycode) {
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
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_get_mode();
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_get_mode();
        }
      #endif
      break;
  }
  return true;
}

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }

    return rotation;
}

void oled_task_user(void) {
  void render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("LOWER\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RAISE\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("ADJUST\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
  }


  void render_logo(void) {
      static const char PROGMEM qmk_logo[] = {
          0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
          0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
          0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
      };

      oled_write_P(qmk_logo, false);
  }

    if (is_keyboard_master()) {
        render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_logo();  // Renders a static logo
    }
}
#endif
