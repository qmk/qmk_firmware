/* Copyright 2019 Takuya Urakawa (dm9records.com)
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


enum plaid_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum plaid_keycodes {
  QWERTY = SAFE_RANGE,
  LED_1,
  LED_2,
  LED_3,
  LED_4,
  LED_5,
  LED_6,
  LED_7,
  LED_8,
  LED_9,
  LED_0
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// array of keys considered modifiers for led purposes
const uint16_t modifiers[] = {
    KC_LCTL,
    KC_RCTL,
    KC_LALT,
    KC_RALT,
    KC_LSFT,
    KC_RSFT,
    KC_LGUI,
    KC_RGUI,
    LOWER,
    RAISE
};

//Setup consts for LED modes
#define LEDMODE_ON 1 //always on
#define LEDMODE_OFF 0 //always off
#define LEDMODE_MODS 2 //On with modifiers
#define LEDMODE_BLINKIN 3 //blinkinlights - % chance toggle on keypress
#define LEDMODE_KEY 4 //On with any keypress, off with key release
#define LEDMODE_ENTER 5 // On with enter key

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Esc/hy|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  fn  | Alt  | GUI  |Lower |    Space    |Raise | GUI  | Alt  |Shift | Ctrl |
 * `-----------------------------------------------------------------------------------'
 *  (karabiner remaps Caps lock -> fn)
 */
