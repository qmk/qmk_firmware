#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"

/* CAPS WORD Sounds by JCanto */
float cwords_on[][2] = SONG(PLANCK_SOUND);
float cwords_off[][2] = SONG(VIOLIN_SOUND);

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;
tap_dance_action_t *action;

enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
  DANCE_3,
  DANCE_2,
  DANCE_4,
  DANCE_5,
  DANCE_6,
  DANCE_7,
};

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _LAYER4,
  _LAYER5,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_planck_grid(
    KC_ESCAPE,  KC_Q,  KC_W,  TD(DANCE_7),  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  TD(DANCE_0),  TD(DANCE_1),  KC_BSPC,
    KC_TAB,  LT(4,KC_A),  MT(MOD_LSFT, KC_S),  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  MT(MOD_RSFT, KC_L),  KC_SCLN,  KC_QUOTE,
    TD(DANCE_2),  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMMA,  KC_DOT,  TD(DANCE_3),  KC_ENTER,
    TD(DANCE_4),  KC_LEFT_GUI,  KC_LEFT_ALT,  KC_RIGHT_ALT,  TD(DANCE_5),  KC_SPACE,  KC_SPACE,  RAISE,  CW_TOGG,  KC_LEFT,  KC_DOWN,  KC_RIGHT
),

[_LOWER] = LAYOUT_planck_grid(
    KC_TILD,  KC_EXLM,  KC_AT,  KC_HASH,  KC_DLR,  KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_TRANSPARENT,
    KC_DELETE,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,
    KC_TRANSPARENT,  KC_F7,  KC_F8,  KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_HOME,  KC_END,  KC_HOME,  KC_UP,  KC_TRANSPARENT,
    KC_COMMA,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_MEDIA_NEXT_TRACK,  KC_LEFT,  KC_DOWN,  KC_RIGHT
),

[_RAISE] = LAYOUT_planck_grid(
    KC_GRAVE,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  KC_TRANSPARENT,
    KC_DELETE, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_MINUS,  KC_EQUAL,  KC_LBRC,  KC_RBRC,  KC_BSLS,
    KC_TRANSPARENT,  KC_F7,  KC_F8,  KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_HOME,  KC_NUBS, KC_PAGE_UP, KC_PGDN,  KC_TRANSPARENT,
    KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_MEDIA_NEXT_TRACK,  KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP,  KC_MEDIA_PLAY_PAUSE
),

[_ADJUST] = LAYOUT_planck_grid(
    KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_MS_UP,  KC_MS_DOWN,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_DELETE,
    KC_TRANSPARENT,  QK_AUDIO_ON,  QK_AUDIO_OFF,  AU_TOGG,  KC_TRANSPARENT,  KC_TRANSPARENT,  RGB_TOG,  RGB_VAI,  RGB_VAD,  KC_TRANSPARENT,  QK_BOOT,
    KC_CAPS,  KC_TRANSPARENT,  QK_MUSIC_ON,  QK_MUSIC_OFF,  MU_TOGG,  KC_TRANSPARENT,  KC_TRANSPARENT,  RGB_MODE_FORWARD,  RGB_HUI,  KC_TRANSPARENT,  KC_AUDIO_VOL_UP,  KC_TRANSPARENT,
    KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE
),

[_LAYER4] = LAYOUT_planck_grid(
    KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_KP_SLASH,  KC_BSPC,
    KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_KP_4,  KC_KP_5,  KC_KP_6,  KC_KP_ASTERISK,  KC_EQUAL,
    KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_KP_MINUS,  KC_ENTER,
    KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_KP_0,  KC_KP_DOT,  KC_KP_PLUS,  KC_TRANSPARENT
),

[_LAYER5] = LAYOUT_planck_grid(
    KC_ESCAPE,  KC_TRANSPARENT,  KC_W,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_BSPC,
    KC_TRANSPARENT, KC_A, KC_S, KC_D, KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,
    KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_UP,  KC_ENTER,
    KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  TD(DANCE_6),  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_LEFT,  KC_DOWN,  KC_RIGHT
),

};



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case TD(DANCE_0):
    case TD(DANCE_1):
    case TD(DANCE_3):
    case TD(DANCE_7):
        action = &tap_dance_actions[TD_INDEX(keycode)];
        if (!record->event.pressed && action->state.count && !action->state.finished) {
            tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
            tap_code16(tap_hold->tap);
        }
        break;
  }
  return true;
}

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo+=1;
            } else {
                muse_tempo-=1;
            }
        }
    } else {
        if (clockwise) {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_DOWN);
            unregister_code(KC_MS_WH_DOWN);
        #else
            register_code(KC_PGDN);
            unregister_code(KC_PGDN);
        #endif
        } else {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_UP);
            unregister_code(KC_MS_WH_UP);
        #else
            register_code(KC_PGUP);
            unregister_code(KC_PGUP);
        #endif
        }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
        return false;
    default:
        return true;
    }
}
#endif

/* BEGIN Lighting Layers by JCanto */

// Light LEDs 1 to 4 red when _LOWER is active.
const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_GREEN}       // Light 9 LEDs, starting with LED 1
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_BLUE}       // Light 9 LEDs, starting with LED 1
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_RED}       // Light 9 LEDs, starting with LED 1
);

const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_MAGENTA}       // Light 9 LEDs, starting with LED 1
);

const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_PURPLE}       // Light 9 LEDs, starting with LED 1
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_lower_layer, //  index 0 of the array
    my_raise_layer, //  index 1
    my_adjust_layer, // index 2
    my_layer4_layer,  // index 3
    my_layer5_layer  // index 4
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}
/* END Lighting Layers by JCanto */

