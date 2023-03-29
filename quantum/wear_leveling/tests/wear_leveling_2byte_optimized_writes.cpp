// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <numeric>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "backing_mocks.hpp"

class WearLeveling2ByteOptimizedWrites : public ::testing::Test {
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
TEST_F(WearLeveling2ByteOptimizedWrites, MultibyteBackingStoreWriteCounts) {
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
        EXPECT_EQ(test_write(2000, testvalue.data(), testvalue.size()), WEAR_LEVELING_SUCCESS) << "Write failed with incorrect status";

        std::size_t expected;
        if (length > 3) {
            expected = 4;
        } else if (length > 1) {
            expected = 3;
        } else {
            expected = 2;
        }

        // Check that we got the expected number of write log entries
        EXPECT_EQ(std::distance(inst.log_begin(), inst.log_end()), expected);
    }
}

/**
 * This test runs through writing U16 values of `0` or `1` over the entire logical address range, to even addresses only.
 *  - Addresses <16384 will result in a single optimised backing write
 *  - Higher addresses will result in a multibyte write of 3 backing writes
 */
TEST_F(WearLeveling2ByteOptimizedWrites, WriteOneThenZeroToEvenAddresses) {
    auto& inst = MockBackingStore::Instance();

    // Only attempt writes for each address up to a limit that would NOT force a consolidated data write.
    std::size_t writes_per_loop = (MOCK_WRITE_LOG_MAX_ENTRIES::value / 6) - 1; // Worst case is 6 writes for each pair of writes of 0/1
    std::size_t final_address;
    for (uint32_t address = 0; address < WEAR_LEVELING_LOGICAL_SIZE; address += (writes_per_loop * 2)) {
        // Clear things out
        std::fill(verify_data.begin(), verify_data.end(), 0);
        inst.reset_instance();
        wear_leveling_init();

        // Loop through all the addresses in this range
        std::size_t expected = 0;
        for (uint32_t offset = 0; offset < (writes_per_loop * 2); offset += 2) {
            // If we're about to exceed the limit of the logical store, skip the writes
            if (address + offset + 2 > WEAR_LEVELING_LOGICAL_SIZE) {
                break;
            }

            // The default erased value of the wear-leveling cache is zero, so we write a one first, then a zero, to ensure a backing store write occurs.
            uint16_t val = 1;
            EXPECT_EQ(test_write(address + offset, &val, sizeof(val)), WEAR_LEVELING_SUCCESS) << "Write failed with incorrect status";
            val = 0;
            EXPECT_EQ(test_write(address + offset, &val, sizeof(val)), WEAR_LEVELING_SUCCESS) << "Write failed with incorrect status";

            std::size_t backing_store_writes_expected = 0;
            if (address + offset < 16384) {
                // A U16 value of 0/1 at an even address <16384 will result in 1 backing write each, so we need 2 backing writes for 2 logical writes
                backing_store_writes_expected = 2;
            } else {
                // All other addresses result in a multibyte write (3 backing store writes) to write two local bytes of data
                backing_store_writes_expected = 6;
            }

            // Keep track of the total number of expected writes to the backing store
            expected += backing_store_writes_expected;

            // Verify we're at the correct number of writes
            EXPECT_EQ(std::distance(inst.log_begin(), inst.log_end()), expected) << "Write log doesn't match required number of backing store writes for address " << (address + offset);

            // Verify that the write log entries we expect are actually present
            std::size_t       write_index = expected - backing_store_writes_expected;
            auto              write_iter  = inst.log_begin() + write_index;
            write_log_entry_t e;
            if (address + offset < 16384) {
                // A U16 value of 0/1 at an even address <16384 will result in 1 backing write each, so we need 2 backing writes for 2 logical writes
                for (std::size_t i = 0; i < 2; ++i) {
                    e.raw16[0] = write_iter->value;
                    EXPECT_EQ(LOG_ENTRY_GET_TYPE(e), LOG_ENTRY_TYPE_WORD_01) << "Invalid write log entry type at " << (address + offset);
                    ++write_iter;
                }
            } else {
                // Multibyte write
                e.raw16[0] = write_iter->value;
                EXPECT_EQ(LOG_ENTRY_GET_TYPE(e), LOG_ENTRY_TYPE_MULTIBYTE) << "Invalid write log entry type at " << (address + offset);
                EXPECT_EQ(LOG_ENTRY_MULTIBYTE_GET_LENGTH(e), 2) << "Invalid write log entry length at " << (address + offset);
                ++write_iter;
            }

            // Keep track of the final address written, so we can verify the entire logical range was handled
            final_address = address + offset;
        }

        // Verify the number of writes that occurred to the backing store
        size_t backing_write_count = std::distance(inst.log_begin(), inst.log_end());
        EXPECT_EQ(backing_write_count, expected) << "Invalid write count at address " << address;

        // Verify the data is what we expected
        std::array<std::uint8_t, WEAR_LEVELING_LOGICAL_SIZE> readback;
        EXPECT_EQ(wear_leveling_read(0, readback.data(), WEAR_LEVELING_LOGICAL_SIZE), WEAR_LEVELING_SUCCESS) << "Failed to read back the saved data";
        EXPECT_TRUE(memcmp(readback.data(), verify_data.data(), WEAR_LEVELING_LOGICAL_SIZE) == 0) << "Readback for address " << address << " did not match";

        // Re-init and re-read, testing the reload capability
        EXPECT_NE(wear_leveling_init(), WEAR_LEVELING_FAILED) << "Re-initialisation failed";
        EXPECT_EQ(wear_leveling_read(0, readback.data(), WEAR_LEVELING_LOGICAL_SIZE), WEAR_LEVELING_SUCCESS) << "Failed to read back the saved data";
        EXPECT_TRUE(memcmp(readback.data(), verify_data.data(), WEAR_LEVELING_LOGICAL_SIZE) == 0) << "Readback for address " << address << " did not match";
    }

    // Verify the full range of the logical area got written
    EXPECT_EQ(final_address, WEAR_LEVELING_LOGICAL_SIZE - 2) << "Invalid final write address";
}

