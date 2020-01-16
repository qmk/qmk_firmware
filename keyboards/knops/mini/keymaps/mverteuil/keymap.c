#include QMK_KEYBOARD_H

#define MAXIMIZ A(G(KC_F))
#define NXTDSPL C(A(G(KC_RIGHT)))
#define BTMHALF A(G(KC_DOWN))
#define TOPHALF A(G(KC_UP))
#define NXTTHRD SS_LCTL(SS_LALT(SS_TAP(X_RIGHT)))
#define PRVTHRD C(A(KC_LEFT))

#define LT_MSTP LT(_LAYERS, KC_MSTP)
#define LT_ESC LT(_LAYERS, KC_ESC)
#define LT_NXTH TD(TD_SPEC)

enum mini_layers {
    _MEDIA,
    _COPYPASTA,
    _SPECTACLES,
    _LAYERS,
};

enum { TD_SPEC = 0 };

void td_spectacles_finish(qk_tap_dance_state_t *state, void *user_data);
void td_spectacles_reset(qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
    /* Tap once for spectacles macro, hold for layer toggle */
    [TD_SPEC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_spectacles_finish, td_spectacles_reset),
};

void led_set_layer(int layer);

/*
 *   Key Layout
 *	 _____	 _____	 _____
 *	| 	  | | 	  | | 	  |
 *	|  1  | |  2  | |  3  |
 *	|_____| |_____| |_____|
 *	 _____	 _____	 _____
 *	| 	  | | 	  | | 	  |
 *	|  4  | |  5  | |  6  |
 *	|_____| |_____| |_____|
 *
 *  Hold 1 and:
 *    - press 4, 5, or 6 to change layers
 *    - press 3 to reset, or press and hold 3 to enter DFU programming mode
 *
 *  If something prevents you from using the above to reprogram, you can hold 3 while powering on as a fallback.
 */

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     *   Layer 0 (Media Keys)
     *	 _____	 _____	 _____
     *	| 	  | | 	  | | 	  |
     *	 Stop    VolUp   Play
     *	|_____| |_____| |_____|
     *	 _____	 _____	 _____
     *	| 	  | | 	  | | 	  |
     *	 Prev    VolDwn  Next
     *	|_____| |_____| |_____|
     *
     */
    [_MEDIA] = LAYOUT(
        LT_MSTP, KC_VOLU, KC_MPLY,
        KC_MPRV, KC_VOLD, KC_MNXT
    ),

    /*
     *   Layer 1 (Copy and Paste Macros)
     *	 _____	 _____	 _____
     *	| 	  | | 	  | | 	  |
     *	  ESC    Ctl+Z   CSf+Z
     *	|_____| |_____| |_____|
     *	 _____	 _____	 _____
     *	| 	  | | 	  | | 	  |
     *	 Ctl+X   Ctl+C   Ctl+V
     *	|_____| |_____| |_____|
     *
     */

    [_COPYPASTA] = LAYOUT(
        LT_ESC,  C(KC_Z), C(S(KC_Z)),
        C(KC_X), C(KC_C), C(KC_V)
    ),

    /*
     *   Layer 2 (Spectacles Macros)
     *	 _LT&__	 _____	 _____
     *	| Win | | Win | | Win |
     *	| Next| | Top | |Mximze
     *	|_1/3_| |_1/2_| |_____|
     *	 _____	 _____	 _____
     *	| Win | | Win | | Win |
     *	| Prev| | Bot | | Next|
     *	|_1/3_| |_1/2_| |Displ|
     *
     */
    [_SPECTACLES] = LAYOUT(
        LT_NXTH,TOPHALF,MAXIMIZ,
        PRVTHRD,BTMHALF,NXTDSPL
    ),

    /*
     *  Layer 3 (Layer Select/Reset)
     *	 _____	 _____	 _____
     *	| 	  | | 	  | |     |
     *	|None | |None | |Reset|
     *	|_____| |_____| |_____|
     *	 _____	 _____	 _____
     *	|Layer| |Layer| |Layer|
     *  |  0  | |  1  | |  2  |
     *	|_____| |_____| |_____|
     *
     *  Layers 0, 1, and 2 have the top left button held to activate this layer.
     *  Then press the specific layer to switch to it.
     *
     */
    [_LAYERS] = LAYOUT(
        _______, _______, RESET,
        TO(_MEDIA),TO(_COPYPASTA),TO(_SPECTACLES)
    )

};
/* clang-format on */

