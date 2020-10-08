/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers { _WM = 0, _DK, _FUN, _MOD_A, _MOD_I, _MOD_U, _MOD_E, _MOD_O, _MOD_C, _MOD_L, _MOD_N, _MOD_S, _MOD_Z };

enum tmk_style_macros { _DK_ACT = 0, _DK_REL };
#define DK_ACT M(_DK_ACT)  // activate dead key layer
#define DK_REL M(_DK_REL)  // release dead key layer

enum macros { KC_COMS = SAFE_RANGE };

#define KC_AA XP(_HU_AA_L, _HU_AA_U)
#define KC_II XP(_HU_II_L, _HU_II_U)
#define KC_UU XP(_HU_UU_L, _HU_UU_U)
#define KC_EE XP(_HU_EE_L, _HU_EE_U)
#define KC_OO XP(_HU_OO_L, _HU_OO_U)
#define KC_OE XP(_HU_OE_L, _HU_OE_U)
#define KC_UE XP(_HU_UE_L, _HU_UE_U)
#define KC_OEE XP(_HU_OEE_L, _HU_OEE_U)
#define KC_UEE XP(_HU_UEE_L, _HU_UEE_U)
#define KC_AU XP(_PL_AU_L, _PL_AU_U)
#define KC_EU XP(_PL_EU_L, _PL_EU_U)
#define KC_EL XP(_PL_LE_L, _PL_LE_U)
#define KC_CI XP(_PL_CI_L, _PL_CI_U)
#define KC_NI XP(_PL_NI_L, _PL_NI_U)
#define KC_SI XP(_PL_SI_L, _PL_SI_U)
#define KC_ZI XP(_PL_ZI_L, _PL_ZI_U)
#define KC_ZE XP(_PL_ZE_L, _PL_ZE_U)

#define KC_A_WD LT(_MOD_A, KC_A)  // press for a, hold for dia_a layer
#define KC_I_WD LT(_MOD_I, KC_I)  // press for i, hold for dia_i layer
#define KC_U_WD LT(_MOD_U, KC_U)  // press for u, hold for dia_u layer
#define KC_E_WD LT(_MOD_E, KC_E)  // press for e, hold for dia_e layer
#define KC_O_WD LT(_MOD_O, KC_O)  // press for o, hold for dia_o layer
#define KC_C_WD LT(_MOD_C, KC_C)  // cpress for c, hold for dia_c layer
#define KC_L_WD LT(_MOD_L, KC_L)  // press for l, hold for dia_l layer
#define KC_N_WD LT(_MOD_N, KC_N)  // press for n, hold for dia_n layer
#define KC_S_WD LT(_MOD_S, KC_S)  // press for s, hold for dia_s layer
#define KC_Z_WD LT(_MOD_Z, KC_Z)  // press for z, hold for dia_z layer

#define KC_ENOP ALT_T(KC_ENT)     // press for enter, hold for option
#define KC_BSCM GUI_T(KC_BSPC)    // press for backspace, hold for command
#define KC_CTES CTL_T(KC_ESC)     // press for escape, hold for control
#define KC_SHTB SFT_T(KC_TAB)     // press for tab, hold for shift
#define KC_SPFN LT(_FUN, KC_SPC)  // press for space, hold for function layer (aka spacefn)
#define KC_CSTB S(RCTL(KC_TAB))   // shift + control + tab
#define KC_C_TB RCTL(KC_TAB)      // control + tab
#define KC_C_LF RCTL(KC_LEFT)     // control + left
#define KC_C_RT RCTL(KC_RGHT)     // control + right

enum unicode_names {
    _HU_AA_U,
    _HU_AA_L,
    _HU_II_U,
    _HU_II_L,
    _HU_UU_U,
    _HU_UU_L,
    _HU_EE_U,
    _HU_EE_L,
    _HU_OO_U,
    _HU_OO_L,
    _HU_OE_U,
    _HU_OE_L,
    _HU_UE_U,
    _HU_UE_L,
    _HU_OEE_U,
    _HU_OEE_L,
    _HU_UEE_U,
    _HU_UEE_L,

