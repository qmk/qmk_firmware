#include "action_util.h"
#include "keyboard_report_util.hpp"
#include "test_common.hpp"

using testing::_;
using testing::InSequence;

class SH : public TestFixture {};
class SHParametrizedTestFixture : public ::testing::WithParamInterface<std::pair<KeymapKey, KeymapKey>>, public SH {};

// XXX hand_swap_config[row][column] -> column, row
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{0, 0}, {2, 0}, {1, 0}}
};

// works
TEST_F(SH, SwapHandsTapLongHoldSwaps) {
    TestDriver driver;
    auto       key_sh_t = KeymapKey(0, 0, 0, SH_T(KC_SPACE));
    auto       key_a = KeymapKey(0, 1, 0, KC_A);
    auto       key_b = KeymapKey(0, 2, 0, KC_B);

    set_keymap({key_sh_t, key_a, key_b});

    debug_enable = true;
    debug_keyboard = true;

    key_sh_t.press();
    idle_for(211);
    assert(is_swap_hands_on());
    key_a.press();
    EXPECT_REPORT(driver, (key_b.report_code));
    idle_for(1);
    key_sh_t.release();
    idle_for(1);
    key_a.release();
    
    EXPECT_EMPTY_REPORT(driver);
    keyboard_task();
}

// fails
TEST_F(SH, SwapHandsTapShortHoldSwaps) {
    TestDriver driver;
    auto       key_sh_t = KeymapKey(0, 0, 0, SH_T(KC_SPACE));
    auto       key_a = KeymapKey(0, 1, 0, KC_A);
    auto       key_b = KeymapKey(0, 2, 0, KC_B);

    set_keymap({key_sh_t, key_a, key_b});

    debug_enable = true;
    debug_keyboard = true;

    key_sh_t.press();
    idle_for(1);
    assert(is_swap_hands_on());
    key_a.press();
    EXPECT_REPORT(driver, (key_b.report_code));
    idle_for(1);
    key_sh_t.release();
    idle_for(1);
    key_a.release();

    EXPECT_EMPTY_REPORT(driver);
    keyboard_task();
}
