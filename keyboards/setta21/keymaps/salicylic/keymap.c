#include QMK_KEYBOARD_H
#include "keymap_jp.h"


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#ifdef OLED_DRIVER_ENABLE
static uint32_t        oled_timer = 0;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _BASE = 0,
  _ARROW,
  _MACRO,
  _ADJUST,
};

enum custom_keycodes {
  RGB_RST = SAFE_RANGE,
  SEND_SUM,
  SEND_AVE,
  SEND_CIF,
  SEND_MAX,
  SEND_MIN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_numpad_6x4(
      //,-----------------------------------|
           KC_ESC,   KC_F2,  JP_EQL,  KC_DEL,
      //|--------+--------+--------+--------|
          KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
      //|--------+--------+--------+--------|
            KC_P7,   KC_P8,   KC_P9,         
      //|--------+--------+--------+--------|
            KC_P4,   KC_P5,   KC_P6, KC_PPLS,
      //|--------+--------+--------+--------|
            KC_P1,   KC_P2,   KC_P3,         
      //|--------+--------+--------+--------|
LT(_ARROW, KC_P0),LT(_MACRO, KC_PDOT),KC_PENT
      //`-----------------------------------'
  ),

  [_ARROW] = LAYOUT_numpad_6x4(
      //,-----------------------------------|
          _______, _______, _______, _______,
      //|--------+--------+--------+--------|
          XXXXXXX, _______, _______, _______,
      //|--------+--------+--------+--------|
          XXXXXXX,   KC_UP, XXXXXXX,         
      //|--------+--------+--------+--------|
          KC_LEFT, KC_DOWN,KC_RIGHT, _______,
      //|--------+--------+--------+--------|
          XXXXXXX, KC_DOWN, XXXXXXX,         
      //|--------+--------+--------+--------|
       MO(_ARROW),       MO(_MACRO), _______ 
      //`-----------------------------------'
  ),

  [_MACRO] = LAYOUT_numpad_6x4(
      //,-----------------------------------|
          _______, _______, _______, _______,
      //|--------+--------+--------+--------|
         SEND_MIN,SEND_MAX,SEND_CIF,SEND_AVE,
      //|--------+--------+--------+--------|
            KC_F7,   KC_F8,   KC_F9,         
      //|--------+--------+--------+--------|
            KC_F4,   KC_F5,   KC_F6,SEND_SUM,
      //|--------+--------+--------+--------|
           KC_F11,  KC_F12,   KC_F3,         
      //|--------+--------+--------+--------|
          _______,          _______, JP_RPRN 
      //`-----------------------------------'
  ),

  [_ADJUST] = LAYOUT_numpad_6x4( /* Base */
      //,-----------------------------------|
          _______, _______, _______, _______,
      //|--------+--------+--------+--------|
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      //|--------+--------+--------+--------|
          RGB_SAD, RGB_SAI, XXXXXXX,         
      //|--------+--------+--------+--------|
          RGB_HUD, RGB_HUI, XXXXXXX, RGB_TOG,
      //|--------+--------+--------+--------|
          RGB_VAD, RGB_VAI, XXXXXXX,         
      //|--------+--------+--------+--------|
          _______,          _______, RGB_MOD 
      //`-----------------------------------'
  )
};


//A description for expressing the layer position in LED mode.
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _ARROW, _MACRO, _ADJUST);
}

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool result = false;
  if (record->event.pressed) {
     #ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
     #endif
  }
  switch (keycode) {
    case SEND_SUM:
      if (record->event.pressed) {
        SEND_STRING("_SUM*");
      }
      break;
    case SEND_AVE:
      if (record->event.pressed) {
        SEND_STRING("_AVERAGE*");
      }
      break;
    case SEND_CIF:
      if (record->event.pressed) {
        SEND_STRING("_COUNTIF*");
      }
      break;
    case SEND_MAX:
      if (record->event.pressed) {
        SEND_STRING("_MAX*");
      }
      break;
    case SEND_MIN:
      if (record->event.pressed) {
        SEND_STRING("_MIN*");
      }
      break;
    #ifdef RGBLIGHT_ENABLE
      case RGB_MOD:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
      case RGB_RST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
    #endif
    default:
      result = true;
      break;
  }

  return result;
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_0; }


void render_layer_state(void) {
    oled_write_P(PSTR("LAYER: "), false);
    oled_write_P(PSTR(" Arrow "), layer_state_is(_ARROW));
    oled_write_P(PSTR(" Macro "), layer_state_is(_MACRO));
}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR("NumLock"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR("              "), false);
}

void render_layer_messages(void) {
    oled_write_P(PSTR("Setta21                For Your Good Job. "), false);
}


void render_status(void) {
    /* Show Keyboard Layout  */
    render_layer_messages();
    render_keylock_status(host_keyboard_leds());
    render_layer_state();
}

void oled_task_user(void) {
    render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
}

#endif
