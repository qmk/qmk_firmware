#pragma once

#include "quantum.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    CH_CUSTOM = SAFE_RANGE,
    CH_ZOOM_JOIN_MEETING,
    CH_ZOOM_START_MEETING,
    CH_ZOOM_LEAVE_MEETING,
    CH_ZOOM_SCHEDULE_MEETING,
    CH_ZOOM_FOCUS,
    CH_ZOOM_SHARE_SCREEN_START_STOP_TOGGLE,
    CH_ZOOM_MUTE_TOGGLE,
    CH_ZOOM_RECORD_TOGGLE,
    CH_ZOOM_REACT_TOGGLE,
    CH_ZOOM_RAISE_HAND_TOGGLE,
    CH_ZOOM_FULL_SCREEN_TOGGLE,
    CH_ZOOM_SWITCH_CAMERA,
    CH_ZOOM_VIDEO_TOGGLE,
    CH_ZOOM_JUMP_TO_CHAT,
    CH_ZOOM_SCREENSHOT,
};

#define KEY_MACROS_MAX_COUNT  3
#define KEYCODE_COUNT 16

const uint8_t PROGMEM windowsConfigs[KEYCODE_COUNT][KEY_MACROS_MAX_COUNT] = {
    { KC_NO, KC_NO, KC_NO },
    { KC_LCTRL, KC_T },
    { KC_NO, KC_NO, KC_NO},
    { KC_LALT, KC_F4 },
    { KC_NO, KC_NO, KC_NO },
    { KC_LCTRL, KC_LALT, KC_S },
    { KC_LALT, KC_LSHIFT, KC_S },
    { KC_LALT, KC_A },
    { KC_LALT, KC_R },
    { KC_NO, KC_NO, KC_NO },
    { KC_LALT, KC_Y },
    { KC_LALT, KC_F },
    { KC_LALT, KC_N },
    { KC_LALT, KC_V },
    { KC_LCTRL, KC_T },
    { KC_LALT, KC_LSHIFT, KC_T }
};
