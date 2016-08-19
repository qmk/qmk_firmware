/*
 * PLEASE NOTE: This keymap has been updated to work with the Infinity ErgoDox. To build for the Infinity,
 * simply append `SUBPROJECT=infinity` to the end of your `make` statement. This keymap file is untested
 * on the Infinity ErgoDox.
 * 
 * About this keymap:
 * 
 * The Dvorak layout shown herestems from my early Kinesis years, using the Contour PS/2 with a Dvorak
 * software layout. Because of this, the RBRC and LBRC were on opposite sides of the board in the corner
 * keys. I've decided to continue using this layout with my ErgoDox.
 *
 * The QWERTY layout shown here is based entirely on the Kinesis Advantage layout, with the additional
 * keys as shown in the diagrams. The Colemak layout is merely an adaptation of that.
 *
 * I've enabled persistent keymaps for Qwerty, Dvorak and Colemak layers, similar to the default Planck
 * layouts.
 * 
 * For a better explanation of the layout matrices shown below, take a look at ../../ez/ez.h where the
 * keymap is defined, beginning on line 81.
 *
 */

#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _DV 0 // Dvorak layer
#define _QW 1 // Qwerty layer
#define _CM 2 // Colemak layer
#define _MD 3 // Media Layer
#define _KP 4 // Keypad Layer

// Macro name shortcuts
#define DVORAK M(_DV)
#define QWERTY M(_QW)
#define COLEMAK M(_CM)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DV] = {  // layer 0 : Dvorak
/*  
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ]    |   1  |   2  |   3  |   4  |   5  | ESC  |           | ESC  |   6  |   7  |   8  |   9  |   0  |   [    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   '  |   ,  |   .  |   Y  |   Y  |      |           |      |   F  |   G  |   C  |   R  |   L  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CapsLk |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |   S  |   -    |
 * |--------+------+------+------+------+------| _MD  |           | _KP  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   X  |      |           |      |   B  |   M  |   W  |   V  |   Z  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LGUI |   `  |  INS | Left | Rght |                                       |  Up  |  Dn  |   /  |   =  | RGUI |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | LCtr | LAlt |       | Ralt | RCtr |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Home |       | PgUp |      |      |
 *                                 | BkSp | Del  |------|       |------| Enter| Space|
 *                                 |      |      | End  |       | PgDn |      |      |
 *                                 `--------------------'       `--------------------'
 *
 */
#ifdef SUBPROJECT_infinity // Infinity Ergodox
	// left hand
	{XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT, KC_HOME},
	{XXXXXXX, XXXXXXX, XXXXXXX, KC_LCTL, KC_END },
	{KC_6,    MO(_KP), XXXXXXX, MO(_MD), KC_DEL },
	{KC_5,    KC_Y,    KC_I,    KC_X,    KC_BSPC},
	{KC_4,    KC_P,    KC_U,    KC_K,    KC_RGHT},
	{KC_3,    KC_DOT,  KC_E,    KC_J,    KC_LEFT},
	{KC_2,    KC_COMM, KC_O,    KC_Q,    KC_INS },
	{KC_1,    KC_QUOT, KC_A,    KC_SCLN, KC_GRV },
	{KC_RBRC, KC_TAB,  KC_CAPS, KC_LSFT, KC_LGUI},

	//Right Hand
	{XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, KC_PGUP},
	{XXXXXXX, XXXXXXX, XXXXXXX, KC_RCTL, KC_PGDN},
	{KC_ESC,  MO(_MD), XXXXXXX, MO(_KP), KC_ENT },
	{KC_6,    KC_F,    KC_D,    KC_B,    KC_SPC },
	{KC_7,    KC_G,    KC_H,    KC_M,    KC_UP  },
	{KC_8,    KC_C,    KC_T,    KC_W,    KC_DOWN},
	{KC_9,    KC_R,    KC_N,    KC_V,    KC_SLSH},
	{KC_0,    KC_L,    KC_S,    KC_Z,    KC_EQL },
	{KC_LBRC, KC_BSLS, KC_MINS, KC_RSFT, KC_RGUI}