// uint8_t layer_state_set_user(uint8_t state) {
//     return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
// }

// uint8_t layer_state_set_user(uint8_t state) {
//     state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
//     switch (get_highest_layer(state)) {
//     case _RAISE:
//         //rgblight_setrgb (RGB_BLUE);
//         rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
//         break;
//     case _LOWER:
//         //rgblight_setrgb (RGB_GREEN);
//         rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
//         break;
//     case _LAYER4:
//         //rgblight_setrgb (RGB_MAGENTA);
//         rgblight_set_layer_state(4, layer_state_cmp(state, _LAYER4));
//         break;
//     case _ADJUST:
//         //rgblight_setrgb (RGB_RED);
//         rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
//         break;
//     default: //  for any other layers, or the default layer
//         rgblight_setrgb (0x00,  0xFF, 0xFF);
//         break;
//     }
//   return state;
// }

uint8_t layer_state_set_user(uint8_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    rgblight_set_layer_state(0, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(1, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(2, layer_state_cmp(state, _ADJUST));
    rgblight_set_layer_state(3, layer_state_cmp(state, _LAYER4));
    rgblight_set_layer_state(4, layer_state_cmp(state, _LAYER5));

    return state;
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

/* CAPS WORD by JCanto */
void caps_word_set_user(bool active) {
    if (active) {
        PLAY_SONG(cwords_on);
    } else {
        PLAY_SONG(cwords_off);
    }
}
/* CAPS WORD by JCanto */


#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[4];

uint8_t dance_step(tap_dance_state_t *state);

uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void on_dance_2(tap_dance_state_t *state, void *user_data);
void dance_2_finished(tap_dance_state_t *state, void *user_data);
void dance_2_reset(tap_dance_state_t *state, void *user_data);

void on_dance_2(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_LEFT_SHIFT);
        tap_code16(KC_LEFT_SHIFT);
        tap_code16(KC_LEFT_SHIFT);
    }
    if(state->count > 3) {
        tap_code16(KC_LEFT_SHIFT);
    }
}

void dance_2_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(KC_LEFT_SHIFT); break;
        case SINGLE_HOLD: register_code16(KC_LEFT_SHIFT); break;
        case DOUBLE_TAP: register_code16(KC_LEFT_SHIFT); register_code16(KC_LEFT_SHIFT); break;
        case DOUBLE_HOLD: register_code16(LGUI(KC_D)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_LEFT_SHIFT); register_code16(KC_LEFT_SHIFT);
    }
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(KC_LEFT_SHIFT); break;
        case SINGLE_HOLD: unregister_code16(KC_LEFT_SHIFT); break;
        case DOUBLE_TAP: unregister_code16(KC_LEFT_SHIFT); break;
        case DOUBLE_HOLD: unregister_code16(LGUI(KC_D)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_LEFT_SHIFT); break;
    }
    dance_state[0].step = 0;
}
void on_dance_4(tap_dance_state_t *state, void *user_data);
void dance_4_finished(tap_dance_state_t *state, void *user_data);
void dance_4_reset(tap_dance_state_t *state, void *user_data);

void on_dance_4(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_LEFT_CTRL);
        tap_code16(KC_LEFT_CTRL);
        tap_code16(KC_LEFT_CTRL);
    }
    if(state->count > 3) {
        tap_code16(KC_LEFT_CTRL);
    }
}

void dance_4_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_LEFT_CTRL); break;
        case SINGLE_HOLD: register_code16(KC_LEFT_CTRL); break;
        case DOUBLE_TAP: register_code16(KC_LEFT_CTRL); register_code16(KC_LEFT_CTRL); break;
        case DOUBLE_HOLD: register_code16(LGUI(LSFT(KC_D))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_LEFT_CTRL); register_code16(KC_LEFT_CTRL);
    }
}

void dance_4_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_LEFT_CTRL); break;
        case SINGLE_HOLD: unregister_code16(KC_LEFT_CTRL); break;
        case DOUBLE_TAP: unregister_code16(KC_LEFT_CTRL); break;
        case DOUBLE_HOLD: unregister_code16(LGUI(LSFT(KC_D))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_LEFT_CTRL); break;
    }
    dance_state[1].step = 0;
}
void dance_5_finished(tap_dance_state_t *state, void *user_data);
void dance_5_reset(tap_dance_state_t *state, void *user_data);

void dance_5_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[2].step = dance_step(state);
    switch (dance_state[2].step) {
        case SINGLE_HOLD: layer_on(_LOWER); break;
        case DOUBLE_TAP: layer_move(5); break;
    }
}

void dance_5_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[2].step) {
        case SINGLE_HOLD:
          layer_off(_LOWER);
        break;
    }
    dance_state[2].step = 0;
}
void dance_6_finished(tap_dance_state_t *state, void *user_data);
void dance_6_reset(tap_dance_state_t *state, void *user_data);

void dance_6_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[3].step = dance_step(state);
    switch (dance_state[3].step) {
        case DOUBLE_TAP: layer_move(0); break;
    }
}

void dance_6_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[3].step) {
    }
    dance_state[3].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_TAP_HOLD(KC_O, KC_MINUS),
        [DANCE_1] = ACTION_TAP_DANCE_TAP_HOLD(KC_P, KC_EQUAL),
        [DANCE_3] = ACTION_TAP_DANCE_TAP_HOLD(KC_UP, KC_SLASH),
        [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [DANCE_4] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_4, dance_4_finished, dance_4_reset),
        [DANCE_5] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_5_finished, dance_5_reset),
        [DANCE_6] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_6_finished, dance_6_reset),
        [DANCE_7] = ACTION_TAP_DANCE_TAP_HOLD(KC_E, KC_MCTL),
};
