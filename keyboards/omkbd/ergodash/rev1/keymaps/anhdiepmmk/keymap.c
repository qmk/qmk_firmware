#include QMK_KEYBOARD_H


enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUM,
    // _SYM,
    // _NAV,
    // _FUN,
    // _MEDIA,
    // _MOUSE
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  NUM,
};

// home row mod
#define HO_A MT(MOD_LCTL, KC_A)
#define HO_S MT(MOD_LSFT, KC_S)
#define HO_D MT(MOD_LALT, KC_D)
#define HO_F MT(MOD_LGUI, KC_F)
#define HO_J MT(MOD_RGUI, KC_J)
#define HO_K MT(MOD_RALT, KC_K)
#define HO_L MT(MOD_RSFT, KC_L)
#define HO_SCLN MT(MOD_RCTL, KC_SCLN)

// thumb
#define TH_ENT LT(NUM, KC_ENT) 

// num alias
#define A_R_B KC_RIGHT_BRACKET 
#define A_L_B KC_LEFT_BRACKET 
#define A_EQ KC_EQUAL 
#define A_BS KC_BACKSLASH
#define A_SMC KC_SEMICOLON
#define A_GRAV KC_GRAVE
#define A_MINUS KC_MINUS

#define EISU LALT(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |   [  |                    |   ]  |   6  |   7  |   8  |   9  |   0  |Pscree|
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |  `   |   Q  |   W  |   E  |   R  |   T  |   -  |                    |   =  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |  Del |                    | Bksp |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  | Space|                    | Enter|   N  |   M  |   ,  |   .  |   /  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  GUI |  ALt | EISU |||||||| Lower| Space|  Del |||||||| Bksp | Enter| Raise|||||||| Left | Down |  Up  | Right|
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY] = LAYOUT(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_GRV,                              KC_BSLS, KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,   KC_EQL,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,                             KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_BSPC,
    KC_ESC,  HO_A,    HO_S,    HO_D,    HO_F,    KC_G,    KC_NO,                               KC_NO,   KC_H,    HO_J,    HO_K,    HO_L,    HO_SCLN,   KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    LOWER,                               RAISE,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_NO,
    KC_LCTL, KC_LGUI, KC_NO,   KC_LALT,          KC_DEL,  LOWER,   KC_SPC,             TH_ENT, RAISE,   KC_BSPC,          KC_RGUI, KC_APP,  KC_NO,     KC_NO
  ),

  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |   {  |                    |   }  |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |  ~   |   !  |   @  |   #  |   $  |   %  |   _  |                    |   +  |   ^  |   &  |   *  |   (  |   )  |  |   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   1  |   2  |   3  |   4  |   5  |  Del |                    | Bksp |   H  |   J  |   K  |   L  |   :  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   6  |   7  |   8  |   9  |   0  | Space|                    | Enter|   N  |   M  |   <  |   >  |   ?  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  GUI |  ALt | EISU |||||||| Lower| Space|  Del |||||||| Bksp | Enter| Raise|||||||| Home |PageDn|PageUp|  End |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______,                            _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_CAPS, KC_7, KC_8, KC_9, KC_0,    _______, _______,                            _______, _______, KC_HOME, _______, KC_END,  KC_PGUP, KC_INS,
    _______, KC_4, KC_5, KC_6, _______, _______, _______,                            _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGDN, _______,
    _______, KC_1, KC_2, KC_3, _______, _______, LOWER,                              RAISE,   _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
    _______, _______, _______, _______, _______, LOWER,   _______,          _______, RAISE,   _______,          _______, KC_PSCR, _______, _______
),

  /* Raise
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |   {  |                    |   }  |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |  ~   |   !  |   @  |   #  |   $  |   %  |   _  |                    |   +  |   ^  |   &  |   *  |   (  |   )  |  |   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   1  |   2  |   3  |   4  |   5  |  Del |                    | Bksp |   H  |   J  |   K  |   L  |   :  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   6  |   7  |   8  |   9  |   0  | Space|                    | Enter|   N  |   M  |   <  |   >  |   ?  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  GUI |  ALt | EISU |||||||| Lower| Space|  Del |||||||| Bksp | Enter| Raise|||||||| Home |PageDn|PageUp|  End |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_RAISE] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______,                            _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_CAPS, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, _______,                            _______, _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_INS,
    _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                            _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGDN, _______,
    _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, LOWER,                              RAISE,   _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
    _______, _______, _______, _______,          _______, LOWER,   _______,          _______, RAISE,   _______,          _______, KC_PSCR, _______, _______ 
  ),

  /* Adjust
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      | Reset|RGB ON|  MODE|  HUE-|  HUE+|      |                    |      |  SAT-|  SAT+|  VAL-|  VAL+|      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      | BL ON|  BRTG|  INC|   DEC|      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      |      |      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______,
    _______, QK_BOOT, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,_______,                       _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______,
    _______, _______, BL_TOGG, BL_BRTG, BL_UP  , BL_DOWN,_______,                       _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,          _______,_______,_______,       _______,_______, _______,          _______, _______, _______, _______
  ),
  /* 
   * Num
   */
  [_NUM] = LAYOUT(
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______,
    _______, A_L_B  , KC_7   , KC_8   , KC_9   , A_R_B  ,_______,                       _______, _______, _______, _______, _______, _______, _______,
    _______, A_SMC  , KC_4   , KC_5   , KC_6   , A_EQ   ,_______,                       _______, _______, _______, _______, _______, _______, _______,
    _______, A_GRAV , KC_1   , KC_2   , KC_3   , A_BS   ,_______,                       _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,          KC_DOT ,KC_0   ,A_MINUS,       _______,_______, _______,          _______, _______, _______, _______
  )
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
         print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
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
    case NUM:
      if (record->event.pressed) {
        layer_on(_NUM);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_NUM);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}
