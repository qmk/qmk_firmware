#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif



#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

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
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------.                  ,-----------------------------------------------.
      KC_ESC,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                      KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,KC_BSPC,\
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
     KC_LCTL,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                      KC_H,   KC_J,   KC_K,   KC_L,KC_SCLN,KC_QUOT,\
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
      ADJUST,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                      KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,KC_BSLS,\
  //|-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------+-------|
     KC_LSFT,                         KC_SPC,  LOWER,KC_LGUI,   KC_LALT,  RAISE, KC_ENT,                        KC_RSFT \
  //`-------------------------------------------------------'  `-------------------------------------------------------'
  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------.                  ,-----------------------------------------------.
     KC_TRNS,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                      KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_TRNS,\
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
     KC_TRNS,KC_HOME,KC_LEFT,  KC_UP,KC_RGHT,KC_PGUP,                     KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,\
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
     KC_TRNS, KC_END,KC_PSCR,KC_DOWN, KC_INS,KC_PGDN,                     KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,\
  //|-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------+-------|
     KC_TRNS,                        KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,                        KC_TRNS \
  //`-------------------------------------------------------'  `-------------------------------------------------------'
  ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------.                  ,-----------------------------------------------.
     KC_TRNS,KC_EXLM,  KC_AT,KC_HASH, KC_DLR,KC_PERC,                   KC_CIRC,KC_PSLS,KC_PAST,KC_PMNS,KC_PPLS,KC_TRNS,\
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
     KC_TRNS,KC_RBRC,KC_LABK,KC_ASTR,KC_SCLN,KC_LBRC,                      KC_1,   KC_2,   KC_3,   KC_4,   KC_5, KC_EQL,\
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
     KC_TRNS,KC_BSLS,KC_RABK,KC_LPRN,KC_JYEN,KC_UNDS,                      KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_PENT,\
  //|-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+--- ---+-------+-------+-------|
     KC_TRNS,                        KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,                        KC_TRNS \
  //`-------------------------------------------------------'  `-------------------------------------------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------.                  ,-----------------------------------------------.
     KC_TRNS, RGBRST,RGB_TOG,  KC_NO,  KC_NO,  KC_NO,                     KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,\
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
     KC_TRNS,RGB_HUI,RGB_SAI,RGB_VAI,AG_SWAP,  KC_NO,                     KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,\
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
     KC_TRNS,RGB_HUD,RGB_SAD,RGB_VAD,AG_NORM,  KC_NO,                     KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,\
  //|-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------+-------|
     KC_TRNS,                        KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,                        KC_TRNS \
  //`-------------------------------------------------------'  `-------------------------------------------------------'
)
};

int RGB_current_mode;


// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
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
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
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
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
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
#endif
