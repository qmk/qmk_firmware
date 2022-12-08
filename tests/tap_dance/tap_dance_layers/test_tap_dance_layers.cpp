// Copyright 2022 Sergey Vlasov (@sigprof)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "action_tapping.h"
#include "test_keymap_key.hpp"
#include "tap_dance_defs.h"

using testing::_;
using testing::InSequence;

struct TapDanceKeyParams {
    std::string name;                  // Tap dance name (part of test name)
    uint16_t    keycode;               // Tap dance keycode (TD(n))
    uint16_t    expect_on_tap;         // Keycode for single tap
    uint16_t    expect_on_hold;        // Keycode for single hold (may be MO(1))
    uint16_t    expect_on_double_tap;  // Keycode for double tap (may be MO(1))
    uint16_t    expect_on_double_hold; // Keycode for double hold (may be MO(1))
};

struct OtherKeyLayerParams {
    uint16_t keycode;           // Keycode in the keymap
    uint16_t expect_on_press;   // Keycode to expect on press
    uint16_t expect_on_release; // Keycode to expect on release (may be KC_NO if none)
};

struct OtherKeyParams {
    std::string         name; // Other key name (part of test name)
    OtherKeyLayerParams l0;   // Keycodes for layer 0
    OtherKeyLayerParams l1;   // Keycodes for layer 1
};

typedef std::tuple<TapDanceKeyParams, OtherKeyParams> TapDanceLayersParams;

class TapDanceLayers : public ::testing::WithParamInterface<TapDanceLayersParams>, public TestFixture {
   protected:
    TapDanceKeyParams tap_dance;
    OtherKeyParams    other_key;

    std::unique_ptr<KeymapKey> key_td, key_td_l1, key_other, key_other_l1;

    void SetUp() override {
        std::tie(tap_dance, other_key) = GetParam();

        key_td       = std::make_unique<KeymapKey>(0, 1, 0, tap_dance.keycode);
        key_td_l1    = std::make_unique<KeymapKey>(1, 1, 0, KC_TRNS);
        key_other    = std::make_unique<KeymapKey>(0, 2, 0, other_key.l0.keycode);
        key_other_l1 = std::make_unique<KeymapKey>(1, 2, 0, other_key.l1.keycode);

        set_keymap({*key_td, *key_td_l1, *key_other, *key_other_l1});
    }
};

static const TapDanceKeyParams tap_dance_keys[] = {
    TapDanceKeyParams{
        "LayerMove",
        TD(TD_L_MOVE),
        KC_APP,
        KC_APP,
        MO(1),
        MO(1),
    },
    TapDanceKeyParams{
        "LayerToggle",
        TD(TD_L_TOGG),
        KC_APP,
        KC_APP,
        MO(1),
        MO(1),
    },
    TapDanceKeyParams{
        "CustomLT",
        TD(TD_LT_APP),
        KC_APP,
        MO(1),
        KC_RCTL,
        KC_RCTL,
    },
};

static const OtherKeyParams other_keys[] = {
    OtherKeyParams{
        "Builtin",
        OtherKeyLayerParams{KC_A, KC_A, KC_NO},
        OtherKeyLayerParams{KC_B, KC_B, KC_NO},
    },
    OtherKeyParams{
        "CustomFast",
        OtherKeyLayerParams{FAST_AB, KC_A, KC_B},
        OtherKeyLayerParams{FAST_CD, KC_C, KC_D},
    },
    OtherKeyParams{
        "CustomSlow",
        OtherKeyLayerParams{SLOW_AB, KC_A, KC_B},
        OtherKeyLayerParams{SLOW_CD, KC_C, KC_D},
    },
};

// clang-format off
INSTANTIATE_TEST_CASE_P(
    Layers,
    TapDanceLayers,
    ::testing::Combine(
        ::testing::ValuesIn(tap_dance_keys),
        ::testing::ValuesIn(other_keys)
    ),
    [](const ::testing::TestParamInfo<TapDanceLayersParams>& info) {
        return std::get<0>(info.param).name + std::get<1>(info.param).name;
    }
);
// clang-format on

