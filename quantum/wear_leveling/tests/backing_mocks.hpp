// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <type_traits>
#include <vector>

extern "C" {
#include "wear_leveling.h"
#include "wear_leveling_internal.h"
};

// Maximum number of mock write log entries to keep
using MOCK_WRITE_LOG_MAX_ENTRIES = std::integral_constant<std::size_t, 1024>;
// Complement to the backing store integral, for emulating flash erases of all bytes=0xFF
using BACKING_STORE_INTEGRAL_COMPLEMENT = std::integral_constant<backing_store_int_t, ((backing_store_int_t)(~(backing_store_int_t)0))>;
// Total number of elements stored in the backing arrays
using BACKING_STORE_ELEMENT_COUNT = std::integral_constant<std::size_t, (WEAR_LEVELING_BACKING_SIZE / sizeof(backing_store_int_t))>;

class MockBackingStoreElement {
   private:
    backing_store_int_t value;
    std::size_t         writes;
    std::size_t         erases;

   public:
    MockBackingStoreElement() : value(BACKING_STORE_INTEGRAL_COMPLEMENT::value), writes(0), erases(0) {}
    void reset() {
        erase();
        writes = 0;
        erases = 0;
    }
    void erase() {
        if (!is_erased()) {
            ++erases;
        }
        value = BACKING_STORE_INTEGRAL_COMPLEMENT::value;
    }
    backing_store_int_t get() const {
        return value;
    }
    void set(const backing_store_int_t& v) {
        EXPECT_TRUE(is_erased()) << "Attempted write at index which isn't empty.";
        value = v;
        ++writes;
    }
    std::size_t num_writes() const {
        return writes;
    }
    std::size_t num_erases() const {
        return erases;
    }
    bool is_erased() const {
        return value == BACKING_STORE_INTEGRAL_COMPLEMENT::value;
    }
};

struct MockBackingStoreLogEntry {
    MockBackingStoreLogEntry(uint32_t address, backing_store_int_t value) : address(address), value(value), erased(false) {}
    MockBackingStoreLogEntry(bool erased) : address(0), value(0), erased(erased) {}
    uint32_t            address = 0;     // The address of the operation
    backing_store_int_t value   = 0;     // The value of the operation
    bool                erased  = false; // Whether the entire backing store was erased
};

class MockBackingStore {
   private:
    MockBackingStore() {
        reset_instance();
    }

    // The actual data stored in the emulated flash
    std::array<MockBackingStoreElement, BACKING_STORE_ELEMENT_COUNT::value> backing_storage;
    // The number of erase cycles that have occurred
    std::uint64_t backing_erasure_count;
    // The max number of writes to an element of the backing store
    std::uint64_t backing_max_write_count;
    // The total number of writes to all elements of the backing store
    std::uint64_t backing_total_write_count;
    // The write log for the backing store
    std::vector<MockBackingStoreLogEntry> write_log;
    // Whether init should fail
    bool init_fail;
    // Whether unlocks should fail
    bool unlock_fail;
    // Whether writes should fail
    bool write_fail;
    // Whether locks should fail
    bool lock_fail;
    // The element index at which an erase should fail
    std::size_t erase_fail_index;

    template <typename... Args>
    void append_log(Args&&... args) {
        if (write_log.size() < MOCK_WRITE_LOG_MAX_ENTRIES::value) {
            write_log.emplace_back(std::forward<Args>(args)...);
        }
    }

   public:
    static MockBackingStore& Instance() {
        static MockBackingStore instance;
        return instance;
    }

    // Clear out the internal data for the next run
    void reset_instance();

    // APIs for the backing store
    bool init();
    bool unlock();
    bool erase();
    bool write(std::uint32_t address, backing_store_int_t value);
    bool lock();
    bool read(std::uint32_t address, backing_store_int_t& value) const;

    // Control over when init/writes/erases should fail
    void set_init_fail(bool fail) {
        init_fail = fail;
    }
    void set_unlock_fail(bool fail) {
        unlock_fail = fail;
    }
    void set_erase_fail(std::size_t fail_index) {
        erase_fail_index = fail_index;
    }
    void set_write_fail(bool fail) {
        write_fail = fail;
    }
    void set_lock_fail(bool fail) {
        lock_fail = fail;
    }

    auto storage_begin() const -> decltype(backing_storage.begin()) {
        return backing_storage.begin();
    }
    auto storage_end() const -> decltype(backing_storage.end()) {
        return backing_storage.end();
    }

    auto log_begin() const -> decltype(write_log.begin()) {
        return write_log.begin();
    }
    auto log_end() const -> decltype(write_log.end()) {
        return write_log.end();
    }
};
