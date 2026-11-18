// Copyright 2026 Andre Brait (@andrebrait)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gtest/gtest.h"

extern "C" {
#include "os_detection.h"
#include "eeprom.h"
#include "nvm_os_detection.h"
}

static void fill_eeprom(uint8_t value) {
    for (uintptr_t i = 0; i < EEPROM_SIZE; ++i) {
        eeprom_write_byte(reinterpret_cast<uint8_t *>(i), value);
    }
}

static size_t changed_eeprom_bytes(uint8_t fill) {
    size_t changed = 0;
    for (uintptr_t i = 0; i < EEPROM_SIZE; ++i) {
        changed += eeprom_read_byte(reinterpret_cast<const uint8_t *>(i)) != fill;
    }
    return changed;
}

// Magic, capture count and capture reason.
static const size_t header_bytes = sizeof(uint16_t) + 2;

class OsDetectionDebugTest : public ::testing::Test {
   protected:
    void SetUp() override {
        fill_eeprom(0xA5);
        erase_wlength_data();
    }
};

TEST_F(OsDetectionDebugTest, ErasedOrStaleStorageHoldsNoCapture) {
    for (uint8_t fill : {0x00, 0x01, 0xA5, 0xFF}) {
        fill_eeprom(fill);
        EXPECT_EQ(nvm_os_detection_read_setup_count(), 0) << "fill 0x" << std::hex << int(fill);
    }
}

TEST_F(OsDetectionDebugTest, StoredCaptureRoundTripsWithinBlock) {
    for (uint16_t w_length : {0xFF, 0x4, 0x2}) {
        process_wlength(w_length);
    }
    store_setups_in_eeprom();

    ASSERT_EQ(nvm_os_detection_read_setup_count(), 3);
    EXPECT_EQ(nvm_os_detection_read_setup(0), 0xFF);
    EXPECT_EQ(nvm_os_detection_read_setup(1), 0x4);
    EXPECT_EQ(nvm_os_detection_read_setup(2), 0x2);
    EXPECT_LE(changed_eeprom_bytes(0xA5), header_bytes + 3 * sizeof(uint16_t));
}

TEST_F(OsDetectionDebugTest, OversizedCaptureIsClampedToBlock) {
    uint16_t setups[OS_DETECTION_STORED_SETUPS + 10];
    for (uint16_t i = 0; i < OS_DETECTION_STORED_SETUPS + 10; ++i) {
        setups[i] = i;
    }
    nvm_os_detection_update_setups(setups, OS_DETECTION_STORED_SETUPS + 10, 0);

    ASSERT_EQ(nvm_os_detection_read_setup_count(), OS_DETECTION_STORED_SETUPS);
    EXPECT_EQ(nvm_os_detection_read_setup(OS_DETECTION_STORED_SETUPS - 1), OS_DETECTION_STORED_SETUPS - 1);
    EXPECT_LE(changed_eeprom_bytes(0xA5), header_bytes + OS_DETECTION_STORED_SETUPS * sizeof(uint16_t));
}

TEST_F(OsDetectionDebugTest, EraseClearsCapture) {
    process_wlength(0xFF);
    store_setups_in_eeprom();
    nvm_os_detection_erase();
    EXPECT_EQ(nvm_os_detection_read_setup_count(), 0);
}
