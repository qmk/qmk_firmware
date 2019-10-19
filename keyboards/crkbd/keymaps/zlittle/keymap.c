  #include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  BASE,
  NUMB,
  SYMB,
  ONE_HAND,
  ONE_HAND_ALT
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};
#define BASE 0 // default layer
#define SYMB 1 // symbols
#define NUMB 2 // numbers/motion
#define ONE_HAND 3 //one handed operation
#define ONE_HAND_ALT 4


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap 0: Basic layer
	 *
	 * ,-------------------------------------------.                         ,-------------------------------------------.
	 * | ALT/ta |   Q  |   W  |   E  |   R  |   T  |                        |  Y   |   U  |   I  |   O  |   P  |  | \   |
	 * |--------+------+------+------+------+------|                        |------+------+------+------+------+--------|
	 * |sup /BS |   A  |   S  |  D   |   F  |   G  |                        |   H  |   J  |   K  |   L  | ;  : |  ' "   |
	 * |--------+------+------+------+------+------|                        |------+------+------+------+------+--------|
	 * | ENT    |   Z  |   X  |   C  |   V  |   B  |                        |   N  |   M  | ,  < | . >  | /  ? |  - _   |
	 * `--------+------+------+------+------+-------                        -------+------+------+------+------+--------'
	 *                    .----------.   .-------.                                 .------.   .-----.
	 *                    |esc       |   |ctrl/Del|                               | ent   |   | Tab |
	 *                    '----------'   '-------'                                 `------.   '-----'
	 *                                 ,-----                                ------.
	 *                                 | SYMB |                             | NUMB |
	 *                                 |      |                             |Space |
	 *                                 |      |                             |      |
	 *                                 `-------                             `------'
	 */
	 [BASE] = LAYOUT(
	      MT(MOD_LALT, KC_TAB),  KC_Q,  KC_W,   KC_E,   KC_R, KC_T,                   KC_Y,    KC_U, KC_I, KC_O,   KC_P,    KC_PIPE,
	    MT(MOD_LGUI, KC_BSPC),  KC_A,  KC_S,   KC_D,   KC_F, KC_G,                  KC_H,    KC_J, KC_K, KC_L,   KC_SCLN, KC_QUOT,
	     KC_ENT,KC_Z,  KC_X,   KC_C,   KC_V, KC_B,     		            				   KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
	     KC_ESC, MT(MOD_LCTL, KC_DEL), LT(SYMB, KC_SPC),                   					 LT(NUMB, KC_SPC), KC_LSFT, KC_TAB
	     ),
/* Keymap 1: Symbols layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                         |      |   &  |  =   |   scn|  scn |  \ |   |
 * |--------+------+------+------+------+------|                         |------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |                         |   +  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------|                         |------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |                         |      |      |  ,   |  .   |  / ? | - _    |
 * `--------+------+------+------+------+-------                          ------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |   rgb|   |      |                                 |      |   | DEL |
 *                        '------'   '------'                                 `------.   '-----'
 *
 *                                 ,------                                   ------.
 *                                 |      |                                 |      |
 *                                 |   ;  |                                 |   ;  |
 *                                 |      |                                 |      |
 *                                 `-------                                 `------'
 */
[SYMB] = LAYOUT(
    TO(ONE_HAND), KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                     KC_TRNS, KC_AMPR, KC_EQL, LCTL(LSFT(KC_3)), LCTL(LSFT(KC_4)), KC_BSLS,
    LCTL(LSFT(KC_4)),  KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                      KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT,
      KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                   KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
                                  KC_TRNS, KC_TRNS, KC_SCLN,                  KC_EQL,  KC_SCLN, KC_DEL
    ),
/* Keymap 2: Pad/Function layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                         |  6   |  7   |  8   |  9   |  0   | VolUp  |
 * |--------+------+------+------+------+------|                         |------+------+------+------+------+--------|
 * |  F1    |  F2  | F3   | F4   | F5   | F6   |                         |      | LEFT | DOWN |  UP  | RIGHT| VolDn  |
 * |--------+------+------+------+------+------|                         |------+------+------+------+------+--------|
 * |  F7    |  F8  | F9   | F10  | F11  | F12  |                         | MLFT | MDWN | MUP  | MRGHT|Ply/Pa|  Skip  |
 * `--------+------+------+------+------+-------                         `------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----
 *                                 ,------|                              ------
 *                                 |      |                             |       |
 *                                 |      |                             |       |
 *                                 |      |                             |       |
 *                                 `-------                             `--------
 */
