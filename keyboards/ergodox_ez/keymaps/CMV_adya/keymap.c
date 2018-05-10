#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "shortcut_utils.h"

#define __________ KC_TRANSPARENT
#define XXXXXXXXXX KC_NO

#define CT(kc) CTL_T(kc)

/* LAYERS */
enum {
  _COLEMAK = 0,
  _STANDARD,
  _MACROS,
  _SYMBOLS,
  _NAVIGAT,
};

/* MACROS */
enum {
  NEXT_TAB = 0,
  PREV_TAB,
  NEW_TAB,
  CLOSE_TAB,
  NEXT_WIN,
  CLOSE_WIN,
  TOG_DAMR, // CMV: toggle on/off delay after modifier relase
  TOG_DAKP, // CMV: toggle on/off dynamic active key processing
  INFOS,
};

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * COLEMAK - Main and default layer
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   NO   |  1   |  2   |  3   |  4   |  5   |TG(1) |           | TG(2)|   6  |   7  |   8  |   9  |   0  |   NO   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  LALT  |  Q   |  W   |  F   |  P   |  G   |TG(4) |           | TG(4)|   J  |   L  |   U  |   Y  |  . , |  RCTRL |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | MO(3)  |  A   |  R   |  S   |  T   |  D   |------|           |------|   H  |   N  |   E  |   I  |   O  |   ' "  |
 * |--------+------+------+------+------+------|HYPER |           |  MEH |------+------+------+------+------+--------|
 * | LSHIFT |  Z   |  X   |  C   |  V   |  B   |      |           |      |   K  |   M  |  - _ |  = + |  ; : | RSHIFT |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | ESC  |MO(4) | RALT |MO(3) |LCTRL |                                       | LEFT | RIGHT|  < > |  \ / | RALT |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  NO  |  NO  |       |  NO  |  NO  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | PGDN |       | PGUP |      |  DEL |
 *                                 |SPACE | TAB  |------|       |------| ENTER|      |
 *                                 |      |      | END  |       | HOME |      | BSPC |
 *                                 `--------------------'       `--------------------'
 */
  [_COLEMAK] = KEYMAP(
    XXXXXXXXXX,         KC_1,         KC_2,         KC_3,         KC_4,         KC_5,TG(_STANDARD),
       KC_LALT,         KC_Q,         KC_W,         KC_F,         KC_P,         KC_G, TG(_NAVIGAT),
  MO(_SYMBOLS),         KC_A,         KC_R,         KC_S,         KC_T,         KC_D,
     KC_LSHIFT,         KC_Z,         KC_X,         KC_C,         KC_V,         KC_B, ALL_T(KC_NO),
     KC_ESCAPE, MO(_NAVIGAT),      KC_RALT, MO(_SYMBOLS),     KC_LCTRL,
                                                                          XXXXXXXXXX,   XXXXXXXXXX,
                                                                                         KC_PGDOWN,
                                                              KC_SPACE,       KC_TAB,       KC_END,

 TG(_STANDARD),         KC_6,         KC_7,         KC_8,         KC_9,         KC_0,   XXXXXXXXXX,
  TG(_NAVIGAT),         KC_J,         KC_L,         KC_U,         KC_Y,       KC_DOT,     KC_RCTRL,
                        KC_H,         KC_N,         KC_E,         KC_I,         KC_O,     KC_QUOTE,
  MEH_T(KC_NO),         KC_K,         KC_M,     KC_MINUS,     KC_EQUAL,    KC_SCOLON,OSM(MOD_LSFT),
                                   KC_LEFT,     KC_RIGHT,      KC_LABK,    KC_BSLASH,      KC_RALT,
    XXXXXXXXXX,   XXXXXXXXXX,
       KC_PGUP,
       KC_HOME,     KC_ENTER,    KC_BSPACE
  ),


