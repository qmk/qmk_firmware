#pragma once

#include "quantum.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    CH_CUSTOM = SAFE_RANGE,
    // zoom
    CH_ZOOM_MUTE_TOGGLE,
    CH_ZOOM_VIDEO_TOGGLE,
    CH_ZOOM_SHARE_SCREEN_START_STOP_TOGGLE,
    CH_ZOOM_RAISE_HAND_TOGGLE,
    CH_ZOOM_LEAVE_MEETING,
    CH_SWITCH_WINDOW,
    CH_LAST_KEYCODE
};

#define KEY_MACROS_MAX_COUNT  3
#define KEYCODE_COUNT 16

const uint16_t windows_configs[KEYCODE_COUNT][KEY_MACROS_MAX_COUNT] = {
    { KC_NO, KC_NO, KC_NO },
    // zoom
    { KC_LALT, KC_A, KC_NO },
    { KC_LALT, KC_V, KC_NO },
    { KC_LALT, KC_S, KC_NO },
    { KC_LALT, KC_Y, KC_NO },
    { KC_LALT, KC_Q, KC_NO },
    { KC_LALT, KC_TAB, KC_NO },
};

const uint16_t macos_configs[KEYCODE_COUNT][KEY_MACROS_MAX_COUNT] = {
    { KC_NO, KC_NO, KC_NO },
    // zoom
    { KC_LGUI, KC_LSHIFT, KC_A },
    { KC_LGUI, KC_LSHIFT, KC_V },
    { KC_LGUI, KC_LSHIFT, KC_S },
    { KC_LALT, KC_Y, KC_NO },
    { KC_LGUI, KC_W, KC_NO },
    { KC_LGUI, KC_TAB, KC_NO },
};
