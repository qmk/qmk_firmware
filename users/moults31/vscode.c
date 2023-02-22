/* Copyright 2021 moults31
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
#include "vscode.h"

bool process_record_vsc(uint16_t keycode, keyrecord_t *record) {
    bool rv = true;

    switch (keycode) {
        case M_VSC_TERMFOCUS:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("`"));
            }
            break;
        case M_VSC_SIDEBARFOCUS:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("0"));
            }
            break;
        case M_VSC_SIDEBARCLOSE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("b"));
            }
            break;
        case M_VSC_FILECLOSE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("w"));
            }
            break;
        case M_VSC_FILENXT:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LEFT_CTRL) SS_TAP(X_K) SS_TAP(X_PAGE_DOWN) SS_UP(X_LEFT_CTRL));
            }
            break;
        case M_VSC_FILEPRV:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LEFT_CTRL) SS_TAP(X_K) SS_TAP(X_PGUP) SS_UP(X_LEFT_CTRL));
            }
            break;
        case M_VSC_DBGCNSLFOCUS:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_D))));
            }
            break;
        case M_VSC_MVEDTRNXTGRP:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_RIGHT))));
            }
            break;
        case M_VSC_MVEDTRPRVGRP:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_LEFT))));
            }
            break;
        case M_VSC_EDGRPNXT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_L))));
            }
            break;
        case M_VSC_EDGRPPRV:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_K))));
            }
            break;
        case M_VSC_VIEWSIZEINC:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_P))));
            }
            break;
        case M_VSC_VIEWSIZEDEC:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_O))));
            }
            break;
    }

    return rv;
}
