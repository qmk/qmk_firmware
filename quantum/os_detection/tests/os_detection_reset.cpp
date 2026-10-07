// Copyright 2026 Andre Brait (@andrebrait)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <cstdlib>
#include <vector>
#include <string>
#include "gtest/gtest.h"

extern "C" {
#include "quantum.h"
#include "os_detection.h"
#include "eeprom.h"
#include "via.h"
#include "nvm_eeprom_via_internal.h"
#include "nvm_eeconfig.h"
#include "process_quantum.h"

keymap_config_t keymap_config = {};

void eeconfig_read_keymap(keymap_config_t *config) {
    nvm_eeconfig_read_keymap(config);
}

void eeconfig_update_keymap(const keymap_config_t *config) {
    nvm_eeconfig_update_keymap(config);
}

void eeconfig_disable(void) {
    nvm_eeconfig_disable();
}

void advance_time(uint32_t ms);
}

static bool         held[MATRIX_ROWS][MATRIX_COLS];
static uint16_t     keymap[4][MATRIX_ROWS][MATRIX_COLS];
static uint8_t      active_layer;
static unsigned     resets;
static unsigned     reports;
static os_variant_t reported;

static std::vector<uint16_t> packet_lengths(const std::string &output) {
    std::vector<uint16_t> lengths;
    const char           *prefix = "wLength: 0x";
    for (size_t at = 0; (at = output.find(prefix, at)) != std::string::npos; ++at) {
        lengths.push_back(std::strtoul(output.c_str() + at + strlen(prefix), nullptr, 16));
    }
    return lengths;
}

extern "C" {
bool matrix_is_on(uint8_t row, uint8_t col) {
    return held[row][col];
}

uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key) {
    return keymap[layer][key.row][key.col];
}

action_t action_for_key(uint8_t layer, keypos_t key) {
    action_t action = {};
    action.code     = keymap_key_to_keycode(layer, key) == KC_TRNS ? ACTION_TRANSPARENT : ACTION_NO;
    return action;
}

uint8_t layer_switch_get_layer(keypos_t key) {
    return keymap[active_layer][key.row][key.col] == KC_TRNS ? 0 : active_layer;
}

void soft_reset_keyboard(void) {
    ++resets;
}

void reset_keyboard(void) {
    ++resets;
}

bool process_detected_host_os_kb(os_variant_t os) {
    ++reports;
    reported = os;
    return true;
}
}

class OsDetectionResetTest : public ::testing::Test {
   protected:
    void SetUp() override {
        timer_init();
        advance_time(1);
        erase_wlength_data();
        memset(held, 0, sizeof(held));
        memset(keymap, 0, sizeof(keymap));
        active_layer = 0;
        resets = reports = 0;
        reported         = OS_UNSURE;
        for (uintptr_t i = 0; i < TOTAL_EEPROM_BYTE_COUNT; ++i) {
            eeprom_write_byte(reinterpret_cast<uint8_t *>(i), 0xA5);
        }
        keymap_config.raw = 0;
        eeconfig_update_keymap(&keymap_config);
        os_detection_init();
        clear_stored_setups();
        keymap[0][0][0] = OS_DETECTION_SKIP_RESET_KEY;
    }

    void usb(usb_configure_state_t state, usb_hid_protocol_t protocol = USB_PROTOCOL_REPORT) {
        struct usb_device_state device = {};
        device.configure_state         = state;
        device.protocol                = protocol;
        os_detection_notify_usb_device_state_change(device);
    }

    void fingerprint(std::initializer_list<uint16_t> lengths) {
        for (uint16_t length : lengths) {
            process_wlength(length);
        }
    }

    void pending_reset() {
        if (detected_host_os() == OS_UNSURE) {
            fingerprint({0xFF, 0xFF, 0x4});
        }
        usb(USB_DEVICE_STATE_CONFIGURED);
        advance_time(OS_DETECTION_DEBOUNCE);
        os_detection_task();
        advance_time(OS_DETECTION_RESET_DEBOUNCE);
        usb(USB_DEVICE_STATE_INIT);
        advance_time(OS_DETECTION_RESET_DEBOUNCE);
    }

