#include QMK_KEYBOARD_H

enum layers { MAC_BASE, NIX_BASE };

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

// customization
enum custom_keycodes {
    LAYER_LED_CHG = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LAYER_LED_CHG:
            if (record->event.pressed) {
                // send TG1
                SEND_STRING("Toggle layer 1!");
            } else {
                // send color change
                SEND_STRING("Toggle light!");
            }
            break;
    }
    return true;
};

// (i _think_ this is essentially where the "overrides" go)

void matrix_scan_user(void) {                    // runs frequently to update info
    uint8_t        layer = biton32(layer_state); // get current layer
    static uint8_t current_layer;                // check historic layer
    static bool    has_layer_changed = true;
    // static, so it is kept the same between calls
    // defaults to true, so that it runs once to initially set the light

    if (layer != current_layer) {
        has_layer_changed = true;
        current_layer     = layer; // update layer information
    }
    // Check for layer change, and apply color if its changed since last check
    if (has_layer_changed) {
        //backlight_leds_off(); // turn off all LEDs
        // change backlight based on layer.  These should be numbers or whatever you defined the layers as
        switch (layer) {
            case MAC_BASE:
                //default_layers_leds_on();
                break;
            case NIX_BASE:
                //backlight_leds_off();
                break;
            default:
                //default_layers_leds_on();
                break;
        }
        has_layer_changed = false;
    }
};

// turning clang-format off to keep this section easier to read
// clang-format off
// TBD: replace KC_NO codes with macros from via
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[MAC_BASE] = LAYOUT_ansi_69(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, LAYER_LED_CHG,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_NO, 
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_DEL, 
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_ESC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, 
        KC_LCTL, KC_LGUI, KC_NO, KC_BSPC, TG(1), KC_LALT, KC_SPC, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT
    ),
	[NIX_BASE] = LAYOUT_ansi_69(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, LAYER_LED_CHG, 
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, 
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_DEL, 
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_ESC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, 
        KC_LCTL, KC_LCTL, KC_LGUI, KC_BSPC, TG(1), KC_LALT, KC_SPC, KC_END, KC_LEFT, KC_DOWN, KC_RGHT
    )
};

//clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [NIX_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
};
#endif // ENCODER_MAP_ENABLE
