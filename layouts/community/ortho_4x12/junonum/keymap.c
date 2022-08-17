#include QMK_KEYBOARD_H
#include "muse.h"

enum planck_layers {
    _QWERTY,
    _COLEMAK,
    _DVORAK,
    _LOWER,
    _RAISE,
    _PLOVER,
    _ADJUST,

    _FN1,
    _DPAD,
    _DPADNUM
};

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    DVORAK,
    PLOVER,
    BACKLIT,
    EXT_PLV,

    DP_ON,
    DP_OFF
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SPACEFN LT(_FN1, KC_SPC)
#define DPADNUM MO(_DPADNUM)

// Homerow mods
#define MD_A    LALT_T(KC_A)
#define MD_S    LGUI_T(KC_S)
#define MD_D    LCTL_T(KC_D)
#define MD_F    LSFT_T(KC_F)

#define MD_J    RSFT_T(KC_J)
#define MD_K    RCTL_T(KC_K)
#define MD_L    RGUI_T(KC_L)
#define MD_SCLN RALT_T(KC_SCLN)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_ortho_4x12(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  MD_A,    MD_S,    MD_D,    MD_F,    KC_G,    KC_H,    MD_J,    MD_K,    MD_L,    MD_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
        _______, KC_LCTL, KC_LGUI, KC_LALT, LOWER,   SPACEFN, SPACEFN, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
        ),

    [_COLEMAK] = LAYOUT_ortho_4x12(
        KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
        KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
        _______, KC_LCTL, KC_LGUI, KC_LALT, LOWER,   SPACEFN, SPACEFN, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
    ),

    [_DVORAK] = LAYOUT_ortho_4x12(
        KC_ESC,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
        KC_TAB,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_QUOT,
        KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT ,
        _______, KC_LCTL, KC_LGUI, KC_LALT, LOWER,   SPACEFN, SPACEFN, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
    ),

    [_LOWER] = LAYOUT_ortho_4x12(
        KC_TILD, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_DLR,  KC_PERC, KC_CIRC, KC_UNDS, KC_PIPE,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_EXLM, KC_AT,   KC_HASH, KC_PLUS, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MPLY
    ),

    [_RAISE] = LAYOUT_ortho_4x12(
        KC_GRV,  _______, _______, KC_LBRC, KC_RBRC, _______, _______, KC_7,    KC_8,    KC_9,   KC_0,     _______,
        _______, _______, _______, KC_LCBR, KC_RCBR, _______, _______, KC_4,    KC_5,    KC_6,   KC_MINUS, KC_BSLS,
        _______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,   KC_EQUAL, KC_ENT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MPLY
    ),

    [_PLOVER] = LAYOUT_ortho_4x12(
        KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
        XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [_ADJUST] = LAYOUT_ortho_4x12(
        _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
        _______, _______, MU_MOD,  AU_ON,   AU_OFF,  CG_NORM, CG_SWAP, QWERTY,  COLEMAK,  DVORAK,  PLOVER,  _______,
        _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
    ),

    [_FN1] = LAYOUT_ortho_4x12(
        KC_APP,  DP_ON,   KC_PGDN, KC_UP,   KC_PGUP, KC_INS,  KC_CAPS, KC_PGUP, KC_UP,   KC_PGDN, KC_PSCR, _______,
        _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_HOME, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_DEL ,
        _______, _______, _______, _______, _______, KC_END,  KC_END,  _______, KC_VOLD, KC_VOLU, KC_MUTE, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, DP_ON,   _______, _______, _______
    ),

    // Slightly modified layer with inverted T-shaped directional pad
    [_DPAD] = LAYOUT_ortho_4x12(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_ENT ,
        XXXXXXX, KC_LCTL, KC_LGUI, KC_LALT, DPADNUM, KC_SPC,  KC_SPC,  DPADNUM, DP_OFF,  KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Extended numeric layer for FPS weapon switching and StarCraft group control
    [_DPADNUM] = LAYOUT_ortho_4x12(
        KC_LGUI, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DP_OFF,  XXXXXXX,
        KC_LCTL, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX, KC_F10,  KC_F11,  KC_F12,  XXXXXXX,
        KC_LSFT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_SLSH, XXXXXXX,
        _______, _______, _______, _______, DPADNUM, XXXXXXX, XXXXXXX, DPADNUM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};

#ifdef AUDIO_ENABLE
float plover_song[][2]    = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);

float caps_song_on[][2]  = SONG(NUM_LOCK_ON_SOUND);
float caps_song_off[][2] = SONG(SCROLL_LOCK_ON_SOUND);

// Custom songs for DPAD layer status
float dpad_song_on[][2] = {
	HD_NOTE(_A4), HD_NOTE(_A4), HD_NOTE(_A4),
	QD_NOTE(_F4), QD_NOTE(_C5), HD_NOTE(_A4),
	QD_NOTE(_F4),  QD_NOTE(_C5), WD_NOTE(_A4)
};

float dpad_song_off[][2] = {
	ED_NOTE(_C6), ED_NOTE(_C6),
	ED_NOTE(_C6), ED_NOTE(_C6),
	W__NOTE(_REST), QD_NOTE(_GS5),
	QD_NOTE(_AS5), Q__NOTE(_C6),
	Q__NOTE(_AS5), Q__NOTE(_C6)
};
#endif

#ifndef BACKLIGHT_ENABLE
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#else

layer_state_t layer_state_set_user(layer_state_t state) {
    // LED control, lighting up when Fn layer is activated
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    switch (get_highest_layer(state)) {
        case _QWERTY:
            backlight_set(0);
            break;
        case _FN1:
            backlight_set(3);
            break;
        case _DPAD:
            backlight_set(3);
            break;
    }
    return state;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                print("mode just switched to qwerty and this is a huge string\n");
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
        case DVORAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DVORAK);
            }
            return false;
            break;
        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
                backlight_step();
