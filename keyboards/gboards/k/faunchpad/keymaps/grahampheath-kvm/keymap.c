#include QMK_KEYBOARD_H

enum custom_keycodes {
    PREV = SAFE_RANGE,
    NEXT,
    PORTONE,
    PORTTWO,
    PORTTHREE,
    PORTFOUR,
    BUZZ,
    //SPEED,
    AUTO,
    FASTR,
    SLOWR,
    PASS,
};

int msecs = 600;
int TAP_CODE_DELAY = 600;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case PORTONE:
          if (record->event.pressed) {
              // when keycode QMKBEST is pressed
              // SEND_STRING(SS_TAP() SS_DELAY(600) SS_TAP(X_SCROLLLOCK) SS_DELAY(600) SS_TAP());
              tap_code(KC_SCROLLLOCK);
              tap_code(KC_SCROLLLOCK);
              tap_code(KC_1);
          } else {
              // when keycode QMKBEST is released
          }
          break;

      case PORTTWO:
        if (record->event.pressed) {
          // when keycode QMKBEST is pressed
          // SEND_STRING(SS_TAP(X_SCROLLLOCK) SS_DELAY(600) SS_TAP(X_SCROLLLOCK) SS_DELAY(600) SS_TAP(X_2));
          tap_code(KC_SCROLLLOCK);
          tap_code(KC_SCROLLLOCK);
          tap_code(KC_2);
          
        } else {
          // when keycode QMKBEST is released
        }
        break;
      
      case PORTTHREE:
        if (record->event.pressed) {
          // when keycode QMKBEST is pressed
          // SEND_STRING(SS_TAP(X_SCROLLLOCK) SS_DELAY(600) SS_TAP(X_SCROLLLOCK) SS_DELAY(600) SS_TAP(X_3));
          tap_code(KC_SCROLLLOCK);
          tap_code(KC_SCROLLLOCK);
          tap_code(KC_3);
          
        } else {
          // when keycode QMKBEST is released
        }
        break;
                  
      case PORTFOUR:
        if (record->event.pressed) {
          // when keycode QMKBEST is pressed
          // SEND_STRING(SS_TAP(X_SCROLLLOCK) SS_DELAY(600) SS_TAP(X_SCROLLLOCK) SS_DELAY(600) SS_TAP(X_4));
          
        } else {
          // when keycode QMKBEST is released
          tap_code(KC_SCROLLLOCK);
          tap_code(KC_SCROLLLOCK);
          tap_code(KC_4);
          
        }
        break;              
            
      case NEXT:
        if (record->event.pressed) {
          // when keycode QMKBEST is pressed
          // SEND_STRING(SS_TAP(X_SCROLLLOCK) SS_DELAY(600) SS_TAP(X_SCROLLLOCK) SS_DELAY(600) SS_TAP(X_PGDOWN));
          tap_code(KC_SCROLLLOCK);
          tap_code(KC_SCROLLLOCK);
          tap_code(KC_PGDOWN);
          
        } else {
          // when keycode QMKBEST is released
        }
        break;
        
      case PREV:
        if (record->event.pressed) {
          // when keycode QMKBEST is pressed
          // SEND_STRING(SS_TAP(X_SCROLLLOCK) SS_DELAY(600) SS_TAP(X_SCROLLLOCK) SS_DELAY(600) SS_TAP(X_PGUP));
          tap_code(KC_SCROLLLOCK);
          tap_code(KC_SCROLLLOCK);
          tap_code(KC_PGUP);
          
        } else {
          // when keycode QMKBEST is released
        }
        break;

      }
    return true;
};


/*    
 *  .---------------------------.
 *  |      |      |      |      | 
 *  |---------------------------|
 *  |PORTONE |PORTTWO |PORTTHREE |PORTFOUR | 
 *  '---------------------------'
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_faunch( PREV,     NEXT,     KC_2,       KC_SCROLLLOCK,
                       PORTONE,  PORTTWO,  PORTTHREE,  PORTFOUR)
};

// Don't fuck with this, thanks.
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);

/*
  SL = Scroll Lock, KC_SLCK

  SL, SL, Page Up = Previous port
  SL, SL, Page Down = Next port
  SL, SL, [1-4] = Select port by number
  SL, SL, F11 = Toggle Buzzer 
  SL, SL, F12 = Switching Speed (mouse gesture mode)
  SL, SL, Space = Enable auto switching
  SL, SL, [+ or -] = Increase/decrease switching interval
  ESC = Exit switching mode
  SL, SL, F2 = Toggle keyboard and mouse passthrough mode

  Manual: https://m.media-amazon.com/images/I/B1eWHCNCqIS.pdf

*/