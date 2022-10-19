/* Copyright 2015-2017 Jack Humbert
 * Portions Copyright 2020 Joel Elkins
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "jdelkins.h"
#include "muse.h"

#ifdef LAYOUT
#undef LAYOUT
#endif
#define LAYOUT LAYOUT_planck_2x2u

uint16_t bspc_timer;

enum {
    MY_BSPC = USER_SAFE_RANGE,
    BACKLIT,
};

// recycle unused layers defined in my userspace
#define _RAISE _FUNC
#define _LOWER _SECRETS

#define KP MO(_KP)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

int ctl_state = 0;

void ctl_finished(qk_tap_dance_state_t *state, void *user_data) {
    ctl_state = cur_dance(state);
    switch (ctl_state) {
        case SINGLE_TAP:    qk_leader_start(); break;
        case SINGLE_HOLD:   register_code(KC_LCTL); break;
        case DOUBLE_TAP:    tap_code(KC_RCTL); break;
        case DOUBLE_HOLD:   register_code(KC_RCTL); break;
        case TRIPLE_TAP:    tap_code(KC_RCTL); tap_code(KC_RCTL); break;
        case TRIPLE_HOLD:   tap_code(KC_RCTL); register_code(KC_RCTL); break;
    }
}

void ctl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (ctl_state) {
        case SINGLE_HOLD:   unregister_code(KC_LCTL); break;
        case DOUBLE_HOLD:
        case TRIPLE_HOLD:   unregister_code(KC_RCTL); break;
    }
    ctl_state = 0;
}

void g_finished(qk_tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state)) {
        case SINGLE_TAP:
            tap_code16(C(KC_END));
            break;
        case DOUBLE_TAP:
            tap_code16(C(KC_HOME));
            break;
    }
}

int kp_state = 0;

void kp_finished(qk_tap_dance_state_t *state, void *user_data) {
    kp_state = hold_cur_dance(state);
    switch (kp_state) {
        case SINGLE_HOLD: layer_on(_KP);  break;
        case DOUBLE_HOLD: layer_on(_RPT); break;
    }
}

void kp_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (kp_state) {
        case SINGLE_HOLD: layer_off(_KP);  break;
        case DOUBLE_HOLD: layer_off(_RPT); break;
    }
    kp_state = 0;
}

enum {
    TD_LDCTL,
    TD_G,
    TD_KP
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LDCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctl_finished, ctl_reset),
    [TD_G]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, g_finished, NULL),
    [TD_KP]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, kp_finished, kp_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  `   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Gui  | Alt  |Keypad|    Bksp     |    Space    | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT(
    KC_TAB,       KC_Q,        KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_GRV,
    KC_LCTL,      KC_A,        KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,      KC_Z,        KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    TD(TD_LDCTL), MO(_ADJUST), MY_GUI,  MY_ALT,      MY_BSPC,          MY_SPC,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Same as _QWERTY but disable wutoshift */
[_RPT] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,      _______,         _______,      _______, _______, _______, _______
),

[_GAME] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_NO,   KC_LALT, RAISE,         KC_SPC,          KC_SPC,      _______, _______, _______, _______
),

[_RAISE] = LAYOUT(
    KC_ESC,  _______, FW_WRD,  KB_EOL,  TG(_RPT), _______,  KB_COPY, KC_PGUP, _______, KC_LPRN,  KC_RPRN,  KC_MINS,
    KC_RCTL, KB_BOL,  _______, KC_PGDN, _______,  TD(TD_G), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  _______,  KC_BSLS,
    _______, _______, KC_DEL,  KC_CAPS, KB_PASTE, BK_WRD,   _______, _______, _______, _______,  _______,  MY_CALC,
    KC_RCTL, _______, _______, _______,        _______,          _______,     KC_HOME, KC_PGDN,  KC_PGUP,  KC_END
),

[_KP] = LAYOUT(
    KC_ESC,  KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F13,  KC_F14,   KC_7,    KC_8,    KC_9,    KC_MINS, KC_EQL,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX, XXXXXXX,  KC_4,    KC_5,    KC_6,    KC_ASTR, _______,
    KC_NUM,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX, XXXXXXX,  KC_1,    KC_2,    KC_3,    KC_SLSH, _______,
    _______, _______, _______, _______,     _______,          _______,       KC_0,    KC_DOT,  KC_PLUS, KC_END
),

[_LOWER] = LAYOUT(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LCBR, KC_RCBR, KC_EQL,
    _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, _______, _______, _______, KC_LBRC, KC_RBRC, KC_PIPE,
    _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______, _______, _______, KC_HOME, KC_END,  KC_MPLY,
    _______, _______, _______, _______,       _______,         _______,     KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
),

[_ADJUST] = LAYOUT(
    _______, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL,
    KC_RCTL, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, TG(_KP), KC_BRID, KC_BRIU, KC_MUTE,
    _______, RGB_TOG, KB_MAKE, KB_FLSH, KB_VRSN, KB_BOOT, _______, TG_SYS,  _______, _______, _______, KC_MPLY,
    KC_RCTL, _______, _______, _______,      _______,          _______,     KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
)

/* [_ADJUST] = LAYOUT( */
/*     _______, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL , */
/*     _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK,  DVORAK,  PLOVER,  _______, */
/*     _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______, */
/*     _______, _______, _______, _______,      _______,          _______,     _______, _______, _______,  _______ */
/* ) */

};

/* plwnck rev6 RGB layout:
 * ----------------------------------
 * |   6       5       4        3   |
 * |               0                |
 * |   7       8       1        2   |
 * ----------------------------------
 */