// Test single tap of the tap dance key with tapping term delay after the tap.
TEST_P(TapDanceLayers, SingleTap) {
    TestDriver driver;
    InSequence s;

    // The tap of the tap dance key does not result in sending a report
    // immediately.
    EXPECT_NO_REPORT(driver);
    tap_key(*key_td);

    // After the tapping term expires, a tap event for the single tap keycode
    // is generated.
    idle_for(TAPPING_TERM - 1);
    EXPECT_REPORT(driver, (tap_dance.expect_on_tap));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    // Pressing the other key produces the reports for the layer 0 mapping of
    // that key.
    EXPECT_REPORT(driver, (other_key.l0.expect_on_press));
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_EMPTY_REPORT(driver);
    }
    key_other->press();
    run_one_scan_loop();

    // Releasing the other key produces the reports for the layer 0 mapping of
    // that key.
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (other_key.l0.expect_on_release));
    }
    EXPECT_EMPTY_REPORT(driver);
    key_other->release();
    run_one_scan_loop();
}

// Test single tap of the tap dance key without a delay between the tap dance
// key and the other key.
TEST_P(TapDanceLayers, SingleTapFast) {
    TestDriver driver;
    InSequence s;

    // The tap of the tap dance key does not result in sending a report
    // immediately.
    EXPECT_NO_REPORT(driver);
    tap_key(*key_td);

    // A quick press of the other key causes the tap event for the tap dance to
    // be sent before the press event for the other key, and the layer 0
    // mapping is used for the other key.
    EXPECT_REPORT(driver, (tap_dance.expect_on_tap));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (other_key.l0.expect_on_press));
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_EMPTY_REPORT(driver);
    }
    key_other->press();
    run_one_scan_loop();

    // Releasing the other key produces the reports for the layer 0 mapping of
    // that key.
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (other_key.l0.expect_on_release));
    }
    EXPECT_EMPTY_REPORT(driver);
    key_other->release();
    run_one_scan_loop();
}

// Test single hold of the tap dance key with tapping term delay after the hold
// (test variant for tap dances which switch the layer on hold).
TEST_P(TapDanceLayers, SingleHoldLayer) {
    if (tap_dance.expect_on_hold != MO(1)) {
        // Do nothing - the SingleHoldKeycode test would run instead.
        return;
    }

    TestDriver driver;
    InSequence s;

    // No report gets sent immediately after the hold of the tap dance key.
    EXPECT_NO_REPORT(driver);
    key_td->press();
    run_one_scan_loop();

    // After the tapping term expires, the tap dance finishes and switches the
    // layer, but does not send a report.
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);
    run_one_scan_loop();

    // Pressing the other key produces the reports for the layer 1 mapping of
    // that key.
    EXPECT_REPORT(driver, (other_key.l1.expect_on_press));
    if (other_key.l1.expect_on_release != KC_NO) {
        EXPECT_EMPTY_REPORT(driver);
    }
    key_other->press();
    run_one_scan_loop();

    // Releasing the tap dance key does not produce a report.
    EXPECT_NO_REPORT(driver);
    key_td->release();
    run_one_scan_loop();

    // Releasing the other key produces the report for the layer 1 mapping of
    // that key.
    if (other_key.l1.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (other_key.l1.expect_on_release));
    }
    EXPECT_EMPTY_REPORT(driver);
    key_other->release();
    run_one_scan_loop();
}

// Test single hold of the tap dance key with tapping term delay after the hold
// (test variant for tap dances which send a keycode on single hold).
TEST_P(TapDanceLayers, SingleHoldKeycode) {
    if (tap_dance.expect_on_hold == MO(1)) {
        // Do nothing - the SingleHoldLayer test would run instead.
        return;
    }

    TestDriver driver;
    InSequence s;

    // No report gets sent immediately after the hold of the tap dance key.
    EXPECT_NO_REPORT(driver);
    key_td->press();
    run_one_scan_loop();

    // After the tapping term expires, the tap dance sends the report with the
    // hold keycode.
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);
    EXPECT_REPORT(driver, (tap_dance.expect_on_hold));
    run_one_scan_loop();

    // Pressing the other key produces the reports for the layer 0 mapping of
    // that key.
    EXPECT_REPORT(driver, (tap_dance.expect_on_hold, other_key.l0.expect_on_press));
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (tap_dance.expect_on_hold));
    }
    key_other->press();
    run_one_scan_loop();

    // Releasing the tap dance key sends the release report for the
    // corresponding hold keycode.
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_EMPTY_REPORT(driver);
    } else {
        EXPECT_REPORT(driver, (other_key.l0.expect_on_press));
    }
    key_td->release();
    run_one_scan_loop();

    // Releasing the other key produces the reports for the layer 0 mapping of
    // that key.
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (other_key.l0.expect_on_release));
    }
    EXPECT_EMPTY_REPORT(driver);
    key_other->release();
    run_one_scan_loop();
}

