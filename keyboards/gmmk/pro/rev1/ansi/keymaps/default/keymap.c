/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// Snap Tap Configuration
#define SNAP_TAP_ENABLED 1  // Set to 0 to disable Snap Tap
#define SNAP_TAP_PAIRS 4    // Maximum number of key pairs for Snap Tap

// Snap Tap key pairs - define opposing keys that should use Snap Tap
// Format: {key1, key2, 0} - the 0 is a terminator
static const uint16_t snap_tap_pairs[][3] = {
    {KC_A, KC_D, 0},        // Left/Right movement
    {KC_W, KC_S, 0},        // Forward/Backward movement  
    {KC_LEFT, KC_RIGHT, 0}, // Arrow keys
    {KC_UP, KC_DOWN, 0},    // Arrow keys
    {0, 0, 0}               // Terminator
};

// Snap Tap state tracking
typedef struct {
    uint16_t key1;
    uint16_t key2;
    bool key1_pressed;
    bool key2_pressed;
    uint32_t key1_timestamp;
    uint32_t key2_timestamp;
} snap_tap_pair_state_t;

static snap_tap_pair_state_t snap_tap_states[SNAP_TAP_PAIRS];

// Initialize Snap Tap states
void snap_tap_init(void) {
    for (int i = 0; i < SNAP_TAP_PAIRS; i++) {
        snap_tap_states[i].key1 = snap_tap_pairs[i][0];
        snap_tap_states[i].key2 = snap_tap_pairs[i][1];
        snap_tap_states[i].key1_pressed = false;
        snap_tap_states[i].key2_pressed = false;
        snap_tap_states[i].key1_timestamp = 0;
        snap_tap_states[i].key2_timestamp = 0;
    }
}

// Find Snap Tap pair for a given keycode
int find_snap_tap_pair(uint16_t keycode) {
    for (int i = 0; i < SNAP_TAP_PAIRS; i++) {
        if (snap_tap_states[i].key1 == keycode || snap_tap_states[i].key2 == keycode) {
            return i;
        }
    }
    return -1;
}

// Handle Snap Tap logic
bool snap_tap_process(uint16_t keycode, keyrecord_t *record) {
    if (!SNAP_TAP_ENABLED) return true;
    
    int pair_index = find_snap_tap_pair(keycode);
    if (pair_index == -1) return true;
    
    snap_tap_pair_state_t *state = &snap_tap_states[pair_index];
    bool is_key1 = (keycode == state->key1);
    bool is_key2 = (keycode == state->key2);
    
    if (!is_key1 && !is_key2) return true;
    
    if (record->event.pressed) {
        // Key press
        if (is_key1) {
            state->key1_pressed = true;
            state->key1_timestamp = record->event.time;
            
            // If key2 is already pressed, release it (prioritize key1)
            if (state->key2_pressed) {
                unregister_code(state->key2);
                state->key2_pressed = false;
            }
        } else if (is_key2) {
            state->key2_pressed = true;
            state->key2_timestamp = record->event.time;
            
            // If key1 is already pressed, release it (prioritize key2)
            if (state->key1_pressed) {
                unregister_code(state->key1);
                state->key1_pressed = false;
            }
        }
        
        // Register the new key
        register_code(keycode);
        return false; // Don't process normally, we handled it
        
    } else {
        // Key release
        if (is_key1) {
            state->key1_pressed = false;
            unregister_code(keycode);
            
            // If key2 was pressed before key1 was released, re-register key2
            if (state->key2_pressed) {
                register_code(state->key2);
            }
        } else if (is_key2) {
            state->key2_pressed = false;
            unregister_code(keycode);
            
            // If key1 was pressed before key2 was released, re-register key1
            if (state->key1_pressed) {
                register_code(state->key1);
            }
        }
        
        return false; // Don't process normally, we handled it
    }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the QK_BOOT key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,          _______,
        _______, RM_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, RM_VALU, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          _______,
        _______, _______, RM_VALD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, RM_HUEU, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RM_NEXT, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RM_SPDD, RM_PREV, RM_SPDU
    ),


};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif

// Initialize Snap Tap on keyboard startup
void keyboard_post_init_user(void) {
    snap_tap_init();
}

// Process Snap Tap for all key events
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Handle Snap Tap logic first
    if (!snap_tap_process(keycode, record)) {
        return false; // Snap Tap handled this key
    }
    
    // Continue with normal key processing
    return true;
}