#endif
#ifdef KEYBOARD_planck_rev5
                writePinLow(E6);
#endif
            } else {
                unregister_code(KC_RSFT);
#ifdef KEYBOARD_planck_rev5
                writePinHigh(E6);
#endif
            }
            return false;
            break;
        case PLOVER:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(plover_song);
#endif
                layer_off(_RAISE);
                layer_off(_LOWER);
                layer_off(_ADJUST);
                layer_on(_PLOVER);
                if (!eeconfig_is_enabled()) {
                    eeconfig_init();
                }
                keymap_config.raw  = eeconfig_read_keymap();
                keymap_config.nkro = 1;
                eeconfig_update_keymap(keymap_config.raw);
            }
            return false;
            break;
        case EXT_PLV:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(plover_gb_song);
#endif
                layer_off(_PLOVER);
            }
            return false;
            break;

            // Play audio upon switching Caps Lock and custom layers

        case KC_CAPS:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                if (host_keyboard_led_state().caps_lock) {
                    PLAY_SONG(caps_song_off);
                } else {
                    PLAY_SONG(caps_song_on);
                }
#endif
            }
            return true;

        case DP_ON:
            if (record->event.pressed) {
            } else {  // only actived upon key release
#ifdef AUDIO_ENABLE
                PLAY_SONG(dpad_song_on);
#endif

                layer_off(_FN1);
                layer_on(_DPAD);
            }

        case DP_OFF:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(dpad_song_off);
#endif

                layer_off(_DPAD);
            }
    }
    return true;
}

bool     muse_mode      = false;
uint8_t  last_muse_note = 0;
uint16_t muse_counter   = 0;
uint8_t  muse_offset    = 70;
uint16_t muse_tempo     = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo += 1;
            } else {
                muse_tempo -= 1;
            }
        }
    } else {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(plover_song);
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                PLAY_SONG(plover_gb_song);
#endif
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
#ifdef AUDIO_ENABLE
                stop_all_notes();
#endif
            }
    }
    return true;
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
