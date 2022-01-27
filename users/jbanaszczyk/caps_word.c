#include "quantum.h"
#include <deferred_exec.h>
#include "caps_word.h"
#include "jbanaszczyk_keycodes.h"

static bool is_caps_word_on = false;

bool is_caps_word_enabled(void) {
	if (is_caps_word_on) {
		led_t led_state = (led_t)host_keyboard_leds();
		is_caps_word_on = led_state.caps_lock;
	}
	return is_caps_word_on;
}

void caps_word_enable(void) {
	if (is_caps_word_enabled()) {
		return;
	}
	dprintf("caps_word_enable\n");
	is_caps_word_on = true;
	tap_code(KC_CAPS_LOCK);
}

void caps_word_disable(void) {
	if (!is_caps_word_enabled()) {
		return;
	}
	dprintf("caps_word_disable\n");
	is_caps_word_on = false;
	tap_code(KC_CAPS_LOCK);
}

void caps_word_toggle(void) {
	is_caps_word_enabled()
	? caps_word_disable()
	: caps_word_enable();
}

bool should_terminate_caps_word(uint16_t keycode, const keyrecord_t *record) {
	if (!record->event.pressed) {
		return false;
	}

	switch (keycode) {
		case QK_MOD_TAP          ... QK_MOD_TAP_MAX:
		case QK_LAYER_TAP        ... QK_LAYER_TAP_MAX:
		case QK_TAP_DANCE        ... QK_TAP_DANCE_MAX:
		case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX: {
			if (record->tap.count==0)
				return false;
		}
	}

	switch (keycode) {
		case QK_LAYER_TAP      ... QK_LAYER_TAP_MAX:
		case QK_TO             ... QK_TO_MAX:
		case QK_MOMENTARY      ... QK_MOMENTARY_MAX:
		case QK_DEF_LAYER      ... QK_DEF_LAYER_MAX:
		case QK_TOGGLE_LAYER   ... QK_TOGGLE_LAYER_MAX:
		case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
		case QK_ONE_SHOT_MOD   ... QK_ONE_SHOT_MOD_MAX:
		case QK_LAYER_MOD      ... QK_LAYER_MOD_MAX: {
			return false;
		}
	}

	uint16_t mod = (keycode >> 8) & 0x1F;
	keycode = keycode & 0xFF;

	switch (mod) {
		case 0:
		case MOD_LSFT:
		case MOD_RSFT:
		case MOD_RALT: {
			break;
		}
		default: {
			return false;
		}
	}

	switch (keycode) {
		case KC_CAPS:
		case KC_LSFT:
		case KC_RSFT:
		case KC_RALT:
		case KC_A  ... KC_Z:
		case KC_1  ... KC_0:
		case KC_P1 ... KC_P0:
		case KC_UNDS:
		case KC_BSPC:
		case KC_INS:
		case KC_DEL:
		case KC_LEFT:
		case KC_RGHT: {
			return false;
		}
	}
	return true;
}

bool process_record_caps_word(uint16_t keycode, const keyrecord_t *record) {

	if (!record->event.pressed) {
		return true;
	}

	if (keycode==KC_CAPS_WORD) {
		caps_word_toggle();
		return false;
	}

	if (is_caps_word_enabled() && should_terminate_caps_word(keycode, record)) {
		caps_word_disable();
	}

	return true;
}
