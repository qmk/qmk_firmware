/*
tap danc eis turned on in the rules now...
*/
#include "sweet16.h"
#include "action_layer.h"

#define _EMOJI 0
#define _TAPLAND 1
#define _LEDCNTL 2


#define TAPPING_TOGGLE 2

enum custom_keycodes {
    SHRUG,
    DISFACE,
    FU,
    TFLIP,
    TFLIP2,
    SAD_EYES,
    TPUT,
    HAPPYFACE,
    HEARTFACE,
    CLOUD,
    CHANFACE,
    CMDCLEAR
};
//Tap Dance Declarations
enum {
  TD_EXAMPLE1 = 0,
  TD_EXAMPLE2,
  TD_EXAMPLE3,
  TD_EXAMPLE4
};

void tap(uint16_t keycode){
    register_code(keycode);
    unregister_code(keycode);
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* EMOJI Pad
    * ,-------------------------------.
    * |TFLIP | TFlIP2|ANGRYFL|  TPUT  |
    * |------+-------+-------+--------|
    * | CLOUD|       |       | CLEAR  |
    * |------+-------+-------+--------|
    * |SHRUG |DISFACE| HRTFAC| HAPPYF |
    * |------+-------+-------+--------|
    * | ENTER|       |LEDCNTR| tapland| 
    * `-------------------------------'
    */
      //purple
    [_EMOJI]{
       {TFLIP,   TFLIP2,   KC_TRNS,      FU }, 
       {CLOUD,   KC_TRNS,  KC_TRNS,      CMDCLEAR}, 
       {SHRUG,   DISFACE,  HEARTFACE,    HAPPYFACE}, 
       {KC_ENT,  KC_TRNS,  MO(_LEDCNTL), MO(_TAPLAND)}
    },
 
    /* TapLand
    * ,-------------------------------.
    * | str1 | str2  |  str3 |   str4 |
    * |------+-------+-------+--------|
    * |      |       |       |        |
    * |------+-------+-------+--------|
    * |      |       |       |        |
    * |------+-------+-------+--------|
    * |      |       |       |        | 
    * `-------------------------------'
    */
    //blue
    [_TAPLAND]{
       {TD(TD_EXAMPLE1), TD(TD_EXAMPLE2),  TD(TD_EXAMPLE3), TD(TD_EXAMPLE4)}, 
       {KC_TRNS,         KC_TRNS,          KC_TRNS,         KC_TRNS}, 
       {KC_TRNS,         KC_TRNS,          KC_TRNS,         KC_TRNS}, 
       {KC_TRNS,         KC_TRNS,          KC_TRNS,         KC_TRNS}
    },
    /* LEDControl Pad
    * ,-------------------------------.
    * | snake|breathe|rainbow|gradient|
    * |------+-------+-------+--------|
    * | xmas |  Val+ | Sat+  |   HUE+ |
    * |------+-------+-------+--------|
    * |kngrdr|  Val- | Sat-  |   HUE- |
    * |------+-------+-------+--------|
    * | swirl|       | PLAIN | ON/OFF | 
    * `-------------------------------'
    */
    //blue
    [_LEDCNTL]{
        {RGB_M_SN, RGB_M_B,    RGB_M_R,     RGB_M_G}, 
        {RGB_M_X,  RGB_VAI,    RGB_SAI,     RGB_HUI}, 
        {RGB_M_K,  RGB_VAD,    RGB_SAD,     RGB_HUD}, 
        {RGB_M_SW, KC_TRNS,    RGB_M_P,     RGB_TOG}
     },
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case CLOUD:       // (っ◕‿◕)っ
                if(record->event.pressed){
                    process_unicode((0x28|QK_UNICODE), record);   // Head
                    process_unicode((0x3063|QK_UNICODE), record);   // Hand
                    process_unicode((0x25D5|QK_UNICODE), record);   // Eye
                    process_unicode((0x203F|QK_UNICODE), record);  // Mouth
                    process_unicode((0x25D5|QK_UNICODE), record);  // Eye
                    process_unicode((0x29|QK_UNICODE), record);   //Head
                    process_unicode((0x3063|QK_UNICODE), record); // Hand
                }
                return false;
                break;
            case FU:       // t(-_-t)
                if(record->event.pressed){
                    SEND_STRING("t(-_-t)");
                }
                return false;
                break;  
            case HAPPYFACE:       // ʘ‿ʘ 
                if(record->event.pressed){
                    process_unicode((0x298|QK_UNICODE), record);   // Eye
                    process_unicode((0x203F|QK_UNICODE), record);   // Mouth
                    process_unicode((0x298|QK_UNICODE), record);   // Eye
                }
                return false;
                break; 
            case CMDCLEAR:
                if (record->event.pressed) {
                    register_code(KC_LGUI);
                    tap(KC_A);                 
                    unregister_code(KC_LGUI);
                    tap(KC_DEL);                 
                }
                return false;
                break;  
            case SHRUG:
                if (record->event.pressed) {
                    set_unicode_input_mode(UC_WIN);
                    process_unicode((0x00AF|QK_UNICODE), record); // Hand
                    tap(KC_BSLS);                 // Arm
                    register_code(KC_LSFT);
                    tap(KC_UNDS);                 // Arm
                    tap(KC_LPRN);                 // Head
                    unregister_code(KC_LSFT);
                    process_unicode((0x30C4|QK_UNICODE), record); // Face
                    register_code(KC_LSFT);
                    tap(KC_RPRN);                 // Head
                    tap(KC_UNDS);                 // Arm
                    unregister_code(KC_LSFT);
                    tap(KC_SLSH);                 // Arm
                    process_unicode((0x00AF|QK_UNICODE), record); // Hand
                }
                return false; 
                break;
            case HEARTFACE:       // ♥‿♥
                if(record->event.pressed){
                    process_unicode((0x2665|QK_UNICODE), record);   // Eye
                    process_unicode((0x203F|QK_UNICODE), record);   // Mouth
                    process_unicode((0x2665|QK_UNICODE), record);   // Eye
                }
                return false;
                break;  
            case DISFACE:       // ಠ_ಠ
                if(record->event.pressed){
                    process_unicode((0x0CA0|QK_UNICODE), record);   // Eye
                    register_code(KC_RSFT);
                    tap(KC_MINS);
                    unregister_code(KC_RSFT);
                    process_unicode((0x0CA0|QK_UNICODE), record);   // Eye
                }
                return false;
                break;
            case TFLIP:         // (╯°□°)╯ ︵ ┻━┻
                if(record->event.pressed){
                    register_code(KC_RSFT);
                    tap(KC_9);
                    unregister_code(KC_RSFT);
                    process_unicode((0x256F|QK_UNICODE), record);   // Arm
                    process_unicode((0x00B0|QK_UNICODE), record);   // Eye
                    process_unicode((0x25A1|QK_UNICODE), record);   // Mouth
                    process_unicode((0x00B0|QK_UNICODE), record);   // Eye
                    register_code(KC_RSFT);
                    tap(KC_0);
                    unregister_code(KC_RSFT);
                    process_unicode((0x256F|QK_UNICODE), record);   // Arm
                    tap(KC_SPC);
                    process_unicode((0x0361|QK_UNICODE), record);   // Flippy
                    tap(KC_SPC);
                    process_unicode((0x253B|QK_UNICODE), record);   // Table
                    process_unicode((0x2501|QK_UNICODE), record);   // Table
                    process_unicode((0x253B|QK_UNICODE), record);   // Table
                }
                return false;
                break;
            case TFLIP2:         // ┻━┻︵ \(°□°)/ ︵ ┻━┻
                if(record->event.pressed){
                    process_unicode((0x253B|QK_UNICODE), record);   // Table
                    process_unicode((0x2501|QK_UNICODE), record);   // Table
                    process_unicode((0x253B|QK_UNICODE), record);   // Table
                    tap(KC_SPC);
                    process_unicode((0x0361|QK_UNICODE), record);   // Flippy
                    tap(KC_SPC);
                    tap(KC_BSLASH);
                    register_code(KC_RSFT);
                    tap(KC_9);
                    unregister_code(KC_RSFT);
                    process_unicode((0x00B0|QK_UNICODE), record);   // Eye
                    process_unicode((0x25A1|QK_UNICODE), record);   // Mouth
                    process_unicode((0x00B0|QK_UNICODE), record);   // Eye
                    register_code(KC_RSFT);
                    tap(KC_0);
                    unregister_code(KC_RSFT);
                    tap(KC_SLASH);
                    tap(KC_SPC);
                    process_unicode((0x0361|QK_UNICODE), record);   // Flippy
                    tap(KC_SPC);
                    process_unicode((0x253B|QK_UNICODE), record);   // Table
                    process_unicode((0x2501|QK_UNICODE), record);   // Table
                    process_unicode((0x253B|QK_UNICODE), record);   // Table
                }
                return false;
                break;
                } 
    }
    return true;
}


