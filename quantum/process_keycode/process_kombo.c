/* Copyright 2019 Bence Domonkos
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

#ifdef KOMBO_ENABLE

#include "process_kombo.h"

extern kombo_t key_kombos[];
uint64_t static kombo_key_state = 0;
uint16_t static key_buffer[64];
uint16_t static kombo_hkey = KC_NO;
size_t static n_buffer = 0;
bool static kombo_is_enabled = true;

// should be specific for every other keyboard matrices
// should return a number between 0-63 (inclusive) for kombo keys and -1 for the others
extern int8_t
kombo_get_pos(uint8_t row, uint8_t col);

__attribute__ ((weak))
bool
process_kombo_event(size_t kombo_index, keypos_t pos) {
	return true;
}

static void
kombo_init(void) {
	n_buffer = 0;
	kombo_key_state = 0;
	kombo_hkey = KC_NO;
}

void
kombo_toggle(void) {
	kombo_is_enabled ? kombo_disable() : kombo_enable();
}

void
kombo_enable(void) {
	kombo_is_enabled = true;
	kombo_init();
}

void
kombo_disable(void) {
	if (kombo_hkey != KC_NO)
		unregister_code16(kombo_hkey);
	kombo_is_enabled = false;
	kombo_init();
}

static void
flush(void) {
	for (size_t i = 0; i < n_buffer; i++) {
		tap_code16(key_buffer[i]);
	}
	kombo_init();
}

bool
process_kombo(uint16_t keycode, keyrecord_t *record) {
	if (!kombo_is_enabled)
		return true;

	int8_t pos = kombo_get_pos(record->event.key.row, record->event.key.col);
	uint64_t pos_mask = 1ULL << pos;
	size_t static kombo_just_triggered = ~0;

	if (record->event.pressed
	|| (kombo_hkey != KC_NO && key_kombos[kombo_just_triggered].keys & pos_mask)) {
		unregister_code16(kombo_hkey);
		kombo_hkey = KC_NO;
	}

	if (pos < 0) {
		flush();
		return true;
	}

	if (record->event.pressed) {
		bool is_key_in_kombo = false;

		kombo_just_triggered = ~0;
		kombo_key_state |= pos_mask;
		for (size_t i = 0; key_kombos[i].keys != 0; i++) {
			if (((~key_kombos[i].keys & kombo_key_state) == 0)
			&& ((key_kombos[i].keys | kombo_key_state) == key_kombos[i].keys)) {
				is_key_in_kombo = true;
			}
			if (key_kombos[i].keys == kombo_key_state) {
				if (!process_kombo_event(i, record->event.key)) {
					n_buffer = 0;
					if (key_kombos[i].is_instant)
						kombo_key_state &= ~pos_mask;
					return false;
				}
				if (key_kombos[i].is_instant) {
					register_code16(key_kombos[i].keycode);
					kombo_hkey = key_kombos[i].keycode;
					n_buffer = 0;
					kombo_key_state &= ~pos_mask;
				} else {
					key_buffer[n_buffer++] = keycode;
				}
				kombo_just_triggered = i;
				return false;
			}
		}

		if (is_key_in_kombo) {
			key_buffer[n_buffer++] = keycode;
			return false;
		} else {
			flush();
		}
	} else {
		kombo_key_state &= ~pos_mask;
		if (kombo_just_triggered == ~0) {
			flush();
		} else {
			if (!key_kombos[kombo_just_triggered].is_instant) {
				tap_code16(key_kombos[kombo_just_triggered].keycode);
				n_buffer = 0;
				kombo_just_triggered = ~0;
			}
		}
	}

	return true;
}

#endif
