 -0,0 +1,77 @@
#include QMK_KEYBOARD_H

enum {
    BASE = 0,
    PHOTOSHOP,
    NUMPAD,
    MAULI   
 };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
                 TO(PHOTOSHOP),   TO(NUMPAD),   TO(NA), TO(BASE),
                 KC_PPLS,   KC_up,   KC_PMNS, KC_F5,
        KC_MUTE, KC_LEFT,   KC_ESC,   KC_RGHT, KC_TAB,
        KC_ESC,  KC_DEL, KC_down, KC_BSPC, KC_ENT
    ),
    [PHOTOSHOP] = LAYOUT(
                 CUT,   PASTE,   COPY, TO(BASE),
                 UNDO,   REDO,   KC_RGHT, KC_TAB,
        KC_MUTE, KC_MPRV,   KC_MPLY,   KC_MNXT, KC_MUTE,
        KC_ESC,  KC_DEL, KC_NO, KC_NO, KC_ENT
    ),
    [NUMPAD] = LAYOUT(
                 KC_P7,   KC_P8,   KC_P9, TO(BASE),
                 KC_P4,   KC_P5,   KC_P6, KC_PMNS,
        KC_MUTE, KC_P1,   KC_P2,   KC_P3, KC_PPLS,
        KC_ESC,  KC_DEL, KC_P0, KC_PDOT, KC_PENT
    ),  
    [MAULI] = LAYOUT(
                 MAULI,   MAULI,   MAULI, TO(BASE),
                 MAULI,   MAULI,   MAULI, MAULI,
        MAULI, MAULI,   MAULI,   MAULI, MAULI,
        MAULI,  MAULI, MAULI, MAULI, MAULI
              //Currently no purpose, feel free to edit
    ) 
};

enum custom_keycodes {
    COPY = SAFE_RANGE, 
    CUT,               
    PASTE,            
    UNDO,              
    REDO,              
    MAULI    
      //just some macros, feel free to edit
/};

bool process_record_user(uint16_t keycode, keyrecord_t record) {
    switch (keycode) {
    case COPY:
        if (record->event.pressed) {
            // when keycode COPY is pressed
            register_code(KC_LCTL);
            register_code(C);
        } else {
          unregister_code(KC_LCTL)
          unregister_code(C)
            // when keycode COPY is released
        }
        break;
    case PASTE:
        if (record->event.pressed) {
            // when keycode PASTE is pressed
            register_code(KC_LCTL);
            register_code(V);
        } else {
            unregister_code(KC_LCTL)
            unregister_code(V)
            // when keycode PASTE is released
        }
        break;
    case CUT:
        if (record->event.pressed) {
            // when keycode CUT is pressed
            register_code(KC_LCTL);
            register_code(X);
        } else {
            unregister_code(KC_LCTL)
            unregister_code(X)
            // when keycode CUT is released
        }
        break;
    case MAULI:
        if (record->event.pressed) {
            // when keycode MAULI is pressed
            SEND_STRING("©MauliQT©");
            register_code(KC_PENT);
        } else {
            SEND_STRING("©MauliQT©");
            unregister_code(KC_PENT)
            // when keycode MAULI is released
        }
        break;
case UNDO:
        if (record->event.pressed) {
            // when keycode UNDO is pressed
            register_code(KC_LCTL);
            register_code(Z);
        } else {
            unregister_code(KC_LCTL)
            unregister_code(Z)
            // when keycode UNDO is released
        }
        break;
case REDO:
        if (record->event.pressed) {
            // when keycode REDO is pressed
            register_code(KC_LCTL);
            register_code(Y);
        } else {
            unregister_code(KC_LCTL)
            unregister_code(Y)
            // when keycode REDO is released
        }
        break;        
    }
    return true;
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { / First encoder below the controller /
    if (clockwise) {
      tap_code(KC_VOLD); /volume down/
    } else {
      tap_code(KC_VOLU); /volume up/
                 //Just plain audio controlle
    }
  } else if (index == 1) { / Second encoder /
    if (clockwise) {
      tap_code16(C(KC_PMNS); /ZOOM IN/               
    } else {
      tap_code16(C(KC_PPLS); /ZOOM OUT*/
                 //Photoshop zoom config
    }
  }
    return true;
}
                 
