#include "test_fixture.h"
#include "gmock/gmock.h"
#include "test_driver.h"
#include "test_matrix.h"
#include "keyboard.h"

using testing::_;
using testing::AnyNumber;
using testing::Return;
using testing::Between;

void TestFixture::SetUpTestCase() {
    TestDriver driver;
    EXPECT_CALL(driver, send_keyboard_mock(_));
    keyboard_init();
}

void TestFixture::TearDownTestCase() {
}

TestFixture::TestFixture() {
}

TestFixture::~TestFixture() {
    TestDriver driver;
    clear_all_keys();
    // Run for a while to make sure all keys are completely released
    // Should probably wait until tapping term etc, has timed out
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(AnyNumber());
    for (int i=0; i<100; i++) {
        keyboard_task();
    }
    testing::Mock::VerifyAndClearExpectations(&driver); 
    // Verify that the matrix really is cleared
    EXPECT_CALL(driver, send_keyboard_mock(KeyboardReport())).Times(Between(0, 1));
}