    std::string snapshot() {
        testing::internal::CaptureStdout();
        print_stored_setups();
        return testing::internal::GetCapturedStdout();
    }
};

TEST_F(OsDetectionResetTest, ReinitializationResetsWithoutBypass) {
    pending_reset();
    os_detection_task();
    EXPECT_EQ(resets, 1u);
}

TEST_F(OsDetectionResetTest, HeldKeyCancelsPendingResetWithoutDeferringItUntilRelease) {
    pending_reset();
    held[0][0] = true;
    os_detection_task();
    EXPECT_EQ(resets, 0u);
    held[0][0] = false;
    advance_time(OS_DETECTION_DEBOUNCE * 2);
    os_detection_task();
    EXPECT_EQ(resets, 0u);
    pending_reset();
    os_detection_task();
    EXPECT_EQ(resets, 1u);
}

TEST_F(OsDetectionResetTest, HeldMomentaryLayerWorksBeforeLayerKeyEventsAreProcessed) {
    // Model macOS base + Fn layer, with no MO event processed yet.
    active_layer    = 2;
    keymap[2][0][0] = KC_B;
    keymap[2][1][0] = MO(3);
    keymap[3][0][0] = OS_DETECTION_SKIP_RESET_KEY;
    keymap[3][1][0] = KC_TRNS;
    held[0][0] = held[1][0] = true;
    pending_reset();
    os_detection_task();
    EXPECT_EQ(resets, 0u);
    EXPECT_EQ(active_layer, 2);
}

TEST_F(OsDetectionResetTest, InactiveLayerMappingDoesNotSuppressReset) {
    keymap[0][0][0] = KC_B;
    keymap[1][0][0] = OS_DETECTION_SKIP_RESET_KEY;
    held[0][0]      = true;
    pending_reset();
    os_detection_task();
    EXPECT_EQ(resets, 1u);
}

TEST_F(OsDetectionResetTest, HeldBypassDefersOsDecisionsUntilReleaseWithoutPersistingDisable) {
    held[0][0] = true;
    fingerprint({0x2, 0x24, 0x2, 0x28, 0xFF});
    usb(USB_DEVICE_STATE_CONFIGURED);
    advance_time(OS_DETECTION_DEBOUNCE);
    os_detection_task();
    EXPECT_EQ(reports, 0u);
    EXPECT_EQ(reported, OS_UNSURE);
    EXPECT_EQ(resets, 0u);
    keymap_config_t persisted = {};
    eeconfig_read_keymap(&persisted);
    EXPECT_FALSE(persisted.os_detection_disabled);

    held[0][0] = false;
    os_detection_task();
    EXPECT_EQ(reports, 1u);
    EXPECT_EQ(reported, OS_MACOS);
    EXPECT_EQ(resets, 0u);
}

TEST_F(OsDetectionResetTest, FirstResetSnapshotSurvivesReinitializationUntilExplicitReplacement) {
    fingerprint({0xFF, 0xFF, 0x4});
    pending_reset();
    os_detection_task();
    const auto failure = snapshot();
    EXPECT_EQ(packet_lengths(failure), (std::vector<uint16_t>{0xFF, 0xFF, 0x4}));
    erase_wlength_data();
    fingerprint({0x2, 0x24, 0x2, 0x28, 0xFF});
    pending_reset();
    os_detection_task();
    EXPECT_EQ(packet_lengths(snapshot()), packet_lengths(failure));
    store_setups_in_eeprom();
    EXPECT_EQ(packet_lengths(snapshot()), (std::vector<uint16_t>{0x2, 0x24, 0x2, 0x28, 0xFF}));
    clear_stored_setups();
    const auto cleared = snapshot();
    EXPECT_TRUE(packet_lengths(cleared).empty());
    pending_reset();
    os_detection_task();
    EXPECT_EQ(packet_lengths(snapshot()), (std::vector<uint16_t>{0x2, 0x24, 0x2, 0x28, 0xFF}));
}

