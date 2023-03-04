#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "action_tapping.h"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using testing::_;
using testing::InSequence;

class OneShotLayerModTap : public TestFixture {};

TEST_F(OneShotLayerModTap, tap_mod_tap_hold_key) {
    TestDriver driver;
    InSequence s;
    auto       osl_key          = KeymapKey{0, 0, 0, OSL(1)};
    auto       mod_tap_hold_key = KeymapKey(1, 1, 0, SFT_T(KC_A));

    set_keymap({osl_key, mod_tap_hold_key});

    /* Set one shot layer */
    tap_key(osl_key);
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press mod-tap-hold key */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-hold key */
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    expect_layer_state(0);
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(OneShotLayerModTap, tap_and_hold_mod_tap_hold_key_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       osl_key          = KeymapKey{0, 0, 0, OSL(1)};
    auto       mod_tap_hold_key = KeymapKey(1, 1, 0, SFT_T(KC_A));

    set_keymap({osl_key, mod_tap_hold_key});

    /* Set one shot layer */
    tap_key(osl_key);
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press mod-tap-hold key */
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    mod_tap_hold_key.press();
    idle_for(TAPPING_TERM + 1);
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-hold key */
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(OneShotLayerModTap, tap_regular_key_while_mod_tap_key_is_held_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       osl_key          = KeymapKey{0, 0, 0, OSL(1)};
    auto       mod_tap_hold_key = KeymapKey(1, 1, 0, SFT_T(KC_A));
    auto       regular_key1     = KeymapKey(1, 2, 0, KC_1);

    set_keymap({osl_key, mod_tap_hold_key, regular_key1});

    /* Set one shot layer */
    tap_key(osl_key);
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press mod-tap-hold key */
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    mod_tap_hold_key.press();
    idle_for(TAPPING_TERM + 1);
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press regular key */
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_1));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    regular_key1.press();
    run_one_scan_loop();
    expect_layer_state(0);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release regular key */
    EXPECT_NO_REPORT(driver);
    regular_key1.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-hold key */
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(OneShotLayerModTap, tap_a_mod_tap_key_while_another_mod_tap_key_is_held_tapping_term) {
    TestDriver driver;
    InSequence s;
    auto       osl_key                 = KeymapKey{0, 0, 0, OSL(1)};
    auto       regular_key0            = KeymapKey(0, 2, 0, KC_0);
    auto       first_mod_tap_hold_key  = KeymapKey(1, 1, 0, SFT_T(KC_A));
    auto       second_mod_tap_hold_key = KeymapKey(1, 2, 0, CTL_T(KC_B));

    set_keymap({osl_key, regular_key0, first_mod_tap_hold_key, second_mod_tap_hold_key});

    /* Set one shot layer */
    tap_key(osl_key);
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press first mod-tap-hold key */
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    first_mod_tap_hold_key.press();
    idle_for(TAPPING_TERM + 1);
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press second tap-hold key */
    EXPECT_NO_REPORT(driver);
    second_mod_tap_hold_key.press();
    run_one_scan_loop();
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release second tap-hold key */
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT, KC_B));
    EXPECT_REPORT(driver, (KC_LEFT_SHIFT));
    second_mod_tap_hold_key.release();
    run_one_scan_loop();
    expect_layer_state(0);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release first mod-tap-hold key */
    EXPECT_EMPTY_REPORT(driver);
    first_mod_tap_hold_key.release();
    run_one_scan_loop();
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(OneShotLayerModTap, tap_regular_key_while_mod_tap_key_is_held) {
    TestDriver driver;
    InSequence s;
    auto       osl_key          = KeymapKey{0, 0, 0, OSL(1)};
    auto       mod_tap_hold_key = KeymapKey(1, 1, 0, SFT_T(KC_A));
    auto       regular_key0     = KeymapKey(0, 2, 0, KC_0);
    auto       regular_key1     = KeymapKey(1, 2, 0, KC_1);

    set_keymap({osl_key, mod_tap_hold_key, regular_key0, regular_key1});

    /* Set one shot layer */
    tap_key(osl_key);
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press mod-tap-hold key */
    EXPECT_NO_REPORT(driver);
    mod_tap_hold_key.press();
    run_one_scan_loop();
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press regular key */
    EXPECT_NO_REPORT(driver);
    regular_key1.press();
    run_one_scan_loop();
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release regular key */
    EXPECT_NO_REPORT(driver);
    regular_key1.release();
    run_one_scan_loop();
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release mod-tap-hold key */
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_0));
    EXPECT_EMPTY_REPORT(driver);
    mod_tap_hold_key.release();
    run_one_scan_loop();
    expect_layer_state(0);
    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(OneShotLayerModTap, tap_a_mod_tap_key_while_another_mod_tap_key_is_held) {
    TestDriver driver;
    InSequence s;
    auto       osl_key                 = KeymapKey{0, 0, 0, OSL(1)};
    auto       regular_key0            = KeymapKey(0, 2, 0, KC_0);
    auto       first_mod_tap_hold_key  = KeymapKey(1, 1, 0, SFT_T(KC_A));
    auto       second_mod_tap_hold_key = KeymapKey(1, 2, 0, CTL_T(KC_B));

    set_keymap({osl_key, regular_key0, first_mod_tap_hold_key, second_mod_tap_hold_key});

    /* Set one shot layer */
    tap_key(osl_key);
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press first mod-tap-hold key */
    EXPECT_NO_REPORT(driver);
    first_mod_tap_hold_key.press();
    run_one_scan_loop();
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Press second tap-hold key */
    EXPECT_NO_REPORT(driver);
    second_mod_tap_hold_key.press();
    run_one_scan_loop();
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release second tap-hold key */
    EXPECT_NO_REPORT(driver);
    second_mod_tap_hold_key.release();
    run_one_scan_loop();
    expect_layer_state(1);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Release first mod-tap-hold key */
    EXPECT_REPORT(driver, (KC_A));
    EXPECT_EMPTY_REPORT(driver);
    EXPECT_REPORT(driver, (KC_0));
    EXPECT_EMPTY_REPORT(driver);
    first_mod_tap_hold_key.release();
    run_one_scan_loop();
    expect_layer_state(0);
    testing::Mock::VerifyAndClearExpectations(&driver);
}