/*
 * SYMBOLS - Symbols layer
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   __   |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   __   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  LALT  |  #   |  &   |  ?   |  {   |  }   |TO(4) |           | TO(4)|   -  | KP_7 | KP_8 | KP_9 |   /  |  RCTRL |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | __ (MO)|  ~   |  $   |  !   |  (   |  )   |------|           |------|   +  | KP_4 | KP_5 | KP_6 |   *  |   %    |
 * |--------+------+------+------+------+------|HYPER |           |  MEH |------+------+------+------+------+--------|
 * | LSHIFT |  ^   |  |   |  @   |  [   |  ]   |      |           |      |  . , | KP_1 | KP_2 | KP_3 | KP_0 | RSHIFT |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  __  |  `   | RALT |__(MO)|LCTRL |                                       |   UP | DOWN |   =  |  __  | RALT |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  __  |  __  |       |  __  |  __  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | PGDN |       | PGUP |      |  DEL |
 *                                 |SPACE | TAB  |------|       |------| ENTER|      |
 *                                 |      |      | END  |       | HOME |      | BSPC |
 *                                 `--------------------'       `--------------------'
 */
  [_SYMBOLS] = KEYMAP(
    __________,        KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_F5,        KC_F6,
       KC_LALT,      KC_HASH, KC_AMPERSAND,  KC_QUESTION,      KC_LCBR,      KC_RCBR, TO(_NAVIGAT),
    __________,     KC_TILDE,    KC_DOLLAR,   KC_EXCLAIM,      KC_LPRN,      KC_RPRN,
     KC_LSHIFT,KC_CIRCUMFLEX,      KC_PIPE,        KC_AT,  KC_LBRACKET,  KC_RBRACKET, ALL_T(KC_NO),
    __________,     KC_GRAVE,      KC_RALT,   __________,     KC_LCTRL,
                                                                          __________,   __________,
                                                                                         KC_PGDOWN,
                                                              KC_SPACE,       KC_TAB,       KC_END,

         KC_F7,        KC_F8,        KC_F9,       KC_F10,       KC_F11,       KC_F12,   __________,
  TO(_NAVIGAT),  KC_KP_MINUS,      KC_KP_7,      KC_KP_8,      KC_KP_9,  KC_KP_SLASH,     KC_RCTRL,
                  KC_KP_PLUS,      KC_KP_4,      KC_KP_5,      KC_KP_6,KC_KP_ASTERISK,  KC_PERCENT,
  MEH_T(KC_NO),    KC_KP_DOT,      KC_KP_1,      KC_KP_2,      KC_KP_3,      KC_KP_0,    KC_RSHIFT,
                                     KC_UP,      KC_DOWN,     KC_EQUAL,  __________,      KC_RALT,
    __________,   __________,
       KC_PGUP,
       KC_HOME,     KC_ENTER,    KC_BSPACE
  ),