/*
 *	Knops Mini LED Numbers:
 *	 _____	 _____	 _____
 *	| 	  | | 	  | | 	  |
 *	|  1  | |  2  | |  3  |    <---
 *	|_____| |_____| |_____|       |      These LEDs are called 'Switch LEDs'
 *	 _____	 _____	 _____        |----- To turn on/off these leds, use:
 *	| 	  | | 	  | | 	  |       |	  set_switch_led( [1-6], [true/false]);
 *	|  4  | |  5  | |  6  |    <---
 *	|_____| |_____| |_____|
 *
 *	 < 0 >   < 1 >   < 2 >     <---      These front-LEDs are called 'Layer LEDs'
 *							             To turn on/off these leds, use:
 *										 set_layer_led( [0-2], [true/false] );
 */

void set_switch_led(int ledId, bool state) {
    switch (ledId) {
        case 1:
            writePin(D7, state);
            break;
        case 2:
            writePin(readPin(B7) ? C6 : C7, state);
            break;
        case 3:
            writePin(D4, state);
            break;
        case 4:
            writePin(E6, state);
            break;
        case 5:
            writePin(B4, state);
            break;
        case 6:
            writePin(D6, state);
            break;
    }
}

void set_layer_led(int layerId, bool layerState) {
    if (layerState) {
        switch (layerId) {
            case 0:
                writePinLow(D5);
                break;
            case 1:
                writePinHigh(B6);
                break;
            case 2:
                writePinLow(B0);
                break;
            case 3:
                writePinLow(D5);
                writePinHigh(B6);
                writePinLow(B0);
                break;
        }
    } else {
        switch (layerId) {
            case 0:
                writePinHigh(D5);
                break;
            case 1:
                writePinLow(B6);
                break;
            case 2:
                writePinHigh(B0);
                break;
            case 3:
                writePinHigh(D5);
                writePinLow(B6);
                writePinHigh(B0);
                break;
        }
    }
}

/*
 * This function led_set_layer gets called when you switch between layers.
 * It allows you to turn on and off leds for each different layer and do
 * other cool stuff.
 */
void led_set_layer(int layer) {
    switch (layer) {
        case 0:
            set_switch_led(1, true);
            set_switch_led(2, true);
            set_switch_led(3, true);
            set_switch_led(4, true);
            set_switch_led(5, false);
            set_switch_led(6, false);
            break;

        case 1:
            set_switch_led(1, true);
            set_switch_led(2, true);
            set_switch_led(3, true);
            set_switch_led(4, false);
            set_switch_led(5, true);
            set_switch_led(6, false);
            break;

        case 2:
            set_switch_led(1, true);
            set_switch_led(2, true);
            set_switch_led(3, true);
            set_switch_led(4, false);
            set_switch_led(5, false);
            set_switch_led(6, true);
            break;

        case 3:
            set_switch_led(1, false);
            set_switch_led(2, false);
            set_switch_led(3, true);
            set_switch_led(4, true);
            set_switch_led(5, true);
            set_switch_led(6, true);
            break;
    }
}

/*
 * Prepare all LED ports for output
 */
void led_init_ports() {
    setPinOutput(D7);  // Switch 1 LED
    setPinOutput(C6);  // Switch 2 LED Pin1
    setPinOutput(C7);  // Switch 2 LED Pin2
    setPinOutput(D4);  // Switch 3 LED
    setPinOutput(E6);  // Switch 4 LED
    setPinOutput(B4);  // Switch 5 LED
    setPinOutput(D6);  // Switch 6 LED
    setPinOutput(D5);  // Layer 0 LED
    setPinOutput(B6);  // Layer 1 LED
    setPinOutput(B0);  // Layer 2 LED

    // Cycle through layer LEDs
    for (int i = 0; i < 4; i++) {
        led_set_layer(i % 3);
        wait_ms(200);
    }
}

// Runs on layer change, no matter where the change was initiated
layer_state_t layer_state_set_user(layer_state_t state) {
    // Skip from initialization state 0 to 1
    if (state == 0) state = 1;

    // Check for active layers and set layer LED appropriately
    // Layers are indicated by active bits
    // i.e. 0001 = just 1, 0011 = 1 and 2, 0010 = just 2, etc.
    for (int i = 0; i < 4; i++) {
        bool isActive = (state & 1 << i) == 1 << i;
        set_layer_led(i, isActive);
        if (isActive) led_set_layer(i);
    }

    return state;
}

void matrix_init_user(void) { led_init_ports(); }

void matrix_scan_user(void) {}

void td_spectacles_finish(qk_tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        layer_on(_LAYERS);
    } else {
        SEND_STRING(NXTTHRD);
    }
}

void td_spectacles_reset(qk_tap_dance_state_t *state, void *user_data) { layer_off(_LAYERS); }