TEST_F(OsDetectionResetTest, LongTraceIsBoundedAndDoesNotCorruptAdjacentViaStorage) {
    for (unsigned i = 0; i < 350; ++i) {
        process_wlength(0x100 + i);
    }
    store_setups_in_eeprom();
    const auto            output = snapshot();
    std::vector<uint16_t> expected;
    for (uint16_t length = 0x100; length < 0x132; ++length) {
        expected.push_back(length);
    }
    EXPECT_EQ(packet_lengths(output), expected);
    EXPECT_EQ(eeprom_read_byte(reinterpret_cast<const uint8_t *>(VIA_EEPROM_CUSTOM_CONFIG_ADDR - 1)), 0xA5);
    EXPECT_EQ(eeprom_read_byte(reinterpret_cast<const uint8_t *>(VIA_EEPROM_CONFIG_END)), 0xA5);
    erase_wlength_data();
    EXPECT_EQ(packet_lengths(snapshot()), packet_lengths(output));
    store_setups_in_eeprom();
    EXPECT_TRUE(packet_lengths(snapshot()).empty());
}

TEST_F(OsDetectionResetTest, CorruptSnapshotCountIsRejectedAndRearmed) {
    fingerprint({0xFF, 0xFF, 0x4});
    store_setups_in_eeprom();
    eeprom_write_byte(reinterpret_cast<uint8_t *>(VIA_EEPROM_CUSTOM_CONFIG_ADDR + 2), 255);
    EXPECT_TRUE(packet_lengths(snapshot()).empty());
    pending_reset();
    os_detection_task();
    EXPECT_EQ(packet_lengths(snapshot()), (std::vector<uint16_t>{0xFF, 0xFF, 0x4}));
}

TEST_F(OsDetectionResetTest, ToggleCommitsOnReleaseAndPersistsWithoutClobberingPreferences) {
    keymap_config.nkro           = true;
    keymap_config.no_gui         = true;
    keymap_config.oneshot_enable = true;
    eeconfig_update_keymap(&keymap_config);
    keyrecord_t record   = {};
    record.event.pressed = true;
    EXPECT_FALSE(process_quantum(QK_OS_TOG, &record));
    EXPECT_FALSE(keymap_config.os_detection_disabled);
    EXPECT_EQ(resets, 0u);
    record.event.pressed = false;
    EXPECT_FALSE(process_quantum(QK_OS_TOG, &record));
    EXPECT_TRUE(keymap_config.os_detection_disabled);
    EXPECT_EQ(resets, 0u);

    // Simulate volatile configuration loss and the normal EEPROM reload.
    keymap_config.raw = 0;
    erase_wlength_data();
    eeconfig_read_keymap(&keymap_config);
    EXPECT_TRUE(keymap_config.os_detection_disabled);
    EXPECT_TRUE(keymap_config.nkro);
    EXPECT_TRUE(keymap_config.no_gui);
    EXPECT_TRUE(keymap_config.oneshot_enable);
    process_wlength(0xFF);
    process_wlength(0xFF);
    process_wlength(0xFF);
    usb(USB_DEVICE_STATE_CONFIGURED);
    advance_time(OS_DETECTION_DEBOUNCE);
    os_detection_task();
    EXPECT_EQ(detected_host_os(), OS_UNSURE);
    EXPECT_EQ(reports, 0u);
    pending_reset();
    os_detection_task();
    EXPECT_EQ(resets, 0u);

    record.event.pressed = true;
    EXPECT_FALSE(process_quantum(QK_OS_TOG, &record));
    EXPECT_TRUE(keymap_config.os_detection_disabled);
    EXPECT_EQ(resets, 0u); // Never reboot while the toggle key remains held.
    record.event.pressed = false;
    EXPECT_FALSE(process_quantum(QK_OS_TOG, &record));
    EXPECT_EQ(resets, 1u);
    keymap_config.raw = 0;
    eeconfig_read_keymap(&keymap_config);
    EXPECT_FALSE(keymap_config.os_detection_disabled);
    EXPECT_TRUE(keymap_config.nkro);
    EXPECT_TRUE(keymap_config.no_gui);
    EXPECT_TRUE(keymap_config.oneshot_enable);
}

