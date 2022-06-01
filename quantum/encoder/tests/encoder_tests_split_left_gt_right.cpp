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

bool isLeftHand;

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!isLeftHand) {
        // this method has no effect on slave half
        printf("ignoring update on right hand (%d,%s)\n", index, clockwise ? "CW" : "CC");
        return true;
    }
    updates[updates_array_idx % 32] = {index, clockwise};
    updates_array_idx++;
    return true;
}

bool setAndRead(pin_t pin, bool val) {
    setPin(pin, val);
    return encoder_read();
}

class EncoderSplitTestLeftGreaterThanRight : public ::testing::Test {
   protected:
    void SetUp() override {
        updates_array_idx = 0;
        for (int i = 0; i < 32; i++) {
            pinIsInputHigh[i] = 0;
            pins[i]           = 0;
        }
    }
};

TEST_F(EncoderSplitTestLeftGreaterThanRight, TestInitLeft) {
    isLeftHand = true;
    encoder_init();
    EXPECT_EQ(pinIsInputHigh[0], true);
    EXPECT_EQ(pinIsInputHigh[1], true);
    EXPECT_EQ(pinIsInputHigh[2], true);
    EXPECT_EQ(pinIsInputHigh[3], true);
    EXPECT_EQ(pinIsInputHigh[4], true);
    EXPECT_EQ(pinIsInputHigh[5], true);
    EXPECT_EQ(pinIsInputHigh[6], false);
    EXPECT_EQ(pinIsInputHigh[7], false);
    EXPECT_EQ(pinIsInputHigh[8], false);
    EXPECT_EQ(pinIsInputHigh[9], false);
    EXPECT_EQ(updates_array_idx, 0); // no updates received
}

TEST_F(EncoderSplitTestLeftGreaterThanRight, TestInitRight) {
    isLeftHand = false;
    encoder_init();
    EXPECT_EQ(pinIsInputHigh[0], false);
    EXPECT_EQ(pinIsInputHigh[1], false);
    EXPECT_EQ(pinIsInputHigh[2], false);
    EXPECT_EQ(pinIsInputHigh[3], false);
    EXPECT_EQ(pinIsInputHigh[4], false);
    EXPECT_EQ(pinIsInputHigh[5], false);
    EXPECT_EQ(pinIsInputHigh[6], true);
    EXPECT_EQ(pinIsInputHigh[7], true);
    EXPECT_EQ(pinIsInputHigh[8], true);
    EXPECT_EQ(pinIsInputHigh[9], true);
    EXPECT_EQ(updates_array_idx, 0); // no updates received
}

TEST_F(EncoderSplitTestLeftGreaterThanRight, TestOneClockwiseLeft) {
    isLeftHand = true;
    encoder_init();
    // send 4 pulses. with resolution 4, that's one step and we should get 1 update.
    setAndRead(0, false);
    setAndRead(1, false);
    setAndRead(0, true);
    setAndRead(1, true);

    EXPECT_EQ(updates_array_idx, 1); // one update received
    EXPECT_EQ(updates[0].index, 0);
    EXPECT_EQ(updates[0].clockwise, true);
}

TEST_F(EncoderSplitTestLeftGreaterThanRight, TestOneClockwiseRightSent) {
    isLeftHand = false;
    encoder_init();
    // send 4 pulses. with resolution 4, that's one step and we should get 1 update.
    setAndRead(6, false);
    setAndRead(7, false);
    setAndRead(6, true);
    setAndRead(7, true);

    uint8_t slave_state[32] = {0};
    encoder_state_raw(slave_state);

    EXPECT_EQ(slave_state[0], 0xFF);
    EXPECT_EQ(slave_state[1], 0);
}

TEST_F(EncoderSplitTestLeftGreaterThanRight, TestMultipleEncodersRightReceived) {
    isLeftHand = true;
    encoder_init();

    uint8_t slave_state[32] = {1, 0xFF}; // First right encoder is CCW, Second right encoder no change, third right encoder CW
    encoder_update_raw(slave_state);

    EXPECT_EQ(updates_array_idx, 2); // two updates received, one for each changed item on the right side
    EXPECT_EQ(updates[0].index, 3);
    EXPECT_EQ(updates[0].clockwise, false);
    EXPECT_EQ(updates[1].index, 4);
    EXPECT_EQ(updates[1].clockwise, true);
}