[NUMB] = LAYOUT(
    KC_TRNS, KC_1, 	  KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_VOLU,
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_VOLD,
    KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_MPLY, KC_MNXT,
                            KC_F11, KC_F12, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS
    ),
    /* Keymap 2: Pad/Function layer
     *
     * ,-------------------------------------------.                         ,-------------------------------------------.
     * |        |   1  |  2   |  3   |  4   |  5   |                         |  6   |  7   |  8   |  9   |  0   | VolUp  |
     * |--------+------+------+------+------+------|                         |------+------+------+------+------+--------|
     * |  F1    |  F2  | F3   | F4   | F5   | F6   |                         |      | LEFT | DOWN |  UP  | RIGHT| VolDn  |
     * |--------+------+------+------+------+------|                         |------+------+------+------+------+--------|
     * |  F7    |  F8  | F9   | F10  | F11  | F12  |                         | MLFT | MDWN | MUP  | MRGHT|Ply/Pa|  Skip  |
     * `--------+------+------+------+------+-------                         `------+------+------+------+------+--------'
     *                        .------.   .------.                                 .------.   .-----.
     *                        |      |   |      |                                 |      |   |     |
     *                        '------'   '------'                                 `------.   '-----
     *                                 ,------|                              ------
     *                                 |      |                             |       |
     *                                 |      |                             |       |
     *                                 |      |                             |       |
     *                                 `-------                             `--------
     */
    [ONE_HAND] = LAYOUT(
        TO(BASE), KC_7, 	  KC_8,    KC_9,    KC_MINS,    KC_SLSH,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_VOLU,
        KC_TRNS, KC_4,   KC_5,   KC_6,   KC_PLUS,   KC_BSLS,                       KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_VOLD,
        KC_TRNS, KC_1,   KC_2,   KC_3,   KC_DOT,  KC_PIPE,                      KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_MPLY, KC_MNXT,
                                KC_0, LT(ONE_HAND_ALT, KC_DEL), KC_TRNS,                        TO(BASE), KC_TRNS, KC_TRNS
        )
        ,
        /* Keymap 2: Pad/Function layer
         *
         * ,-------------------------------------------.                         ,-------------------------------------------.
         * |        |   1  |  2   |  3   |  4   |  5   |                         |  6   |  7   |  8   |  9   |  0   | VolUp  |
         * |--------+------+------+------+------+------|                         |------+------+------+------+------+--------|
         * |  F1    |  F2  | F3   | F4   | F5   | F6   |                         |      | LEFT | DOWN |  UP  | RIGHT| VolDn  |
         * |--------+------+------+------+------+------|                         |------+------+------+------+------+--------|
         * |  F7    |  F8  | F9   | F10  | F11  | F12  |                         | MLFT | MDWN | MUP  | MRGHT|Ply/Pa|  Skip  |
         * `--------+------+------+------+------+-------                         `------+------+------+------+------+--------'
         *                        .------.   .------.                                 .------.   .-----.
         *                        |      |   |      |                                 |      |   |     |
         *                        '------'   '------'                                 `------.   '-----
         *                                 ,------|                              ------
         *                                 |      |                             |       |
         *                                 |      |                             |       |
         *                                 |      |                             |       |
         *                                 `-------                             `--------
         */
        [ONE_HAND_ALT] = LAYOUT(
            TO(BASE), KC_7, 	  KC_8,    KC_9,    KC_MINS,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_VOLU,
            LCTL(LSFT(KC_4)), KC_4,   KC_5,   KC_6,   KC_PLUS,   KC_F5,                       KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_VOLD,
            KC_TRNS, LCTL(KC_Z),   LCTL(KC_X),   LCTL(KC_C),   LCTL(KC_V),  KC_F10,                      KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_MPLY, KC_MNXT,
                                    KC_0, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS
            )
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_master)
   return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
 return rotation;
}

// // When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

void oled_task_user(void) {

  if (is_master) {
	static const char PROGMEM font_logo[] = {
			0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
			0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
	0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
  switch (biton32(layer_state)) {
    case BASE:
        oled_write_P(font_logo, false);
      break;
    case NUMB:
      oled_write_P(PSTR("NUMBERS\n\n\n"), false);
      break;
    case SYMB:
      oled_write_P(PSTR("SYMBOLS\n\n\n"), false);
      break;
    case ONE_HAND:
      oled_write_P(PSTR("ONE HAND\n\n\n"), false);
      break;
    case ONE_HAND_ALT:
      oled_write_P(PSTR("ONE HAND ALT\n\n\n"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
        oled_write_P(font_logo, false);
  }
} else {
  oled_write_ln(read_layer_state(), false);
       oled_write_ln(read_keylog(), false);
       oled_write_ln(read_keylogs(), false);
}
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
