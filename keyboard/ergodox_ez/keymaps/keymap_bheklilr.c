#include "keymap_common.h"
#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MOUS 2 // mouse keys
#define ARRS 3 // arrow keys and media keys
#define NMPD 4 // numpad

#define SYMBT(k) LT(SYMB, k)
#define MOUST(k) LT(MOUS, k)
#define ARRST(k) LT(ARRS, k)
#define NMPDT(k) LT(NMPD, k)

#define SUBL_GOTO LCTL(KC_P)
#define SUBL_PROJ LCTL(LALT(KC_P))
#define SUBL_PAL RCTL(RSFT(KC_P))
#define UNDO LCTL(KC_Z)
#define CTAL_T(k) CTL_T(ALT_T(k))
#define CTSH_T(k) CTL_T(SFT_T(k))
#define ALSH_T(k) ALT_T(SFT_T(k))

#define CTLALT LCTL(KC_LALT)
#define CTLSFT LCTL(KC_LSFT)
#define ALTSFT LALT(KC_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Grv/Gui|   1  |   2  |   3  |   4  |   5  |  6   |           | C+S+P|   7  |   8  |   9  |   0  |   -  |   \    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  | CTL+ |           | CTL+P|   Y  |   U  |   I  |   O  |   P  |   =    |
 * |--------+------+------+------+------+------| PGUP |           |      |------+------+------+------+------+--------|
 * | Esc    |   A  |   S  | D/L4 | F/L3 |   G  |------|           |------|   H  |J/SYMB|K/MOUS|   L  |   ;  |   '    |
 * |--------+------+------+------+------+------| CTL+ |           | CTL+ |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  | PGDN |           | ALT+P|   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *  | Undo  |  '"  |  Ins | Home | End  |                                       | PgUp | PgDn | Ctl+[| Ctl+]| Undo |
 *  `-----------------------------------'                                       `----------------------------------'
 *                                        ,---------------.       ,---------------.
 *                                        | App  | LGui   |       | Meh  |Esc/Ctrl|
 *                                 ,------|------|--------|       |------+--------+------.
 *                                 |      |      |CtlSft  |       |AltSft|        |      |
 *                                 | BkSp | Tab  |--------|       |------| Enter  |Space |
 *                                 |      |      |[/CtlAlt|       |]/Alt |        |      |
 *                                 `----------------------'       `----------------------'
 */
[BASE] = KEYMAP(
	GUI_T(KC_GRV),	KC_1,		KC_2,		KC_3,		KC_4,		KC_5,		KC_6,
	KC_DEL,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,		LCTL(KC_PGUP),
	KC_ESC,		KC_A,		KC_S,		NMPDT(KC_D),	ARRST(KC_F),	KC_G,
	KC_LSFT,	CTL_T(KC_Z),	KC_X,		KC_C,		KC_V,		KC_B,		LCTL(KC_PGDN),
	UNDO,		LSFT(KC_SCLN),	KC_INS,		KC_HOME,	KC_END,
											KC_APP,		KC_LGUI,
													CTLSFT,
									KC_BSPC,	KC_TAB,		CTAL_T(KC_LBRC),
	/**************************************************************************************************************/
	SUBL_PROJ,	KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,	KC_BSLS,
	SUBL_GOTO,	KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_EQL,
			KC_H,		SYMBT(KC_J),	MOUST(KC_K),	KC_L,		KC_SCLN,	KC_QUOT,
	SUBL_PAL,	KC_N,		KC_M,		KC_COMM,	KC_DOT,		CTL_T(KC_SLSH),	KC_RSFT,
					KC_PGUP,	KC_PGDN,	LCTL(KC_LBRC),	LCTL(KC_RBRC),	UNDO,
	MEH_T(KC_NO),	CTL_T(KC_ESC),
	ALTSFT,
	ALT_T(KC_RBRC),	KC_ENT,		KC_SPC
),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   ;  |   [  |   ]  |   `  |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   (  |   )  |   ~  |      |           |      |      |      |      |      |      |        |
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
// SYMBOLS
[SYMB] = KEYMAP(
	KC_TRNS,	KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F6,
	KC_TRNS,	KC_EXLM,	KC_AT,		KC_LCBR,	KC_RCBR,	KC_PIPE,	KC_TRNS,
	KC_TRNS,	KC_HASH,	KC_SCLN,	KC_LBRC,	KC_RBRC,	KC_GRV,
	KC_TRNS,	KC_PERC,	KC_CIRC,	KC_LPRN,	KC_RPRN,	KC_TILD,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
											KC_TRNS,	KC_TRNS,
													KC_TRNS,
									KC_TRNS,	KC_TRNS,	KC_TRNS,
	/**************************************************************************************************************/
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
			KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
					KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS
),
/* Keymap 2: Mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | Lclk | Rclk |------|       |------| ScrU | ScrD |
 *                                 |      |      | Mclk |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MOUS] = KEYMAP(
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_MS_U,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_MS_L,	KC_MS_D,	KC_MS_R,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
											KC_TRNS,	KC_TRNS,
													KC_TRNS,
									KC_BTN1,	KC_BTN2,	KC_BTN3,
	/**************************************************************************************************************/
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
			KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
					KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_MS_WH_UP,	KC_MS_WH_DOWN
),
/* Keymap 2: Arrow and media keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |  Calc  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |  Up  |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      | Left | Down | Right|      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | Ctl+ | Ctl+ |------|       |------| Ctrl | Shft |
 *                                 | Alt  | Shft |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[ARRS] = KEYMAP(
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
											KC_TRNS,	KC_TRNS,
													KC_TRNS,
									CTLALT,		CTLSFT,		KC_TRNS,
	/**************************************************************************************************************/
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_CALC,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_UP,		KC_TRNS,	KC_TRNS,	KC_TRNS,
			KC_TRNS,	KC_LEFT,	KC_DOWN,	KC_RGHT,	KC_TRNS,	KC_MPLY,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_MPRV,	KC_MNXT,	KC_TRNS,	KC_TRNS,
					KC_VOLU,	KC_VOLD,	KC_MUTE,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_LCTL,	KC_LSFT
),
/*
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      | Debug| Prog |           |      |  F7  |  F8  |  F9  |  F10 |  F11 |   F12  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |   Up |   7  |   8  |   9  |   *  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |   0  |    . |      |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      | GUI+ |      |       |      | GUI+ | GUI+ |
 *                                 | GUI  | CTL  |------|       |------| ALT  | CTL+ |
 *                                 |      |      |      |       |      |      | ALT  |
 *                                 `--------------------'       `--------------------'
 */
