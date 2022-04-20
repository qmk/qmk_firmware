// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <numeric>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "backing_mocks.hpp"

class WearLeveling8ByteConsolidation : public ::testing::Test {
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
TEST_F(WearLeveling8ByteConsolidation, MultibyteBackingStoreWriteCounts) {
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

        // Check that we got the expected number of write log entries
        EXPECT_EQ(std::distance(inst.log_begin(), inst.log_end()), 1);
    }
}

/**
 * This test forces consolidation by writing enough to the write log that it overflows, consolidating the data into the
 * base logical area.
 */
TEST_F(WearLeveling8ByteConsolidation, ConsolidationOverflow) {
    auto& inst = MockBackingStore::Instance();

    // Generate a test block of data
    std::array<std::uint8_t, WEAR_LEVELING_LOGICAL_SIZE> testvalue;
    std::iota(testvalue.begin(), testvalue.end(), 0x20);

    // Write the data
    EXPECT_EQ(test_write(0, testvalue.data(), testvalue.size()), WEAR_LEVELING_CONSOLIDATED) << "Write failed with incorrect status";

    // The write log is 32 bytes, so we expect 4 backing store writes before consolidation (log entries 0...3).
    // Consolidation will perform an erase (log entry 4), then write the resulting data to the first 32 bytes in the backing store (log entries 5...9).
    EXPECT_EQ(std::distance(inst.log_begin(), inst.log_end()), 9);

    // Verify the backing store writes for the write log
    std::size_t       index;
    write_log_entry_t e;
    for (index = 0; index < 4; ++index) {
        auto write_iter = inst.log_begin() + index;
        EXPECT_EQ(write_iter->address, WEAR_LEVELING_LOGICAL_SIZE + (index * BACKING_STORE_WRITE_SIZE)) << "Invalid write log address";
        write_log_entry_t e;
        e.raw64 = write_iter->value;
        EXPECT_EQ(LOG_ENTRY_GET_TYPE(e), LOG_ENTRY_TYPE_MULTIBYTE) << "Invalid write log entry type";
    }

    // Verify the backing store erase
    {
        index           = 4;
        auto write_iter = inst.log_begin() + index;
        e.raw64         = write_iter->value;
        EXPECT_TRUE(write_iter->erased) << "Backing store erase did not occur as required";
    }

    // Verify the backing store writes for consolidation
    for (index = 5; index < 9; ++index) {
        auto write_iter = inst.log_begin() + index;
        EXPECT_EQ(write_iter->address, (index - 5) * 8) << "Invalid write log entry address";
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