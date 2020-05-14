/* Copyright 2020 Eye Oh Designs
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
//#include S50_H
// Defines the keycodes used by our macros in process_record_user

#define ______ KC_TRNS
#define QWERTY 0
#define RAISE 1
#define NUMBRS 2
enum custom_keycodes { QMKBEST = SAFE_RANGE, QMKURL };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	    [QWERTY] = ISO_Right_Num(
	     
	/* Layer 0
     * ,____.      ,---------------------------------------------------------------------.
     * |Knob|      | Esc| Q  | W  | E  | R  | T  | Y  | U  | I  | O  | P  | 7  | 8  |  9 |
     * `----'     ,-----+----+----+----+----+----+----+----+----+----+----|----+----|----|
     *            |Tb   | A  | S  | D  | F  | G  | H  | J  | K  | L  | ;  | 4  | 5  |  6 |
     *       ,----------+----+----+----+----+----+----+----+----+----+----+----+----+----|
     *       |  \ |Shift| Z  | X  | C  | V  | B  | N  | M  | ,  | .  | /  | 1  | 2  |  3 |
     *      ,-----+-----+---------+----+----+----+----+----+----+----+----+----+----+----|
     *       CTL-OS| Alt |Raise|            Space /NUMBRS    | Raise |Ctrl|Del |    0    |
     *      `----------------------------------------------------------------------------'
	 */
	 
                        KC_ESC,       KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,   KC_O,   KC_P,    KC_7, KC_8, KC_9, \
KC_MUTE,                                                                                                                   \
				    KC_TAB,           KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,   KC_L,   KC_SCLN, KC_4, KC_5, KC_6, \
                                                                                                                           \
		       KC_BSLS,SFT_T(KC_CAPS),KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM,KC_DOT, KC_SLSH, KC_1, KC_2, KC_3, \
                                                                                                                           \
               KC_LGUI,  KC_LALT,KC_LCTL,      MO(RAISE),           LT(NUMBRS,KC_SPC),           KC_RCTL,KC_BSPC,  KC_0    \
),

	[RAISE] = ISO_Right_Num(
	/* Layer 1
     * ,____.      ,---------------------------------------------------------------------.
     * |Knob|      | `  |    |    |PgUp|    |  - |  = |    | Up |    |PSCR|    |    |    |
     * `----'     ,-----+----+----+----+----+----+----+----+----+----+----|----+----|----|
     *            |     |    |Home|PgDn|End |  [ | ]  |Left|Down|Rght| '  |Ent |ASON|ASUP|
     *       ,----------+----+----+----+----+----+----+----+----+----+----+----+----+----|
     *       |          |    |    |    |    |    |    |    |    |    |  \ |    |ASOF|ASDN|
     *      ,-----+-----+---------+----+----+----+----+----+----+----+----+----+----+----|
     *      | OS  | Ctrl| Alt |                             |       | Ctrl| Del| BL STEP |
     *      `----------------------------------------------------------------------------'
     */
                      KC_GRAVE,______,______,KC_PGUP, ______,  KC_LBRC,KC_RBRC,______,KC_UP,______,KC_PSCR,______,______,______,\
RESET,                                                                                                                          \
				   ______,______,KC_HOME,KC_PGDN,KC_END,KC_MINS,KC_EQL, KC_LEFT,KC_DOWN,KC_RIGHT,KC_QUOT,KC_ENT,KC_ASON,KC_ASUP,\
                                                                                                                                \
				 ______,______,______,______,______,______,______,______,______, ______,______,KC_BSLS,  ______,KC_ASOFF, KC_ASDN,\
                                                                                                                                \
		KC_LGUI,  KC_LALT,   KC_LCTL,                      ______,                     ______,  KC_RCTL, KC_DEL,      BL_STEP    \
),
	[NUMBRS] = ISO_Right_Num(
	/* Layer 2
     * ,____.      ,---------------------------------------------------------------------.
     * |Knob|      | F1 | F2 | F3 | F4 | F5 | F6 | F7 | F8 | F9 | F10| F11|F12 |    |    |
     * `----'     ,-----+----+----+----+----+----+----+----+----+----+----|----+----|----|
     *            |     | 1  | 2  | 3  | 4  | 5  | 6  | 7  |  8 | 9  | 0  |    |    |    |
     *       ,----------+----+----+----+----+----+----+----+----+----+----+----+----+----|
     *       |          | !  | @  | #  |  $ | %  | ^  | &  |  * | (  | )  |    |    |    |
     *      ,-----+-----+---------+----+----+----+----+----+----+----+----+----+----+----|
     *      | OS  | Ctrl| Alt |                             |       | Ctrl|    |    |    |
     *      `----------------------------------------------------------------------------'
     */  
                      KC_F1,    KC_F2,   KC_F3, KC_F4,   KC_F5,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12,______,______,\
RESET,                                                                                                                                     \
				     KC_TAB,    KC_1,    KC_2 , KC_3 ,   KC_4 ,  KC_5 ,   KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 ,  ______,______,______,\
                                                                                                                                           \
				   ______,______,KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,______,______,______,\
                                                                                                                                           \
		        KC_LGUI,  KC_LALT,   KC_LCTL,                      ______,                     ______,  KC_RCTL,      ______,    ______    \
)
};

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

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {}

void encoder_update_user(uint8_t index, bool clockwise) {
 if (index == 0) {
	 if (clockwise) {
  register_code(KC_VOLU);
  unregister_code(KC_VOLU);
 }  else{
	register_code (KC_VOLD);
	unregister_code(KC_VOLD);
 }
 }
}
