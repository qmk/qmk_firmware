/* Copyright 2021 Balz Guenat
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <vector>
#include <algorithm>
#include <stdio.h>

extern "C" {
#include "encoder.h"
#include "encoder/tests/mock_split.h"
}

struct update {
    int8_t index;
    bool   clockwise;
};

uint8_t updates_array_idx = 0;
update  updates[32];

bool isMaster;
bool isLeftHand;

extern "C" {
bool is_keyboard_master(void) {
    return isMaster;
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!is_keyboard_master()) {
        // this method has no effect on slave half
        printf("ignoring update on slave (%d,%s)\n", index, clockwise ? "CW" : "CC");
        return true;
    }
    updates[updates_array_idx % 32] = {index, clockwise};
    updates_array_idx++;
    return true;
}
};

bool setAndRead(pin_t pin, bool val) {
    setPin(pin, val);
    return encoder_task();
}

class EncoderSplitTestNoLeft : public ::testing::Test {
   protected:
    void SetUp() override {
        updates_array_idx = 0;
        for (int i = 0; i < 32; i++) {
            pinIsInputHigh[i] = 0;
            pins[i]           = 0;
        }
    }
};

TEST_F(EncoderSplitTestNoLeft, TestInitLeft) {
    isLeftHand = true;
    encoder_init();
    EXPECT_EQ(pinIsInputHigh[0], false);
    EXPECT_EQ(pinIsInputHigh[1], false);
    EXPECT_EQ(pinIsInputHigh[2], false);
    EXPECT_EQ(pinIsInputHigh[3], false);
    EXPECT_EQ(updates_array_idx, 0); // no updates received
}

TEST_F(EncoderSplitTestNoLeft, TestInitRight) {
    isLeftHand = false;
    encoder_init();
    EXPECT_EQ(pinIsInputHigh[0], true);
    EXPECT_EQ(pinIsInputHigh[1], true);
    EXPECT_EQ(pinIsInputHigh[2], true);
    EXPECT_EQ(pinIsInputHigh[3], true);
    EXPECT_EQ(updates_array_idx, 0); // no updates received
}

TEST_F(EncoderSplitTestNoLeft, TestOneClockwiseLeftMaster) {
    isMaster   = true;
    isLeftHand = false;
    encoder_init();
    // send 4 pulses. with resolution 4, that's one step and we should get 1 update.
    setAndRead(2, false);
    setAndRead(3, false);
    setAndRead(2, true);
    setAndRead(3, true);

    EXPECT_EQ(updates_array_idx, 1); // one update received
    EXPECT_EQ(updates[0].index, 1);
    EXPECT_EQ(updates[0].clockwise, true);

    int              events_queued = 0;
    encoder_events_t events;
    encoder_retrieve_events(&events);
    while (events.tail != events.head) {
        events.tail = (events.tail + 1) % MAX_QUEUED_ENCODER_EVENTS;
        ++events_queued;
    }
    EXPECT_EQ(events_queued, 0); // No events should be queued on master
}

TEST_F(EncoderSplitTestNoLeft, TestOneClockwiseRightSlave) {
    isMaster   = false;
    isLeftHand = false;
    encoder_init();
    // send 4 pulses. with resolution 4, that's one step and we should get 1 update.
    setAndRead(2, false);
    setAndRead(3, false);
    setAndRead(2, true);
    setAndRead(3, true);

    EXPECT_EQ(updates_array_idx, 0); // no updates received

    int              events_queued = 0;
    encoder_events_t events;
    encoder_retrieve_events(&events);
    while (events.tail != events.head) {
        events.tail = (events.tail + 1) % MAX_QUEUED_ENCODER_EVENTS;
        ++events_queued;
    }
    EXPECT_EQ(events_queued, 1); // One event should be queued on slave
}
