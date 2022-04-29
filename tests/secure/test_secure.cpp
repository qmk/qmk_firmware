/* Copyright 2021 Stefan Kerkmann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gtest/gtest.h"
#include "keyboard_report_util.hpp"
#include "test_common.hpp"

using testing::_;
using testing::AnyNumber;
using testing::InSequence;

class Secure : public TestFixture {
   public:
    void SetUp() override {
        secure_lock();
    }
    // Convenience function to tap `key`.
    void TapKey(KeymapKey key) {
        key.press();
        run_one_scan_loop();
        key.release();
        run_one_scan_loop();
    }

    // Taps in order each key in `keys`.
    template <typename... Ts>
    void TapKeys(Ts... keys) {
        for (KeymapKey key : {keys...}) {
            TapKey(key);
        }
    }
};

TEST_F(Secure, test_lock) {
    TestDriver driver;

    // Allow any number of empty reports.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(0);

    EXPECT_FALSE(secure_is_unlocked());
    secure_unlock();
    EXPECT_TRUE(secure_is_unlocked());
    run_one_scan_loop();
    EXPECT_TRUE(secure_is_unlocked());
    secure_lock();
    EXPECT_FALSE(secure_is_unlocked());

    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(Secure, test_unlock_timeout) {
    TestDriver driver;

    // Allow any number of empty reports.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(0);

    EXPECT_FALSE(secure_is_unlocked());
    secure_unlock();
    EXPECT_TRUE(secure_is_unlocked());
    idle_for(SECURE_IDLE_TIMEOUT+1);
    EXPECT_FALSE(secure_is_unlocked());

    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(Secure, test_unlock_request) {
    TestDriver driver;
    auto       key_mo = KeymapKey(0, 0, 0, MO(1));
    auto       key_a  = KeymapKey(0, 1, 0, KC_A);
    auto       key_b  = KeymapKey(0, 2, 0, KC_B);
    auto       key_c  = KeymapKey(0, 3, 0, KC_C);
    auto       key_d  = KeymapKey(0, 4, 0, KC_D);

    set_keymap({key_mo, key_a, key_b, key_c, key_d});

    // Allow any number of empty reports.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(0);

    EXPECT_TRUE(secure_is_locked());
    secure_request_unlock();
    EXPECT_TRUE(secure_is_unlocking());
    TapKeys(key_a, key_b, key_c, key_d);
    EXPECT_TRUE(secure_is_unlocked());

    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(Secure, test_unlock_request_fail) {
    TestDriver driver;
    auto       key_e = KeymapKey(0, 0, 0, KC_E);
    auto       key_a = KeymapKey(0, 1, 0, KC_A);
    auto       key_b = KeymapKey(0, 2, 0, KC_B);
    auto       key_c = KeymapKey(0, 3, 0, KC_C);
    auto       key_d = KeymapKey(0, 4, 0, KC_D);

    set_keymap({key_e, key_a, key_b, key_c, key_d});

    // Allow any number of empty reports.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(AnyNumber());
    { // Expect the following reports in this order.
        InSequence s;
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_A)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_B)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_C)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_D)));
    }
    EXPECT_TRUE(secure_is_locked());
    secure_request_unlock();
    EXPECT_TRUE(secure_is_unlocking());
    TapKeys(key_e, key_a, key_b, key_c, key_d);
    EXPECT_FALSE(secure_is_unlocked());

    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(Secure, test_unlock_request_timeout) {
    TestDriver driver;

    // Allow any number of empty reports.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(0);

    EXPECT_FALSE(secure_is_unlocked());
    secure_request_unlock();
    EXPECT_TRUE(secure_is_unlocking());
    idle_for(SECURE_UNLOCK_TIMEOUT+1);
    EXPECT_FALSE(secure_is_unlocking());
    EXPECT_FALSE(secure_is_unlocked());

    testing::Mock::VerifyAndClearExpectations(&driver);
}


TEST_F(Secure, test_unlock_request_fail_mid) {
    TestDriver driver;
    auto       key_e = KeymapKey(0, 0, 0, KC_E);
    auto       key_a = KeymapKey(0, 1, 0, KC_A);
    auto       key_b = KeymapKey(0, 2, 0, KC_B);
    auto       key_c = KeymapKey(0, 3, 0, KC_C);
    auto       key_d = KeymapKey(0, 4, 0, KC_D);

    set_keymap({key_e, key_a, key_b, key_c, key_d});

    // Allow any number of empty reports.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(AnyNumber());
    { // Expect the following reports in this order.
        InSequence s;
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_C)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_D)));
    }
    EXPECT_FALSE(secure_is_unlocked());
    secure_request_unlock();
    EXPECT_TRUE(secure_is_unlocking());
    TapKeys(key_a, key_b, key_e, key_c, key_d);
    EXPECT_FALSE(secure_is_unlocking());
    EXPECT_FALSE(secure_is_unlocked());

    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(Secure, test_unlock_request_fail_out_of_order) {
    TestDriver driver;
    auto       key_e = KeymapKey(0, 0, 0, KC_E);
    auto       key_a = KeymapKey(0, 1, 0, KC_A);
    auto       key_b = KeymapKey(0, 2, 0, KC_B);
    auto       key_c = KeymapKey(0, 3, 0, KC_C);
    auto       key_d = KeymapKey(0, 4, 0, KC_D);

    set_keymap({key_e, key_a, key_b, key_c, key_d});

    // Allow any number of empty reports.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(AnyNumber());
    { // Expect the following reports in this order.
        InSequence s;
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_B)));
        EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_C)));
    }
    EXPECT_FALSE(secure_is_unlocked());
    secure_request_unlock();
    EXPECT_TRUE(secure_is_unlocking());
    TapKeys(key_a, key_d, key_b, key_c);
    EXPECT_TRUE(secure_is_locked());
    EXPECT_FALSE(secure_is_unlocking());
    EXPECT_FALSE(secure_is_unlocked());

    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(Secure, test_unlock_request_on_layer) {
    TestDriver driver;
    auto       key_mo = KeymapKey(0, 0, 0, MO(1));
    auto       key_a  = KeymapKey(0, 1, 0, KC_A);
    auto       key_b  = KeymapKey(0, 2, 0, KC_B);
    auto       key_c  = KeymapKey(0, 3, 0, KC_C);
    auto       key_d  = KeymapKey(0, 4, 0, KC_D);

    set_keymap({key_mo, key_a, key_b, key_c, key_d});

    // Allow any number of empty reports.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(0);

    EXPECT_TRUE(secure_is_locked());
    key_mo.press();
    run_one_scan_loop();
    secure_request_unlock();
    key_mo.release();
    run_one_scan_loop();
    EXPECT_TRUE(secure_is_unlocking());
    TapKeys(key_a, key_b, key_c, key_d);
    EXPECT_TRUE(secure_is_unlocked());
    EXPECT_FALSE(layer_state_is(1));

    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(Secure, test_unlock_request_mid_stroke) {
    TestDriver driver;
    auto       key_e = KeymapKey(0, 0, 0, KC_E);
    auto       key_a = KeymapKey(0, 1, 0, KC_A);
    auto       key_b = KeymapKey(0, 2, 0, KC_B);
    auto       key_c = KeymapKey(0, 3, 0, KC_C);
    auto       key_d = KeymapKey(0, 4, 0, KC_D);

    set_keymap({key_e, key_a, key_b, key_c, key_d});

    // Allow any number of empty reports.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(KC_E)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    EXPECT_TRUE(secure_is_locked());
    key_e.press();
    run_one_scan_loop();
    secure_request_unlock();
    key_e.release();
    run_one_scan_loop();
    EXPECT_TRUE(secure_is_unlocking());
    TapKeys(key_a, key_b, key_c, key_d);
    EXPECT_TRUE(secure_is_unlocked());

    testing::Mock::VerifyAndClearExpectations(&driver);
}

TEST_F(Secure, test_unlock_request_mods) {
    TestDriver driver;
    auto       key_lsft = KeymapKey(0, 0, 0, KC_LSFT);
    auto       key_a    = KeymapKey(0, 1, 0, KC_A);
    auto       key_b    = KeymapKey(0, 2, 0, KC_B);
    auto       key_c    = KeymapKey(0, 3, 0, KC_C);
    auto       key_d    = KeymapKey(0, 4, 0, KC_D);

    set_keymap({key_lsft, key_a, key_b, key_c, key_d});

    // Allow any number of empty reports.
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport(key_lsft.report_code)));
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport()));
    EXPECT_TRUE(secure_is_locked());
    key_lsft.press();
    run_one_scan_loop();
    secure_request_unlock();
    key_lsft.release();
    run_one_scan_loop();
    EXPECT_TRUE(secure_is_unlocking());
    TapKeys(key_a, key_b, key_c, key_d);
    EXPECT_TRUE(secure_is_unlocked());

    testing::Mock::VerifyAndClearExpectations(&driver);
}
