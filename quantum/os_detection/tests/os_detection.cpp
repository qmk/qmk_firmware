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
}

class OsDetectionTest : public ::testing::Test {
   protected:
    void SetUp() override {
        erase_wlength_data();
    }
};

os_variant_t check_sequence(const std::vector<uint16_t> &w_lengths) {
    for (auto &w_length : w_lengths) {
        process_wlength(w_length);
    }
    return detected_host_os();
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
}

TEST_F(OsDetectionTest, TestChibiosMacos) {
    EXPECT_EQ(check_sequence({0x2, 0x24, 0x2, 0x28, 0xFF}), OS_MACOS);
}

TEST_F(OsDetectionTest, TestLufaMacos) {
    EXPECT_EQ(check_sequence({0x2, 0x10, 0x2, 0xE, 0xFF}), OS_MACOS);
}

TEST_F(OsDetectionTest, TestVusbMacos) {
    EXPECT_EQ(check_sequence({0x2, 0xE, 0x2, 0xE, 0xFF}), OS_MACOS);
}

TEST_F(OsDetectionTest, TestChibiosIos) {
    EXPECT_EQ(check_sequence({0x2, 0x24, 0x2, 0x28}), OS_IOS);
}

TEST_F(OsDetectionTest, TestLufaIos) {
    EXPECT_EQ(check_sequence({0x2, 0x10, 0x2, 0xE}), OS_IOS);
}

TEST_F(OsDetectionTest, TestVusbIos) {
    EXPECT_EQ(check_sequence({0x2, 0xE, 0x2, 0xE}), OS_IOS);
}

TEST_F(OsDetectionTest, TestChibiosWindows10) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0x4, 0x24, 0x4, 0x24, 0x4, 0xFF, 0x24, 0xFF, 0x4, 0xFF, 0x24, 0x4, 0x24, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A}), OS_WINDOWS);
}

TEST_F(OsDetectionTest, TestChibiosWindows10_2) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0x4, 0x24, 0x4, 0x24, 0x4, 0x24, 0x4, 0x24, 0x4, 0x24}), OS_WINDOWS);
}

TEST_F(OsDetectionTest, TestLufaWindows10) {
    EXPECT_EQ(check_sequence({0x12, 0xFF, 0xFF, 0x4, 0x10, 0xFF, 0xFF, 0xFF, 0x4, 0x10, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A}), OS_WINDOWS);
}

TEST_F(OsDetectionTest, TestLufaWindows10_2) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0x4, 0x10, 0xFF, 0x4, 0xFF, 0x10, 0xFF, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A, 0x20A}), OS_WINDOWS);
}

TEST_F(OsDetectionTest, TestLufaWindows10_3) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0x4, 0x10, 0x4, 0x10}), OS_WINDOWS);
}

TEST_F(OsDetectionTest, TestVusbWindows10) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0x4, 0xE, 0xFF}), OS_WINDOWS);
}

TEST_F(OsDetectionTest, TestVusbWindows10_2) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0x4, 0xE, 0x4}), OS_WINDOWS);
}

TEST_F(OsDetectionTest, TestChibiosPs5) {
    EXPECT_EQ(check_sequence({0x2, 0x4, 0x2, 0x28, 0x2, 0x24}), OS_LINUX);
}

TEST_F(OsDetectionTest, TestLufaPs5) {
    EXPECT_EQ(check_sequence({0x2, 0x4, 0x2, 0xE, 0x2, 0x10}), OS_LINUX);
}

TEST_F(OsDetectionTest, TestVusbPs5) {
    EXPECT_EQ(check_sequence({0x2, 0x4, 0x2, 0xE, 0x2}), OS_LINUX);
}

TEST_F(OsDetectionTest, TestChibiosNintendoSwitch) {
    EXPECT_EQ(check_sequence({0x82, 0xFF, 0x40, 0x40, 0xFF, 0x40, 0x40, 0xFF, 0x40, 0x40, 0xFF, 0x40, 0x40, 0xFF, 0x40, 0x40}), OS_LINUX);
}

TEST_F(OsDetectionTest, TestLufaNintendoSwitch) {
    EXPECT_EQ(check_sequence({0x82, 0xFF, 0x40, 0x40, 0xFF, 0x40, 0x40}), OS_LINUX);
}

TEST_F(OsDetectionTest, TestVusbNintendoSwitch) {
    EXPECT_EQ(check_sequence({0x82, 0xFF, 0x40, 0x40}), OS_LINUX);
}

TEST_F(OsDetectionTest, TestChibiosQuest2) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF}), OS_LINUX);
}

TEST_F(OsDetectionTest, TestVusbQuest2) {
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0xFF, 0xFE}), OS_LINUX);
}
