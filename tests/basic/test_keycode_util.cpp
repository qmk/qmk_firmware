// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#include "test_common.hpp"

class KeycodeToIdentifierSuite : public ::testing::TestWithParam<std::pair<std::uint16_t, std::string>> {};

TEST_P(KeycodeToIdentifierSuite, ConversionTests) {
    ASSERT_EQ(get_keycode_identifier_or_default(GetParam().first), GetParam().second);
}

INSTANTIATE_TEST_CASE_P(ConversionTestsP, KeycodeToIdentifierSuite,
                        // clang-format off
::testing::Values(
    // Goto layer
    std::make_pair(TO(0), "TO(0)"),
    std::make_pair(TO(0x1F), "TO(31)"),
    // Momentary switch layer
    std::make_pair(MO(0), "MO(0)"),
    std::make_pair(MO(0x1F), "MO(31)"),
    // Set default layer
    std::make_pair(DF(0), "DF(0)"),
    std::make_pair(DF(0x1F), "DF(31)"),
    // Toggle layer
    std::make_pair(TG(0), "TG(0)"),
    std::make_pair(TG(0x1F), "TG(31)"),
    // One-shot layer
    std::make_pair(OSL(0), "OSL(0)"),
    std::make_pair(OSL(0x1F), "OSL(31)"),
    // One-shot mod
    std::make_pair(OSM(MOD_LSFT), "OSM(MOD_LSFT)"),
    std::make_pair(OSM(MOD_LSFT | MOD_LCTL), "OSM(MOD_LCTL | MOD_LSFT)"),
    // Layer Mod
    std::make_pair(LM(0, MOD_LSFT), "LM(0, MOD_LSFT)"),
    std::make_pair(LM(0xF, MOD_LSFT), "LM(15, MOD_LSFT)"),
    std::make_pair(LM(0xF, MOD_LSFT | MOD_LCTL), "LM(15, MOD_LCTL | MOD_LSFT)"),
    // Layer tap toggle
    std::make_pair(TT(0), "TT(0)"),
    std::make_pair(TT(0x1F), "TT(31)"),
    // Layer tap
    std::make_pair(LT(0, KC_A), "LT(0, KC_A)"),
    std::make_pair(LT(0xF, KC_SPACE), "LT(15, KC_SPACE)"),
    std::make_pair(LT(1, KC_SPC), "LT(1, KC_SPACE)"),
    // Mod tap
    std::make_pair(MT(MOD_LCTL, KC_A), "MT(MOD_LCTL, KC_A)"),
    std::make_pair(MT(MOD_LCTL | MOD_LSFT, KC_A), "MT(MOD_LCTL | MOD_LSFT, KC_A)"),
    std::make_pair(ALT_T(KC_TAB), "MT(MOD_LALT, KC_TAB)"),
    // Mods
    std::make_pair(LCTL(KC_A), "QK_MODS(KC_A, QK_LCTL)"),
    std::make_pair(HYPR(KC_SPACE), "QK_MODS(KC_SPACE, QK_LCTL | QK_LSFT | QK_LALT | QK_LGUI)")
));
// clang-format on
