/* Copyright 2019 kratsyn
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

extern backlight_config_t backlight_config;

bool at_enable = false;
uint32_t at_clock = 0;

enum custom_keycodes {
    ALT_TAB_TICK = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALT_TAB_TICK:
            at_enable = record->event.pressed;
            if (at_enable) {
                dprintf("[ALT_TAB] Registered. (%u)\n",at_clock);
                at_clock = timer_read();
                register_code(KC_LALT);
                tap_code(KC_TAB);
            } else {
                dprintf("[ALT_TAB] Deregistered. (%u)\n",at_clock);
                unregister_code(KC_LALT);
            }
            break;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        BL_STEP,			OSL(1),		KC_MUTE,
        LCTL(LSFT(KC_ESC)), KC_UP,		ALT_TAB_TICK,
        KC_LEFT, 			KC_DOWN, 	KC_RGHT
    ),
    [1] = LAYOUT(
        BL_BRTG,	KC_ESC,		BL_TOGG,
        LGUI(KC_P), KC_PGUP,	LCA(KC_DELETE),
        EEP_RST, 	KC_PGDOWN,	RESET 
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_WH_D);
            dprintf("[ENC %u] TRUE\n",index);
        } else {
            tap_code(KC_WH_U);
            dprintf("[ENC %u] FALSE\n",index);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
            dprintf("[ENC %u] TRUE\n",index);
        } else {
            tap_code(KC_VOLD);
            dprintf("[ENC %u] FALSE\n",index);
        }
    }
}

void matrix_scan_user(void) {
    // [ALT-TAB] (send tab every 500ms until the key is released
    if (at_enable && (timer_elapsed(at_clock) > 500 )) {
        tap_code(KC_TAB);
        at_clock = timer_read();
    }
}

void keyboard_post_init_user(void) {
	debug_enable=true;
	//debug_matrix=true;
	//debug_keyboard=true;
	//debug_mouse=true;
}

void eeconfig_init_user(void) { // EEPROM Reset
	// reset the config structure
	backlight_config.raw = 0;
	backlight_init();

	dprint("[SYS] EEPROM Reset to default values.\n");
}
