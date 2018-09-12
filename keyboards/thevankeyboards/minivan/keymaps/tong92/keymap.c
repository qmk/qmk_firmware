//Author: tong92 <tong92power@gmail.com>
#include QMK_KEYBOARD_H

#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif

extern keymap_config_t keymap_config;

enum tv44_layers {
  _WINDOW,
  _MAC,
  _LOWER,
  _RAISE,
  _WINDOW_SHORTCUT,
  _MAC_SHORTCUT,
  _MOUSE
};

enum tv44_keycodes {
  WINDOW = SAFE_RANGE,
  MAC,
  MOUSE,
  BACKLIT,
  EXT_MOUSE
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define LOWER F(_LOWER)
#define RAISE F(_RAISE)
#define XXXXXXX KC_NO
#define WINDOW_SHORTCUT MO(_WINDOW_SHORTCUT)
#define MAC_SHORTCUT MO(_MAC_SHORTCUT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Window - Qwerty
 * ,--------------------------------------------------------------------------.
 * | Tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  Bksp |
 * |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
 * | Ctrl  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  | Enter|
 * |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
 * | Shift  |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  | /   |Shift|
 * |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
 * | Ft   |  GUI  | Alt  | Space/LOWER | Space/RAISE |  '   |  [  |  ]  | Alt |
 * `--------------------------------------------------------------------------'
 */
[_WINDOW] = LAYOUT_arrow(
KC_TAB, KC_Q,   KC_W,   KC_E, KC_R,   KC_T,   KC_Y,   KC_U, KC_I,   KC_O,   KC_P,   KC_BSPC,
KC_LCTL,KC_A,   KC_S,   KC_D, KC_F,   KC_G,   KC_H,   KC_J, KC_K,   KC_L,   KC_SCLN,KC_ENT,
KC_LSFT,KC_Z,   KC_X,   KC_C, KC_V,   KC_B,   KC_N,   KC_M, KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
WINDOW_SHORTCUT,    KC_LGUI,KC_LALT,              LOWER,  RAISE,        KC_QUOT,KC_LBRC,KC_RBRC,KC_RALT
),
/* Mac - Qwerty
 * ,--------------------------------------------------------------------------.
 * | Tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  Bksp |
 * |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
 * | Cmd   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  | Enter|
 * |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
 * | Shift  |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  | /   |Shift|
 * |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
 * | Ft   |  Alt | Ctrl  | Space/LOWER | Space/RAISE |  '   |  [  |  ]  | Alt |
 * `--------------------------------------------------------------------------'
 */
[_MAC] = LAYOUT_arrow(
KC_TAB, KC_Q,   KC_W,   KC_E, KC_R,   KC_T,   KC_Y,   KC_U, KC_I,   KC_O,   KC_P,   KC_BSPC,
KC_LGUI,KC_A,   KC_S,   KC_D, KC_F,   KC_G,   KC_H,   KC_J, KC_K,   KC_L,   KC_SCLN,KC_ENT,
KC_LSFT,KC_Z,   KC_X,   KC_C, KC_V,   KC_B,   KC_N,   KC_M, KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
MAC_SHORTCUT,    KC_LALT, KC_LCTRL,              LOWER,  RAISE,        KC_QUOT,KC_LBRC,KC_RBRC,KC_RALT
),
/* LOWER
 * ,--------------------------------------------------------------------------.
 * |  `   |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |       |
 * |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
 * |       |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  -  |  +  |  [  |  ]  |   \  |
 * |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
 * |        |  F7 |  F8 |  F9 | F10 | F11 | F12 |     | HOME| PgUp|  UP | PgDo|
 * |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
 * |      |       |      |             |             |  END | LEFT| Down|RIGHT|
 * `--------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_arrow(
KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   _______,
_______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_MINS,KC_PLUS,KC_LBRC,KC_RBRC,KC_BSLS,
_______,KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, XXXXXXX,KC_HOME,KC_PGUP,KC_UP  ,KC_PGDN,
XXXXXXX,_______,_______,                _______,XXXXXXX,        KC_END, KC_LEFT,KC_DOWN,KC_RIGHT
),
/* RAISE
 * ,--------------------------------------------------------------------------.
 * |  ~   |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |       |
 * |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
 * |       |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  _  |  =  |  {  |  }  |   |  |
 * |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
 * |        |  F7 |  F8 |  F9 | F10 | F11 | F12 |     | HOME| PgUp|  UP | PgDo|
 * |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
 * |      |       |      |             |             |  END | LEFT| Down|RIGHT|
 * `--------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_arrow(
KC_TILD,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,_______,
_______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_UNDS,KC_EQL, KC_LCBR,KC_RCBR,KC_PIPE,
_______,KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,KC_HOME,KC_PGUP,KC_UP  ,KC_PGDN,
XXXXXXX,_______,_______,                _______,_______,        KC_END, KC_LEFT,KC_DOWN,KC_RIGHT
),
/* Window Shortcut
 * ,--------------------------------------------------------------------------.
 * |  ESC |WinOf|WinUp|     |     |Sh+Ca|     | PgUp| UP  | PgDo|PrtSc| DELET |
 * |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
 * |       |WinLe|WinDo|WinRi|     |Al+Ca|CapsL| LEFT| DOWN|RIGHT|     |      |
 * |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
 * |        |WinLW|WinRW|     |     |Ct+Ca|ScroL| HOME|     | END |     | Ctrl|
 * |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
 * |      | DeskL | DeskR| Task Manager|    DeskX    | MOUSE|     |     | LED |
 * `--------------------------------------------------------------------------'
 */
[_WINDOW_SHORTCUT] = LAYOUT_arrow(
KC_ESC ,LALT(KC_F4)        ,LGUI(KC_UP)         ,XXXXXXX       ,XXXXXXX,S(KC_CAPS)         ,XXXXXXX          ,KC_PGUP,KC_UP  ,KC_PGDN ,KC_PSCR,KC_DELT,
_______,LGUI(KC_LEFT)      ,LGUI(KC_DOWN)       ,LGUI(KC_RIGHT),XXXXXXX,LALT(KC_CAPS)      ,KC_CAPS          ,KC_LEFT,KC_DOWN,KC_RIGHT,XXXXXXX,XXXXXXX,
_______,LGUI(LSFT(KC_LEFT)),LGUI(LSFT(KC_RIGHT)),XXXXXXX       ,XXXXXXX,LCTL(KC_CAPS)      ,KC_SLCK          ,KC_HOME,XXXXXXX,KC_END  ,XXXXXXX,KC_RCTL,
_______,LGUI(LCTL(KC_LEFT)),LGUI(LCTL(KC_RIGHT)),                       LCTL(LALT(KC_DELT)),LGUI(LCTL(KC_F4)),        MOUSE  ,XXXXXXX ,XXXXXXX,BACKLIT
),
/* Mac Shortcut
 * ,--------------------------------------------------------------------------.
 * |  ESC |CmdUp|CmdDo|     |     |     |     | PgUp| UP  | PgDo|PrtSc| DELET |
 * |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
 * |       |WBlkL|WBlkR|     |ScrFu|     |CapsL| LEFT| DOWN|RIGHT|     |      |
 * |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
 * |        |BlckL|BlckR|     |     |     |     | HOME|     | END |     | Ctrl|
 * |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
 * |      |       |      |             |             | MOUSE|     |     | LED |
 * `--------------------------------------------------------------------------'
 */
[_MAC_SHORTCUT] = LAYOUT_arrow(
KC_ESC ,LGUI(KC_UP)        ,LGUI(KC_DOWN)         ,XXXXXXX       ,XXXXXXX,XXXXXXX         ,XXXXXXX          ,KC_PGUP,KC_UP  ,KC_PGDN ,KC_PSCR,KC_DELT,
_______,LALT(LSFT(KC_LEFT))      ,LALT(LSFT(KC_RIGHT))       ,XXXXXXX,LGUI(LCTL(KC_F)),XXXXXXX      ,KC_CAPS          ,KC_LEFT,KC_DOWN,KC_RIGHT,XXXXXXX,XXXXXXX,
_______,LGUI(LSFT(KC_LEFT)),LGUI(LSFT(KC_RIGHT)),XXXXXXX       ,XXXXXXX,XXXXXXX     ,XXXXXXX          ,KC_HOME,XXXXXXX,KC_END  ,XXXXXXX,KC_RCTL,
_______,_______,_______, _______,_______,        MOUSE  ,XXXXXXX ,XXXXXXX,BACKLIT
),
/* MOUSE
 * ,--------------------------------------------------------------------------.
 * |      |     |     |Mo_Up|     |     |     |M_WhL|M_WhU|M_WhR|     | RESET |
 * |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
 * |       |     |Mo_Le|Mo_Do|Mo_Ri|     |     |M_Bt1|M_WhD|M_Bt2|     |      |
 * |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
 * |        |     |     |     |     |     |     |M_AC0|M_AC1|M_AC2|     |WINDO|
 * |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
 * |      |      |      | GO_DEFAULT  |  GO_DEFAULT |       |     |     | MAC |
 * `--------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_arrow(
XXXXXXX,XXXXXXX,XXXXXXX,KC_MS_U,XXXXXXX,XXXXXXX,XXXXXXX,KC_WH_L,KC_WH_U,KC_WH_R,XXXXXXX,RESET,
XXXXXXX,XXXXXXX,KC_MS_L,KC_MS_D,KC_MS_R,XXXXXXX,XXXXXXX,KC_BTN1,KC_WH_D,KC_BTN2,XXXXXXX,XXXXXXX,
XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_ACL0,KC_ACL1,KC_ACL2,XXXXXXX,WINDOW,
XXXXXXX,XXXXXXX,XXXXXXX,                EXT_MOUSE,EXT_MOUSE,        XXXXXXX,XXXXXXX,XXXXXXX,MAC
)
};

const uint16_t PROGMEM fn_actions[] = {
 [_LOWER] = ACTION_LAYER_TAP_KEY(_LOWER, KC_SPC),
 [_RAISE] = ACTION_LAYER_TAP_KEY(_RAISE, KC_SPC)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case WINDOW:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WINDOW);
      }
      return false;
      break;
    case MAC:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_MAC);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      }
      return false;
      break;
    case MOUSE:
      if (record->event.pressed) {
        layer_on(_MOUSE);
      }
      return false;
      break;
    case EXT_MOUSE:
      if (record->event.pressed) {
        layer_off(_MOUSE);
        layer_off(_WINDOW_SHORTCUT);
        layer_off(_MAC_SHORTCUT);
      }
      return false;
      break;
  }
  return true;
};

