#include "narze.h"

// Mod taps does not work with shifted keycodes eg. SFT_T(KC_LPRN)
// So a macro is needed
// Implementation copied from process_space_cadet

static uint8_t mtwm_last = 0;
static uint16_t mtwm_timer = 0;
static uint8_t mtwm_mods = 0;

void perform_mod_tap_with_mod(keyrecord_t *record, uint8_t holdMod, uint8_t tapMod, uint8_t keycode) {
    if (record->event.pressed) {
        mtwm_last  = holdMod;
        mtwm_timer = timer_read();
        mtwm_mods = get_mods();

        if (IS_MOD(holdMod)) {
            register_mods(MOD_BIT(holdMod));
        }
    } else {
        if (mtwm_last == holdMod && timer_elapsed(mtwm_timer) < TAPPING_TERM) {
            if (holdMod != tapMod) {
                if (IS_MOD(holdMod)) {
                    unregister_mods(MOD_BIT(holdMod));
                }
                if (IS_MOD(tapMod)) {
                    register_mods(MOD_BIT(tapMod));
                }
            }
            set_weak_mods(mtwm_mods);
            tap_code(keycode);
            clear_weak_mods();

            if (IS_MOD(tapMod)) {
                unregister_mods(MOD_BIT(tapMod));
            }
        } else {
            if (IS_MOD(holdMod)) {
                unregister_mods(MOD_BIT(holdMod));
            }
        }
    }
}
