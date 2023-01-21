#include QMK_KEYBOARD_H

enum layer_names {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
  GUSR,
  HGRP,
  CHUS,
};

#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen
#define KC_ESCC MT(MOD_LCTL, KC_ESC)
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST QK_BOOT
#define KC_BL_S BL_STEP

// Left and right shift as mot-tap square braces
#define KC_LSBR MT(MOD_LSFT, KC_LBRC)
#define KC_RSBR MT(MOD_RSFT, KC_RBRC)

// mod-tap shift/minus
#define KC_SMIN MT(MOD_LSFT, KC_MINS)

// Tap-toggle layers
#define KC_TT_L TT(1)
#define KC_TT_R TT(2)

#define KC_RGBM RGB_MOD
#define KC_RGBT RGB_TOG

#define KC_SLOK LGUI(LCTL(KC_Q)) // mojave lock screen
#define KC_GUSR GUSR // "gam info user" macro
#define KC_HGRP HGRP // "history | grep" macro
#define KC_CHUS CHUS // "thisisunsafe" chrome browser macro

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                    ,-------+-------+-------+-------+-------+-------.
     KC_GRV , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                      KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                      KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_BSLS,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     KC_ESC , KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                      KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
  //|-------+-------+-------+-------+-------+-------+-------.    ,-------|-------+-------+-------+-------+-------+-------|
     KC_LSBR, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,KC_TT_L,     KC_TT_R, KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_RSBR,
  //`-------+-------+-------+---+---+-------+-------+-------/    \-------+-------+-------+---+---+-------+-------+-------'
                                 KC_LCTL,KC_SMIN,KC_LGUI,             KC_ENT ,KC_SPC ,KC_LALT
  //                            `-------+-------+-------'            `-------+-------+-------'
  ),

  [_LOWER] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                    ,-------+-------+-------+-------+-------+-------.
     KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                     KC_CIRC,KC_AMPR,KC_ASTR,KC_MINS,KC_EQL ,_______,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     _______,KC_SLOK,_______, KC_UP ,_______,KC_RGBT,                      KC_P7 , KC_P8 , KC_P9 , KC_E  , KC_F  ,KC_LPRN,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     KC_DEL ,_______,KC_LEFT,KC_DOWN,KC_RGHT,KC_GUSR,                      KC_P4 , KC_P5 , KC_P6 , KC_C  , KC_D  ,KC_RPRN,
  //|-------+-------+-------+-------+-------+-------+-------.    ,-------|-------+-------+-------+-------+-------+-------|
     KC_BL_S,_______,_______,_______,KC_HGRP,KC_CHUS,_______,     _______, KC_P1 , KC_P2 , KC_P3 , KC_A  , KC_B  ,_______,
  //`-------+-------+-------+---+---+-------+-------+-------/    \-------+-------+-------+---+---+-------+-------+-------'
				 _______,_______,_______,             KC_DOT , KC_P0 ,KC_COLN
  //                            `-------+-------+-------'            `-------+-------+-------'
  ),

  [_RAISE] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                    ,-------+-------+-------+-------+-------+-------.
     KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                      KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     _______,KC_RGBT,KC_RGBM,_______,_______,_______,                     _______,KC_AMPR,KC_MUTE,_______,_______,_______,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     _______,KC_CAPW,KC_CPYW,KC_CAPP,KC_CPYP,KC_PGUP,                     KC_EQL ,KC_HOME,KC_VOLU,KC_MRWD,KC_MFFD,_______,
  //|-------+-------+-------+-------+-------+-------+-------.    ,-------|-------+-------+-------+-------+-------+-------|
     _______,_______,_______,_______,_______,KC_PGDN,_______,     _______,KC_PLUS,KC_END ,KC_VOLD,KC_MPLY,KC_MSTP,_______,
  //`-------+-------+-------+---+---+-------+-------+-------/    \-------+-------+-------+---+---+-------+-------+-------'
                                 _______,_______,_______,             _______,_______,_______
  //                            `-------+-------+-------'            `-------+-------+-------'
  ),

  [_ADJUST] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                          ,--------+--------+--------+--------+--------+--------.
      _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______,                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      QK_BOOT, DB_TOGG, RGB_HUD, RGB_SAD, RGB_VAD, _______,                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------.        ,--------|--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //`--------+--------+--------+----+---+--------+--------+--------/        \--------+--------+--------+---+----+--------+--------+--------'
                                      _______, _______, _______,                  _______, _______, _______
  //                                `--------+--------+--------'                `--------+--------+--------'
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case GUSR:
      if (record->event.pressed) {
        SEND_STRING("gam info user ");
      }
      break;
    case HGRP:
      if (record->event.pressed) {
        SEND_STRING("history|grep ");
      }
      break;
    case CHUS:
      if (record->event.pressed) {
	SEND_STRING("thisisunsafe");
      }
      break;
  }
  return true;
}