#else // Ergodox and Ergodox EZ 
        // left hand
	{KC_RBRC, KC_TAB,  KC_CAPS, KC_LSFT, KC_LGUI, XXXXXXX},
	{KC_1,    KC_QUOT, KC_A,    KC_SCLN, KC_GRV,  KC_END },
	{KC_2,    KC_COMM, KC_O,    KC_Q,    KC_INS,  KC_DEL },
	{KC_3,    KC_DOT,  KC_E,    KC_J,    KC_LEFT, KC_BSPC},
	{KC_4,    KC_P,    KC_U,    KC_K,    KC_RGHT, KC_HOME},
	{KC_5,    KC_Y,    KC_I,    KC_X,    XXXXXXX, KC_LCTL},
	{KC_ESC,  XXXXXXX, XXXXXXX, MO(_MD), XXXXXXX, KC_LALT},

	// right hand
	{KC_ESC,  XXXXXXX, XXXXXXX, MO(_KP), XXXXXXX, KC_RALT},
	{KC_6,    KC_F,    KC_D,    KC_B,    XXXXXXX, KC_RCTL},
	{KC_7,    KC_G,    KC_H,    KC_M,    KC_UP,   KC_PGUP},
	{KC_8,    KC_C,    KC_T,    KC_W,    KC_DOWN, KC_SPC },
	{KC_9,    KC_R,    KC_N,    KC_V,    KC_SLSH, KC_ENT },
	{KC_0,    KC_L,    KC_S,    KC_Z,    KC_EQL,  KC_PGDN},
	{KC_LBRC, KC_BSLS, KC_MINS, KC_RSFT, KC_RGUI, XXXXXXX}
#endif
  },


[_QW] = {  // layer 1 : QWERTY
/* 
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | ESC  |           | ESC  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CapsLk |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------| _MD  |           | _KP  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LGUI |   `  |  INS | Left | Rght |                                       |  Up  |  Dn  |   [  |   ]  | RGUI |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | LCtr | LAlt |       | Ralt | RCtr |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Home |       | PgUp |      |      |
 *                                 | BkSp | Del  |------|       |------| Enter| Space|
 *                                 |      |      | End  |       | PgDn |      |      |
 *                                 `--------------------'       `--------------------'
 */
#ifdef SUBPROJECT_infinity // Infinity Ergodox
	// left hand
	{XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT, KC_HOME},
	{XXXXXXX, XXXXXXX, XXXXXXX, KC_LCTL, KC_END },
	{KC_6,    MO(_KP), XXXXXXX, MO(_MD), KC_DEL },
	{KC_5,    KC_Y,    KC_I,    KC_X,    KC_BSPC},
	{KC_4,    KC_P,    KC_U,    KC_K,    KC_RGHT},
	{KC_3,    KC_DOT,  KC_E,    KC_J,    KC_LEFT},
	{KC_2,    KC_COMM, KC_O,    KC_Q,    KC_INS },
	{KC_1,    KC_QUOT, KC_A,    KC_SCLN, KC_GRV },
	{KC_RBRC, KC_TAB,  KC_CAPS, KC_LSFT, KC_LGUI},

	//Right Hand
	{XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, KC_PGUP},
	{XXXXXXX, XXXXXXX, XXXXXXX, KC_RCTL, KC_PGDN},
	{KC_ESC,  MO(_MD), XXXXXXX, MO(_KP), KC_ENT },
	{KC_6,    KC_F,    KC_D,    KC_B,    KC_SPC },
	{KC_7,    KC_G,    KC_H,    KC_M,    KC_UP  },
	{KC_8,    KC_C,    KC_T,    KC_W,    KC_DOWN},
	{KC_9,    KC_R,    KC_N,    KC_V,    KC_SLSH},
	{KC_0,    KC_L,    KC_S,    KC_Z,    KC_EQL },
	{KC_LBRC, KC_BSLS, KC_MINS, KC_RSFT, KC_RGUI}
#else // Ergodox and Ergodox EZ 
        // left hand
	{KC_EQL,  KC_TAB,  KC_CAPS, KC_LSFT, KC_LGUI, XXXXXXX},
	{KC_1,    KC_Q,    KC_A,    KC_Z,    KC_GRV,  KC_END },
	{KC_2,    KC_W,    KC_S,    KC_X,    KC_INS,  KC_DEL },
	{KC_3,    KC_E,    KC_D,    KC_C,    KC_LEFT, KC_BSPC},
	{KC_4,    KC_R,    KC_F,    KC_V,    KC_RGHT, KC_HOME},
	{KC_5,    KC_T,    KC_G,    KC_B,    XXXXXXX, KC_LCTL},
	{KC_ESC,  XXXXXXX, XXXXXXX, MO(_MD), XXXXXXX, KC_LALT},

	// right hand
	{KC_ESC,  XXXXXXX, XXXXXXX, MO(_KP), XXXXXXX, KC_RALT},
	{KC_6,    KC_Y,    KC_H,    KC_N,    XXXXXXX, KC_RCTL},
	{KC_7,    KC_U,    KC_J,    KC_M,    KC_UP,   KC_PGUP},
	{KC_8,    KC_I,    KC_K,    KC_COMM, KC_DOWN, KC_SPC },
	{KC_9,    KC_O,    KC_L,    KC_DOT,  KC_LBRC, KC_ENT },
	{KC_0,    KC_P,    KC_SCLN, KC_SLSH, KC_RBRC, KC_PGDN},
	{KC_MINS, KC_BSLS, KC_QUOT, KC_RSFT, KC_RGUI, XXXXXXX}
#endif
  },


