// Copyright 2023 Vladislav Kucheriavykh (@precondition)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard_report_util.hpp"
#include "quantum.h"
#include "keycode.h"
#include "test_common.h"
#include "test_driver.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using testing::_;
using testing::InSequence;

class NeutralizedKeyOverrides : public TestFixture {};

TEST_F(NeutralizedKeyOverrides, modifier_is_suppressed_but_not_neutralized) {
    // Tested key override:
    // ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL),
    //
    // MOD_MASK_SHIFT is not part of MODS_TO_NEUTRALIZE so we need to make
    // sure that no dummy mod neutralizer keycode gets sent when this key
    // override is getting triggered. However, the replacement (KC_DEL) is
    // not a shifted keycode, so the shift of the trigger should be
    // suppressed nonetheless.

    TestDriver driver;
    KeymapKey  key_lctrl(0, 0, 0, KC_LEFT_CTRL);
    KeymapKey  key_lsft(0, 0, 1, KC_LEFT_SHIFT);
    KeymapKey  key_bspc(0, 1, 0, KC_BACKSPACE);

    set_keymap({key_lctrl, key_lsft, key_bspc});

    key_lsft.press();
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Left shift should be removed from the report but no dummy keycode
    // should be inserted because left shift is not in the list of mods
    // to neutralize.
    key_bspc.press();
    EXPECT_REPORT(driver, (KC_DELETE));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Left shift is still held down so we should restore it after
    // sending the overriden key with suppressed mods.
    key_bspc.release();
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_lsft.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(NeutralizedKeyOverrides, modifier_is_suppressed_and_neutralized) {
    // Tested key override:
    // ko_make_basic(MOD_BIT_LGUI, KC_H, KC_6)
    //
    // MOD_BIT_LGUI is part of the MODS_TO_NEUTRALIZE so the
    // DUMMY_MOD_NEUTRALIZER_KEYCODE should get sent during
    // the suppression of the GUI modifier.

    TestDriver driver;
    KeymapKey  key_lgui(0, 0, 0, KC_LEFT_GUI);
    KeymapKey  key_h(0, 1, 0, KC_H);

    set_keymap({key_lgui, key_h});

    key_lgui.press();
    EXPECT_REPORT(driver, (KC_LEFT_GUI));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_h.press();
    {
        InSequence seq;

        EXPECT_REPORT(driver, (KC_LEFT_GUI, DUMMY_MOD_NEUTRALIZER_KEYCODE));
        EXPECT_REPORT(driver, (KC_LEFT_GUI));
        EXPECT_REPORT(driver, (KC_6));
    }
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_h.release();
    EXPECT_REPORT(driver, (KC_LEFT_GUI));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_lgui.release();
    // The two following reports should also be sent but they're not.
    // See qmk_firmware issue #22208.
    // EXPECT_REPORT(driver, (KC_LEFT_GUI, DUMMY_MOD_NEUTRALIZER_KEYCODE));
    // EXPECT_REPORT(driver, (KC_LEFT_GUI));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(NeutralizedKeyOverrides, active_mods_must_match_exactly) {
    // Tested key override:
    // ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL),
    //
    // The active modifiers should match exactly one of neutralized mod masks.
    // If MOD_BIT_LALT is part of MODS_TO_NEUTRALIZE, that doesn't mean that
    // Shift+Alt+Backspace should trigger the DUMMY_MOD_NEUTRALIZER_KEYCODE,
    // even though it should trigger the key override and replace
    // Shift+Backspace into Delete.

    TestDriver driver;
    KeymapKey  key_lalt(0, 0, 0, KC_LEFT_ALT);
    KeymapKey  key_lsft(0, 0, 1, KC_LEFT_SHIFT);
    KeymapKey  key_bspc(0, 1, 0, KC_BACKSPACE);

    set_keymap({key_lalt, key_lsft, key_bspc});

    key_lsft.press();
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_lalt.press();
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_LEFT_ALT));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_bspc.press();
    EXPECT_REPORT(driver, (KC_LEFT_ALT, KC_DELETE));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_bspc.release();
    EXPECT_REPORT(driver, (KC_LEFT_ALT, KC_LEFT_SHIFT));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_lsft.release();
    EXPECT_REPORT(driver, (KC_LEFT_ALT));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_lalt.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(NeutralizedKeyOverrides, do_not_suppress_if_replacement_uses_same_mods) {
    // Tested key override:
    // ko_make_basic(MOD_BIT_LCTRL, KC_D, LCTL(KC_V))
    //
    // If the replacement mods correspond to the trigger mods, there is no need for
    // mod suppression and consequently no need for mod neutralization.

    TestDriver driver;
    KeymapKey  key_lctrl(0, 0, 0, KC_LEFT_CTRL);
    KeymapKey  key_d(0, 1, 0, KC_D);

    set_keymap({key_lctrl, key_d});

    key_lctrl.press();
    EXPECT_REPORT(driver, (KC_LEFT_CTRL));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_d.press();
    EXPECT_REPORT(driver, (KC_LEFT_CTRL, KC_V));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_lctrl.release();
    {
        InSequence seq;

        EXPECT_REPORT(driver, (KC_LEFT_CTRL));
        EXPECT_EMPTY_REPORT(driver);
    }
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_d.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(NeutralizedKeyOverrides, do_not_neutralize_if_replacement_uses_same_mods) {
    // Tested key override:
    // ko_make_basic(MOD_BIT_LGUI, KC_D, LGUI(KC_V))
    //
    // If the replacement mods correspond to the trigger mods, there is no need for
    // mod suppression and consequently no need for mod neutralization.

    TestDriver driver;
    KeymapKey  key_lgui(0, 0, 0, KC_LEFT_GUI);
    KeymapKey  key_d(0, 1, 0, KC_D);

    set_keymap({key_lgui, key_d});

    key_lgui.press();
    EXPECT_REPORT(driver, (KC_LEFT_GUI));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_d.press();
    EXPECT_REPORT(driver, (KC_LEFT_GUI, KC_V));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_lgui.release();
    {
        InSequence seq;

        EXPECT_REPORT(driver, (KC_LEFT_GUI));
        EXPECT_EMPTY_REPORT(driver);
    }
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_d.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(NeutralizedKeyOverrides, do_not_neutralize_if_replacement_uses_any_mods) {
    // Tested key override:
    // ko_make_basic(MOD_BIT_LGUI, KC_GRAVE, LCTL(LALT(KC_ESCAPE)))
    //
    // The mods of the replacement are activated in the same keyboard report as
    // the deactivation of the suppressed mods so there is no need to send the
    // DUMMY_MOD_NEUTRALIZER_KEYCODE; the replacement mods will already
    // neutralize the trigger mods for us.

    TestDriver driver;
    KeymapKey  key_lgui(0, 0, 0, KC_LEFT_GUI);
    KeymapKey  key_grv(0, 1, 0, KC_GRAVE);

    set_keymap({key_lgui, key_grv});

    key_lgui.press();
    EXPECT_REPORT(driver, (KC_LEFT_GUI));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_grv.press();
    EXPECT_REPORT(driver, (KC_LEFT_CTRL, KC_LEFT_ALT, KC_ESCAPE));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_lgui.release();
    {
        InSequence seq;

        EXPECT_REPORT(driver, (KC_LEFT_GUI));
        EXPECT_EMPTY_REPORT(driver);
    }
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_grv.release();
    EXPECT_NO_REPORT(driver);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(NeutralizedKeyOverrides, do_not_neutralize_if_no_mods_are_suppressed) {
    // Tested key override:
    // like ko_make_basic(MOD_BIT_LALT, KC_1, KC_P1)  but with
    // `suppressed_mods` forcibly set to 0

    TestDriver driver;
    KeymapKey  key_lalt(0, 0, 0, KC_LEFT_ALT);
    KeymapKey  key_1(0, 1, 0, KC_1);

    set_keymap({key_lalt, key_1});

    key_lalt.press();
    EXPECT_REPORT(driver, (KC_LEFT_ALT));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_1.press();
    EXPECT_REPORT(driver, (KC_LEFT_ALT, KC_P1));
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    key_lalt.release();
    {
        InSequence seq;

        EXPECT_REPORT(driver, (KC_LEFT_ALT));
        EXPECT_EMPTY_REPORT(driver);
    }
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_1));
    idle_for(10000);

    key_1.release();
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

TEST_F(NeutralizedKeyOverrides, do_not_neutralize_set_diff_between_trigger_and_replacement_mods) {
    // Tested key override:
    // ko_make_basic(MOD_BIT_LGUI|MOD_BIT_LALT, KC_Y, LCTL(LGUI(KC_W)))
    //
    // Although the set difference between the trigger mods (MOD_BIT_LGUI|MOD_BIT_LALT) and
    // replacement mods (MOD_BIT_LCTL|MOD_BIT_LGUI) is a bitset (MOD_BIT_LALT) in the
    // MODS_TO_NEUTRALIZE, the DUMMY_MOD_NEUTRALIZER_KEYCODE should not be sent.
    {
        InSequence seq;

        TestDriver driver;
        KeymapKey  key_lalt(0, 0, 0, KC_LEFT_ALT);
        KeymapKey  key_lgui(0, 0, 1, KC_LEFT_GUI);
        KeymapKey  key_lctrl(0, 0, 2, KC_LEFT_CTRL);
        KeymapKey  key_lsft(0, 0, 3, KC_LEFT_SHIFT);
        KeymapKey  key_y(0, 1, 0, KC_Y);

        set_keymap({key_lalt, key_lgui, key_lctrl, key_lsft, key_y});

        key_lalt.press();
        EXPECT_REPORT(driver, (KC_LEFT_ALT));
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);

        key_lgui.press();
        EXPECT_REPORT(driver, (KC_LEFT_GUI, KC_LEFT_ALT));
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);

        key_y.press();
        EXPECT_REPORT(driver, (KC_LEFT_CTRL, KC_LEFT_GUI, KC_W));
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);

        key_lalt.release();
        EXPECT_REPORT(driver, (KC_LEFT_ALT, KC_LEFT_GUI));
        EXPECT_REPORT(driver, (KC_LEFT_GUI));
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);

        key_y.release();
        EXPECT_NO_REPORT(driver);
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);

        key_lgui.release();
        EXPECT_EMPTY_REPORT(driver);
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);
    }
}

