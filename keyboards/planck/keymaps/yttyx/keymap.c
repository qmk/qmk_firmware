
#include QMK_KEYBOARD_H

enum planck_layers {
  _BA,        // Base (Balance Twelve mirror variant)
  _PL,        // Plover (http://opensteno.org)
  _NP,        // Numeric/punctuation
  _FN,        // Function
  _CU         // Cursor
};

enum planck_keycodes {
  BA  = SAFE_RANGE,
  PL
};


// Abbreviations
#define KX_SFT_Z   MT(MOD_LSFT, KC_Z)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* BA
    .--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.
    | P      | L      | C      | D      | W      | PL     | U      | O      | Y      | K      | Q      | BS     |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    | N      | R      | S      | T      | M      | CU     | A      | E      | I      | H      | V      | Ret    |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    | Z Sft  | J      | F      | G      | B      |        | ' @    | , <    | . >    | X      | Sft    |        |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    | Ctl    | Alt    | Sup    | NP     | Spc    | Esc    | Sft    | FN     | Sup    | Alt    | Ctl    |        |
    '--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'
  */                                                                                                            
  [_BA] = LAYOUT_planck_grid(                                                   
    KC_P,     KC_L,    KC_C,    KC_D,    KC_W,   PL,      KC_U,    KC_O,    KC_Y,    KC_K,    KC_Q,    KC_BSPC,
    KC_N,     KC_R,    KC_S,    KC_T,    KC_M,   TG(_CU), KC_A,    KC_E,    KC_I,    KC_H,    KC_V,    KC_ENT,
    KX_SFT_Z, KC_J,    KC_F,    KC_G,    KC_B,   XXXXXXX, KC_QUOT, KC_COMM, KC_DOT,  KC_X,    XXXXXXX, XXXXXXX,
    KC_LCTL,  KC_LALT, KC_LGUI, MO(_NP), KC_SPC, KC_ESC,  KC_RSFT, MO(_FN), KC_LALT, KC_LCTL, KC_LGUI, XXXXXXX
  ),

  /* Plover
    .--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.
    | #      | #      | #      | #      |        | BA     | #      | #      | #      | #      | #      |        |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    | S      | T      | P      | H      |        | *      | F      | P      | L      | T      | D      |        |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    | S      | K      | W      | R      |        | *      | R      | B      | G      | S      | Z      |        |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    | Exit   |        |        | A      | O      |        | E      | U      |        |        |        |        |
    '--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'
  */
  [_PL] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1, XXXXXXX, BA,      KC_1, KC_1, KC_1,    KC_1,    KC_1,    XXXXXXX,
    KC_Q,    KC_W,    KC_E,    KC_R, XXXXXXX, KC_Y,    KC_U, KC_I, KC_O,    KC_P,    KC_LBRC, XXXXXXX,
    KC_A,    KC_S,    KC_D,    KC_F, XXXXXXX, KC_H,    KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_C, KC_V,    XXXXXXX, KC_N, KC_M, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  /* Numeric/punctuation
    .--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.
    | 1 !    | 2 "    | 3 £    | 4 $    | 5 %    |        | 6 ^    | 7 &    | 8 *    | 9 (    | 0 )    | BS     |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    | Tab    | Ctl-X  | Ctl-C  | Ctl-V  | Ctl-Z  |        | [ {    | ] }    | - _    | ; :    | \ |    | Ret    |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    | Sft    |        |        | Del    | Ins    |        | / ?    | = +    | # ~    | `      | Sft    |        |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    | Ctl    | Alt    | Sup    | NP     | Spc    |        | Sft    |        | Sup    | Alt    | Ctl    |        |
    '--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'
  */                                                                                                            
  [_NP] = LAYOUT_planck_grid(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    KC_TAB,  C(KC_X), C(KC_C), C(KC_V), C(KC_Z), XXXXXXX, KC_LBRC, KC_RBRC, KC_MINS, KC_SCLN, KC_NUBS, _______,
    KC_LSFT, XXXXXXX, XXXXXXX, KC_DEL,  KC_INS,  XXXXXXX, KC_SLSH, KC_EQL,  KC_NUHS, KC_GRV,  XXXXXXX, XXXXXXX,
    _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______, _______, _______, XXXXXXX
  ),

  /* Function
    .--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.
    | Esc    | F1     | F2     | F3     | F4     |        |        |        |        |        |        |        |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    | Tab    | F5     | F6     | F7     | F8     |        |        |        |        |        |        |        |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    | Sft    | F9     | F10    | F11    | F12    |        | PScr   | Break  | ScLk   | Caps   | Sft    |        |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    | Ctl    | Alt    | Sup    |        | Spc    |        | Sft    | FN     | Sup    | Alt    | Ctl    |        |
    '--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'
  */                                                                                                            
  [_FN] = LAYOUT_planck_grid(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, KC_F11,  KC_F12,  XXXXXXX, KC_PSCR, KC_BRK,  KC_SLCK, KC_CAPS, XXXXXXX, XXXXXXX,
    _______, _______, _______, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, XXXXXXX
  ),

  /* Cursor
    .--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.
    |        |        |        |        |        |        | Home   | Up     | End    | PgUp   |        |        |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    |        |        |        |        |        | BA     | Left   | Down   | Right  | PgDn   |        |        |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    | Sft    |        |        |        |        |        |        |        |        |        | Sft    |        |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    | Ctl    | Alt    | Sup    |        |        |        | Sft    | FN     | Sup    | Alt    | Ctl    |        |
    '--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'
  */                                                                                                            
  [_CU] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_PGUP, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX,
    _______, _______, _______, XXXXXXX, _______, _______, _______, XXXXXXX, _______, _______, _______, XXXXXXX
  )

};


#ifdef AUDIO_ENABLE
  float plover_on[][2]   = SONG(PLOVER_SOUND);
  float plover_off[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case PL:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_on);
        #endif
        
        layer_off(_NP);
        layer_off(_FN);
        layer_off(_CU);
        layer_on(_PL);

        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
    case BA:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_off);
        #endif
       
        layer_off(_NP);
        layer_off(_PL);
        layer_off(_FN);
        layer_off(_CU);
      }
      return false;
    }
    return true;
  }