/*
 * NAVIGAT - Navigation layer
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  WAKE  | F13  | F14  | F15  | F16  | F17  | F18  |           |  F19 |  F20 |  F21 |  F22 |  F23 |  F24 |  SLEEP |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   __   |TO(0) |TO(1) |  UP  |TO(2) |TO(3) |  __  |           |  __  | TO(4)| TO(5)| MS_UP| TO(6)| TO(8)| MS_ACC2|
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   __   | MUTE | LEFT | DOWN |RIGHT |VOLUP |------|           |------| WBACK| MS_LT| MS_DN| MS_RT|MSWHUP| MS_ACC1|
 * |--------+------+------+------+------+------|  __  |           |  __  |------+------+------+------+------+--------|
 * |   __   |ESCAPE|LSHIFT| LALT | RALT |VOLDN |      |           |      |NEWTAB|NT_WIN|CS_WIN|MSBTN2|MSWHDN| MS_ACC0|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  __  |__(MO)|  __  | LGUI |LCTRL |                                       |PV_TAB|NT_TAB|MSBTN3|CS_TAB|  F5  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  __  |  __  |       | POWER|  __  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  __  |       |  __  |      |      |
 *                                 |SPACE | TAB  |------|       |------| ENTER|MSBTN1|
 *                                 |      |      | PGDN |       | PGUP |      |      |
 *                                 `--------------------'       `--------------------'
 */
  [_NAVIGAT] = KEYMAP(
       KC_WAKE,       KC_F13,       KC_F14,       KC_F15,       KC_F16,       KC_F17,       KC_F18,
    __________,        TO(0),        TO(1),        KC_UP,        TO(2),        TO(3),   __________,
    __________,      KC_MUTE,      KC_LEFT,      KC_DOWN,     KC_RIGHT,      KC_VOLU,
    __________,    KC_ESCAPE,    KC_LSHIFT,      KC_LALT,      KC_RALT,      KC_VOLD,   __________,
    __________,   __________,   __________,      KC_LGUI,     KC_LCTRL,
                                                                          __________,   __________,
                                                                                        __________,
                                                              KC_SPACE,       KC_TAB,    KC_PGDOWN,

        KC_F19,       KC_F20,       KC_F21,       KC_F22,       KC_F23,       KC_F24,      KC_SLEP,
    __________,        TO(4),        TO(5),     KC_MS_UP,        TO(6),        TO(8), KC_MS_ACCEL2,
                 KC_WWW_BACK,   KC_MS_LEFT,   KC_MS_DOWN,  KC_MS_RIGHT,  KC_MS_WH_UP, KC_MS_ACCEL1,
    __________,   M(NEW_TAB),  M(NEXT_WIN), M(CLOSE_WIN),   KC_MS_BTN2,KC_MS_WH_DOWN, KC_MS_ACCEL0,
                               M(PREV_TAB),  M(NEXT_TAB),   KC_MS_BTN3, M(CLOSE_TAB),        KC_F5,
        KC_PWR,   __________,
    __________,
       KC_PGUP,     KC_ENTER,   KC_MS_BTN1
  ),

/*
 * STANDARD - Scancodes sent at their (approximative) standard key spatial positions
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | EQUAL  | KC_1 | KC_2 | KC_3 | KC_4 | KC_5 |TO(0) |           | TO(0)| KC_6 | KC_7 | KC_8 | KC_9 | KC_0 |  MINUS |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  DEL   | KC_Q | KC_W | KC_E | KC_R | KC_T |TO(4) |           | TO(4)| KC_Y | KC_U | KC_I | KC_O | KC_P | BSLASH |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | TO(1)  | KC_A | KC_S | KC_D | KC_F | KC_G |------|           |------| KC_H | KC_J | KC_K | KC_L | SCLN |  QUOTE |
 * |--------+------+------+------+------+------|HYPER |           |  MEH |------+------+------+------+------+--------|
 * | LSHIFT | KC_Z | KC_X | KC_C | KC_V | KC_B |      |           |      | KC_N | KC_M | COMMA|  DOT | SLASH| RSHIFT |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | ESC  |GRAVE | LGUI | LALT |LCTRL |                                       | LEFT | RIGHT|LBRACK|RBRACK| RALT |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | APP  |  NO  |       |  NO  |INSERT|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | PGDN |       | PGUP |      |  DEL |
 *                                 |SPACE | TAB  |------|       |------| ENTER|      |
 *                                 |      |      | END  |       | HOME |      | BSPC |
 *                                 `--------------------'       `--------------------'
 */
  [_STANDARD] = KEYMAP(
      KC_EQUAL,         KC_1,         KC_2,         KC_3,         KC_4,         KC_5, TO(_COLEMAK),
     KC_DELETE,         KC_Q,         KC_W,         KC_E,         KC_R,         KC_T, TO(_NAVIGAT),
  MO(_SYMBOLS),         KC_A,         KC_S,         KC_D,         KC_F,         KC_G,
     KC_LSHIFT,         KC_Z,         KC_X,         KC_C,         KC_V,         KC_B, ALL_T(KC_NO),
     KC_ESCAPE,     KC_GRAVE,      KC_LGUI,      KC_LALT,     KC_LCTRL,
                                                                              KC_APP,   __________,
                                                                                         KC_PGDOWN,
                                                              KC_SPACE,       KC_TAB,       KC_END,

  TO(_COLEMAK),         KC_6,         KC_7,         KC_8,         KC_9,         KC_0,     KC_MINUS,
  TO(_NAVIGAT),         KC_Y,         KC_U,         KC_I,         KC_O,         KC_P,    KC_BSLASH,
                        KC_H,         KC_J,         KC_K,         KC_L,    KC_SCOLON,     KC_QUOTE,
  MEH_T(KC_NO),         KC_N,         KC_M,     KC_COMMA,       KC_DOT,     KC_SLASH,    KC_RSHIFT,
                                   KC_LEFT,     KC_RIGHT,   KC_LBRACKET, KC_RBRACKET,      KC_RALT,
    __________,    KC_INSERT,
       KC_PGUP,
       KC_HOME,     KC_ENTER,    KC_BSPACE
  ),