[_CM] = {  // layer 2 : Colemak
/* 
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | ESC  |           | ESC  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   F  |   P  |   G  |      |           |      |   J  |   L  |   U  |   Y  |   ;  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSpc  |   A  |   R  |   S  |   T  |   D  |------|           |------|   H  |   N  |   E  |   I  |   O  |   '    |
 * |--------+------+------+------+------+------| _MD  |           | _KP  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   K  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LGUI |   `  |  INS | Left | Rght |                                       |  Up  |  Dn  |   [  |   ]  | RGUI |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | LCtr | LAlt |       | Ralt | RCtr |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Home |       | PgUp |      |      |
 *                                 | BkSp | Del  |------|       |------| Enter| Space|
 *                                 |      |      | End  |       | PgDn |      |      |
 *                                 `--------------------'       `--------------------'
 */
#ifdef SUBPROJECT_infinity // Infinity Ergodox
	// left hand
	{XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT, KC_HOME},
	{XXXXXXX, XXXXXXX, XXXXXXX, KC_LCTL, KC_END },
	{KC_6,    MO(_KP), XXXXXXX, MO(_MD), KC_DEL },
	{KC_5,    KC_Y,    KC_I,    KC_X,    KC_BSPC},
	{KC_4,    KC_P,    KC_U,    KC_K,    KC_RGHT},
	{KC_3,    KC_DOT,  KC_E,    KC_J,    KC_LEFT},
	{KC_2,    KC_COMM, KC_O,    KC_Q,    KC_INS },
	{KC_1,    KC_QUOT, KC_A,    KC_SCLN, KC_GRV },
	{KC_RBRC, KC_TAB,  KC_CAPS, KC_LSFT, KC_LGUI},

	//Right Hand
	{XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, KC_PGUP},
	{XXXXXXX, XXXXXXX, XXXXXXX, KC_RCTL, KC_PGDN},
	{KC_ESC,  MO(_MD), XXXXXXX, MO(_KP), KC_ENT },
	{KC_6,    KC_F,    KC_D,    KC_B,    KC_SPC },
	{KC_7,    KC_G,    KC_H,    KC_M,    KC_UP  },
	{KC_8,    KC_C,    KC_T,    KC_W,    KC_DOWN},
	{KC_9,    KC_R,    KC_N,    KC_V,    KC_SLSH},
	{KC_0,    KC_L,    KC_S,    KC_Z,    KC_EQL },
	{KC_LBRC, KC_BSLS, KC_MINS, KC_RSFT, KC_RGUI}
#else // Ergodox and Ergodox EZ 
        // left hand
	{KC_EQL,  KC_TAB,  KC_BSPC, KC_LSFT, KC_LGUI, XXXXXXX},
	{KC_1,    KC_Q,    KC_A,    KC_Z,    KC_GRV,  KC_END },
	{KC_2,    KC_W,    KC_R,    KC_X,    KC_INS,  KC_DEL },
	{KC_3,    KC_F,    KC_S,    KC_C,    KC_LEFT, KC_BSPC},
	{KC_4,    KC_P,    KC_T,    KC_V,    KC_RGHT, KC_HOME},
	{KC_5,    KC_G,    KC_D,    KC_B,    XXXXXXX, KC_LCTL},
	{KC_ESC,  XXXXXXX, XXXXXXX, MO(_MD), XXXXXXX, KC_LALT},

	// right hand
	{KC_ESC,  XXXXXXX, XXXXXXX, MO(_KP), XXXXXXX, KC_RALT},
	{KC_6,    KC_J,    KC_H,    KC_K,    XXXXXXX, KC_RCTL},
	{KC_7,    KC_L,    KC_N,    KC_M,    KC_UP,   KC_PGUP},
	{KC_8,    KC_U,    KC_E,    KC_COMM, KC_DOWN, KC_SPC },
	{KC_9,    KC_Y,    KC_I,    KC_DOT,  KC_LBRC, KC_ENT },
	{KC_0,    KC_SCLN, KC_O,    KC_SLSH, KC_RBRC, KC_PGDN},
	{KC_MINS, KC_BSLS, KC_QUOT, KC_RSFT, KC_RGUI, XXXXXXX}
#endif
  },


