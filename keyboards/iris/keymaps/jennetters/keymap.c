#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  YUNO,
  SHRG,
  NOVY,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_YUNO YUNO
#define KC_SHRG SHRG
#define KC_NOVY NOVY
#define KC_RST RESET
#define KC_BL_S BL_STEP

//Tap Dance Declartaions
enum {
  ESC_GR = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(

  //  ,----+----+----+----+----+----.              ,----+----+----+----+----+----.
  //  | ESC| 1  | 2  | 3  | 4  | 5  |              | 6  | 7  | 8  | 9  | 0  | -  |
  //  |----+----+----+----+----+----|              |----+----+----+----+----+----|
  //  | TAB| Q  | W  | E  | R  | T  |              | Y  | U  | I  | O  | P  | BSP|
  //  |----+----+----+----+----+----|              |----+----+----+----+----+----|
  //  | CAP| A  | S  | D  | F  | G  |              | H  | J  | K  | L  | ;  | '  |
  //  |----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
  //  | SFT| Z  | X  | C  | V  | B  | SPC|    | SPC| N  | M  | ,  | .  | /  | ENT|
  //  `----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
  //                   \  GUI| ALT| CTL /      \RASE\ CTL | SFT / 
  //                    `----+----+----'        `----+----+----'

  TD(ESC_GR), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, \
  KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, \
  KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_SPC, KC_SPC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT, \
  KC_LGUI, KC_LALT, KC_LCTL, KC_RASE, KC_RCTL, KC_RSFT
  ),

  [_LOWER] = LAYOUT_kc(
 
  //  ,----+----+----+----+----+----.              ,----+----+----+----+----+----.
  //  |  ~ | !  | @  | #  | $  | %  |              | ^  | &  | *  | (  | )  | DEL|
  //  |----+----+----+----+----+----|              |----+----+----+----+----+----|
  //  |    | 1  | 2  | 3  | 4  | 5  |              | 6  | 7  | 8  | 9  | 0  |    |
  //  |----+----+----+----+----+----|              |----+----+----+----+----+----|
  //  |    |    |    |    |    |    |              |    |    |    |    |    |PIPE|
  //  |----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
  //  | \  |    |    |    |    | [  | (  |    | )  | ]  |    |    |    | -  |    |
  //  `----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
  //                   \     |    | DEL /      \ DEL\     |     / 
  //                    `----+----+----'        `----+----+----'

  TILD, EXLM, AT, HASH, DLR, PERC, CIRC, AMPR, ASTR, LPRN, RPRN, DEL, \
   , 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, , \
   , , , , , , , , , , ,PIPE, \
  BL_S, , , , , LCBR, LPRN, RPRN, RCBR, , , , MINS, , \
   , , DEL, DEL, ,  
  ),

  [_RAISE] = LAYOUT_kc(
  //  ,----+----+----+----+----+----.              ,----+----+----+----+----+----.
  //  |    | F1 | F2 |    |    |    |              |    |    |    | [  | ]  | =  |
  //  |----+----+----+----+----+----|              |----+----+----+----+----+----|
  //  |    |    | UP |    |    |    |              |    |    |    | {  | }  | DEL|
  //  |----+----+----+----+----+----|              |----+----+----+----+----+----|
  //  |    | LT | DN | RT |    |    |              |SHRG|    |    |    |PIPE|    |
  //  |----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
  //  |    |    |    |    |    |    |    |    |    |    |    |    |    | \  |    |
  //  `----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
  //                   \     |    |     /      \    \     |     / 
  //                    `----+----+----'        `----+----+----'

   , F1, F2, , , , , , , LBRC, RBRC, EQL, \
   , , UP, , , , YUNO, NOVY, , LCBR, RCBR, DEL, \
   , LEFT, DOWN, RIGHT, , , SHRG, , , , PIPE, , \
   , , , , , , , , , , , , BSLS, , \
   , , , , , 
  ),

  [_ADJUST] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                          ,--------+--------+--------+--------+--------+--------.
      _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, \
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, \
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, \
  //|--------+--------+--------+--------+--------+--------+--------.        ,--------|--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, \
  //`--------+--------+--------+----+---+--------+--------+--------/        \--------+--------+--------+---+----+--------+--------+--------'
                                      _______, _______, _______,                  _______, _______, _______
  //                                `--------+--------+--------'                `--------+--------+--------'
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void esc_gr_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_ESC);
  } else if (state->count == 2) {
    register_code (KC_GRV);
  } else {
    register_code (KC_LSFT);
    register_code (KC_GRV);
  }
}

void esc_gr_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_ESC);
  } else if (state->count == 2) {
    unregister_code (KC_GRV);
  } else {
    unregister_code (KC_LSFT);
    unregister_code (KC_GRV);
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for ESC, twice for `, thrice for ~
  [ESC_GR] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, esc_gr_finished, esc_gr_reset)
  // Other declarations would go here, separated by commas, if you have them
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
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
    case SHRG:
      if (record->event.pressed) {
      SEND_STRING("¯\\_(ツ)_/¯"); // I dunno.
               return false;
      }
    /* Ignore for now - special characters not working with macros
       }
    case NOVY:
      if (record->event.pressed) {
        SEND_STRING("ლ(ಠ_ಠლ)"); // YUNO?!
                return false;
      } 
    */ 
  }
  return true;
}