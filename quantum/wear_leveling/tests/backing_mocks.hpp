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
#include "fnv.h"
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

    // Type containing each of the entries and the write counts
    using storage_t = std::array<MockBackingStoreElement, BACKING_STORE_ELEMENT_COUNT::value>;

    // Whether the backing store is locked
    bool locked;
    // The actual data stored in the emulated flash
    storage_t backing_storage;
    // The number of erase cycles that have occurred
    std::uint64_t backing_erasure_count;
    // The max number of writes to an element of the backing store
    std::uint64_t backing_max_write_count;
    // The total number of writes to all elements of the backing store
    std::uint64_t backing_total_write_count;
    // The write log for the backing store
    std::vector<MockBackingStoreLogEntry> write_log;

    // The number of times each API was invoked
    std::uint64_t backing_init_invoke_count;
    std::uint64_t backing_unlock_invoke_count;
    std::uint64_t backing_erase_invoke_count;
    std::uint64_t backing_write_invoke_count;
    std::uint64_t backing_lock_invoke_count;

    // Whether init should succeed
    std::function<bool(std::uint64_t)> init_success_callback;
    // Whether erase should succeed
    std::function<bool(std::uint64_t)> erase_success_callback;
    // Whether unlocks should succeed
    std::function<bool(std::uint64_t)> unlock_success_callback;
    // Whether writes should succeed
    std::function<bool(std::uint64_t, std::uint32_t)> write_success_callback;
    // Whether locks should succeed
    std::function<bool(std::uint64_t)> lock_success_callback;

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

    std::uint64_t erasure_count() const {
        return backing_erasure_count;
    }
    std::uint64_t max_write_count() const {
        return backing_max_write_count;
    }
    std::uint64_t total_write_count() const {
        return backing_total_write_count;
    }

    // The number of times each API was invoked
    std::uint64_t init_invoke_count() const {
        return backing_init_invoke_count;
    }
    std::uint64_t unlock_invoke_count() const {
        return backing_unlock_invoke_count;
    }
    std::uint64_t erase_invoke_count() const {
        return backing_erase_invoke_count;
    }
    std::uint64_t write_invoke_count() const {
        return backing_write_invoke_count;
    }
    std::uint64_t lock_invoke_count() const {
        return backing_lock_invoke_count;
    }

    // Clear out the internal data for the next run
    void reset_instance();

    bool is_locked() const {
        return locked;
    }

    // APIs for the backing store
    bool init();
    bool unlock();
    bool erase();
    bool write(std::uint32_t address, backing_store_int_t value);
    bool lock();
    bool read(std::uint32_t address, backing_store_int_t& value) const;

    // Control over when init/writes/erases should succeed
    void set_init_callback(std::function<bool(std::uint64_t)> callback) {
        init_success_callback = callback;
    }
    void set_erase_callback(std::function<bool(std::uint64_t)> callback) {
        erase_success_callback = callback;
    }
    void set_unlock_callback(std::function<bool(std::uint64_t)> callback) {
        unlock_success_callback = callback;
    }
    void set_write_callback(std::function<bool(std::uint64_t, std::uint32_t)> callback) {
        write_success_callback = callback;
    }
    void set_lock_callback(std::function<bool(std::uint64_t)> callback) {
        lock_success_callback = callback;
    }

    auto storage_begin() const -> decltype(backing_storage.begin()) {
        return backing_storage.begin();
    }
    auto storage_end() const -> decltype(backing_storage.end()) {
        return backing_storage.end();
    }

    auto storage_begin() -> decltype(backing_storage.begin()) {
        return backing_storage.begin();
    }
    auto storage_end() -> decltype(backing_storage.end()) {
        return backing_storage.end();
    }

    auto log_begin() -> decltype(write_log.begin()) {
        return write_log.begin();
    }
    auto log_end() -> decltype(write_log.end()) {
        return write_log.end();
    }

    auto log_begin() const -> decltype(write_log.begin()) {
        return write_log.begin();
    }
    auto log_end() const -> decltype(write_log.end()) {
        return write_log.end();
    }
};
