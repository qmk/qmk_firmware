#include "action_util.h"
#include "keyboard_report_util.hpp"
#include "test_common.hpp"

using testing::_;
using testing::InSequence;

class SwapHands : public TestFixture {};

// XXX hand_swap_config[row][column] -> column, row
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{0, 0}, {2, 0}, {1, 0}, {3, 0}}
};

TEST_F(SwapHands, LongHoldSwaps) {
    TestDriver driver;
    auto       key_sh_t = KeymapKey(0, 0, 0, SH_T(KC_SPACE));
    auto       key_a = KeymapKey(0, 1, 0, KC_A);
    auto       key_b = KeymapKey(0, 2, 0, KC_B);

    set_keymap({key_sh_t, key_a, key_b});

    key_sh_t.press();
    idle_for(211);
    key_a.press();
    EXPECT_REPORT(driver, (key_b.report_code));
    idle_for(1);
    key_sh_t.release();
    idle_for(1);
    key_a.release();
    
    EXPECT_EMPTY_REPORT(driver);
    keyboard_task();
}

TEST_F(SwapHands, ShortHoldSwaps) {
    TestDriver driver;
    auto       key_sh_t = KeymapKey(0, 0, 0, SH_T(KC_SPACE));
    auto       key_a = KeymapKey(0, 1, 0, KC_A);
    auto       key_b = KeymapKey(0, 2, 0, KC_B);

    set_keymap({key_sh_t, key_a, key_b});

    key_sh_t.press();
    idle_for(1);
    key_a.press();
    EXPECT_REPORT(driver, (key_b.report_code));
    idle_for(1);
    key_sh_t.release();
    idle_for(1);
    key_a.release();

    EXPECT_EMPTY_REPORT(driver);
    keyboard_task();
}

TEST_F(SwapHands, HoldAfterOSM_Swaps) {
    TestDriver driver;
    auto       key_sh_t = KeymapKey(0, 0, 0, SH_T(KC_SPACE));
    auto       key_a = KeymapKey(0, 1, 0, KC_A);
    auto       key_b = KeymapKey(0, 2, 0, KC_B);
    auto       key_m = KeymapKey(0, 3, 0, OSM(MOD_LSFT));

    set_keymap({key_sh_t, key_a, key_b, key_m});

    debug_enable = true;
    debug_keyboard = true;

    key_m.press();
    idle_for(1);
    key_m.release();
    idle_for(1);
    key_sh_t.press();
    idle_for(1);
    key_a.press();
    EXPECT_REPORT(driver, (key_b.report_code, KC_LEFT_SHIFT));
    idle_for(1);
    key_sh_t.release();
    idle_for(1);
    key_a.release();

    EXPECT_EMPTY_REPORT(driver);
    keyboard_task();
}

