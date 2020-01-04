#include "rainbowUnicorn.h"

#include "quantum.h"

static struct {
    bool    enabled;
    uint8_t color;
    char    string[2];
    uint8_t mods;
} state = {false, 0};

bool rainbowUnicornIsEnabled() { return state.enabled; }
void rainbowUnicornEnable() { state.enabled = true; }
void rainbowUnicornDisable() { state.enabled = false; }
void rainbowUnicornToggle() { state.enabled ^= true; }

void rainbowUnicorn(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
        case ALT_T(KC_A)... ALT_T(KC_Z):
        case CTL_T(KC_A)... CTL_T(KC_Z):
        case GUI_T(KC_A)... GUI_T(KC_Z):
        case SFT_T(KC_A)... SFT_T(KC_Z):
            if (record->event.pressed) {
                state.mods = get_mods();
                clear_mods();

                tap_code16(C(KC_C));

                itoa(state.color + 3, state.string, 10);
                send_string(state.string);

                set_mods(state.mods);
            } else {
                state.color = (state.color + 1) % 11;
            }
    }
}
