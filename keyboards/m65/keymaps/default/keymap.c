#include "m65.h"

#define TAP(keycode) tap_code16(keycode)

enum custom_keycodes {
  F_Q = SAFE_RANGE, /* do */
  F_W , /* write */
  F_E , /* exp */
  F_R , /* read */
  F_T , /* */
  F_Y , /* */
  F_U , /* */
  F_I , /* */
  F_O , /* */
  F_P , /* */
  F_A , /* */
  F_S , /* */
  F_D , /* */
  F_F , /* */
  F_G , /* */
  F_H , /* */
  F_J , /* */
  F_K , /* */
  F_L , /* */
  F_Z , /* */
  F_X , /* */
  F_C , /* */
  F_V , /* */
  F_B , /* */
  F_N , /* */
  F_M , /* */
  C_Q , /* do */
  C_W , /* write */
  C_E , /* exp */
  C_R , /* read */
  C_T , /* */
  C_Y , /* */
  C_U , /* */
  C_I , /* */
  C_O , /* */
  C_P , /* */
  C_A , /* */
  C_S , /* */
  C_D , /* */
  C_F , /* */
  C_G , /* */
  C_H , /* */
  C_J , /* */
  C_K , /* */
  C_L , /* */
  C_Z , /* */
  C_X , /* */
  C_C , /* */
  C_V , /* */
  C_B , /* */
  C_N , /* */
  C_M , /* */
  M_EXTDISP,
  M_FIND
};

  enum layer_names {
    _QW = 0,
    _Fortran,
    _CPP
    };


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QW] = KEYMAP(
       KC_ESC,            KC_1,         KC_2,    KC_3,     KC_4,  KC_5,   KC_6,    KC_7,   KC_8,    KC_9,    KC_0,     KC_MINS,    KC_BSPC,
       KC_TAB,            KC_Q,         KC_W,    KC_E,     KC_R,  KC_T,   KC_Y,    KC_U,   KC_I,    KC_O,    KC_P, KC_LBRACKET, KC_RBRACKET,
      KC_NUHS,            KC_A,         KC_S,    KC_D,     KC_F,  KC_G,   KC_H,    KC_J,   KC_K,    KC_L, KC_SCLN,     KC_QUOT,      KC_ENT,
      KC_LSPO, KC_NONUS_BSLASH,         KC_Z,    KC_X,     KC_C,  KC_V,   KC_B,    KC_N,   KC_M, KC_COMM,  KC_DOT,       KC_UP,     KC_SLSH,
      KC_LCTL,         KC_LGUI, TT(_Fortran), KC_LALT, TT(_CPP),KC_SPC, KC_SPC, KC_SPC, KC_RALT, KC_RSPC, KC_LEFT,     KC_DOWN,    KC_RGHT),

  [_Fortran] = KEYMAP(
      KC_GRV, KC_AUDIO_MUTE,  KC_AUDIO_VOL_UP,  KC_AUDIO_VOL_DOWN,   KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE,  KC_MEDIA_NEXT_TRACK, M_EXTDISP,  KC_SYSTEM_SLEEP, KC_SYSTEM_WAKE, KC_PSCREEN, KC_DEL, KC_EQL,
      KC_BTN3,     F_Q,     F_W,     F_E,     F_R,     F_T,     F_Y,     F_U,     F_I,     F_O,     F_P, KC_TRNS, KC_TRNS,
      KC_BTN2,     F_A,     F_S,     F_D,     F_F,     F_G,     F_H,     F_J,     F_K,     F_L, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_BTN1,     F_Z,     F_X,     F_C,     F_V,     F_B,     F_N,     F_M, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS,
      KC_TRNS, KC_BTN4, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R),

  [_CPP] = KEYMAP(
      KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
      KC_TRNS,     C_Q,     C_W,     C_E,     C_R,     C_T,     C_Y,     C_U,     C_I,     C_O,     C_P, KC_TRNS, KC_TRNS,
      KC_TRNS,     C_A,     C_S,     C_D,     C_F,     C_G,     C_H,     C_J,     C_K,     C_L, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS,     C_Z,     C_X,     C_C,     C_V,     C_B,     C_N,     C_M, KC_TRNS, KC_TRNS, KC_WH_U, KC_TRNS,
      KC_TRNS,   RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_WH_L, KC_WH_D, KC_WH_R),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  // keyevent_t event = record->event;

  switch (id) {

  }
  return MACRO_NONE;
}

