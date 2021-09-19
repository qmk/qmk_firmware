/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
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
#include "bb-macro.h"

/* MACRO Definitions
 * This file has my macros/unicodes
 * Hooks for other functionality to inject itself into the process_record
 */

// Tap dance definitons
#ifdef AUDIO_ENABLE
#ifdef TAP_DANCE_ENABLE
qk_tap_dance_action_t tap_dance_actions[] = {
    // Music playback speed modulator
    [TD_AUDIO_TEMPO] = ACTION_TAP_DANCE_DOUBLE(MU_SLOW, MU_FAST),
};
#endif // AUDIO_ENABLE
#endif // TAP_DANCE_ENABLE

// Unicode definitions; for single character keys
//  We mask their definitions if unicode is not enabled
#ifdef UNICODEMAP_ENABLE
const uint32_t PROGMEM unicode_map[] = {
    [UPC_A_CIRC]  = 0x00C2, [LOW_A_CIRC]  = 0x00E2, // Â â
    [UPC_C_CEDI]  = 0x00C7, [LOW_C_CEDI]  = 0x00E7, // Ç ç
    [UPC_G_BREV]  = 0x011E, [LOW_G_BREV]  = 0x001F, // Ğ ğ
    [UPC_I_CIRC]  = 0x00CE, [LOW_I_CIRC]  = 0x00EE, // Î î
    [UPC_I_DOTL]  = 0x0049, [LOW_I_DOTL]  = 0x0131, // I ı
    [UPC_I_DOTT]  = 0x0130, [LOW_I_DOTT]  = 0x0069, // İ i
    [UPC_O_DIAE]  = 0x00D6, [LOW_O_DIAE]  = 0x00F6, // Ö ö
    [UPC_S_CEDI]  = 0x015E, [LOW_S_CEDI]  = 0x015F, // Ş ş
    [UPC_U_CIRC]  = 0x00DB, [LOW_U_CIRC]  = 0x00FB, // Û û
    [UPC_U_DIAE]  = 0x00DC, [LOW_U_DIAE]  = 0x00FC, // Ü ü
    [UPC_ALPHA]   = 0x0391, [LOW_ALPHA]   = 0x03B1, // Α α
    [UPC_BETA]    = 0x0392, [LOW_BETA]    = 0x03B2, // Β β
    [UPC_GAMMA]   = 0x0393, [LOW_GAMMA]   = 0x03B3, // Γ γ
    [UPC_DELTA]   = 0x0394, [LOW_DELTA]   = 0x03B4, // Δ δ
    [UPC_EPSILON] = 0x0395, [LOW_EPSILON] = 0x03B5, // Ε ε
    [UPC_ZETA]    = 0x0396, [LOW_ZETA]    = 0x03B6, // Ζ ζ
    [UPC_ETA]     = 0x0397, [LOW_ETA]     = 0x03B7, // Η η
    [UPC_THETA]   = 0x0398, [LOW_THETA]   = 0x03B8, // Θ θ
    [UPC_IOTA]    = 0x0399, [LOW_IOTA]    = 0x03B9, // Ι ι
    [UPC_KAPPA]   = 0x039A, [LOW_KAPPA]   = 0x03BA, // Κ κ
    [UPC_LAMBDA]  = 0x039B, [LOW_LAMBDA]  = 0x03BB, // Λ λ
    [UPC_MU]      = 0x039C, [LOW_MU]      = 0x03BC, // Μ μ
    [UPC_NU]      = 0x039D, [LOW_NU]      = 0x03BD, // Ν ν
    [UPC_XI]      = 0x039E, [LOW_XI]      = 0x03BE, // Ξ ξ
    [UPC_OMICRON] = 0x039F, [LOW_OMICRON] = 0x03BF, // Ο ο
    [UPC_PI]      = 0x03A0, [LOW_PI]      = 0x03C0, // Π π
    [UPC_RHO]     = 0x03A1, [LOW_RHO]     = 0x03C1, // Ρ ρ
    [UPC_SIGMA]   = 0x03A3, [LOW_SIGMA]   = 0x03C3, // Σ σ
    [UPC_TAU]     = 0x03A4, [LOW_TAU]     = 0x03C4, // Τ τ
    [UPC_UPSILON] = 0x03A5, [LOW_UPSILON] = 0x03C5, // Υ υ
    [UPC_PHI]     = 0x03A6, [LOW_PHI]     = 0x03C6, // Φ φ
    [UPC_CHI]     = 0x03A7, [LOW_CHI]     = 0x03C7, // Χ χ
    [UPC_PSI]     = 0x03A8, [LOW_PSI]     = 0x03C8, // Ψ ψ
    [UPC_OMEGA]   = 0x03A9, [LOW_OMEGA]   = 0x03C9, // Ω ω
    [ELLIPSIS]    = 0x2026,  // …
    [PLANCK_CON]  = 0x210F,  // ℏ
    [ANGSTROM]    = 0x212B,  // Å
    [BITCOIN]     = 0x20BF   // ₿
};
#endif // UNICODEMAP_ENABLE

// Keycodes
bool process_record_macro(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // AltGr + Caps should change the oled layout variable
        case KC_CAPSLOCK:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_RALT)) {
                    userspace_config.layout = (userspace_config.layout + 1) % 3;
                }
            }
            return true;
            break;
        case BB_OLED:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    // Scroll in opposite direction 
                    userspace_config.layout = (userspace_config.layout + 4) % 3;
                } else {
                    userspace_config.layout = (userspace_config.layout + 1) % 3;
                }
            }
            return false;
            break;
        // Plain macros
        case BB_PGPK:
            // My public PGP key
            if (record->event.pressed) {
                SEND_STRING("0B7151C823559DD8A7A04CE36426139E2F4C6CCE");
            }
            return false; break;
        case DBL_ANG:
            // Double angular bracket
            if (record->event.pressed) {
                SEND_STRING("<>"SS_TAP(X_LEFT));
            }
            return false; break;
        case DBL_PAR:
            // Double paranthesis
            if (record->event.pressed) {
                SEND_STRING("()"SS_TAP(X_LEFT));
            }
            return false; break;
        case DBL_BRC:
            // Double square brackets
            if (record->event.pressed) {
                SEND_STRING("[]"SS_TAP(X_LEFT));
            }
            return false; break;
        case DBL_CBR:
            // Double curly brackets
            if (record->event.pressed) {
                SEND_STRING("{}"SS_TAP(X_LEFT));
            }
            return false; break;
        // Unicode macros
#       ifdef UNICODEMAP_ENABLE
        case TR_FLAG:
            // Turkish flag
            if (record->event.pressed) {
                send_unicode_string("🇹🇷");
            }
            return false; break;
        case BB_LENY:
            // Lenny face: ( ͡° ͜ʖ ͡°)
            if (record->event.pressed) {
                send_unicode_string("( ͡° ͜ʖ ͡°)");
            }
            return false; break;
        case BB_TABL:
            // Table flip: ┻━┻︵ \(°□°)/ ︵ ┻━┻
            if (record->event.pressed) {
                send_unicode_string("┻━┻︵ \\(°□°)/ ︵ ┻━┻");
            }
            return false; break;
#       endif // UNICODEMAP_ENABLE
    }
    return true;
}
