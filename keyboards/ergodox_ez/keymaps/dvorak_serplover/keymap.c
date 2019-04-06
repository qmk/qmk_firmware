#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "keymap_steno.h"
#include "version.h"

enum layers {
	BASE, // default layer
	SYMB, // symbols
	PLVR, // plover steno (gemini protocol)
	QWRT, // qwerty layer for gaming
	LEDS,  // LED controls
};

enum custom_keycodes {
	PLACEHOLDER = SAFE_RANGE, // can always be here
	L_MIN,
	L_MP = L_MIN,
	L_MM,
	L_HP,
	L_HM,
	L_SP,
	L_SM,
	L_VP,
	L_VM,
	L_ON,
	L_OFF,
	L_MAX
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | Esc  |           | PLVR |   6  |   7  |   8  |   9  |   0  |   \    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   '  |   ,  |   .  |   P  |   Y  |  L1  |           |      |   F  |   G  |   C  |   R  |   L  |   /    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCtrl  |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |   S  |   -    |
 * |--------+------+------+------+------+------|  L4  |           |  L3  |------+------+------+------+------+--------|
 * | LShift |   ;  |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |   Z  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Lalt  |  Grv |      | Left | Right|                                       |  Up  | Down |   [  |   ]  | RAlt |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | LCtrl| LGui |       | RGui | RCtrl  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 |Backsp|Delete|------|       |------| Enter  |Space |
 *                                 |   ace|      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_EQL,         KC_1,     KC_2,    KC_3,   KC_4,   KC_5,   KC_ESC,
        KC_TAB,         KC_QUOT,  KC_COMM, KC_DOT, KC_P,   KC_Y,   MO(SYMB),
        KC_LCTRL,       KC_A,     KC_O,    KC_E,   KC_U,   KC_I,
        KC_LSFT,        KC_SCLN,  KC_Q,    KC_J,   KC_K,   KC_X,   MO(LEDS),
        KC_LALT,        KC_GRV,   KC_NO,   KC_LEFT,KC_RGHT,
                                               KC_LCTL,KC_LGUI,
                                                              KC_HOME,
                                               KC_BSPC,KC_DEL,KC_END,
        // right hand
        TG(PLVR),       KC_6,     KC_7,    KC_8,   KC_9,   KC_0,     KC_BSLS,
        KC_NO,          KC_F,     KC_G,    KC_C,   KC_R,   KC_L,     KC_SLSH,
                        KC_D,     KC_H,    KC_T,   KC_N,   KC_S,     KC_MINS,
        TG(QWRT),       KC_B,     KC_M,    KC_W,   KC_V,   KC_Z,     KC_RSFT,
                                  KC_UP,   KC_DOWN,KC_LBRC,KC_RBRC,  KC_RALT,
        KC_RGUI,KC_RCTL,
        KC_PGUP,
        KC_PGDN,KC_ENT, KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |  KP7 |  KP8 | KP9  |  KP* |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |  KP4 |  KP5 | KP6  |  KP+ |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |  KP1 |  KP2 | KP3  |  KP/ |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |  KP. | KP0  |  KP= |      |
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
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_P7,  KC_P8,   KC_P9,   KC_PAST, KC_F12,
                KC_DOWN, KC_P4,  KC_P5,   KC_P6,   KC_PPLS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_P1,  KC_P2,   KC_P3,   KC_PSLS, KC_TRNS,
                         KC_TRNS,KC_PDOT, KC_P0,   KC_PEQL, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 3: Plover (Gemini PR over Serial)
 * Note the use of ST[1234] and S[12], which aren't really needed but
 * I wanted to see whether plover handled them. Not currently using
 * the FN key, since I have no idea what it would do. Also note
 * the non-steno arrow keys, added because they would be handy to
 * have while editing.
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | BKSPC  |   #  |   #  |   #  |   #  |   #  |      |           | Leave|   #  |   #  |   #  |   #  |   #  |   #    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   S  |   T  |   P  |   H  |   *  |      |           |      |   *  |   F  |   P  |   L  |   T  |   D    |
 * |--------+------+------+------+------+------|   *  |           |  *   |------+------+------+------+------+--------|
 * |        |   S  |   K  |   W  |   R  |   *  |------|           |------|   *  |   R  |   B  |   G  |   S  |   Z    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |   *  |           |  *   |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Left | Right|                                       |  Up  | Down |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |   A  |   O  |------|       |------|   E  |   U  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[PLVR] = LAYOUT_ergodox(
#ifdef STENO_KEYS_HIGH
       KC_BSPC, STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5, KC_NO,
       KC_NO,   STN_SN,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,STN_ST1,
       KC_NO,   STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  STN_ST2,
#else
  #ifdef STENO_KEYS_IN
       KC_BSPC, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
       KC_NO,   KC_NO,   STN_N1,  STN_N2,  STN_N3,  STN_N4, STN_ST1,
       KC_NO,   KC_NO,   STN_S1,  STN_TL,  STN_PL,  STN_HL,
       KC_NO,   KC_NO,   STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,
  #else
       KC_BSPC, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
       KC_NO,   STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5, STN_ST1,
       KC_NO,   STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,
       KC_NO,   STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_ST2,
  #endif
#endif
       KC_NO,   KC_NO,   KC_NO,   KC_LEFT, KC_RIGHT,
                                           KC_NO,   KC_NO,
                                                    KC_NO,
                                  STN_A,   STN_O,   KC_NO,
    // right hand
#ifdef STENO_KEYS_HIGH
       TG(PLVR),STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,
       STN_ST3, STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
                STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
       STN_ST4, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
#else
  #ifdef STENO_KEYS_IN
       TG(PLVR),KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       STN_ST3, STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,
                STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,  KC_NO,
       STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,  KC_NO,
  #else
       TG(PLVR),KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       STN_ST3, STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,
                STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
       STN_ST4, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
  #endif
#endif
                         KC_UP,   KC_DOWN, KC_NO,   KC_NO,   KC_NO,
       KC_NO,   KC_NO,
       KC_NO,
       KC_NO,   STN_E,   STN_U
),

/* Keymap 4: qwerty-ish
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | Esc  |           | Esc  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LGui   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |  LGui  |
 * |--------+------+------+------+------+------| Spc  |           |  L3  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Lalt |  Grv |  '"  | Left | Right|                                       |  Up  | Down |   [  |   ]  | RAlt |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | LCtrl| LAlt |       | RGui | RCtrl  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 |Backsp|Delete|------|       |------| Enter  |Space |
 *                                 |   ace|      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
[QWRT] = LAYOUT_ergodox(  // layer 4: qwerty for gaming
        // left hand
        KC_EQL,       KC_1,         KC_2,    KC_3,   KC_4,   KC_5,   KC_ESC,
        KC_TAB,       KC_Q,         KC_W,    KC_E,   KC_R,   KC_T,   TG(SYMB),
        KC_LGUI,      KC_A,         KC_S,    KC_D,   KC_F,   KC_G,
        KC_LSFT,      KC_Z,         KC_X,    KC_C,   KC_V,   KC_B,   KC_SPACE,
        KC_LALT,      KC_GRV,       KC_QUOT, KC_LEFT,KC_RGHT,
						       KC_LCTL,KC_LALT,
					                       KC_HOME,
					        KC_BSPC,KC_DEL,KC_END,
        // right hand
        KC_ESC,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,     KC_MINS,
        KC_NO,      KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,     KC_BSLS,
                    KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,  KC_QUOT,
        TG(QWRT),   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,  KC_RSFT,
                            KC_UP,  KC_DOWN,KC_LBRC,KC_RBRC,  KC_RALT,
        KC_RGUI,KC_RCTL,
        KC_PGUP,
        KC_PGDN,KC_ENT, KC_SPC
    ),
// layer 5: LED controls
[LEDS] = LAYOUT_ergodox(
       // left hand
       KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
       KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
       KC_NO,  L_MP,   L_HP,   L_SP,   L_VP,   L_ON,
       KC_NO,  L_MM,   L_HM,   L_SM,   L_VM,   L_OFF,  KC_NO,
       KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
                                       KC_NO,  KC_NO,
                                               KC_NO,
                               KC_NO,  KC_NO,  KC_NO,
       // right hand
       KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
                KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
                         KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO,   KC_NO,
       KC_NO,
       KC_NO,   KC_NO,   KC_NO
    ),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB),                // FN1 - Momentary Layer 1 (Symbols)
    [4] = ACTION_LAYER_TAP_TOGGLE(LEDS),                // FN4 - Momentary Layer 4 (LED controls)
};

#ifdef RGBLIGHT_ENABLE
static int32_t rgbmode = 25;
#endif
#ifdef I2CLCD_ENABLE
uint8_t current_brightness = 0, target_brightness = 0;
#endif
// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgbmode = rgblight_get_mode();
#endif
    steno_set_mode(STENO_MODE_GEMINI);
#ifdef I2CLCD_ENABLE
    lcd_backlight(current_brightness);
#endif
};

// static rainbow, by default
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef RGBLIGHT_ENABLE
	if (keycode >= L_MIN && keycode < L_MAX) {
		if (IS_PRESSED(record->event)) {
			switch (keycode) {
				case L_MP:
					rgbmode = (rgbmode + 1) % RGBLIGHT_MODES;
					rgblight_mode(rgbmode);
					break;
				case L_MM:
					rgbmode = (rgbmode + RGBLIGHT_MODES - 1) % RGBLIGHT_MODES;
					rgblight_mode(rgbmode);
					break;
				case L_HP:
					rgblight_increase_hue();
					break;
				case L_HM:
					rgblight_decrease_hue();
					break;
				case L_SP:
					rgblight_increase_sat();
					break;
				case L_SM:
					rgblight_decrease_sat();
					break;
				case L_VP:
					rgblight_increase_val();
					break;
				case L_VM:
					rgblight_decrease_val();
					break;
				case L_ON:
					rgblight_enable();
					break;
				case L_OFF:
					rgblight_toggle();
					break;
			}
		}
	}
#endif
	return true;
}

#ifdef I2CLCD_ENABLE
void
lcd_update_user(void) {
    if (current_brightness == target_brightness)
        return;
    if (current_brightness < target_brightness) {
        ++current_brightness;
    } else {
        --current_brightness;
    }
    lcd_backlight(current_brightness);
}
#endif

// Runs whenever there is a layer state change.
static uint8_t prev_layer = 0;
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  #ifdef I2CLCD_ENABLE
  if (layer == PLVR && prev_layer != PLVR) {
    target_brightness = 150;
    lcd_move(3, 5);
    lcd_string("PHROFR R-D", 10);
  } else {
    target_brightness = 0;
    if (prev_layer == PLVR) {
      lcd_clear();
    }
  }
  #endif
  prev_layer = layer;
  switch (layer) {
      case BASE:
	#ifdef RGBLIGHT_ENABLE
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
	#else
	  // restore defaults (which were saved in eeprom, probably)
	  rgblight_init();
        #endif
	#endif
        break;
      case SYMB:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case PLVR:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case QWRT:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case LEDS:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
      default:
        break;
    }

    return state;
};