TEST_F(OsDetectionResetTest, DisablingCancelsQueuedResetAndStopsTraceCollection) {
    process_wlength(0x2);
    process_wlength(0x24);
    store_setups_in_eeprom();
    const auto saved = snapshot();
    pending_reset();
    const unsigned reports_before_disable = reports;
    EXPECT_FALSE(os_detection_toggle());
    os_detection_task();
    EXPECT_EQ(resets, 0u);
    EXPECT_EQ(packet_lengths(snapshot()), packet_lengths(saved));
    process_wlength(0xFF);
    process_wlength(0xFF);
    process_wlength(0xFF);
    usb(USB_DEVICE_STATE_INIT);
    advance_time(OS_DETECTION_RESET_DEBOUNCE);
    os_detection_task();
    EXPECT_EQ(resets, 0u);
    EXPECT_EQ(reports, reports_before_disable);
    EXPECT_EQ(detected_host_os(), OS_UNSURE);
    EXPECT_EQ(packet_lengths(snapshot()), packet_lengths(saved));
    store_setups_in_eeprom();
    EXPECT_TRUE(packet_lengths(snapshot()).empty());
}

TEST_F(OsDetectionResetTest, ReenablingDiscardsDisabledUsbTransitionsAndDetectsFreshFingerprint) {
    EXPECT_FALSE(os_detection_toggle());
    pending_reset();
    EXPECT_TRUE(os_detection_toggle());
    os_detection_task();
    EXPECT_EQ(resets, 0u);
    EXPECT_EQ(reports, 0u);
    process_wlength(0xFF);
    process_wlength(0xFF);
    process_wlength(0xFF);
    usb(USB_DEVICE_STATE_CONFIGURED);
    advance_time(OS_DETECTION_DEBOUNCE);
    os_detection_task();
    EXPECT_EQ(reports, 1u);
    EXPECT_EQ(reported, OS_LINUX);
    pending_reset();
    os_detection_task();
    EXPECT_EQ(resets, 1u);
}

TEST_F(OsDetectionResetTest, ConfiguredReportKvmWithoutStringsStillForcesEnumeration) {
    usb(USB_DEVICE_STATE_CONFIGURED);
    advance_time(OS_DETECTION_RESET_DEBOUNCE * 10);
    os_detection_task();
    ASSERT_EQ(reported, OS_UNSURE);
    usb(USB_DEVICE_STATE_INIT);
    advance_time(OS_DETECTION_RESET_DEBOUNCE * 10);
    os_detection_task();
    EXPECT_EQ(resets, 1u);
    EXPECT_TRUE(packet_lengths(snapshot()).empty());
}

TEST_F(OsDetectionResetTest, BootProtocolDoesNotArmEvenWithWindowsLikeStrings) {
    fingerprint({0xFF, 0xFF, 0x4});
    usb(USB_DEVICE_STATE_CONFIGURED, USB_PROTOCOL_BOOT);
    advance_time(OS_DETECTION_RESET_DEBOUNCE);
    os_detection_task();
    ASSERT_EQ(reported, OS_WINDOWS);
    usb(USB_DEVICE_STATE_INIT, USB_PROTOCOL_BOOT);
    // USB_EVENT_RESET subsequently restores REPORT protocol without a new configured host.
    usb(USB_DEVICE_STATE_INIT, USB_PROTOCOL_REPORT);
    advance_time(OS_DETECTION_RESET_DEBOUNCE * 10);
    os_detection_task();
    EXPECT_EQ(resets, 0u);
}

TEST_F(OsDetectionResetTest, LateBootProtocolCancelsQueuedResetBeforeDebounce) {
    fingerprint({0xFF, 0xFF, 0x4});
    usb(USB_DEVICE_STATE_CONFIGURED);
    advance_time(OS_DETECTION_RESET_DEBOUNCE);
    os_detection_task();
    usb(USB_DEVICE_STATE_INIT);
    os_detection_task();
    EXPECT_EQ(resets, 0u);
    advance_time(OS_DETECTION_RESET_DEBOUNCE - 1);
    os_detection_task();
    EXPECT_EQ(resets, 0u);
    usb(USB_DEVICE_STATE_INIT, USB_PROTOCOL_BOOT);
    usb(USB_DEVICE_STATE_INIT, USB_PROTOCOL_REPORT);
    advance_time(OS_DETECTION_RESET_DEBOUNCE);
    os_detection_task();
    EXPECT_EQ(resets, 0u);
}

