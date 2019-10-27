/*
 *           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 * Copyright (C) 2019 4sStylZ <4sstylz@protonmail.ch>
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */
#include QMK_KEYBOARD_H

/**
 * Macro for selecting all the text in the document.
 * Usual shortcut : Ctrl+A.
 *
 * @param keyrecord_t *record
 *
 * @return void
 */
void select_all(keyrecord_t *record) {
    if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_A);
        unregister_code(KC_LCTL);
    }
}

/**
 * Macro for selecting the current row.
 *
 * @param keyrecord_t *record
 *
 * @return void
 */
void select_row(keyrecord_t *record) {
    if (record->event.pressed) {
        tap_code(KC_HOME);
        register_code(KC_LSFT);
        tap_code(KC_END);
        unregister_code(KC_LSFT);
    }
}

/**
 * Macro for selecting the current word.
 * Usage : You need to have the cursor into the word or directly at the right.
 *
 *
 * Usual shortcut : Ctrl+A.
 *
 * @param keyrecord_t *record
 *
 * @return void
 */
void select_word(keyrecord_t *record) {
    if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_LEFT);
        register_code(KC_LSFT);
        tap_code(KC_RIGHT);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
    }
}

/**
 * Macro for inserting two 0 with keypad.
 * Be carefull to have the keypad lock enabled
 *
 * @param keyrecord_t *record
 *
 * @return void
 */
void insert_00(keyrecord_t *record) {
    if (record->event.pressed) {
        register_code(KC_LSFT);
        tap_code(KC_0);
        tap_code(KC_0);
        unregister_code(KC_LSFT);
    }
}

/**
 * Bépo Windows lock
 *
 * @param keyrecord_t *record
 *
 * @return void
 */
void windows_lock(void) {
    register_code(KC_LGUI);
    tap_code(KC_O);
    unregister_code(KC_LGUI);
}

