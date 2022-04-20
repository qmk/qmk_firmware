// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "backing_mocks.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Backing Store Mock implementation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MockBackingStore::reset_instance() {
    for (auto&& e : backing_storage)
        e.reset();
    backing_erasure_count     = 0;
    backing_max_write_count   = 0;
    backing_total_write_count = 0;
    init_fail                 = false;
    write_fail                = false;
    erase_fail_index          = BACKING_STORE_ELEMENT_COUNT::value;
    write_log.clear();
}

bool MockBackingStore::init(void) {
    return !init_fail;
}

bool MockBackingStore::erase(void) {
    // Erase each slot
    for (std::size_t i = 0; i < backing_storage.size(); ++i) {
        // Drop out of erase early with failure if we need to
        if (i >= erase_fail_index) {
            append_log(true);
            return false;
        }

        backing_storage[i].erase();
    }

    // Keep track of the erase in the write log so that we can verify during tests
    append_log(true);

    ++backing_erasure_count;
    return true;
}

bool MockBackingStore::write(uint32_t address, backing_store_int_t value) {
    // precondition: value's buffer size already matches BACKING_STORE_WRITE_SIZE
    EXPECT_TRUE(address % BACKING_STORE_WRITE_SIZE == 0) << "Supplied address was not aligned with the backing store integral size.";
    EXPECT_TRUE(address + BACKING_STORE_WRITE_SIZE <= WEAR_LEVELING_BACKING_SIZE) << "Address would result of out-of-bounds access.";

    // Drop out of write early with failure if we need to
    if (write_fail) {
        return false;
    }

    // Write the complement as we're simulating flash memory -- 0xFF means 0x00
    std::size_t index = address / BACKING_STORE_WRITE_SIZE;
    backing_storage[index].set(~value);

    // Keep track of the write log so that we can verify during tests
    append_log(address, value);

    // Keep track of the total number of writes into the backing store
    ++backing_total_write_count;

    return true;
}

bool MockBackingStore::read(uint32_t address, backing_store_int_t& value) const {
    // precondition: value's buffer size already matches BACKING_STORE_WRITE_SIZE
    EXPECT_TRUE(address % BACKING_STORE_WRITE_SIZE == 0) << "Supplied address was not aligned with the backing store integral size.";
    EXPECT_TRUE(address + BACKING_STORE_WRITE_SIZE <= WEAR_LEVELING_BACKING_SIZE) << "Address would result of out-of-bounds access.";

    // Read and take the complement as we're simulating flash memory -- 0xFF means 0x00
    std::size_t index = address / BACKING_STORE_WRITE_SIZE;
    value             = ~backing_storage[index].get();

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Backing Implementation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" bool backing_store_init(void) {
    return MockBackingStore::Instance().init();
}

extern "C" bool backing_store_erase(void) {
    return MockBackingStore::Instance().erase();
}

extern "C" bool backing_store_write(uint32_t address, backing_store_int_t value) {
    return MockBackingStore::Instance().write(address, value);
}

extern "C" bool backing_store_read(uint32_t address, backing_store_int_t* value) {
    return MockBackingStore::Instance().read(address, *value);
}
