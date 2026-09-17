// Copyright 2022 bwprobably
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum layer_names {
    _BASE,
    _MTG,
    _MAC
};

enum custom_keycodes {
  pvt = SAFE_RANGE,
  snap,
  ALT_TAB
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/*
     * ┌───┬───┬───┬───┐
     * │pvt│pst│ up│cpy│
     * ├───┼───┼───┤───│
     * │sft│ lf│ dn│rt │
     * ├───┼───┼───┼───┤───┤
     * │[1]│ctr│wtb│app│bt3│
     * ├───┴───┼───┤───│───│
     */
	[_BASE] = LAYOUT
		(pvt, LCTL(KC_V), KC_UP, LCTL(KC_C),
		LSFT_T(KC_ESC), KC_LEFT, KC_DOWN, KC_RGHT,
		TO(1),   KC_LCTL,   ALT_TAB,  KC_APP, MS_BTN3),
	/*
		 * ┌────┬────┬────┬────┐
		 * │mte │ BI │ up │pgu │
		 * ├────┼────┼────┤────│
		 * │snp │ lf │ dn │ rt │
		 * ├────┼────┼────┼────┤───┤
		 * │[1] │mut │min │pgd │ply│
		 * ├────┴────┼────┤────│───│
		 */
	[_MTG] = LAYOUT (
		LCTL(LSFT(KC_H)), LCTL(KC_F6), KC_TRNS, KC_PGUP,
		snap,  KC_TRNS, KC_TRNS, KC_TRNS,
		TO(2), KC_MUTE, LGUI(KC_M), KC_PGDN, KC_MPLY),
		/*
			 * ┌────┬────┬────┬────┐
			 * │sdbr│past│ up │ cpy│
			 * ├────┼────┼────┤────│
			 * │snp │ lf │ dn │ rt │
			 * ├────┼────┼────┤─────│────┤
			 * │[1] |qkfl│ min│focus│ ply│
			 * ├────┴────┼────┤─────│────│
			 */
	[_MAC] = LAYOUT (
	 LSFT(LGUI(KC_L)), LGUI(KC_V), KC_TRNS, LGUI(KC_C),
		LGUI(LCTL(LSFT(KC_4))), KC_TRNS, KC_TRNS, KC_TRNS,
		TO(0),   LSFT(LGUI(KC_O)), LCTL(LALT(KC_F3)), LCTL(LSFT(KC_1)), KC_TRNS)
};


bool encoder_update_user(uint8_t index, bool clockwise) {
      if (IS_LAYER_ON(_MTG)) {
              if (clockwise) {
                  tap_code(KC_VOLU);
              } else {
                  tap_code16(S(KC_VOLD));
              }
          } else {
              if (clockwise) {
                  tap_code(MS_WHLD);
              } else {
                  tap_code(MS_WHLU);
              }
          }
          return false;
      }



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
    case pvt:
        if (record->event.pressed) {
            // creates pivot table in excel
            SEND_STRING(SS_LALT("nvt"));
        }
        break;
    case snap:
        if (record->event.pressed) {
           SEND_STRING(SS_TAP(X_LGUI)SS_DELAY(500)"snip"SS_DELAY(500)SS_TAP(X_ENTER)SS_LALT("n")); // opens snipping and creates new snip
        }
        break;

    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    }
    return true;
}

void housekeeping_task_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}
