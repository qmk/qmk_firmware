#include QMK_KEYBOARD_H

enum custom_keycodes {
    abbette = SAFE_RANGE,
    parens,
    brackets,
};

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS, MO(2), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_ENT, KC_ENT, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, KC_LCTL, KC_LALT, KC_LGUI, KC_BSPC, KC_SPC, MO(1), KC_RGUI, brackets),
    [1] = LAYOUT(KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_BSLS, KC_NO, KC_UP, KC_NO, KC_VOLD, KC_VOLU, KC_RBRC, KC_NO, KC_UP, KC_NO, KC_PGUP, KC_F12, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_MRWD, KC_MFFD, KC_LBRC, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPLY, KC_TRNS, OSL(3), LCAG(KC_M), KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SPC, KC_DEL, KC_TRNS, KC_TRNS, parens),
    [2] = LAYOUT(KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NLCK, KC_P7, KC_P8, KC_P9, KC_PSLS, KC_PEQL, KC_CAPS, abbette, KC_UP, KC_NO, KC_VOLD, KC_VOLU, KC_PPLS, KC_P4, KC_P5, KC_P6, KC_PSLS, KC_PEQL, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_MRWD, KC_MFFD, KC_PPLS, KC_P1, KC_P2, KC_P3, KC_PAST, KC_PEQL, OSL(3), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPLY, KC_PENT, KC_PPLS, KC_P0, KC_P0, KC_PDOT, KC_PAST, KC_TRNS, KC_TRNS, KC_TRNS, SGUI(LALT(KC_V)), KC_SPC, KC_DEL, KC_PMNS, KC_PMNS, KC_PMNS),
    [3] = LAYOUT(KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LCAG(KC_1), LCAG(KC_2), LCAG(KC_3), LCAG(KC_4), KC_NO, LCAG(KC_PLUS), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LCAG(KC_C), LCAG(KC_P), LCAG(KC_UP), LCAG(KC_N), KC_NO, LCAG(KC_MINS), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LCAG(KC_LEFT), LCAG(KC_DOWN), LCAG(KC_RGHT), KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, EEP_RST, EEP_RST, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};


//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
      if (!is_keyboard_master())
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
      return rotation;
    }

    // When you add source files to SRC in rules.mk, you can use functions.
    const char *read_layer_state(void);
    const char *read_logo(void);
    void set_keylog(uint16_t keycode, keyrecord_t *record);
    const char *read_keylog(void);
    const char *read_keylogs(void);
    // const char *read_mode_icon(bool swap);
    // const char *read_host_led_state(void);
    // void set_timelog(void);
    // const char *read_timelog(void);

    void oled_task_user(void) {
      if (is_keyboard_master()) {
        // If you want to change the display of OLED, you need to change here
        oled_write_ln(read_layer_state(), false);
        oled_write_ln(read_keylog(), false);
        oled_write_ln(read_keylogs(), false);
        //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
        //oled_write_ln(read_host_led_state(), false);
        //oled_write_ln(read_timelog(), false);
      } else {
        oled_write(read_logo(), false);
        // oled_scroll_left();  // Turns on scrolling
      }
    }


#endif // OLED_DRIVER_ENABLE

    bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        #ifdef OLED_DRIVER_ENABLE
            set_keylog(keycode, record);
        #endif
            // set_timelog();
    }

    switch (keycode) {
    case abbette:
        if (record->event.pressed) {
            // when keycode is pressed
            SEND_STRING("Gargoylemobil");
        } else {
            // when keycode is released
        }
        break;
    case parens:
        if (record->event.pressed) {
            // when keycode is pressed
            SEND_STRING("()"SS_TAP(X_LEFT));
        } else {
            // when keycode is released
        }
        break;
    case brackets:
        if (record->event.pressed) {
            // when keycode is pressed
            SEND_STRING("[]"SS_TAP(X_LEFT));
        } else {
            // when keycode is released
        }
        break;
    }
    return true;
};