/*
 * MACROS - Macros keys (host-wise and keyboard-wise)
 *
 */
  [_MACROS] = KEYMAP(
    __________,   __________,   __________,   __________,   __________,   __________,   __________,
    __________,   __________,   __________,   __________,   __________,   __________, TO(_NAVIGAT),
    __________,   __________,   __________,     M(INFOS),  M(TOG_DAKP),  M(TOG_DAMR),
    __________,   __________,   __________,   __________,   __________,   __________,   __________,
    __________,   __________,   __________,   __________,   __________,
                                                                          __________,   __________,
                                                                                        __________,
                                                            __________,   __________,   __________,

    __________,   __________,   __________,   __________,   __________,   __________,   __________,
  TO(_NAVIGAT),   __________,   __________,   __________,   __________,   __________,   __________,
                  __________,   __________,   __________,   __________,   __________,   __________,
    __________,   __________,   __________,   __________,   __________,   __________,   __________,
                                __________,   __________,   __________,   __________,   __________,
    __________,   __________,
    __________,
    __________,   __________,   __________
  ),

  /*
  [LAYER] = KEYMAP(
    __________,   __________,   __________,   __________,   __________,   __________,   __________,
    __________,   __________,   __________,   __________,   __________,   __________,   __________,
    __________,   __________,   __________,   __________,   __________,   __________,
    __________,   __________,   __________,   __________,   __________,   __________,   __________,
    __________,   __________,   __________,   __________,   __________,
                                                                          __________,   __________,
                                                                                        __________,
                                                            __________,   __________,   __________,

    __________,   __________,   __________,   __________,   __________,   __________,   __________,
    __________,   __________,   __________,   __________,   __________,   __________,   __________,
                  __________,   __________,   __________,   __________,   __________,   __________,
    __________,   __________,   __________,   __________,   __________,   __________,   __________,
                                __________,   __________,   __________,   __________,   __________,
    __________,   __________,
    __________,
    __________,   __________,   __________
  ),
  */
};

/* COL-ROW (not spatial but QMK internal use) (in KEYMAP() k#COL#ROW)
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   0-0  | 0-1  | 0-2  | 0-3  | 0-4  | 0-5  | 0-6  |           |  0-7 |  0-8 |  0-9 |  0-A |  0-B |  0-C |   0-D  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   1-0  | 1-1  | 1-2  | 1-3  | 1-4  | 1-5  | 1-6  |           |  1-7 |  1-8 |  1-9 |  1-A |  1-B |  1-C |   1-D  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   2-0  | 2-1  | 2-2  | 2-3  | 2-4  | 2-5  |------|           |------|  2-8 |  2-9 |  2-A |  2-B |  2-C |   2-D  |
 * |--------+------+------+------+------+------| 3-6  |           |  3-7 |------+------+------+------+------+--------|
 * |   3-0  | 3-1  | 3-2  | 3-3  | 3-4  | 3-5  |      |           |      |  3-8 |  3-9 |  3-A |  3-B |  3-C |   3-D  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | 4-0  | 4-1  | 4-2  | 4-3  | 4-4  |                                       |  4-9 |  4-A |  4-B |  4-C |  4-D |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | 5-5  | 5-6  |       |  5-7 |  5-8 |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | 5-4  |       |  5-9 |      |      |
 *                                 | 5-3  | 5-2  |------|       |------|  5-B |  5-A |
 *                                 |      |      | 5-1  |       |  5-C |      |      |
 *                                 `--------------------'       `--------------------'
 */
