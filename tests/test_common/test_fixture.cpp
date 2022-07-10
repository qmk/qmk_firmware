#include "test_fixture.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "gmock/gmock-cardinalities.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_driver.hpp"
#include "test_logger.hpp"
#include "test_matrix.h"
#include "test_keymap_key.hpp"

extern "C" {
#include "action.h"
#include "action_tapping.h"
#include "action_util.h"
#include "action_layer.h"
#include "debug.h"
#include "eeconfig.h"
#include "keyboard.h"
#include "keymap.h"

void set_time(uint32_t t);
void advance_time(uint32_t ms);
}

using testing::_;

/* This is used for dynamic dispatching keymap_key_to_keycode calls to the current active test_fixture. */
TestFixture* TestFixture::m_this = nullptr;

/* Override weak QMK function to allow the usage of isolated per-test keymaps in unit-tests.
 * The actual call is dynamicaly dispatched to the current active test fixture, which in turn has it's own keymap. */
extern "C" uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t position) {
    uint16_t keycode;
    TestFixture::m_this->get_keycode(layer, position, &keycode);
    return keycode;
}

void TestFixture::SetUpTestCase() {
    test_logger.info() << "TestFixture setup-up start." << std::endl;

    // The following is enough to bootstrap the values set in main
    eeconfig_init_quantum();
    eeconfig_update_debug(debug_config.raw);

    TestDriver driver;
    keyboard_init();

    test_logger.info() << "TestFixture setup-up end." << std::endl;
}

void TestFixture::TearDownTestCase() {}

TestFixture::TestFixture() {
    m_this = this;
}

TestFixture::~TestFixture() {
    test_logger.info() << "TestFixture clean-up start." << std::endl;
    TestDriver driver;

    /* Reset keyboard state. */
    clear_all_keys();

    clear_keyboard();

    clear_oneshot_mods();
    clear_oneshot_locked_mods();
    reset_oneshot_layer();

    layer_clear();

#if defined(SWAP_HANDS_ENABLE)
    clear_oneshot_swaphands();
#endif

    idle_for(TAPPING_TERM * 10);
    testing::Mock::VerifyAndClearExpectations(&driver);

    /* Verify that the matrix really is cleared */
    EXPECT_NO_REPORT(driver);
    idle_for(TAPPING_TERM * 10);
    testing::Mock::VerifyAndClearExpectations(&driver);

    m_this = nullptr;

    test_logger.info() << "TestFixture clean-up end." << std::endl;

    print_test_log();
}

void TestFixture::add_key(KeymapKey key) {
    if (this->find_key(key.layer, key.position)) {
        FAIL() << "Key is already mapped for layer " << +key.layer << " and (column,row) (" << +key.position.col << "," << +key.position.row << ")";
    }

    this->keymap.push_back(key);
}

void TestFixture::tap_key(KeymapKey key, unsigned delay_ms) {
    key.press();
    idle_for(delay_ms);
    key.release();
    run_one_scan_loop();
}

void TestFixture::set_keymap(std::initializer_list<KeymapKey> keys) {
    this->keymap.clear();
    for (auto& key : keys) {
        add_key(key);
    }
}

const KeymapKey* TestFixture::find_key(layer_t layer, keypos_t position) const {
    auto keymap_key_predicate = [&](KeymapKey candidate) { return candidate.layer == layer && candidate.position.col == position.col && candidate.position.row == position.row; };

    auto result = std::find_if(this->keymap.begin(), this->keymap.end(), keymap_key_predicate);

    if (result != std::end(this->keymap)) {
        return &(*result);
    }
    return nullptr;
}

void TestFixture::get_keycode(const layer_t layer, const keypos_t position, uint16_t* result) const {
    bool key_is_out_of_bounds = position.col >= MATRIX_COLS && position.row >= MATRIX_ROWS;

    if (key_is_out_of_bounds) {
        /* See if this is done in hardware as well, because this is 100% out of bounds reads on all QMK keebs out there. */
        auto msg = [&]() {
            std::stringstream msg;
            msg << "Keycode for position (" << +position.col << "," << +position.row << ") requested! This is out of bounds." << std::endl;
            return msg.str();
        }();

        *result = KC_NO;
        test_logger.error() << msg;
        EXPECT_FALSE(key_is_out_of_bounds) << msg;
        return;
    }

    if (auto key = this->find_key(layer, position)) {
        *result = key->code;
        return;
    }

    FAIL() << "No key is mapped for layer " << +layer << " and (column,row) " << +position.col << "," << +position.row << ")";
}

void TestFixture::run_one_scan_loop() {
    keyboard_task();
    advance_time(1);
}

void TestFixture::idle_for(unsigned time) {
    for (unsigned i = 0; i < time; i++) {
        run_one_scan_loop();
    }
}

void TestFixture::print_test_log() const {
    const ::testing::TestInfo* const test_info = ::testing::UnitTest::GetInstance()->current_test_info();
    if (HasFailure()) {
        std::cerr << test_info->test_case_name() << "." << test_info->name() << " failed!" << std::endl;
        test_logger.print_log();
    }
    test_logger.reset();
}

void TestFixture::expect_layer_state(layer_t layer_state) const {
    test_logger.trace() << "Layer state: (" << +layer_state << ") Highest layer bit: (" << +get_highest_layer(layer_state) << ")" << std::endl;
    EXPECT_TRUE(layer_state_is(layer_state));
}
