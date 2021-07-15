#include "test_fixture.hpp"
#include "gmock/gmock.h"
#include "test_driver.hpp"
#include "test_matrix.h"
#include "keyboard.h"
#include "action.h"
#include "action_tapping.h"

extern "C" {
#include "debug.h"
#include "eeconfig.h"
#include "action_layer.h"

void set_time(uint32_t t);
void advance_time(uint32_t ms);
}

int8_t sendchar(uint8_t c) {
    fprintf(stderr, "%c", c);
    return 0;
}

void init_logging(void) {
    print_set_sendchar(sendchar);

    // Customise these values to desired behaviour
    debug_enable   = true;
    debug_matrix   = true;
    debug_keyboard = true;
    debug_mouse    = true;

    // The following is enough to bootstrap the above values
    eeconfig_init_quantum();
    eeconfig_update_debug(debug_config.raw);
}

using testing::_;
using testing::AnyNumber;
using testing::Between;
using testing::Return;

void TestFixture::SetUpTestCase() {
    init_logging();

    TestDriver driver;
    EXPECT_CALL(driver, send_keyboard_mock(_));
    keyboard_init();
}

void TestFixture::TearDownTestCase() {}

TestFixture::TestFixture() {}

TestFixture::~TestFixture() {
    TestDriver driver;
    // Run for a while to make sure all keys are completely released
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(AnyNumber());
    layer_clear();
    clear_all_keys();
    idle_for(TAPPING_TERM + 10);
    testing::Mock::VerifyAndClearExpectations(&driver);
    // Verify that the matrix really is cleared
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(0);
    idle_for(TAPPING_TERM + 10);
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
