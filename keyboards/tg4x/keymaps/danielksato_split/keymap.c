/* Copyright 2018 u/mythosmann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#define _BL 0
#define _GL 1
#define _FL 2
#define _OL 3
#define _NL 4
#define _UL 5
#define KC_X0 RGB_TOG
#define KC_X1 RGB_MOD
// Defines the keycodes used by macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};
//Tap Dance Declarations
enum {
  TD_1 = 9,
  TD_2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// ,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
// |  Esc  |   q   |   w   |   e   |   r   |   t   |   y   |   u   |   i   |   o   |   p   |   '   | Bspc  |
// |-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-------|
// |  Tab   |   a   |   s   |   d   |   f   |   g   |   h   |   j   |   k   |   l   |   ;   |    Enter    |
// |---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----------|
// |  Shift     |   z   |   x   |   c   |   v   |   b   |   n   |   m   |   ,   |   .   |   /   |   Shift  |
// |---------,--'------,'-------',------'-------'-------'-------'-------',------'--,----'--,----'--,-------|
// |   Ctl   |   Win   |   Alt   |   Fn                 |   Spc          | Ralt    | Rwin  |  FN   | RCtl  |
// `---------'---------'---------'----------------------'----------------'---------'-------'-------'-------'
  [_BL] = LAYOUT_SPLIT_ANSI( /* Base */
//,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
   KC_ESC , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  , KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_GRV,KC_BSPC, \
//|-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-------------|
   KC_TAB, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  , KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT, \
//|---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'-----,-'-------------|
    KC_RSFT    , KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  , KC_N  , KC_M  ,KC_COMM, KC_DOT,KC_SLSH,  KC_RSFT , \
//|---------,--'------,'-------',------'-------'-------',------'-------',------'--,----'--,----'--,-------|
     KC_LCTL, KC_LGUI , KC_LALT ,   MO(_FL)      ,  KC_SPC       , MO(_OL), KC_RALT ,MO(_FL),KC_RCTL   \
