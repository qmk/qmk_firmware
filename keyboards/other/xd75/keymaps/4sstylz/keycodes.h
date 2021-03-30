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
        tap_code16(C(KC_A));
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
        tap_code16(S(KC_END));
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
        tap_code16(S(KC_RGHT));
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
        tap_code16(S(KC_0));
        tap_code16(S(KC_0));
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
    tap_code16(G(KC_O));
}