TEST_F(OsDetectionResetTest, KnownReportHostForcesKvmReenumerationAndCanRearmAfterReboot) {
    pending_reset(); // New host sends no strings before the forced reboot.
    os_detection_task();
    EXPECT_EQ(resets, 1u);

    // Simulate the resulting MCU reboot and a BIOS session with no string requests.
    erase_wlength_data();
    usb(USB_DEVICE_STATE_CONFIGURED, USB_PROTOCOL_BOOT);
    advance_time(OS_DETECTION_RESET_DEBOUNCE);
    os_detection_task();
    usb(USB_DEVICE_STATE_INIT);
    advance_time(OS_DETECTION_RESET_DEBOUNCE);
    os_detection_task();
    EXPECT_EQ(resets, 1u);

    // A later genuine OS session must arm the next KVM switch again.
    erase_wlength_data();
    fingerprint({0x2, 0x24, 0x2, 0x28, 0xFF});
    pending_reset();
    os_detection_task();
    EXPECT_EQ(resets, 2u);
}

#ifdef OS_DETECTION_BOOT_LOOP_GUARD
TEST_F(OsDetectionResetTest, RapidAutomaticRebootsPersistAndFourthAttemptIsBlocked) {
    for (unsigned count = 1; count <= OS_DETECTION_BOOT_LOOP_GUARD_MAX_REBOOTS; ++count) {
        timer_init();
        advance_time(1);
        os_detection_init(); // New MCU boot; persisted guard record survives.
        pending_reset();
        os_detection_task();
        EXPECT_EQ(resets, count);
    }
    timer_init();
    advance_time(1);
    os_detection_init();
    pending_reset();
    os_detection_task();
    EXPECT_EQ(resets, OS_DETECTION_BOOT_LOOP_GUARD_MAX_REBOOTS);
    advance_time(OS_DETECTION_BOOT_LOOP_GUARD_FAST_MS * 2);
    usb(USB_DEVICE_STATE_INIT);
    advance_time(OS_DETECTION_RESET_DEBOUNCE);
    os_detection_task();
    EXPECT_EQ(resets, OS_DETECTION_BOOT_LOOP_GUARD_MAX_REBOOTS);
}

TEST_F(OsDetectionResetTest, ContinuousConfiguredUsbRearmsGuardDespiteLedNotifications) {
    for (unsigned count = 0; count < OS_DETECTION_BOOT_LOOP_GUARD_MAX_REBOOTS; ++count) {
        timer_init();
        advance_time(1);
        os_detection_init();
        pending_reset();
        os_detection_task();
    }
    timer_init();
    advance_time(1);
    os_detection_init();
    pending_reset();
    os_detection_task();
    ASSERT_EQ(resets, OS_DETECTION_BOOT_LOOP_GUARD_MAX_REBOOTS);
    usb(USB_DEVICE_STATE_CONFIGURED);
    advance_time(OS_DETECTION_BOOT_LOOP_GUARD_REARM_MS - 1);
    os_detection_task();              // Observe the stable session before a later LED notification.
    usb(USB_DEVICE_STATE_CONFIGURED); // Same link state, e.g. an LED update.
    os_detection_task();
    EXPECT_EQ(resets, OS_DETECTION_BOOT_LOOP_GUARD_MAX_REBOOTS);
    advance_time(1);
    os_detection_task(); // Clear the persisted count once, without rebooting.
    EXPECT_EQ(resets, OS_DETECTION_BOOT_LOOP_GUARD_MAX_REBOOTS);
    usb(USB_DEVICE_STATE_INIT);
    advance_time(OS_DETECTION_RESET_DEBOUNCE);
    os_detection_task();
    EXPECT_EQ(resets, OS_DETECTION_BOOT_LOOP_GUARD_MAX_REBOOTS + 1);
}

