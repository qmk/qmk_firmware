/*
 * Keybit8 - Default Keymap
 * Minecraft Control Layout with Layer Support
 * 
 * Layer 0 (Base): Basic movement and actions
 *   - W, A, S, LT(_LAYER3, KC_D), Space, Shift, LT(_LAYER2, KC_E), LT(_LAYER1, KC_1)
 * Layer 1: Hotbar 2-9 (activated by holding key 7 - KC_1)
 * Layer 2: Additional actions (activated by holding key 6 - KC_E)
 * Layer 3: Game layer (activated by holding key 3 - KC_D)
 *   - LEFT, UP, DOWN, RIGHT, 0, 1, 2, Space
 * 
 * LED Status:
 *   - Layer 0: Green LED OFF
 *   - Layer 1: Green LED steady ON
 *   - Layer 2: Green LED slowly blinks (500ms period)
 *   - Layer 3: Green LED steady ON
 * 
 * Web Game Support:
 * - LED and speaker control via Web Serial API
 * - 8 red LEDs for game feedback
 * - 1 green LED for layer status
 * - Speaker for sound effects
 */

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "timer.h"

// Layer definitions
enum layer_names {
    _BASE,
    _LAYER1,
    _LAYER2,
    _LAYER3  // Game layer
};

// LED and Speaker control for Web Game
#define RED_LED_PINS_ARRAY { D2, B4, B1, B2, D3, B5, B3, F7 }
static const pin_t red_led_pins[] = RED_LED_PINS_ARRAY;
#define GREEN_LED_PIN F6
#define SPEAKER_PIN B6

// Layer 2 green LED blink control
static bool     layer2_blink_enabled = false;
static uint32_t layer2_blink_timer   = 0;
static bool     layer2_led_state     = false;

// Speaker control variables
static bool speaker_active = false;
static uint16_t speaker_frequency = 0;
static uint16_t speaker_duration = 0;
static uint32_t speaker_start_time = 0;

// Layer 0 (Base): W, A, S, D, Space, Shift, E, 1
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ W │ A │ S │LT3│
     * ├───┼───┼───┼───┤
     * │Spc│Shf│LT2│LT1│
     * └───┴───┴───┴───┘
     * LT3 = Layer 3 on hold, KC_D on tap
     * LT2 = Layer 2 on hold, KC_E on tap
     * LT1 = Layer 1 on hold, KC_1 on tap
     */
    [_BASE] = LAYOUT(
        KC_W,              KC_A,              KC_S,              LT(_LAYER3, KC_D),
        KC_SPC,            KC_LSFT,           LT(_LAYER2, KC_E), LT(_LAYER1, KC_1)
    ),

    /*
     * Layer 1: Hotbar 2-9
     * Activated by holding L1_T (key 7)
     */
    [_LAYER1] = LAYOUT(
        KC_2,    KC_3,    KC_4,    KC_5,
        KC_6,    KC_7,    KC_8,    KC_9
    ),

    /*
     * Layer 2: Additional actions
     * Activated by holding L2_T (key 6)
     */
    [_LAYER2] = LAYOUT(
        KC_Q,    KC_R,    KC_F,    KC_TAB,
        KC_ENT,  KC_ESC,  KC_T,    KC_C
    ),

    /*
     * Layer 3: Game layer
     * Activated by holding D key (key 3) - same as Layer 1/2
     */
    [_LAYER3] = LAYOUT(
        KC_LEFT, KC_UP,   KC_DOWN, KC_RIGHT,  // left, up, down, right
        KC_0,    KC_1,    KC_2,    KC_SPC     // 0, 1, 2, space
    )
};

// Initialize LED and Speaker pins
void keyboard_post_init_user(void) {
    // Set LED pins as output
    for (uint8_t i = 0; i < 8; i++) {
        setPinOutput(red_led_pins[i]);
        writePinLow(red_led_pins[i]);
    }
    setPinOutput(GREEN_LED_PIN);
    writePinLow(GREEN_LED_PIN);
    
    // Set speaker pin as output
    setPinOutput(SPEAKER_PIN);
    writePinLow(SPEAKER_PIN);
}

// Handle speaker timing and LED blinking
void matrix_scan_user(void) {
    // Handle speaker timing
    if (speaker_active) {
        uint32_t elapsed = timer_elapsed32(speaker_start_time);
        if (elapsed >= speaker_duration) {
            speaker_active = false;
            writePinLow(SPEAKER_PIN);
        } else {
            // Simple tone generation (toggle pin at frequency)
            // Calculate toggle interval based on frequency
            uint32_t interval = 1000 / (speaker_frequency * 2); // milliseconds per half cycle
            static uint32_t last_toggle = 0;
            uint32_t now = timer_read32();
            
            if (now - last_toggle >= interval) {
                togglePin(SPEAKER_PIN);
                last_toggle = now;
            }
        }
    }

    // Handle green LED blink for Layer 2
    if (layer2_blink_enabled) {
        // Blink slowly (500ms period per half cycle)
        if (timer_elapsed32(layer2_blink_timer) > 500) {
            layer2_blink_timer = timer_read32();
            layer2_led_state   = !layer2_led_state;
            writePin(GREEN_LED_PIN, layer2_led_state);
        }
    }
}

// Layer state handling (green LED behaviour per layer)
//  - Layer 0 (BASE): green LED OFF
//  - Layer 1:        green LED steady ON
//  - Layer 2:        green LED slowly blinks
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t highest = get_highest_layer(state);

    switch (highest) {
        case _BASE:
            layer2_blink_enabled = false;
            layer2_led_state     = false;
            writePinLow(GREEN_LED_PIN);
            break;

        case _LAYER1:
            layer2_blink_enabled = false;
            layer2_led_state     = false;
            writePinHigh(GREEN_LED_PIN);
            break;

        case _LAYER2:
            // Enable blinking for layer 2
            layer2_blink_enabled = true;
            layer2_led_state     = true;
            layer2_blink_timer   = timer_read32();
            writePinHigh(GREEN_LED_PIN);
            break;

        case _LAYER3:
            // Game layer: green LED steady ON
            layer2_blink_enabled = false;
            layer2_led_state     = false;
            writePinHigh(GREEN_LED_PIN);
            break;
    }

    return state;
}

