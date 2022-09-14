#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _MTG,
		_MAC
};

enum custom_keycodes {
  pvt = SAFE_RANGE,
  endmtg,
  snap,
  copy,
  paste,
  min
};

#define ALT_TAB LALT(KC_TAB)

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
		(pvt,      paste,   KC_UP,    copy,
		KC_LSFT, KC_LEFT, KC_DOWN, KC_RGHT,
		TO(1),   KC_LCTL,   ALT_TAB,  KC_APP, KC_BTN3),
	/*
		 * ┌───┬───┬───┬───┐
		 * │mte│f5 │ up│pgu│
		 * ├───┼───┼───┤───│
		 * │snp│ lf│ dn│rt │
		 * ├───┼───┼───┼───┤───┤
		 * │[1]│mut│min│pgd│ply│
		 * ├───┴───┼───┤───│───│
		 */
	[_MTG] = LAYOUT
		(endmtg, KC_F5, KC_TRNS, KC_PGUP,
		snap,  KC_TRNS, KC_TRNS, KC_TRNS,
		TO(2), KC_MUTE,     min, KC_PGDN, KC_MPLY),
		/*
			 * ┌───┬───┬───┬───┐
			 * │mte│f5 │ up│pgu│
			 * ├───┼───┼───┤───│
			 * │snp│ lf│ dn│rt │
			 * ├───┼───┼───┼───┤───┤
			 * │[1]│mut│min│pgd│ply│
			 * ├───┴───┼───┤───│───│
			 */
	[_MAC] = LAYOUT
	 (KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		TO(0),   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
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
                  tap_code(KC_WH_D);
              } else {
                  tap_code(KC_WH_U);
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
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case endmtg:
        if (record->event.pressed) {
            // ends teams meeting
            SEND_STRING(SS_LCTL(SS_LSFT("h")));
        } else {
            // when keycode QMKURL is released
        }
        break;

    case snap:
        if (record->event.pressed) {
           SEND_STRING(SS_LGUI("sn") SS_TAP(X_ENTER) SS_LALT("n")); // opens snipping and creates new snip
        }
        break;

    case copy:
    if (record->event.pressed) {
        // ends teams meeting
        SEND_STRING(SS_LCTL("c"));
    } else {
        // when keycode QMKURL is released
    }
    break;

    case paste:
    if (record->event.pressed) {
        // ends teams meeting
        SEND_STRING(SS_LCTL("v"));
    } else {
        // when keycode QMKURL is released
    }
    break;

    case min:
    if (record->event.pressed) {
        // ends teams meeting
        SEND_STRING(SS_LGUI("m"));
    } else {
        // when keycode QMKURL is released
    }
    break;
    }
    return true;
}
