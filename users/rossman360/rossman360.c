#include "rossman360.h"

void my_custom_function(void) {

}

#define PGMOD LT(_NUM, KC_PGDN)
#define TABMOD LT(_FN1, KC_TAB)
#define SPCMOD LT(_FN1, KC_SPACE)
#define ENTMOD LT(_FN2, KC_ENTER)
#define ESCMOD LT(_NUM, KC_ESC)
#define RSMOD LT(_FN1, KC_RSHIFT)
#define CMDBSP MT(MOD_LGUI, KC_BSPC)
#define ALTDEL MT(MOD_LALT, KC_DEL)
#define CTRLSP MT(MOD_LCTL, KC_SPACE)
#define BWORD LCTL(KC_BSPC)
#define JUMPBACK LSFT(KC_TAB)
#define LWORD LCTL(KC_LEFT)
#define RWORD LCTL(KC_RIGHT)
#define UNDO LCTL(KC_Z)
#define NTAB LCTL(KC_T)
#define CTAB LCTL(KC_W)
#define XPANDR LCTL(LSFT(KC_X))
#define TAB1 LCTL(KC_1)
#define TAB2 LCTL(KC_2)
#define TAB3 LCTL(KC_3)
#define TAB4 LCTL(KC_4)
#define RVOLU LCTL(KC_RBRC)
#define RVOLD LCTL(KC_LBRC)

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
};
return true;
};
