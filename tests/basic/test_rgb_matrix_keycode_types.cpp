// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <iomanip>
#include <initializer_list>
#include <sstream>
#include <string>

#include "test_common.hpp"

extern "C" {
#include "quantum/rgb_matrix/animations/keycode_types.h"
#include "quantum/keycode_string.h"
}

namespace {

std::string format_keycode(uint16_t keycode) {
    std::ostringstream oss;
    oss << get_keycode_string(keycode) << " (0x" << std::uppercase << std::hex << keycode << ")";
    return oss.str();
}

template <typename Callable, typename KeyContainer>
void expect_all(const KeyContainer& keys, Callable&& predicate, bool expected) {
    for (uint16_t keycode : keys) {
        SCOPED_TRACE(::testing::Message() << (expected ? "expected true for " : "expected false for ") << format_keycode(keycode));
        EXPECT_EQ(expected, predicate(keycode));
    }
}

} // namespace

class KeycodeTypesTest : public ::testing::Test {};

TEST_F(KeycodeTypesTest, IsArrowKeycodeMatchesDirectionalKeys) {
    const uint16_t arrows[] = {KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT};
    expect_all(arrows, [](uint16_t keycode) { return is_arrow_keycode(keycode); }, true);
}

TEST_F(KeycodeTypesTest, IsArrowKeycodeRejectsOtherKeys) {
    const uint16_t non_arrows[] = {KC_HOME, KC_END, KC_A, KC_F1, RSFT(KC_LEFT), LCTL(KC_RIGHT)};
    expect_all(non_arrows, [](uint16_t keycode) { return is_arrow_keycode(keycode); }, false);
}

TEST_F(KeycodeTypesTest, IsModifierKeycodeCoversAllModifierRanges) {
    const uint16_t modifiers[] = {
        KC_LCTL,
        KC_RGUI,
        OSM(MOD_LSFT),
        OSM(MOD_RALT),
        LSFT_T(KC_A),
        RCTL_T(KC_B),
    };
    expect_all(modifiers, [](uint16_t keycode) { return is_modifier_keycode(keycode); }, true);
}

TEST_F(KeycodeTypesTest, IsModifierKeycodeRejectsNonModifiers) {
    const uint16_t non_modifiers[] = {KC_A, KC_F1, KC_LEFT, MO(1), LT(1, KC_B), OSL(2)};
    expect_all(non_modifiers, [](uint16_t keycode) { return is_modifier_keycode(keycode); }, false);
}

TEST_F(KeycodeTypesTest, IsBaseCharacterKeycodeAcceptsCharacters) {
    const uint16_t characters[] = {KC_A, KC_Z, KC_1, KC_0, KC_MINUS, KC_EQUAL, KC_KP_SLASH, KC_KP_PLUS, KC_KP_1, KC_NONUS_BACKSLASH};
    for (uint16_t keycode : characters) {
        uint8_t base = static_cast<uint8_t>(keycode);
        SCOPED_TRACE(::testing::Message() << "base key " << format_keycode(keycode));
        EXPECT_TRUE(is_base_character_keycode(base));
    }
}

TEST_F(KeycodeTypesTest, IsBaseCharacterKeycodeRejectsNonCharacters) {
    const uint16_t non_characters[] = {KC_ESC, KC_F5, KC_LEFT, KC_AUDIO_MUTE, KC_HOME};
    for (uint16_t keycode : non_characters) {
        uint8_t base = static_cast<uint8_t>(keycode);
        SCOPED_TRACE(::testing::Message() << "base key " << format_keycode(keycode));
        EXPECT_FALSE(is_base_character_keycode(base));
    }
}

TEST_F(KeycodeTypesTest, IsCharacterKeycodeAcceptsBaseAndAllowedModCombos) {
    const uint16_t character_cases[] = {
        KC_A,
        KC_1,
        LSFT(KC_A),
        RSFT(KC_5),
        RALT(KC_E),
        S(RALT(KC_I)),
    };
    expect_all(character_cases, [](uint16_t keycode) { return is_character_keycode(keycode); }, true);
}

TEST_F(KeycodeTypesTest, IsCharacterKeycodeRejectsDisallowedModifiers) {
    const uint16_t disallowed[] = {
        LALT(KC_A),
        LGUI(KC_B),
        RGUI(KC_C),
        LCTL(KC_D),
        LCTL(LSFT(KC_E)),
        LALT(LSFT(KC_F)),
    };
    expect_all(disallowed, [](uint16_t keycode) { return is_character_keycode(keycode); }, false);
}

TEST_F(KeycodeTypesTest, IsCharacterKeycodeRejectsNonCharacterBases) {
    const uint16_t non_character_bases[] = {KC_F1, RSFT(KC_F5), RALT(KC_UP), KC_HOME};
    expect_all(non_character_bases, [](uint16_t keycode) { return is_character_keycode(keycode); }, false);
}

class KeycodeModifierMacroTest : public ::testing::Test {};

TEST_F(KeycodeModifierMacroTest, RightAltMacroDetectsRightAlt) {
    EXPECT_TRUE(HAS_RIGHT_ALT_MOD(RALT(KC_A)));
}

TEST_F(KeycodeModifierMacroTest, RightAltMacroRejectsLeftAlt) {
    EXPECT_FALSE(HAS_RIGHT_ALT_MOD(LALT(KC_A)));
}

TEST_F(KeycodeModifierMacroTest, ShiftMacroDetectsEitherShift) {
    EXPECT_TRUE(HAS_SHIFT_MOD(RSFT(KC_B)));
    EXPECT_TRUE(HAS_SHIFT_MOD(LSFT(KC_C)));
}

TEST_F(KeycodeModifierMacroTest, ShiftMacroRejectsKeysWithoutShift) {
    EXPECT_FALSE(HAS_SHIFT_MOD(KC_D));
    EXPECT_FALSE(HAS_SHIFT_MOD(LCTL(KC_D)));
}

TEST_F(KeycodeModifierMacroTest, CtrlOrGuiMacroDetectsCtrl) {
    EXPECT_TRUE(HAS_CTRL_OR_GUI_MOD(LCTL(KC_E)));
}

TEST_F(KeycodeModifierMacroTest, CtrlOrGuiMacroDetectsGui) {
    EXPECT_TRUE(HAS_CTRL_OR_GUI_MOD(RGUI(KC_F)));
}

TEST_F(KeycodeModifierMacroTest, CtrlOrGuiMacroRejectsPlainKeys) {
    EXPECT_FALSE(HAS_CTRL_OR_GUI_MOD(KC_G));
}

TEST_F(KeycodeModifierMacroTest, AltMacroDetectsLeftAlt) {
    EXPECT_TRUE(HAS_ALT_MOD(LALT(KC_H)));
}

TEST_F(KeycodeModifierMacroTest, AltMacroDetectsRightAlt) {
    EXPECT_TRUE(HAS_ALT_MOD(RALT(KC_H)));
}

TEST_F(KeycodeModifierMacroTest, AltMacroRejectsNonAlt) {
    EXPECT_FALSE(HAS_ALT_MOD(KC_I));
}