[NMPD] = KEYMAP(
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	DEBUG,		RESET,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
											KC_TRNS,	KC_TRNS,
													KC_TRNS,
									LGUI(KC_NO),	LGUI(KC_LCTL),	KC_TRNS,
	/**************************************************************************************************************/
	KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,
	KC_TRNS,	KC_UP,		KC_KP_7,	KC_KP_8,	KC_KP_9,	KC_ASTR,	KC_TRNS,
			KC_DOWN,	KC_KP_4,	KC_KP_5,	KC_KP_6,	KC_PLUS,	KC_MINS,
	KC_TRNS,	KC_AMPR,	KC_KP_1,	KC_KP_2,	KC_KP_3,	KC_BSLS,	KC_TRNS,
					KC_0,		KC_DOT,		KC_TRNS,	KC_EQL,		KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	LGUI(KC_LALT),	LGUI(LCTL(KC_LALT))
),
};

const uint16_t PROGMEM fn_actions[] = {
	[SYMB+1] = ACTION_LAYER_TAP_TOGGLE(SYMB),
	[MOUS+1] = ACTION_LAYER_TAP_TOGGLE(MOUS),
	[ARRS+1] = ACTION_LAYER_TAP_TOGGLE(ARRS),
	[NMPD+1] = ACTION_LAYER_TAP_TOGGLE(NMPD)

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	// MACRODOWN only works in this function
	switch(id) {
		case 0:
			if (record->event.pressed) {
				register_code(KC_RSFT);
			} else {
				unregister_code(KC_RSFT);
			}
			break;
		case 1:
			break;
	}
	return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void * matrix_init_user(void) {
	ergodox_led_all_off();
	ergodox_led_all_set(LED_BRIGHTNESS_HI);

	ergodox_right_led_1_on();
	_delay_ms(111);
	ergodox_right_led_1_off();
	ergodox_right_led_2_on();
	_delay_ms(111);
	ergodox_right_led_2_off();
	ergodox_right_led_3_on();
	_delay_ms(111);
	ergodox_right_led_3_off();
};

// Runs constantly in the background, in a loop.
void * matrix_scan_user(void) {
	uint8_t layer = biton32(layer_state);

	ergodox_board_led_off();

	if ((layer & 0b001) > 0) {
		ergodox_right_led_1_on();
	} else {
		ergodox_right_led_1_off();
	}
	if ((layer & 0b010) > 0) {
		ergodox_right_led_2_on();
	} else {
		ergodox_right_led_2_off();
	}
	if ((layer & 0b100) > 0) {
		ergodox_right_led_3_on();
	} else {
		ergodox_right_led_3_off();
	}
};
