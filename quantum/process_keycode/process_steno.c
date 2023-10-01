/* Copyright 2017, 2022 Joseph Wasson, Vladislav Kucheriavykh
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
#include "process_steno.h"
#include "quantum_keycodes.h"
#include "eeconfig.h"
#include "keymap_steno.h"
#include <string.h>
#ifdef VIRTSER_ENABLE
#    include "virtser.h"
#endif
#ifdef STENO_ENABLE_ALL
#    include "eeprom.h"
#endif

// All steno keys that have been pressed to form this chord,
// stored in MAX_STROKE_SIZE groups of 8-bit arrays.
static uint8_t chord[MAX_STROKE_SIZE] = {0};
// The number of physical keys actually being held down.
// This is not always equal to the number of 1 bits in `chord` because it is possible to
// simultaneously press down four keys, then release three of those four keys and then press yet
// another key while the fourth finger is still holding down its key.
// At the end of this scenario given as an example, `chord` would have five bits set to 1 but
// `n_pressed_keys` would be set to 2 because there are only two keys currently being pressed down.
static int8_t n_pressed_keys = 0;

#ifdef STENO_ENABLE_ALL
static steno_mode_t mode;
#elif defined(STENO_ENABLE_GEMINI)
static const steno_mode_t mode = STENO_MODE_GEMINI;
#elif defined(STENO_ENABLE_BOLT)
static const steno_mode_t mode = STENO_MODE_BOLT;
#endif

static inline void steno_clear_chord(void) {
    memset(chord, 0, sizeof(chord));
}

#ifdef STENO_ENABLE_GEMINI

#    ifdef VIRTSER_ENABLE
void send_steno_chord_gemini(void) {
    // Set MSB to 1 to indicate the start of packet
    chord[0] |= 0x80;
    for (uint8_t i = 0; i < GEMINI_STROKE_SIZE; ++i) {
        virtser_send(chord[i]);
    }
}
#    else
#        pragma message "VIRTSER_ENABLE = yes is required for Gemini PR to work properly out of the box!"
#    endif // VIRTSER_ENABLE

/**
 * @precondition: `key` is pressed
 */
bool add_gemini_key_to_chord(uint8_t key) {
    // Although each group of the packet is 8 bits long, the MSB is reserved
    // to indicate whether that byte is the first byte of the packet (MSB=1)
    // or one of the remaining five bytes of the packet (MSB=0).
    // As a consequence, only 7 out of the 8 bits are left to be used as a bit array
    // for the steno keys of that group.
    const int group_idx       = key / 7;
    const int intra_group_idx = key - group_idx * 7;
    // The 0th steno key of the group has bit=0b01000000, the 1st has bit=0b00100000, etc.
    const uint8_t bit = 1 << (6 - intra_group_idx);
    chord[group_idx] |= bit;
    return false;
}
#endif // STENO_ENABLE_GEMINI

#ifdef STENO_ENABLE_BOLT

#    define TXB_GRP0 0b00000000
#    define TXB_GRP1 0b01000000
#    define TXB_GRP2 0b10000000
#    define TXB_GRP3 0b11000000
#    define TXB_GRPMASK 0b11000000

#    define TXB_GET_GROUP(code) ((code & TXB_GRPMASK) >> 6)

static const uint8_t boltmap[64] PROGMEM = {TXB_NUL, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_S_L, TXB_S_L, TXB_T_L, TXB_K_L, TXB_P_L, TXB_W_L, TXB_H_L, TXB_R_L, TXB_A_L, TXB_O_L, TXB_STR, TXB_STR, TXB_NUL, TXB_NUL, TXB_NUL, TXB_STR, TXB_STR, TXB_E_R, TXB_U_R, TXB_F_R, TXB_R_R, TXB_P_R, TXB_B_R, TXB_L_R, TXB_G_R, TXB_T_R, TXB_S_R, TXB_D_R, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_Z_R};

#    ifdef VIRTSER_ENABLE
static void send_steno_chord_bolt(void) {
    for (uint8_t i = 0; i < BOLT_STROKE_SIZE; ++i) {
        // TX Bolt uses variable length packets where each byte corresponds to a bit array of certain keys.
        // If a user chorded the keys of the first group with keys of the last group, for example, there
        // would be bytes of 0x00 in `chord` for the middle groups which we mustn't send.
        if (chord[i]) {
            virtser_send(chord[i]);
        }
    }
    // Sending a null packet is not always necessary, but it is simpler and more reliable
    // to unconditionally send it every time instead of keeping track of more states and
    // creating more branches in the execution of the program.
    virtser_send(0);
}
#    else
#        pragma message "VIRTSER_ENABLE = yes is required for TX Bolt to work properly out of the box!"
#    endif // VIRTSER_ENABLE

