#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

#ifdef OLED_ENABLE
static uint32_t        oled_timer = 0;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _BASE,
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
  [_BASE] = LAYOUT(
      //,-----------------------------------|
           KC_ESC,   KC_F2,  JP_EQL,  KC_DEL,
      //|--------+--------+--------+--------|
          KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
      //|--------+--------+--------+--------+--------|
            KC_P7,   KC_P8,   KC_P9,    LCTL(JP_LBRC),
      //|--------+--------+--------+--------+--------|
            KC_P4,   KC_P5,   KC_P6, KC_PPLS,  JP_EQL,
      //|--------+--------+--------+--------+--------|
            KC_P1,   KC_P2,   KC_P3,           KC_DEL,
      //|--------+--------+--------+--------+--------|
LT(_ARROW, KC_P0),LT(_MACRO, KC_PDOT),KC_PENT,KC_BSPC
      //`--------------------------------------------'
  ),

  [_ARROW] = LAYOUT(
      //,-----------------------------------|
          _______, _______, _______, _______,
      //|--------+--------+--------+--------|
          XXXXXXX, _______, _______, _______,
      //|--------+--------+--------+--------+--------|
          XXXXXXX,   KC_UP, XXXXXXX,          _______,
      //|--------+--------+--------+--------+--------|
          KC_LEFT, KC_DOWN,KC_RIGHT, _______, _______,
      //|--------+--------+--------+--------+--------|
          XXXXXXX, KC_DOWN, XXXXXXX,          _______,
      //|--------+--------+--------+--------+--------|
       MO(_ARROW),       MO(_MACRO), _______, _______
      //`--------------------------------------------'
  ),

  [_MACRO] = LAYOUT(
      //,-----------------------------------|
          _______, _______, _______, _______,
      //|--------+--------+--------+--------|
         SEND_MIN,SEND_MAX,SEND_CIF,SEND_AVE,
      //|--------+--------+--------+--------+--------|
            KC_F7,   KC_F8,   KC_F9,          _______,
      //|--------+--------+--------+--------+--------|
            KC_F4,   KC_F5,   KC_F6,SEND_SUM, _______,
      //|--------+--------+--------+--------+--------|
           KC_F11,  KC_F12,   KC_F3,          _______,
      //|--------+--------+--------+--------+--------|
          _______,          _______, JP_RPRN, _______
      //`--------------------------------------------'
  ),

  [_ADJUST] = LAYOUT( /* Base */
      //,-----------------------------------|
          _______, _______, _______, _______,
      //|--------+--------+--------+--------|
          XXXXXXX, XXXXXXX, XXXXXXX, _______,
      //|--------+--------+--------+--------+--------|
          RGB_SAD, RGB_SAI, XXXXXXX,          _______,
      //|--------+--------+--------+--------+--------|
          RGB_HUD, RGB_HUI, XXXXXXX, RGB_TOG, _______,
      //|--------+--------+--------+--------+--------|
          RGB_VAD, RGB_VAI, XXXXXXX,          _______,
      //|--------+--------+--------+--------+--------|
          _______,          _______, RGB_MOD, _______
      //`--------------------------------------------'
  )
};

//A description for expressing the layer position in LED mode.
layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _ARROW, _MACRO, _ADJUST);
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case _ARROW:
      rgblight_sethsv_at(HSV_BLUE, 0);
      break;
    case _MACRO:
      rgblight_sethsv_at(HSV_RED, 0);
      break;
    case _ADJUST:
      rgblight_sethsv_at(HSV_PURPLE, 0);
      break;
    default: //  for any other layers, or the default layer
      rgblight_sethsv_range( 0, 0, 0, 0, 1);
      break;
    }
    rgblight_set_effect_range( 1, 8);
#endif
return state;
}

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool result = false;
  if (record->event.pressed) {
     #ifdef OLED_ENABLE
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
    default:
      result = true;
      break;
  }

  return result;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_layer_state(void) {
    oled_write_P(PSTR("     "), false);
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("Arrow"), layer_state_is(_ARROW));
    oled_write_P(PSTR("Macro"), layer_state_is(_MACRO));
    oled_write_P(PSTR("Adjus"), layer_state_is(_ADJUST));
    oled_write_P(PSTR("     "), false);
}

void render_keylock_status(led_t led_state) {
    oled_write_P(PSTR("NumL "), led_state.num_lock);
}

void render_layer_messages(void) {
    oled_write_P(PSTR("GETtA 25       For  Your Good Job. "), false);
}

void render_status(void) {
    /* Show Keyboard Layout  */
    render_layer_state();
    render_keylock_status(host_keyboard_led_state());
}

bool oled_task_user(void) {
    static const char PROGMEM font_logo[] = {
        0x80,0x81,0x82,0x83,0x84,
        0xa0,0xa1,0xa2,0xa3,0xa4,
        0xc0,0xc1,0xc2,0xc3,0xc4,

        0x85,0x86,0x87,0x88,0x89,
        0xa5,0xa6,0xa7,0xa8,0xa9,
        0xc5,0xc6,0xc7,0xc8,0xc9,

        0x8a,0x8b,0x8c,0x8d,0x8e,
        0xaa,0xab,0xac,0xad,0xae,
        0xca,0xcb,0xcc,0xcd,0xce,0
        };
    oled_write_P(font_logo, false);

    render_status();  // Renders the current keyboard state (layer, lock)
    return false;
}

#endif