#ifdef CUSTOM_MODIFIED_VALUES_ENABLE
bool keycodes_for_key(uint16_t default_kc, uint8_t layer, keypos_t key) {
  // RightAlt + BACKSPACE = DEL (No matter what key position or layer)
  if(default_kc == KC_BSPACE) return CMV(KC_BSPACE, 0, KC_DELETE, 0);

  switch(layer) {
  case _COLEMAK:
    switch(key.col) {
    case 1:
      if(key.row == 0xC) return CMV(default_kc, KC_COMMA, 0, 0);
      break;

    case 4:
      switch(key.row) {
        case 0xB: return CMV(default_kc, KC_RABK, 0, 0);
        case 0xC: return CMV(default_kc, KC_SLASH, 0, 0);
      }
      break;

    }
    break;

  case _SYMBOLS:
    if(key.col == 3 && key.row == 8) return CMV(default_kc, KC_COMMA, 0, 0);
    break;
  }
  return true;
}
#endif


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {

#ifdef CMV_COMPLETE_VERSION
      case TOG_DAKP:
        if(record->event.pressed) toggle_dakp();
        break;

      case TOG_DAMR:
# ifndef CMV_NO_DELAY_AFTER_MODIFIER_RELEASE
        if(record->event.pressed) toggle_damr();
# endif
        break;
#endif

      case INFOS:
        if(record->event.pressed) SEND_STRING("QMK: " QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION " from " QMK_BUILDDATE);
        break;

      case NEXT_WIN:
        if(record->event.pressed) shortcut_press(2, KC_LALT, KC_TAB);
        else shortcut_release(2, KC_TAB, KC_LALT);
        break;

      case NEW_TAB:
        if(record->event.pressed) shortcut_press(2, KC_LCTRL, KC_T);
        else shortcut_release(2, KC_T, KC_LCTRL);
        break;

      case CLOSE_TAB:
        if(record->event.pressed) shortcut_press(2, KC_LCTRL, KC_W);
        else shortcut_release(2, KC_W, KC_LCTRL);
        break;

      case CLOSE_WIN:
        if(record->event.pressed) shortcut_press(2, KC_LALT, KC_F4);
        else shortcut_release(2, KC_F4, KC_LALT);
        break;

      case NEXT_TAB:
        if(record->event.pressed) shortcut_press(2, KC_LCTRL, KC_PGDOWN);
        else shortcut_release(2, KC_PGDOWN, KC_LCTRL);
        break;

      case PREV_TAB:
        if(record->event.pressed) shortcut_press(2, KC_LCTRL, KC_PGUP);
        else shortcut_release(2, KC_PGUP, KC_LCTRL);
        break;

      }
    return MACRO_NONE;
};


uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 0:
      break;
      case 1:
        ergodox_right_led_3_on();
        break;
      case 2:
        ergodox_right_led_2_on();
        break;
      case 3:
        ergodox_right_led_3_on();
        ergodox_right_led_2_on();
        break;
      case 4:
        ergodox_right_led_1_on();
        break;
      case 5:
        ergodox_right_led_3_on();
        ergodox_right_led_1_on();
        break;
      case 6:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      default:
        break;
    }

    return state;
};
