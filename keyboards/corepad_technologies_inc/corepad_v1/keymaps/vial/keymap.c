#include QMK_KEYBOARD_H
#include "lib/logo.h"

#define NUM_LAYERS 8
#define LAYER_MENU_HOLD 500

static bool layer_menu = false;
static bool combo_active = false;
static uint16_t combo_timer = 0;
static uint8_t selected_layer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT(
    KC_MPLY,
    KC_MUTE,
    KC_MSTP
),

[1] = LAYOUT(
    KC_TRNS,
    KC_TRNS,
    KC_TRNS
),

[2] = LAYOUT(
    KC_TRNS,
    KC_TRNS,
    KC_TRNS
),

[3] = LAYOUT(
    KC_TRNS,
    KC_TRNS,
    KC_TRNS
),

[4] = LAYOUT(
    KC_TRNS,
    KC_TRNS,
    KC_TRNS
),

[5] = LAYOUT(
    KC_TRNS,
    KC_TRNS,
    KC_TRNS
),

[6] = LAYOUT(
    KC_TRNS,
    KC_TRNS,
    KC_TRNS
),

[7] = LAYOUT(
    KC_TRNS,
    KC_TRNS,
    KC_TRNS
)

};

#include QMK_KEYBOARD_H
#include "lib/logo.h"


#if defined(OLED_ENABLE)
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}

bool oled_task_user(void) {

    if (layer_menu) {

        oled_clear();

        oled_write_ln_P(PSTR("CorePad"), false);
        oled_write_ln_P(PSTR(""), false);
        oled_write_ln_P(PSTR("Layer Select"), false);

        char buf[8];
        snprintf(buf, sizeof(buf), "< %d >", selected_layer);

        oled_write_ln(buf, false);

        return false;
    }

    oled_write_raw_P(corepad_logo, sizeof(corepad_logo));
    return false;
}
#endif

#if defined(RGBLIGHT_ENABLE)
// XIAO RP2040's onboard WS2812 LED sits behind a load switch that must be
// enabled before the LED will light up. This runs before rgblight_init(),
// so the power rail is up in time for the boot flash below.
void keyboard_pre_init_user(void) {
    setPinOutput(GP11);
    writePinHigh(GP11);
}

// Quick boot flash (red -> green -> blue -> white), then restore whatever
// effect/color Vial last saved to EEPROM, so this never overwrites your
// configured lighting - it just announces "I'm alive" on power-up.
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);

    rgblight_sethsv_noeeprom(HSV_RED);
    wait_ms(150);
    rgblight_sethsv_noeeprom(HSV_GREEN);
    wait_ms(150);
    rgblight_sethsv_noeeprom(HSV_BLUE);
    wait_ms(150);
    rgblight_sethsv_noeeprom(HSV_WHITE);
    wait_ms(150);
}
#endif
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        bool left  = matrix_is_on(0, 0);
        bool right = matrix_is_on(0, 2);

        if (!layer_menu && left && right) {
            combo_active = true;
            combo_timer = timer_read();
        }

        if (layer_menu) {
            switch (record->event.key.col) {
                case 0:
                    selected_layer = (selected_layer == 0) ? NUM_LAYERS - 1 : selected_layer - 1;
                    return false;

                case 1:
                    default_layer_set(1UL << selected_layer);
                    layer_move(selected_layer);
                    layer_menu = false;
                    return false;

                case 2:
                    selected_layer = (selected_layer + 1) % NUM_LAYERS;
                    return false;
            }
        }
    }

    return true;
}

void matrix_scan_user(void) {
    if (combo_active && timer_elapsed(combo_timer) > LAYER_MENU_HOLD) {
        combo_active = false;
        layer_menu = true;
        selected_layer = get_highest_layer(layer_state);
    }

    if (!matrix_is_on(0, 0) || !matrix_is_on(0, 2)) {
        combo_active = false;
    }
}