TEST_F(OsDetectionResetTest, LongUptimeBreaksConsecutiveRapidResetSequence) {
    pending_reset();
    os_detection_task();
    ASSERT_EQ(resets, 1u);
    timer_init();
    advance_time(1);
    os_detection_init();
    advance_time(OS_DETECTION_BOOT_LOOP_GUARD_FAST_MS);
    pending_reset();
    os_detection_task();
    ASSERT_EQ(resets, 2u);
    for (unsigned count = 0; count < OS_DETECTION_BOOT_LOOP_GUARD_MAX_REBOOTS; ++count) {
        timer_init();
        advance_time(1);
        os_detection_init();
        pending_reset();
        os_detection_task();
        EXPECT_EQ(resets, count + 3);
    }
}

TEST_F(OsDetectionResetTest, ExactlyOneSecondIsNotARapidReset) {
    pending_reset();
    os_detection_task();
    ASSERT_EQ(resets, 1u);
    timer_init();
    advance_time(OS_DETECTION_BOOT_LOOP_GUARD_FAST_MS - OS_DETECTION_DEBOUNCE - 2 * OS_DETECTION_RESET_DEBOUNCE);
    os_detection_init();
    pending_reset(); // Request occurs exactly at FAST_MS.
    os_detection_task();
    ASSERT_EQ(resets, 2u);
    for (unsigned count = 0; count < OS_DETECTION_BOOT_LOOP_GUARD_MAX_REBOOTS; ++count) {
        timer_init();
        advance_time(1);
        os_detection_init();
        pending_reset();
        os_detection_task();
        EXPECT_EQ(resets, count + 3);
    }
}
#endif

TEST_F(OsDetectionResetTest, DescriptorAssemblyPostponesForcedResetUntilQuiet) {
    fingerprint({0xFF, 0xFF, 0x4});
    usb(USB_DEVICE_STATE_CONFIGURED);
    advance_time(OS_DETECTION_DEBOUNCE);
    os_detection_task();
    usb(USB_DEVICE_STATE_INIT);
    advance_time(OS_DETECTION_RESET_DEBOUNCE - 1);
    os_detection_notify_usb_descriptor_request(); // Non-string descriptor request.
    os_detection_task();
    EXPECT_EQ(resets, 0u);
    advance_time(OS_DETECTION_RESET_DEBOUNCE - 1);
    os_detection_task();
    EXPECT_EQ(resets, 0u);
    advance_time(1);
    os_detection_task();
    EXPECT_EQ(resets, 1u);
    EXPECT_EQ(packet_lengths(snapshot()), (std::vector<uint16_t>{0xFF, 0xFF, 0x4}));
}

TEST_F(OsDetectionResetTest, DescriptorActivityLetsLateBootProtocolCancelReenumeration) {
    fingerprint({0xFF, 0xFF, 0x4});
    usb(USB_DEVICE_STATE_CONFIGURED);
    advance_time(OS_DETECTION_DEBOUNCE);
    os_detection_task();
    usb(USB_DEVICE_STATE_INIT);
    advance_time(OS_DETECTION_RESET_DEBOUNCE - 1);
    os_detection_notify_usb_descriptor_request();
    advance_time(OS_DETECTION_RESET_DEBOUNCE - 1);
    os_detection_task();
    EXPECT_EQ(resets, 0u); // Original INIT timeout has already elapsed.
    usb(USB_DEVICE_STATE_CONFIGURED, USB_PROTOCOL_BOOT);
    advance_time(OS_DETECTION_RESET_DEBOUNCE);
    os_detection_task();
    EXPECT_EQ(resets, 0u);
}

TEST_F(OsDetectionResetTest, HeldToggleKeyCancelsAutomaticResetDuringModeChange) {
    pending_reset();
    keymap[0][0][0] = QK_OS_TOG;
    held[0][0]      = true;
    os_detection_task();
    EXPECT_EQ(resets, 0u);
    held[0][0] = false;
    advance_time(OS_DETECTION_RESET_DEBOUNCE);
    os_detection_task();
    EXPECT_EQ(resets, 0u);
}
