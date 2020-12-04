/* Copyright 2018 MechMerlin
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
#define BASE 0
#define NAV  1
#define PUNC 2
#define CADET 3
#define _______ KC_TRNS

enum custom_keycodes {
  TAGGED = SAFE_RANGE, H1, H2, H3, MATH,
  CDFC, ALSO, MARROW,
  TASK, MERMAID,
  NOT, EXP, MUL, EMPTY, SSCRIPT, SUM,
  AND, OR, UNION, INTERSECTION, SUBSET, SUPERSET, FORALL, INFTY, EXISTS, PARTIAL,
  FALSE, TRUE, VDASH, DASHV, UP, DOWN, LEFT, RIGHT, IFF,
  LLCORNER, ULCORNER, NEQ, SIMEQ, EQUIV, LEQ, GEQ, FRAC,
  SPC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_all(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
      LCTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,   KC_J,   KC_K,    KC_L,    LT(PUNC, KC_SCLN), KC_QUOT, KC_ENT,
      KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MO(CADET), KC_UP,   MO(1),
      LT(NAV, KC_CAPS), KC_LGUI, KC_LALT,                   KC_SPACE, KC_SPACE, KC_SPACE,      KC_RALT, LGUI(KC_LSFT),          LGUI(KC_LSFT), LGUI(KC_LSFT), LCTL(KC_LSFT) 
      ),

  [NAV] = LAYOUT_all(
      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
      _______, KC_VOLD, LCTL(KC_RIGHT), KC_VOLU, _______, _______, KC_END,  KC_PGDN, KC_PGUP, KC_HOME, _______, _______, _______, KC_DEL,
      _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______, _______,
      _______, KC_LSFT, RGB_TOG, _______, BL_DEC,  BL_TOGG, LCTL(KC_LEFT),  LCTL(LSFT(KC_LEFT)), _______, _______, LCTL(LSFT(KC_RIGHT)), _______, _______, _______, _______,
      _______, _______, _______,                   _______, _______, _______, _______, _______,                  _______, _______, RESET 
      ),

  [PUNC] = LAYOUT_all(
      _______, H1,   H2,  H3, MATH,   _______,  _______, _______,   _______,  _______, _______,   _______,  _______, _______, _______, 
      _______, _______, _______, _______, _______, TAGGED, _______, _______, _______, _______, _______, _______, _______, _______,
      CDFC,    _______, ALSO, _______, _______, KC_LPRN, KC_RPRN, _______, MARROW, _______, _______, _______, _______,
      _______, _______, _______, _______, TASK, _______, _______, _______, MERMAID, _______, _______, _______, _______, _______, _______,
      _______, _______, _______,                   _______, _______, _______, _______, _______,                  _______, _______, _______
      ),

  [CADET] = LAYOUT_all(
      _______,  NOT,   _______,  _______, _______,   _______,  EXP, _______,   MUL,  _______, EMPTY,   SSCRIPT,  SUM, _______, _______, 
      _______,  AND, OR, UNION, INTERSECTION, SUBSET, SUPERSET, FORALL, INFTY, EXISTS, PARTIAL, _______, _______, _______,
      _______, FALSE, TRUE, VDASH, DASHV, UP, DOWN, LEFT, RIGHT, IFF, _______, _______, _______,
      _______, _______, LLCORNER, ULCORNER, NEQ, SIMEQ, EQUIV, LEQ,  GEQ, _______, _______, FRAC, _______, _______, _______,
      _______, _______, _______,                   SPC, SPC, SPC, _______, _______,                  _______, _______, _______
      ),
};

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case H1:
      if (record->event.pressed) {
        SEND_STRING("# ");
      } 
      break;
    case H2:
      if (record->event.pressed) {
        SEND_STRING("## ");
      } 
      break;
    case H3:
      if (record->event.pressed) {
        SEND_STRING("### ");
      } 
      break;
    case MATH:
      if (record->event.pressed) {
        SEND_STRING("$$"SS_TAP(X_LEFT));
      } 
      break;
    case TAGGED:
      if (record->event.pressed) {
        SEND_STRING("tagged: ");
      } 
      break;
    case CDFC:
      if (record->event.pressed) {
        SEND_STRING("```");
      }
      break;
    case ALSO:
      if (record->event.pressed) {
        SEND_STRING("See also:"SS_TAP(X_ENTER));
      }
      break;
    case MARROW:
      if (record->event.pressed) {
        SEND_STRING("-->");
      }
      break;
    case TASK:
      if (record->event.pressed) {
        // Press
        SEND_STRING("- [ ] ");
      } else {
        // Release
      }
      break;
    case MERMAID:
      if (record->event.pressed) {
        // Press
        SEND_STRING("```mermaid"SS_TAP(X_ENTER));
      } else {
        // Release
      }
      break;
    case NOT:
      if (record->event.pressed) {
        SEND_STRING("\\neg ");
      }
      break;
    case EXP:
      if (record->event.pressed) {
        SEND_STRING("^{}"SS_TAP(X_LEFT));
      }
      break;
    case MUL:
      if (record->event.pressed) {
        SEND_STRING("\\cdot ");
      }
      break;
    case EMPTY:
      if (record->event.pressed) {
        SEND_STRING("\\emptyset");
      }
      break;
    case SSCRIPT:
      if (record->event.pressed) {
        SEND_STRING("_{}"SS_TAP(X_LEFT));
      }
      break;
    case SUM:
      if (record->event.pressed) {
        SEND_STRING("\\sum");
      }
      break;
    case AND:
      if (record->event.pressed) {
        SEND_STRING("\\land ");
      } else {
      }
      break;
    case OR:
      if (record->event.pressed) {
        SEND_STRING("\\or ");
      } else {
      }
      break;
    case UNION:
      if (record->event.pressed) {
        SEND_STRING("\\cup ");
      } else {
      }
      break;
    case INTERSECTION:
      if (record->event.pressed) {
        SEND_STRING("\\cap ");
      } else {
      }
      break;
    case SUBSET:
      if (record->event.pressed) {
        SEND_STRING("\\subset ");
      } else {
      }
      break;
    case SUPERSET:
      if (record->event.pressed) {
        SEND_STRING("\\superset");
      } else {
      }
      break;
    case FORALL:
      if (record->event.pressed) {
        SEND_STRING("\\forall ");
      } else {
      }
      break;
    case INFTY:
      if (record->event.pressed) {
        SEND_STRING("\\infty");
      } else {
      }
      break;
    case EXISTS:
      if (record->event.pressed) {
        SEND_STRING("\\exists");
      } else {
      }
      break;
    case PARTIAL:
      if (record->event.pressed) {
        SEND_STRING("\\partial");
      } else {
      }
      break;
    case TRUE:
      if (record->event.pressed) {
        SEND_STRING("\\top ");
      } else {
      }
      break;
    case FALSE:
      if (record->event.pressed) {
        SEND_STRING("\\bot ");
      } else {
      }
      break;
    case VDASH:
      if (record->event.pressed) {
        SEND_STRING("\\vdash ");
      } else {
      }
      break;
    case DASHV:
      if (record->event.pressed) {
        SEND_STRING("\\dashv ");
      } else {
      }
      break;
    case UP:
      if (record->event.pressed) {
        SEND_STRING("\\uparrow ");
      } else {
      }
      break;
    case DOWN:
      if (record->event.pressed) {
        SEND_STRING("\\downarrow ");
      } else {
      }
      break;
    case LEFT:
      if (record->event.pressed) {
        SEND_STRING("\\leftarrow ");
      } else {
      }
      break;
    case RIGHT:
      if (record->event.pressed) {
        SEND_STRING("\\rightarrow ");
      } else {
      }
      break;
    case IFF:
      if (record->event.pressed) {
        SEND_STRING("\\iff ");
      } else {
      }
      break;
    case LLCORNER:
      if (record->event.pressed) {
        SEND_STRING("\\llcorner ");
      } else {
      }
      break;
    case ULCORNER:
      if (record->event.pressed) {
        SEND_STRING("\\ulcorner ");
      } else {
      }
      break;
    case NEQ:
      if (record->event.pressed) {
        SEND_STRING("\\neq ");
      } else {
      }
      break;
    case SIMEQ:
      if (record->event.pressed) {
        SEND_STRING("\\simeq ");
      } else {
      }
      break;
    case EQUIV:
      if (record->event.pressed) {
        SEND_STRING("\\equiv ");
      } else {
      }
      break;
    case LEQ:
      if (record->event.pressed) {
        SEND_STRING("\\leq ");
      } else {
      }
      break;
    case GEQ:
      if (record->event.pressed) {
        SEND_STRING("\\geq ");
      } else {
      }
      break;
    case FRAC:
      if (record->event.pressed) {
        SEND_STRING("\\frac{}"SS_TAP(X_LEFT));
      }
      break;
    case SPC:
      if (record->event.pressed) {
        SEND_STRING("\\space");
      }
      break;
  }
  return true;
}

void led_set_user(uint8_t usb_led) {

}
