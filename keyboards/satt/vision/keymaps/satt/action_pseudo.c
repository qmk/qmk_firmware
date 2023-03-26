/* Copyright 2020 shela
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

#include "quantum.h"
#include "command.h"
#include "action_pseudo.h"

static uint8_t send_key_shift_bit[SHIFT_BIT_SIZE];

/*
 * Action Pseudo Process.
 * Gets the keycode in the same position of the specified layer.
 * The keycode is sent after conversion according to the conversion keymap.
 */
void action_pseudo_process(keyrecord_t *record, uint8_t base_layer, const uint16_t (*keymap)[2]) {
    uint8_t  prev_shift;
    uint16_t keycode;
    uint16_t pseudo_keycode;

    /* Get keycode from specified layer */
    keycode = keymap_key_to_keycode(base_layer, record->event.key);

    prev_shift = get_mods() & MOD_MASK_SHIFT;

    if (record->event.pressed) {
        /* If magic commands entered, keycode is not converted */
        if (IS_COMMAND()) {
            if (prev_shift) {
                add_shift_bit(keycode);
            }
            register_code(keycode);
            return;
        }

        if (prev_shift) {
            pseudo_keycode = convert_keycode(keymap, keycode, true);
            dprintf("pressed: %02X, converted: %04X\n", keycode, pseudo_keycode);
            add_shift_bit(keycode);

            if (IS_LSFT(pseudo_keycode)) {
                register_code(QK_LSFT ^ pseudo_keycode);
            } else {
                /* Delete shift mod temporarily */
                unregister_mods(prev_shift);
                register_code(pseudo_keycode);
                register_mods(prev_shift);
            }
        } else {
            pseudo_keycode = convert_keycode(keymap, keycode, false);
            dprintf("pressed: %02X, converted: %04X\n", keycode, pseudo_keycode);

            if (IS_LSFT(pseudo_keycode)) {
                register_weak_mods(MOD_LSFT);
                register_code(QK_LSFT ^ pseudo_keycode);
                /* Prevent key repeat to avoid unintended output on Windows */
                unregister_code(QK_LSFT ^ pseudo_keycode);
                unregister_weak_mods(MOD_LSFT);
            } else {
                register_code(pseudo_keycode);
            }
        }
    } else {
        if (get_shift_bit(keycode)) {
            del_shift_bit(keycode);
            pseudo_keycode = convert_keycode(keymap, keycode, true);
        } else {
            pseudo_keycode = convert_keycode(keymap, keycode, false);
        }
        dprintf("released: %02X, converted: %04X\n", keycode, pseudo_keycode);

        if (IS_LSFT(pseudo_keycode)) {
            unregister_code(QK_LSFT ^ pseudo_keycode);
        } else {
            unregister_code(pseudo_keycode);
        }
    }
}

/* Convert keycode according to the keymap */
uint16_t convert_keycode(const uint16_t (*keymap)[2], uint16_t keycode, bool shift_modded) {
    uint16_t pseudo_keycode = 0x00; /* default value */

    switch (keycode) {
        case KC_A ... KC_CAPS_LOCK:
#if defined(__AVR__)
            if (shift_modded) {
                pseudo_keycode = pgm_read_word(&keymap[keycode][1]);
            } else {
                pseudo_keycode = pgm_read_word(&keymap[keycode][0]);
            }
#else
            if (shift_modded) {
                pseudo_keycode = keymap[keycode][1];
            } else {
                pseudo_keycode = keymap[keycode][0];
            }
#endif
            break;
    }

    /* If pseudo keycode is the default value, use the keycode as it is */
    if (pseudo_keycode == 0x00) {
        if (shift_modded) {
            pseudo_keycode = S(keycode);
        } else {
            pseudo_keycode = keycode;
        }
    }

    return pseudo_keycode;
}

uint8_t get_shift_bit(uint16_t keycode) {
    if ((keycode >> 3) < SHIFT_BIT_SIZE) {
        return send_key_shift_bit[keycode >> 3] & (1 << (keycode & 7));
    } else {
        dprintf("get_shift_bit: Can't get shift bit. keycode: %02X\n", keycode);
        return 0;
    }
}

void add_shift_bit(uint16_t keycode) {
    if ((keycode >> 3) < SHIFT_BIT_SIZE) {
        send_key_shift_bit[keycode >> 3] |= (1 << (keycode & 7));
    } else {
        dprintf("add_shift_bit: Can't add shift bit. keycode: %02X\n", keycode);
    }
}

void del_shift_bit(uint16_t keycode) {
    if ((keycode >> 3) < SHIFT_BIT_SIZE) {
        send_key_shift_bit[keycode >> 3] &= ~(1 << (keycode & 7));
    } else {
        dprintf("del_shift_bit: Can't delete shift bit. keycode: %02X\n", keycode);
    }
}