/* tap dance time */
void tdexample1(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    SEND_STRING(EXAMPLESTRING1);
    reset_tap_dance (state);
  }
}
void tdexample2(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    SEND_STRING(EXAMPLESTRING2);
    reset_tap_dance (state);
  }
}
void tdexample3(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    SEND_STRING(EXAMPLESTRING3);
    reset_tap_dance (state);
  }
}
void tdexample4(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    SEND_STRING(EXAMPLESTRING4);
    reset_tap_dance (state);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_EXAMPLE1] = ACTION_TAP_DANCE_FN(tdexample1),
    [TD_EXAMPLE2] = ACTION_TAP_DANCE_FN(tdexample2),
    [TD_EXAMPLE3] = ACTION_TAP_DANCE_FN(tdexample3),
    [TD_EXAMPLE4] = ACTION_TAP_DANCE_FN(tdexample4)
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
tap(RGB_M_P);
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

  uint8_t layer = biton32(layer_state);

  
  switch (layer) {
    case _TAPLAND:
      rgblight_setrgb(0, 16, 0); //green
      break;
    
    case _LEDCNTL:
      rgblight_setrgb(0, 0, 16); //blue
      break;
    
    case _EMOJI:
      rgblight_setrgb(16, 0, 16); //purple
      break;
    
    default:
      // none
      break;
  }

};