// Test single hold of the tap dance key without tapping term delay after the
// hold (test variant for tap dances which switch the layer on hold).
TEST_P(TapDanceLayers, SingleHoldFastLayer) {
    if (tap_dance.expect_on_hold != MO(1)) {
        // Do nothing - the SingleHoldFastKeycode test would run instead.
        return;
    }

    TestDriver driver;
    InSequence s;

    // No report gets sent immediately after the hold of the tap dance key.
    EXPECT_NO_REPORT(driver);
    key_td->press();
    run_one_scan_loop();

    // Pressing the other key produces the reports for the layer 1 mapping of
    // that key.
    EXPECT_REPORT(driver, (other_key.l1.expect_on_press));
    if (other_key.l1.expect_on_release != KC_NO) {
        EXPECT_EMPTY_REPORT(driver);
    }
    key_other->press();
    run_one_scan_loop();

    // Releasing the tap dance key does not produce a report.
    EXPECT_NO_REPORT(driver);
    key_td->release();
    run_one_scan_loop();

    // Releasing the other key produces the reports for the layer 1 mapping of
    // that key.
    if (other_key.l1.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (other_key.l1.expect_on_release));
    }
    EXPECT_EMPTY_REPORT(driver);
    key_other->release();
    run_one_scan_loop();
}

// Test single hold of the tap dance key without tapping term delay after the hold
// (test variant for tap dances which send a keycode on single hold).
TEST_P(TapDanceLayers, SingleHoldFastKeycode) {
    if (tap_dance.expect_on_hold == MO(1)) {
        // Do nothing - the SingleHoldFastLayer test would run instead.
        return;
    }

    TestDriver driver;
    InSequence s;

    // No report gets sent immediately after the hold of the tap dance key.
    EXPECT_NO_REPORT(driver);
    key_td->press();
    run_one_scan_loop();

    // Pressing the other key produces first the report for the tap dance hold
    // keycode, and then the reports for the layer 0 mapping of the other key.
    EXPECT_REPORT(driver, (tap_dance.expect_on_hold));
    EXPECT_REPORT(driver, (tap_dance.expect_on_hold, other_key.l0.expect_on_press));
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (tap_dance.expect_on_hold));
    }
    key_other->press();
    run_one_scan_loop();

    // Releasing the tap dance key sends a release report for the corresponding
    // hold keycode.
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_EMPTY_REPORT(driver);
    } else {
        EXPECT_REPORT(driver, (other_key.l0.expect_on_press));
    }
    key_td->release();
    run_one_scan_loop();

    // Releasing the other key produces the report for the layer 0 mapping of
    // that key.
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (other_key.l0.expect_on_release));
    }
    EXPECT_EMPTY_REPORT(driver);
    key_other->release();
    run_one_scan_loop();
}

// Test double tap of the tap dance key with tapping term delay after the hold
// (test variant for tap dances which switch the layer on double tap).
TEST_P(TapDanceLayers, DoubleTapLayer) {
    if (tap_dance.expect_on_double_tap != MO(1)) {
        // Do nothing - the DoubleTapKeycode test would run instead.
        return;
    }

    TestDriver driver;
    InSequence s;

    // No report gets sent immediately after the double tap of the tap dance
    // key.
    EXPECT_NO_REPORT(driver);
    tap_key(*key_td);
    tap_key(*key_td);

    // After the tapping term this tap dance does not send a report too.
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);
    run_one_scan_loop();

    // Pressing the other key produces the reports for the layer 1 mapping of
    // that key.
    EXPECT_REPORT(driver, (other_key.l1.expect_on_press));
    if (other_key.l1.expect_on_release != KC_NO) {
        EXPECT_EMPTY_REPORT(driver);
    }
    key_other->press();
    run_one_scan_loop();

    // Releasing the other key produces the report for the layer 1 mapping of
    // that key.
    if (other_key.l1.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (other_key.l1.expect_on_release));
    }
    EXPECT_EMPTY_REPORT(driver);
    key_other->release();
    run_one_scan_loop();
}

