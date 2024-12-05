/* Copyright 2022 Ruslan Sayfutdinov (@KapJI)
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

extern "C" {
#include "os_detection.h"
#include "timer.h"

void advance_time(uint32_t ms);
}

static uint32_t     reported_count;
static os_variant_t reported_os;

class OsDetectionTest : public ::testing::Test {
   protected:
    void SetUp() override {
        erase_wlength_data();
        reported_count = 0;
        reported_os    = OS_UNSURE;
    }
};

os_variant_t check_sequence(const std::vector<uint16_t> &w_lengths) {
    for (auto &w_length : w_lengths) {
        process_wlength(w_length);
    }
    return detected_host_os();
}

bool process_detected_host_os_kb(os_variant_t os) {
    reported_count = reported_count + 1;
    reported_os    = os;

    return true;
}

void assert_not_reported(void) {
    // check that it does not report the result, nor any intermediate results
    EXPECT_EQ(reported_count, 0);
    EXPECT_EQ(reported_os, OS_UNSURE);
}

void assert_reported(os_variant_t os) {
    // check that it reports exclusively the result, not any intermediate results
    EXPECT_EQ(reported_count, 1);
    EXPECT_EQ(reported_os, os);
    EXPECT_EQ(reported_os, detected_host_os());
}

/* Some collected data.

ChibiOS:
Windows 10: [FF, FF, 4, 24, 4, 24, 4, FF, 24, FF, 4, FF, 24, 4, 24, 20A, 20A, 20A, 20A, 20A, 20A, 20A, 20A, 20A, 20A, 20A, 20A, 20A, 20A, 20A, 20A, 20A, 20A, 20A, 20A, 20A, 20A, 20A, 20A]
Windows 10 (another host): [FF, FF, 4, 24, 4, 24, 4, 24, 4, 24, 4, 24]
macOS 12.5: [2, 24, 2, 28, FF]
iOS/iPadOS 15.6: [2, 24, 2, 28]
Linux (including Android, Raspberry Pi and WebOS TV): [FF, FF, FF]
PS5: [2, 4, 2, 28, 2, 24]
Nintendo Switch: [82, FF, 40, 40, FF, 40, 40, FF, 40, 40, FF, 40, 40, FF, 40, 40]
Quest 2: [FF, FF, FF, FE, FF, FE, FF, FE, FF, FE, FF]

LUFA:
Windows 10 (first connect): [12, FF, FF, 4, 10, FF, FF, FF, 4, 10, 20A, 20A, 20A, 20A, 20A, 20A]
Windows 10 (subsequent connect): [FF, FF, 4, 10, FF, 4, FF, 10, FF, 20A, 20A, 20A, 20A, 20A, 20A]
Windows 10 (another host): [FF, FF, 4, 10, 4, 10]
macOS: [2, 10, 2, E, FF]
iOS/iPadOS: [2, 10, 2, E]
Linux: [FF, FF, FF]
PS5: [2, 4, 2, E, 2, 10]
Nintendo Switch: [82, FF, 40, 40, FF, 40, 40]

V-USB:
Windows 10: [FF, FF, 4, E, FF]
Windows 10 (another host): [FF, FF, 4, E, 4]
macOS: [2, E, 2, E, FF]
iOS/iPadOS: [2, E, 2, E]
Linux: [FF, FF, FF]
PS5: [2, 4, 2, E, 2]
Nintendo Switch: [82, FF, 40, 40]
Quest 2: [FF, FF, FF, FE]

Common parts:
Windows: [..., FF, FF, 4, ...]
macOS: [2, _, 2, _, FF]
iOS/iPadOS: [2, _, 2, _]
Linux: [FF, FF, FF]
PS5: [2, 4, 2, _, 2, ...]
Nintendo Switch: [82, FF, 40, 40, ...]
Quest 2: [FF, FF, FF, FE, ...]
*/
TEST_F(OsDetectionTest, TestLinux) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0xFF}), OS_LINUX);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestChibiosMacos) {
    EXPECT_EQ(check_sequence({0x2, 0x24, 0x2, 0x28, 0xFF}), OS_MACOS);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestLufaMacos) {
    EXPECT_EQ(check_sequence({0x2, 0x10, 0x2, 0xE, 0xFF}), OS_MACOS);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestVusbMacos) {
    EXPECT_EQ(check_sequence({0x2, 0xE, 0x2, 0xE, 0xFF}), OS_MACOS);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestChibiosIos) {
    EXPECT_EQ(check_sequence({0x2, 0x24, 0x2, 0x28}), OS_IOS);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestLufaIos) {
    EXPECT_EQ(check_sequence({0x2, 0x10, 0x2, 0xE}), OS_IOS);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestVusbIos) {
    EXPECT_EQ(check_sequence({0x2, 0xE, 0x2, 0xE}), OS_IOS);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestChibiosWindows10) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0x4, 0x24, 0x4, 0x24, 0x4, 0xFF, 0x24, 0xFF, 0x4, 0xFF, 0x24, 0x4, 0x24, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A}), OS_WINDOWS);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestChibiosWindows10_2) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0x4, 0x24, 0x4, 0x24, 0x4, 0x24, 0x4, 0x24, 0x4, 0x24}), OS_WINDOWS);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestLufaWindows10) {
    EXPECT_EQ(check_sequence({0x12, 0xFF, 0xFF, 0x4, 0x10, 0xFF, 0xFF, 0xFF, 0x4, 0x10, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A}), OS_WINDOWS);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestLufaWindows10_2) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0x4, 0x10, 0xFF, 0x4, 0xFF, 0x10, 0xFF, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A}), OS_WINDOWS);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestLufaWindows10_3) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0x4, 0x10, 0x4, 0x10}), OS_WINDOWS);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestVusbWindows10) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0x4, 0xE, 0xFF}), OS_WINDOWS);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestVusbWindows10_2) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0x4, 0xE, 0x4}), OS_WINDOWS);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestChibiosPs5) {
    EXPECT_EQ(check_sequence({0x2, 0x4, 0x2, 0x28, 0x2, 0x24}), OS_LINUX);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestLufaPs5) {
    EXPECT_EQ(check_sequence({0x2, 0x4, 0x2, 0xE, 0x2, 0x10}), OS_LINUX);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestVusbPs5) {
    EXPECT_EQ(check_sequence({0x2, 0x4, 0x2, 0xE, 0x2}), OS_LINUX);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestChibiosNintendoSwitch) {
    EXPECT_EQ(check_sequence({0x82, 0xFF, 0x40, 0x40, 0xFF, 0x40, 0x40, 0xFF, 0x40, 0x40, 0xFF, 0x40, 0x40, 0xFF, 0x40, 0x40}), OS_LINUX);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestLufaNintendoSwitch) {
    EXPECT_EQ(check_sequence({0x82, 0xFF, 0x40, 0x40, 0xFF, 0x40, 0x40}), OS_LINUX);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestVusbNintendoSwitch) {
    EXPECT_EQ(check_sequence({0x82, 0xFF, 0x40, 0x40}), OS_LINUX);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestChibiosQuest2) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF}), OS_LINUX);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestVusbQuest2) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0xFF, 0xFE}), OS_LINUX);
    os_detection_task();
    assert_not_reported();
}