[_QWERTY] = LAYOUT_plaid_grid(
    KC_TAB        , KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    HYPR_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_RSFT       , KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    KC_RCTL       , KC_CAPS, KC_RALT, KC_RGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_RGUI, KC_RALT, KC_RSFT, KC_RCTL
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  | F10  | F11  | F12  |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      | Prev | Vol- | Play |
 * `-----------------------------------------------------------------------------------'
 * volume up key repeats randomly on mac, have to use mac specific volume
 */
[_LOWER] = LAYOUT_plaid_grid(
    KC_GRV , KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0       , KC_BSPC,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC    , KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______    , _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC__VOLDOWN, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |      |      | End  |      |      |      |Pg Up |      |      |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Home |      |Pg Dn |      |      | Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      | Copy |Paste |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      | Next | Vol+ | Mute |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_plaid_grid(
    KC_TILD, _______, _______, KC_END, _______, _______, _______,  KC_PGUP, _______, _______, _______  , KC_DEL , 
    _______, KC_HOME, _______, KC_PGDN, _______, _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______  , _______, 
    _______, _______, _______, KC_COPY, KC_PSTE, KC_PGDN, _______, _______, _______, _______, _______  , _______,  
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC__VOLUP, KC_MUTE
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Reset | Red  |Green | Rmod | Gmod |Rblink|Gblink| Rkey | Gkey | Rcar | Gcar |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |Power |Sleep |Wake  |Eject |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_plaid_grid(
    QK_BOOT, LED_1  , LED_2  ,  LED_3  , LED_4  , LED_5  ,LED_6   , LED_7  , LED_8  , LED_9  , LED_0  , _______ ,
    _______, KC_PWR , KC_SLEP,  KC_WAKE, KC_EJCT, _______, _______, _______, _______, _______, _______, _______ ,
    _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
    _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______
)


};

//Setup config struct for LED
typedef union {
  uint32_t raw;
  struct {
    uint8_t  red_mode :8;
    uint8_t  green_mode :8;
  };
} led_config_t;
led_config_t led_config;

//Set leds to saved state during powerup
void keyboard_post_init_user(void) {
  // set LED pin modes
  setPinOutput(LED_RED);
  setPinOutput(LED_GREEN);

  // Call the post init code.
  led_config.raw = eeconfig_read_user();

  if(led_config.red_mode == LEDMODE_ON) {
      writePinHigh(LED_RED);
  }

  if(led_config.green_mode == LEDMODE_ON) {
      writePinHigh(LED_GREEN);
  }
}

void eeconfig_init_user(void) {  // EEPROM is getting reset! 
  led_config.raw = 0;
  led_config.red_mode = LEDMODE_ON;
  led_config.green_mode = LEDMODE_MODS;
  eeconfig_update_user(led_config.raw);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void led_keypress_update(uint8_t led, uint8_t led_mode, uint16_t keycode, keyrecord_t *record) {
    switch (led_mode) {
      case LEDMODE_MODS:
        for (int i=0;i<sizeof(modifiers) / sizeof(modifiers[0]);i++) {
          if(keycode==modifiers[i]) {
            if (record->event.pressed) {
              writePinHigh(led);
            }
            else {
              writePinLow(led);
            }
          }
        }
        break;
      case LEDMODE_BLINKIN:
        if (record->event.pressed) {

          /* Markov Chain
           *
           *   1 - x           1 - y
           *   /---\           /---\
           *   v   |           v   |
           *  /------\   x   /------\
           *  |      |------>|      |
           *  |  on  |   y   | off  |
           *  |      |<------|      |
           *  \------/       \------/
          */

          /* Non-homogeneous Markov Chain
           *
           * /-----\ 1 - x0 /-----\ 1 - x1 /-----\  
           * |on  0|------->|on  1|------->|on  2|----> ...  
           * \-----/\      /\-----/\      /\-----/\
           *         \    /         \    /         .
           *        x0\  /         x1\  /           .
           *           \/             \/             .
           *           /\             /\              
           *        y0/  \         y1/  \            .
           *         /    \         /    \          .
           *        /      \       /      \        .
           * /-----\ 1 - y0 /-----\ 1 - y1 /-----\/  
           * |off 0|------->|off 1|------->|off 2|----> ...
           * \-----/        \-----/        \-----/  
           *
           *
           * if x = 1/4 and y 1/4, behavior is equivalent to the original code
           * and converges to a steady state at the rate of 1/2^k
           * where k is the number of key presses
           * (the distance from a given vector to the steady state, [1/2, 1/2], 
           * is cut in half every key press)
           *
           * if x = y, then it is guaranteed that the steady state is still
           * [1/2, 1/2], but the rate at which it converges is variable 
           *
           * if x != y, then there is no well-defined steady state
          */

          double x = (1.0*rand())/RAND_MAX;
          double y = x;

          double p = (readPin(led)) ? x : y;
          if (rand() < p*RAND_MAX) {
            togglePin(led);
          }

          /* following code is restriced to x + y <= 1
           * if(rand() % 2 == 1) { */
          /*   if(rand() % 2 == 0) { */
          /*     writePinLow(led); */
          /*   } */
          /*   else { */
          /*     writePinHigh(led); */
          /*   } */
          /* } */
        }
        break;
      case LEDMODE_KEY:
        if (record->event.pressed) {
          writePinHigh(led);
          return;
        }
        else {
          writePinLow(led);
          return;
        }
        break;
      case LEDMODE_ENTER:
        if (keycode==KC_ENT) {
          writePinHigh(led);
        }
        else {
          writePinLow(led);
        }
        break;

    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  /* If the either led mode is keypressed based, call the led updater
     then let it fall through the keypress handlers. Just to keep 
     the logic out of this procedure */
  if (led_config.red_mode >= LEDMODE_MODS && led_config.red_mode <= LEDMODE_ENTER) {
      led_keypress_update(LED_RED, led_config.red_mode, keycode, record);
  }
  if (led_config.green_mode >= LEDMODE_MODS && led_config.green_mode <= LEDMODE_ENTER) {
      led_keypress_update(LED_GREEN, led_config.green_mode, keycode, record);
  }
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LED_1:
      if (record->event.pressed) {
        if (led_config.red_mode==LEDMODE_ON) {
            led_config.red_mode=LEDMODE_OFF;
            writePinLow(LED_RED);
        }
        else {
            led_config.red_mode=LEDMODE_ON;
            writePinHigh(LED_RED);
        }
      }
      break;
    case LED_2:
      if (record->event.pressed) {
        if (led_config.green_mode==LEDMODE_ON) {
            led_config.green_mode=LEDMODE_OFF;
            writePinLow(LED_GREEN);
        }
        else {
            led_config.green_mode=LEDMODE_ON;
            writePinHigh(LED_GREEN);
        }
      }
      break;
    case LED_3:
      led_config.red_mode=LEDMODE_MODS;
      break;
    case LED_4:
      led_config.green_mode=LEDMODE_MODS;
      break;
    case LED_5:
      led_config.red_mode=LEDMODE_BLINKIN;
      break;
    case LED_6:
      led_config.green_mode=LEDMODE_BLINKIN;
      break;
    case LED_7:
      led_config.red_mode=LEDMODE_KEY;
      break;
    case LED_8:
      led_config.green_mode=LEDMODE_KEY;
      break;
    case LED_9:
      led_config.red_mode=LEDMODE_ENTER;
      break;
    case LED_0:
      led_config.green_mode=LEDMODE_ENTER;
      break;
  }

  if (keycode >= LED_1 && keycode <= LED_0) {
    eeconfig_update_user(led_config.raw);
  }

  return true;
}