// Test double tap of the tap dance key with tapping term delay after the hold
// (test variant for tap dances which send a keycode on double tap).
TEST_P(TapDanceLayers, DoubleTapKeycode) {
    if (tap_dance.expect_on_double_tap == MO(1)) {
        // Do nothing - the DoubleTapLayer test would run instead.
        return;
    }

    TestDriver driver;
    InSequence s;

    // No report gets sent immediately after the double tap of the tap dance
    // key.
    EXPECT_NO_REPORT(driver);
    tap_key(*key_td);
    tap_key(*key_td);

    // After the tapping term this tap dance sends the double tap keycode.
    idle_for(TAPPING_TERM - 1);
    EXPECT_REPORT(driver, (tap_dance.expect_on_double_tap));
    EXPECT_EMPTY_REPORT(driver);
    run_one_scan_loop();

    // Pressing the other key produces the reports for the layer 0 mapping of
    // that key.
    EXPECT_REPORT(driver, (other_key.l0.expect_on_press));
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_EMPTY_REPORT(driver);
    }
    key_other->press();
    run_one_scan_loop();

    // Releasing the other key produces the report for the layer 0 mapping of
    // that key.
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (other_key.l0.expect_on_release));
    }
    EXPECT_EMPTY_REPORT(driver);
    key_other->release();
    run_one_scan_loop();
}

// Test double tap of the tap dance key without tapping term delay after the
// hold (test variant for tap dances which switch the layer on double tap).
TEST_P(TapDanceLayers, DoubleTapFastLayer) {
    if (tap_dance.expect_on_double_tap != MO(1)) {
        // Do nothing - the DoubleTapFastKeycode test would run instead.
        return;
    }

    TestDriver driver;
    InSequence s;

    // No report gets sent immediately after the double tap of the tap dance
    // key.
    EXPECT_NO_REPORT(driver);
    tap_key(*key_td);
    tap_key(*key_td);

    // Pressing the other key produces the reports for the layer 1 mapping of
    // that key.
    EXPECT_REPORT(driver, (other_key.l1.expect_on_press));
    if (other_key.l1.expect_on_release != KC_NO) {
        EXPECT_EMPTY_REPORT(driver);
    }
    key_other->press();
    run_one_scan_loop();

    // Releasing the other key produces the report for the layer 1 mapping of
    // that key.
    if (other_key.l1.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (other_key.l1.expect_on_release));
    }
    EXPECT_EMPTY_REPORT(driver);
    key_other->release();
    run_one_scan_loop();
}

// Test double tap of the tap dance key without tapping term delay after the
// hold (test variant for tap dances which send a keycode on double tap).
TEST_P(TapDanceLayers, DoubleTapFastKeycode) {
    if (tap_dance.expect_on_double_tap == MO(1)) {
        // Do nothing - the DoubleTapFastLayer test would run instead.
        return;
    }

    TestDriver driver;
    InSequence s;

    // No report gets sent immediately after the double tap of the tap dance
    // key.
    EXPECT_NO_REPORT(driver);
    tap_key(*key_td);
    tap_key(*key_td);

    // Pressing the other key produces first the report for the tap dance
    // double tap keycode, and then the reports for the layer 0 mapping of the
    // other key.
    EXPECT_REPORT(driver, (tap_dance.expect_on_double_tap));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (other_key.l0.expect_on_press));
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_EMPTY_REPORT(driver);
    }
    key_other->press();
    run_one_scan_loop();

    // Releasing the other key produces the report for the layer 0 mapping of
    // that key.
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (other_key.l0.expect_on_release));
    }
    EXPECT_EMPTY_REPORT(driver);
    key_other->release();
    run_one_scan_loop();
}

// Test double hold of the tap dance key with tapping term delay after the hold
// (test variant for tap dances which switch the layer on double hold).
TEST_P(TapDanceLayers, DoubleHoldLayer) {
    if (tap_dance.expect_on_double_hold != MO(1)) {
        // Do nothing - the DoubleHoldKeycode test would run instead.
        return;
    }

    TestDriver driver;
    InSequence s;

    // No report gets sent immediately after the double hold of the tap dance
    // key.
    EXPECT_NO_REPORT(driver);
    tap_key(*key_td);
    key_td->press();
    run_one_scan_loop();

    // After the tapping term expires, the tap dance finishes and switches the
    // layer, but does not send a report.
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);
    run_one_scan_loop();

    // Pressing the other key produces the reports for the layer 1 mapping of
    // that key.
    EXPECT_REPORT(driver, (other_key.l1.expect_on_press));
    if (other_key.l1.expect_on_release != KC_NO) {
        EXPECT_EMPTY_REPORT(driver);
    }
    key_other->press();
    run_one_scan_loop();

    // Releasing the tap dance key does not produce a report.
    EXPECT_NO_REPORT(driver);
    key_td->release();
    run_one_scan_loop();

    // Releasing the other key produces the report for the layer 1 mapping of
    // that key.
    if (other_key.l1.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (other_key.l1.expect_on_release));
    }
    EXPECT_EMPTY_REPORT(driver);
    key_other->release();
    run_one_scan_loop();
}

