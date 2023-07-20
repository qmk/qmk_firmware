/*

#include "pattrigue_danish.c"

Add the following to the very start of process_record_user before the switch case in keymap.c:

if (!process_record_user_danish(keycode, record)) return false;

Add the following function call:

void matrix_scan_user(void) {
	 check_danish_mod_tap_timers(); 
}

And:
make moonlander:layout
*/

#include "keymap_german_mac_iso.h"

#define NUM_UMLAUTE_MOD_TAPS 1
#define TOGGLE_UMLAUTE_MOD_TAP_KEYCODE KC_F24

bool umlaute_mod_tap_enabled = true;

typedef struct {
    uint16_t timer;
    uint16_t keycode;
    bool     held;
} umlaute_mod_tap;

umlaute_mod_tap umlaute_mod_taps[NUM_UMLAUTE_MOD_TAPS] = 
{
	{.keycode = DE_UDIA},
};

void toggle_umlaute_mod_tap(void) {
    umlaute_mod_tap_enabled = !umlaute_mod_tap_enabled;
}

bool umlaute_mod_tap_key(uint16_t keycode, keyrecord_t *record, uint16_t i) {
    if (record->event.pressed) {
       umlaute_mod_taps[i].timer = timer_read();
        umlaute_mod_taps[i].held = true;
        tap_code16(keycode);
    } else {
        umlaute_mod_taps[i].held = false;
        umlaute_mod_taps[i].timer = 0;
    }
    return false;
}

void reset_umlaute_mod_taps(void) {
	for (uint16_t i = 0; i < NUM_UMLAUTE_MOD_TAPS; i++) {
		umlaute_mod_taps[i].timer = 0;
        umlaute_mod_taps[i].held = false;
    }
}

bool process_record_user_umlaute(uint16_t keycode, keyrecord_t *record) {
    if (keycode == TOGGLE_UMLAUTE_MOD_TAP_KEYCODE && record->event.pressed) {
        toggle_umlaute_mod_tap();    
    }

    if (!umlaute_mod_tap_enabled) return true;

    if (record->event.pressed) {
		reset_umlaute_mod_taps();
	}

    switch (keycode) {
		case DE_U:
			return umlaute_mod_tap_key(keycode, record, 0);
    }

    return true;
}

void check_umlaute_mod_tap_timers(void) {
    if (!umlaute_mod_tap_enabled) return;

    for (uint16_t i = 0; i < NUM_UMLAUTE_MOD_TAPS; i++) {
        if (umlaute_mod_taps[i].held) {
            if (timer_elapsed(umlaute_mod_taps[i].timer) > 500) {
                tap_code16(KC_BSPC);
                tap_code16(umlaute_mod_taps[i].keycode);

       			umlaute_mod_taps[i].timer = 0;
                umlaute_mod_taps[i].held = false;
            }
        }
    }
}