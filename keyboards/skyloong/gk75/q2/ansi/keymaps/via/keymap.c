//  Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later


#include QMK_KEYBOARD_H
enum layer_names {
    _WIN,
    _MAC,
    _WIN_INDEX,
    _MAC_INDEX
};

int FN_ON = 0;
bool WIN_LOCK = 0;
bool FN_WIN = 0;
bool FN_MAC = 0;
bool L_WIN = 0;
bool L_MAC = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_WIN] =  LAYOUT_all(
         KC_ESC,              KC_F1,    KC_F2,    KC_F3,    KC_F4,       KC_F5,     KC_F6,     KC_F7,    KC_F8,           KC_F9,      KC_F10,   KC_F11,   KC_F12,    KC_MUTE,
         KC_GRV,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,        KC_6,     KC_7,       KC_8,     KC_9,            KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,   KC_HOME,
         KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,        KC_Y,     KC_U,       KC_I,     KC_O,            KC_P,     KC_LBRC,  KC_RBRC,   KC_BSLS,    KC_DEL,
        KC_CAPS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,        KC_H,     KC_J,       KC_K,     KC_L,         KC_SCLN,     KC_QUOT,              KC_ENT,   KC_PGUP,
        KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,        KC_N,     KC_M,    KC_COMM,   KC_DOT,         KC_SLSH,     KC_RSFT,               KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,             KC_SPC,   KC_SPC,      KC_SPC,                        KC_RALT,  MO(_WIN_INDEX),     KC_RCTL,  KC_LEFT,   KC_DOWN,   KC_RGHT
    ),

     [_MAC] =  LAYOUT_all(
        _______,             KC_F14,   KC_F15, C(KC_UP),  KC_WSCH,   G(KC_SPC), LSG(KC_4),   KC_MPRV,  KC_MPLY,          KC_MNXT,      KC_MUTE,  KC_VOLD,  KC_VOLU,    KC_MUTE,
         KC_GRV,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,        KC_6,      KC_7,       KC_8,     KC_9,            KC_0,      KC_MINS,   KC_EQL,   KC_BSPC,   KC_HOME,
         KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,        KC_Y,      KC_U,       KC_I,     KC_O,            KC_P,      KC_LBRC,  KC_RBRC,   KC_BSLS,    KC_DEL,
        KC_CAPS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,        KC_H,      KC_J,       KC_K,     KC_L,         KC_SCLN,      KC_QUOT,              KC_ENT,   KC_PGUP,
        KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,        KC_N,      KC_M,    KC_COMM,   KC_DOT,         KC_SLSH,      KC_RSFT,               KC_UP,
        KC_LCTL,  KC_LALT,  KC_LGUI,             KC_SPC,   KC_SPC,      KC_SPC,                         KC_RGUI,  MO(_MAC_INDEX),      KC_RALT,  KC_LEFT,   KC_DOWN,   KC_RGHT
    ),

    [_WIN_INDEX] =  LAYOUT_all(
        _______,             KC_F14,   KC_F15, G(KC_TAB),  KC_WSCH, G(C(KC_S)), LSG(KC_S),   KC_MPRV,  KC_MPLY,    KC_MNXT,      KC_MUTE,  KC_VOLD,  KC_VOLU,   RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,    DF(_WIN),  DF(_MAC),   _______,  _______,    RGB_TOG,     RGB_RMOD,  RGB_MOD,   KC_DEL,    KC_END,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,  _______,  _______,    KC_INS,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,            _______,   KC_PGDN,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,            RGB_VAI,
        _______,  _______,  _______,            _______,  _______,     _______,                        _______,    _______,      _______,  RGB_SPD,  RGB_VAD,   RGB_SPI
    ),

    [_MAC_INDEX] = LAYOUT_all(
        _______,              KC_F1,    KC_F2,    KC_F3,    KC_F4,       KC_F5,     KC_F6,     KC_F7,    KC_F8,      KC_F9,       KC_F10,   KC_F11,   KC_F12,   RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,    DF(_WIN),  DF(_MAC),   _______,  _______,    RGB_TOG,     RGB_RMOD,  RGB_MOD,   KC_DEL,    KC_END,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,  _______,  _______,    KC_INS,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,            _______,   KC_PGDN,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,            RGB_VAI,
        _______,  _______,  _______,            _______,  _______,     _______,                        _______,    _______,      _______,  RGB_SPD,  RGB_VAD,   RGB_SPI
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_WIN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(C(KC_WH_D), C(KC_WH_U)), ENCODER_CCW_CW(G(C(KC_LEFT)),G(C(KC_RGHT))) },
    [_MAC] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_F14, KC_F15), ENCODER_CCW_CW(G(KC_MINS), G(KC_EQL)), ENCODER_CCW_CW(C(KC_UP), C(KC_DOWN)) },
    [_WIN_INDEX] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(RGB_HUD, RGB_HUI), ENCODER_CCW_CW(RGB_SPD, RGB_SPI), ENCODER_CCW_CW(RGB_SAD, RGB_SAI) },
    [_MAC_INDEX] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(RGB_HUD, RGB_HUI), ENCODER_CCW_CW(RGB_SPD, RGB_SPI), ENCODER_CCW_CW(RGB_SAD, RGB_SAI) }
};
#endif

