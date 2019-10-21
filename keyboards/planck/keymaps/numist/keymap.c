#include QMK_KEYBOARD_H
#include "keymap_steno.h"
#include "muse.h"

extern keymap_config_t keymap_config;

enum planck_layers { _QWERTY, _COLEMAK, _FN, _NUM, _LOWER, _RAISE, _PLOVER, _ADJUST };

enum planck_keycodes { QWERTY = SAFE_RANGE, COLEMAK, PLOVER, EXT_PLV, DYNAMIC_MACRO_RANGE };

enum planck_macros {
    KC_M_UNDO,
    KC_M_CUT,
    KC_M_COPY,
    KC_M_PASTE,
    KC_M_FIND,
    KC_M_AGAIN,
};

#define DYNAMIC_MACRO_SIZE 256
#include "dynamic_macro.h"

#define LOWER LT(_LOWER, KC_BSPC)
#define RAISE LT(_RAISE, KC_BSPC)
#define FN_SPC LT(_FN, KC_SPC)

#define CAG_ESC LCAG_T(KC_ESC)

#define LS_PGUP LSFT_T(KC_PGUP)
#define LS_HOME LSFT_T(KC_HOME)

#define NP_PGDN LT(_NUM, KC_PGDN)

#define RS_ENT RSFT_T(KC_ENT)

#define M_UNDO M(KC_M_UNDO)
#define M_CUT M(KC_M_CUT)
#define M_COPY M(KC_M_COPY)
#define M_PSTE M(KC_M_PASTE)
#define M_FIND M(KC_M_FIND)
#define M_AGAIN M(KC_M_AGAIN)

#define M_RECD1 DYN_REC_START1
#define M_STOP1 DYN_REC_STOP
#define M_PLAY1 DYN_MACRO_PLAY1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
    CAG_ESC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
    LS_PGUP, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, RS_ENT ,
    NP_PGDN, KC_LCTL, KC_LALT, KC_LGUI, LOWER  , FN_SPC , FN_SPC , RAISE  , KC_RSFT, KC_RCTL, KC_BTN1, XXXXXXX
),

[_COLEMAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    CAG_ESC, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    LS_PGUP, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, RS_ENT ,
    NP_PGDN, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   FN_SPC,  FN_SPC,  RAISE,   KC_RSFT, KC_RCTL, KC_BTN1, XXXXXXX
),

[_FN] = LAYOUT_planck_grid(
    KC_GRV , M_RECD1, M_STOP1, M_PLAY1, KC_MPRV, KC_MPLY, KC_MNXT, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, XXXXXXX,
    _______, KC_LCTL, KC_LALT, KC_LGUI, M_FIND , M_AGAIN, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, XXXXXXX, XXXXXXX,
    LS_HOME, M_UNDO , M_CUT  , M_COPY , M_PSTE , XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, KC_BSLS, KC_PIPE,
    KC_END , _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX
),

[_NUM] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_7   , KC_8   , KC_9   , XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_4   , KC_5   , KC_6   , XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_1   , KC_2   , KC_3   , XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_0   , KC_DOT , XXXXXXX, XXXXXXX, XXXXXXX
),

[_RAISE] = LAYOUT_planck_grid(
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,   KC_6 , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL ,
    KC_DEL , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,  KC_F6 , KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_HASH, KC_BSLS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX
),

// Lisa Simpson says: "_LOWER is just S(_RAISE)!"
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL ,
    KC_DEL , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_TILD, KC_PIPE, KC_HOME, KC_END,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX
),

};

#ifdef AUDIO_ENABLE
float plover_song[][2]    = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
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
    }
    return true;
}

bool     muse_mode      = false;
uint8_t  last_muse_note = 0;
uint16_t muse_counter   = 0;
uint8_t  muse_offset    = 70;
uint16_t muse_tempo     = 50;

void matrix_init_user() {
    eeconfig_init();
    steno_set_mode(STENO_MODE_GEMINI);  // or STENO_MODE_BOLT
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
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch (id) {
        case KC_M_UNDO:
            return MACRODOWN(D(LGUI), T(Z), U(LGUI), END);
        case KC_M_CUT:
            return MACRODOWN(D(LGUI), T(X), U(LGUI), END);
        case KC_M_COPY:
            return MACRODOWN(D(LGUI), T(C), U(LGUI), END);
        case KC_M_PASTE:
            return MACRODOWN(D(LGUI), T(V), U(LGUI), END);
        case KC_M_FIND:
            return MACRODOWN(D(LGUI), T(F), U(LGUI), END);
        case KC_M_AGAIN:
            return MACRODOWN(D(LGUI), T(G), U(LGUI), END);
    }

    return MACRO_NONE;
}
