// Copyright 2026 Andre Brait (@andrebrait)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gtest/gtest.h"

extern "C" {
#include "os_detection.h"
#include "keycode_config.h"
#include "nvm_eeconfig.h"

keymap_config_t keymap_config = {};
static bool     master        = true;

bool is_keyboard_master(void) {
    return master;
}

void eeconfig_update_keymap(const keymap_config_t *config) {
    nvm_eeconfig_update_keymap(config);
}
}

TEST(OsDetectionSplitTest, SlaveFollowsMasterDespiteItsOwnSavedDisabledPreference) {
    master            = true;
    keymap_config.raw = 0;
    os_detection_init();
    EXPECT_FALSE(os_detection_toggle()); // This half saves detection OFF as master.
    EXPECT_TRUE(keymap_config.os_detection_disabled);

    master = false; // The other half is now USB master and has detection ON.
    slave_update_detected_host_os(OS_MACOS);
    EXPECT_EQ(detected_host_os(), OS_MACOS);
    slave_update_detected_host_os(OS_UNSURE); // Master switched detection OFF.
    EXPECT_EQ(detected_host_os(), OS_UNSURE);

    slave_update_detected_host_os(OS_WINDOWS);
    master = true; // Local EEPROM preference becomes authoritative again.
    EXPECT_EQ(detected_host_os(), OS_UNSURE);
}
