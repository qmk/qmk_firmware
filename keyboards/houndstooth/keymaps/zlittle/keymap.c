#include QMK_KEYBOARD_H

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
	      MT(MOD_LALT, KC_TAB),  KC_Q,  KC_W,   KC_E,   KC_R, KC_T,                  					 KC_Y,    KC_U, KC_I, KC_O,   KC_P,    KC_PIPE,
	    MT(MOD_LGUI, KC_BSPC),  KC_A,  KC_S,   KC_D,   KC_F, KC_G,                 							 KC_H,    KC_J, KC_K, KC_L,   KC_SCLN, KC_QUOT,
	     KC_ENT,KC_Z,  KC_X,   KC_C,   KC_V, KC_B,     		            				  				 				KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
	     KC_LSFT,LGUI(LCTL(KC_Q)),KC_ESC, MT(MOD_LCTL, KC_DEL), LT(SYMB, KC_SPC),LT(SYMB, KC_SPC),         	LT(NUMB, KC_SPC),	 LT(NUMB, KC_SPC), KC_LSFT, KC_TAB,LCTL(LSFT(KC_3)),LCTL(LSFT(KC_4))
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
                            KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_SCLN,KC_SCLN,                 KC_EQL, KC_EQL,  KC_SCLN, KC_DEL,KC_TRNS, KC_TRNS
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
                    KC_TRNS,KC_TRNS,KC_F11, KC_F12, KC_TRNS,KC_TRNS,                      KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS
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
        KC_TRNS,KC_TRNS,  KC_0, LT(ONE_HAND_ALT, KC_DEL), KC_TRNS,KC_TRNS,                     KC_TRNS, TO(BASE), KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS
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
            KC_TRNS,KC_TRNS,  KC_0, KC_TRNS, KC_TRNS,KC_TRNS,                        KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS
            )
};
