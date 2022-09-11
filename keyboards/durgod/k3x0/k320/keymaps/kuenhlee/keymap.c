/* Copyright 2021 kuenhlee
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

// Layer shorthand
#define _BL     0u
#define _FL     1u  // Multimedia Related, Virtual Desktop control
#define _SL     2u  // Just for System Related
#define _UL     3u  // Unicode Map

#define KC_ADTP LGUI(LCTL(KC_D))      // Adding New Virtual Desktop
#define KC_DDTP LGUI(LCTL(KC_F4))     // Deleting / Removing Current Virtual Desktop
#define KC_NDTP LGUI(LCTL(KC_RGHT))   // Navigate to the Next Virtual Desktop
#define KC_PDTP LGUI(LCTL(KC_LEFT))   // Navigate to the Previous Virtual Desktop
#define KC_WINL LGUI(KC_LEFT)         // Snap Windows to Left
#define KC_WINR LGUI(KC_RGHT)         // Snap Windows to Right
#define KC_WINU LGUI(KC_UP)           // Maximize the Window
#define KC_WIND LGUI(KC_DOWN)         // Minimize the desktop window
#define KC_TASK LCTL(LSFT(KC_ESC))    // Launch Task Manager

#define KC_FIND LCTL(LSFT(KC_F))      // Find In Files
#define KC_STOP LCTL(LSFT(KC_HOME))   // Select from Cursor to Home
#define KC_SEND LCTL(LSFT(KC_END))    // Select from Cursor to End

// °±²³µ©ΩθΩ√∞∆≈≠→↓←↑≡■□●○∴«»÷≤≥Σ
// Defines the Enumeration for Unicode Map
enum unicode_names {
  DEGR, 
  PONE,
  POW2,
  POW3,
  MYU,
  COPY,
  THET,
  OHM,
  SQRT,
  INFI,
  DELT,
  APPR,
  NEQU,
  RARR,
  DARR,
  LARR,
  UARR,
  SAME,
  BSQR,
  WSQR,
  BDOT,
  WDOT,
  THFR,
  DIV,
  LTOE,
  MTOE,
  DLAR,
  DRAR,
  SUM,
};

const uint32_t PROGMEM unicode_map[] = {
  [DEGR]  = 0x00B0, // °
  [PONE]  = 0x00B1, // ±
  [POW2]  = 0x00B2, // ²
  [POW3]  = 0x00B3, // ³
  [MYU]   = 0x00B5, // µ
  [COPY]  = 0x00A9, // ©
  [THET]  = 0x03B8, // θ
  [OHM]   = 0x2126, // Ω
  [SQRT]  = 0x221A, // √
  [INFI]  = 0x221E, // ∞
  [DELT]  = 0x0394, // ∆
  [APPR]  = 0x2248, // ≈
  [NEQU]  = 0x2260, // ≠
  [RARR]  = 0x2192, // →
  [DARR]  = 0x2193, // ↓
  [LARR]  = 0x2190, // ←
  [UARR]  = 0x2191, // ↑
  [SAME]  = 0x2261, // ≡
  [BSQR]  = 0x25A0, // ■
  [WSQR]  = 0x25A1, // □
  [BDOT]  = 0x25CF, // ●
  [WDOT]  = 0x25CB, // ○
  [THFR]  = 0x2234, // ∴
  [DIV]   = 0x00F7, // ÷
  [LTOE]  = 0x2264, // ≤
  [MTOE]  = 0x2265, // ≥
  [DLAR]  = 0x00AB, // «
  [DRAR]  = 0x00BB, // »
  [SUM]   = 0x03A3  // Σ
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT_tkl_ansi( /* Base Layer */
      KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,             KC_PSCR,  KC_SLCK,  KC_PAUS,
      KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
      KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
      KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,
      KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,                      KC_UP,
      KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(_FL),  KC_APP,   KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
  ),

  [_FL] = LAYOUT_tkl_ansi( /* First Layer */
      KC_TRNS,  KC_MPLY,  KC_MSTP,  KC_MRWD,  KC_MFFD,  KC_MUTE,  KC_VOLD,  KC_VOLU,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_CALC,            XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_ADTP,  KC_STOP,  KC_PDTP,
      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_TASK,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MSEL,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_DDTP,  KC_SEND,  KC_NDTP,
      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_FIND,  KC_WHOM,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,            XXXXXXX,  XXXXXXX,  KC_MYCM,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MAIL,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MENU,                      KC_WINU,
      XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                MO(_SL),  KC_TRNS,  MO(_UL),  XXXXXXX,  KC_WINL,  KC_WIND,  KC_WINR
  ),

  [_SL] = LAYOUT_tkl_ansi( /* Second Layer */
      XXXXXXX,  KC_SLEP,  XXXXXXX,  XXXXXXX,  KC_PWR,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                KC_TRNS,  KC_TRNS,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
  ),

  [_UL] = LAYOUT_tkl_ansi( /* Unicode Layer */
      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,
      X(APPR),  X(NEQU),  X(POW2),  X(POW3),  XXXXXXX,  XXXXXXX,  X(BSQR),  X(WSQR),  X(INFI),  X(BDOT),  X(WDOT),  XXXXXXX,  X(PONE),  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  X(SUM),   XXXXXXX,  X(MYU),   X(SAME),  XXXXXXX,  X(OHM),   X(DLAR),  X(DRAR),  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  X(SQRT),  X(DELT),  XXXXXXX,  XXXXXXX,  X(THFR),  XXXXXXX,  XXXXXXX,  XXXXXXX,  X(THET),  X(DEGR),  XXXXXXX,
      XXXXXXX,            XXXXXXX,  XXXXXXX,  X(COPY),  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  X(LTOE),  X(MTOE),  X(DIV),   XXXXXXX,                      X(UARR),
      XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  KC_TRNS,  KC_TRNS,  XXXXXXX,  X(LARR),  X(DARR),  X(RARR)
  )
};

void matrix_init_user(void) {
  set_unicode_input_mode(UC_WINC);
}
