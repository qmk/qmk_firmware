// Copyright 2026 Arca <arca.artem@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "test_common.hpp"

using testing::_;
using testing::InSequence;

class DynamicTappingTerm : public TestFixture {
   public:
    ~DynamicTappingTerm() override {
        g_tapping_term = TAPPING_TERM;
    }
};

TEST_F(DynamicTappingTerm, TappingUpRaisesTermByIncrementPerPress) {
    TestDriver driver;
    KeymapKey  up_key = KeymapKey{0, 0, 0, DT_UP};

    set_keymap({up_key});
    g_tapping_term = TAPPING_TERM;

    EXPECT_NO_REPORT(driver);
    tap_key(up_key);
    EXPECT_EQ(g_tapping_term, TAPPING_TERM + DYNAMIC_TAPPING_TERM_INCREMENT);

    tap_key(up_key);
    EXPECT_EQ(g_tapping_term, TAPPING_TERM + 2 * DYNAMIC_TAPPING_TERM_INCREMENT);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(DynamicTappingTerm, TappingDownLowersTermByIncrementPerPress) {
    TestDriver driver;
    KeymapKey  down_key = KeymapKey{0, 0, 0, DT_DOWN};

    set_keymap({down_key});
    g_tapping_term = 200;

    EXPECT_NO_REPORT(driver);
    tap_key(down_key);
    EXPECT_EQ(g_tapping_term, 200 - DYNAMIC_TAPPING_TERM_INCREMENT);

    tap_key(down_key);
    EXPECT_EQ(g_tapping_term, 200 - 2 * DYNAMIC_TAPPING_TERM_INCREMENT);
    VERIFY_AND_CLEAR(driver);
}

TEST_F(DynamicTappingTerm, LoweredTappingTermChangesModTapResolution) {
    TestDriver driver;
    InSequence s;
    KeymapKey  mod_tap_key = KeymapKey{0, 0, 0, SFT_T(KC_P)};
    KeymapKey  down_key    = KeymapKey{0, 1, 0, DT_DOWN};

    set_keymap({mod_tap_key, down_key});
    g_tapping_term = TAPPING_TERM;

    // Strictly between the lowered term (TAPPING_TERM - 10 * INCREMENT) and the
    // default TAPPING_TERM, so the same hold duration taps under the default
    // term but holds once DT_DOWN has lowered the term below it.
    const uint16_t hold_ms = TAPPING_TERM - 5 * DYNAMIC_TAPPING_TERM_INCREMENT;

    /* Part A: baseline, hold_ms held under the default tapping term resolves as a tap. */
    EXPECT_NO_REPORT(driver);
    mod_tap_key.press();
    idle_for(hold_ms);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_P));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    // Flush the quick-tap window (QUICK_TAP_TERM defaults to TAPPING_TERM) so the
    // next press of the same mod-tap key hold-resolves instead of auto-repeating
    // the tap above.
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM + 1);
    VERIFY_AND_CLEAR(driver);

    /* Part B: lower the tapping term below hold_ms. */
    EXPECT_NO_REPORT(driver);
    for (int i = 0; i < 10; i++) {
        tap_key(down_key);
    }
    EXPECT_EQ(g_tapping_term, TAPPING_TERM - 10 * DYNAMIC_TAPPING_TERM_INCREMENT);
    VERIFY_AND_CLEAR(driver);

    /* Part C: the same hold duration now expires the lowered term mid-idle,
     * so the mod-tap key resolves as a hold instead of a tap. */
    EXPECT_REPORT(driver, (KC_LSFT));
    mod_tap_key.press();
    idle_for(hold_ms);
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    mod_tap_key.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}