/**
 * This test runs through writing U16 values of `0` or `1` over the entire logical address range, to odd addresses only.
 *  - Addresses <63 will result in 2 optimised backing writes
 *  - Address 63 results in a single optimised backing write for the first logical byte, and a multibyte write of 2 backing writes for the second logical byte
 *  - Higher addresses will result in a multibyte write of 3 backing writes
 */
TEST_F(WearLeveling2ByteOptimizedWrites, WriteOneThenZeroToOddAddresses) {
    auto& inst = MockBackingStore::Instance();

    // Only attempt writes for each address up to a limit that would NOT force a consolidated data write.
    std::size_t writes_per_loop = (MOCK_WRITE_LOG_MAX_ENTRIES::value / 6) - 1; // Worst case is 6 writes for each pair of writes of 0/1
    std::size_t final_address;
    for (uint32_t address = 1; address < WEAR_LEVELING_LOGICAL_SIZE; address += (writes_per_loop * 2)) {
        // Clear things out
        std::fill(verify_data.begin(), verify_data.end(), 0);
        inst.reset_instance();
        wear_leveling_init();

        // Loop through all the addresses in this range
        std::size_t expected = 0;
        for (uint32_t offset = 0; offset < (writes_per_loop * 2); offset += 2) {
            // If we're about to exceed the limit of the logical store, skip the writes
            if (address + offset + 2 > WEAR_LEVELING_LOGICAL_SIZE) {
                break;
            }

            // The default erased value of the wear-leveling cache is zero, so we write a one first, then a zero, to ensure a backing store write occurs.
            uint16_t val = 1;
            EXPECT_EQ(test_write(address + offset, &val, sizeof(val)), WEAR_LEVELING_SUCCESS) << "Write failed with incorrect status";
            val = 0;
            EXPECT_EQ(test_write(address + offset, &val, sizeof(val)), WEAR_LEVELING_SUCCESS) << "Write failed with incorrect status";

            std::size_t backing_store_writes_expected = 0;
            if (address + offset < 63) {
                // A U16 value of 0/1 at an odd address <64 will result in 2 backing writes each, so we need 4 backing writes for 2 logical writes
                backing_store_writes_expected = 4;
            } else if (address + offset == 63) {
                // If we're straddling the boundary for optimised bytes (addr==64), then the first logical byte is written using the optimised write (1 backing
                // store write), and the second logical byte uses a multibyte write (2 backing store writes)
                backing_store_writes_expected = 2    // First logical bytes written using optimised log entries
                                                + 4; // Second logical bytes written using multibyte log entries
            } else {
                // All other addresses result in a multibyte write (3 backing store writes) to write two local bytes of data
                backing_store_writes_expected = 6;
            }

            // Keep track of the total number of expected writes to the backing store
            expected += backing_store_writes_expected;

            // Verify we're at the correct number of writes
            EXPECT_EQ(std::distance(inst.log_begin(), inst.log_end()), expected) << "Write log doesn't match required number of backing store writes for address " << (address + offset);

            // Verify that the write log entries we expect are actually present
            std::size_t       write_index = expected - backing_store_writes_expected;
            auto              write_iter  = inst.log_begin() + write_index;
            write_log_entry_t e;
            if (address + offset < 63) {
                // A U16 value of 0/1 at an odd address <64 will result in 2 backing writes each, so we need 4 backing writes for 2 logical writes
                for (std::size_t i = 0; i < 4; ++i) {
                    e.raw16[0] = write_iter->value;
                    EXPECT_EQ(LOG_ENTRY_GET_TYPE(e), LOG_ENTRY_TYPE_OPTIMIZED_64) << "Invalid write log entry type";
                    ++write_iter;
                }
            } else if (address + offset == 63) {
                // First log entry is the 64-addr optimised one
                e.raw16[0] = write_iter->value;
                EXPECT_EQ(LOG_ENTRY_GET_TYPE(e), LOG_ENTRY_TYPE_OPTIMIZED_64) << "Invalid write log entry type";
                ++write_iter;

                // Second log entry is the multibyte entry for the second logical byte
                e.raw16[0] = write_iter->value;
                EXPECT_EQ(LOG_ENTRY_GET_TYPE(e), LOG_ENTRY_TYPE_MULTIBYTE) << "Invalid write log entry type";
                EXPECT_EQ(LOG_ENTRY_MULTIBYTE_GET_LENGTH(e), 1) << "Invalid write log entry length";
                ++write_iter;
            } else {
                // Multibyte write
                e.raw16[0] = write_iter->value;
                EXPECT_EQ(LOG_ENTRY_GET_TYPE(e), LOG_ENTRY_TYPE_MULTIBYTE) << "Invalid write log entry type";
                EXPECT_EQ(LOG_ENTRY_MULTIBYTE_GET_LENGTH(e), 2) << "Invalid write log entry length";
                ++write_iter;
            }

            // Keep track of the final address written, so we can verify the entire logical range was handled
            final_address = address + offset;
        }

        // Verify the number of writes that occurred to the backing store
        size_t backing_write_count = std::distance(inst.log_begin(), inst.log_end());
        EXPECT_EQ(backing_write_count, expected) << "Invalid write count at address " << address;

        // Verify the data is what we expected
        std::array<std::uint8_t, WEAR_LEVELING_LOGICAL_SIZE> readback;
        EXPECT_EQ(wear_leveling_read(0, readback.data(), WEAR_LEVELING_LOGICAL_SIZE), WEAR_LEVELING_SUCCESS) << "Failed to read back the saved data";
        EXPECT_TRUE(memcmp(readback.data(), verify_data.data(), WEAR_LEVELING_LOGICAL_SIZE) == 0) << "Readback for address " << address << " did not match";

        // Re-init and re-read, testing the reload capability
        EXPECT_NE(wear_leveling_init(), WEAR_LEVELING_FAILED) << "Re-initialisation failed";
        EXPECT_EQ(wear_leveling_read(0, readback.data(), WEAR_LEVELING_LOGICAL_SIZE), WEAR_LEVELING_SUCCESS) << "Failed to read back the saved data";
        EXPECT_TRUE(memcmp(readback.data(), verify_data.data(), WEAR_LEVELING_LOGICAL_SIZE) == 0) << "Readback for address " << address << " did not match";
    }

    // Verify the full range of the logical area got written
    EXPECT_EQ(final_address, WEAR_LEVELING_LOGICAL_SIZE - 3) << "Invalid final write address";
}