// Regression reported in https://github.com/qmk/qmk_firmware/pull/21777#issuecomment-1922815841
TEST_F(OsDetectionTest, TestDetectMacM1AsIOS) {
    EXPECT_EQ(check_sequence({0x02, 0x32, 0x02, 0x24, 0x101, 0xFF}), OS_IOS);
    os_detection_task();
    assert_not_reported();
}

TEST_F(OsDetectionTest, TestDoNotReportIfUsbUnstable) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0xFF, 0xFE}), OS_LINUX);
    os_detection_task();
    assert_not_reported();

    advance_time(OS_DETECTION_DEBOUNCE);
    os_detection_task();
    assert_not_reported();
    EXPECT_EQ(detected_host_os(), OS_LINUX);
}

static struct usb_device_state usb_device_state_configured = {.configure_state = USB_DEVICE_STATE_CONFIGURED};

TEST_F(OsDetectionTest, TestReportAfterDebounce) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0xFF, 0xFE}), OS_LINUX);
    os_detection_notify_usb_device_state_change(usb_device_state_configured);
    os_detection_task();
    assert_not_reported();

    advance_time(1);
    os_detection_task();
    assert_not_reported();
    EXPECT_EQ(detected_host_os(), OS_LINUX);

    advance_time(OS_DETECTION_DEBOUNCE - 3);
    os_detection_task();
    assert_not_reported();
    EXPECT_EQ(detected_host_os(), OS_LINUX);

    advance_time(1);
    os_detection_task();
    assert_not_reported();
    EXPECT_EQ(detected_host_os(), OS_LINUX);

    // advancing the timer alone must not cause a report
    advance_time(1);
    assert_not_reported();
    EXPECT_EQ(detected_host_os(), OS_LINUX);
    // the task will cause a report
    os_detection_task();
    assert_reported(OS_LINUX);
    EXPECT_EQ(detected_host_os(), OS_LINUX);

    // check that it remains the same after a long time
    advance_time(OS_DETECTION_DEBOUNCE * 15);
    assert_reported(OS_LINUX);
    EXPECT_EQ(detected_host_os(), OS_LINUX);
}

