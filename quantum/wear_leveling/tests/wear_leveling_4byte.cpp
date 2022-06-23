// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <numeric>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "backing_mocks.hpp"

class WearLeveling4Byte : public ::testing::Test {
   protected:
    void SetUp() override {
        MockBackingStore::Instance().reset_instance();
        wear_leveling_init();
    }
};

static std::array<std::uint8_t, WEAR_LEVELING_LOGICAL_SIZE> verify_data;

static wear_leveling_status_t test_write(const uint32_t address, const void* value, size_t length) {
    memcpy(&verify_data[address], value, length);
    return wear_leveling_write(address, value, length);
}

/**
 * This test ensures the correct number of backing store writes occurs with a multibyte write, given the input buffer size.
 */
TEST_F(WearLeveling4Byte, MultibyteBackingStoreWriteCounts) {
    auto& inst = MockBackingStore::Instance();

    for (std::size_t length = 1; length <= 5; ++length) {
        // Clear things out
        std::fill(verify_data.begin(), verify_data.end(), 0);
        inst.reset_instance();
        wear_leveling_init();

        // Generate a test block of data
        std::vector<std::uint8_t> testvalue(length);
        std::iota(testvalue.begin(), testvalue.end(), 0x20);

        // Write the data
        EXPECT_EQ(test_write(0, testvalue.data(), testvalue.size()), WEAR_LEVELING_SUCCESS) << "Write failed with incorrect status";

        std::size_t expected;
        if (length > 1) {
            expected = 2;
        } else {
            expected = 1;
        }

        // Check that we got the expected number of write log entries
        EXPECT_EQ(std::distance(inst.log_begin(), inst.log_end()), expected);
    }
}

/**
 * This test forces consolidation by writing enough to the write log that it overflows, consolidating the data into the
 * base logical area.
 */
TEST_F(WearLeveling4Byte, ConsolidationOverflow) {
    auto& inst = MockBackingStore::Instance();

    // Generate a test block of data
    std::array<std::uint8_t, WEAR_LEVELING_LOGICAL_SIZE> testvalue;
    std::iota(testvalue.begin(), testvalue.end(), 0x20);

    // Write the data
    EXPECT_EQ(test_write(0, testvalue.data(), testvalue.size()), WEAR_LEVELING_CONSOLIDATED) << "Write failed with incorrect status";

    // The write log is 24 bytes, so we expect 6 backing store writes before consolidation (log entries 0...5).
    // Consolidation will perform an erase (log entry 6), then write the resulting data to the first 24 bytes in the backing store (log entries 7...12).
    EXPECT_EQ(std::distance(inst.log_begin(), inst.log_end()), 13) << "Invalid number of entries in the write log";

    // All multibyte writes for this block result in two backing store writes, based off the length
    std::size_t       index;
    write_log_entry_t e;
    for (index = 0; index < 6; ++index) {
        auto write_iter = inst.log_begin() + index;
        EXPECT_EQ(write_iter->address, WEAR_LEVELING_LOGICAL_SIZE + (index * BACKING_STORE_WRITE_SIZE)) << "Invalid write log address";
        // If this is the backing store write that contains the metadata, verify it
        if (index % 2 == 0) {
            e.raw32[0] = write_iter->value;
            EXPECT_EQ(LOG_ENTRY_GET_TYPE(e), LOG_ENTRY_TYPE_MULTIBYTE) << "Invalid write log entry type";
        }
    }

    // Verify the backing store erase
    {
        index           = 6;
        auto write_iter = inst.log_begin() + index;
        e.raw32[0]      = write_iter->value;
        EXPECT_TRUE(write_iter->erased) << "Backing store erase did not occur as required";
    }

    // Verify the backing store writes for consolidation
    for (index = 7; index < 13; ++index) {
        auto write_iter = inst.log_begin() + index;
        EXPECT_EQ(write_iter->address, (index - 7) * 4) << "Invalid write log entry address";
    }

    // Verify the data is what we expected
    std::array<std::uint8_t, WEAR_LEVELING_LOGICAL_SIZE> readback;
    EXPECT_EQ(wear_leveling_read(0, readback.data(), WEAR_LEVELING_LOGICAL_SIZE), WEAR_LEVELING_SUCCESS) << "Failed to read back the saved data";
    EXPECT_TRUE(memcmp(readback.data(), verify_data.data(), WEAR_LEVELING_LOGICAL_SIZE) == 0) << "Readback did not match";

    // Re-init and re-read, verifying the reload capability
    EXPECT_NE(wear_leveling_init(), WEAR_LEVELING_FAILED) << "Re-initialisation failed";
    EXPECT_EQ(wear_leveling_read(0, readback.data(), WEAR_LEVELING_LOGICAL_SIZE), WEAR_LEVELING_SUCCESS) << "Failed to read back the saved data";
    EXPECT_TRUE(memcmp(readback.data(), verify_data.data(), WEAR_LEVELING_LOGICAL_SIZE) == 0) << "Readback did not match";
}

/**
 * This test verifies multibyte readback gets canceled with an out-of-bounds address.
 */
TEST_F(WearLeveling4Byte, PlaybackReadbackMultibyte_OOB) {
    auto& inst     = MockBackingStore::Instance();
    auto  logstart = inst.storage_begin() + (WEAR_LEVELING_LOGICAL_SIZE / sizeof(backing_store_int_t));

    // Set up a 2-byte logical write of [0x11,0x12] at logical offset 0x10
    auto entry0    = LOG_ENTRY_MAKE_MULTIBYTE(0x10, 2);
    entry0.raw8[3] = 0x11;
    entry0.raw8[4] = 0x12;
    (logstart + 0)->set(~entry0.raw32[0]);
    (logstart + 1)->set(~entry0.raw32[1]);

    // Set up a 2-byte logical write of [0x13,0x14] at logical offset 0x1000 (out of bounds)
    auto entry1    = LOG_ENTRY_MAKE_MULTIBYTE(0x1000, 2);
    entry1.raw8[3] = 0x13;
    entry1.raw8[4] = 0x14;
    (logstart + 2)->set(~entry1.raw32[0]);
    (logstart + 3)->set(~entry1.raw32[1]);

    // Set up a 2-byte logical write of [0x15,0x16] at logical offset 0x10
    auto entry2    = LOG_ENTRY_MAKE_MULTIBYTE(0x10, 2);
    entry2.raw8[3] = 0x15;
    entry2.raw8[4] = 0x16;
    (logstart + 4)->set(~entry2.raw32[0]);
    (logstart + 5)->set(~entry2.raw32[1]);

    EXPECT_EQ(inst.erasure_count(), 0) << "Invalid initial erase count";
    EXPECT_EQ(wear_leveling_init(), WEAR_LEVELING_CONSOLIDATED) << "Readback should have failed and triggered consolidation";
    EXPECT_EQ(inst.erasure_count(), 1) << "Invalid final erase count";

    uint8_t buf[2];
    wear_leveling_read(0x10, buf, sizeof(buf));
    EXPECT_EQ(buf[0], 0x11) << "Readback should have maintained the previous pre-failure value from the write log";
    EXPECT_EQ(buf[1], 0x12) << "Readback should have maintained the previous pre-failure value from the write log";
}
