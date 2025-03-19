// Copyright 2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>

#include "test_common.hpp"

enum {
    MYMACRO1 = SAFE_RANGE,
    MYMACRO2,
};

// clang-format off
extern "C" {

KEYCODE_STRING_NAMES_KB(
    KEYCODE_STRING_NAME(MYMACRO1),
);

KEYCODE_STRING_NAMES_USER(
    KEYCODE_STRING_NAME(MYMACRO2),
    KEYCODE_STRING_NAME(KC_EXLM),
);

const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{9, 0}, {8, 0}, {7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
  {{9, 1}, {8, 1}, {7, 1}, {6, 1}, {5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}},
  {{9, 2}, {8, 2}, {7, 2}, {6, 2}, {5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}},
  {{9, 3}, {8, 3}, {7, 3}, {6, 3}, {5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}},
};

} // extern "C"
// clang-format on

class KeycodeStringTest : public TestFixture {};

TEST_F(KeycodeStringTest, get_keycode_string) {
    struct TestParams {
        uint16_t    keycode;
        std::string expected;
    };
    for (const auto [keycode, expected] : std::vector<TestParams>({
             {KC_TRNS, "KC_TRNS"},
             {KC_ESC, "KC_ESC"},
             {KC_A, "KC_A"},
             {KC_Z, "KC_Z"},
             {KC_0, "KC_0"},
             {KC_9, "KC_9"},
             {KC_KP_0, "KC_KP_0"},
             {KC_KP_9, "KC_KP_9"},
             {KC_LBRC, "KC_LBRC"},
             {KC_NUHS, "KC_NUHS"},
             {KC_NUBS, "KC_NUBS"},
             {KC_CAPS, "KC_CAPS"},
             {DB_TOGG, "DB_TOGG"},
             {KC_LCTL, "KC_LCTL"},
             {KC_LSFT, "KC_LSFT"},
             {KC_RALT, "KC_RALT"},
             {KC_RGUI, "KC_RGUI"},
             {KC_UP, "KC_UP"},
             {KC_HYPR, "KC_HYPR"},
             {KC_MEH, "KC_MEH"},
             // F1-F24 keycodes.
             {KC_F1, "KC_F1"},
             {KC_F12, "KC_F12"},
             {KC_F13, "KC_F13"},
             {KC_F24, "KC_F24"},
             // Macro keycodes.
             {MC_0, "MC_0"},
             {MC_31, "MC_31"},
             // Keyboard range keycodes.
             {QK_KB_0, "QK_KB_0"},
             {QK_KB_31, "QK_KB_31"},
             // User range keycodes.
             {QK_USER_2, "QK_USER_2"},
             {QK_USER_31, "QK_USER_31"},
             // Modified keycodes.
             {KC_COLN, "S(KC_SCLN)"},
             {C(KC_PGUP), "C(KC_PGUP)"},
             {RALT(KC_BSPC), "RALT(KC_BSPC)"},
             // One-shot mods.
             {OSM(MOD_LSFT), "OSM(MOD_LSFT)"},
             {OSM(MOD_RGUI), "OSM(MOD_RGUI)"},
             {OSM(MOD_RCTL | MOD_RGUI), "OSM(0x19)"},
             // Layer switch keycodes.
             {DF(2), "DF(2)"},
             {PDF(12), "PDF(12)"},
             {MO(3), "MO(3)"},
             {TO(0), "TO(0)"},
             {TT(1), "TT(1)"},
             {TG(3), "TG(3)"},
             {OSL(3), "OSL(3)"},
             {LM(3, MOD_RALT), "LM(3,MOD_RALT)"},
             {LT(15, KC_QUOT), "LT(15,KC_QUOT)"},
             // Tap dance keycodes.
             {TD(0), "TD(0)"},
             {TD(31), "TD(31)"},
             // Mod-tap keycodes.
             {LSFT_T(KC_ENT), "LSFT_T(KC_ENT)"},
             {RCTL_T(KC_RGHT), "RCTL_T(KC_RGHT)"},
             {HYPR_T(KC_GRV), "HYPR_T(KC_GRV)"},
             {MEH_T(KC_EQL), "MEH_T(KC_EQL)"},
             {RSA_T(KC_LBRC), "MT(0x16,KC_LBRC)"},
             // Extrakey keycodes.
             {KC_WBAK, "KC_WBAK"},
             {KC_WFWD, "KC_WFWD"},
             {KC_WREF, "KC_WREF"},
             {KC_VOLU, "KC_VOLU"},
             {KC_VOLD, "KC_VOLD"},
             // Mouse Key keycodes.
             {MS_LEFT, "MS_LEFT"},
             {MS_RGHT, "MS_RGHT"},
             {MS_UP, "MS_UP"},
             {MS_WHLU, "MS_WHLU"},
             {MS_WHLD, "MS_WHLD"},
             {MS_BTN1, "MS_BTN1"},
             {MS_BTN8, "MS_BTN8"},
             // Swap Hands keycodes.
             {SH_MON, "SH_MON"},
             {SH_TOGG, "SH_TOGG"},
             {SH_T(KC_PSCR), "SH_T(KC_PSCR)"},
             // Secure keycodes.
             {SE_LOCK, "SE_LOCK"},
             {SE_UNLK, "SE_UNLK"},
             {SE_TOGG, "SE_TOGG"},
             {SE_REQ, "SE_REQ"},
             // Programmable button keycodes.
             {PB_1, "PB_1"},
             {PB_32, "PB_32"},
             // Magic button keycodes.
             {QK_MAGIC + 7, "QK_MAGIC+7"},
             // Quantum keycodes.
             {QK_LOCK, "QK_LOCK"},
             {QK_QUANTUM + 7, "QK_QUANTUM+7"},
             // Custom keycode names.
             {MYMACRO1, "MYMACRO1"},
             {MYMACRO2, "MYMACRO2"},
             {KC_EXLM, "KC_EXLM"},
         })) {
        EXPECT_EQ(get_keycode_string(keycode), expected) << "where keycode = 0x" << std::hex << keycode;
    }
}
