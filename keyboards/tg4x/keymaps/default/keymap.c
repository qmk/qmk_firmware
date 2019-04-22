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
#define _FL 1
#define _ADJUST 2
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
/*
,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
|  Esc  |   q   |   w   |   e   |   r   |   t   |   y   |   u   |   i   |   o   |   p   |   '   | Bspc  |
|-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-------|
|  Tab   |   a   |   s   |   d   |   f   |   g   |   h   |   j   |   k   |   l   |   ;   |    Enter    |
|---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----------|
|  Shift     |   z   |   x   |   c   |   v   |   b   |   n   |   m   |   ,   |   .   |   /   |   Shift  |
|-------,----'--,----'--,----'-------'-------'-------'-------'-------'--,----'--,----'--,----'--,-------|
|  Ctl  |  Alt  |  Fn   |                                               |  Fn   | Left  |  Up   | Right |
`-------'-------'-------'-----------------------------------------------'-------'-------'-------'-------'*/
  [_BL] = LAYOUT( /* Base */
//,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
   KC_ESC , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  , KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_SCLN,KC_BSPC, \
//|-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-------------|
   TD(TD_1)  , KC_A  , KC_S  , KC_D  , KC_F  , KC_G  , KC_H  , KC_J  , KC_K  , KC_L  ,KC_QUOT,    KC_ENT  , \
//|---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'-----,-'-------------|
    KC_LSFT    , KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  , KC_N  , KC_M  ,KC_COMM, KC_DOT,KC_SLSH, KC_RSFT  , \
//|-------,----'--,----'--,----'-------'-------'-------'-------'-------'--,----'--,----'--,----'--,-------|
   KC_LCTL,TD(TD_2),MO(_FL),        KC_SPC                                ,TG(_FL),KC_LEFT, KC_UP ,KC_RGHT   \
//`-------'-------'-------'-----------------------------------------------'-------'-------'-------'-------'
),

/*
,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
|   `   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   -   |  Del  |
|-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-------|
|  Caps   | Home  | PgUp  |       |       | MsUp  |       |   [   |   ]   |   =   |   \   |    Enter    |
|---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----------|
|  Shift     |  End  | PgDn  |  MsL  | MsDn  |  MsR  |       |       |       |       |       |   Shift  |
|-------,----'--,----'--,----'-------'-------'-------'-------'-------'--,----'--,----'--,----'--,-------|
|  Ctl  |  Alt  |  Win  |                                               |  Fn   | Left  | Down  | Right |
`-------'-------'-------'-----------------------------------------------'-------'-------'-------'-------'*/
  [_FL] = LAYOUT( /* Function */
//,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
   KC_GRV , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  , KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_MINS,KC_DEL , \
//|-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-------------|
   RGB_TOG  ,KC_HOME,KC_PGUP,KC_TRNS,KC_F5,KC_TRNS,KC_TRNS,KC_LBRC,KC_RBRC,KC_EQL ,KC_BSLS,    KC_ENT   , \
//|---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----------|
    KC_TRNS    ,KC_END ,KC_PGDN,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_UP, KC_RSFT  , \
//|-------,----'--,----'--,----'-------'-------'-------'-------'-------'--,----'--,----'--,----'--,-------|
   KC_TRNS,KC_TRNS,KC_TRNS,         KC_SPC                                ,KC_TRNS,KC_LEFT,KC_DOWN,KC_RGHT  \
//`-------'-------'-------'-----------------------------------------------'-------'-------'-------'-------'
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
  if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
    //if caps lock is on
    rgblight_sethsv_at(0,255,255, 0);
    //turns the first led green
    switch (biton32(layer_state)) {
      case _BL:
      //when the base layer is active, turns the LEDs teal
        rgblight_sethsv_range(50,190,125,1,7);
        break;
      case _FL:
      //when the function layer is active, turns the LEDs purple
        rgblight_sethsv_range(205,150,240,1,7);
        break;
      default:
      //if anything else is active, turns the LEDs off. isn't in use, mostly a fallback
        rgblight_sethsv(0,0,0);
        break;
    }
  } else {
    //if caps lock isn't on
        rgblight_sethsv_at(0,0,0, 0);
        switch (biton32(layer_state)) {
          //same code as above
          case _BL:
            rgblight_sethsv_range(50,190,125,1,7);
            break;
          case _FL:
            rgblight_sethsv_range(205,150,240,1,7);
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