/**
 * @precondition: `key` is pressed
 */
static bool add_bolt_key_to_chord(uint8_t key) {
    uint8_t boltcode = pgm_read_byte(boltmap + key);
    chord[TXB_GET_GROUP(boltcode)] |= boltcode;
    return false;
}
#endif // STENO_ENABLE_BOLT

#ifdef STENO_COMBINEDMAP
/* Used to look up when pressing the middle row key to combine two consonant or vowel keys */
static const uint16_t combinedmap_first[] PROGMEM  = {STN_S1, STN_TL, STN_PL, STN_HL, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR, STN_A, STN_E};
static const uint16_t combinedmap_second[] PROGMEM = {STN_S2, STN_KL, STN_WL, STN_RL, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR, STN_O, STN_U};
#endif

#ifdef STENO_ENABLE_ALL
void steno_init(void) {
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    mode = eeprom_read_byte(EECONFIG_STENOMODE);
}

void steno_set_mode(steno_mode_t new_mode) {
    steno_clear_chord();
    mode = new_mode;
    eeprom_update_byte(EECONFIG_STENOMODE, mode);
}
#endif // STENO_ENABLE_ALL

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

bool process_steno(uint16_t keycode, keyrecord_t *record) {
    if (keycode < QK_STENO || keycode > QK_STENO_MAX) {
        return true; // Not a steno key, pass it further along the chain
        /*
         * Clearing or sending the chord state is not necessary as we intentionally ignore whatever
         * normal keyboard keys the user may have tapped while chording steno keys.
         */
    }
    if (IS_NOEVENT(record->event)) {
        return true;
    }
    if (!process_steno_user(keycode, record)) {
        return false; // User fully processed the steno key themselves
    }
    switch (keycode) {
#ifdef STENO_ENABLE_ALL
        case QK_STENO_BOLT:
            if (record->event.pressed) {
                steno_set_mode(STENO_MODE_BOLT);
            }
            return false;

        case QK_STENO_GEMINI:
            if (record->event.pressed) {
                steno_set_mode(STENO_MODE_GEMINI);
            }
            return false;
#endif // STENO_ENABLE_ALL

#ifdef STENO_COMBINEDMAP
        case QK_STENO_COMB ... QK_STENO_COMB_MAX: {
            bool first_result  = process_steno(combinedmap_first[keycode - QK_STENO_COMB], record);
            bool second_result = process_steno(combinedmap_second[keycode - QK_STENO_COMB], record);
            return first_result && second_result;
        }
#endif // STENO_COMBINEDMAP
        case STN__MIN ... STN__MAX:
            if (record->event.pressed) {
                n_pressed_keys++;
                switch (mode) {
#ifdef STENO_ENABLE_BOLT
                    case STENO_MODE_BOLT:
                        add_bolt_key_to_chord(keycode - QK_STENO);
                        break;
#endif // STENO_ENABLE_BOLT
#ifdef STENO_ENABLE_GEMINI
                    case STENO_MODE_GEMINI:
                        add_gemini_key_to_chord(keycode - QK_STENO);
                        break;
#endif // STENO_ENABLE_GEMINI
                    default:
                        return false;
                }
                if (!post_process_steno_user(keycode, record, mode, chord, n_pressed_keys)) {
                    return false;
                }
            } else { // is released
                n_pressed_keys--;
                if (!post_process_steno_user(keycode, record, mode, chord, n_pressed_keys)) {
                    return false;
                }
                if (n_pressed_keys > 0) {
                    // User hasn't released all keys yet,
                    // so the chord cannot be sent
                    return false;
                }
                n_pressed_keys = 0;
                if (!send_steno_chord_user(mode, chord)) {
                    steno_clear_chord();
                    return false;
                }
                switch (mode) {
#if defined(STENO_ENABLE_BOLT) && defined(VIRTSER_ENABLE)
                    case STENO_MODE_BOLT:
                        send_steno_chord_bolt();
                        break;
#endif // STENO_ENABLE_BOLT && VIRTSER_ENABLE
#if defined(STENO_ENABLE_GEMINI) && defined(VIRTSER_ENABLE)
                    case STENO_MODE_GEMINI:
                        send_steno_chord_gemini();
                        break;
#endif // STENO_ENABLE_GEMINI && VIRTSER_ENABLE
                    default:
                        break;
                }
                steno_clear_chord();
            }
            break;
    }
    return false;
}