// Test double hold of the tap dance key with tapping term delay after the hold
// (test variant for tap dances which send a keycode on double hold).
TEST_P(TapDanceLayers, DoubleHoldKeycode) {
    if (tap_dance.expect_on_double_hold == MO(1)) {
        // Do nothing - the DoubleHoldLayer test would run instead.
        return;
    }

    TestDriver driver;
    InSequence s;

    // No report gets sent immediately after the double hold of the tap dance
    // key.
    EXPECT_NO_REPORT(driver);
    tap_key(*key_td);
    key_td->press();
    run_one_scan_loop();

    // After the tapping term expires, the tap dance sends the report with the
    // double hold keycode.
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM);
    EXPECT_REPORT(driver, (tap_dance.expect_on_double_hold));
    run_one_scan_loop();

    // Pressing the other key produces the reports for the layer 0 mapping of
    // that key.
    EXPECT_REPORT(driver, (tap_dance.expect_on_double_hold, other_key.l0.expect_on_press));
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (tap_dance.expect_on_double_hold));
    }
    key_other->press();
    run_one_scan_loop();

    // Releasing the tap dance key sends the release report for the
    // corresponding double hold keycode.
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_EMPTY_REPORT(driver);
    } else {
        EXPECT_REPORT(driver, (other_key.l0.expect_on_press));
    }
    key_td->release();
    run_one_scan_loop();

    // Releasing the other key produces the reports for the layer 0 mapping of
    // that key.
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (other_key.l0.expect_on_release));
    }
    EXPECT_EMPTY_REPORT(driver);
    key_other->release();
    run_one_scan_loop();
}

// Test double hold of the tap dance key without tapping term delay after the
// hold (test variant for tap dances which switch the layer on double hold).
TEST_P(TapDanceLayers, DoubleHoldFastLayer) {
    if (tap_dance.expect_on_double_hold != MO(1)) {
        // Do nothing - the DoubleHoldFastKeycode test would run instead.
        return;
    }

    TestDriver driver;
    InSequence s;

    // No report gets sent immediately after the double hold of the tap dance
    // key.
    EXPECT_NO_REPORT(driver);
    tap_key(*key_td);
    key_td->press();
    run_one_scan_loop();

    // Pressing the other key produces the reports for the layer 1 mapping of
    // that key.
    EXPECT_REPORT(driver, (other_key.l1.expect_on_press));
    if (other_key.l1.expect_on_release != KC_NO) {
        EXPECT_EMPTY_REPORT(driver);
    }
    key_other->press();
    run_one_scan_loop();

    // Releasing the tap dance key does not produce a report.
    EXPECT_NO_REPORT(driver);
    key_td->release();
    run_one_scan_loop();

    // Releasing the other key produces the reports for the layer 1 mapping of
    // that key.
    if (other_key.l1.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (other_key.l1.expect_on_release));
    }
    EXPECT_EMPTY_REPORT(driver);
    key_other->release();
    run_one_scan_loop();
}

// Test double hold of the tap dance key without tapping term delay after the hold
// (test variant for tap dances which send a keycode on double hold).
TEST_P(TapDanceLayers, DoubleHoldFastKeycode) {
    if (tap_dance.expect_on_double_hold == MO(1)) {
        // Do nothing - the DoubleHoldFastLayer test would run instead.
        return;
    }

    TestDriver driver;
    InSequence s;

    // No report gets sent immediately after the double hold of the tap dance
    // key.
    EXPECT_NO_REPORT(driver);
    tap_key(*key_td);
    key_td->press();
    run_one_scan_loop();

    // Pressing the other key produces first the report for the tap dance
    // double hold keycode, and then the reports for the layer 0 mapping of the
    // other key.
    EXPECT_REPORT(driver, (tap_dance.expect_on_double_hold));
    EXPECT_REPORT(driver, (tap_dance.expect_on_double_hold, other_key.l0.expect_on_press));
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (tap_dance.expect_on_double_hold));
    }
    key_other->press();
    run_one_scan_loop();

    // Releasing the tap dance key sends a release report for the corresponding
    // double hold keycode.
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_EMPTY_REPORT(driver);
    } else {
        EXPECT_REPORT(driver, (other_key.l0.expect_on_press));
    }
    key_td->release();
    run_one_scan_loop();

    // Releasing the other key produces the report for the layer 0 mapping of
    // that key.
    if (other_key.l0.expect_on_release != KC_NO) {
        EXPECT_REPORT(driver, (other_key.l0.expect_on_release));
    }
    EXPECT_EMPTY_REPORT(driver);
    key_other->release();
    run_one_scan_loop();
}
