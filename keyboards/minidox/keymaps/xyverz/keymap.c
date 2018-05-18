#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DVORAK 0
#define _QWERTY 1
#define _COLEMAK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum planck_keycodes {
  DVORAK = SAFE_RANGE,
  QWERTY,
  COLEMAK,
  LOWER,
  RAISE,
  BACKLIT
};

// Adding macros to make the keymaps below much easier to read.
#define SFTSCLN SFT_T(KC_SCLN)
#define SFTSLSH SFT_T(KC_SLSH)
#define SFTZED SFT_T(KC_Z)
//#define ALTENT ALT_T(KC_ENT)
//#define ESCTRL CTL_T(KC_ESC)
//#define TABGUI GUI_T(KC_TAB)
#define CTRLQ CTL_T(KC_Q)
#define CTRLV CTL_T(KC_V)
#define ALTJ ALT_T(KC_J)
#define ALTW ALT_T(KC_W)
#define CTRLX CTL_T(KC_X)
#define CTRLDOT CTL_T(KC_DOT)
#define ALTC ALT_T(KC_C)
#define ALTCOMM ALT_T(KC_COMM)
//#define GUIBSPC GUI_T(KC_BSPC)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Dvorak
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   '  |   ,  |   .  |   P  |   Y  |           |   F  |   G  |   C  |   R  |   L  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   O  |   E  |   U  |   I  |           |   D  |   H  |   T  |   N  |   S  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |SFT/ ;|CTL/ Q|ALT/ J|   K  |   X  |           |   B  |   M  |ALT/ W|CTL/ V|SFT/ Z|
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  | LOWER| Gui  |      |    |      | Ent  |RAISE |
 *                  `-------------| BSpc |    | Spc  |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_DVORAK] = LAYOUT ( \
  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,       KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    \
  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,       KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    \
  SFTSCLN, CTRLQ,   ALTJ,    KC_K,    KC_X,       KC_B,    KC_M,    ALTW,    CTRLV,   SFTZED,  \
                    LOWER,   KC_LGUI, KC_BSPC,    KC_SPC,  KC_ENT,  RAISE                      \
),

/* Qwerty
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |SFT/ Z|CTL/ X|ALT/ C|   V  |   B  |           |   N  |   M  |ALT/ ,|CTL/ .|SFT/ /|
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  | LOWER| Gui  |      |    |      | Ent  |RAISE |
 *                  `-------------| BSpc |    | Spc  |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_QWERTY] = LAYOUT ( \
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, \
  SFTZED,  CTRLX,   ALTC,    KC_V,    KC_B,       KC_N,    KC_M,    ALTCOMM, CTRLDOT, SFTSLSH, \
                    LOWER,   KC_LGUI, KC_BSPC,    KC_SPC,  KC_ENT,  RAISE                      \
),

/* Colemak
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   F  |   P  |   G  |           |   J  |   L  |   U  |   Y  |   L  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   R  |   S  |   T  |   D  |           |   H  |   N  |   E  |   I  |   S  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |SFT/ Z|CTL/ X|ALT/ C|   V  |   B  |           |   K  |   M  |ALT/ ,|CTL/ .|SFT/ /|
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  | LOWER| Gui  |      |    |      | Ent  |RAISE |
 *                  `-------------| BSpc |    | Spc  |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_COLEMAK] = LAYOUT ( \
  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, \
  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,       KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    \
  SFTZED,  CTRLX,   ALTC,    KC_V,    KC_B,       KC_K,    KC_M,    ALTCOMM, CTRLDOT, SFTSLSH, \
                    LOWER,   KC_LGUI, KC_BSPC,    KC_SPC,  KC_ENT,  RAISE                      \
),

/* Lower
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |           |   ^  |   &  |   *  |   (  |   )  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | CAPS |      |  UP  |      | Home |           | PgDn |   +  |   {  |   }  |   _  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   ~  | Left | Down | Right| End  |           | PgUp | Mute | Vol- | Vol+ |   /  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | Del  |      |    |      |   |  |      |
 *                  `-------------| Esc  |    | Tab  |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_LOWER] = LAYOUT ( \
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, \
  KC_CAPS, _______, KC_UP,   _______, KC_HOME,    KC_PGUP, KC_PLUS, KC_LCBR, KC_RCBR, KC_UNDS, \
  KC_TILD, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,     KC_PGDN, KC_MUTE, KC_VOLD, KC_VOLU, KC_SLSH, \
                    _______, KC_DEL,  KC_ESC,     KC_TAB,  KC_PIPE, _______                    \
),

/* Raise
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | CAPS |      |  UP  |      | Home |           | PgDn |   =  |   [  |   ]  |   -  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   `  | Left | Down | Right| End  |           | PgUp | Prev | Play | Next |   ?  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | Del  |      |    |      |   \  |      |
 *                  `-------------| Esc  |    | Tab  |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_RAISE] = LAYOUT ( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    \
  KC_CAPS, _______, KC_UP,   _______, KC_HOME,    KC_PGUP, KC_EQL,  KC_LBRC, KC_RBRC, KC_MINS, \
  KC_GRV,  KC_LEFT, KC_DOWN, KC_RGHT, KC_END,     KC_PGDN, KC_MPRV, KC_MPLY, KC_MNXT, KC_QUES, \
                    _______, KC_DEL,  KC_ESC,     KC_TAB,  KC_BSLS, _______                    \
),

/* Adjust (Lower + Raise)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |  F6  |  F7  |  F8  |  F9  | F10  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  F11 |      |      |      |      |           |      | PrSc | ScLk | Paus | F12  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |QWERTY|COLEMK|DVORAK|      |           |RESET |      |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      |      |      |    |      |      |      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_ADJUST] =  LAYOUT ( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_UP,   KC_F9,   KC_F10,  \
  KC_F11,  _______, _______, _______, _______,    _______, KC_PSCR, KC_SLCK, KC_PAUS, KC_F12,  \
  _______, QWERTY,  COLEMAK, DVORAK,  _______,    RESET,   _______, _______, _______, _______, \
                    _______, _______, _______,    _______, _______, _______                    \
)
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
};

void matrix_init_user(void) {
   // This will disable the red LEDs on the ProMicros
   DDRD &= ~(1<<5);
   PORTD &= ~(1<<5);
   DDRB &= ~(1<<0);
   PORTB &= ~(1<<0);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_COLEMAK);
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_DVORAK);
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
      }
    return true;
};
