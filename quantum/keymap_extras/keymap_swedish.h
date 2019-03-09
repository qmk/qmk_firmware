/* Copyright 2017 Andreas Lindhé
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

#ifndef KEYMAP_SWEDISH_H
#define KEYMAP_SWEDISH_H

#include "keymap_nordic.h"

// There are slight differrences in the keyboards in the nordic contries

// Swedish redifinitions from the nordic keyset
#undef  NO_AE
#define NO_AE   KC_QUOT  // ä
#undef  NO_CIRC
#define NO_CIRC LSFT(KC_RBRC)  // ^
#undef  NO_OSLH
#define NO_OSLH KC_SCLN  // ö

// Additional Swedish keys not defined in the nordic keyset
#define NO_AA   KC_LBRC  // å
#define NO_ASTR LSFT(KC_BSLS)  // *

// Norwegian unique MAC characters (not vetted for Swedish)
#define NO_ACUT_MAC KC_EQL  // =
#define NO_APOS_MAC KC_NUBS  // '
#define NO_AT_MAC   KC_BSLS  // @
#define NO_BSLS_MAC ALGR(LSFT(KC_7)) // '\'
#define NO_DLR_MAC  LSFT(KC_4) // $
#define NO_GRV_MAC ALGR(NO_BSLS) // `
#define NO_GRTR_MAC LSFT(KC_GRV)  // >
#define NO_LCBR_MAC ALGR(LSFT(KC_8))  // {
#define NO_LESS_MAC KC_GRV  // <
#define NO_PIPE_MAC ALGR(KC_7)  // |
#define NO_RCBR_MAC ALGR(LSFT(KC_9))  // }

#endif

