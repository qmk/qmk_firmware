#include "rossman360.h"

void my_custom_function(void) {

}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
switch (keycode) {
    case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
        if (!record->event.pressed) {
        uint8_t temp_mod = get_mods();
        uint8_t temp_osm = get_oneshot_mods();
        clear_mods(); clear_oneshot_mods();
        SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);
    #ifndef FLASH_BOOTLOADER
            if ((temp_mod | temp_osm) & MOD_MASK_SHIFT)
    #endif
            {
                SEND_STRING(":flash");
            }
            if ((temp_mod | temp_osm) & MOD_MASK_CTRL) {
                SEND_STRING(" -j8 --output-sync");
            }
            tap_code(KC_ENT);
            set_mods(temp_mod);
    }
    break;
	case CSPEAK:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_PGDOWN) SS_TAP(X_ENTER) SS_TAP(X_ENTER) SS_TAP(X_PGDOWN));
	}
	break;
	case SPEAK1:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_PGDOWN) SS_TAP(X_ENTER) SS_TAP(X_ENTER) SS_TAP(X_PGDOWN) SS_LCTRL(SS_TAP(X_1)));
	}
	break;
	case SPEAK2:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_PGDOWN) SS_TAP(X_ENTER) SS_TAP(X_ENTER) SS_TAP(X_PGDOWN) SS_LCTRL(SS_TAP(X_2)));
	 }
	break;
	case SPEAK3:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_PGDOWN) SS_TAP(X_ENTER) SS_TAP(X_ENTER) SS_TAP(X_PGDOWN) SS_LCTRL(SS_TAP(X_3)));
	}
	break;
	case SPEAK4:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_PGDOWN) SS_TAP(X_ENTER) SS_TAP(X_ENTER) SS_TAP(X_PGDOWN) SS_LCTRL(SS_TAP(X_4)));
	}
	break;
	case PARADOWN:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_PGDOWN) SS_TAP(X_ENTER) SS_TAP(X_PGDOWN));
	}
	break;
	case PMERGE:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_BSPACE) SS_TAP(X_SPACE) SS_LCTRL(SS_TAP(X_BSPACE)) SS_TAP(X_SPACE));
	}
	break;
	case WREFRESH:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_SPACE) SS_TAP(X_BSPACE));
	}
	break;
	case REMCAPS:
	if (record->event.pressed) {
		SEND_STRING(SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_LCTRL(SS_TAP(X_LEFT)) SS_TAP(X_DELETE));
	}
	break;
	case EMDASH:
	if (record->event.pressed) {
		SEND_STRING(SS_LCTRL(SS_LSFT(SS_TAP(X_U))) SS_TAP(X_2) SS_TAP(X_0) SS_TAP(X_1) SS_TAP(X_4) SS_TAP(X_SPACE) SS_TAP(X_SPACE));
	}
	break;
};
return true;
};