//`---------'---------'---------'-----------------------'---------------'---------'-------'-------'-------'
),
// ,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
// |  Esc  |   q   |   w   |   e   |   r   |   t   |   y   |   u   |   i   |   o   |   p   |   '   | Bspc  |
// |-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-------|
// |  Tab   |   a   |   s   |   d   |   f   |   g   |   h   |   j   |   k   |   l   |   ;   |    Enter    |
// |---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----------|
// |  Shift     |   z   |   x   |   c   |   v   |   b   |   n   |   m   |   ,   |   .   |   /   |   Shift  |
// |---------,--'------,'-------',------'-------'-------'-------'-------',------'--,----'--,----'--,-------|
// |   Ctl   |   Win   |   Alt   |   Fn                 |   Spc          | Ralt    | Rwin  |  FN   | RCtl  |
// `---------'---------'---------'----------------------'----------------'---------'-------'-------'-------'
  [_GL] = LAYOUT_SPLIT_ANSI( /* Game */
//,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
   KC_ESC , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  , KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_DEL,KC_BSPC, \
//|-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-------------|
   KC_TAB   , KC_A  , KC_S  , KC_D  , KC_F  , KC_G  , KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,    KC_ENT   , \
//|---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'-----,-'-------------|
    KC_LSFT    , KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  , KC_N  , KC_M  ,KC_COMM, KC_DOT,KC_SLSH, TG(_GL)  , \
//|---------,--'------,'-------',------'-------'-------',------'-------',------'--,----'--,----'--,-------|
     KC_LCTL, KC_LGUI , KC_LALT ,   KC_SPC              ,  MO(_FL)       , KC_RALT ,KC_RGUI,KC_MENU,KC_RCTL   \
//`---------'---------'---------'-----------------------'---------------'---------'-------'-------'-------'
),
// ,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
// |   `   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   -   |  Del  |
// |-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-------|
// |  Caps   | Home  | PgUp  |       |       |       |       |   [   |   ]   |   =   |   \   |    Enter    |
// |---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----------|
// |  Shift     |  End  | PgDn  |       |       |       |       |       |       |       |  Up   |   Shift  |
// |---------,--'------,'-------',------'-------'-------'-------'-------'-------',------'--,----'--,-------|
// |   Ctl   |   Win   |   Alt   |   Fn                 |   Spc          | Ralt    |  Left | Down  | Right |
// `---------'---------'---------'-----------------------------------------------'---------'-------'-------'
  [_FL] = LAYOUT_SPLIT_ANSI( /* Function */
//,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
   KC_GRV , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  , KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_LBRC,KC_RBRC, \
//|-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-------------|
   MO(_NL)  ,KC_HOME,KC_PGUP,KC_TRNS,KC_TRNS,KC_TRNS,KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,KC_QUOT,    KC_ENT   , \
//|---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----------|
    KC_TRNS    ,KC_END ,KC_PGDN,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_MINUS,KC_EQL,KC_BSLS, KC_RSFT  , \
//|---------,--'------,'-------',------'-------'-------',------'-------',------'--,----'--,----'--,-------|
    KC_TRNS , KC_TRNS , KC_TRNS ,      KC_TRNS          ,  KC_TRNS      ,KC_TRNS  ,KC_LEFT,KC_DOWN,KC_RGHT  \
//`---------'---------'---------'-----------------------'---------------'---------'-------'-------'-------'
),
  [_NL] = LAYOUT_SPLIT_ANSI( /* Nav */
//,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
   KC_GRV , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  , KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_GRV,KC_DEL , \
//|-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-------------|
   KC_TRNS  ,KC_HOME,KC_PGUP,KC_TRNS,KC_TRNS,KC_TRNS,KC_HOME,KC_PGDOWN,KC_PGUP,KC_END,KC_QUOT,    KC_ENT   , \
//|---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----------|
    KC_TRNS    ,KC_END ,KC_PGDN,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_BSLS,KC_UP, KC_RSFT  , \
//|---------,--'------,'-------',------'-------'-------',------'-------',------'--,----'--,----'--,-------|
    KC_TRNS , KC_TRNS , KC_TRNS ,      KC_TRNS          ,  KC_TRNS      ,KC_TRNS  ,KC_LEFT,KC_DOWN,KC_RGHT  \
//`---------'---------'---------'-----------------------'---------------'---------'-------'-------'-------'
),
// ,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
// |   `   |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |  F7   |  F8   |  F9   |  F10  |  F11  |  F12  |
// |-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-------|
// |  RGB    |       |       |       |       |       |       |       |       |       |       |    Enter    |
// |---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----------|
// |            |       |       |       |       |       |       |       |       |       |  Up   |          |
// |---------,--'------,'-------',------'-------'-------'-------'-------'-------',------'--,----'--,-------|
// |         |         |         |   Spc                                         |  Left   | Down  | Right |
// `---------'---------'---------'-----------------------------------------------'---------'-------'-------'
  [_OL] = LAYOUT_SPLIT_ANSI( /* Other Function */
//,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
   KC_GRV , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,KC_F12 , \
//|-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-------------|
   RGB_TOG  ,KC_VOLU,KC_MPRV,KC_MPLY,KC_MNXT,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,    KC_ENT   , \
//|---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----------|
    MO(_UL)    ,KC_VOLD,KC_MUTE,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_UP, RESET      , \
//|---------,--'------,'-------',------'-------'-------',------'-------',------'--,----'--,----'--,-------|
    KC_TRNS , KC_TRNS , KC_TRNS ,      KC_TRNS          ,  MO(_GL)      ,KC_TRNS  ,KC_LEFT,KC_DOWN,KC_RGHT  \
//`---------'---------'---------'-----------------------'---------------'---------'-------'-------'-------'
),
  [_UL] = LAYOUT_SPLIT_ANSI( /* Update */
//,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
   KC_GRV , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 , RESET , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,KC_F12 , \
//|-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-------------|
   RGB_TOG  ,KC_VOLU,KC_MPRV,KC_MPLY,KC_MNXT,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,    KC_ENT   , \
//|---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----------|
    KC_TRNS    ,KC_VOLD,KC_MUTE,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_UP, RESET      , \
//|---------,--'------,'-------',------'-------'-------',------'-------',------'--,----'--,----'--,-------|
    KC_TRNS , KC_TRNS , KC_TRNS ,      KC_TRNS          ,  KC_TRNS      ,KC_TRNS  ,KC_LEFT,KC_DOWN,KC_RGHT  \
//`---------'---------'---------'-----------------------'---------------'---------'-------'-------'-------'
),
};

/*
Tap dance stuff.
td_1 is tab when hit, but caps lock when double tapped.
td_2 is alt when hit, but windows key when double tapped
*/
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_1]  = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_CAPS),
  [TD_2]  = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LGUI)
// Other declarations would go here, separated by commas,
};

/*
Custom Macro stuff
These are just the example macros used by qmk.
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
      } else {
        // when keycode QMKURL is released
      }
      break;
  }
  return true;
}

void update_led(void) {
  if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { //if caps lock is on
    rgblight_sethsv_at(0,255,255, 0); //turns the first led red
    switch (biton32(layer_state)) {
      case _BL: //when the base layer is active, turns the LEDs yellow
        rgblight_sethsv_range(140,175,175,1,7);
        break;
      case _FL: //when the function layer is active, turns the LEDs cyan
        rgblight_sethsv_range(0,255,125,1,7);
        break;
      case _OL:
        rgblight_sethsv_range(255,20,240,1,7);
        break;
      case _GL:
        rgblight_sethsv_range(35,255,255,1,7);
        break;
      default: //if anything else is active, turns the LEDs off. isn't in use, mostly a fallback
        rgblight_sethsv(0,0,0);
        break;
    }
  } else { //if caps lock isn't on
      rgblight_sethsv_at(0,0,0, 0);
      switch (biton32(layer_state)) { //same code as above
        case _BL:
          rgblight_sethsv_range(140,175,175,1,7);
          break;
        case _FL:
          rgblight_sethsv_range(0,255,125,1,7);
          break;
        case _OL:
          rgblight_sethsv_range(255,20,240,1,7);
          break;
        case _GL:
          rgblight_sethsv_range(35,255,255,1,7);
          break;
        default:
          rgblight_sethsv(0,0,0);
          break;
        }
    }
  }

void led_set_user(uint8_t usb_led) {
  update_led();
}

uint32_t layer_state_set_user(uint32_t state) {
  update_led();
  return state;
}
