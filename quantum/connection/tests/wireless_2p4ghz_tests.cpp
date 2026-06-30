// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C" {
#include "wireless_2p4ghz.h"
}

TEST(Wireless2P4GhzWeakDefaults, IsConnectedReturnsFalse) {
    EXPECT_FALSE(wireless_2p4ghz_is_connected());
}

TEST(Wireless2P4GhzWeakDefaults, CanSendNkroReturnsFalse) {
    EXPECT_FALSE(wireless_2p4ghz_can_send_nkro());
}

TEST(Wireless2P4GhzWeakDefaults, KeyboardLedsReturnsZero) {
    EXPECT_EQ(wireless_2p4ghz_keyboard_leds(), 0);
}

TEST(Wireless2P4GhzWeakDefaults, InitDoesNotCrash) {
    wireless_2p4ghz_init();
    SUCCEED();
}

TEST(Wireless2P4GhzWeakDefaults, TaskDoesNotCrash) {
    wireless_2p4ghz_task();
    SUCCEED();
}

TEST(Wireless2P4GhzWeakDefaults, UnpairDoesNotCrash) {
    wireless_2p4ghz_unpair();
    SUCCEED();
}

TEST(Wireless2P4GhzWeakDefaults, SendKeyboardDoesNotCrash) {
    report_keyboard_t report = {0};
    wireless_2p4ghz_send_keyboard(&report);
    wireless_2p4ghz_send_keyboard(NULL);
    SUCCEED();
}

TEST(Wireless2P4GhzWeakDefaults, SendNkroDoesNotCrash) {
    report_nkro_t report = {0};
    wireless_2p4ghz_send_nkro(&report);
    wireless_2p4ghz_send_nkro(NULL);
    SUCCEED();
}

TEST(Wireless2P4GhzWeakDefaults, SendMouseDoesNotCrash) {
    report_mouse_t report = {0};
    wireless_2p4ghz_send_mouse(&report);
    wireless_2p4ghz_send_mouse(NULL);
    SUCCEED();
}

TEST(Wireless2P4GhzWeakDefaults, SendConsumerDoesNotCrash) {
    wireless_2p4ghz_send_consumer(0x00E2);
    SUCCEED();
}

TEST(Wireless2P4GhzWeakDefaults, SendSystemDoesNotCrash) {
    wireless_2p4ghz_send_system(0x0081);
    SUCCEED();
}

TEST(Wireless2P4GhzWeakDefaults, SendRawHidDoesNotCrash) {
    uint8_t data[32] = {0};
    wireless_2p4ghz_send_raw_hid(data, sizeof(data));
    SUCCEED();
}
