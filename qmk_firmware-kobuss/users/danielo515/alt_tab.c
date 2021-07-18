#include "danielo515.h"
#include "alt_tab.h"

bool                       altPressed = false;
__attribute__((weak)) void alt_tab_activated(void){};
__attribute__((weak)) void alt_tab_deactivated(void){};
extern bool                onMac;

// =============== ALT_TAB single key handling
bool process_alt_tab(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALT_TAB:
            if (!record->event.pressed) {
                return false;
            }
            if (altPressed) {
                tap_code(KC_TAB);
            } else {
                altPressed = true;
                onMac ? register_code(KC_LGUI) : register_code(KC_LALT);
                tap_code(KC_TAB);
                alt_tab_activated();
            }
        // avoid alt releasing if the key is of movement
        case KC_RIGHT ... KC_UP:
            if (altPressed) {
                return true;  // yes QMK, do your stuff
            }
    }
    // Reset sticky alt tab when any other key is pressed
    if (altPressed) {
        onMac ? unregister_code(KC_LGUI) : unregister_code(KC_LALT);
        altPressed = false;
        alt_tab_deactivated();
        return false;
    }
    return true;
};
