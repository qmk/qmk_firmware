/* Copyright 2020 Stephen Bush
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

/*
 *  qmk compile -kb planck/rev6 -km muppetjones
 */

#include QMK_KEYBOARD_H
#include "muse.h"
#include "muppetjones.h"

#define LAYOUT_planck_wrapper(...) LAYOUT_planck_grid(__VA_ARGS__)

/* Extend layers from muppetjones.h
    _CLMK_DH = 0,
    _QWERTY
    _MOUSE,
    _LOWER,
    _RAISE,
    _NAV,
    _ADJUST,
 */
enum planck_layers {
    _PLOVER = _ADJUST + 1,
};

enum planck_keycodes {
    PLOVER = SAFE_RANGE,
    BACKLIT,
    EXT_PLV,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off

/* Colemak DH II
 * ,-----------------------------------------------------------------------------------.
 * |   Q  |   W  |   F  |   P  |   B  |  Del | Bksp |   J  |   L  |   U  |   Y  |   ;  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   A  |   R  |   S  |   T  |   G  |      |  "   |   M  |   N  |   E  |   I  |   O  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   Z  |   X  |   C  |   D  | V SFT| Enter| Tab  |   K  |   H  |   ,  |   .  |   /  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  |HY_ESC|Lower |    Space    |Raise |HY_ESC| Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_CLMK_DH] = LAYOUT_planck_wrapper(
    __COLEMAK_MOD_DH_L1________________________, KC_DEL,  KC_BSPC, __COLEMAK_MOD_DH_R1_W_QUOT_________________,
    __COLEMAK_MOD_DH_L2_W_GACS_________________, CW_TOGG, KC_QUOT, __COLEMAK_MOD_DH_R2_W_SCAG_________________,
    __COLEMAK_MOD_DH_L3_W_SFTV_________________, KC_ENT,  KC_TAB,  __COLEMAK_MOD_DH_R3________________________,
    TD_LAYR,  XXXXXXX, XXXXXXX, HY_ESC, LOW_ENT, KC_BSPC, KC_BSPC, RAI_SPC, HY_ESC,  KC_BSPC, XXXXXXX, XXXXXXX
),

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_wrapper(
    __QWERTY_L1________________________________, _______, _______, __QWERTY_R1________________________________,
    __QWERTY_L2________________________________, _______, _______, __QWERTY_R2________________________________,
    __QWERTY_L3________________________________, _______, _______, __QWERTY_R3________________________________,
    __BLANK____________________________________, _______, _______, __BLANK____________________________________
),

/* MOUSE
 * No encoders. Just an empty layer.
 */
[_MOUSE] = LAYOUT_planck_wrapper(
    __BLANK____________________________________, _______, _______, __BLANK____________________________________,
    __BLANK____________________________________, _______, _______, __BLANK____________________________________,
    __BLANK____________________________________, _______, _______, __BLANK____________________________________,
    __BLANK____________________________________, _______, _______, __BLANK____________________________________
),

// /* Colemak DH
//  * ,-----------------------------------------------------------------------------------.
//  * | Tab  |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * | Esc  |   A  |   R  |   S  |   T  |   G  |   M  |   N  |   E  |   I  |   O  |  "   |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * | Shift|   Z  |   X  |   C  |   D  |   V  |   K  |   H  |   ,  |   .  |   /  |Enter |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
//  * `-----------------------------------------------------------------------------------'
//  */
// [_CLMK_DH] = LAYOUT_planck_grid(
//     KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
//     HY_ESC,  HOME_A,  HOME_R,  HOME_S,  HOME_T,  KC_G,    KC_M,    HOME_N,  HOME_E,  HOME_I, HOME_O, KC_QUOT,
//     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, SC_SENT,
//     KC_LCTL, NUMPD,   KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX
// ),
/* Lower (numpad, symbols)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |   (  |   )  |  ~   |      |      |      |  7 & |  8 * |  9 ( |   \  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |   {  |   }  |  `   |      |      | -  _ |  4 $ |  5 % |  6 ^ |   *  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |   [  |   ]  |      |      |      | =  + |  1 ! |  2 @ |  3 # |   |  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Space    |      |   0  |   .  |      |      |
 * `-----------------------------------------------------------------------------------'
 * 21.02.22: Removed F keys.
 * 21.03.28: Completely revamped to contain 10-key numpad and symbols.
 */
[_LOWER] = LAYOUT_planck_wrapper(
    __SYMBOLS_L1_______________________________, _______, _______, __NUMPAD_R1________________________________,
    __SYMBOLS_L2_______________________________, _______, _______, __NUMPAD_R2________________________________,
    __SYMBOLS_L3_______________________________, _______, _______, __NUMPAD_R3________________________________,
    _______, _______, _______, _______, _______, _______, _______, __NUMPAD_R4________________________________
),

/* Raise
* ,-----------------------------------------------------------------------------------.
* |   `  |      |      |      |      |      |      | Pg Up| HOME |      | END  |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* | GUI  | ALT  | CTL  | SFT  |      |      |      | Pg Dn| LEFT | DOWN |  UP  |RIGHT |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      |      |      |      |      |      |      |      |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
* `-----------------------------------------------------------------------------------'
* 21.02.22: Removed F keys and replaced with useful programming keys.
*/
[_RAISE] = LAYOUT_planck_wrapper(
    XXXXXXX, XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX, _______, _______, __NAV_R1___________________________________,
    KC_LGUI, KC_LALT, HR_LBRC, HR_RBRC, KC_MINS, _______, _______, __NAV_R2___________________________________,
    XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, KC_EQL,  _______, _______, __NAV_R3___________________________________,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Nav
 * Available in raise.
 */
[_NAV] = LAYOUT_planck_wrapper(
    __BLANK____________________________________, _______, _______, __BLANK____________________________________,
    __BLANK____________________________________, _______, _______, __BLANK____________________________________,
    __BLANK____________________________________, _______, _______, __BLANK____________________________________,
    __BLANK____________________________________, _______, _______, __BLANK____________________________________
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_PLOVER] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Brite |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|CLMKII|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|ClmkDH|      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_wrapper(
    __ADJUST_L1________________________________, AU_NEXT, PLOVER,  __MEDIA_R1_________________________________,
    __ADJUST_L2________________________________, AU_PREV, CLMK_DH, __MEDIA_R2_________________________________,
    __ADJUST_L3________________________________, MU_NEXT, QWERTY,  __MEDIA_R3_________________________________,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
)

/*
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
[_ADJUST] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

 */
    // clang-format on
};

#ifdef AUDIO_ENABLE
float plover_song[][2]    = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

#define LIGHT_GOLDEN 30, 255, 100
#define LIGHT_MAGENTA 213, 255, 100
#define LIGHT_AZURE 148, 255, 100

// Define light layers
// -- e.g., light up LEDS 3-6 with RED when the numpd layer is active
const rgblight_segment_t PROGMEM rgb_clmk_dh[] = RGBLIGHT_LAYER_SEGMENTS({0, 9, HSV_RED});
const rgblight_segment_t PROGMEM rgb_lower[]   = RGBLIGHT_LAYER_SEGMENTS({0, 9, LIGHT_GOLDEN});
const rgblight_segment_t PROGMEM rgb_raise[]   = RGBLIGHT_LAYER_SEGMENTS({0, 9, LIGHT_MAGENTA});
const rgblight_segment_t PROGMEM rgb_numpd[]   = RGBLIGHT_LAYER_SEGMENTS({0, 9, LIGHT_AZURE});

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(rgb_clmk_dh, rgb_lower, rgb_raise, rgb_numpd);

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;  // Enable the LED layers
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    return state;
}

bool process_record_keymap(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
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
    }

    return true;
}

bool     muse_mode      = false;
uint8_t  last_muse_note = 0;
uint16_t muse_counter   = 0;
uint8_t  muse_offset    = 70;
uint16_t muse_tempo     = 50;

bool encoder_update(bool clockwise) {
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

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) {
                    PLAY_SONG(plover_song);
                }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) {
                    PLAY_SONG(plover_gb_song);
                }
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
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
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
