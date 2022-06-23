// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <numeric>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "backing_mocks.hpp"

class WearLeveling2Byte : public ::testing::Test {
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
TEST_F(WearLeveling2Byte, ConsolidationOverflow) {
    auto& inst = MockBackingStore::Instance();

    // Generate a test block of data which forces OPTIMIZED_64 writes
    std::array<std::uint8_t, WEAR_LEVELING_LOGICAL_SIZE> testvalue;
    std::iota(testvalue.begin(), testvalue.end(), 0x20);

    // Write the data
    EXPECT_EQ(test_write(0, testvalue.data(), testvalue.size()), WEAR_LEVELING_CONSOLIDATED) << "Write failed with incorrect status";

    // All writes are at address<64, so each logical byte written will generate 1 write log entry, thus 1 backing store write.
    // The write log is 24 bytes, so we expect 12 backing store writes before consolidation (log entries 0...11).
    // Consolidation will perform an erase (log entry 12), then write the resulting data to the first 24 bytes in the backing store (log entries 13...24).
    EXPECT_EQ(std::distance(inst.log_begin(), inst.log_end()), 25);

    // Verify the backing store writes for the write log
    std::size_t       index;
    write_log_entry_t e;
    for (index = 0; index < 12; ++index) {
        auto write_iter = inst.log_begin() + index;
        EXPECT_EQ(write_iter->address, WEAR_LEVELING_LOGICAL_SIZE + (index * BACKING_STORE_WRITE_SIZE)) << "Invalid write log address";
        e.raw16[0] = write_iter->value;
        EXPECT_EQ(LOG_ENTRY_GET_TYPE(e), LOG_ENTRY_TYPE_OPTIMIZED_64) << "Invalid write log entry type";
    }

    // Verify the backing store erase
    {
        index           = 12;
        auto write_iter = inst.log_begin() + index;
        e.raw16[0]      = write_iter->value;
        EXPECT_TRUE(write_iter->erased) << "Backing store erase did not occur as required";
    }

    // Verify the backing store writes for consolidation
    for (index = 13; index < 25; ++index) {
        auto write_iter = inst.log_begin() + index;
        EXPECT_EQ(write_iter->address, (index - 13) * 2) << "Invalid write log entry address";
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
TEST_F(WearLeveling2Byte, PlaybackReadbackMultibyte_OOB) {
    auto& inst     = MockBackingStore::Instance();
    auto  logstart = inst.storage_begin() + (WEAR_LEVELING_LOGICAL_SIZE / sizeof(backing_store_int_t));

    // Set up a 2-byte logical write of [0x11,0x12] at logical offset 0x10
    auto entry0    = LOG_ENTRY_MAKE_MULTIBYTE(0x10, 2);
    entry0.raw8[3] = 0x11;
    entry0.raw8[4] = 0x12;
    (logstart + 0)->set(~entry0.raw16[0]);
    (logstart + 1)->set(~entry0.raw16[1]);
    (logstart + 2)->set(~entry0.raw16[2]);

    // Set up a 2-byte logical write of [0x13,0x14] at logical offset 0x1000 (out of bounds)
    auto entry1    = LOG_ENTRY_MAKE_MULTIBYTE(0x1000, 2);
    entry1.raw8[3] = 0x13;
    entry1.raw8[4] = 0x14;
    (logstart + 3)->set(~entry1.raw16[0]);
    (logstart + 4)->set(~entry1.raw16[1]);
    (logstart + 5)->set(~entry1.raw16[2]);

    // Set up a 2-byte logical write of [0x15,0x16] at logical offset 0x10
    auto entry2    = LOG_ENTRY_MAKE_MULTIBYTE(0x10, 2);
    entry2.raw8[3] = 0x15;
    entry2.raw8[4] = 0x16;
    (logstart + 6)->set(~entry2.raw16[0]);
    (logstart + 7)->set(~entry2.raw16[1]);
    (logstart + 8)->set(~entry2.raw16[2]);

    EXPECT_EQ(inst.erasure_count(), 0) << "Invalid initial erase count";
    EXPECT_EQ(wear_leveling_init(), WEAR_LEVELING_CONSOLIDATED) << "Readback should have failed and triggered consolidation";
    EXPECT_EQ(inst.erasure_count(), 1) << "Invalid final erase count";

    uint8_t buf[2];
    wear_leveling_read(0x10, buf, sizeof(buf));
    EXPECT_EQ(buf[0], 0x11) << "Readback should have maintained the previous pre-failure value from the write log";
    EXPECT_EQ(buf[1], 0x12) << "Readback should have maintained the previous pre-failure value from the write log";
}

/**
 * This test verifies optimized 64 readback gets canceled with an out-of-bounds address.
 */
TEST_F(WearLeveling2Byte, PlaybackReadbackOptimized64_OOB) {
    auto& inst     = MockBackingStore::Instance();
    auto  logstart = inst.storage_begin() + (WEAR_LEVELING_LOGICAL_SIZE / sizeof(backing_store_int_t));

    // Set up a 1-byte logical write of 0x11 at logical offset 0x10
    auto entry0 = LOG_ENTRY_MAKE_OPTIMIZED_64(0x10, 0x11);
    (logstart + 0)->set(~entry0.raw16[0]);

    // Set up a 1-byte logical write of 0x11 at logical offset 0x30 (out of bounds)
    auto entry1 = LOG_ENTRY_MAKE_OPTIMIZED_64(0x30, 0x11);
    (logstart + 1)->set(~entry1.raw16[0]);

    // Set up a 1-byte logical write of 0x12 at logical offset 0x10
    auto entry2 = LOG_ENTRY_MAKE_OPTIMIZED_64(0x10, 0x12);
    (logstart + 2)->set(~entry2.raw16[0]);

    EXPECT_EQ(inst.erasure_count(), 0) << "Invalid initial erase count";
    EXPECT_EQ(wear_leveling_init(), WEAR_LEVELING_CONSOLIDATED) << "Readback should have failed and triggered consolidation";
    EXPECT_EQ(inst.erasure_count(), 1) << "Invalid final erase count";
    uint8_t tmp;
    wear_leveling_read(0x10, &tmp, sizeof(tmp));
    EXPECT_EQ(tmp, 0x11) << "Readback should have maintained the previous pre-failure value from the write log";
}

/**
 * This test verifies word 0/1 readback gets canceled with an out-of-bounds address.
 */
TEST_F(WearLeveling2Byte, PlaybackReadbackWord01_OOB) {
    auto& inst     = MockBackingStore::Instance();
    auto  logstart = inst.storage_begin() + (WEAR_LEVELING_LOGICAL_SIZE / sizeof(backing_store_int_t));

    // Set up a 1-byte logical write of 1 at logical offset 0x10
    auto entry0 = LOG_ENTRY_MAKE_WORD_01(0x10, 1);
    (logstart + 0)->set(~entry0.raw16[0]);

    // Set up a 1-byte logical write of 1 at logical offset 0x1000 (out of bounds)
    auto entry1 = LOG_ENTRY_MAKE_WORD_01(0x1000, 1);
    (logstart + 1)->set(~entry1.raw16[0]);

    // Set up a 1-byte logical write of 0 at logical offset 0x10
    auto entry2 = LOG_ENTRY_MAKE_WORD_01(0x10, 0);
    (logstart + 2)->set(~entry2.raw16[0]);

    EXPECT_EQ(inst.erasure_count(), 0) << "Invalid initial erase count";
    EXPECT_EQ(wear_leveling_init(), WEAR_LEVELING_CONSOLIDATED) << "Readback should have failed and triggered consolidation";
    EXPECT_EQ(inst.erasure_count(), 1) << "Invalid final erase count";
    uint8_t tmp;
    wear_leveling_read(0x10, &tmp, sizeof(tmp));
    EXPECT_EQ(tmp, 1) << "Readback should have maintained the previous pre-failure value from the write log";
}
