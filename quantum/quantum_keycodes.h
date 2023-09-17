/* Copyright 2016-2017 Jack Humbert
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

#pragma once

//  Pull in dd keycodes to maintain header compatibility
#include "keycodes.h"

// US ANSI shifted keycode aliases
#include "keymap_us.h"

// TODO: sub-ranges?
// clang-format off
#define QK_LCTL                0x0100
#define QK_LSFT                0x0200
#define QK_LALT                0x0400
#define QK_LGUI                0x0800
#define QK_RMODS_MIN           0x1000
#define QK_RCTL                0x1100
#define QK_RSFT                0x1200
#define QK_RALT                0x1400
#define QK_RGUI                0x1800

#define SAFE_RANGE             QK_USER
// clang-format on

// Generic decoding for the whole QK_MODS range
#define QK_MODS_GET_MODS(kc) (((kc) >> 8) & 0x1F)
#define QK_MODS_GET_BASIC_KEYCODE(kc) ((kc)&0xFF)

// Keycode modifiers & aliases
#define LCTL(kc) (QK_LCTL | (kc))
#define LSFT(kc) (QK_LSFT | (kc))
#define LALT(kc) (QK_LALT | (kc))
#define LGUI(kc) (QK_LGUI | (kc))
#define LOPT(kc) LALT(kc)
#define LCMD(kc) LGUI(kc)
#define LWIN(kc) LGUI(kc)
#define RCTL(kc) (QK_RCTL | (kc))
#define RSFT(kc) (QK_RSFT | (kc))
#define RALT(kc) (QK_RALT | (kc))
#define RGUI(kc) (QK_RGUI | (kc))
#define ALGR(kc) RALT(kc)
#define ROPT(kc) RALT(kc)
#define RCMD(kc) RGUI(kc)
#define RWIN(kc) RGUI(kc)

#define HYPR(kc) (QK_LCTL | QK_LSFT | QK_LALT | QK_LGUI | (kc))
#define MEH(kc) (QK_LCTL | QK_LSFT | QK_LALT | (kc))
#define LCAG(kc) (QK_LCTL | QK_LALT | QK_LGUI | (kc))
#define LSG(kc) (QK_LSFT | QK_LGUI | (kc))
#define SGUI(kc) LSG(kc)
#define SCMD(kc) LSG(kc)
#define SWIN(kc) LSG(kc)
#define LAG(kc) (QK_LALT | QK_LGUI | (kc))
#define RSG(kc) (QK_RSFT | QK_RGUI | (kc))
#define RAG(kc) (QK_RALT | QK_RGUI | (kc))
#define LCA(kc) (QK_LCTL | QK_LALT | (kc))
#define LSA(kc) (QK_LSFT | QK_LALT | (kc))
#define RSA(kc) (QK_RSFT | QK_RALT | (kc))
#define RCS(kc) (QK_RCTL | QK_RSFT | (kc))
#define SAGR(kc) RSA(kc)

// Modified keycode aliases
#define C(kc) LCTL(kc)
#define S(kc) LSFT(kc)
#define A(kc) LALT(kc)
#define G(kc) LGUI(kc)

// GOTO layer - 32 layer max
#define TO(layer) (QK_TO | ((layer)&0x1F))
#define QK_TO_GET_LAYER(kc) ((kc)&0x1F)

// Momentary switch layer - 32 layer max
#define MO(layer) (QK_MOMENTARY | ((layer)&0x1F))
#define QK_MOMENTARY_GET_LAYER(kc) ((kc)&0x1F)

// Set default layer - 32 layer max
#define DF(layer) (QK_DEF_LAYER | ((layer)&0x1F))
#define QK_DEF_LAYER_GET_LAYER(kc) ((kc)&0x1F)

// Toggle to layer - 32 layer max
#define TG(layer) (QK_TOGGLE_LAYER | ((layer)&0x1F))
#define QK_TOGGLE_LAYER_GET_LAYER(kc) ((kc)&0x1F)

// One-shot layer - 32 layer max
#define OSL(layer) (QK_ONE_SHOT_LAYER | ((layer)&0x1F))
#define QK_ONE_SHOT_LAYER_GET_LAYER(kc) ((kc)&0x1F)

// L-ayer M-od: Momentary switch layer with modifiers active - 16 layer max
#define LM(layer, mod) (QK_LAYER_MOD | (((layer)&0xF) << 5) | ((mod)&0x1F))
#define QK_LAYER_MOD_GET_LAYER(kc) (((kc) >> 5) & 0xF)
#define QK_LAYER_MOD_GET_MODS(kc) ((kc)&0x1F)

// One-shot mod
#define OSM(mod) (QK_ONE_SHOT_MOD | ((mod)&0x1F))
#define QK_ONE_SHOT_MOD_GET_MODS(kc) ((kc)&0x1F)

// Layer tap-toggle - 32 layer max
#define TT(layer) (QK_LAYER_TAP_TOGGLE | ((layer)&0x1F))
#define QK_LAYER_TAP_TOGGLE_GET_LAYER(kc) ((kc)&0x1F)

// L-ayer, T-ap - 256 keycode max, 16 layer max
#define LT(layer, kc) (QK_LAYER_TAP | (((layer)&0xF) << 8) | ((kc)&0xFF))
#define QK_LAYER_TAP_GET_LAYER(kc) (((kc) >> 8) & 0xF)
#define QK_LAYER_TAP_GET_TAP_KEYCODE(kc) ((kc)&0xFF)

// M-od, T-ap - 256 keycode max
#define MT(mod, kc) (QK_MOD_TAP | (((mod)&0x1F) << 8) | ((kc)&0xFF))
#define QK_MOD_TAP_GET_MODS(kc) (((kc) >> 8) & 0x1F)
#define QK_MOD_TAP_GET_TAP_KEYCODE(kc) ((kc)&0xFF)

#define LCTL_T(kc) MT(MOD_LCTL, kc)
#define RCTL_T(kc) MT(MOD_RCTL, kc)
#define CTL_T(kc) LCTL_T(kc)

#define LSFT_T(kc) MT(MOD_LSFT, kc)
#define RSFT_T(kc) MT(MOD_RSFT, kc)
#define SFT_T(kc) LSFT_T(kc)

#define LALT_T(kc) MT(MOD_LALT, kc)
#define RALT_T(kc) MT(MOD_RALT, kc)
#define LOPT_T(kc) LALT_T(kc)
#define ROPT_T(kc) RALT_T(kc)
#define ALGR_T(kc) RALT_T(kc)
#define ALT_T(kc) LALT_T(kc)
#define OPT_T(kc) LOPT_T(kc)

#define LGUI_T(kc) MT(MOD_LGUI, kc)
#define RGUI_T(kc) MT(MOD_RGUI, kc)
#define LCMD_T(kc) LGUI_T(kc)
#define LWIN_T(kc) LGUI_T(kc)
#define RCMD_T(kc) RGUI_T(kc)
#define RWIN_T(kc) RGUI_T(kc)
#define GUI_T(kc) LGUI_T(kc)
#define CMD_T(kc) LCMD_T(kc)
#define WIN_T(kc) LWIN_T(kc)

#define C_S_T(kc) MT(MOD_LCTL | MOD_LSFT, kc)                        // Left Control + Shift e.g. for gnome-terminal
#define MEH_T(kc) MT(MOD_LCTL | MOD_LSFT | MOD_LALT, kc)             // Meh is a less hyper version of the Hyper key -- doesn't include GUI, so just Left Control + Shift + Alt
#define LCAG_T(kc) MT(MOD_LCTL | MOD_LALT | MOD_LGUI, kc)            // Left Control + Alt + GUI
#define RCAG_T(kc) MT(MOD_RCTL | MOD_RALT | MOD_RGUI, kc)            // Right Control + Alt + GUI
#define HYPR_T(kc) MT(MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI, kc) // see http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/
#define LSG_T(kc) MT(MOD_LSFT | MOD_LGUI, kc)                        // Left Shift + GUI
#define SGUI_T(kc) LSG_T(kc)
#define SCMD_T(kc) LSG_T(kc)
#define SWIN_T(kc) LSG_T(kc)
#define LAG_T(kc) MT(MOD_LALT | MOD_LGUI, kc) // Left Alt + GUI
#define RSG_T(kc) MT(MOD_RSFT | MOD_RGUI, kc) // Right Shift + GUI
#define RAG_T(kc) MT(MOD_RALT | MOD_RGUI, kc) // Right Alt + GUI
#define LCA_T(kc) MT(MOD_LCTL | MOD_LALT, kc) // Left Control + Alt
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc) // Left Shift + Alt
#define RSA_T(kc) MT(MOD_RSFT | MOD_RALT, kc) // Right Shift + Alt
#define RCS_T(kc) MT(MOD_RCTL | MOD_RSFT, kc) // Right Control + Shift
#define SAGR_T(kc) RSA_T(kc)

#define ALL_T(kc) HYPR_T(kc)

// Dedicated keycode versions for Hyper and Meh, if you want to use them as standalone keys rather than mod-tap
#define KC_HYPR HYPR(KC_NO)
#define KC_MEH MEH(KC_NO)

// Unicode aliases
// UNICODE_ENABLE - Allows Unicode input up to 0x7FFF
#define UC(c) (QK_UNICODE | (c))
#define QK_UNICODE_GET_CODE_POINT(kc) ((kc)&0x7FFF)

// UNICODEMAP_ENABLE - Allows Unicode input up to 0x10FFFF, requires unicode_map
#define UM(i) (QK_UNICODEMAP | ((i)&0x3FFF))
#define QK_UNICODEMAP_GET_INDEX(kc) ((kc)&0x3FFF)

#define UP(i, j) (QK_UNICODEMAP_PAIR | ((i)&0x7F) | (((j)&0x7F) << 7)) // 127 max i and j
#define QK_UNICODEMAP_PAIR_GET_UNSHIFTED_INDEX(kc) ((kc)&0x7F)
#define QK_UNICODEMAP_PAIR_GET_SHIFTED_INDEX(kc) (((kc) >> 7) & 0x7F)

// Swap Hands
#define SH_T(kc) (QK_SWAP_HANDS | ((kc)&0xFF))
#define QK_SWAP_HANDS_GET_TAP_KEYCODE(kc) ((kc)&0xFF)

// MIDI aliases
#define MIDI_TONE_MIN QK_MIDI_NOTE_C_0
#define MIDI_TONE_MAX QK_MIDI_NOTE_B_5
#define MIDI_OCTAVE_MIN QK_MIDI_OCTAVE_N2
#define MIDI_OCTAVE_MAX QK_MIDI_OCTAVE_7
#define MIDI_TRANSPOSE_MIN QK_MIDI_TRANSPOSE_N6
#define MIDI_TRANSPOSE_MAX QK_MIDI_TRANSPOSE_6
#define MIDI_VELOCITY_MIN QK_MIDI_VELOCITY_0
#define MIDI_VELOCITY_MAX QK_MIDI_VELOCITY_10
#define MIDI_CHANNEL_MIN QK_MIDI_CHANNEL_1
#define MIDI_CHANNEL_MAX QK_MIDI_CHANNEL_16

// TODO: somehow migrate sequencer to DD?
#include "sequencer.h"

#define SEQUENCER_STEP_MIN (QK_SEQUENCER + 0xF)
#define SEQUENCER_STEP_MAX (SEQUENCER_STEP_MIN + SEQUENCER_STEPS)

#define SEQUENCER_RESOLUTION_MIN (SEQUENCER_STEP_MAX + 1)
#define SEQUENCER_RESOLUTION_MAX (SEQUENCER_RESOLUTION_MIN + SEQUENCER_RESOLUTIONS)

#define SEQUENCER_TRACK_MIN (SEQUENCER_RESOLUTION_MAX + 1)
#define SEQUENCER_TRACK_MAX (SEQUENCER_TRACK_MIN + SEQUENCER_TRACKS)

#define SQ_S(n) (n < SEQUENCER_STEPS ? SEQUENCER_STEP_MIN + n : KC_NO)
#define SQ_R(n) (n < SEQUENCER_RESOLUTIONS ? SEQUENCER_RESOLUTION_MIN + n : KC_NO)
#define SQ_T(n) (n < SEQUENCER_TRACKS ? SEQUENCER_TRACK_MIN + n : KC_NO)

#include "quantum_keycodes_legacy.h"
