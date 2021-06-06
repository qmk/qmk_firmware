/* Copyright 2021 3araht
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
#ifndef PEDAL_NORMALLY_CLOSED
    _OPEN,
#endif
    _CLOSE,
#ifdef PEDAL_NORMALLY_CLOSED
    _OPEN,
#endif
    _QWERTY,
    _MISC,
    _FN
};

// Alias layout macros that expand groups of keys.
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_OPEN] = LAYOUT( \
                  MI_Gs_1, MI_As_1, MI_Cs_2, MI_F_2, MI_Gs_3, \
       MI_E_1, MI_A_1, MI_G_2, MI_Ds_2, MI_F_3, MI_As_2, MI_F_1, \
         MI_D_2, MI_A_2, MI_C_3, MI_E_3, MI_C_2, MI_G_1, TG_SWAP, \
       MI_E_2, MI_Gs_2, MI_B_2, MI_D_3, MI_Fs_3, MI_Cs_3, MI_Fs_1, \
     MI_D_1, MI_B_1, MI_G_3, MI_A_3, MI_Ds_3, MI_Fs_2, MI_Ds_1, MI_C_1,  \
     \
     MO_SWAP,    MI_B_5, MI_Gs_5, MI_G_5, MI_F_5,     FN_MUTE, \
         MI_Cs_3, MI_A_5, MI_Fs_5, MI_E_5, MI_Ds_5, \
        MI_C_3, MI_D_3, MI_G_3, MI_As_4, MI_C_5, MI_D_5, \
     TG_SWAP, MI_B_2, MI_E_3, MI_Cs_4, MI_Fs_3, MI_A_3, MI_C_4, MI_E_4, \
       MI_A_2, MI_F_3, MI_As_3, MI_Gs_3, MI_B_3, MI_D_4, MI_Gs_4, MI_B_4, \
     MI_Gs_2, MI_As_2, MI_Ds_3, MI_F_4, MI_Ds_4, MI_Fs_4, MI_A_4, MI_Cs_5, MI_G_4 \
    ),

    [_CLOSE] = LAYOUT( \
                  MI_Gs_1, MI_As_1, MI_Ds_2, MI_Ds_3, MI_G_3, \
       MI_D_1, MI_D_2, MI_As_2, MI_C_3, MI_Cs_2, MI_C_2, MI_Fs_1, \
         MI_G_1, MI_G_2, MI_B_2, MI_D_3, MI_F_3, MI_Fs_2, TG_SWAP, \
       MI_A_1, MI_E_2, MI_A_2, MI_Cs_3, MI_E_3, MI_Gs_2, MI_B_1, \
     MI_E_1, MI_E_2, MI_Fs_3, MI_Gs_3, MI_B_3, MI_F_2, MI_Cs_1, MI_F_1,  \
     \
     MO_SWAP,    MI_A_5, MI_Gs_5, MI_Fs_5, MI_F_5,     FN_MUTE, \
         MI_C_3, MI_G_5, MI_As_4, MI_C_5, MI_Ds_5, \
        MI_D_3, MI_Cs_3, MI_Gs_3, MI_As_3, MI_C_4, MI_D_5, \
     TG_SWAP, MI_B_2, MI_Fs_3, MI_Fs_4, MI_G_3, MI_B_3, MI_D_4, MI_G_4, \
       MI_A_2, MI_F_3, MI_E_3, MI_A_3, MI_Cs_4, MI_E_4, MI_A_4, MI_Cs_5, \
     MI_Gs_2, MI_As_2, MI_Ds_3, MI_F_4, MI_E_4, MI_Gs_4, MI_B_4, MI_E_5, MI_Ds_4 \
    ),

    [_QWERTY] = LAYOUT_wrapper( \
                   _________________NUMBER_L__________________, \
       KC_GESC, KC_TAB, _________________QWERTY_L1_________________, \
          KC_CAPS, _________________QWERTY_L2_________________, KC_H, \
       KC_LSFT, _________________QWERTY_L3_________________, KC_N, \
     KC_LCTL, KC_GRV, KC_LGUI, KC_LALT, MIS_EIS, KC_SPC, KC_SPC, KC_PSCR,  \
     \
     MO(_MISC),        KC_LBRC, KC_RBRC, KC_BSLS, KC_0,         _______, \
                  KC_6, KC_7, KC_8, KC_9, KC_BSPC, \
                _________________QWERTY_R1_________________, KC_DEL, \
     KC_PGUP, KC_G, _________________QWERTY_R2_________________, KC_ENT, \
            KC_PGDN, KC_B, _________________QWERTY_R3_________________, KC_RSFT, \
         KC_HOME, KC_END, KC_SPC, MIS_KAN, KC_RALT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT \
    ),

    [_MISC] = LAYOUT_wrapper( \
                    _________________FUNC__L___________________, \
       _______, _______, _______, _______, _______, _______, _______, \
          _______, _______, _______, _______, _______, _______, _______, \
       _______, _______, _______, _______, _______, _______, _______, \
     _______, _______, _______, _______, _______, _______, _______, _______,  \
     \
     _______,        _______, _______, _______, KC_F10,         _______, \
                  KC_F6, KC_F7, KC_F8, KC_F9, _______, \
                _______, _______, _______, _______, _______, _______, \
     _______, _______, _______, _______, _______, _______, KC_QUOT, _______, \
            _______, _______, _______, _______, _______, _______, _______, _______, \
         _______, _______, _______, _______, _______, _______, _______, _______, _______ \
    ),

    [_FN] = LAYOUT( \
                   DF_SWAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
       XXXXXXX, DF_QWER, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
     XXXXXXX, XXXXXXX, AG_NORM, AG_SWAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  \
     \
     _______,        MI_OCTD, MI_OCTU, MI_VELD, MI_VELU,         _______, \
                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
    )
};

void keyboard_post_init_user(void) {
    //  Set octave to MI_OCT_0
    midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;

    // avoid using 127 since it is used as a special number in some sound sources.
    midi_config.velocity = MIDI_INITIAL_VELOCITY;
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise){
    if (index == 1) {  /* An encoder on the right side */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
#endif  // ENCODER_ENABLE
