// Copyright 2017, 2022 Joseph Wasson, Vladislav Kucheriavykh
// SPDX-License-Identifier: GPL-2.0-or-later

#include "process_steno.h"
#include "steno.h"
#include "progmem.h"

#ifdef STENO_ENABLE_BOLT
void steno_add_key_to_chord_bolt(uint8_t chord[MAX_STROKE_SIZE], uint8_t key);
void steno_send_chord_bolt(uint8_t chord[MAX_STROKE_SIZE]);
#endif

#ifdef STENO_ENABLE_GEMINI
void steno_add_key_to_chord_gemini(uint8_t chord[MAX_STROKE_SIZE], uint8_t key);
void steno_send_chord_gemini(uint8_t chord[MAX_STROKE_SIZE]);
#endif

// All steno keys that have been pressed to form this chord,
// stored in MAX_STROKE_SIZE groups of 8-bit arrays.
extern uint8_t chord[MAX_STROKE_SIZE];

// The number of physical keys actually being held down.
// This is not always equal to the number of 1 bits in `chord` because it is possible to
// simultaneously press down four keys, then release three of those four keys and then press yet
// another key while the fourth finger is still holding down its key.
// At the end of this scenario given as an example, `chord` would have five bits set to 1 but
// `n_pressed_keys` would be set to 2 because there are only two keys currently being pressed down.
static int8_t n_pressed_keys = 0;

#ifdef STENO_COMBINEDMAP
// Used to look up when pressing the middle row key to combine two consonant or vowel keys
static const uint16_t combinedmap_first[] PROGMEM  = {QK_STENO_S1, QK_STENO_TL, QK_STENO_PL, QK_STENO_HL, QK_STENO_FR, QK_STENO_PR, QK_STENO_LR, QK_STENO_TR, QK_STENO_DR, QK_STENO_A, QK_STENO_E};
static const uint16_t combinedmap_second[] PROGMEM = {QK_STENO_S2, QK_STENO_KL, QK_STENO_WL, QK_STENO_RL, QK_STENO_RR, QK_STENO_BR, QK_STENO_GR, QK_STENO_SR, QK_STENO_ZR, QK_STENO_O, QK_STENO_U};

static bool process_steno_combinedmap(uint16_t keycode, keyrecord_t *record) {
    uint16_t first_keycode  = pgm_read_word(&combinedmap_first[keycode - QK_STENO_S3]);
    uint16_t second_keycode = pgm_read_word(&combinedmap_second[keycode - QK_STENO_S3]);

    bool first_result  = process_steno(first_keycode, record);
    bool second_result = process_steno(second_keycode, record);
    return first_result && second_result;
}
#endif

/* override to intercept chords right before they get sent.
 * return zero to suppress normal sending behavior.
 */
__attribute__((weak)) bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[MAX_STROKE_SIZE]) {
    return true;
}

__attribute__((weak)) bool post_process_steno_user(uint16_t keycode, keyrecord_t *record, steno_mode_t mode, uint8_t chord[MAX_STROKE_SIZE], int8_t n_pressed_keys) {
    return true;
}

__attribute__((weak)) bool process_steno_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

static void steno_add_keycode_to_chord(uint16_t keycode) {
    switch (steno_get_mode()) {
#ifdef STENO_ENABLE_BOLT
        case STENO_MODE_BOLT:
            if (keycode < QK_STENO_FUNCTION || keycode > QK_STENO_ZR) {
                return;
            }

            steno_add_key_to_chord_bolt(chord, keycode - QK_STENO_FUNCTION);
            break;
#endif
#ifdef STENO_ENABLE_GEMINI
        case STENO_MODE_GEMINI:
            if (keycode < QK_STENO_FUNCTION || keycode > QK_STENO_ZR) {
                return;
            }

            steno_add_key_to_chord_gemini(chord, keycode - QK_STENO_FUNCTION);
            break;
#endif
        default:
            break;
    }
}

static void steno_send_chord(void) {
    switch (steno_get_mode()) {
#ifdef STENO_ENABLE_BOLT
        case STENO_MODE_BOLT:
            steno_send_chord_bolt(chord);
            break;
#endif
#ifdef STENO_ENABLE_GEMINI
        case STENO_MODE_GEMINI:
            steno_send_chord_gemini(chord);
            break;
#endif
        default:
            break;
    }
}

bool process_steno(uint16_t keycode, keyrecord_t *record) {
    if (!IS_STENO_KEYCODE(keycode)) {
        // Clearing or sending the chord state is not necessary as we intentionally ignore whatever
        // normal keyboard keys the user may have tapped while chording steno keys.
        return true; // pass keycode further along the chain
    }

    if (IS_NOEVENT(record->event)) {
        return true;
    }

    if (!process_steno_user(keycode, record)) {
        return false; // User fully processed the steno key themselves
    }

    switch (keycode) {
#if NUM_STENO_PROTOCOLS > 1
        case QK_STENO_MODE_NEXT:
            if (record->event.pressed) {
                steno_mode_next();
            }
            return false;

        case QK_STENO_MODE_PREVIOUS:
            if (record->event.pressed) {
                steno_mode_previous();
            }
            return false;

        case QK_STENO_MODE_BOLT:
            if (record->event.pressed) {
                steno_set_mode(STENO_MODE_BOLT);
            }
            return false;

        case QK_STENO_MODE_GEMINI:
            if (record->event.pressed) {
                steno_set_mode(STENO_MODE_GEMINI);
            }
            return false;
#endif

#ifdef STENO_COMBINEDMAP
        case QK_STENO_S3 ... QK_STENO_EU:
            return process_steno_combinedmap(keycode, record);
#endif

        case QK_STENO_FUNCTION ... QK_STENO_X26:
            if (record->event.pressed) {
                n_pressed_keys++;
                steno_add_keycode_to_chord(keycode);
                if (!post_process_steno_user(keycode, record, steno_get_mode(), chord, n_pressed_keys)) {
                    return false;
                }
            } else { // is released
                n_pressed_keys--;
                if (!post_process_steno_user(keycode, record, steno_get_mode(), chord, n_pressed_keys)) {
                    return false;
                }
                if (n_pressed_keys > 0) {
                    // User hasn't released all keys yet,
                    // so the chord cannot be sent
                    return false;
                }
                n_pressed_keys = 0;
                if (!send_steno_chord_user(steno_get_mode(), chord)) {
                    steno_clear_chord();
                    return false;
                }
                steno_send_chord();
                steno_clear_chord();
            }
            return false;
        default:
            break;
    }

    return true;
}
