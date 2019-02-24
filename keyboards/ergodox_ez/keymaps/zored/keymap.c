#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"

#define LCGS(code) LCTL(LGUI(LSFT(code)))
#define LCS(code) LCTL(LSFT(code))

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,      // can always be here
  EPRM,           
  RGB_SLD,        
  
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox(
    // left hand
    KC_ESC,         KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,          
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           _______,        
    LT(1,KC_CLCK),  KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           
    KC_LSPO,        CTL_T(KC_Z),    ALT_T(KC_X),    GUI_T(KC_C),    KC_V,           KC_B,           KC_MEH,         
    C_S_T(XXXXXXX), LCA_T(XXXXXXX), KC_DLR,         KC_LEFT,        KC_RGHT,        
                                                                                    _______,        _______,        
                                                                                                    KC_HOME,        
                                                                    KC_SPC,         KC_BSPC,        KC_END,         
        // right hand
        KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         KC_RBRC,        
        _______,        KC_Y,           KC_U,           KC_I,           KC_O,           LT(2,KC_P),     KC_LBRC,        
                        KC_H,           KC_J,           KC_K,           KC_L,           LT(2,KC_SCLN),  KC_QUOT,        
        KC_HYPR,        KC_N,           KC_M,           RGUI_T(KC_PCMM),RALT_T(KC_PDOT),RCTL_T(KC_SLSH),KC_RSPC,        
        KC_BSLS,        KC_GRV,         KC_DOWN,        KC_UP,          TG(3),          
        KC_ESC,         _______,        
        KC_PGUP,        
        KC_PGDN,        KC_DEL,         KC_ENT
    ),


  [1] = LAYOUT_ergodox(
    // left hand
    _______,        _______,        _______,        _______,        _______,        _______,        _______,        
    _______,        KC_EXLM,        KC_AT,          KC_LCBR,        KC_RCBR,        KC_BSLS,        _______,        
    _______,        KC_HASH,        KC_DLR,         KC_LPRN,        KC_RPRN,        KC_GRV,         
    _______,        KC_PERC,        KC_CIRC,        KC_LBRC,        KC_RBRC,        KC_TILD,        _______,        
    _______,        _______,        _______,        _______,        _______,        
                                                                                    _______,        _______,        
                                                                                                    _______,        
                                                                    _______,        KC_DEL,         _______,        
        // right hand
        _______,        _______,        _______,        _______,        _______,        _______,        _______,        
        _______,        KC_PPLS,        KC_7,           KC_8,           KC_9,           _______,        KC_PIPE,        
                        KC_EQL,         KC_4,           KC_5,           KC_6,           KC_PAST,        _______,        
        _______,        KC_MINS,        KC_1,           KC_2,           KC_3,           KC_AMPR,        _______,        
        KC_EQL,         KC_0,           KC_DOT,         _______,        _______,        
        _______,        _______,        
        _______,        
        _______,        _______,        _______
    ),


  [2] = LAYOUT_ergodox(
    // left hand
    _______,        _______,        _______,        _______,        _______,        _______,        _______,        
    _______,        _______,        KC_BTN2,        KC_MS_U,        KC_BTN1,        _______,        _______,        
    _______,        _______,        KC_MS_L,        KC_MS_D,        KC_MS_R,        _______,        
    _______,        _______,        _______,        _______,        _______,        _______,        _______,        
    _______,        _______,        _______,        KC_BTN1,        KC_BTN2,        
                                                                                    _______,        _______,        
                                                                                                    _______,        
                                                                    _______,        _______,        _______,        
        // right hand
        _______,        KC_PWR,         KC_SLEP,        _______,        _______,        _______,        _______,        
        _______,        _______,        KC_ACL0,        KC_ACL1,        KC_ACL2,        _______,        _______,        
                        KC_LEFT,        KC_DOWN,        KC_UP,          KC_RGHT,        _______,        _______,        
        _______,        KC_WH_L,        KC_WH_D,        KC_WH_U,        KC_WH_R,        _______,        _______,        
        KC_VOLU,        KC_VOLD,        KC_MUTE,        _______,        _______,        
        _______,        _______,        
        _______,        
        _______,        _______,        _______
    ),


  [3] = LAYOUT_ergodox(
    // left hand
    _______,        _______,        _______,        _______,        _______,        _______,        _______,        
    _______,        _______,        _______,        _______,        _______,        _______,        _______,        
    _______,        KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           
    _______,        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           _______,        
    _______,        _______,        _______,        _______,        _______,        
                                                                                    _______,        _______,        
                                                                                                    _______,        
                                                                    KC_C,           KC_V,           _______,        
        // right hand
        _______,        _______,        _______,        _______,        _______,        _______,        _______,        
        _______,        _______,        _______,        _______,        _______,        _______,        _______,        
                        KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_LBRC,        
        _______,        KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOT,        
        _______,        _______,        _______,        _______,        _______,        
        _______,        _______,        
        _______,        
        _______,        KC_N,           KC_M
    ),


};

bool suspended = false;
const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 1:
        ergodox_right_led_1_on();
        break;
      case 2:
        ergodox_right_led_2_on();
        break;
      case 3:
        ergodox_right_led_3_on();
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      default:
        break;
    }
    return state;

};