const rgblight_segment_t PROGMEM rpt_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 2, HSV_PINK},
    {7, 2, HSV_PINK}
);

const rgblight_segment_t PROGMEM game_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 2, HSV_RED},
    {6, 2, HSV_RED}
);

const rgblight_segment_t PROGMEM raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 4, HSV_GREEN}
);

const rgblight_segment_t PROGMEM kp_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 8, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 4, HSV_BLUE}
);

const rgblight_segment_t PROGMEM adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 8, HSV_BLUE}
);

const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_WHITE},
    {8, 1, HSV_WHITE}
);

const rgblight_segment_t PROGMEM numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 2, HSV_PURPLE}
);

enum rgb_layer_index {
    L_RPT,
    L_GAME,
    L_RAISE,
    L_KP,
    L_LOWER,
    L_ADJUST,
    L_CAPSLOCK,
    L_NUMLOCK
};

const rgblight_segment_t * const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    [L_RPT] = rpt_layer,
    [L_GAME] = game_layer,
    [L_RAISE] = raise_layer,
    [L_KP] = kp_layer,
    [L_LOWER] = lower_layer,
    [L_ADJUST] = adjust_layer,
    [L_CAPSLOCK] = capslock_layer,
    [L_NUMLOCK] = numlock_layer
);

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_keymap(layer_state_t state) {
    rgblight_set_layer_state(L_RPT, layer_state_cmp(state, _RPT));
    rgblight_set_layer_state(L_GAME, layer_state_cmp(state, _GAME));
    rgblight_set_layer_state(L_RAISE, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(L_KP, layer_state_cmp(state, _KP));
    rgblight_set_layer_state(L_LOWER, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(L_ADJUST, layer_state_cmp(state, _ADJUST));
    rgblight_set_layer_state(L_CAPSLOCK, CAPSLOCK_ON);
    rgblight_set_layer_state(L_NUMLOCK, NUMLOCK_ON && layer_state_cmp(state, _KP));
    if (layer_state_cmp(state, _GAME) || layer_state_cmp(state, _RPT))
        autoshift_disable();
    else
        autoshift_enable();
    return update_tri_layer_state(state, _KP, _RAISE, _LOWER);
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(L_CAPSLOCK, led_state.caps_lock);
    rgblight_set_layer_state(L_NUMLOCK, led_state.num_lock && layer_state_is(_KP));
    return true;
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    bool rc = true;
    static bool bspc_del = false;
    static bool bspc_initiated_func = false;

    switch (keycode) {
        case MY_BSPC:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_KP)) {
                    // special case: if _KP was turned on by another key,
                    // treat this as KC_DEL and don't do anything else
                    bspc_del = true;
                    register_code(KC_DEL);
                    return false;
                } else {
                    bspc_timer = timer_read();
                    bspc_initiated_func = true;
                    layer_on(_KP);
                }
            } else {
                if (bspc_del) {
                    // special case: if _KP was turned on by another key,
                    // treat this as KC_DEL and don't do anything else
                    unregister_code(KC_DEL);
                    bspc_del = false;
                    return false;
                }

                if (bspc_initiated_func) {
                    layer_off(_KP);
                    bspc_initiated_func = false;
                }

                if (bspc_timer > 0) {
                    // here the key was pressed and released before the timer
                    // expired, so treat as a backspace tap and pretend we
                    // never activated _KP
                    bspc_timer = 0;
                    tap_code(KC_BSPC);
                } else {
                    // the timer went off, so KC_BSPC was registered in
                    // matrix_scan_keymap. unregister it now
                    unregister_code(KC_BSPC);
                }
            }
            return false; // special case, return now without resetting timer
                          // other paths should set rc and break
            break;

        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
                backlight_step();
#endif
            } else {
                unregister_code(KC_RSFT);
            }
            rc = false;
            break;
    }

    bspc_timer = 0;
    return rc;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

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
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}

void keyboard_post_init_keymap(void) {
    rgblight_layers = my_rgb_layers;
    bspc_timer = 0;
}

LEADER_EXTERNS();

void matrix_scan_keymap(void) {
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
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
    // if MY_BSPC is held down too long, pretend like it wasn't and start
    // pressing backspace
    if (bspc_timer > 0 && timer_elapsed(bspc_timer) > LEADER_TIMEOUT) {
        layer_off(_KP);
        bspc_timer = 0;
        register_code(KC_BSPC);
    }
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_K) {
            layer_invert(_KP);
        }
        SEQ_ONE_KEY(KC_G) {
            layer_invert(_GAME);
        }
        SEQ_ONE_KEY(KC_KP_5) {
            layer_invert(_KP);
        }
        SEQ_ONE_KEY(KC_5) {
            layer_invert(_KP);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_1) {
            send_secret_string(0);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_2) {
            send_secret_string(1);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_3) {
            send_secret_string(2);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_4) {
            send_secret_string(3);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_5) {
            send_secret_string(4);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_6) {
            send_secret_string(5);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_M) {
            send_secret_string(0);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_COMM) {
            send_secret_string(1);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_DOT) {
            send_secret_string(2);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_J) {
            send_secret_string(3);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_K) {
            send_secret_string(4);
        }
        SEQ_TWO_KEYS(KC_SCLN, KC_L) {
            send_secret_string(5);
        }
        SEQ_ONE_KEY(KC_C) {
            tap_code16(C(KC_C));
        }
        // neovim: terminal escape
        SEQ_ONE_KEY(KC_QUOT) {
            tap_code16(C(KC_BSLS));
            tap_code16(C(KC_N));
        }
    }
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
