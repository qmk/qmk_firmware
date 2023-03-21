/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#include QMK_KEYBOARD_H
#include "common_oled.h"

enum keymap_layers {
    _BASE,
    _LHAND,
    _FUNC
};

//Layers and special keys.
#define SPC_LHND LT(_LHAND, KC_SPC)
#define BSP_FUNC LT(_FUNC, KC_BSPC)
#define DEL_FUNC LT(_FUNC, KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* QWERTY
     * .--------------------------------------------------------------.  .--------------------------------------------------------------.
     * | Esc    | 1      | 2      | 3      | 4      | 5      |   `    |  |    =   | 6      | 7      | 8      | 9      | 0      | -      |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * | Tab    | Q      | W      | E      | R      | T      |   [    |  |    ]   | Y      | U      | I      | O      | P      | \      |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * | LCtrl  | A      | S      | D      | F      | G      |   Home |  |   End  | H      | J      | K      | L      | :      | '      |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * | Shift/(| Z      | X      | C      | V      | B      |   Play |  |   Mute | N      | M      | ,      | .      | /      | Shift/)|
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * | LCtrl  | Win    | Alt    | MO(3)  | L2/Del | Space  | Space  |  | Bcksp  | Bcksp  | Left   | Down   | Up     | Right  | Ctrl   |
     * '--------+--------+--------+--------+--------+--------+--------'  '--------+--------+--------+--------+--------+--------+--------'
     *      Encoder 1         Encoder 2                                                                  Encoder 3         Encoder 4
     * .-----------------------------------.                                                        .-----------------------------------.
     * | VolUp  | VolDn  | VolUp  | VolDn  |                                                        | PgUp   | PgDn   | PgUp   | PgDn   |
     * |--------+--------+--------+--------+--------.                                      .--------+--------+--------+--------+--------|
     * | VolDn  | VolUp  | Next   | Play   | Prev   | Touch Encoder          Touch Encoder | RgbHuI | RgbHuD | RgbMdD | RgbTog | RgbMdI |
     * '--------+--------+--------+--------+--------'                                      '--------+--------+--------+--------+--------'
     */
    [_BASE] = LAYOUT(
			KC_ESC,  KC_1,    KC_2,    KC_3,  KC_4, 	KC_5,     KC_GRV, 		KC_EQL,   KC_6,     KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS, 
			KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R, 	KC_T,     KC_LBRC,  	KC_RBRC,  KC_Y,     KC_U,    KC_I,    KC_O,   KC_P,    KC_BSLS, 
			KC_LCTL, KC_A,    KC_S,    KC_D,  KC_F, 	KC_G,     KC_HOME,  	KC_END,   KC_H,     KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
			SC_LSPO, KC_Z,    KC_X,    KC_C,  KC_V,     KC_B,     KC_MPLY,  	KC_MUTE,  KC_N,     KC_M,    KC_COMM, KC_DOT, KC_SLSH, SC_RSPC, 
			KC_LCTL, KC_LGUI, KC_LALT, MO(3), DEL_FUNC, SPC_LHND, SPC_LHND, 	BSP_FUNC, BSP_FUNC, KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, KC_RCTL, 
			// Here we have the encoder setup. Encoder 0 clockwise, Encoder 0 counter-clockwise, Encoder 1 clockwise, Encoder 1 counter-clockwise , then right side
			KC_VOLU, KC_VOLD, KC_VOLU, KC_VOLD, KC_PGDN, KC_PGUP, KC_PGDN, KC_PGUP, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY, KC_MPRV, RGB_HUI, RGB_HUD, RGB_RMOD, RGB_TOG, RGB_MOD
			),
    [_LHAND] = LAYOUT(
			QK_BOOT,  KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,		KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS, 
			KC_TRNS, KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, 		KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SCRL, KC_PAUS, KC_TRNS, 
			KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_PGUP, 		KC_PGDN, KC_TRNS, KC_TRNS, KC_INS,  KC_HOME, KC_PGUP, KC_TRNS,
			KC_LSFT, KC_CALC, KC_MYCM, KC_TRNS, KC_ENT,  KC_BSPC, KC_TRNS, 		KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,  KC_END,  KC_PGDN, KC_RSFT, 
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 		KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS,
			// Encoders.
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
			),
    [_FUNC] = LAYOUT(
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 		RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, QK_BOOT, 
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
			// Encoders.
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
			),
	// Placeholder layer!
	[3] = LAYOUT(
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
			// Encoders.
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
			)
};