[_MD] = { // layer 3 : Media layer
/* 
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | TEENSY |  F1  |  F2  |  F3  |  F4  |  F5  | F11  |           |  F12 |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | PrSc | ScLk | Paus |      |      |           |      |      | Mute | Vol- | Vol+ |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| Stop | Prev | Play | Next | Sel  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |Dvorak|Qwerty|Colemk|      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
#ifdef SUBPROJECT_infinity // Infinity Ergodox
	// left hand
	{XXXXXXX, XXXXXXX, XXXXXXX, _______, _______},
	{XXXXXXX, XXXXXXX, XXXXXXX, _______, _______},
	{KC_F11,  _______, XXXXXXX, _______, _______},
	{KC_F5,   _______, _______, _______, _______},
	{KC_F4,   KC_PAUS, _______, COLEMAK, _______},
	{KC_F3,   KC_SLCK, _______, QWERTY,  _______},
	{KC_F2,   KC_PSCR, _______, DVORAK,  _______},
	{KC_F1,   _______, _______, _______, _______},
	{RESET,   _______, _______, _______, _______},

	//Right Hand
	{XXXXXXX, XXXXXXX, XXXXXXX, _______, _______},
	{XXXXXXX, XXXXXXX, XXXXXXX, _______, _______},
	{KC_F12,  _______, XXXXXXX, _______, _______},
	{KC_F6,   _______, KC_MSTP, _______, _______},
	{KC_F7,   KC_VOLU, KC_MPRV, _______, _______},
	{KC_F8,   KC_VOLD, KC_MPLY, _______, _______},
	{KC_F9,   KC_MUTE, KC_MNXT, _______, _______},
	{KC_F10,  _______, KC_MSEL, _______, _______},
	{_______, _______, _______, _______, _______},
#else // Ergodox and Ergodox EZ 
        // left hand
	{RESET,   _______, _______, _______, _______, XXXXXXX},
	{KC_F1,   _______, _______, _______, _______, _______},
	{KC_F2,   KC_PSCR, _______, DVORAK,  _______, _______},
	{KC_F3,   KC_SLCK, _______, QWERTY,  _______, _______},
	{KC_F4,   KC_PAUS, _______, COLEMAK, _______, _______},
	{KC_F5,   _______, _______, _______, XXXXXXX, _______},
	{KC_F11,  XXXXXXX, XXXXXXX, _______, XXXXXXX, _______},

	// right hand
	{KC_F12,  XXXXXXX, XXXXXXX, _______, XXXXXXX, _______},
	{KC_F6,   _______, KC_MSTP, _______, XXXXXXX, _______},
	{KC_F7,   KC_MUTE, KC_MPRV, _______, _______, _______},
	{KC_F8,   KC_VOLD, KC_MPLY, _______, _______, _______},
	{KC_F9,   KC_VOLU, KC_MNXT, _______, _______, _______},
	{KC_F10,  _______, KC_MSEL, _______, _______, _______},
	{_______, _______, _______, _______, _______, XXXXXXX}
#endif
  },


[_KP] = { // layer 4 : Keypad layer
/* 
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Power  |      |      |      |      |      |      |           |      |      | NmLk | KP / | KP * | KP - |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Sleep  |      |      |      |      |      |      |           |      |      | KP 7 | KP 8 | KP 9 | KP + |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Wake   |      |      |      |      |      |------|           |------|      | KP 4 | KP 5 | KP 6 | KP + |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      | KP 1 | KP 2 | KP 3 |KP Ent|        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       | KP 0 |      | KP . |KP Ent|      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
#ifdef SUBPROJECT_infinity // Infinity Ergodox
	// left hand
	{XXXXXXX, XXXXXXX, XXXXXXX, _______, _______},
	{XXXXXXX, XXXXXXX, XXXXXXX, _______, _______},
	{_______, _______, XXXXXXX, _______, _______},
	{_______, _______, _______, _______, _______},
	{_______, _______, _______, _______, _______},
	{_______, _______, _______, _______, _______},
	{_______, _______, _______, _______, _______},
	{_______, _______, _______, _______, _______},
	{KC_PWR,  KC_SLEP, KC_WAKE, _______, _______},

	//Right Hand
	{XXXXXXX, XXXXXXX, XXXXXXX, _______, _______},
	{XXXXXXX, XXXXXXX, XXXXXXX, _______, _______},
	{_______, _______, XXXXXXX, _______, _______},
	{_______, _______, KC_MSTP, _______, _______},
	{KC_NLCK, KC_P7,   KC_P4,   KC_P1,   KC_P0  },
	{KC_PSLS, KC_P8,   KC_P5,   KC_P2,   _______},
	{KC_PAST, KC_P9,   KC_P6,   KC_P3,   KC_PDOT},
	{KC_PMNS, KC_PPLS, KC_PPLS, KC_PENT, KC_PENT},
	{_______, _______, _______, _______, _______},
#else // Ergodox and Ergodox EZ 
        // left hand
	{KC_PWR,  KC_SLEP, KC_WAKE, _______, _______, XXXXXXX},
	{_______, _______, _______, _______, _______, _______},
	{_______, _______, _______, _______, _______, _______},
	{_______, _______, _______, _______, _______, _______},
	{_______, _______, _______, _______, _______, _______},
	{_______, _______, _______, _______, XXXXXXX, _______},
	{_______, XXXXXXX, XXXXXXX, _______, XXXXXXX, _______},

	// right hand
	{_______, XXXXXXX, XXXXXXX, _______, XXXXXXX, _______},
	{_______, _______, _______, _______, XXXXXXX, _______},
	{KC_NLCK, KC_P7,   KC_P4,   KC_P1,   KC_P0,   _______},
	{KC_PSLS, KC_P8,   KC_P5,   KC_P2,   XXXXXXX, _______},
	{KC_PAST, KC_P9,   KC_P6,   KC_P3,   KC_PDOT, _______},
	{KC_PMNS, KC_PPLS, KC_PPLS, KC_PENT, KC_PENT, _______},
	{_______, _______, _______, _______, XXXXXXX, XXXXXXX}
#endif
  },


};

const uint16_t PROGMEM fn_actions[] = {

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case _DV:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_DV);
          }
          break;
        case _QW:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_QW);
          }
          break;
        case _CM:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_CM);
          }
          break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
