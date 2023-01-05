#include QMK_KEYBOARD_H

uint16_t copy_paste_timer;

enum custom_keycodes {
  S_H = SAFE_RANGE, // slack here
  S_H_P,       // slack here + paste 
  T_H_B,         // ticket header bike
  T_H_T,       // ticket header tread 
  E_OP,  	    // email open
  E_CL,		    // email close 
  E_FU,		    // email follow up 
  E_SS,       // email service schedule
  SCRN_C,	    // screen clip 
  DC_C,       // double click + copy
  KC_CCCV,    // one key copy/paste 
  		
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case S_H:
      if (record->event.pressed) {
        SEND_STRING("@HERE");
      }
 break;

    case S_H_P:
      if (record->event.pressed) {
        SEND_STRING("@HERE" SS_TAP(X_SPC) SS_LCTL("v"));
      }
 break;

 case T_H_B:
      if (record->event.pressed) {
        SEND_STRING("Your Peloton Bike - ");
      }
 break;

 case T_H_T:
      if (record->event.pressed) {
        SEND_STRING("Your Peloton Tread - ");
      }
 break;

    case E_OP:
      if (record->event.pressed) {
        // when keycode E_OP is pressed
        SEND_STRING("Hi , "SS_TAP(X_ENTER)SS_TAP(X_ENTER)"Thank you for contacting Peloton."SS_TAP(X_ENTER)SS_TAP(X_ENTER));
      }
break;

    case E_CL:
      if (record->event.pressed) {
                SEND_STRING("Please let me know if you have any other questions."SS_TAP(X_ENTER)SS_TAP(X_ENTER)"Thank you for being the best part of Peloton."); 
      }
break;

    case E_FU:
      if (record->event.pressed) {
                SEND_STRING("I will be personally watching this issue and will reach out to you after this is complete to make sure everything went smoothly."SS_TAP(X_ENTER)SS_TAP(X_ENTER)); 
      }
break;

    case E_SS:
      if (record->event.pressed) {
                SEND_STRING("Please click here to schedule your service."SS_TAP(X_ENTER)SS_TAP(X_ENTER)); 
      }
break;

    case SCRN_C:
      if (record->event.pressed) {
                tap_code16(C(S(KC_F5))); 
      }
break;

   case DC_C:
      if (record->event.pressed) {
                tap_code(KC_BTN1);
                tap_code(KC_BTN1);
                tap_code16(C(KC_C)); 
      }
break;
    
    case KC_CCCV:  // One key copy/paste
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
                    tap_code16(C(KC_C));
                } else {  // Tap, paste
                    tap_code16(C(KC_V));
                }
            }
break;

  }
  return true;
};  

//Tap Dance Declarations
enum {
  TD_SPC_DOT = 0
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_SPC_DOT]  = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_PDOT) 
// Other declarations would go here, separated by commas, if you have them
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
QK_GESC, KC_1, 	KC_2, 	KC_3, 	KC_4, 	KC_5, 				KC_6, 	KC_7, 	KC_8, 	KC_9, 	KC_0, KC_BSLS, 
KC_TAB,  KC_Q, 	KC_W, 	KC_E, 	KC_R, 	KC_T, 				KC_Y, 	KC_U, 	KC_I, 	KC_O, 	KC_P, KC_BSPC, 
KC_LCTL, KC_A, 	KC_S, 	KC_D, 	KC_F, 	KC_G, 				KC_H, 	KC_J, 	KC_K, 	KC_L, 	KC_SCLN, KC_QUOT, 
KC_LSFT, KC_Z, 	KC_X, 	KC_C, 	KC_V, 	KC_B, 				KC_N, 	KC_M, 	KC_COMM, KC_DOT, KC_SLSH, SC_SENT, 
KC_CCCV,   KC_LGUI, KC_LALT, RGB_TOG, MO(1), TD(TD_SPC_DOT), KC_BSPC, KC_ENT, TD(TD_SPC_DOT), MO(2), KC_MINS, KC_EQL, KC_PGUP, KC_PGDN),

	[1] = LAYOUT(
KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_F6, 			KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, 
KC_TRNS, RGB_SAI, RGB_VAI, RGB_SAD, QK_BOOT, KC_LBRC, 			KC_RBRC, KC_PGUP, KC_UP, KC_PGDN, KC_INS, KC_HOME, 
KC_CAPS, RGB_HUD, RGB_VAD, RGB_HUI, KC_TRNS, KC_TRNS, 			KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL, KC_END, 
KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 			MAGIC_TOGGLE_NKRO, KC_TRNS, KC_TRNS, KC_MPLY, KC_MPRV, KC_MNXT, 
KC_NO,   KC_LGUI, KC_LALT, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_VOLU, KC_VOLD),

/*	[2] = LAYOUT(
QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, 				KC_6,KC_7, KC_8, KC_9, KC_0, KC_BSLS, 
KC_TAB,  KC_Q, KC_W, KC_F, KC_P, KC_G, 				KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC, 
KC_LCTL, KC_A, KC_R, KC_S, KC_T, KC_D, 				KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT, 
KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, 				KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT, 
KC_LCTL, KC_LGUI, KC_LALT, KC_NO, TO(0), KC_SPC, KC_BSPC, KC_ENT, KC_SPC, TO(0), KC_MINS, KC_EQL, KC_PGUP, KC_PGDN),
*/
	[2] = LAYOUT(
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
KC_NO, KC_NO, KC_NO, KC_NO, S_H_P, KC_NO, 			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
KC_NO, E_CL,  E_FU,  E_OP,  S_H,   SCRN_C, 			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
KC_NO, DC_C, E_SS, T_H_T, T_H_B, KC_NO, 			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO)

};