TEST_F(NeutralizedKeyOverrides, chaining_overrides_with_same_trigger_mods) {
    // Tested key overrides:
    // ko_make_basic(MOD_BIT_LGUI, KC_H, KC_6)
    // ko_make_basic(MOD_BIT_LGUI, KC_D, LGUI(KC_V))

    {
        InSequence seq;

        TestDriver driver;
        KeymapKey  key_lalt(0, 0, 0, KC_LEFT_ALT);
        KeymapKey  key_lgui(0, 0, 1, KC_LEFT_GUI);
        KeymapKey  key_lctrl(0, 0, 2, KC_LEFT_CTRL);
        KeymapKey  key_lsft(0, 0, 3, KC_LEFT_SHIFT);
        KeymapKey  key_d(0, 1, 0, KC_D);
        KeymapKey  key_h(0, 1, 1, KC_H);

        set_keymap({key_lalt, key_lgui, key_lctrl, key_lsft, key_d, key_h});

        key_lgui.press();
        EXPECT_REPORT(driver, (KC_LEFT_GUI));
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);

        key_d.press();
        EXPECT_REPORT(driver, (KC_LEFT_GUI, KC_V));
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);

        key_d.release();
        EXPECT_REPORT(driver, (KC_LEFT_GUI));
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);

        key_h.press();
        // Ideally, we wouldn't have to send DUMMY_MOD_NEUTRALIZER_KEYCODE since
        // the previous GUI+D→GUI+V already “consumed” the LGUI but solving that
        // issue might require more code than is worth it (perhaps?)
        EXPECT_REPORT(driver, (DUMMY_MOD_NEUTRALIZER_KEYCODE, KC_LEFT_GUI));
        EXPECT_REPORT(driver, (KC_LEFT_GUI));
        EXPECT_REPORT(driver, (KC_6));
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);

        key_h.release();
        EXPECT_REPORT(driver, (KC_LEFT_GUI));
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);

        key_h.press();
        // Ideally, we wouldn't have to send DUMMY_MOD_NEUTRALIZER_KEYCODE since
        // the previous GUI+V *and* GUI+H→6 already “consumed” the LGUI but solving
        // that issue might require more code than is worth it (perhaps?)
        EXPECT_REPORT(driver, (DUMMY_MOD_NEUTRALIZER_KEYCODE, KC_LEFT_GUI));
        EXPECT_REPORT(driver, (KC_LEFT_GUI));
        EXPECT_REPORT(driver, (KC_6));
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);

        key_h.release();
        EXPECT_REPORT(driver, (KC_LEFT_GUI));
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);

        key_lgui.release();
        EXPECT_EMPTY_REPORT(driver);
        run_one_scan_loop();
        VERIFY_AND_CLEAR(driver);
    }
}
