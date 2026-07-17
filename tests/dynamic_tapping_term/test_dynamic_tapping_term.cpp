// Copyright 2026 Arca <arca.artem@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "test_common.hpp"

using testing::_;

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