    _PL_AU_U,
    _PL_AU_L,
    _PL_EU_U,
    _PL_EU_L,
    _PL_LE_U,
    _PL_LE_L,
    _PL_CI_U,
    _PL_CI_L,
    _PL_NI_U,
    _PL_NI_L,
    _PL_SI_U,
    _PL_SI_L,
    _PL_ZI_U,
    _PL_ZI_L,
    _PL_ZE_U,
    _PL_ZE_L
};

const uint32_t PROGMEM unicode_map[] = {
    [_HU_AA_L]  = 0x00E1,  //á
    [_HU_AA_U]  = 0x00C1,  //Á
    [_HU_II_L]  = 0x00ED,  //í
    [_HU_II_U]  = 0x00CD,  //Í
    [_HU_UU_L]  = 0x00FA,  //ú
    [_HU_UU_U]  = 0x00DA,  //Ú
    [_HU_EE_L]  = 0x00E9,  //é
    [_HU_EE_U]  = 0x00C9,  //É
    [_HU_OO_L]  = 0x00F3,  //ó
    [_HU_OO_U]  = 0x00D3,  //Ó
    [_HU_OE_L]  = 0x00F6,  //ö
    [_HU_OE_U]  = 0x00D6,  //Ö
    [_HU_UE_L]  = 0x00FC,  //ü
    [_HU_UE_U]  = 0x00DC,  //Ü
    [_HU_OEE_L] = 0x0151,  //ő
    [_HU_OEE_U] = 0x0150,  //Ő
    [_HU_UEE_L] = 0x0171,  //ű
    [_HU_UEE_U] = 0x0170,  //Ű

    [_PL_AU_L] = 0x0105,  //ą
    [_PL_AU_U] = 0x0104,  //Á
    [_PL_EU_L] = 0x0119,  //ę
    [_PL_EU_U] = 0x0118,  //Ę
    [_PL_LE_L] = 0x0142,  //ł
    [_PL_LE_U] = 0x0141,  //Ł
    [_PL_CI_L] = 0x0107,  //ć
    [_PL_CI_U] = 0x0106,  //Ć
    [_PL_NI_L] = 0x0144,  //ń
    [_PL_NI_U] = 0x0143,  //Ń
    [_PL_SI_L] = 0x015B,  //ś
    [_PL_SI_U] = 0x015A,  //Ś
    [_PL_ZI_L] = 0x017A,  //ź
    [_PL_ZI_U] = 0x0179,  //Ź
    [_PL_ZE_L] = 0x017C,  //ź
    [_PL_ZE_U] = 0x017B   //Ż
};

