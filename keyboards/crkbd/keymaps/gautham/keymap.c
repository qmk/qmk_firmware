#include QMK_KEYBOARD_H

#include "keycodes.h"

#ifdef OLED_DRIVER_ENABLE
#   include "oled.c"
#endif

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#   include "rgb.c"
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
          TAB,       Q,       W,       E,       R,       T,                            Y,       U,       I,       O,       P,    BSLS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         SFEQ,    SFTA,       S,       D,       F,       G,                            H,       J,       K,       L, SFTSCLN,    SFQT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         LCTL,    CTLZ,       X,       C,       V,       B,                            N,       M,    COMM,     DOT, CTLSLSH,   ADGRV,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             LALT,    LWSP,    RSEQ,      RSENT,   LWBSP,    LGUI\
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
          ESC,       1,       2,       3,       4,       5,                            6,       7,       8,       9,       0, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,    ANGL,    ANGR,    LPRN,    RPRN,    PGUP,                         MINS,    LEFT,      UP,   RIGHT,    PLUS, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, ___X___, ___X___,    LBRC,    RBRC,  PGDOWN,                         UNDS,    HOME,    DOWN,     END, ___X___, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,   LWDEL, _______\
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
          ESC,    HASH,     DLR,    LCBR,    RCBR, ___X___,                      ___X___,    AMPR,    PIPE,    EXLM,    ASTR, ___X___,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,    EXLM,      AT,    LPRN,    RPRN, ___X___,                      ___X___,    UNDS,     EQL,    ANGL,    ANGR, ___X___,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,    PERC,    CIRC,    LBRC,    RBRC, ___X___,                      ___X___,    MINS,    PLUS, ___X___,    BSLS, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______\
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      ___X___,  CK_RST, CK_DOWN,   CK_UP, CK_TOGG, RGB_TOG,                       MU_TOG,     F12,      F7,      F8,      F9, ___X___,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      ___X___, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_MOD,                       MU_MOD,     F11,      F4,      F5,      F6,   RESET,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      ___X___, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,  RGBRST,                       AU_TOG,     F10,      F1,      F2,      F3, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,    VOLD,    VOLU\
                                      //`--------------------------'  `--------------------------'
  )
};

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
uint32_t layer_state_set_user(uint32_t state) {
  if (state == default_layer_state) {
    restore_rgb_config();
  } else {
    uint8_t layer = biton32(state);
    if (layer_state == default_layer_state) save_rgb_config();
    rgb_by_layer(layer);
  }
  return state;
}

#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
  #endif
  #ifdef OLED_DRIVER_ENABLE
  if (record->event.pressed) {
    oled_timer = timer_read32();
    add_keylog(keycode);
  }
  #endif

  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    case RGB_TOG ... RGB_MOD:
      if (record->event.pressed) {
        restore_rgb_config();
        process_rgb(keycode, record);
        save_rgb_config();
      }
      return false;
    case RGBRST:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          eeconfig_update_rgblight_default();
          rgblight_enable();
        #elif RGB_MATRIX_ENABLE
          eeconfig_update_rgb_matrix_default();
          rgb_matrix_enable();
        #endif
        save_rgb_config();
      }
      return false;
    #endif
  }
  return true;
}