TEST_F(OsDetectionTest, TestReportAfterDebounceLongWait) {
    EXPECT_EQ(check_sequence({0x12, 0xFF, 0xFF, 0x4, 0x10, 0xFF, 0xFF, 0xFF, 0x4, 0x10, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A}), OS_WINDOWS);
    os_detection_notify_usb_device_state_change(usb_device_state_configured);
    os_detection_task();
    assert_not_reported();

    advance_time(1);
    os_detection_task();
    assert_not_reported();
    EXPECT_EQ(detected_host_os(), OS_WINDOWS);

    // advancing the timer alone must not cause a report
    advance_time(OS_DETECTION_DEBOUNCE * 15);
    assert_not_reported();
    EXPECT_EQ(detected_host_os(), OS_WINDOWS);
    // the task will cause a report
    os_detection_task();
    assert_reported(OS_WINDOWS);
    EXPECT_EQ(detected_host_os(), OS_WINDOWS);

    // check that it remains the same after a long time
    advance_time(OS_DETECTION_DEBOUNCE * 10);
    os_detection_task();
    assert_reported(OS_WINDOWS);
    EXPECT_EQ(detected_host_os(), OS_WINDOWS);
}

TEST_F(OsDetectionTest, TestReportUnsure) {
    EXPECT_EQ(check_sequence({0x12, 0xFF}), OS_UNSURE);
    os_detection_notify_usb_device_state_change(usb_device_state_configured);
    os_detection_task();
    assert_not_reported();

    advance_time(1);
    os_detection_task();
    assert_not_reported();
    EXPECT_EQ(detected_host_os(), OS_UNSURE);

    // advancing the timer alone must not cause a report
    advance_time(OS_DETECTION_DEBOUNCE - 1);
    assert_not_reported();
    EXPECT_EQ(detected_host_os(), OS_UNSURE);
    // the task will cause a report
    os_detection_task();
    assert_reported(OS_UNSURE);
    EXPECT_EQ(detected_host_os(), OS_UNSURE);

    // check that it remains the same after a long time
    advance_time(OS_DETECTION_DEBOUNCE * 10);
    os_detection_task();
    assert_reported(OS_UNSURE);
    EXPECT_EQ(detected_host_os(), OS_UNSURE);
}

TEST_F(OsDetectionTest, TestDoNotReportIntermediateResults) {
    EXPECT_EQ(check_sequence({0x12, 0xFF}), OS_UNSURE);
    os_detection_notify_usb_device_state_change(usb_device_state_configured);
    os_detection_task();
    assert_not_reported();

    advance_time(OS_DETECTION_DEBOUNCE - 1);
    os_detection_task();
    assert_not_reported();
    EXPECT_EQ(detected_host_os(), OS_UNSURE);

    // at this stage, the final result has not been reached yet
    EXPECT_EQ(check_sequence({0xFF}), OS_LINUX);
    os_detection_notify_usb_device_state_change(usb_device_state_configured);
    advance_time(OS_DETECTION_DEBOUNCE - 1);
    os_detection_task();
    assert_not_reported();
    // the intermedite but yet unstable result is exposed through detected_host_os()
    EXPECT_EQ(detected_host_os(), OS_LINUX);

    // the remainder is processed
    EXPECT_EQ(check_sequence({0x4, 0x10, 0xFF, 0xFF, 0xFF, 0x4, 0x10, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A}), OS_WINDOWS);
    os_detection_notify_usb_device_state_change(usb_device_state_configured);
    advance_time(OS_DETECTION_DEBOUNCE - 1);
    os_detection_task();
    assert_not_reported();
    EXPECT_EQ(detected_host_os(), OS_WINDOWS);

    // advancing the timer alone must not cause a report
    advance_time(1);
    assert_not_reported();
    EXPECT_EQ(detected_host_os(), OS_WINDOWS);
    // the task will cause a report
    os_detection_task();
    assert_reported(OS_WINDOWS);
    EXPECT_EQ(detected_host_os(), OS_WINDOWS);

    // check that it remains the same after a long time
    advance_time(OS_DETECTION_DEBOUNCE * 10);
    os_detection_task();
    assert_reported(OS_WINDOWS);
    EXPECT_EQ(detected_host_os(), OS_WINDOWS);
}

TEST_F(OsDetectionTest, TestDoNotGoBackToUnsure) {
    // 0x02 would cause it to go back to Unsure, so check that it does not
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0xFF, 0xFE, 0x02}), OS_LINUX);
    os_detection_task();
    assert_not_reported();
}
