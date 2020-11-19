#include "../../naho6key.h"
#include "../../config.h"
// deprecated includes when I sent actual strings instead of macro kbd
// #include "keymap_french.h"
// #include "sendstring_french.h"

// layers
#define _BASE 0
#define _EMOJI 1
#define _NAV 2
#define _MOUSE 3
#define _MEDIA 4

enum custom_keycodes {
    CK_LT_MEDIA_BASE = SAFE_RANGE,
};

///////////////////////
// Unicode Map (emojis)

enum unicode_name {
    PI,        // π
    FACEPALM,  // 🤦
    SHRUG,     // 🤷
    THUMBSUP,  // 👍
    ROFL,      // 🤣
};

const uint32_t PROGMEM unicode_map[] = {
    [PI]       = 0x003C0,  // π
    [FACEPALM] = 0x1F926,  // 🤦
    [SHRUG]    = 0x1F937,  // 🤷
    [THUMBSUP] = 0x1F44D,  // 👍
    [ROFL]     = 0x1F923,  // 🤣
};

///////////////////////
// Actual layout

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // (white) Base: COPY, (hold = emoji), CUT  //  PAST, NEXT LAYER (hold, or dbltap to toggle), CALCULATOR
    // (pink)  Emoji: 🤦, …, 🤷  //  👍, π, 🤣
    [_BASE]  = KEYMAP(KC_COPY, MO(_EMOJI), KC_CUT, KC_PASTE, TT(_NAV), KC_CALCULATOR),
    [_EMOJI] = KEYMAP(X(FACEPALM), _______, X(SHRUG), X(THUMBSUP), X(PI), X(ROFL)),
    // (blue)  Nav: LEFT, SHIFT, RIGHT  //  DOWN, NEXT LAYER (hold, or dbltap to toggle), UP
    [_NAV] = KEYMAP(KC_LEFT, KC_LSFT, KC_RIGHT, KC_DOWN, TT(_MOUSE), KC_UP),
    // (red)   Mouse: LEFT, CLICK, RIGHT  //  DOWN, MEDIA (hold) or BASE (tap), UP
    // Note: we want to use LT(MEDIA, TO(BASE)) but LT only supports basic keycodes, so we have to use a custom implementation
    [_MOUSE] = KEYMAP(KC_MS_LEFT, KC_MS_BTN1, KC_MS_RIGHT, KC_MS_DOWN, CK_LT_MEDIA_BASE, KC_MS_UP),
    // (green) Media: VOL-, MUTE, VOL+  //  PLAY-PAUSE, NEXT LAYER, RGUI
    [_MEDIA] = KEYMAP(KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, KC_AUDIO_VOL_UP, KC_MEDIA_PLAY_PAUSE, _______, KC_MS_BTN2),
};

///////////////////////
// LED management, using a basic RGB LED wired to 3 pins

void keyboard_pre_init_user(void) {
    // Set our LED pins as output
    setPinOutput(PIN_LED_R);
    setPinOutput(PIN_LED_G);
    setPinOutput(PIN_LED_B);
}

void setRGB(bool r, bool g, bool b) {
    writePin(PIN_LED_R, r);
    writePin(PIN_LED_G, g);
    writePin(PIN_LED_B, b);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _BASE:
            setRGB(1, 1, 1);
            break;
        case _EMOJI:
            setRGB(1, 0, 1);
            break;
        case _NAV:
            setRGB(0, 0, 1);
            break;
        case _MOUSE:
            setRGB(1, 0, 0);
            break;
        case _MEDIA:
            setRGB(0, 1, 0);
            break;
    }
    return state;
}

// Helper (not used anymore, kept for the record)
// bool isShiftHeld(void) { return get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT); }

// Handle special key: HOLD = MO(MEDIA), TAP = TO(BASE)
static bool moveToBaseOnRelease = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == CK_LT_MEDIA_BASE) {
        if (record->event.pressed) {
            // Held = toggle MEDIA on
            moveToBaseOnRelease = true;
            layer_on(_MEDIA);
        } else {
            // Released = move to BASE if no MEDIA key was pressed
            if (moveToBaseOnRelease) {
                // No other key was pressed meanwhile
                layer_move(_BASE);
            } else {
                layer_off(_MEDIA);
            }
        }
    } else {
        // Other key event meanwhile: means we're using as a layer modifier → do NOT move to BASE on release
        moveToBaseOnRelease = false;
    }
    return true;
}
