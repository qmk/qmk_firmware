#include QMK_KEYBOARD_H
#include "keycodes.h"

#ifdef OLED_DRIVER_ENABLE
#    include "oled.c"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif


extern uint8_t is_master;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     HOLD_SFT_CAPS,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                  KC_H,    KC_J,    KC_K,    KC_L,    KC_UP,  TD(TD_ACCENT),
  //---------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LCTL, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M, TD(TD_CTRENCADA), KC_LEFT,  KC_DOWN, KC_RGHT,
  //---------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_RGUI, LOWER, KC_SPC,        KC_ENT, RAISE, KC_RALT
                                      //|--------------------------|  |--------------------------|
  ),

  [_LOWER] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LSFT,LSFT(KC_5),RALT(KC_2),RALT(KC_3),LSFT(KC_4),LSFT(KC_1),            KC_HOME, KC_PGUP, XXXXXXX, XXXXXXX, LSFT(KC_RBRC), KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LCTL,KC_GRV,KC_TILD,LSFT(KC_6),RALT(KC_1),LSFT(KC_MINS),                KC_END , KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX, RALT(KC_NUBS),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_RGUI, KC_TRNS, KC_SPC,    KC_ENT, RAISE, KC_RALT
                                      //|--------------------------|  |--------------------------|
  ),

  [_RAISE] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_ESC, KC_EQL,LSFT(KC_EQL),LSFT(KC_3),RALT(KC_SCLN),RALT(KC_6),           KC_MINS,LSFT(KC_2),LSFT(KC_8),LSFT(KC_9),LSFT(KC_0),KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LSFT,XXXXXXX,XXXXXXX,KC_NUBS,LSFT(KC_QUOT),LSFT(KC_LBRC),               RALT(KC_LBRC),RALT(KC_RBRC),RALT(KC_QUOT),RALT(KC_NUHS),KC_RBRC,LSFT(KC_7),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LCTL, MACRO1, MACRO2, MACRO3, MACRO4, MACRO5,                           KC_COMM,KC_DOT,LSFT(KC_COMM),LSFT(KC_DOT),KC_SLSH,LSFT(KC_SLSH),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_RGUI, LOWER, KC_SPC,    KC_ENT, KC_TRNS, KC_RALT
                                      //|--------------------------|  |--------------------------|
  ),

  [_ADJUST] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,    KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_PWR, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_MOD,                       KC_MSTP, KC_VOLU, KC_MPLY, KC_MUTE, XXXXXXX, RGB_TOG, \
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_SLEP, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, RGBRST,                       KC_MPRV, KC_VOLD, KC_MNXT, XXXXXXX, XXXXXXX, KC_WAKE,  \
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_RGUI, KC_TRNS, KC_SPC,    KC_ENT, KC_TRNS, TO(_GAME)
                                      //|--------------------------|  |--------------------------|
  ),

  [_GAME] = LAYOUT(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    KC_UP,   KC_F3,
  //---------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LCTL, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M, KC_COMM, KC_LEFT,  KC_DOWN, KC_RGHT,
  //---------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, KC_SPC, KC_ENT,      KC_RGUI, KC_TAB, TO(_QWERTY)
                                      //|--------------------------|  |--------------------------|
  )
};


// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CTRENCADA] = ACTION_TAP_DANCE_DOUBLE(KC_NUHS, KC_SCLN),
    [TD_ACCENT] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_QUOT)
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

void rgb_matrix_indicators_user(void) {
  #ifdef RGB_MATRIX_ENABLE
  switch (biton32(layer_state)) {
    case _RAISE:
        rgb_matrix_set_color_all(RGB_YELLOW);
      break;

    case _LOWER:
        rgb_matrix_set_color_all(RGB_BLUE);
      break;

    case _ADJUST:
        rgb_matrix_set_color_all(RGB_GREEN);
      break;
    case _GAME:
        rgb_matrix_set_color_all(RGB_TEAL);
      break;
    default:
        if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
            rgb_matrix_set_color_all(RGB_MAGENTA);
        }
      break;
  }
  #endif
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}

#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
#endif
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
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case MACRO1:
        if (record->event.pressed) {
            SEND_STRING("sergi.massaneda" SS_RALT("2") "gmail.com");
        }
        return false;
    case MACRO2:
        if (record->event.pressed) {
            SEND_STRING("console.log" SS_LSFT("8") SS_LSFT("9"));
        }
        return false;
    case MACRO3:
        if (record->event.pressed) {
            SEND_STRING(SS_LSFT(".") "joy" SS_LSFT(".")); // 😂
        }
        return false;
    case MACRO4:
        if (record->event.pressed) {
            SEND_STRING(SS_LSFT(".") "thumbsup" SS_LSFT(".")); // 👍
        }
        return false;
    case MACRO5:
        if (record->event.pressed) {
            SEND_STRING(SS_LSFT(".") "man" SS_TAP(X_SLSH) "shrugging" SS_LSFT(".")); // 🤷‍♂️
        }
        return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      #ifdef RGB_MATRIX_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgb_matrix_default();
          rgb_matrix_enable();
        }
      #endif
      break;
  }
  return true;
}
