/* Copyright 2020 Stuart Fong
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

#include QMK_KEYBOARD_H
#include "muse.h"

enum planck_layers 
{
    _COLEMAK,
    _PLOVER,
    _LOWER,
    _RAISE,
    _SYMBOL,
    _FUNCTION,
    _ADJUST
};

enum planck_keycodes {
    COLEMAK = SAFE_RANGE,
    PLOVER,
    EXT_PLV,
    CBR,  // {}
    PRN,  // ()
    BRC,  // []
    DQUO, // ""
    PRTSC3, // Capture Entire Screen
    PRTSC4, // Capture Selected Portion
    PRTSC5  // Screenshot Toolbar
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SYMBOL MO(_SYMBOL)
#define FUNCTION MO(_FUNCTION)

#define LTL LT(LOWER, KC_BSPC)
#define LTS LT(SYMBOL, KC_TAB)
#define LTF LT(FUNCTION, KC_ENT)
#define LTR LT(RAISE, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = 
{
    /* Colemak
     * ,-----------------------------------------------------------------------------------.
     * |   Q  |   W  |   F  |   P  |   B  |Macro1|Macro2|   J  |   L  |   U  |   Y  |   ;  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   A  |   R  |   S  |   T  |   G  |Play 1|Play 2|   M  |   N  |   E  |   I  |   O  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   Z  |   X  |   C  |   D  |   V  | Shift| Shift|   K  |   H  |   ,  |   .  |   /  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl | Alt  | GUI  | Bksp |  Tab | Caps |  Esc | Enter| Space|  GUI |  Alt | Ctrl |
     * `-----------------------------------------------------------------------------------'
     */
    [_COLEMAK] = LAYOUT_planck_grid(
        KC_Q,    KC_W,    KC_F,    KC_P, KC_B, DM_REC1, DM_REC2, KC_J, KC_L, KC_U,    KC_Y,    KC_SCLN, 
        KC_A,    KC_R,    KC_S,    KC_T, KC_G, DM_PLY1, DM_PLY2, KC_M, KC_N, KC_E,    KC_I,    KC_O, 
        KC_Z,    KC_X,    KC_C,    KC_D, KC_V, KC_LSFT, KC_RSFT, KC_K, KC_H, KC_COMM, KC_DOT,  KC_SLSH, 
        KC_LCTL, KC_LALT, KC_LGUI, LTL,  LTS,  KC_CAPS, KC_ESC,  LTF,  LTR,  KC_RGUI, KC_RALT, KC_RCTL
    ),

    /* Plover layer (http://opensteno.org)
     * ,-----------------------------------------------------------------------------------.
     * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  Tab |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Enter|   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Exit |  Up  | Down |   A  |   O  | Bksp | Space|   E  |   U  | Left | Right|  Esc |
     * `-----------------------------------------------------------------------------------'
     */
    [_PLOVER] = LAYOUT_planck_grid(
        KC_1,    KC_1,    KC_1,    KC_1, KC_1, KC_1,    KC_1,    KC_1, KC_1, KC_1,     KC_1,    KC_1,
        KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R, KC_T,    KC_Y,    KC_U, KC_I, KC_O,     KC_P,    KC_LBRC,
        KC_ENT,  KC_A,    KC_S,    KC_D, KC_F, KC_G,    KC_H,    KC_J, KC_K, KC_L,     KC_SCLN, KC_QUOT,
        EXT_PLV, KC_UP,   KC_DOWN, KC_C, KC_V, KC_BSPC, KC_SPC,  KC_N, KC_M, KC_LEFT,  KC_RGHT, KC_ESC
    ),

    /* Lower
     * ,-----------------------------------------------------------------------------------.
     * |   -  |   '  |   ;  |  {}  |   %  |      |      |   +  |   7  |   8  |   9  |   .  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   _  |   "  |   =  |  ()  |   /  |      |      |   -  |   4  |   5  |   6  |   0  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   \  |   &  |   !  |  []  |   ^  |      |      |   *  |   1  |   2  |   3  |   ,  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      | Enter| Space| Bksp |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_LOWER] = LAYOUT_planck_grid(
        KC_MINS, KC_QUOT, KC_SCLN, CBR,     KC_PERC, XXXXXXX, XXXXXXX, KC_PPLS, KC_P7, KC_P8,   KC_P9,   KC_DOT, 
        KC_UNDS, DQUO,    KC_PEQL, PRN,     KC_PSLS, XXXXXXX, XXXXXXX, KC_PMNS, KC_P4, KC_P5,   KC_P6,   KC_P0, 
        KC_PIPE, KC_AMPR, KC_EXLM, BRC,     KC_CIRC, XXXXXXX, XXXXXXX, KC_PAST, KC_P1, KC_P2,   KC_P3,   KC_COMM, 
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,  LTR,   KC_BSPC, XXXXXXX, XXXXXXX
    ),

    /* Raise
     * ,-----------------------------------------------------------------------------------.
     * |Buttn4|Buttn3|RClick|LClick| Mute |      |      |Accel2| Home | PgDn | PgUp |  End |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |MouseL|MouseU|MouseD|MouseR| VolD |      |      |Accel1| Left | Down |  Up  | Right|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |WheelL|WheelD|WheelU|WheelR| VolU |      |      |Accel0|  RWD | Play |  FFD | Stop |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_RAISE] = LAYOUT_planck_grid(
        KC_BTN4, KC_BTN3, KC_BTN2, KC_BTN1, KC_MUTE, XXXXXXX, XXXXXXX, KC_ACL2, KC_HOME, KC_PGDN, KC_PGUP, KC_END, 
        KC_MS_L, KC_MS_U, KC_MS_D, KC_MS_R, KC_VOLD, XXXXXXX, XXXXXXX, KC_ACL1, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, 
        KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_VOLU, XXXXXXX, XXXXXXX, KC_ACL0, KC_MRWD, KC_MPLY, KC_MFFD, KC_MSTP, 
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    /* Symbol
     * ,-----------------------------------------------------------------------------------.
     * |   !  |   @  |   #  |   $  |      |      |      |      |   +  |   {  |   }  |   '  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   %  |   ^  |   &  |   |  |      |      |      |      |   -  |   (  |   }  |   "  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   =  |   `  |   \  |   ~  |      |      |      |      |   *  |   (  |   )  |   _  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_SYMBOL] = LAYOUT_planck_grid(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PLUS, KC_LCBR, KC_RCBR, KC_QUOT,
        KC_PERC, KC_CIRC, KC_AMPR, KC_PIPE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_LPRN, KC_RPRN, KC_DQUO,
        KC_EQL,  KC_GRV,  KC_BSLS, KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ASTR, KC_LBRC, KC_RBRC, KC_UNDS,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    /* Function
     * ,-----------------------------------------------------------------------------------.
     * |  F1  |  F2  |  F3  |  F4  |PrtSc5|      |      |      |  F13 |  F14 |  F15 |  F16 |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  F5  |  F6  |  F7  |  F8  |PrtSc4|      |      |      |  F17 |  F18 |  F19 |  F20 |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  F9  |  F10 |  F11 |  F12 |PrtSc3|      |      |      |  F21 |  F22 |  F23 |  F24 |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_FUNCTION] = LAYOUT_planck_grid(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   PRTSC5,  XXXXXXX, XXXXXXX, XXXXXXX, KC_F13,  KC_F14,  KC_F15,  KC_F16,
        KC_F5,   KC_F6,   KC_F7,   KC_F8,   PRTSC4,  XXXXXXX, XXXXXXX, XXXXXXX, KC_F17,  KC_F18,  KC_F19,  KC_F20,
        KC_F9,   KC_F10,  KC_F11,  KC_F12,  PRTSC3,  XXXXXXX, XXXXXXX, XXXXXXX, KC_F21,  KC_F22,  KC_F23,  KC_F24,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    /* Adjust (Lower + Raise)
     *                      v------------------------RGB CONTROL--------------------v
     * ,-----------------------------------------------------------------------------------.
     * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|      |Plover|      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT_planck_grid(
        XXXXXXX, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, XXXXXXX, 
        XXXXXXX, XXXXXXX, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, XXXXXXX, PLOVER,  XXXXXXX, XXXXXXX, XXXXXXX, 
        XXXXXXX, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};

#ifdef AUDIO_ENABLE
    float plover_song[][2]     = SONG(PLOVER_SOUND);
    float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    bool is_plover_on = layer_state_cmp(state, _PLOVER);
    bool static was_plover_on = false, autoshift_on;
    if (is_plover_on != was_plover_on) {
        if (is_plover_on) {
            autoshift_on = get_autoshift_state();
            autoshift_disable();
        } else {
            if (autoshift_on) {
                autoshift_enable();
                autoshift_on = false;
            }
        }
        was_plover_on = is_plover_on;
     }
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CBR:
            if (record->event.pressed) {
                SEND_STRING("{}" SS_TAP(X_LEFT));
            }
            return false;
            break;
        case PRN:
            if (record->event.pressed) {
                SEND_STRING("()" SS_TAP(X_LEFT));
            }
            return false;
            break;
        case BRC:
            if (record->event.pressed) {
                SEND_STRING("[]" SS_TAP(X_LEFT));
            }
            return false;
            break;
        case DQUO:
            if (record->event.pressed) {
                SEND_STRING("\"\"" SS_TAP(X_LEFT));
            }
            return false;
            break;
        case PRTSC3:
            if (record->event.pressed) {
                SEND_STRING(SS_LCMD(SS_LSFT("3")));
            }
            return false;
            break;
        case PRTSC4:
            if (record->event.pressed) {
                SEND_STRING(SS_LCMD(SS_LSFT("4")));
            }
            return false;
            break;
        case PRTSC5:
            if (record->event.pressed) {
                SEND_STRING(SS_LCMD(SS_LSFT("5")));
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

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

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
