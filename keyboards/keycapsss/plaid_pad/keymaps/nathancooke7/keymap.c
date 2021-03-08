#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Mission Control */
  #define DESK_L RCTL(KC_LEFT)
  #define DESK_R RCTL(KC_RIGHT)
  #define DESKTOP KC_F11
  #define MISSION RCTL(KC_UP)
/* Audio */
  #define VOL_D KC_AUDIO_VOL_DOWN
  #define VOL_U KC_AUDIO_VOL_UP
  #define MUTE KC_AUDIO_MUTE
/* Amethyst */
  #define AM_1 KC_F4
  #define AM_2 KC_F2
  #define AM_3 KC_F3
  #define AM_RITE LALT(LCTL(LSFT(KC_2)))
  #define AM_LEFT LALT(LCTL(LSFT(KC_1)))
  #define AM_CYCLE LSFT(LALT(LCTL(KC_SPC)))
  #define AM_CW LSFT(LALT(KC_J))
  #define AM_CCW LSFT(LALT(KC_K))
/* ALT Arrows */
  /* #define ALT_U RALT(KC_DOWN) */
  /* #define ALT_D RALT(KC_UP) */
/* Google Meet */
  #define MUTE_MIC LGUI(KC_D)
/* MISC */
  #define COPY LGUI(KC_C)
  #define PASTE LGUI(KC_V)

LAYOUT_ortho_4x4(
		MUTE     , COPY   , PASTE  , DESKTOP  ,
		AM_LEFT  , DESK_L , DESK_R , AM_RITE  ,
		AM_1     , AM_2   , AM_3   , AM_CYCLE ,
		MUTE_MIC , AM_CW  , AM_CCW , _______
)

};

// Set led state during powerup
void keyboard_post_init_user(void) {
    writePinHigh(LED_RED);
}

void encoder_update_user(uint8_t index, bool clockwise) {
/*
Rev1
,-----------------------,
|  E1 |     |     |  E2 |
|-----+-----+-----+-----|
|     |     |     |     |
|-----+-----+-----+-----|
|     |     |     |     |
|-----+-----+-----+-----|
|     |     |     |     |
`-----------------------'
 */

  // First encoder (E1)
  if (index == 0) {
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
  // Second encoder (E2)
  } else if (index == 1) {
    if (clockwise) {
      tap_code(KC_PGDN);
    } else {
      tap_code(KC_PGUP);
    }
  }
}