#if defined(RGB_MATRIX_ENABLE)  /*&& defined(CAPS_LOCK_INDEX)*/
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_INDEX, 255, 255, 255);
    } else {
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_INDEX, 0, 0, 0);
        }
    }

    if (WIN_LOCK) {
        if(IS_LAYER_ON(1)){
           RGB_MATRIX_INDICATOR_SET_COLOR(WIN_LOCK_INDEX+1, 255, 255, 255);
        }else{
        RGB_MATRIX_INDICATOR_SET_COLOR(WIN_LOCK_INDEX, 255, 255, 255);
        }
    } else {
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(WIN_LOCK_INDEX, 0, 0, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(WIN_LOCK_INDEX+1, 0, 0, 0);
        }
    }

   switch (get_highest_layer(layer_state)) {
      case 2:{
        RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 255, 255, 255);
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 0, 0, 0);
         }
      } break;
      case 3:{
        RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 255, 255, 255);
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 0, 0, 0);
         }
      } break;

      case 0:{
       if (L_WIN) {
            RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 255, 255, 255);
            if (!rgb_matrix_get_flags()) {
               RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 0, 0, 0);
            }
            }else{
                if (!rgb_matrix_get_flags()) {
                   RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 0, 0, 0);
                 }
              }
         } break;

     case 1:{
       if (L_MAC) {
            RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 255, 255, 255);
            if (!rgb_matrix_get_flags()) {
               RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 0, 0, 0);
            }
            }else{
                if (!rgb_matrix_get_flags()) {
                   RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 0, 0, 0);
                 }
              }
         } break;

      default:{
         if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 0, 0, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 0, 0, 0);
         }
      }
    }
    return false;
}
#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#    ifdef RGB_MATRIX_ENABLE
       case RGB_TOG:
           if (record->event.pressed) {
               switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                    } break;
            }
        }
        return false;

       case RGB_VAI:
       rgb_matrix_set_flags(LED_FLAG_ALL);
       return true;
#   endif
     case MO(1):
      if (record->event.pressed) {
       FN_ON = 1;
      } else {
       FN_ON = 0;
      }
      return true;

     case MO(2):
      if (record->event.pressed) {
       FN_WIN = 1;
      } else {
       FN_WIN = 0;
      }
      return true;

     case MO(3):
      if (record->event.pressed) {
       FN_MAC = 1;
      } else {
       FN_MAC = 0;
      }
      return true;

     case KC_LGUI:
      if (FN_WIN | FN_MAC | FN_ON){
          if ( record->event.pressed){
             WIN_LOCK = !WIN_LOCK ; //change win lock state
            }
          if (!WIN_LOCK) {
             return false; //windows key locked do nothing
            }
        }
      if (WIN_LOCK) {
             return false; //windows key locked do nothing
            }
      return true;  // continue all further processing of this key

     case DF(0):
      if (record->event.pressed) {
       L_WIN = 1;
       L_MAC = 0;
       layer_move(0);
       set_single_persistent_default_layer(0); // Save default layer 0 to eeprom
      } else {
       L_WIN = 0;
      }
      return false; // cancel all further processing of this key

     case DF(1):
      if (record->event.pressed) {
       L_MAC = 1;
       L_WIN = 0;
       layer_move(1);
       set_single_persistent_default_layer(1);  //Save default layer 1 to eeprom
      } else {
       L_MAC = 0;
      }
      return false; // cancel  all further processing of this key

      default:
       L_MAC = 0;
       L_WIN = 0;
      return true;
    }
}
