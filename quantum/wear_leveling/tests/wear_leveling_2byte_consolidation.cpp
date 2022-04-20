// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <numeric>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "backing_mocks.hpp"

class WearLeveling2ByteConsolidation : public ::testing::Test {
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
 * This test forces consolidation by writing enough to the write log that it overflows, consolidating the data into the
 * base logical area.
 */
TEST_F(WearLeveling2ByteConsolidation, ConsolidationOverflow) {
    auto& inst = MockBackingStore::Instance();

    // Generate a test block of data which forces OPTIMIZED_64 writes
    std::array<std::uint8_t, WEAR_LEVELING_LOGICAL_SIZE> testvalue;
    std::iota(testvalue.begin(), testvalue.end(), 0x20);

    // Write the data
    EXPECT_EQ(test_write(0, testvalue.data(), testvalue.size()), WEAR_LEVELING_CONSOLIDATED) << "Write failed with incorrect status";

    // All writes are at address<64, so each logical byte written will generate 1 write log entry, thus 1 backing store write.
    // The write log is 32 bytes, so we expect 16 backing store writes before consolidation (log entries 0...15).
    // Consolidation will perform an erase (log entry 16), then write the resulting data to the first 32 bytes in the backing store (log entries 17...33).
    EXPECT_EQ(std::distance(inst.log_begin(), inst.log_end()), 33);

    // Verify the backing store writes for the write log
    std::size_t       index;
    write_log_entry_t e;
    for (index = 0; index < 16; ++index) {
        auto write_iter = inst.log_begin() + index;
        EXPECT_EQ(write_iter->address, WEAR_LEVELING_LOGICAL_SIZE + (index * BACKING_STORE_WRITE_SIZE)) << "Invalid write log address";
        e.raw16[0] = write_iter->value;
        EXPECT_EQ(LOG_ENTRY_GET_TYPE(e), LOG_ENTRY_TYPE_OPTIMIZED_64) << "Invalid write log entry type";
    }

    // Verify the backing store erase
    {
        index           = 16;
        auto write_iter = inst.log_begin() + index;
        e.raw16[0]      = write_iter->value;
        EXPECT_TRUE(write_iter->erased) << "Backing store erase did not occur as required";
    }

    // Verify the backing store writes for consolidation
    for (index = 17; index < 33; ++index) {
        auto write_iter = inst.log_begin() + index;
        EXPECT_EQ(write_iter->address, (index - 17) * 2) << "Invalid write log entry address";
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