void eeconfig_init_user(void) { set_unicode_input_mode(UC_LNX); }

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch (id) {
        case _DK_ACT:
            if (record->event.pressed) {
                if (keyboard_report->mods & MOD_BIT(KC_LSFT) || keyboard_report->mods & MOD_BIT(KC_RSFT)) {
                    register_code(KC_COMM);
                } else {
                    set_oneshot_layer(_DK, ONESHOT_START);
                }
            } else {
                clear_oneshot_layer_state(ONESHOT_PRESSED);
                unregister_code(KC_COMM);
            }
            break;
        case _DK_REL:
            if (record->event.pressed) {
                register_code(KC_3);
            } else {
                clear_oneshot_layer_state(ONESHOT_PRESSED);
                unregister_code(KC_3);
            }
            break;
    }

    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_COMS:
            if (record->event.pressed) {
                register_code(KC_COMM);
                register_code(KC_SPC);
            } else {
                unregister_code(KC_SPC);
                unregister_code(KC_COMM);
            }
            break;
    }

    return true;
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_WM] = LAYOUT(
    KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,                      KC_J,    KC_F,    KC_U_WD, KC_P,    KC_SCLN,
    KC_A_WD, KC_S_WD, KC_H,    KC_T,    KC_G,                      KC_Y,    KC_N_WD, KC_E_WD, KC_O_WD, KC_I_WD,
    KC_Z_WD, KC_X,    KC_M,    KC_C_WD, KC_V,    XXXXXXX, XXXXXXX, KC_K,    KC_L_WD, DK_ACT,  KC_DOT,  KC_SLSH,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_SHTB, KC_CTES, KC_ENOP, KC_BSCM, KC_SPFN, KC_SHTB, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_DK] = LAYOUT(
    KC_PERC, KC_AMPR, KC_QUES, KC_PLUS, KC_AT,                     KC_DLR,  KC_UNDS, KC_LBRC, KC_RBRC, KC_EXLM,
    KC_HASH, KC_LPRN, KC_EQL,  KC_0,    KC_LCBR,                   KC_RCBR, KC_1,    KC_ASTR, KC_RPRN, KC_MINS,
    KC_6,    KC_7,    KC_8,    KC_9,    KC_PIPE, XXXXXXX, XXXXXXX, KC_BSLS, KC_2,    DK_REL,  KC_4,    KC_5,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_SHTB, KC_CTES, KC_ENOP, KC_BSCM, KC_COMS, KC_SHTB, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_FUN] = LAYOUT(
    XXXXXXX, KC_DEL,  KC_C_LF, KC_C_RT, KC_INS,                    KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_PSCR,
    KC_GRV,  KC_END,  KC_PGUP, KC_PGDN, KC_HOME,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT,
    XXXXXXX, KC_CSTB, KC_C_TB, KC_COPY, KC_PSTE, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX, KC_CIRC,
    UC_M_OS, UC_M_LN, UC_M_WC, KC_SHTB, XXXXXXX, KC_ENOP, KC_BSPC, _______, KC_SHTB, XXXXXXX, RESET,   CG_TOGG
  ),

  [_MOD_A] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, KC_AA,   XXXXXXX,                   XXXXXXX, KC_AA,   XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_AU,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_AU,   XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX, KC_ENOP, XXXXXXX, XXXXXXX, KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_MOD_I] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_II  , XXXXXXX,                   XXXXXXX, KC_II,   XXXXXXX, XXXXXXX, _______,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX, KC_ENOP, XXXXXXX, XXXXXXX, KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_MOD_U] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, KC_UEE,  XXXXXXX,                   XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_UU,   XXXXXXX,                   XXXXXXX, KC_UU,   XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_UE,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UE,   KC_UEE,  XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX, KC_ENOP, XXXXXXX, XXXXXXX, KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_MOD_E] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_EE,   XXXXXXX,                   XXXXXXX, KC_EE,   _______, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_EU,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_EU,   XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX, KC_ENOP, XXXXXXX, XXXXXXX, KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_MOD_O] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, KC_OEE,  XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_OO,   XXXXXXX,                   XXXXXXX, KC_OO,   XXXXXXX, _______, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_OE,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_OE,   KC_OEE,  XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX, KC_ENOP, XXXXXXX, XXXXXXX, KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_MOD_C] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_CI,   XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX, KC_ENOP, XXXXXXX, XXXXXXX, KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_MOD_L] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_EL,   XXXXXXX,                   XXXXXXX, KC_EL,   XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX, KC_ENOP, XXXXXXX, XXXXXXX, KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_MOD_N] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_NI,   XXXXXXX,                   XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX, KC_ENOP, XXXXXXX, XXXXXXX, KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_MOD_S] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, _______, XXXXXXX, KC_SI,   XXXXXXX,                   XXXXXXX, KC_SI,   XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX, KC_ENOP, XXXXXXX, XXXXXXX, KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_MOD_Z] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_ZE,   XXXXXXX,                   XXXXXXX, KC_ZE,   XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_ZI,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ZI,   XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX, KC_ENOP, XXXXXXX, XXXXXXX, KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX
  )
};
//clang-format on
