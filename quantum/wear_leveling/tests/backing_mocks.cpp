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

    locked = true;

    backing_erasure_count     = 0;
    backing_max_write_count   = 0;
    backing_total_write_count = 0;

    backing_init_invoke_count   = 0;
    backing_unlock_invoke_count = 0;
    backing_erase_invoke_count  = 0;
    backing_write_invoke_count  = 0;
    backing_lock_invoke_count   = 0;

    init_success_callback   = [](std::uint64_t) { return true; };
    erase_success_callback  = [](std::uint64_t) { return true; };
    unlock_success_callback = [](std::uint64_t) { return true; };
    write_success_callback  = [](std::uint64_t, std::uint32_t) { return true; };
    lock_success_callback   = [](std::uint64_t) { return true; };

    write_log.clear();
}

bool MockBackingStore::init(void) {
    ++backing_init_invoke_count;

    if (init_success_callback) {
        return init_success_callback(backing_init_invoke_count);
    }
    return true;
}

bool MockBackingStore::unlock(void) {
    ++backing_unlock_invoke_count;

    EXPECT_TRUE(is_locked()) << "Attempted to unlock but was not locked";
    locked = false;

    if (unlock_success_callback) {
        return unlock_success_callback(backing_unlock_invoke_count);
    }
    return true;
}

bool MockBackingStore::erase(void) {
    ++backing_erase_invoke_count;

    // Erase each slot
    for (std::size_t i = 0; i < backing_storage.size(); ++i) {
        // Drop out of erase early with failure if we need to
        if (erase_success_callback && !erase_success_callback(backing_erase_invoke_count)) {
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
    ++backing_write_invoke_count;

    // precondition: value's buffer size already matches BACKING_STORE_WRITE_SIZE
    EXPECT_TRUE(address % BACKING_STORE_WRITE_SIZE == 0) << "Supplied address was not aligned with the backing store integral size";
    EXPECT_TRUE(address + BACKING_STORE_WRITE_SIZE <= WEAR_LEVELING_BACKING_SIZE) << "Address would result of out-of-bounds access";
    EXPECT_FALSE(is_locked()) << "Write was attempted without being unlocked first";

    // Drop out of write early with failure if we need to
    if (write_success_callback && !write_success_callback(backing_write_invoke_count, address)) {
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

bool MockBackingStore::lock(void) {
    ++backing_lock_invoke_count;

    EXPECT_FALSE(is_locked()) << "Attempted to lock but was not unlocked";
    locked = true;

    if (lock_success_callback) {
        return lock_success_callback(backing_lock_invoke_count);
    }
    return true;
}

bool MockBackingStore::read(uint32_t address, backing_store_int_t& value) const {
    // precondition: value's buffer size already matches BACKING_STORE_WRITE_SIZE
    EXPECT_TRUE(address % BACKING_STORE_WRITE_SIZE == 0) << "Supplied address was not aligned with the backing store integral size";
    EXPECT_TRUE(address + BACKING_STORE_WRITE_SIZE <= WEAR_LEVELING_BACKING_SIZE) << "Address would result of out-of-bounds access";

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

extern "C" bool backing_store_unlock(void) {
    return MockBackingStore::Instance().unlock();
}

extern "C" bool backing_store_erase(void) {
    return MockBackingStore::Instance().erase();
}

extern "C" bool backing_store_write(uint32_t address, backing_store_int_t value) {
    return MockBackingStore::Instance().write(address, value);
}

extern "C" bool backing_store_lock(void) {
    return MockBackingStore::Instance().lock();
}

extern "C" bool backing_store_read(uint32_t address, backing_store_int_t* value) {
    return MockBackingStore::Instance().read(address, *value);
}
