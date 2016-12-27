#include "bluepad.h"
#include "issi.h"
#include "action_layer.h"

//Tap Dance Declarations
enum {
  TD_LAYER = 0,
  TD_RESET,
  TD_AST_BS
};

/*   ACTION_TAP_DANCE_DOUBLE(TG(1), TG(2)),  KC_PSLS, KC_PAST, KC_PMNS, \ */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP( /* Base */
  TD(TD_LAYER),  KC_PSLS, KC_PMNS, TD(TD_AST_BS), \
  KC_P7,  KC_P8,   KC_P9,   KC_PPLS, \
  KC_P4,  KC_P5,   KC_P6, \
  KC_P1,  KC_P2,   KC_P3,   KC_PENT, \
  KC_P0,  KC_PDOT),

[1] = KEYMAP( /* phone */
  TD(TD_LAYER),    M(0),      M(1),   M(2), \
  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_F13, \
  KC_TRNS,  KC_TRNS,   KC_TRNS, \
  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS, \
  KC_TRNS,  KC_HASH),

[2] = KEYMAP( /* Debug/Program */
  TG(2),  TG(2),   TG(2),   DEBUG, \
  TG(2),  TG(2),   TG(2),   TG(2), \
  TG(2),  TG(2),   TG(2), \
  TG(2),  TG(2),   TG(2),   TD(TD_RESET), \
  TG(2),  TG(2)),
};

const uint16_t PROGMEM fn_actions[] = {
};

void layer_tap (qk_tap_dance_state_t *state, void *user_data) {
  xprintf("layer_tap: %d\n", state->count);
  switch(state->count){
    case 1:
      layer_invert(1);
      break;
    case 2:
      layer_off(1);
      layer_on(2);
      break;
  }
}

void reset_keyboard_kb(){
  // Tell the ISSI to blink all LEDs to indicate programming mode
  writeRegister8(0x0B, 0x0A, 0x00);
  writeRegister8(0x0B, 0x05, 0b00101001);
  writeRegister8(0x0B, 0x0A, 0x01);
  xprintf("programming!\n");
  reset_keyboard();
}

void reset_tap (qk_tap_dance_state_t *state, void *user_data) {
  xprintf("reset_tap: %d\n", state->count);
  switch(state->count){
    case 1:
      clear_keyboard();
      layer_off(2);
      break;
    case 2:
      reset_keyboard_kb();
      break;
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_LAYER] = ACTION_TAP_DANCE_FN(layer_tap),
  [TD_RESET] = ACTION_TAP_DANCE_FN(reset_tap),
  [TD_AST_BS] = ACTION_TAP_DANCE_DOUBLE(KC_PAST, KC_BSPC),
// Other declarations would go here, separated by commas, if you have them
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            return MACRO( I(100), T(8), T(8), T(5), T(4), T(9), T(3), T(7), W(50), D(LSHIFT), T(3), U(LSHIFT), END);
          }
        case 1:
          if (record->event.pressed) {
            return MACRO( I(100), T(8), T(8), T(5), T(7), T(8), T(7), T(6), W(50), D(LSHIFT), T(3), U(LSHIFT), END);
          }
        case 2:
          if (record->event.pressed) {
            return MACRO( I(100), T(8), T(8), T(5), T(2), T(2), T(9), T(3), W(50), D(LSHIFT), T(3), U(LSHIFT), END);
          }
        break;
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