static inline void led_fortran(const bool on){

  if (on){
#ifdef KEYBOARD_m65_rev1
    writePinHigh(B13);
#endif
  } else {
#ifdef KEYBOARD_m65_rev1
    writePinLow(B13);
#endif
  }

}

static inline void led_cpp(const bool on){

  if (on){
#ifdef KEYBOARD_m65_rev1
    writePinHigh(B12);
#endif
  } else {
#ifdef KEYBOARD_m65_rev1
    writePinLow(B12);
#endif
  }

}

void matrix_init_user(void) {
#ifdef KEYBOARD_m65_rev1
  setPinOutput(B13);
  setPinOutput(B12);
#endif
}

void matrix_scan_user(void) {

  led_fortran(IS_LAYER_ON(_Fortran));
  led_cpp(IS_LAYER_ON(_CPP));
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // bool lalt = (keyboard_report->mods & MOD_BIT(KC_LALT));
  switch (keycode) {
    case M_EXTDISP:
      if (record->event.pressed) {
        TAP(LGUI(KC_P));
      }
      break;
    case M_FIND:
      if (record->event.pressed) {
        TAP(LALT(KC_F2));
      }
      break;
    case F_Q:
      if (record->event.pressed) {
        SEND_STRING("intent(inout)");
      }
      break;
    case F_W:
      if (record->event.pressed) {
        SEND_STRING("write()");
        TAP(KC_LEFT);
      }
      break;
    case F_R:
      if (record->event.pressed) {
        SEND_STRING("read()");TAP(KC_LEFT);
      }
      break;
    case F_E:
      if (record->event.pressed) {
        SEND_STRING("exp()");TAP(KC_LEFT);
      }
      break;
    case F_T:
      if (record->event.pressed) {
        SEND_STRING("type :: ");TAP(KC_ENT);
        SEND_STRING("end type");TAP(KC_UP);
      }
      break;
    case F_Y:
      if (record->event.pressed) {
        SEND_STRING("call random_number()");TAP(KC_LEFT);
      }
      break;
    case F_U:
      if (record->event.pressed) {
        SEND_STRING("use ");
      }
      break;
    case F_I:
      if (record->event.pressed) {
        SEND_STRING("if () then");
        TAP(KC_ENT);
        SEND_STRING("else");
        TAP(KC_ENT);
        SEND_STRING("end if");
        TAP(KC_UP);
        TAP(KC_UP);
        TAP(KC_LEFT);
        TAP(KC_LEFT);
      }
      break;
    case F_O:
      if (record->event.pressed) {
        SEND_STRING("open()");TAP(KC_LEFT);
      }
      break;
    case F_P:
      if (record->event.pressed) {
        SEND_STRING("parameter");
      }
      break;
    case F_A:
      if (record->event.pressed) {
        SEND_STRING("return");TAP(KC_ENT);
      }
      break;
    case F_S:
      if (record->event.pressed) {
        SEND_STRING("subroutine");TAP(KC_ENT);
        SEND_STRING("end subroutine");TAP(KC_UP);
      }
      break;
    case F_D:
      if (record->event.pressed) {
        SEND_STRING("do ");
        TAP(KC_ENT);
        SEND_STRING("end do");
        TAP(KC_UP);
      }
      break;
    case F_F:
      if (record->event.pressed) {
        SEND_STRING("function");TAP(KC_ENT);
        SEND_STRING("end function");TAP(KC_UP);
      }
      break;
    case F_G:
      if (record->event.pressed) {
        SEND_STRING("https://en.wikipedia.org/wiki/Goto");
      }
      break;
    case F_H:
      if (record->event.pressed) {
      }
      break;
    case F_J:
      if (record->event.pressed) {
      }
      break;
    case F_K:
      if (record->event.pressed) {
      }
      break;
    case F_L:
      if (record->event.pressed) {
        SEND_STRING("close()");TAP(KC_LEFT);
      }
      break;
    case F_Z:
      if (record->event.pressed) {
      }
      break;
    case F_X:
      if (record->event.pressed) {
      }
      break;
    case F_C:
      if (record->event.pressed) {
        SEND_STRING("class()");TAP(KC_LEFT);
      }
      break;
    case F_V:
      if (record->event.pressed) {
      }
      break;
    case F_B:
      if (record->event.pressed) {
      }
      break;
    case F_N:
      if (record->event.pressed) {
        SEND_STRING("newunit");
      }
      break;
    case F_M:
      if (record->event.pressed) {
        SEND_STRING("module");TAP(KC_ENT);
        SEND_STRING("end module");TAP(KC_UP);
      }
      break;
    case C_Q:
      if (record->event.pressed) {
      }
      break;
    case C_W:
      if (record->event.pressed) {
      }
      break;
    case C_E:
      if (record->event.pressed) {
      }
      break;
    case C_R:
      if (record->event.pressed) {
      }
      break;
    case C_T:
      if (record->event.pressed) {
      }
      break;
    case C_Y:
      if (record->event.pressed) {
      }
      break;
    case C_U:
      if (record->event.pressed) {
      }
      break;
    case C_I:
      if (record->event.pressed) {
        SEND_STRING("if () {");TAP(KC_ENT);
        SEND_STRING("} else {");TAP(KC_ENT);
        SEND_STRING("}");
        TAP(KC_UP);
        TAP(KC_UP);
        TAP(KC_RIGHT);
        TAP(KC_RIGHT);
        TAP(KC_RIGHT);

      }
      break;
    case C_O:
      if (record->event.pressed) {
      }
      break;
    case C_P:
      if (record->event.pressed) {
      }
      break;
    case C_A:
      if (record->event.pressed) {
      }
      break;
    case C_S:
      if (record->event.pressed) {
        SEND_STRING("switch () {");TAP(KC_ENT);
        SEND_STRING("case :"); TAP(KC_ENT);
        SEND_STRING("break;");TAP(KC_ENT);
        SEND_STRING("default:");TAP(KC_ENT);
        SEND_STRING("}");
        TAP(KC_UP);TAP(KC_UP);TAP(KC_UP);TAP(KC_UP);
      }
      break;
    case C_D:
      if (record->event.pressed) {
      }
      break;
    case C_F:
      if (record->event.pressed) {
      }
      break;
    case C_G:
      if (record->event.pressed) {
        SEND_STRING("https://en.wikipedia.org/wiki/Goto");
      }
      break;
    case C_H:
      if (record->event.pressed) {
      }
      break;
    case C_J:
      if (record->event.pressed) {
      }
      break;
    case C_K:
      if (record->event.pressed) {
      }
      break;
    case C_L:
      if (record->event.pressed) {
      }
      break;
    case C_Z:
      if (record->event.pressed) {
      }
      break;
    case C_X:
      if (record->event.pressed) {
      }
      break;
    case C_C:
      if (record->event.pressed) {
      }
      break;
    case C_V:
      if (record->event.pressed) {
      }
      break;
    case C_B:
      if (record->event.pressed) {
      }
      break;
    case C_N:
      if (record->event.pressed) {
      }
      break;
    case C_M:
      if (record->event.pressed) {
      }
      break;
  }

  return true;
}