/**
 * This test verifies readback after playback of the write log, simulating power loss and reboot.
 */
TEST_F(WearLeveling2ByteOptimizedWrites, PlaybackReadbackOptimized64_Success) {
    auto& inst     = MockBackingStore::Instance();
    auto  logstart = inst.storage_begin() + (WEAR_LEVELING_LOGICAL_SIZE / sizeof(backing_store_int_t));

    // Invalid FNV1a_64 hash
    (logstart + 0)->set(0);
    (logstart + 1)->set(0);
    (logstart + 2)->set(0);
    (logstart + 3)->set(0);

    // Set up a 1-byte logical write of 0x11 at logical offset 0x01
    auto entry0 = LOG_ENTRY_MAKE_OPTIMIZED_64(0x01, 0x11);
    (logstart + 4)->set(~entry0.raw16[0]); // start at offset 4 to skip FNV1a_64 result

    wear_leveling_init();
    uint8_t tmp;

    wear_leveling_read(0x01, &tmp, sizeof(tmp));
    EXPECT_EQ(tmp, 0x11) << "Failed to read back the seeded data";
}

/**
 * This test verifies readback after playback of the write log, simulating power loss and reboot.
 */
TEST_F(WearLeveling2ByteOptimizedWrites, PlaybackReadbackWord01_Success) {
    auto& inst     = MockBackingStore::Instance();
    auto  logstart = inst.storage_begin() + (WEAR_LEVELING_LOGICAL_SIZE / sizeof(backing_store_int_t));

    // Invalid FNV1a_64 hash
    (logstart + 0)->set(0);
    (logstart + 1)->set(0);
    (logstart + 2)->set(0);
    (logstart + 3)->set(0);

    // Set up a 1-byte logical write of 1 at logical offset 0x02
    auto entry0 = LOG_ENTRY_MAKE_WORD_01(0x02, 1);
    (logstart + 4)->set(~entry0.raw16[0]); // start at offset 4 to skip FNV1a_64 result

    wear_leveling_init();
    uint8_t tmp;

    wear_leveling_read(0x02, &tmp, sizeof(tmp));
    EXPECT_EQ(tmp, 1) << "Failed to read back the seeded data";
}
