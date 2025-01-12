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
extern "C" const keycode_string_name_t keycode_string_names_kb[] = {
    KEYCODE_STRING_NAME(MYMACRO1),
    KEYCODE_STRING_NAMES_END // End of table sentinel.
};
extern "C" const keycode_string_name_t keycode_string_names_user[] = {
    KEYCODE_STRING_NAME(MYMACRO2),
    KEYCODE_STRING_NAME(KC_EXLM),
    KEYCODE_STRING_NAMES_END // End of table sentinel.
};
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
             {KC_RCTL, "KC_RCTL"},
             {KC_RSFT, "KC_RSFT"},
             // F1-F24 keycodes.
             {KC_F1, "KC_F1"},
             {KC_F12, "KC_F12"},
             {KC_F13, "KC_F13"},
             {KC_F24, "KC_F24"},
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
             {HYPR_T(KC_GRV), "MT(0xF,KC_GRV)"},
             // Extrakey keycodes.
             {KC_WBAK, "KC_WBAK"},
             {KC_VOLU, "KC_VOLU"},
             // Mouse Key keycodes.
             {MS_LEFT, "MS_LEFT"},
             {MS_WHLD, "MS_WHLD"},
             {MS_BTN1, "MS_BTN1"},
             {MS_BTN8, "MS_BTN8"},
             // Custom keycode names.
             {MYMACRO1, "MYMACRO1"},
             {MYMACRO2, "MYMACRO2"},
             {KC_EXLM, "KC_EXLM"},
         })) {
        EXPECT_EQ(get_keycode_string(keycode), expected) << "where keycode = 0x" << std::hex << keycode;
    }
}
